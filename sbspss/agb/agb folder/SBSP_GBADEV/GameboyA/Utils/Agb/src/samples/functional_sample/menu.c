//======================================================
//    menu.c                                           
//    Process menu
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#include <agb.h>
#include "menu.h"
#include "menuitem.h"
#include "share.h"

#define	_menu_y( cursor_pos ) ((cursor_pos) * 2 + 3)
#define	MENU_SELECTED_COLOR (4)

//---------------------- Local variables  --------------------------

int menu_cursor_pos;		//  Current cursor position
int menu_prev_cursor_pos;	//  Cursor position in the previous frame
int menu_old_cursor_pos;	//  Cursor position in the previous demo
int menu_page;			//  Menu page
int menu_prev_page;		//  Menu page in the previous frame

//-------------------- Declaration of subroutines ------------------------

static int menu_exit(void);
static int menu_init_param(void);
static void menu_v_sync_fnc(void);
static int menu_to_prev_page(void);
static int menu_to_next_page(void);
static int menu_to_prev_item(void);
static int menu_to_next_item(void);
static int menu_control(void);
static int menu_strlen( const char* str );
static void menu_print_expl(void);
static void menu_print_title(void);
static void menu_print(void);

//==============================================================
//                   Initialization routine
//==============================================================
void MenuInit( void )
{
    menu_cursor_pos = 1;	//  Optional
    menu_old_cursor_pos = 1;
}
//==============================================================
//                   Main routine
//==============================================================
int Menu(void)
{
    ClearGraphicRam();
    menu_init_param();

    *(vu16 *)REG_IE |= V_BLANK_INTR_FLAG;

    while(1)
    {
	if( menu_control() ) break;
	menu_print();

	V_Wait();

	menu_prev_page = menu_page;
	menu_prev_cursor_pos = menu_cursor_pos;
    }
    ClearGraphicRam();
    *(vu16 *)REG_IE ^= V_BLANK_INTR_FLAG;	// Reset V Blank interrupt flag
    ((vl DispCnt *)REG_DISPCNT)->Lcdc_Off = 1;	// LCDC OFF
    FontPrintCls();
    return menu_exit();
}

//==============================================================
//                    Interrupt routine
//==============================================================

//--------------------------------------------------------------
//                    V Blank function

//--------------------------------------------------------------
static void menu_v_sync_fnc(void)
{
    FontPrintSync();
}

//==============================================================
//                      Subroutines
//==============================================================

//--------------------------------------------------------------
//                   Menu exit function
//--------------------------------------------------------------
static int menu_exit(void)
{
    menu_old_cursor_pos = menu_cursor_pos;
    return menu_cursor_pos;
}
//--------------------------------------------------------------
//                   Menu initialization function
//--------------------------------------------------------------
static int menu_init_param(void)
{
    menu_page=0;
    menu_prev_page = -1;
    menu_prev_cursor_pos = -1;
    menu_cursor_pos = menu_old_cursor_pos;

	//  Set V Blank function 

    SetVBlankFunc( menu_v_sync_fnc );

	// Initialize font

    FontPrintInit(0,0,30,20,OBJ_MODE0_VRAM+0x1000,15);
    FontPalletLoad(15);

	// Set display 
	// 1D mapping

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON
			 | DISP_OBJ_CHAR_1D_MAP;
}
//--------------------------------------------------------------
//                 Return to previous page
//--------------------------------------------------------------
static int menu_to_prev_page(void)
{
    char*** expl_str_array;

    if( menu_page == 0 ) return -1;

    expl_str_array = (char***)mitem[menu_cursor_pos].explanation_str_array;

    if( menu_page != 1 )
    {
	if( NULL == expl_str_array ) return -1;
	if( NULL == expl_str_array[menu_page-1] ) return -1;
    }
    return --menu_page;
}
//--------------------------------------------------------------
//                  Go to next page
//--------------------------------------------------------------
static int menu_to_next_page(void)
{
    char*** expl_str_array;

    expl_str_array = (char***)mitem[menu_cursor_pos].explanation_str_array;

    if( NULL == expl_str_array ) return -1;
    if( NULL == expl_str_array[menu_page+1] ) return -1;
    return ++menu_page;
}
//--------------------------------------------------------------
//                 Select previous menu
//--------------------------------------------------------------
static int menu_to_prev_item(void)
{
    char*** expl_str_array;

    if( NULL == mitem[menu_cursor_pos-1].title_str ) return -1;
    if( NULL == *mitem[menu_cursor_pos-1].title_str ) return -1;

    expl_str_array = (char***)mitem[--menu_cursor_pos].explanation_str_array;

    if( NULL == expl_str_array ) menu_page = 0;
    else menu_page = (menu_page == 0) ? 0:
		     ( NULL == expl_str_array[1] ) ? 0 : 1;

    return menu_cursor_pos;
}
//--------------------------------------------------------------
//                 Select next menu
//--------------------------------------------------------------
static int menu_to_next_item(void)
{
    char*** expl_str_array;

    if( NULL == mitem[menu_cursor_pos+1].title_str ) return -1;
    if( NULL == *mitem[menu_cursor_pos+1].title_str ) return -1;

    expl_str_array = (char***)mitem[++menu_cursor_pos].explanation_str_array;

    if( NULL == expl_str_array ) menu_page = 0;
    else menu_page = (menu_page == 0) ? 0:
		     ( NULL == expl_str_array[1] ) ? 0 : 1;

    return menu_cursor_pos;
}
//--------------------------------------------------------------
//             If controller proces fails, return -1

//--------------------------------------------------------------
static int menu_control(void)
{
    KeyRead();

	//  Demo start

    if( Trg & START_BUTTON )
    {
	return 1;
    }

	//  Move to the left page

    if( Trg & L_BUTTON )
    {
	menu_to_prev_page();
    }

	//  Move to the right page

    if( Trg & R_BUTTON )
    {
	menu_to_next_page();
    }

	//  Move up one menu

    if( Trg & U_KEY )
    {
	menu_to_prev_item();
    }

	//  Move down one menu

    if( Trg & D_KEY )
    {
	menu_to_next_item();
    }

	//  Move down one menu

    if( Trg & SELECT_BUTTON )
    {
	if( -1 == menu_to_next_item() )
	{
	    while( -1 != menu_to_prev_item() );
	}
    }

	//  Start sample after reading explanation in order


    if( Trg & A_BUTTON )
    {
	if( -1 == menu_to_next_page() ) return 1;
    }

	//  Go back to menu

    if( Trg & B_BUTTON )
    {
	menu_page = 0;
    }

    return 0;
}
//--------------------------------------------------------------
//                   Calculate length of character string 
//--------------------------------------------------------------
static int menu_strlen( const char* str )
{
    int i;
    i=0;
    while( str[i++] );
    return i;
}
//--------------------------------------------------------------
//                   Display explanation of sample 
//--------------------------------------------------------------
static void menu_print_expl(void)
{
    MenuItem* mitem_ptr;
    if( (menu_page != menu_prev_page)
     || (menu_cursor_pos != menu_prev_cursor_pos) )
    {
	mitem_ptr = (MenuItem*)&mitem[menu_cursor_pos];
	FontPrintCls();
		    //  Display title of sample
	FontPrintC( (30 - menu_strlen( (char*)*mitem_ptr->title_str ) )/2,
		   4, MENU_SELECTED_COLOR ,
		   *mitem_ptr->title_str );
	if( menu_page == 1 )
	{
	    FontPrint( 0,1,"< RETURN TO MENU" );
	}
	else
	{
	    FontPrint( 0,1,"< PREV PAGE" );
	}
	if( -1 != menu_to_next_page() )
	{
	    menu_to_prev_page();
	    FontPrint( 19,1,"NEXT PAGE >" );
	}
	FontPrint( 0,7,
		*mitem_ptr->explanation_str_array[menu_page] );
    }
}
//--------------------------------------------------------------
//               Display main title

//--------------------------------------------------------------
static void menu_print_title(void)
{
    int i;

    if( menu_prev_page )
    {
	FontPrintCls();

	FontPrintC( 4,2,6,"AGB FUNCTIONAL SAMPLE!" );

	    //  Display title of sample
    }
    if( menu_cursor_pos != menu_prev_cursor_pos || menu_prev_page != 0 )
    {
	if( menu_prev_cursor_pos > 0 )
	{
	    FontPrint( 3,_menu_y(menu_prev_cursor_pos),"   " );
	}
	FontPrintC( 3,_menu_y(menu_cursor_pos),MENU_SELECTED_COLOR,"-->" );
	for( i=1 ; i<menu_cursor_pos ; ++i )
	{
	    FontPrint( 7,_menu_y(i),
		       *mitem[i].title_str );
	}
	FontPrintC( 7,_menu_y(i) , MENU_SELECTED_COLOR,
		    *mitem[i].title_str );
	for( ++i ; mitem[i].title_str != NULL ; ++i )
	{
	    FontPrint( 7,_menu_y(i),
		       *mitem[i].title_str );
	}
    }
}
//--------------------------------------------------------------
//                        Display menu
//--------------------------------------------------------------
static void menu_print(void)
{
    if( menu_page ) menu_print_expl();
    else menu_print_title();
}

//
//
