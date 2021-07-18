/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "project.h"
#include "util.h"
#include "oam.h"
#include "interrupt.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================
extern void intr_main(void);

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================
SYSTEM_INFO global_systemInfo;
SYSTEM_INFO *global_systemInfoPtr;

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================
#define CLEAR_IRQ(irq) 	interruptStatusFlag &= ~(irq)
#define SET_IRQ(irq) 		*(vu16 *) REG_IF = irq; \
												interruptStatusFlag |= irq


// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================
static void vBlankInterrupt(void);
static void hBlankInterrupt(void);
static void vCountInterrupt(void);

static void timer0Interrupt(void);
static void timer1Interrupt(void);
static void timer2Interrupt(void);
static void timer3Interrupt(void);
static void dummyInterrupt(void);

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================
static u32 intrMainBuf[0x200];
static vu16 interruptStatusFlag;

const IRQFunction IRQFunctions[14] =
{
	vBlankInterrupt,										//V Blank Interrupt
	hBlankInterrupt,                    //H Blank Interrupt
	vCountInterrupt,				            //V Counter Interrupt
	timer0Interrupt, //controllerRead,   //Timer 0 Interrupt
	timer1Interrupt,		        				//Timer 1 Interrupt
	timer2Interrupt,            				//Timer 2 Interrupt
	timer3Interrupt,		               	//Timer 3 Interrupt
	dummyInterrupt,                     //Serial Communication Interrupt
	dummyInterrupt,		                  //DMA0 Interrupt
	dummyInterrupt,                     //DMA1 Interrupt
	dummyInterrupt,		                  //DMA2 Interrupt
	dummyInterrupt,                     //DMA3 Interrupt
	dummyInterrupt,		                  //Key Interrupt
	dummyInterrupt,                     //Cassette Interrupt
};

/*
 *	void waitForVBlank(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Waits for VBlank to occur
 *
 *  RETURNS:			Nothing
 */
void waitForVBlank(void)
{
	CLEAR_IRQ(V_BLANK_INTR_FLAG);

	while(1) {

		//Halt(); //Should I use this?

		if (interruptStatusFlag & V_BLANK_INTR_FLAG)
	    break;
  }
}

/*
 *	void initVBlank(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Inits system AGB IRQ's
 *
 *  RETURNS:			Nothing
 */
void initVBlank(void)
{
	//set global ptr to sys info
	global_systemInfoPtr = &global_systemInfo;

  DmaCopy(3, intr_main, intrMainBuf, sizeof(intrMainBuf), 32);
  *(vu32 *)INTR_VECTOR_BUF = (vu32) intrMainBuf;

  *(vu16 *) REG_IME		= 1; //IME_FLAG;
	*(vu16 *) REG_IE		= V_BLANK_INTR_FLAG;
	*(vu16 *) REG_STAT 	= STAT_V_BLANK_IF_ENABLE;

	CLEAR_IRQ(V_BLANK_INTR_FLAG);

	//init controller
	controllerInit();

	//init OAM buffer
	initOamBuffer();

	//IRQ function ptrs
	global_systemInfoPtr->vBlankFunctionPtr = NULL;
	global_systemInfoPtr->hBlankFunctionPtr = NULL;
	global_systemInfoPtr->vCountFunctionPtr = NULL;

	//IRQ counters
	global_systemInfoPtr->vBlankCounter	= 0;
	global_systemInfoPtr->hBlankCounter	= 0;
	global_systemInfoPtr->vCountCounter	= 0;
	global_systemInfoPtr->timer0Counter = 0;
	global_systemInfoPtr->timer1Counter = 0;
	global_systemInfoPtr->timer2Counter = 0;
	global_systemInfoPtr->timer3Counter = 0;

	//frame rate calcs
	global_systemInfoPtr->vbiCounter		= 0;
	global_systemInfoPtr->cycleCount		= 0;
	global_systemInfoPtr->frameRate	    = 0;

	//flag for NO OAM update
	global_systemInfoPtr->updateOAM			= 0;
	global_systemInfoPtr->forceBlank		= 0;
	global_systemInfoPtr->useDebugFont	= 0;

	//temps
	global_systemInfoPtr->temp					= 0;
	global_systemInfoPtr->temp1					= 0;
	global_systemInfoPtr->temp2					= 0;
	global_systemInfoPtr->temp3					= 0;
}

/*
 *	void setVBlankFunction(IRQFunction function)
 *
 *  PARAMETERS:		function:	IRQ function
 *
 *  DESCRIPTION:	Sets VBlank IRQ function
 *
 *  RETURNS:			Nothing
 */
void setVBlankFunction(IRQFunction function)
{
	global_systemInfoPtr->vBlankFunctionPtr = function;
}

/*
 *	void setHBlankFunction(IRQFunction function)
 *
 *  PARAMETERS:		function:	IRQ function
 *
 *  DESCRIPTION:	Sets HBlank IRQ function
 *
 *  RETURNS:			Nothing
 */
void setHBlankFunction(IRQFunction function)
{
	global_systemInfoPtr->hBlankFunctionPtr = function;
}

/*
 *	void setVCountFunction(IRQFunction function)
 *
 *  PARAMETERS:		function:	IRQ function
 *
 *  DESCRIPTION:	Sets VCount IRQ function
 *
 *  RETURNS:			Nothing
 */
void setVCountFunction(IRQFunction function)
{
	global_systemInfoPtr->vCountFunctionPtr = function;
}

/*
 *	void enableVCountInterrupt(long vCount)
 *
 *  PARAMETERS:		vCount:		Scan line to trigger IRQ
 *
 *  DESCRIPTION:	Enables VCount IRQ at scanline vCount
 *
 *  RETURNS:			Nothing
 */
void enableVCountInterrupt(long vCount)
{
	*(vu16 *) REG_IE		|= V_COUNT_INTR_FLAG;
	*(vu16 *) REG_STAT	|= ((vCount << STAT_VCOUNT_CMP_SHIFT) | STAT_V_COUNT_IF_ENABLE);
}

/*
 *	void disableVCountInterrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Disables the VCount IRQ
 *
 *  RETURNS:			Nothing
 */
void disableVCountInterrupt(void)
{
	*(vu16 *) REG_IE	 &= ~(V_COUNT_INTR_FLAG);
	*(vu16 *) REG_STAT &= ~(STAT_V_COUNT_IF_ENABLE);
}

/*
 *	static void vBlankInterrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Top level VBlank IRQ function
 *
 *  RETURNS:			Nothing
 */
static void vBlankInterrupt(void)
{
	setLCDOff();

	//call secondary vBlank function if set
	if (global_systemInfoPtr->vBlankFunctionPtr != NULL)
		(*global_systemInfoPtr->vBlankFunctionPtr)();

	//DMA OAM if requested
	if (global_systemInfoPtr->updateOAM) {
		DmaArrayCopy(3, global_oamData, OAM, 32);
	}

	//read Controller
	controllerRead();

	//inc frame counter
	global_systemInfoPtr->vBlankCounter++;

	//inc vbiCounter for frameRate;
	global_systemInfoPtr->vbiCounter++;

	//compute frame rate
	if (global_systemInfoPtr->vbiCounter >= 60) {
		global_systemInfoPtr->frameRate		= global_systemInfoPtr->cycleCount;
		global_systemInfoPtr->vbiCounter	= global_systemInfoPtr->cycleCount = 0;
	}

	setLCDOn();

	//Done with interrupt
	SET_IRQ(V_BLANK_INTR_FLAG);
}

/*
 *	static void hBlankInterrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Top level HBlank IRQ function
 *
 *  RETURNS:			Nothing
 */
static void hBlankInterrupt(void)
{
	//call secondary hBlank function if set
	if (global_systemInfoPtr->hBlankFunctionPtr != NULL)
		(*global_systemInfoPtr->hBlankFunctionPtr)();

	//inc counter
	global_systemInfoPtr->hBlankCounter++;

	//done with interrupt
	SET_IRQ(H_BLANK_INTR_FLAG);
}

/*
 *	static void vCountInterrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Top level VCount IRQ function
 *
 *  RETURNS:			Nothing
 */
static void vCountInterrupt(void)
{
	//call secondary VCount function if set
	if (global_systemInfoPtr->vCountFunctionPtr != NULL)
		(*global_systemInfoPtr->vCountFunctionPtr)();

	//inc counter
	global_systemInfoPtr->vCountCounter++;

	//done with interrupt
	SET_IRQ(V_COUNT_INTR_FLAG);
}

/*
 *	static void timer0Interrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Timer 0 IRQ function
 *
 *  RETURNS:			Nothing
 */
static void timer0Interrupt(void)
{
	//inc counter
	global_systemInfoPtr->timer0Counter++;

	//done with interrupt
	SET_IRQ(TIMER0_INTR_FLAG);
}

/*
 *	static void timer1Interrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Timer 1 IRQ function
 *
 *  RETURNS:			Nothing
 */
static void timer1Interrupt(void)
{
	//inc counter
	global_systemInfoPtr->timer1Counter++;

	//done with interrupt
	SET_IRQ(TIMER1_INTR_FLAG);
}

/*
 *	static void timer2Interrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Timer 2 IRQ function
 *
 *  RETURNS:			Nothing
 */
static void timer2Interrupt(void)
{
	//inc counter
	global_systemInfoPtr->timer2Counter++;

	//done with interrupt
	SET_IRQ(TIMER2_INTR_FLAG);
}

/*
 *	static void timer3Interrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Timer 0 IRQ function
 *
 *  RETURNS:			Nothing
 */
static void timer3Interrupt(void)
{
	//inc counter
	global_systemInfoPtr->timer3Counter++;

	//done with interrupt
	SET_IRQ(TIMER3_INTR_FLAG);
}

/*
 *	static void dummyInterrupt(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Dummy IRQ placeholder function
 *
 *  RETURNS:			Nothing
 */
static void dummyInterrupt(void)
{

}

/*
 *	void controllerInit(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Inits controller vars
 *
 *  RETURNS:			Nothing
 */
void controllerInit(void)
{
	global_systemInfoPtr->controlPad = global_systemInfoPtr->controlPadTrigger = 0;
}

/*
 *	void controllerRead(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Reads current controller state
 *
 *  RETURNS:			Nothing
 */
void controllerRead(void)
{
	//grab current controller data
	u16 readData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);

	//update and debounce data
	global_systemInfoPtr->controlPadOld = global_systemInfoPtr->controlPad;
  global_systemInfoPtr->controlPadTrigger = readData & (readData ^ global_systemInfoPtr->controlPad);
  global_systemInfoPtr->controlPad = readData;
}


