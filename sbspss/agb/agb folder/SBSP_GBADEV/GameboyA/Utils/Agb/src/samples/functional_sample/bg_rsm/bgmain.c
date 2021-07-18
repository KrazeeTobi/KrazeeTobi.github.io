//======================================================
//    bgmain.c                                           
//    BG sample and main routine
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

//#define CODE32
#include <agb.h>
#include "../share.h"

//------------------------- Data  -----------------------------

extern u16 cl0_Palette[256];
extern u8 cl0_Character[8*8*169];
extern u8 cl0_Map[16*16];
extern u16 bg_map_Palette[16];
extern u8 bg_map_Char[8*8*(32/8/2)*(16/8)];
extern u16 map_data_front[32*32];
extern u16 map_data_back[32*32];
extern const u16 ball_Palette[16];
extern const u8 ball_Char[8*8*(16/8/2)*(64/8)];

//---------------------- Local variables  --------------------------

vu32	bg_oam_buffer[4][2];

vu16	bg_ball_anim_count;
vu16	bg_ball_anim_count_change_mode;

//  bg param
s16	bg_pos_x,bg_pos_y;	//  Assume center of screen is (0,0)
				//  Center cordinate for character
vu16	bg_screen_back_x;

u16	bg_mosaic;
u16	bg_scale_x , bg_scale_y;
u16	bg_rotate;		// 1 rotate = 256

s16	bg_pa,bg_pb,bg_pc,bg_pd;	//  Rotation/scaling
s32	bg_start_x,bg_start_y;		//  Reference starting point



//-------------------- Subroutine declarations  ------------------------

static int  bg_key_control( void );
static void bg_v_blank_intr(void);
static void bg_create_data( void );
static void bg_init_oam( void );
static void bg_v_blank_intr(void);
static void bg_increment_anim_count(void);
static void bg_init_param(void);
static void bg_exit_clear_register(void);

//==============================================================
//                       Main routine
//==============================================================
void bgMain(void)
{
    SetVBlankFunc( bg_v_blank_intr );

	//  Transfer character data

    DmaArrayCopy(3, bg_map_Char , BG_VRAM+0x8000, 16);
    DmaArrayCopy(3, cl0_Character ,   BG_VRAM+0xc000, 16);
    DmaArrayCopy(3, ball_Char,    OBJ_MODE0_VRAM, 16);

	//  Transfer palette data

    DmaArrayCopy(3, cl0_Palette, BG_PLTT,        16);
    DmaArrayCopy(3, bg_map_Palette, BG_PLTT+128*sizeof(u16), 16);
    DmaArrayCopy(3, ball_Palette, OBJ_PLTT,       16);

	//  Transfer BG data

    DmaArrayCopy(3, map_data_front , BG_VRAM,        16);
    DmaArrayCopy(3, map_data_back ,  BG_VRAM+0x2000, 16);
    DmaArrayCopy(3, cl0_Map ,       BG_VRAM+0x4000, 16);

	//  Set each BG

    *(vu16 *)REG_BG0CNT =
		BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1
		| 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT
		| BG_MOS_ON;

    *(vu16 *)REG_BG1CNT =
		BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_2
		| 4 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT
		| BG_MOS_ON;

    *(vu16 *)REG_BG2CNT =
		BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
		| 8 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT
		| BG_MOS_ON | BG_LOOP_ON ;
    *(vu16 *)REG_DISPCNT = DISP_MODE_1 | DISP_OBJ_CHAR_1D_MAP
			 | DISP_OBJ_ON | DISP_BG_ALL_ON;

	// Set V Blank interrupt flag

    *(vu16 *)REG_IE |= V_BLANK_INTR_FLAG;

	//  Semi-transparent setting for cloud

    *(vu16 *)REG_BLDCNT    = 0x3b44;
    *(vu16 *)REG_BLDALPHA  = 0x080c;


    bg_screen_back_x = 0;

    bg_init_param();
    bg_init_oam();
    while(1)
    {
	if( bg_key_control() ) return;
	bg_create_data();
	bg_increment_anim_count();
	V_Wait();
    }
}
//==============================================================
//                    Interrupt routine
//==============================================================

//--------------------------------------------------------------
//                    V Blank function
//--------------------------------------------------------------
static void bg_v_blank_intr(void)
{
	// Set mosaic

    *(vu16 *)REG_MOSAIC = ((u16)bg_mosaic<<4)|((u16)bg_mosaic);

	// DMA Transfer of OAM

    DmaCopy(3, bg_oam_buffer[bg_ball_anim_count>>3], OAM, 8 , 32);

    *(vu16 *)REG_BG0HOFS = bg_screen_back_x >> 3;
    *(vu16 *)REG_BG0VOFS = 0;
    *(vu16 *)REG_BG1HOFS = bg_screen_back_x >> 2;
    *(vu16 *)REG_BG1VOFS = 0;

    *(vs16 *)REG_BG2PA = (s16)bg_pa;
    *(vs16 *)REG_BG2PB = (s16)bg_pb;
    *(vs16 *)REG_BG2PC = (s16)bg_pc;
    *(vs16 *)REG_BG2PD = (s16)bg_pd;

    *(vu16 *)REG_BG2X_L = (bg_start_x & 0xffff);
    *(vu16 *)REG_BG2X_H = (u16)(u32)((bg_start_x & 0x0fff0000)>>16);
    *(vu16 *)REG_BG2Y_L = (bg_start_y & 0xffff);
    *(vu16 *)REG_BG2Y_H = (u16)(u32)((bg_start_y & 0x0fff0000)>>16);

}
//==============================================================
//                      Subroutines
//==============================================================

//--------------------------------------------------------------
//                      Initialize variables
//--------------------------------------------------------------
static void bg_init_param(void)
{

    bg_start_x = 0;
    bg_start_y = 0;
    bg_pa = 0x100;
    bg_pb = 0;
    bg_pc = 0;
    bg_pd = 0x100;

    bg_mosaic = 0;
    bg_scale_x = 0x100;
    bg_scale_y = 0x100;
    bg_rotate = 0;
    bg_pos_x = 0;
    bg_pos_y = 0;

    bg_ball_anim_count = 4;
    bg_ball_anim_count_change_mode = 0;
}
//--------------------------------------------------------------
//                    Initialize OAM  
//--------------------------------------------------------------
static void bg_init_oam( void )
{
    int i;

	/* Set 4 patterns of animation  */

    for( i=0 ; i<4 ; ++i)
    {
	bg_oam_buffer[i][0] = 
			OAM_COLOR_16 | OAM_SQUARE | OAM_SIZE_16x16
			| (112) << OAM_H_POS_SHIFT
			| (72) << OAM_V_POS_SHIFT;
	bg_oam_buffer[i][1] = i*4 | 0x0400;
    }
}
//--------------------------------------------------------------
//                 Controller process
//--------------------------------------------------------------
static int bg_key_control( void )
{
    KeyRead();	// Key operation
 
 	//  Return to the menu
 

 
    if (Trg & SELECT_BUTTON)
    {
	*(vu16 *)REG_IE ^= V_BLANK_INTR_FLAG;	// Reset V Blank interrupt flag
	((vl DispCnt *)REG_DISPCNT)->Lcdc_Off = 1;	// LCDC OFF
	bg_exit_clear_register();
	ClearGraphicRam();
	return 1;
    }
    if( Cont & B_BUTTON )
    {

	    //  Scale using + Cotrol Pad

	if (Cont & U_KEY)
	{
	    bg_scale_y += 0x10;
	    if( bg_scale_y > 0x400 ) bg_scale_y = 0x400;
	}
	if (Cont & D_KEY)
	{
	    bg_scale_y -= 0x08;
	    if( bg_scale_y < 0x40 ) bg_scale_y = 0x40;
	}
	if (Cont & L_KEY)
	{
	    bg_scale_x -= 0x08;
	    if( bg_scale_x < 0x40 ) bg_scale_x = 0x40;
	}
	if (Cont & R_KEY)
	{
	    bg_scale_x += 0x10;
	    if( bg_scale_x > 0x400 ) bg_scale_x = 0x400;
	}

	    // Rotate using LR button 

	if ( Cont & R_BUTTON )
	{
	    bg_rotate = (++bg_rotate)&0xff;
	}
	if ( Cont & L_BUTTON )
	{
	    bg_rotate = (bg_rotate+0xff)&0xff;
	}

    }
    else
    {

	    //  Move using + Control Pad

	if (Cont & U_KEY)
	{
	    bg_pos_y -= 2;
	    if( bg_pos_y < -64 ) bg_pos_y += 128;
	}
	if (Cont & D_KEY)
	{
	    bg_pos_y += 2;
	    if( bg_pos_y > 64 ) bg_pos_y -= 128;
	}
	if (Cont & R_KEY)
	{
	    bg_pos_x += 2;
	    if( bg_pos_x > 64 ) bg_pos_x -= 128;
	}
	if (Cont & L_KEY)
	{
	    bg_pos_x -= 2;
	    if( bg_pos_x < -64 ) bg_pos_x += 128;
	}

	    // Mosaic using LR button

	if ( Trg & R_BUTTON )
	{
	    if( bg_mosaic < 15 ) ++bg_mosaic;
	}
	if ( Trg & L_BUTTON )
	{
	    if( bg_mosaic > 0 ) --bg_mosaic;
	}

    }

	//  Initialize using START button

    if ( Trg & START_BUTTON )
    {
	bg_init_param();
    }
    return 0;

}
//--------------------------------------------------------------
//                    Create data routine 
//--------------------------------------------------------------
static void bg_create_data( void )
{

	// Set rotation/scaling

	//  pa = cos(bg_rotate)*(1/bg_scale_x)
    bg_pa = fix_mul(  _Cos(bg_rotate), fix_inverse(bg_scale_x) );

	//  pb = sin(bg_rotate)*(1/bg_scale_x)
    bg_pb = fix_mul(  _Sin(bg_rotate), fix_inverse(bg_scale_x) );

	//  pc =-sin(bg_rotate)*(1/bg_scale_y)
    bg_pc = fix_mul( -_Sin(bg_rotate), fix_inverse(bg_scale_y) );

	//  pd = cos(bg_rotate)*(1/bg_scale_y)
    bg_pd = fix_mul(  _Cos(bg_rotate), fix_inverse(bg_scale_y) );

	//  Set starting point for reference

	//  120-bg_pos_x in the first line is for 
	// adjustment because bg_pos_x = 0 is center of screen. 
	//  Lower 2 lines are for matrix calculation.
	//  Assume center of rotation/scaling as center of screen 



    bg_start_x = ((120-bg_pos_x)<<8)
	- ( bg_pa * 120 )
	- ( bg_pb * 80 );
    bg_start_y = ((120-bg_pos_y)<<8)
	- ( bg_pc * 120 )
	- ( bg_pd * 80 );

}
//--------------------------------------------------------------
//                Proceed ball animation
//--------------------------------------------------------------
static void bg_increment_anim_count(void)
{
    bg_screen_back_x = (++bg_screen_back_x)&0x07ff;

    if( bg_ball_anim_count_change_mode )
    {
	if( --bg_ball_anim_count <= 4 )
	    bg_ball_anim_count_change_mode = 0;
    }
    else
    {
	if( ++bg_ball_anim_count >= 28 )
	    bg_ball_anim_count_change_mode = 1;
    }
}
//--------------------------------------------------------------
//                    Register clear routine
//--------------------------------------------------------------
static void bg_exit_clear_register(void)
{
    *(vu16 *)REG_BG0HOFS = 0;
    *(vu16 *)REG_BG0VOFS = 0;
    *(vu16 *)REG_BG1HOFS = 0;
    *(vu16 *)REG_BG1VOFS = 0;

    *(vs16 *)REG_BG2PA = 0x100;
    *(vs16 *)REG_BG2PB = 0;
    *(vs16 *)REG_BG2PC = 0;
    *(vs16 *)REG_BG2PD = 0x100;

    *(vu16 *)REG_BG2X_L = 0;
    *(vu16 *)REG_BG2X_H = 0;
    *(vu16 *)REG_BG2Y_L = 0;
    *(vu16 *)REG_BG2Y_H = 0;

    *(vu16 *)REG_MOSAIC = 0;
    *(vu16 *)REG_BLDCNT    = 0x0000;
    *(vu16 *)REG_BLDALPHA  = 0x000f;
}
//-------------------------------------------------------------
