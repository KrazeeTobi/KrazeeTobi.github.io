//======================================================
//    alexpl.c
//    Explanation for alpha blend function
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#include <agb.h>
#include "../share.h"

const char* ap_title_str = "ALPHA BLEND FUNCTIONS";
const char* ap_expl_str0 =
//   .    .    .    .    .    .Up to here (30 characters)
"Alpha blend sample\n"
"Test for changing blend \n"
"ratio or blend mode and for\n"
"making OBJ semi-transparent\n"
"\n"
"+ key       Yoshi1 move\n"
"A & + key   Yoshi0 move\n"
"L R button  EVA EVB change\n"
"START       Blend mode change\n"
"B & START   OBJ mode change\n"
;
const char** ap_expl_str_array[] =
{
    NULL,	//  Must start with NULL
    &ap_expl_str0,
    NULL,	//  Must end with NULL
};
