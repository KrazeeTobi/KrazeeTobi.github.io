/********************************************************************/
/*          sub.h                                                   */
/*            General Purpose Subroutine External Declaration       */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _SUB_H
#define _SUB_H

#include <Agb.h>


/*----------------------- General Purpose Subroutine ------------------------*/

void IntrDummy(void);

void V_Wait(void);
void KeyRead(void);

u8 Title(void);
u8 ObjMove(void);
u8 BgMove(void);


#endif /* _SUB_H */
