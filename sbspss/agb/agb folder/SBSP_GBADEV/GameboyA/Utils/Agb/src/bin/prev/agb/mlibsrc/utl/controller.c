//======================================================
//    controller.c                                         
//    Controller functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include "controller.h"

u16 Cont;
u16 Trg;

//----------------------------------------------------------------------
void ctrInit(void)
{
    Cont = 0;
    Trg = 0;
}
//----------------------------------------------------------------------
void ctrRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);	//  Key pressed
    Cont = ReadData;				        //  Key held down
}
//----------------------------------------------------------------------

//
//
