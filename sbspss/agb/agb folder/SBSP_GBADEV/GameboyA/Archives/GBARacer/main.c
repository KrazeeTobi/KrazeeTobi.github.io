/********************************************************************/
/*          main.c                                                  */
/*            Source of simple (Basic Sample)                       */
/*                                                                  */
/*          Copyright (C) 1999,NINTENDO Co.,Ltd.                    */
/********************************************************************/
//#define CODE32
#include "data.h"
#include "render.h"


/*-------------------- Global Variables  ----------------------------*/

    vu16     IntrCheck;                  // Interrupt check

    u16      Cont, Trg;                  // Key input

    u32      IntrMainBuf[0x200];         // Buffer for interrupt main routine

//	*(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

/*---------------------- Subroutine  ------------------------------*/

void KeyRead(void);
void ObjSnakeMove(void);


/*------------------------------------------------------------------*/
/*                      Interrupt Table                             */
/*------------------------------------------------------------------*/
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[15] = {
    VBlankIntr,   RenderHBlank,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,
};


/*==================================================================*/
/*                      Main Routine                                */
/*==================================================================*/
extern void intr_main(void);

/*#ifdef    __GNUC__
int main(void)
#else
*/
void AgbMain(void)
//#endif
{

//	// Clear work RAM:
//    DmaClear(3, 0, WRAM, USR_BUF_SIZE - 4*64, 32);

    DmaClear(3, 0, EX_WRAM,  EX_WRAM_SIZE,          32);   // Clear external CPU work RAM
    DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 0x200, 32);   // Clear internal CPU work RAM

	// Set up interrupts
    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 16);// Interrupt main routine set
    IntrAddrSet(IntrMainBuf);

/*
*/

	BehaveInit();
	RenderInit();

    while (1) 
	{
        KeyRead();                                  // Key control

		BehaveCycle();
		RenderCycle();

        IntrCheck &= V_BLANK_INTR_FLAG ^ 0xffff;    // Clear V Blank interrupt check

        while (1)
		{
            Halt();                                 // Stop CPU
            if (IntrCheck & V_BLANK_INTR_FLAG)      // Complete V Blank interrupt process
                break;
        }
    }
}


/*==================================================================*/
/*                      Interrupt Routine                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V Blank Process                             */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
//    DmaArrayCopy(3, BgBak,  BG_VRAM, 16);           // Set BG screen
//    DmaArrayCopy(3, OamBak, OAM,     32);           // Set OAM

	RenderVBlank();

    IntrCheck = V_BLANK_INTR_FLAG;                  // Set V Blank interrupt check
}

/*------------------------------------------------------------------*/
/*                      Interrupt Dummy Routine                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                      Subroutine                                  */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Key Read In                                 */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // Key pressed
    Cont = ReadData;                                // Key held down
}

