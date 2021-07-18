//======================================================
//    menuitem.h                                           
//    Pointer to character array and function to display menu
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#ifndef	__MENUITEM_H__
#define	__MENUITEM_H__

#include <agb.h>
#include "share.h"

typedef void (*SampleCallBack)(void);

typedef struct
{
    const char**	title_str;
    const char***	explanation_str_array;
    SampleCallBack	call_back;
} MenuItem;

extern const MenuItem mitem[];

#endif	//  __MENUITEM_H__

//
//
