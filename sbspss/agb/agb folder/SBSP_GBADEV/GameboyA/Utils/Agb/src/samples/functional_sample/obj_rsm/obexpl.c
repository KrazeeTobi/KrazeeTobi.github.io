//======================================================
//    obexpl.c                                           
//    Explanation of object previewer
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#include "../share.h"

const char* ob_title_str = "OBJECT FUNCTIONS";

const char* ob_expl_str0 =
//   .    .    .    .    .    .Up to here (30 characters)
"Sample for scaling/rotation\n"
"of sprite and sample mosaic\n"
"Double field can be checked\n"
"\n"
"+ key      Move\n"
"L button   Reduce mosaic\n"
"R button   Enlarge mosaic\n"
"B & +      Scaling\n"
"B & LR     Rotation\n"
"A button   Double field\n"
"           ON/OFF"
//   .    .    .    .    .    .Up to here (30 characters)
;

const char** ob_expl_str_array[] =
{
    NULL,	//  Always start with NULL
    &ob_expl_str0,
    NULL,	//  Always end with NULL
};

