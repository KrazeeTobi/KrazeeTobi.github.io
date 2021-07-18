//--------------------------------------------------------------
//    bmexpl.c                                                  
//    Explanation of bitmap mode                                                                    
//                                                              
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.                 
//--------------------------------------------------------------

#include "../share.h"

const char* bm_title_str = "BMPMODE FUNCTIONS";

const char* bm_expl_str0 =
//   .    .    .    .    .    .Up to here (30 characters)
"Bitmap BG display sample\n"
"\n"
"Bitmap BG displayed\n"
"using BG mode 4 5\n"
"\n"
"How to operate\n"
"\n"
"A button     Switch mode\n"
"L button     Zoom in\n"
"R button     Zoom out\n"
"START        Initialize\n"
"               parameters\n"
;

const char** bm_expl_str_array[] =
{
    NULL,	//  Always start with NULL
    &bm_expl_str0,
    NULL,	//  Always end with NULL
};

