/********************************************************************/
/*          sub.c                                                   */
/*            General Purpose Subroutine Group                      */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "overlay.h"


/*==================================================================*/
/*                      Interrupt Routine                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Interrupt Dummy Routine                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                       Subroutine                                 */
/*==================================================================*/

#if 0
/*------------------------------------------------------------------*/
/*               V Blank Interrupt Wait Routine                     */
/*------------------------------------------------------------------*/

void V_Wait(void)
{
    IntrCheck &= V_BLANK_INTR_FLAG ^ 0xffff;        // Clear V Blank interrupt check
    while (1) {
        Halt();                                     // Pause CPU
        if (IntrCheck & V_BLANK_INTR_FLAG)          // Complete V Blank interrupt process
            break;
    }
}
#endif

/*------------------------------------------------------------------*/
/*                      Read in Key                                 */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // trigger input
    Cont = ReadData;                                //   beta input
}

/*------------------------------------------------------------------*/
/*                      OBJ Cursor Move Routine                     */
/*------------------------------------------------------------------*/

void ObjCursolMove(OamData *OamDatap, LinkData *LinkDatap, u8 *Cursolp)
{
    s16    Tmp=0;

    switch (Trg) {
        case U_KEY: if ((Tmp = LinkDatap[*Cursolp].U) != -1)  *Cursolp = Tmp;
                    break;
        case D_KEY: if ((Tmp = LinkDatap[*Cursolp].D) != -1)  *Cursolp = Tmp;
                    break;
        case L_KEY: if ((Tmp = LinkDatap[*Cursolp].L) != -1)  *Cursolp = Tmp;
                    break;
        case R_KEY: if ((Tmp = LinkDatap[*Cursolp].R) != -1)  *Cursolp = Tmp;
                    break;
    }
    OamDatap[0].HPos = LinkDatap[*Cursolp].X;
    OamDatap[0].VPos = LinkDatap[*Cursolp].Y;
}

