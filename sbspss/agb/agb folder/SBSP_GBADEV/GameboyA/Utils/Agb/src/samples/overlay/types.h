/********************************************************************/
/*          types.h                                                 */
/*            Type Declaration                                      */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _TYPES_H
#define _TYPES_H

#include <Agb.h>


typedef void (*IntrFuncp)(void);

// Link Data Structure
typedef    struct {
    s16 X;
    s16 Y;
    s8  U;
    s8  D;
    s8  L;
    s8  R;
} LinkData;


#endif /* _TYPES_H */
