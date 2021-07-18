//======================================================
//    obmain.c                                           
//    Object sample - main routine
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

//#define CODE32
#include <agb.h>
#include "../share.h"

//------------------------- Data -----------------------------

extern const u16 hey2_Palette[256];
extern const u8 hey2_Char[8*8*(32/8/1)*(64/8)];

//---------------------- Local variables  --------------------------

s16	ob_pos_x,ob_pos_y;	//  Set screen center as (0,0)
				//  Center coordinate for character
u16	ob_affine;
u16	ob_mosaic;
u16	ob_scale_x , ob_scale_y;
u16	ob_rotate;		// 1 rotation = 256
u16	ob_oam_buffer[16];	//  OAM and scaling/rotation

//-------------------- Subroutines  ------------------------

static int  ob_key_control( void );
static void ob_v_blank_intr(void);
static void ob_create_oam( void );
static void ob_init_oam( void );
static void ob_v_blank_intr(void);
static void ob_init_param(void);

//==============================================================
//                       Main routine
//==============================================================
void obMain(void)
{
    SetVBlankFunc( ob_v_blank_intr );

	//  Send character data

    DmaArrayCopy( 3 , hey2_Palette , OBJ_PLTT , 16 );
    DmaArrayCopy( 3 , hey2_Char , OBJ_MODE0_VRAM , 16 );

	// Set V Blank interrupt flag


    *(vu16 *)REG_IE |= V_BLANK_INTR_FLAG;
    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_OBJ_CHAR_1D_MAP;

    ob_init_param();
    ob_init_oam();

    while(1)
    {
	if( ob_key_control() ) return;
	ob_create_oam();
	V_Wait();
    }
}
//==============================================================
//                    Interrupt routine

//==============================================================

//--------------------------------------------------------------
//                    V Blank function
//--------------------------------------------------------------
static void ob_v_blank_intr(void)
{
	// Set mosaic

    *(vu16 *)REG_MOSAIC = ((u16)ob_mosaic<<12)|((u16)ob_mosaic<<8);

	// DMA transfer of OAM

    DmaCopy(3, ob_oam_buffer, OAM, 32 , 32);
}
//==============================================================
//                      Subroutine
//==============================================================

//--------------------------------------------------------------
//                      Initialize variables
//--------------------------------------------------------------
static void ob_init_param(void)
{
    ob_affine = 0;
    ob_mosaic = 0;
    ob_scale_x = 0x100;
    ob_scale_y = 0x100;
    ob_rotate = 0;
    ob_pos_x = 0;
    ob_pos_y = 0;
}
//--------------------------------------------------------------
//                    Initialize OAM
//--------------------------------------------------------------
static void ob_init_oam( void )
{
    int i;

    for( i=1 ; i<16 ; ++i)
    {
	ob_oam_buffer[i]=0;
    }
    ob_create_oam();
}
//--------------------------------------------------------------
//                 Process controller
//--------------------------------------------------------------
static int ob_key_control( void )
{
    KeyRead();	// Key operation
    if (Trg & SELECT_BUTTON)
    {
	*(vu16 *)REG_IE ^= V_BLANK_INTR_FLAG;	// Reset V Blank interrupt flag
	((vl DispCnt *)REG_DISPCNT)->Lcdc_Off = 1;	// LCDC OFF
	*(vu16 *)REG_MOSAIC = 0;
	DmaClear(3, 0, REG_BGOFS, 2*2*4, 32);	// BG scroll clear
	return 1;
    }
    if( Trg & A_BUTTON )
    {
	ob_affine ^= 1;
    }
    if( Cont & B_BUTTON )
    {

	    //  Scale with + button

	if (Cont & U_KEY)
	{
	    ob_scale_y += 0x10;
	    if( ob_scale_y > 0x400 ) ob_scale_y = 0x400;
	}
	if (Cont & D_KEY)
	{
	    ob_scale_y -= 0x08;
	    if( ob_scale_y < 0x40 ) ob_scale_y = 0x40;
	}
	if (Cont & L_KEY)
	{
	    ob_scale_x -= 0x08;
	    if( ob_scale_x < 0x40 ) ob_scale_x = 0x40;
	}
	if (Cont & R_KEY)
	{
	    ob_scale_x += 0x10;
	    if( ob_scale_x > 0x400 ) ob_scale_x = 0x400;
	}

	    // Rotate with LR button

	if ( Cont & R_BUTTON )
	{
	    ob_rotate = (++ob_rotate)&0xff;
	}
	if ( Cont & L_BUTTON )
	{
	    ob_rotate = (ob_rotate+0xff)&0xff;
	}

    }
    else
    {

	    //  Move with + button

	if (Cont & U_KEY)
	{
	    ob_pos_y -= 2;
	    if( ob_pos_y < -80 ) ob_pos_y = -80;
	}
	if (Cont & D_KEY)
	{
	    ob_pos_y += 2;
	    if( ob_pos_y > 80 ) ob_pos_y = 80;
	}
	if (Cont & R_KEY)
	{
	    ob_pos_x += 2;
	    if( ob_pos_x > 120 ) ob_pos_x = 120;
	}
	if (Cont & L_KEY)
	{
	    ob_pos_x -= 2;
	    if( ob_pos_x < -120 ) ob_pos_x = -120;
	}

	    // Mosaic with LR button

	if ( Trg & R_BUTTON )
	{
	    if( ob_mosaic < 15 ) ++ob_mosaic;
	}
	if ( Trg & L_BUTTON )
	{
	    if( ob_mosaic > 0 ) --ob_mosaic;
	}

    }

	//  Initialize with START

    if ( Trg & START_BUTTON )
    {
	ob_init_param();
    }
    return 0;

}
//--------------------------------------------------------------
//                    Create OAM routine
//--------------------------------------------------------------
static void ob_create_oam( void )
{
    s16 pa,pb,pc,pd;
    s16 start_x,start_y;

    ob_oam_buffer[0] = OAM_V_RECTANGLE | OAM_COLOR_256
    				 | OAM_AFFINE_NORMAL | OAM_MOS_ON;
    							//  Vertical size 64, color mode, mosaic
								//  scaling/rotation ON
    ob_oam_buffer[1] = OAM_SIZE_32x64 >> 16;
    							//  Horizontal size 32, scaling/rotation parameter 0
    ob_oam_buffer[2] = 0x0000;	//  Palette 0, priority 0
				//  character name 0

    start_x = ob_pos_x + 120;	//  Adjustment because it takes ob_pos_x,ob_pos_y
    start_y = ob_pos_y + 80;	//   as (0,0)

	//  Object position changes depending
	//  upon whether it uses doule size field

    if( ob_affine )
    {
	ob_oam_buffer[0] |= 0x0200;	//  Affine double size used
	start_x -= 32;
	start_y -= 64;
    }
    else
    {
	start_x -= 32/2;
	start_y -= 64/2;
    }
	//  Set object position

    ob_oam_buffer[0] |= (u16)((s32)(start_y) & 0x00ff);
    ob_oam_buffer[1] |= (u16)((s32)(start_x) & 0x01ff);

	//  Set scaling/rotation

	//  pa = cos(ob_rotate)*(1/ob_scale_x)
    pa = fix_mul(  _Cos(ob_rotate), fix_inverse(ob_scale_x) );
	//  pb = sin(ob_rotate)*(1/ob_scale_x)
    pb = fix_mul(  _Sin(ob_rotate), fix_inverse(ob_scale_x) );
	//  pc =-sin(ob_rotate)*(1/ob_scale_y)
    pc = fix_mul( -_Sin(ob_rotate), fix_inverse(ob_scale_y) );
	//  pd = cos(ob_rotate)*(1/ob_scale_y)
    pd = fix_mul(  _Cos(ob_rotate), fix_inverse(ob_scale_y) );

    ob_oam_buffer[ 3] = *(u16*)(&pa);
    ob_oam_buffer[ 7] = *(u16*)(&pb);
    ob_oam_buffer[11] = *(u16*)(&pc);
    ob_oam_buffer[15] = *(u16*)(&pd);
}
//-------------------------------------------------------------
