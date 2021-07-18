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
extern long tasksRunning;

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================
void taskTest(void);
void taskFunc_1(long *cycle);
void taskFunc_2(void);
void taskFunc_3(void);
void testCallFunc1(void);
void testCallFunc2(long val);

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================
long printPos;
TASK *task1;
TASK *task2;
TASK *task3;

/*
 *	void AgbMain(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Program entry point
 *
 *  RETURNS:			Nothing
 */
void AgbMain(void)
{
	LCD_OFF;

	clearRamAll();
	initVBlank();

	//init tasking system and set testTask to main task
	initTaskingSystem(taskTest, NORMAL_STACK_SIZE, 0x100);

	//returns here once tasking system is shut down...

	//load font
  FontPrintInit(0,15,30,20,OBJ_MODE0_VRAM,15);
  FontPalletLoad(15);
	FontColor(4);

	//alert system to update font
	global_systemInfoPtr->useDebugFont = 1;

	//set BG mode
	*(vu16 *) REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_OBJ_ON;

	while (1) {
		FontPrintC(0, 0, 2, "Tasking system shut down\n");
		waitForVBlank();
	}

}

/*
 *	void taskTest(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Test task (becomes main task)
 *
 *  RETURNS:			Nothing
 */
void taskTest(void)
{
	//load font
  FontPrintInit(0,15,30,20,OBJ_MODE0_VRAM,15);
  FontPalletLoad(15);
	FontColor(4);

	//alert system to update font
	global_systemInfoPtr->useDebugFont = 1;

	//set BG mode
	*(vu16 *) REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_OBJ_ON;

	//init print pos
	printPos = 0;

	//spawn task1 and pass in var
	task1 = spawnTask((void *) taskFunc_1, NULL_TASK, NORMAL_STACK_SIZE, 0xe, 0x1000, SIBLING_TASK);
	passTaskVar_1(global_spawnedTask, (long) &global_systemInfoPtr->cycleCount);

	while (1) {

		sprintf(global_printBuffer, "Num tasks %ld:%d\n", tasksRunning, global_systemInfoPtr->vBlankCounter);
		FontPrintC(0, printPos++, 2, global_printBuffer);

		//suspend task by ID
		if (global_systemInfoPtr->controlPadTrigger & D_KEY) {
			suspendTask(getTaskWithID(0x1001));
		}

		//resume task by ID
		else if (global_systemInfoPtr->controlPadTrigger & U_KEY) {
			resumeTask(getTaskWithID(0x1001));
		}

		//shut tasking system down
		if (global_systemInfoPtr->controlPadTrigger & L_BUTTON) {

			//kill task1 and any children
			killTask(task1);

			//kill this task
			taskDie();
		}

		//testCallFunc1();
		//testCallFunc2(global_systemInfoPtr->cycleCount);

		sleepme(1);

		global_systemInfoPtr->cycleCount++;
		waitForVBlank();

		printPos = 0;
	}
}

/*
 *	void taskFunc_1(long *cycle)
 *
 *  PARAMETERS:		cycle:	Pointer to main tasks cycle count
 *
 *  DESCRIPTION:	Sample task with paramater
 *
 *  RETURNS:			Nothing
 */
void taskFunc_1(long *cycle)
{
	long temp = 0;

	//spawn 2 tasks (child tasks)
	task2 = spawnTask((void *) taskFunc_2, NULL_TASK, NORMAL_STACK_SIZE, 0x10, 0x1001, CHILD_TASK);
	task3 = spawnTask((void *) taskFunc_3, NULL_TASK, NORMAL_STACK_SIZE, 0x0f, 0x1002, CHILD_TASK);

	while (1) {

		//kill this task (and all children)
		if (global_systemInfoPtr->controlPadTrigger & START_BUTTON) {
			taskDie();
		}

		if (!(global_systemInfoPtr->timer1Counter & 0xf)) {
			temp++;
		}

		sprintf(global_printBuffer, "T1 %d %ld %ld\n", global_systemInfoPtr->timer1Counter, temp, *cycle);
		FontPrintC(0, printPos++, 2, global_printBuffer);

		global_systemInfoPtr->timer1Counter++;

		sleepme(1);
	}
}

/*
 *	void taskFunc_2(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Sample task
 *
 *  RETURNS:			Nothing
 */
void taskFunc_2(void)
{
	while (1) {

		//kill only this task
		if (global_systemInfoPtr->controlPadTrigger & B_BUTTON) {
			taskDie();
		}

		sprintf(global_printBuffer, "T2 Child %d\n", global_systemInfoPtr->timer2Counter);
		FontPrintC(0, printPos++, 2, global_printBuffer);

		global_systemInfoPtr->timer2Counter++;

		sleepme(1);
	}
}

/*
 *	void taskFunc_3(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Sample task
 *
 *  RETURNS:			Nothing
 */
void taskFunc_3(void)
{
	while (1) {

		//kill only this task
		if (global_systemInfoPtr->controlPadTrigger & A_BUTTON) {
			taskDie();
		}

		sprintf(global_printBuffer, "T3 Child %d\n", global_systemInfoPtr->timer3Counter);
		FontPrintC(0, printPos++, 2, global_printBuffer);

		global_systemInfoPtr->timer3Counter++;

		sleepme(1);
	}

}

/*
 *	void testCallFunc1(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Test function
 *
 *  RETURNS:			Nothing
 */
void testCallFunc1(void)
{
	FontPrintC(0, printPos++, 2, "testCallFunc");
}

/*
 *	void testCallFunc2(void)
 *
 *  PARAMETERS:		val:	Value to print
 *
 *  DESCRIPTION:	Test function with param
 *
 *  RETURNS:			Nothing
 */
void testCallFunc2(long val)
{
	sprintf(global_printBuffer, "testCallFunc2 %ld\n", val);
	FontPrintC(0, printPos++, 2, global_printBuffer);
}

/*
 *	void stackFailMessage()
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Debug message alerting stack overrun
 *
 *  RETURNS:			Nothing
 */
void stackFailMessage()
{
	while (1) {
		FontPrintC(0, 0, 2, "STACK FAIL");
		waitForVBlank();
	}

}


