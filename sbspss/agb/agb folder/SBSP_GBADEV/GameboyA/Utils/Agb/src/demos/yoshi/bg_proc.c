//======================================================
//    bg_proc.c
//    Sample Yoshi BG Processing
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================


#include <Agb.h>
#include <IsAgbPrint.H>
#include "yos_main.h"
#include "yos_game.h"

// Character Database Address
#define CHAR_BASE0_ADDR  VRAM+0x0000
#define CHAR_BASE1_ADDR  VRAM+0x4000
#define CHAR_BASE2_ADDR  VRAM+0x8000
#define CHAR_BASE3_ADDR  VRAM+0xc000

// Character Base Block Specification
#define CHAR_BASE_0  0
#define CHAR_BASE_1  1
#define CHAR_BASE_2  2
#define CHAR_BASE_3  3

// Screen Base Block Specification
#define SCR_BASE0  0
#define SCR_BASE1  1
#define SCR_BASE2  2
#define SCR_BASE3  3
#define SCR_BASE4  4
#define SCR_BASE5  5
#define SCR_BASE6  6
#define SCR_BASE7  7

// sin cos Table
short tsin[]={
	0x0000,0x0006,0x000c,0x0012,0x0019,0x001f,0x0025,0x002b,
	0x0031,0x0038,0x003e,0x0044,0x004a,0x0050,0x0056,0x005c,
	0x0061,0x0067,0x006d,0x0073,0x0078,0x007e,0x0083,0x0088,
	0x008e,0x0093,0x0098,0x009d,0x00a2,0x00a7,0x00ab,0x00b0,
	0x00b5,0x00b9,0x00bd,0x00c1,0x00c5,0x00c9,0x00cd,0x00d1,
	0x00d4,0x00d8,0x00db,0x00de,0x00e1,0x00e4,0x00e7,0x00ea,
	0x00ec,0x00ee,0x00f1,0x00f3,0x00f4,0x00f6,0x00f8,0x00f9,
	0x00fb,0x00fc,0x00fd,0x00fe,0x00fe,0x00ff,0x00ff,0x00ff,
	0x0100,0x00ff,0x00ff,0x00ff,0x00fe,0x00fe,0x00fd,0x00fc,
	0x00fb,0x00f9,0x00f8,0x00f6,0x00f4,0x00f3,0x00f1,0x00ee,
	0x00ec,0x00ea,0x00e7,0x00e4,0x00e1,0x00de,0x00db,0x00d8,
	0x00d4,0x00d1,0x00cd,0x00c9,0x00c5,0x00c1,0x00bd,0x00b9,
	0x00b5,0x00b0,0x00ab,0x00a7,0x00a2,0x009d,0x0098,0x0093,
	0x008e,0x0088,0x0083,0x007e,0x0078,0x0073,0x006d,0x0067,
	0x0061,0x005c,0x0056,0x0050,0x004a,0x0044,0x003e,0x0038,
	0x0031,0x002b,0x0025,0x001f,0x0019,0x0012,0x000c,0x0006,
	0x0000,0xfffa,0xfff4,0xffee,0xffe7,0xffe1,0xffdb,0xffd5,
	0xffcf,0xffc8,0xffc2,0xffbc,0xffb6,0xffb0,0xffaa,0xffa4,
	0xff9f,0xff99,0xff93,0xff8d,0xff88,0xff82,0xff7d,0xff78,
	0xff72,0xff6d,0xff68,0xff63,0xff5e,0xff59,0xff55,0xff50,
	0xff4b,0xff47,0xff43,0xff3f,0xff3b,0xff37,0xff33,0xff2f,
	0xff2c,0xff28,0xff25,0xff22,0xff1f,0xff1c,0xff19,0xff16,
	0xff14,0xff12,0xff0f,0xff0d,0xff0c,0xff0a,0xff08,0xff07,
	0xff05,0xff04,0xff03,0xff02,0xff02,0xff01,0xff01,0xff01,
	0xff00,0xff01,0xff01,0xff01,0xff02,0xff02,0xff03,0xff04,
	0xff05,0xff07,0xff08,0xff0a,0xff0c,0xff0d,0xff0f,0xff12,
	0xff14,0xff16,0xff19,0xff1c,0xff1f,0xff22,0xff25,0xff28,
	0xff2c,0xff2f,0xff33,0xff37,0xff3b,0xff3f,0xff43,0xff47,
	0xff4b,0xff50,0xff55,0xff59,0xff5e,0xff63,0xff68,0xff6d,
	0xff72,0xff78,0xff7d,0xff82,0xff88,0xff8d,0xff93,0xff99,
	0xff9f,0xffa4,0xffaa,0xffb0,0xffb6,0xffbc,0xffc2,0xffc8,
	0xffcf,0xffd5,0xffdb,0xffe1,0xffe7,0xffee,0xfff4,0xfffa,
};
short tcos[]={
	0x0100,0x00ff,0x00ff,0x00ff,0x00fe,0x00fe,0x00fd,0x00fc,
	0x00fb,0x00f9,0x00f8,0x00f6,0x00f4,0x00f3,0x00f1,0x00ee,
	0x00ec,0x00ea,0x00e7,0x00e4,0x00e1,0x00de,0x00db,0x00d8,
	0x00d4,0x00d1,0x00cd,0x00c9,0x00c5,0x00c1,0x00bd,0x00b9,
	0x00b5,0x00b0,0x00ab,0x00a7,0x00a2,0x009d,0x0098,0x0093,
	0x008e,0x0088,0x0083,0x007e,0x0078,0x0073,0x006d,0x0067,
	0x0061,0x005c,0x0056,0x0050,0x004a,0x0044,0x003e,0x0038,
	0x0031,0x002b,0x0025,0x001f,0x0019,0x0012,0x000c,0x0006,
	0x0000,0xfffa,0xfff4,0xffee,0xffe7,0xffe1,0xffdb,0xffd5,
	0xffcf,0xffc8,0xffc2,0xffbc,0xffb6,0xffb0,0xffaa,0xffa4,
	0xff9f,0xff99,0xff93,0xff8d,0xff88,0xff82,0xff7d,0xff78,
	0xff72,0xff6d,0xff68,0xff63,0xff5e,0xff59,0xff55,0xff50,
	0xff4b,0xff47,0xff43,0xff3f,0xff3b,0xff37,0xff33,0xff2f,
	0xff2c,0xff28,0xff25,0xff22,0xff1f,0xff1c,0xff19,0xff16,
	0xff14,0xff12,0xff0f,0xff0d,0xff0c,0xff0a,0xff08,0xff07,
	0xff05,0xff04,0xff03,0xff02,0xff02,0xff01,0xff01,0xff01,
	0xff00,0xff01,0xff01,0xff01,0xff02,0xff02,0xff03,0xff04,
	0xff05,0xff07,0xff08,0xff0a,0xff0c,0xff0d,0xff0f,0xff12,
	0xff14,0xff16,0xff19,0xff1c,0xff1f,0xff22,0xff25,0xff28,
	0xff2c,0xff2f,0xff33,0xff37,0xff3b,0xff3f,0xff43,0xff47,
	0xff4b,0xff50,0xff55,0xff59,0xff5e,0xff63,0xff68,0xff6d,
	0xff72,0xff78,0xff7d,0xff82,0xff88,0xff8d,0xff93,0xff99,
	0xff9f,0xffa4,0xffaa,0xffb0,0xffb6,0xffbc,0xffc2,0xffc8,
	0xffcf,0xffd5,0xffdb,0xffe1,0xffe7,0xffee,0xfff4,0xfffa,
	0x0000,0x0006,0x000c,0x0012,0x0019,0x001f,0x0025,0x002b,
	0x0031,0x0038,0x003e,0x0044,0x004a,0x0050,0x0056,0x005c,
	0x0061,0x0067,0x006d,0x0073,0x0078,0x007e,0x0083,0x0088,
	0x008e,0x0093,0x0098,0x009d,0x00a2,0x00a7,0x00ab,0x00b0,
	0x00b5,0x00b9,0x00bd,0x00c1,0x00c5,0x00c9,0x00cd,0x00d1,
	0x00d4,0x00d8,0x00db,0x00de,0x00e1,0x00e4,0x00e7,0x00ea,
	0x00ec,0x00ee,0x00f1,0x00f3,0x00f4,0x00f6,0x00f8,0x00f9,
	0x00fb,0x00fc,0x00fd,0x00fe,0x00fe,0x00ff,0x00ff,0x00ff,
};

// Castle Bitmap
extern u16 _binary_casle1_imb_start[240*160];
extern u16 _binary_casle3_imb_start[240*160];
extern u16 _binary_casle4_imb_start[240*160];
extern u16 _binary_casle5_imb_start[240*160];
extern u16 _binary_casle6_imb_start[240*160];
extern u16 _binary_casle7_imb_start[240*160];
extern u16 _binary_casle1p_imb_start[48*32];
extern u16 _binary_casle3p_imb_start[48*32];
extern u16 _binary_casle4p_imb_start[48*32];
extern u16 _binary_casle5p_imb_start[48*32];
extern u16 _binary_casle6p_imb_start[48*32];
extern u16 _binary_casle7p_imb_start[48*32];

extern u16 mountain_map[32*32];
extern u16 mountain_Palette[256];
extern u8 mountain_Char[8*8*(112/8/1)*(121/8)];

extern gMainVal gMain;
extern gGames gGame;

///////////////////////////////////////////////////////////////////////////////
#define RIGHT 1
#define LEFT 0
#define MAP_MAX_X 1
///////////////////////////////////////////////////////////////////////////////

void bg_init(s8 mode);
void bg_init_first();
void bg_init_gameover();
void bg_init_dead();

void bg_modified(s32 x, s32 y, s32 zoom);

// Set BG Control Register
void SetBgTextControl( vu16 *reg, u16 priority, u16 screen_size, u16 color_mode, u16 mosaic,
						u16 screenblock, u16 char_base );
void SetBgRotationControl( vu16 *reg, u16 priority, u16 screen_size, u16 color_mode, u16 mosaic,
						u16 screenblock, u16 char_base, u16 area_over);

// Set Display Control Register
void SetDispControl(vu16* reg, u16 bgMode, u16 obj_window, u16 window0, u16 window1, 
					u16 obj, u16 bg0, u16 bg1, u16 bg2, u16 bg3,
					u16 blank, u16 format, u16 hblank, u16 frame );

void Bgmode1(s32 x, s32 y, s32 zoom);
void Bgmode3();
void Bg2_UpDown(s32 y);
void Timer0_Intr(void);

void InitBg1();
u8 InitBg1_Map(u8 x, u8 y);
void BgUpdate(s32 x, s32 y, s32 zoom);
void RightBg1();
void LeftBg1();

void InitBg2();
u16 InitBg2_Map(u8 x, u8 y);
void RightBg2();
void LeftBg2();

void InitBg3();
u16 InitBg3_Map(u8 x, u8 y);
void RightBg3();
void LeftBg3();


/////////////////////////////////////////////////////////////////////////////

typedef struct Bg
{
	s32 MapSrc_x;
	s32 MapDest_x;
	s16 Bg_dxR;
	s16 Bg_dxL;
	s16 Bg_dx;
	s16 Offset_x;
	s16 Offset_y;
	u8 ScrollFlag;
	s16 ScrollWait;
	u8 ScrollWait_Y;
}BgDat;

// BG1 Forest Data
extern u16 bg1_Palette[256];
extern u8 bg1_Character[8*8*243];
extern u8 bg1_Map[240*40];
u8 Bg1_ScreenDat[64*64];

// BG2 Mountain Data
extern u8 bg2_Character[8*8*314];
extern u16 bg2_Map[45*40];
u16 Bg2_ScreenDat[32*32];

// Bg3 Cloud Data
extern u16 bg3_Palette[16];
extern u8 bg3_Character[8*8/2*224];
extern u16 bg3_Map[90*30];
u16 Bg3_ScreenDat[32*32];

u8 Bg_Mode;
s32 prev_x, prev_y;

BgDat Bg1;		// Forest
BgDat Bg2;		// Mountain
BgDat Bg3;		// Cloud

s32 rot_center_x, rot_center_y;

// Scaling Rotation Parameter
vs32		bg2pa,bg2pb,bg2pc,bg2pd;
vs32		bg2_center_x , bg2_center_y;
//vu16		scale_x , scale_y;
vu32		scale_x , scale_y;
vu16		rotate_value;	/* rotate with 256 */

// x, y move quantity
int move_val_x;
int move_val_y;

float Bg1_Offset_X, Bg1_Offset_Y;	// BG1 Offset
float Bg3_Offset_Y;
int Counter;

// Direct Sound Variable


u8 Biyoon_Count;
s32 Sa;
///////////////////////////////////////////////////////////////////////////////
int tileX, tileY;
int MapX, MapY;
int SoundSize;
// Subroutine
void BitMapMode();

///////////////////////////////////////////////////////////////////////////////
// BG Initialization
// mode; 0:		First Initialization
//       1:		Game Over
//       2:		Yoshi Dies
void bg_init(s8 mode)
{
	switch (mode)	{
	case 0:
		bg_init_first();
		break;
	case 1:
		bg_init_gameover();
		break;
	case 2:
		bg_init_first();
		break;
	default:
		break;
	}
}

void bg_init_first()
{
	// BG Control Register Initialization
	// Cloud
	SetBgTextControl( (vu16 *)REG_BG0CNT, BG_PRIORITY_3, BG_SCREEN_SIZE_0, BG_COLOR_16,
					BG_MOS_OFF, 28, CHAR_BASE_0);
	// Mountain
	SetBgTextControl( (vu16 *)REG_BG1CNT, BG_PRIORITY_2, BG_SCREEN_SIZE_0, BG_COLOR_256,
					BG_MOS_OFF, 29, CHAR_BASE_2);
	// Forest
	SetBgRotationControl( (vu16 *)REG_BG2CNT, BG_PRIORITY_1, BG_SCREEN_SIZE_2, BG_COLOR_256,
					BG_MOS_OFF, 30, CHAR_BASE_1, BG_LOOP_ON);
	
	// Variable Initialization
	rot_center_x = 120, rot_center_y = 80;
	Counter = 0;
	Biyoon_Count = 0;
	
	scale_x = 0x100;
	scale_y = 0x100;

	bg2_center_x = 256*scale_x;
	bg2_center_y = 232*scale_y;

	rotate_value = 0;
	prev_x = 0;
	prev_y = 0;
	
	// Bg1	Forest
	Bg1.ScrollFlag = RIGHT;
	Bg1.MapSrc_x = 64;//64;
	Bg1.MapDest_x = 0;
	Bg1.Bg_dxR = 0;
	Bg1.Bg_dxL = 0;
	Bg1.Bg_dx = 0;
	
	Bg1.Offset_x = 0;	Bg1.Offset_y = 0;

	// Bg2	Mountain
	Bg2.ScrollFlag = RIGHT;
	Bg2.MapSrc_x = 32;
	Bg2.MapDest_x = 0;
	Bg2.Bg_dxR = 0;
	Bg2.Bg_dxL = 0;
	Bg2.Offset_x = 8;	Bg2.Offset_y = 50;
	Bg2.ScrollWait = 0;	Bg2.ScrollWait_Y = 0;

	// Bg3	Cloud
	Bg3.ScrollFlag = RIGHT;
	Bg3.MapSrc_x = 32;
	Bg3.MapDest_x = 0;
	Bg3.Bg_dxR = 0;
	Bg3.Bg_dxL = 0;
	Bg3.Offset_x = 8;	Bg3.Offset_y = 50;
	Bg3.ScrollWait = 0;	Bg3.ScrollWait_Y = 0;

	Bg_Mode = 1;
	Bg1_Offset_X = 0;	Bg1_Offset_Y = 0;	// Mountain
	Bg3_Offset_Y = 30;
	move_val_x = 0;	move_val_y = 0;


	// Set BG Character and Screen
	// Bg0
	DmaArrayCopy(3, bg3_Character, CHAR_BASE0_ADDR, 16);
	InitBg3();
	DmaArrayCopy(3, Bg3_ScreenDat, CHAR_BASE3_ADDR+0x2000,        16);

	// Bg1
	DmaArrayCopy(3, bg2_Character, CHAR_BASE2_ADDR, 16);
	InitBg2();
	DmaArrayCopy(3, Bg2_ScreenDat, CHAR_BASE3_ADDR+0x2800,        16);
	// Bg2
	DmaArrayCopy(3, bg1_Character, CHAR_BASE1_ADDR, 16);
	DmaArrayCopy(3, bg1_Palette, BG_PLTT,        16);
	InitBg1();
//	DmaArrayCopy(3, BgScreenDat,   CHAR_BASE3_ADDR + 0x3000,        16);
	DmaArrayCopy(3, Bg1_ScreenDat,   CHAR_BASE3_ADDR + 0x3000,        16);

}

void bg_init_gameover()
{
	Bgmode3();
}

void bg_init_dead()
{
}


void bg_modified(s32 x, s32 y, s32 zoom)
{
	switch (Bg_Mode)	{
	case 1:
		Bgmode1(x, y, zoom);
		break;
	case 3:
		Bgmode3();
		break;
	default:
		break;
	}

}


void Bgmode1(s32 x, s32 y, s32 zoom)
{
	s32	start_x , start_y;

	// Set BG Screen Data
	// BG0
	DmaArrayCopy(3, Bg3_ScreenDat, CHAR_BASE3_ADDR+0x2000,        16);
	// BG1
	DmaArrayCopy(3, Bg2_ScreenDat, CHAR_BASE3_ADDR+0x2800,        16);
	// BG2
	DmaArrayCopy(3, Bg1_ScreenDat, CHAR_BASE3_ADDR + 0x3000,        16);

	// Set BG offset
	*(vu16 *)REG_BG0HOFS = (s32)Bg3.Offset_x;
	*(vu16 *)REG_BG0VOFS = Bg3_Offset_Y;
	*(vu16 *)REG_BG1HOFS = Bg2.Offset_x;
//	*(vu16 *)REG_BG1VOFS = Bg3.Offset_y;//Bg1_Offset_Y;
	*(vu16 *)REG_BG1VOFS = Bg1_Offset_Y;

	// Set up Scaling Rotation
	// Set up BG Data Reference Direction
	bg2pa = (s32)tcos[ rotate_value ] * 0x10000 / zoom;
	bg2pb = (s32)tsin[ rotate_value ] * 0x10000 / zoom;
	bg2pc =(s32)-tsin[ rotate_value ] * 0x10000 / zoom;
	bg2pd = (s32)tcos[ rotate_value ] * 0x10000 / zoom;

	*(vu16 *)REG_BG2PA = (u16)bg2pa;
	*(vu16 *)REG_BG2PB = (u16)bg2pb;
	*(vu16 *)REG_BG2PC = (u16)bg2pc;
	*(vu16 *)REG_BG2PD = (u16)bg2pd;


	// Set up BG Data Reference Start Point
	start_x = ( 0 * 0x100 )
//	start_x = ( 1 * 0x100 )
		- (bg2pa * 120 )
		- (bg2pb *  80 )
		- bg2_center_x;

	start_y = ( 0 * 0x100 )
		- (bg2pc * 120 ) 
		- (bg2pd *  80 ) 
		- bg2_center_y;
	
	// Store result

	*(vu16 *)REG_BG2X_L = (start_x & 0xffff);
	*(vu16 *)REG_BG2X_H = (u16)(u32)((start_x & 0x0fff0000)>>16);
	*(vu16 *)REG_BG2Y_L = (start_y & 0xffff);
	*(vu16 *)REG_BG2Y_H = (u16)(u32)((start_y & 0x0fff0000)>>16);

	BgUpdate(x, y, zoom);		// BG Update
}

//991111 T.I
void siro_anm(s16 num)
{
	s16 i;
	u8 *tbl[] = {
		(u8*)_binary_casle1p_imb_start,
		(u8*)_binary_casle3p_imb_start,
		(u8*)_binary_casle4p_imb_start,
		(u8*)_binary_casle5p_imb_start,
		(u8*)_binary_casle6p_imb_start,
		(u8*)_binary_casle7p_imb_start,
#if 0
		(u8*)_binary_casle1_imb_start,
		(u8*)_binary_casle3_imb_start,
		(u8*)_binary_casle4_imb_start,
		(u8*)_binary_casle5_imb_start,
		(u8*)_binary_casle6_imb_start,
		(u8*)_binary_casle7_imb_start
#endif
	};
	u8 *ppix,*pt;
	
	ppix = tbl[num];
//	ppix = tbl[2];
	pt = (u8*)(BG_BITMAP0_VRAM+136*2 + 240*8*2);
	for(i=0; i<32; i++)
	{
		DmaCopy(3, ppix, pt, 48*2,16);//  Set Bitmap
		ppix += 48*2;
		pt += 240*2;
	}
}

// For Game Over
void Bgmode3()
{
	u8 val = 2;

	bg2_center_x = 144 * scale_x;
//	bg2_center_y = (256-152) * scale_y;
	bg2_center_y = (176) * scale_y;

	*(vu16 *)REG_BG2X_L = 0x100;
	*(vu16 *)REG_BG2X_H = 0;
	*(vu16 *)REG_BG2Y_L = 0x100;
	*(vu16 *)REG_BG2Y_H = 0;

	*(vu16 *)REG_BG3PA = 0x100;
	*(vu16 *)REG_BG3PB = 0;
	*(vu16 *)REG_BG3PC = 0x100;
	*(vu16 *)REG_BG3PD = 0;

	*(vu16 *)REG_BG3X_L = 0x100;
	*(vu16 *)REG_BG3X_H = 0;
	*(vu16 *)REG_BG3Y_L = 0x100;
	*(vu16 *)REG_BG3Y_H = 0;

	SetBgRotationControl( (vu16 *)REG_BG3CNT, BG_PRIORITY_2, BG_SCREEN_SIZE_2,
			 BG_COLOR_256, BG_MOS_OFF, 0, 0, BG_LOOP_ON);

	*(vu16 *)REG_DISPCNT = DISP_MODE_3 | DISP_OBJ_BG_ALL_ON| DISP_OBJ_CHAR_1D_MAP;
#if 0
	//	Castle Animation
	Counter++;
	if (Biyoon_Count < 2) {
		if (Counter == 1){
			DmaArrayCopy(3, _binary_casle1_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter < val && Counter!=1){
//			DmaArrayCopy(3, _binary_casle1_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
			siro_anm(0);
		}
		if (Counter > val*2 && Counter < val*3){
//			DmaArrayCopy(3, _binary_casle3_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
//			DmaCopy(3, _binary_casle3_imb_start, BG_BITMAP0_VRAM, 19200,16);	//  Set Bitmap
			siro_anm(1);
		}
		if (Counter > val*3 && Counter < val*4){
//			DmaArrayCopy(3, _binary_casle4_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
//			DmaCopy(3, _binary_casle3_imb_start, BG_BITMAP0_VRAM, 19200,16);	//  Set Bitmap
			siro_anm(2);
		}
		if (Counter > val*4 && Counter < val*5){
//			DmaArrayCopy(3, _binary_casle5_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
//			DmaCopy(3, _binary_casle5_imb_start, BG_BITMAP0_VRAM, 19200,16);	//  Set Bitmap
			siro_anm(3);
		}
		if (Counter > val*5 && Counter < val*6){
//			DmaArrayCopy(3, _binary_casle6_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
//			DmaCopy(3, _binary_casle6_imb_start, BG_BITMAP0_VRAM, 19200,16);	//  Set Bitmap
			siro_anm(4);
		}
		if (Counter > val*6 && Counter < val*7){
//			DmaArrayCopy(3, _binary_casle7_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
//			DmaCopy(3, _binary_casle7_imb_start, BG_BITMAP0_VRAM, 19200,16);	//  Set Bitmap
			siro_anm(5);
		}

		if (Counter > val*7){
			Counter = 0;
			if (--val < 1)
				val = 4;
			Biyoon_Count++;
		}
	}

	if (Biyoon_Count >= 2) {
		val = 2;
		if (Counter < val){
//			DmaArrayCopy(3, _binary_casle3_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
			siro_anm(1);
		}
		if (Counter > val*2 && Counter < val*3){
//			DmaArrayCopy(3, _binary_casle6_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
			siro_anm(4);
		}
		if (Counter > val*3 && Counter < val*4){
//			DmaArrayCopy(3, _binary_casle1_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
			siro_anm(0);
		}
		if (Counter > val*4)
			Counter = 0;
	}
#else
	//	Castle Animation
	Counter++;
	if (Biyoon_Count < 2) {
		if (Counter < val){
			DmaArrayCopy(3, _binary_casle1_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*2 && Counter < val*3){
			DmaArrayCopy(3, _binary_casle3_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*3 && Counter < val*4){
			DmaArrayCopy(3, _binary_casle4_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*4 && Counter < val*5){
			DmaArrayCopy(3, _binary_casle5_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*5 && Counter < val*6){
			DmaArrayCopy(3, _binary_casle6_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*6 && Counter < val*7){
			DmaArrayCopy(3, _binary_casle7_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}

		if (Counter > val*7){
			Counter = 0;
			if (--val < 1)
				val = 4;
			Biyoon_Count++;
		}
	}

	if (Biyoon_Count >= 2) {
		val = 2;
		if (Counter < val){
			DmaArrayCopy(3, _binary_casle3_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*2 && Counter < val*3){
			DmaArrayCopy(3, _binary_casle6_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*3 && Counter < val*4){
			DmaArrayCopy(3, _binary_casle1_imb_start, BG_BITMAP0_VRAM, 16);	//  Set Bitmap
		}
		if (Counter > val*4)
			Counter = 0;
	}

#endif
}


///////////////////////////////////////////////////////////////////////////////
void Bg2_UpDown(s32 y)
{
	s32 y_sa;

	y_sa = y - prev_y;

	if (y_sa != 0)	{
		move_val_y = abs(y_sa);
		
	}

	while(move_val_y)
	{
		if (y_sa > 0)	{
			bg2_center_y -= scale_y;
			Bg1_Offset_Y += 0.5f;
			Bg3_Offset_Y += 0.25f;
		}
		if ( y_sa < 0)	{
			bg2_center_y += scale_y;
			Bg1_Offset_Y -= 0.5f;
			Bg3_Offset_Y -= 0.25f;
		}
		move_val_y--;
	}

/*
	if (y_sa > 0)	{
		bg2_center_y -= y_sa * scale_y;
//		Bg1_Offset_Y += y_sa * 0.5f;
//		Bg3_Offset_Y += y_sa * 0.25f;
	}
	if ( y_sa < 0)	{
		bg2_center_y -= y_sa * scale_y;
//		Bg1_Offset_Y -= y_sa * 0.5f;
//		Bg3_Offset_Y -= y_sa * 0.25f;
	}
*/
	prev_y = y;
}

// Set BG Control Register
void SetBgTextControl( vu16 *reg, u16 priority, u16 screen_size, u16 color_mode, u16 mosaic,
						u16 screenblock, u16 char_base)
{
	*reg = priority | screen_size | color_mode | mosaic
			| screenblock << BG_SCREEN_BASE_SHIFT | char_base << BG_CHAR_BASE_SHIFT ;
}

void SetBgRotationControl( vu16 *reg, u16 priority, u16 screen_size, u16 color_mode, u16 mosaic,
						u16 screenblock, u16 char_base, u16 area_over)
{
	*reg = priority | screen_size | color_mode | mosaic
			| screenblock << BG_SCREEN_BASE_SHIFT | char_base << BG_CHAR_BASE_SHIFT | area_over;
}


void SetDispControl(vu16* reg, u16 bgMode, u16 obj_window, u16 window0, u16 window1, 
					u16 obj, u16 bg0, u16 bg1, u16 bg2, u16 bg3,
					u16 blank, u16 format, u16 hblank, u16 frame )
{
	*reg = obj_window | window0 | window1 |
			obj | bg3 | bg2 | bg1 | bg0 |
			blank | format | hblank | frame | bgMode;

}






void InitBg1()
{
	u8 x, y;
	for (y = 0; y < 64; y++)
	{
		for (x = 0; x < 64; x++)
		{
			Bg1_ScreenDat[y * 64 + x] = InitBg1_Map(x, y);
		}
	}
}

u8 InitBg1_Map(u8 x, u8 y)
{
	if (y < 24)
		return bg1_Map[0];
	if (y >= 24 )
		return bg1_Map[(y - 24) * 240 + x + 0];
	return 0;
}

// BG Update
void BgUpdate(s32 x, s32 y, s32 zoom)
{
	s32 sa;
	s32 tmp;
	Bg2_UpDown(y);

	tmp = 0;
	
	
	sa = (x - prev_x);
	Sa = sa;
	if (sa > 1000)	{
		sa -= 1920;
	}else if (sa < -1000)	{
		sa += 1920;
	}
	
	prev_x = x;
	
	if (sa != 0)	{
		move_val_x = abs(sa);
	}

	if (sa > 0) {		// Right Direction
		// Bg1
		bg2_center_x -= move_val_x * scale_x;
		Bg1.Bg_dx += move_val_x;

//		bg2_center_x -= sa * scale_x;
//		Bg1.Bg_dx += sa;

		if (Bg1.Bg_dx >= 8)	{
			Bg1.Bg_dx -= 8;
			RightBg1();
		}

		// Bg2
		if (++Bg2.ScrollWait >= 2){
			Bg2.ScrollWait = 0;
			Bg2.Offset_x++;
			Bg2.Bg_dxR++;
		}
		if (Bg2.Bg_dxR >= 8)	{
			RightBg2();
			Bg2.Bg_dxR = 0;
		}
		// Bg3
		if ((++Bg3.ScrollWait >= 4)){
			Bg3.ScrollWait = 0;
			Bg3.Offset_x++;
			Bg3.Bg_dxR++;
		}
		if (Bg3.Bg_dxR >= 8)	{
			RightBg3();
			Bg3.Bg_dxR = 0;
		}
	}

	if (sa < 0) {		// Left Direction
		// Bg1
		bg2_center_x += move_val_x * scale_x;
		Bg1.Bg_dx -= move_val_x;
//		bg2_center_x -= sa * scale_x;
//		Bg1.Bg_dx += sa;
		
		if (Bg1.Bg_dx <= -8)	{
			Bg1.Bg_dx += 8;
			LeftBg1();
		}
		
		// Bg2
		if (--Bg2.ScrollWait <= -2){
			Bg2.ScrollWait = 0;
			Bg2.Offset_x--;
			//Bg2.Bg_dxL++;
			Bg2.Bg_dxR--;
		}
		//if (Bg2.Bg_dxL >= 8)	{
		if (Bg2.Bg_dxR <= -8)	{
			LeftBg2();
			Bg2.Bg_dxR = 0;
		//	Bg2.Bg_dxL = 0;
		}
		// Bg3
		if ((--Bg3.ScrollWait <= -4)){
			Bg3.ScrollWait = 0;
			Bg3.Offset_x--;
			Bg3.Bg_dxL++;
		}
		if (Bg3.Bg_dxL >= 8)	{
			LeftBg3();
			Bg3.Bg_dxL = 0;
		}
	}
}



void RightBg1()
{
	u8 i;
	
	if ( Bg1.ScrollFlag != RIGHT )	{	// When direction progressing changed
		Bg1.ScrollFlag = RIGHT;
		Bg1.MapSrc_x += 64;
		if (Bg1.MapSrc_x > 239)
			Bg1.MapSrc_x -= 240;
	}

	// Rewrite Row
	for (i = 0; i< 64; i++)
	{
		if (i < 24 )	{
			Bg1_ScreenDat[i*64 + Bg1.MapDest_x] = bg1_Map[0];
		}
		if (i >= 24 )	{
			Bg1_ScreenDat[i*64 + Bg1.MapDest_x] = bg1_Map[(i - 24)*240 + Bg1.MapSrc_x];
		}
	}

	Bg1.MapSrc_x++;
	if (Bg1.MapSrc_x > 239)
		Bg1.MapSrc_x = 0;
	
	Bg1.MapDest_x++;
	if (Bg1.MapDest_x > 63)
		Bg1.MapDest_x = 0;
}

void LeftBg1()
{
	u8 i;
	
	// When direction progressing changed
	if ( Bg1.ScrollFlag != LEFT )	{
		Bg1.ScrollFlag = LEFT;
		Bg1.MapSrc_x -= 64;
		if (Bg1.MapSrc_x < 0)
			Bg1.MapSrc_x += 240;
	}
	Bg1.MapSrc_x--;
	if (Bg1.MapSrc_x < 0)
		Bg1.MapSrc_x = 239;

	Bg1.MapDest_x--;
	if (Bg1.MapDest_x < 0)
		Bg1.MapDest_x = 63;

	for (i = 0; i< 64; i++)
	{
		if (i < 24 )	{
			Bg1_ScreenDat[i*64 + Bg1.MapDest_x] = bg1_Map[0];
		}
		if (i >= 24 )	{
			Bg1_ScreenDat[i*64 + Bg1.MapDest_x] = bg1_Map[(i-24)*240 + Bg1.MapSrc_x];	// Rewrite Row
		}
	}
}

void InitBg2()
{
	u8 x, y;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			Bg2_ScreenDat[y * 32 + x] = InitBg2_Map(x, y);
		}
	}
}

u16 InitBg2_Map(u8 x, u8 y)
{
	return bg2_Map[y * 45 + x];
}

void RightBg2()
{
	u8 i;

	if ( Bg2.ScrollFlag != RIGHT )	{	// When direction progressing changed
		Bg2.ScrollFlag = RIGHT;
		Bg2.MapSrc_x += 32;
		if (Bg2.MapSrc_x > 44)
			Bg2.MapSrc_x -= 45;
	}

	for (i = 0; i< 32; i++)
	{
		Bg2_ScreenDat[i*32 + Bg2.MapDest_x] = bg2_Map[i*45 + Bg2.MapSrc_x];	// Rewrite Row
	}
	Bg2.MapSrc_x++;
	if (Bg2.MapSrc_x > 44)
		Bg2.MapSrc_x = 0;
	
	Bg2.MapDest_x++;
	if (Bg2.MapDest_x > 31)
		Bg2.MapDest_x = 0;

}




void LeftBg2()
{
	u8 i;

	if ( Bg2.ScrollFlag != LEFT )	{	// When direction progressing changed
		Bg2.ScrollFlag = LEFT;
		Bg2.MapSrc_x -= 32;
		if (Bg2.MapSrc_x < 0)
			Bg2.MapSrc_x += 45;
	}

	Bg2.MapSrc_x--;
	if (Bg2.MapSrc_x < 0)
		Bg2.MapSrc_x = 44;
	Bg2.MapDest_x--;
	if (Bg2.MapDest_x < 0)
		Bg2.MapDest_x = 31;

	for (i = 0; i< 32; i++)
	{
		Bg2_ScreenDat[i*32 + Bg2.MapDest_x] = bg2_Map[i*45 + Bg2.MapSrc_x];	// Rewrite Row
	}

}


void InitBg3()
{
	u8 x, y;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			Bg3_ScreenDat[y * 32 + x] = InitBg3_Map(x, y);
		}
	}

}

u16 InitBg3_Map(u8 x, u8 y)
{
	return bg3_Map[y * 90 + x];
}

void RightBg3()
{
	u8 i;

	if ( Bg3.ScrollFlag != RIGHT )	{	// When direction progressing changed
		Bg3.ScrollFlag = RIGHT;
		Bg3.MapSrc_x += 32;
		if (Bg3.MapSrc_x > 89)
			Bg3.MapSrc_x -= 90;
	}

	for (i = 0; i< 32; i++)
	{
		Bg3_ScreenDat[i*32 + Bg3.MapDest_x] = bg3_Map[i*90 + Bg3.MapSrc_x];	// Rewrite Row
	}
	Bg3.MapSrc_x++;
	if (Bg3.MapSrc_x > 89)
		Bg3.MapSrc_x = 0;
	
	Bg3.MapDest_x++;
	if (Bg3.MapDest_x > 31)
		Bg3.MapDest_x = 0;

}

void LeftBg3()
{
	u8 i;

	if ( Bg3.ScrollFlag != LEFT )	{	// When direction progressing changed
		Bg3.ScrollFlag = LEFT;
		Bg3.MapSrc_x -= 32;
		if (Bg3.MapSrc_x < 0)
			Bg3.MapSrc_x += 90;
	}

	Bg3.MapSrc_x--;
	if (Bg3.MapSrc_x < 0)
		Bg3.MapSrc_x = 89;
	Bg3.MapDest_x--;
	if (Bg3.MapDest_x < 0)
		Bg3.MapDest_x = 31;

	for (i = 0; i< 32; i++)
	{
		Bg3_ScreenDat[i*32 + Bg3.MapDest_x] = bg3_Map[i*90 + Bg3.MapSrc_x];	// Rewrite Row
	}

}
