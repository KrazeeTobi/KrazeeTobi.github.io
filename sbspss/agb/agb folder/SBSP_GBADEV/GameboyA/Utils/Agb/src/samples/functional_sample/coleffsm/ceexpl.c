//======================================================
//    ceexpl.c
//    Explanation of color special effects sample
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agb.h>
#include "../share.h"

const char* ce_title_str = "COLOR SPECIAL EFFECT";

const char* ce_expl_str0 =
//   .    .    .    .    .    .Up to here (30 characters)
"Color special effect sample\n"
"Test effect of brightness\n"
"change on semitransprnt OBJ\n"
"and test color effect OFF\n"
"\n"
"+ key         Yoshi0 move\n"
"B & + key     Yoshi1 move\n"
"A & + key     Yoshi2 move\n"
"LR button     EVA EVB change\n"
"B & LR button EVY change\n"
;

const char** ce_expl_str_array[] =
{
    NULL,	//  Always start with NULL
    &ce_expl_str0,
    NULL,	//  Always end with NULL
};
