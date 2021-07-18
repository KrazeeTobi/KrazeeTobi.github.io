/********************************************************************/
/*          bg.c                                                    */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "bg.h"


//------------------------------------------------------------------//
//			Global Variable   			    //
//------------------------------------------------------------------//

// Animation pattern of waves
BgAnmPat wave2nd_pat[] =
{
	{  0, wave2nd1_Char,   24},
	{  1, wave2nd2_Char,   24},
	{  2, wave2nd3_Char,   24},
	{  0,              0,  -1},
};


Bg Light;  // Light
Bg Coral;  // Coral
Bg OceanA; // Ocean A
Bg OceanB; // Ocean B
Bg Sky;    // Sky

u16 UmiA_ScreenDat[32*32];	// Screen data of Ocean A
u16 Bg2_ScreenDat[32*32];	// Screen data of Ocean B
u16 Sky_ScreenDat[32*32];	// Screen data of Sky
u16 Sango_ScreenDat[32*32]; // Screen data of Coral

s32 ocean_xPos;
s32 sora_xPos;
u8 DisplayArea;
BgAnm wave2nd;

// Initialize wave animation
void initwave2nd(BgAnm* pBgTest)
{
	pBgTest->counter = 0;
	pBgTest->pattern = 0;
	pBgTest->pBgAnm = &wave2nd_pat[0];
//	pBgTest->dstadr = CHAR_BASE3_ADDR+(64);
	pBgTest->dstadr = CHAR_BASE2_ADDR+(64);
}

// Wave animation
void Anm_wave2nd(BgAnm* pBgTest)
{
	if (++pBgTest->counter > pBgTest->pBgAnm->inter)
	{
		pBgTest->counter = 0;
		pBgTest->pBgAnm++;

		if (pBgTest->pBgAnm->inter == -1) {
			pBgTest->pBgAnm = &wave2nd_pat[0];
		}
	}

	DmaCopy(3, pBgTest->pBgAnm->img,
			pBgTest->dstadr, sizeof(wave2nd1_Char), 16);
}




//------------------------------------------------------------------//
//			Initialize BG                               //
//------------------------------------------------------------------//

void InitBg()
{
	ocean_xPos = 0;
	sora_xPos = 0;
	DisplayArea = UP;
	// Transfer GB palette
	DmaArrayCopy(3, umi_ab_256x512_Palette,   BG_PLTT,        16);
	InitSky();
	InitOceanA();
	InitOceanB();
	InitCoral();
	InitLight();

	initwave2nd(&wave2nd);
}


//------------------------------------------------------------------//
//			Main Routine of BG                          //
//------------------------------------------------------------------//

void BgProc(s32 x, s32 y)
{
	if (y < 256){
		DisplayArea = UP;
	} else if(y > 256){
		DisplayArea = DOWN;
	}
}


//------------------------------------------------------------------//
//			Change VRAM of BG                           //
//------------------------------------------------------------------//

void Change_Bg_VRAM(s32 x, s32 y)
{
	// Draw BG
	DrawSky(x, y);
	DrawOceanA(x, y);

	DrawLight(x, y);

	DrawOceanB(x, y);
	DrawCoral(x, y);


	// Delete BG
	DeleteSky(x, y);
	DeleteCoral(x, y);
	DeleteOceanA(x, y);
	DeleteOceanB(x, y);
}


//------------------------------------------------------------------//
//			Update BG                                   //
//------------------------------------------------------------------//

void UpdateBg(s32 x, s32 y)
{
	s32 dx, dy;
	s32 x_sa, y_sa;

	// Difference from the previous positions
	dx = player.mapX - OceanB.oldX;
	dy = player.mapY - OceanB.oldY;

	OceanB.oldX = x;	OceanB.oldY = y;
	Coral.oldX = x; Coral.oldY = y;

	x_sa = dx;	y_sa = dy;

	// Right direction
	if (dx > 0) {
		ocean_xPos += 0x180;//0x80;

		Coral.dx += x_sa;
		if (Coral.dx >= 8)	{
			Coral.dx -= 8;
			CoralRight();
		}

		sora_xPos  += 1;
		Sky.dx += 1;
		if (Sky.dx >= 8)	{
			Sky.dx -= 8;
			SoraRight();
		}
	}

	// Left direction
	if (dx < 0) {
		ocean_xPos -= 0x180;//0x80;

		Coral.dx += x_sa;
		if (Coral.dx < 0)	{
			Coral.dx += 8;
			CoralLeft();
		}

		sora_xPos  -= 1;
		Sky.dx -= 1;
		if (Sky.dx < 0)	{
			Sky.dx += 8;
			SoraLeft();
		}

	}

	if (y_sa > 0) {		// Down direction
		OceanB.dy += y_sa;
		if (OceanB.dy >= 8)	{
			OceanB.dy -= 8;
			OceanB_Down();
			OceanA_Down(&OceanA);
		}
	}

	if (y_sa < 0) {		// Up direction
		OceanB.dy += y_sa;
		if (OceanB.dy < 0)	{
			OceanB.dy += 8;
			OceanB_Up();
			OceanA_Up(&OceanA);
		}
	}
	Change_Bg_VRAM(x , y);
}




//------------------------------------------------------------------//
//			Initialize BG of Sky                        //
//------------------------------------------------------------------//

void InitSky()
{
	Sky.mapX = 0; Sky.mapY = 0;
	Sky.oldX = 0; Sky.oldY = 0;
	Sky.MapSrc_x = 32;
	Sky.MapDest_x = 0;
	Sky.MapSrc_y = 32;
	Sky.MapDest_y = 0;
	Sky.Scroll_Flg_X = RIGHT;
	Sky.Scroll_Flg_Y = DOWN;

	Sky.post_flg = 0;

	Init_Sky_ScreenDat();
}


//------------------------------------------------------------------//
//			Initialize Screen Data of Sky               //
//------------------------------------------------------------------//

void Init_Sky_ScreenDat()
{
	u16 x, y;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			Sky_ScreenDat[y * 32 + x] = sora_Map[y * 64 + x];
		}
	}
}


//------------------------------------------------------------------//
//			Draw BG of Sky                              //
//------------------------------------------------------------------//

void DrawSky(s32 x, s32 y)
{
	if (y < 96) {
		if (Sky.post_flg != 1) {
			*(vu16 *)REG_BG1CNT =
				BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_3
				| 30 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT ;
			DmaArrayCopy(3, sora_Character, CHAR_BASE0_ADDR,          16);
			DmaArrayCopy(3, Sky_ScreenDat,  CHAR_BASE3_ADDR + 0x3000, 16);
			Sky.post_flg = 1;
		}
		DmaArrayCopy(3, Sky_ScreenDat,  CHAR_BASE3_ADDR + 0x3000, 16);
	}
}


//------------------------------------------------------------------//
//			Delete BG of Sky                            //
//------------------------------------------------------------------//

void DeleteSky(s32 x, s32 y)
{
	if (y > 96 && y < 104) {
//	if (y >= 96) {
		if (Sky.post_flg != 0) {
			DmaClear(3, 0, CHAR_BASE0_ADDR,          0x8000,  16);
			DmaClear(3, 0, CHAR_BASE3_ADDR + 0x3000, 0x0800,  16);
			
			Sky.post_flg = 0;
		}
	}
}


void SoraRight()
{
	u8 i;
	
	if ( Sky.Scroll_Flg_X != RIGHT )	{	// In case the direction is changed.
		Sky.Scroll_Flg_X = RIGHT;
		Sky.MapSrc_x += 32;
		if (Sky.MapSrc_x > 63)
			Sky.MapSrc_x -= 64;
	}

	// Rewrite column
	for (i = 0; i< 32; i++)
	{
		Sky_ScreenDat[i*32 + Sky.MapDest_x]
				= sora_Map[i*64 + Sky.MapSrc_x];	// Rewrite column
	}

	Sky.MapSrc_x++;
	if (Sky.MapSrc_x > 63)
		Sky.MapSrc_x = 0;
	Sky.MapDest_x++;
	if (Sky.MapDest_x > 31)
		Sky.MapDest_x = 0;
}


void SoraLeft()
{
	u8 i;

	if ( Sky.Scroll_Flg_X != LEFT )	{	// In case the direction is changed.
		Sky.Scroll_Flg_X = LEFT;
		Sky.MapSrc_x -= 32;
		if (Sky.MapSrc_x < 0)
			Sky.MapSrc_x += 64;
	}

	Sky.MapSrc_x--;
	if (Sky.MapSrc_x < 0)
		Sky.MapSrc_x = 63;
	Sky.MapDest_x--;
	if (Sky.MapDest_x < 0)
		Sky.MapDest_x = 31;

	for (i = 0; i< 32; i++)
	{
		Sky_ScreenDat[i*32 + Sky.MapDest_x]
			= sora_Map[i*64 + Sky.MapSrc_x];	// Rewrite column
	}
}


//------------------------------------------------------------------//
//			Initialize Coral                            //
//------------------------------------------------------------------//

void InitCoral()
{
	Coral.mapX = 0; Coral.mapY = 0;
	Coral.oldX = 0; Coral.oldY = 0;
	Coral.dx = 0; Coral.dy = 0;
	Coral.MapSrc_x = 32;
	Coral.MapDest_x = 0;
	Coral.MapSrc_y = 32;
	Coral.MapDest_y = 0;
	Coral.Scroll_Flg_X = RIGHT;
	Coral.Scroll_Flg_Y = DOWN;

	Coral.post_flg = 0;

	InitCoralScreenDat();
}


//------------------------------------------------------------------//
//			Initialize Screen Data of Coral             //
//------------------------------------------------------------------//

void InitCoralScreenDat()
{
	u16 x, y;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			Sango_ScreenDat[y * 32 + x] = sango1024x256_Map[y * 128 + x];
		}
	}
}


//------------------------------------------------------------------//
//			Draw Coral                                  //
//------------------------------------------------------------------//

void DrawCoral(s32 x, s32 y)
{
	if (y > 256)	{
//	if (y > 256 && y < 264)	{
		if (Coral.post_flg != 1) {
			*(vu16 *)REG_BG1CNT =					// BG control set
				BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
				| 29 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

			DmaArrayCopy(3, sango1024x256_Character,   CHAR_BASE2_ADDR,   16);
			DmaArrayCopy(3, Sango_ScreenDat,  CHAR_BASE3_ADDR + 0x2800, 16);

			Coral.post_flg = 1;
		}
		DmaArrayCopy(3, Sango_ScreenDat,  CHAR_BASE3_ADDR + 0x2800, 16);
	}
}


//------------------------------------------------------------------//
//			Delete Coral                                //
//------------------------------------------------------------------//

void DeleteCoral(s32 x, s32 y)
{
	if (y < 256) {
		if (Coral.post_flg != 0){
			DmaClear(3, 0, CHAR_BASE2_ADDR,          0x4000, 16);
			DmaClear(3, 0, CHAR_BASE3_ADDR + 0x2800, 0x0800, 16);

			Coral.post_flg = 0;
		}
	}
}


void CoralRight()
{
	u8 i;
	
	if ( Coral.Scroll_Flg_X != RIGHT )	{	// In case the direction is changed
		Coral.Scroll_Flg_X = RIGHT;
		Coral.MapSrc_x += 32;
		if (Coral.MapSrc_x > 127)
			Coral.MapSrc_x -= 128;
	}

	// Rewrite column
	for (i = 0; i< 32; i++)
	{
		Sango_ScreenDat[i*32 + Coral.MapDest_x]
				= sango1024x256_Map[i*128 + Coral.MapSrc_x];	// Rewrite column
	}

	Coral.MapSrc_x++;
	if (Coral.MapSrc_x > 127)
		Coral.MapSrc_x = 0;
	Coral.MapDest_x++;
	if (Coral.MapDest_x > 31)
		Coral.MapDest_x = 0;
}


void CoralLeft()
{
	u8 i;

	if ( Coral.Scroll_Flg_X != LEFT )	{	// In case the direction is changed
		Coral.Scroll_Flg_X = LEFT;
		Coral.MapSrc_x -= 32;
		if (Coral.MapSrc_x < 0)
			Coral.MapSrc_x += 128;
	}

	Coral.MapSrc_x--;
	if (Coral.MapSrc_x < 0)
		Coral.MapSrc_x = 127;
	Coral.MapDest_x--;
	if (Coral.MapDest_x < 0)
		Coral.MapDest_x = 31;

	for (i = 0; i< 32; i++)
	{
		Sango_ScreenDat[i*32 + Coral.MapDest_x]
				= sango1024x256_Map[i*128 + Coral.MapSrc_x];	// Rewrite column
	}

}

void CoralUpDown()
{

}

//------------------------------------------------------------------//
//			Initialize Light                            //
//------------------------------------------------------------------//

void InitLight()
{
	Light.post_flg = 0;
}


//------------------------------------------------------------------//
//			Initialize screen data of Light             //
//------------------------------------------------------------------//

void InitLightScreenDat()
{
}


//------------------------------------------------------------------//
//			Draw Light                                  //
//------------------------------------------------------------------//

void DrawLight(s32 x, s32 y)
{
	if(Light.post_flg != 1){
		*(vu16 *)REG_BG0CNT =
			BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_3
			| 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT;
		*(vu16 *)REG_WINOUT = (WIN_OBJ_ON << 8) | (WIN_BG0_ON << 8)
					| (WIN_BLEND_ON << 8) | WIN_OBJ_ON | WIN_BG1_ON | WIN_BG2_ON;

		DmaArrayCopy(3, light4_Character,   CHAR_BASE3_ADDR,        16);
		DmaArrayCopy(3, light4_Map,  CHAR_BASE3_ADDR + 0x3800,        16);
		
		Light.post_flg = 1;
	}

}


//------------------------------------------------------------------//
//			Delete Light                                //
//------------------------------------------------------------------//

void DeleteLight(s32 x, s32 y)
{
	if (y > 96 + 88 && y < 96 + 96) {
		DmaClear(3, 0, CHAR_BASE3_ADDR,          0x4000, 16);
		DmaClear(3, 0, CHAR_BASE3_ADDR + 0x3800, 0x0800, 16);

		*(vu16 *)REG_WINOUT = (WIN_OBJ_ON << 8) | (WIN_BLEND_ON << 8)
						| WIN_OBJ_ON | WIN_BG1_ON | WIN_BG2_ON;
	}
}


//------------------------------------------------------------------//
//			Initialize Ocean A                          //
//------------------------------------------------------------------//

void InitOceanA()
{
	OceanA.mapX = 0; OceanA.mapY = 0;
	OceanA.oldX = 0; OceanA.oldY = 0;
	OceanA.MapSrc_x = 32;
	OceanA.MapDest_x = 0;
	OceanA.MapSrc_y = 32;
	OceanA.MapDest_y = 0;
	OceanA.Scroll_Flg_X = RIGHT;
	OceanA.Scroll_Flg_Y = DOWN;
	OceanA.post_flg = 0;
	InitOceanAScreenDat();
}


//------------------------------------------------------------------//
//			Initialize Screen Data of Ocean A           //
//------------------------------------------------------------------//

void InitOceanAScreenDat()
{
	u8 x, y;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			UmiA_ScreenDat[y * 32 + x] = umia__Map[y * 32 + x];
		}
	}
}


void OceanA_Idle(Bg *pBg, s32 x, s32 y)
{
	if (y < 192) {
		if (pBg->post_flg == 0){
			pBg->post_flg = 1;
		}
	}
	if (y > 192 && y < 200) {
		if (OceanA.post_flg == 1){
			DmaClear(3, 0, CHAR_BASE2_ADDR,          0x0400, 16);
			DmaClear(3, 0, CHAR_BASE3_ADDR + 0x2800, 0x0800, 16);
			OceanA.post_flg = 0;
		}
	}

}

//------------------------------------------------------------------//
//			Draw Ocean A                                //
//------------------------------------------------------------------//

void DrawOceanA(s32 x, s32 y)
{
	if (y < 192) {
		*(vu16 *)REG_BG2CNT =
			BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1
			| 29 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
		DmaArrayCopy(3, umia__Character,   CHAR_BASE2_ADDR,   16);
		DmaArrayCopy(3, UmiA_ScreenDat, CHAR_BASE3_ADDR + 0x2800, 16);

		Anm_wave2nd(&wave2nd);
	}
}


//------------------------------------------------------------------//
//			Delete Ocean A                              //
//------------------------------------------------------------------//

void DeleteOceanA(s32 x, s32 y)
{
	if (y > 192 && y < 200) {
		DmaClear(3, 0, CHAR_BASE2_ADDR,          0x2280, 16);
		DmaClear(3, 0, CHAR_BASE3_ADDR + 0x2800, 0x0800, 16);
	}
}


void OceanA_Up(Bg* pBg)
{
	u8 i;

	if ( pBg->Scroll_Flg_Y != UP )	{	// In case the directory is changed
		pBg->Scroll_Flg_Y = UP;
		pBg->MapSrc_y -= 32;
		if (pBg->MapSrc_y < 0)
			pBg->MapSrc_y += 64;
	}

	pBg->MapSrc_y--;
	if (pBg->MapSrc_y < 0)
		pBg->MapSrc_y = 63;
	pBg->MapDest_y--;
	if (pBg->MapDest_y < 0)
		pBg->MapDest_y = 31;

	for (i = 0; i< 32; i++)
	{
		UmiA_ScreenDat[pBg->MapDest_y*32 + i] = umia__Map[pBg->MapSrc_y*32 + i];
	}

}



void OceanA_Down(Bg* pBg)
{
	u8 i;
	
	if ( pBg->Scroll_Flg_Y != DOWN )	{	// In case the directory is changed
		pBg->Scroll_Flg_Y = DOWN;
		pBg->MapSrc_y += 32;
		if (pBg->MapSrc_y > 63)
			pBg->MapSrc_y -= 64;
	}

	// Rewrite row
	for (i = 0; i< 32; i++)
	{
		UmiA_ScreenDat[pBg->MapDest_y*32 + i] = umia__Map[pBg->MapSrc_y*32 + i];
	}

	pBg->MapSrc_y++;
	if (pBg->MapSrc_y > 63)
		pBg->MapSrc_y = 0;
	pBg->MapDest_y++;
	if (pBg->MapDest_y > 31)
		pBg->MapDest_y = 0;
}


//------------------------------------------------------------------//
//			Initialize Ocean B                          //
//------------------------------------------------------------------//

void InitOceanB()
{
	OceanB.mapX = 0; OceanB.mapY = 0;
	OceanB.oldX = 0; OceanB.oldY = 0;
	OceanB.MapSrc_x = 32;
	OceanB.MapDest_x = 0;
	OceanB.MapSrc_y = 32;
	OceanB.MapDest_y = 0;
	OceanB.Scroll_Flg_X = RIGHT;
	OceanB.Scroll_Flg_Y = DOWN;
	OceanB.post_flg = 0;

	InitOceanBScreenDat();
}


//------------------------------------------------------------------//
//		Initialize Screen Data of Ocean B                   //
//------------------------------------------------------------------//

void InitOceanBScreenDat()
{
	u8 x, y;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			Bg2_ScreenDat[y * 32 + x] = umi_ab_256x512_Map[y * 32 + x];
		}
	}
}


//------------------------------------------------------------------//
//			Draw Ocean B                                //
//------------------------------------------------------------------//

void DrawOceanB(s32 x, s32 y)
{
	if (y > 192) {
		*(vu16 *)REG_BG2CNT = // BG control set
			BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_3
			| 15 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT ;
		DmaArrayCopy(3, umi_ab_256x512_Character, CHAR_BASE0_ADDR, 16);
		DmaArrayCopy(3, Bg2_ScreenDat,  CHAR_BASE1_ADDR + 0x3800,  16);
	}
}


//------------------------------------------------------------------//
//			Delete Ocean B                              //
//------------------------------------------------------------------//

void DeleteOceanB(s32 x, s32 y)
{
	if (y < 192 && y > 184) {
		if (OceanB.post_flg != 0)
			OceanB.post_flg = 0;
//		DmaClear(3, 0, CHAR_BASE0_ADDR,          0x8000, 16);
//		DmaClear(3, 0, CHAR_BASE1_ADDR + 0x3800, 0x0800, 16);
	}
}


void OceanB_Up()
{
	u8 i;

	if ( OceanB.Scroll_Flg_Y != UP )	{	// In case the directory is changed
		OceanB.Scroll_Flg_Y = UP;
		OceanB.MapSrc_y -= 32;
		if (OceanB.MapSrc_y < 0)
			OceanB.MapSrc_y += 64;
	}

	OceanB.MapSrc_y--;
	if (OceanB.MapSrc_y < 0)
		OceanB.MapSrc_y = 63;
	OceanB.MapDest_y--;
	if (OceanB.MapDest_y < 0)
		OceanB.MapDest_y = 31;


	for (i = 0; i< 32; i++)
	{
		Bg2_ScreenDat[OceanB.MapDest_y*32 + i] = umi_ab_256x512_Map[OceanB.MapSrc_y*32 + i];
	}
}


void OceanB_Down()
{
	u8 i;
	
	if ( OceanB.Scroll_Flg_Y != DOWN )	{	// In case the directory is chagned
		OceanB.Scroll_Flg_Y = DOWN;
		OceanB.MapSrc_y += 32;
		if (OceanB.MapSrc_y > 63)
			OceanB.MapSrc_y -= 64;
	}

	// Rewrite row
	for (i = 0; i< 32; i++)
	{
		Bg2_ScreenDat[OceanB.MapDest_y*32 + i]
			= umi_ab_256x512_Map[OceanB.MapSrc_y*32 + i];
	}
	OceanB.MapSrc_y++;
	if (OceanB.MapSrc_y > 63)
		OceanB.MapSrc_y = 0;
	OceanB.MapDest_y++;
	if (OceanB.MapDest_y > 31)
		OceanB.MapDest_y = 0;
}


