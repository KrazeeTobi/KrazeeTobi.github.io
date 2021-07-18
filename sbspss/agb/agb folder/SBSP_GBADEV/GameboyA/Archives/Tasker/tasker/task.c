/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "main.h"
#include "task.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================
extern void saveSystemStack(void);
extern void setSystemStack(void);
extern void executeTaskingSystem(TASK *taskActive);
extern void returnFromTaskingSystem(void);
extern void restoreTaskRegisters(TASK *taskActive);

extern long task1Stack[];
extern long task2Stack[];
extern long task3Stack[];
extern long task4Stack[];
extern long task5Stack[];
// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================
TASK *global_activeTask;		//task currently active
TASK *global_spawnedTask;		//last task spawned (so the spawner can know who its child is)

long tasksRunning;					//num tasks running.
long systemStack;
long systemRA;
// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================
#define MAIN_TASK_ID					(0x2000)
#define STACK_RESERVE 				(24)
#define MAX_TASK_STACKS				(5)			//temp debug...

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================
static BOOL deleteActiveTask(TASK *taskPtr);
static void killTaskChildren(TASK *taskPtr, TASK_ID taskID, TASK_MASK taskMask);

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================

/*
 *	void initTaskingSystem(void *taskFunction, u_short stackSize, long taskPriority)
 *
 *  PARAMETERS:		taskFunction:		Initial task function (usually main task)
 *                stackSize:			Stack size
 *                taskPriority:		Priority
 *
 *  DESCRIPTION:	Init tasking sytem and jump to taskFunction
 *
 *  RETURNS:			Never returns
 */
void initTaskingSystem(void *taskFunction, u_short stackSize, long taskPriority)
{
	//no active tasks
	global_activeTask = NULL;

	//no tasks running
	tasksRunning = 0;

	//spawn main task
	spawnTask(taskFunction, NULL_TASK, stackSize, taskPriority, MAIN_TASK_ID, GLOBAL_TASK);

	//never returns, jumps to taskFunction
	executeTaskingSystem(global_spawnedTask);
}

/*
 *	TASK *spawnTask(void(*taskFunction)(void), void(*taskDestructor)(void), u_short stackSize,
 *									long taskPriority, TASK_ID taskID, TASK_TYPE taskType)
 *
 *  PARAMETERS:		taskFunction:		Task function
 *                taskDestructor:	Function to call upon task destruction
 *                stackSize:			Stack size
 *								taskPriority:		Task priority
 *                taskID:					Task ID
 *								taskType:				Task type
 *
 *  DESCRIPTION:	Spawns a new task
 *
 *  RETURNS:			Pointer to spawned task
 */
TASK *spawnTask(void(*taskFunction)(void), void(*taskDestructor)(void), u_short stackSize, long taskPriority, TASK_ID taskID, TASK_TYPE taskType)
{
	TASK *taskSearch;
	u_long uniquePriority;
	long taskCount;
	static TASK_ID uniqueTaskID = 0;

	//for cheesy stack handler
	long *taskStacks[MAX_TASK_STACKS] = {
		task1Stack,
		task2Stack,
		task3Stack,
		task4Stack,
		task5Stack,
	};

	//temp debug stack checks
	if (tasksRunning >= MAX_TASK_STACKS) {
		return (NULL);
	}
	//end temp debug stack checks

	//create unique task priority
	uniquePriority = ((taskPriority << 16) | (uniqueTaskID++));

	//cheesy stack handler for now...
	global_spawnedTask = (TASK *) taskStacks[tasksRunning];

	//set max stack addr
	global_spawnedTask->stackAddr = (long *) ((char *) global_spawnedTask + sizeof(TASK));

	//write magic number for stack overflow check
	*(global_spawnedTask->stackAddr) = TASK_CHECKSUM;

	//set stackpointer to TOP of stack
	global_spawnedTask->stackTop = (long) ((char *)global_spawnedTask->stackAddr + (stackSize - 1) * 4);

	global_spawnedTask->sp = (global_spawnedTask->stackTop - STACK_RESERVE);
	global_spawnedTask->lr = (long) taskFunction;

	//init rest of task struct
	global_spawnedTask->destruct 	= taskDestructor;   //task destructor function
	global_spawnedTask->waitState	= 1;  							//task is now active
	global_spawnedTask->taskID		= taskID;						//set taskID
	global_spawnedTask->priority	= uniquePriority;		//set unique pri
	global_spawnedTask->message		= NULL;							//no messages

	switch(taskType)
	{
		case CHILD_TASK:
			global_spawnedTask->parent = global_activeTask;
			break;

		case SIBLING_TASK:
			global_spawnedTask->parent = global_activeTask->parent;
			break;

		default:
			global_spawnedTask->parent = NULL;
			break;
	}

	//link task into list
	if (global_activeTask == NULL) {
		global_spawnedTask->next = global_spawnedTask;
		global_activeTask = global_spawnedTask;
	}

	//sort the task by priority into the task list
	else {
		taskSearch = global_activeTask;

		//find the task with the highest run priority
		while(taskSearch->priority < taskSearch->next->priority)
			taskSearch = taskSearch->next;

		//taskSearch is now highest priority
		for(taskCount=0; (taskCount<tasksRunning) && (taskSearch->next->priority < uniquePriority); taskCount++)
			taskSearch = taskSearch->next;

		global_spawnedTask->next = taskSearch->next;
		taskSearch->next = global_spawnedTask;
	}

	//inc num tasks running
	tasksRunning++;

	return (global_spawnedTask);
}

/*
 *	TASK *getNextTask(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Gets next task unless activeTask is empty
 *
 *  RETURNS:			Pointer to next task
 */
TASK *getNextTask(void)
{
	//if no active task, then no tasks are running
	if (global_activeTask == NULL)
		return (NULL);

	while (1) {

		//get next task
		global_activeTask = global_activeTask->next;

		//if suspended skip it
		if (global_activeTask->waitState != -1) {

			if (--global_activeTask->waitState == 0) {
				return (global_activeTask);
			}
		}
	}
}

/*
 *	TASK *getTaskWithID(TASK_ID taskID)
 *
 *  PARAMETERS:		taskID:	ID of task
 *
 *  DESCRIPTION:	Gets task with taskID
 *
 *  RETURNS:			Pointer to task
 */
TASK *getTaskWithID(TASK_ID taskID)
{
	TASK *start;

	//get next task
	start	= global_activeTask->next;

	//search all tasks
	while (start != global_activeTask) {

		if (start->taskID == taskID)
			return (start);

		start = start->next;
	}

	//couldn't find task
	return (NULL);
}

/*
 *	void suspendTask(TASK *taskPtr)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *
 *  DESCRIPTION:	Suspends task
 *
 *  RETURNS:			Nothing
 */
void suspendTask(TASK *taskPtr)
{
	//if suspending active task just sleep
	if (taskPtr == global_activeTask) {
		sleepme(-1);
	}

	//suspending other task so set waitState to -1
	else {
		taskPtr->waitState = -1;
	}
}

/*
 *	void resumeTask(TASK *taskPtr)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *
 *  DESCRIPTION:	Resumes task
 *
 *  RETURNS:			Nothing
 */
void resumeTask(TASK *taskPtr)
{
	taskPtr->waitState = 1;
}

/*
 *	void taskDie(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Kills active task
 *
 *  RETURNS:			Nothing
 */
void taskDie(void)
{
	killTask(global_activeTask);
}

/*
 *	void killTaskWithID(TASK_ID taskID)
 *
 *  PARAMETERS:		taskID:	ID of task
 *
 *  DESCRIPTION:	Kills task(s) with taskID
 *
 *  RETURNS:			Nothing
 */
void killTaskWithID(TASK_ID taskID)
{
	TASK *taskPtr;

	while ((taskPtr = getTaskWithID(taskID))) {
		killTask(taskPtr);
	}
}

/*
 *	void killTask(TASK *taskPtr)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *
 *  DESCRIPTION:	Kills task
 *
 *  RETURNS:			Nothing
 */
void killTask(TASK *taskPtr)
{
	TASK *activeTask;

	//save current task
	activeTask = global_activeTask;

	//delete task if it exists
	if (deleteActiveTask(taskPtr)) {

		//kill all children (and their children)
		killTaskChildren(taskPtr, TASK_ID_MASK_ALL, TASK_ID_MASK_ALL);

		//return if we didn't delete activeTask
		if (global_activeTask == activeTask)
			return;

		//if last tasks was deleted, exit tasking system
		if (global_activeTask == NULL) 	{
			returnFromTaskingSystem();

		}

		else {
			//need to set orig stack due to activeTask being deleted
			setSystemStack();

			//call next task on list.
			restoreTaskRegisters(global_activeTask);
		}
	}
}

/*
 *	static BOOL deleteActiveTask(TASK *taskPtr)
 *
 *  PARAMETERS:		task:	Pointer to task
 *
 *  DESCRIPTION:	Deletes 'task' from active task list (leaves task->next intact so its
 *                link is still valid)
 *                Updates 'task_active' if it is the task we're deleting.
 *
 *  RETURNS:			TRUE upon success, FALSE otherwise
 */
static BOOL deleteActiveTask(TASK *taskPtr)
{
	TASK *next;
	TASK *prev;
	long i;
	long localTasksRunning = tasksRunning;

	prev = global_activeTask;
	next = global_activeTask->next;

	for (i=0; i<localTasksRunning; i++) {

		//scan through all tasks looking for parent
		if (next == taskPtr) {

			//call destructor function if present
			if (taskPtr->destruct) {
				taskPtr->destruct();
			}

			//dec num tasks running
			tasksRunning--;

			//remove task from list
			prev->next = taskPtr->next;

			//if parent == self it's only active task.
			if (prev == taskPtr) {
				global_activeTask = NULL;
				return (TRUE);
			}

			if (taskPtr == global_activeTask) {
				global_activeTask = getNextTask();
			}

			return (TRUE);
		}

		prev = next;
		next = next->next;
	}

	//could not delete task
	return (FALSE);
}

/*
 *	static void killTaskChildren(TASK *taskPtr, TASK_ID taskID, TASK_MASK taskMask)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *                taskID:		Task ID
 *                taskMask:	Mask
 *
 *  DESCRIPTION:	Kills all children belonging to taskPtr (doesn't kill taskPtr)
 *
 *  RETURNS:			Nothing
 */
static void killTaskChildren(TASK *taskPtr, TASK_ID taskID, TASK_MASK taskMask)
{
	TASK *next;
	short	i;
	TASK_MASK match;
	long localTasksRunning = tasksRunning;

	match	= (taskID & taskMask);

	//get task's child
	next = taskPtr->next;

	for (i=0; i<localTasksRunning; i++) {

		//is this a child of task
		if (next->parent == taskPtr) {

			//kill all children belonging to this task
			killTaskChildren(next, taskID, taskMask);

			//delete task if id's match mask
			if ((next->taskID & taskMask) == match) {
				deleteActiveTask(next);
			}
		}

		next = next->next;
	}

}

/*
 *	void passTaskVar_1(TASK *taskPtr, long var0)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *								var0:			Var to pass to task
 *
 *  DESCRIPTION:	Sets task arguments
 *
 *  RETURNS:			Nothing
 */
void passTaskVar_1(TASK *taskPtr, long var0)
{
	//passing 1 argument
	taskPtr->r0 = var0;
}

/*
 *	void passTaskVar_2(TASK *taskPtr, long var0, long var1)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *								var0:			Var to pass to task
 *								var1:			Var to pass to task
 *
 *  DESCRIPTION:	Sets task arguments
 *
 *  RETURNS:			Nothing
 */
void passTaskVar_2(TASK *taskPtr, long var0, long var1)
{
	//passing 2 arguments
	taskPtr->r0 = var0;
	taskPtr->r1 = var1;
}

/*
 *	void passTaskVar_3(TASK *taskPtr, long var0, long var1, long var2)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *								var0:			Var to pass to task
 *								var1:			Var to pass to task
 *								var2:			Var to pass to task
 *
 *  DESCRIPTION:	Sets task arguments
 *
 *  RETURNS:			Nothing
 */
void passTaskVar_3(TASK *taskPtr, long var0, long var1, long var2)
{
	//passing 3 arguments
	taskPtr->r0 = var0;
	taskPtr->r1 = var1;
	taskPtr->r2 = var2;
}

/*
 *	void passTaskVar_4(TASK *taskPtr, long var0, long var1, long var2, long var3)
 *
 *  PARAMETERS:		taskPtr:	Pointer to task
 *								var0:			Var to pass to task
 *								var1:			Var to pass to task
 *								var2:			Var to pass to task
 *								var3:			Var to pass to task
 *
 *  DESCRIPTION:	Sets task arguments
 *
 *  RETURNS:			Nothing
 */
void passTaskVar_4(TASK *taskPtr, long var0, long var1, long var2, long var3)
{
	//passing 4 arguments
	taskPtr->r0 = var0;
	taskPtr->r1 = var1;
	taskPtr->r2 = var2;
	taskPtr->r3 = var3;
}


