/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _TASK_H
#define _TASK_H

/*-------------------------- defines ------------------------------ */
#define NORMAL_STACK_SIZE	(2048)
#define NULL_TASK (void *) NULL

#define TASK_CHECKSUM 		(0x3a803140)

#define	TASK_ID_MASK_ALL	(0x0000)
#define	TASK_ID_MASK_ID		(0xffff)
/*-------------------------- structs ------------------------------ */
typedef unsigned short TASK_ID;
typedef unsigned short TASK_MASK;

typedef enum TASK_TYPE
{
	CHILD_TASK = 0,
	SIBLING_TASK,
	GLOBAL_TASK

} TASK_TYPE;

typedef struct _task
{
	//system registers
	long r0;										//0
	long r1;            				//4
	long r2;            				//8
	long r3;            				//12
	long r4;            				//16
	long r5;            				//20
	long r6;            				//24
	long r7;            				//28
	long r8;            				//32
	long r9;            				//36
	long r10;           				//40
	long fp;            				//44 	r11
	long ip;            				//48 	r12
	long sp;            				//52 	r13
	long lr;            				//56 	r14
	long pc;										//60	Prob delete
	long cpsr;          				//64

	long waitState;							//68
	long *stackAddr;						//72 	Address of stack memory (stack must not exceed this!)
	long stackTop;							//76 	Top of task stack

	long *message;							//80  Task will WAIT until this is 0
	u_long	priority;   				//84
	struct 	_task *parent; 			//88  ptr to parent (NULL = NONE)
	struct 	_task *next;	 			//92 	ptr to next free or active TASK
	void 		(*destruct)(void);	//96
	TASK_ID	taskID;							//100 Task ID
	u_short	var;								//102 Task Misc var

} TASK;

/*-------------------------- external functs -----------------------*/
extern void sleepme(long len);

extern void initTaskingSystem(void *taskFunction, u_short stackSize, long taskPriority);
extern TASK *spawnTask(void(*taskFunction)(void), void(*taskDestructor)(void), u_short stackSize, long taskPriority, TASK_ID taskID, TASK_TYPE taskType);

extern TASK *getTaskWithID(TASK_ID taskID);
extern void suspendTask(TASK *taskPtr);
extern void resumeTask(TASK *taskPtr);

extern void taskDie(void);
extern void killTaskWithID(TASK_ID taskID);
extern void killTask(TASK *taskPtr);

extern void passTaskVar_1(TASK *taskPtr, long var0);
extern void passTaskVar_2(TASK *taskPtr, long var0, long var1);
extern void passTaskVar_3(TASK *taskPtr, long var0, long var1, long var2);
extern void passTaskVar_4(TASK *taskPtr, long var0, long var1, long var2, long var3);

/*-------------------------- external vars -------------------------*/
extern TASK	*global_activeTask;
extern TASK	*global_spawnedTask;

#endif // _TASK_H
