//======================================================
//    swexpl.c
//    Explanation of window sample
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#include <agb.h>
#include "../share.h"

const char* sw_title_str = "WINDOW FUNCTIONS";
const char* sw_expl_str0 =
//   .    .    .    .    .    .Up to here (30 characters)
"Simple window sample\n"
"Displayed object in window\n"
"changes depending on window\n"
"\n"
"+ key      Move\n"
"A & + key  OBJ window move\n"
"START      Yoshi priority\n"
"             change"
;
const char** sw_expl_str_array[] =
{
    NULL,	//  Always start with NULL
    &sw_expl_str0,
    NULL,	//  Always end with NULL
};
