/********************************************************************/
/*          bg.h                                                    */
/*                 Data external declaration                        */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef	_BG_H
#define	_BG_H

// Character data base address
#define CHAR_BASE0_ADDR  VRAM+0x0000
#define CHAR_BASE1_ADDR  VRAM+0x4000
#define CHAR_BASE2_ADDR  VRAM+0x8000
#define CHAR_BASE3_ADDR  VRAM+0xc000

// Specify character base block 
#define CHAR_BASE_0  0
#define CHAR_BASE_1  1
#define CHAR_BASE_2  2
#define CHAR_BASE_3  3

//#define RIGHT 1
//#define LEFT  0
#define UP    2
#define DOWN  3

#define BG_INIT   0x00
#define BG_DRAW   0x01
#define BG_DELETE 0x02
#define BG_IDLE   0x03


//------------------------------------------------------------------//
//		Structure for BG                                    //
//------------------------------------------------------------------//

typedef struct
{
	s32 mapX, mapY;			// map coordinate
	s32 oldX, oldY;			// previous coordinate 
	s32 dx, dy;			// distance moved
	s32 MapSrc_x;	s32 MapSrc_y;	// Source coordinate of screen data 
	s32 MapDest_x;	s32 MapDest_y;	// Destination coordinate of screen data
	s32 move_val_x, move_val_y;	// distance moved
	s8  Scroll_Flg_X;		// Scroll direction of X axis
	u8  Scroll_Flg_Y;		// Scroll direction of Y axis   
	u8  post_flg;			// To check if data is transferred 
}Bg;



//------------------------------------------------------------------//
//			Prototype Declaration			    //
//------------------------------------------------------------------//

// Sky
void InitSky();
void Init_Sky_ScreenDat();
void DrawSky(s32 x, s32 y);
void DeleteSky(s32 x, s32 y);
void SoraRight();
void SoraLeft();
void SoraUpDown();


// Coral
void InitCoral();
void InitCoralScreenDat();
void DrawCoral(s32 x, s32 y);
void DeleteCoral(s32 x, s32 y);
void CoralRight();
void CoralLeft();
void CoralUpDown();


// Light
void InitLight();
void InitLightScreenDat();
void DrawLight(s32 x, s32 y);
void DeleteLight(s32 x, s32 y);

// Ocean A
void InitOceanA();
void InitOceanAScreenDat();
void DrawOceanA(s32 x, s32 y);
void DeleteOceanA(s32 x, s32 y);
void OceanA_Up(Bg *pBg);
void OceanA_Down(Bg *pBg);
void OceanA_Idle(Bg *pBg, s32 x, s32 y);

// Ocean B
void InitOceanB();
void InitOceanBScreenDat();
void DrawOceanB(s32 x, s32 y);
void DeleteOceanB(s32 x, s32 y);
void OceanB_Up();
void OceanB_Down();


// Initialize BG 
void InitBg();
// Main processing of BG 
void BgProc(s32 x, s32 y);
// Update BG
void UpdateBg(s32 x, s32 y);
// Change VRAM  
void Change_Bg_VRAM(s32 x, s32 y);


// BG animation pattern
typedef struct {
	u8 pat;				// pattern No
	u8* img;			// pointer to graphics data  
	s8 inter;			// animation intervals 
}BgAnmPat;

// Structure for BG animation 
typedef struct {
	u8 counter;			// counter
	u8 pattern;			// pattern No
	u32 dstadr;			// destination address
	BgAnmPat* pBgAnm;		// pointer to pattern data  
}BgAnm;

void initwave2nd(BgAnm* pBgTest);
void Anm_wave2nd(BgAnm* pBgTest);


//------------------------------------------------------------------//
//			External reference declaration 		    //
//------------------------------------------------------------------//
extern Player player;
// Ocean A graphics data 
extern u8 umia__Character[8*8*18];
extern u16 umia__Map[32*64];

// Ocean B graphics data 
extern u16 umi_ab_256x512_Palette[256];
extern u8 umi_ab_256x512_Character[8*8*438];
extern u16 umi_ab_256x512_Map[32*64];

// Coral graphics data 
extern u8 sango1024x256_Character[8*8*247];
extern u16 sango1024x256_Map[128*32];

// Sky graphics data 
extern u8 sora_Character[8*8*488];
extern u16 sora_Map[64*32];

// Light graphics data
extern u8 light4_Character[8*8*100];
extern u16 light4_Map[32*32];

// Data for wave animation 
extern u8 wave2nd1_Char[8*8*(32/8/1)*(8/8)];
extern u8 wave2nd2_Char[8*8*(32/8/1)*(8/8)];
extern u8 wave2nd3_Char[8*8*(32/8/1)*(8/8)];


#endif