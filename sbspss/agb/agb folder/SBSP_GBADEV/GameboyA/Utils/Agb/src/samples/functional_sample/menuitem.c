//======================================================
//    menuitem.c                                           
//    Pointer to character array and function to display menu
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#include <agb.h>
#include "share.h"
#include "menuitem.h"

//--------------------------- External reference  -----------------------
extern const char* ob_title_str;
extern const char** ob_expl_str_array[];
extern void obMain(void);

extern const char* bg_title_str;
extern const char** bg_expl_str_array[];
extern void bgMain(void);

extern const char* bm_title_str;
extern const char** bm_expl_str_array[];
extern void bm_Main(void);

extern const char* sw_title_str;
extern const char** sw_expl_str_array[];
extern void swMain(void);

extern const char* ap_title_str;
extern const char** ap_expl_str_array[];
extern void apMain(void);

extern const char* we_title_str;
extern const char** we_expl_str_array[];
extern void weMain(void);

extern const char* ce_title_str;
extern const char** ce_expl_str_array[];
extern void ceMain(void);

//-- Table to display menu and to call a callback function --

const MenuItem mitem[] =
{
    {NULL,NULL,NULL},

    {
	&ob_title_str,
	ob_expl_str_array,
	obMain,
    },
    {
	&bg_title_str,
	bg_expl_str_array,
	bgMain,
    },
    {
	&bm_title_str,
	bm_expl_str_array,
	bm_Main,
    },
    {
	&sw_title_str,
	sw_expl_str_array,
	swMain,
    },
    {
	&ap_title_str,
	ap_expl_str_array,
	apMain,
    },
    {
	&ce_title_str,
	ce_expl_str_array,
	ceMain,
    },

    {NULL,NULL,NULL},
};

