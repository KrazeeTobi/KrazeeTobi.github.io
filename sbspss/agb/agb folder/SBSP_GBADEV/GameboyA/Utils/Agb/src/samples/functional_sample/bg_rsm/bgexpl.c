//======================================================
//    obexpl.c                                           
//    Explanation of object previewer
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#include "../share.h"

const char* bg_title_str = "BG FUNCTIONS";

const char* bg_expl_str0 =
//   .    .    .    .    .    .Up to here (30 characters)
"BG rotation/scaling and\n"
"masaic sample\n"
"Operate only foremost BG\n"
"Back BG is scrolling\n"
"\n"
"How to operate\n"
"\n"
"+ key         Move\n"
"L button      Zoom out mosaic\n"
"R button      Zoom in mosaic\n"
"B & + key     Scaling\n"
"B & LR button Rotation\n"
;
const char** bg_expl_str_array[] =
{
    NULL,	//  Always start with NULL
    &bg_expl_str0,
    NULL,	//  Always end with NULL
};

