/********************************************************************/
/*          ring.c                                                  */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "ring.h"


//------------------------------------------------------------------//
//			Global Variable                             //
//------------------------------------------------------------------//

Ring ring[RING_MAX_NUM];

// ring map data
RingMapData ring_map_dat[] = 
{
//    x    y
	{ 200, 360},
	{ 300, 338},
	{ 384, 350},
	{ 488, 15},
	{ 598, 12},

	{ 648, 10},
	{ 708, 20},
	{ 868, 14},
	{ 908, 16},
	{1168, 24},

	{1208, 360},
	{1348, 340},
	{1508, 360},
	{1648, 352},
	{1808, 368},

	{2008, 350},
	{2148, 369},
	{2308, 370},
	{2448, 360},
	{2588, 350},

	{3008, 360},
	{3248, 340},
	{3408, 360},
	{3648, 352},
	{3808, 368},

	{4008, 350},
	{4148, 369},
	{4208, 370},
	{4448, 360},
	{4608, 350},

};

const	u32 Oam_32x64dot[1][2] = {
	{ OAM_COLOR_256 | OAM_V_RECTANGLE | OAM_SIZE_32x64
	, 0},
};


//------------------------------------------------------------------//
//			External Reference Declaration              //
//------------------------------------------------------------------//

extern ObjBuf Oam;
extern Player player;
extern u32	Oam_def[1][2];
extern u8 ring_32_64_right_Char[8*8*(32/8/1/1)*(64/8) + 0];
extern u8 ring_32_64_left_Char[8*8*(32/8/1/1)*(64/8) + 0];
extern short sin_tbl[];
extern short cos_tbl[];

//------------------------------------------------------------------//
//			Initialize Ring                             //
//------------------------------------------------------------------//

void InitRing()
{
	int i;
	Ring* pRing;
	
	pRing = ring;

	for(i = 0; i < RING_MAX_NUM; i++, pRing++) {
		pRing->x = ring_map_dat[i].xPos;
		pRing->y = ring_map_dat[i].yPos;
		pRing->vx = 0;
		pRing->vy = 0;
		pRing->flg = 1;
		pRing->state = RING_NORMAL_STATE;
		pRing->pass_flg = 0;
		pRing->dat = 0;
		pRing->counter = 0;
		pRing->pass_counter = 0;
	}
	DmaArrayCopy(3, ring_32_64_left_Char, RING_L_VRAM_POS, 16)
	DmaArrayCopy(3, ring_32_64_right_Char, RING_R_VRAM_POS, 16)
}


//------------------------------------------------------------------//
//			Main Processing of Ring                     //
//------------------------------------------------------------------//

void RingProc()
{
	u8 i;
	Ring *pRing;
	pRing = ring;

	// inside screen check
	for(i = 0; i < RING_MAX_NUM; i++, pRing++)
	{
		if( pRing->x > player.mapX -  32 &&
	        pRing->x < player.mapX + 240 &&
	        pRing->y > player.mapY -  64 &&
	        pRing->y < player.mapY + 160)
		{
			pRing->flg = 1;
		}else {
			pRing->flg = 0;
		}
	}

	// status control
	RingStateControl(ring);
	// ring pass check
	RingPass(ring, &player);
	// draw ring
	DrawRing(ring);
}


//------------------------------------------------------------------//
//			Ring Status Control                         //
//------------------------------------------------------------------//

void RingStateControl(Ring* pRing)
{
	u8 i;
	for(i = 0; i < RING_MAX_NUM; i++, pRing++) {
		if(pRing->flg != 0)	{
			(*pRing_state_tbl[pRing->state])(pRing, i);
		}
	}
}


//------------------------------------------------------------------//
//			Create Ring                                 //
//------------------------------------------------------------------//

void CreateRing(Player *pPlayer)
{
	u8 i;
	Ring *pRing;
	
	pRing = ring;

	for(i = 0; i < RING_MAX_NUM; i++, pRing++) {
		pRing->x = ring_map_dat[i].xPos;
		pRing->y = ring_map_dat[i].yPos;
		pRing->counter = i * 4;
	}
}


//------------------------------------------------------------------//
//			Draw Ring                                   //
//------------------------------------------------------------------//

void DrawRing(Ring *pRing)
{
	int i;

	OamData *pOam;	// OAM
	RingMapData *pRingMap;

	pOam = &Oam.Objbuf[RING_OAM_POS];
	pRingMap = ring_map_dat;

	for(i = 0; i < RING_MAX_NUM; i++, pRing++) {
		if(pRing->flg != 0)	{	// inside screen
			// right of ring
			*pOam = *(OamData *)Oam_32x64dot;
			pOam->CharNo = RING_R_CHAR_NO;
			pOam->HPos   = ring_map_dat[i].xPos - player.mapX + 16 + pRing->vx;
			pOam->VPos   = ring_map_dat[i].yPos - player.mapY + pRing->vy;
			pOam->Priority = 0x00;
			pOam++;

			// left to ring
			*pOam = *(OamData *)Oam_32x64dot;
			pOam->CharNo = RING_L_CHAR_NO;
			pOam->HPos   = ring_map_dat[i].xPos - player.mapX + pRing->vx;
			pOam->VPos   = ring_map_dat[i].yPos - player.mapY + pRing->vy;
			pOam->Priority = 0x02;
			pOam++;

		}else{
			*pOam = *(OamData *)Oam_def;
			pOam++;
			*pOam = *(OamData *)Oam_def;
			pOam++;
		}
	}
}


//------------------------------------------------------------------//
//			Normal Status of Ring                       //
//------------------------------------------------------------------//

void RingNormal(Ring *pRing, u8 i)
{
	s16 cnt;

	pRing->counter += 4;
	cnt = pRing->counter & 0xff;
	pRing->vx = 0;
	pRing->vy = cos_tbl[cnt]/32;
}


//------------------------------------------------------------------//
//		Status Dolphin Passes Ring                          //
//------------------------------------------------------------------//

void RingPassed(Ring *pRing, u8 i)
{
	s16 cnt;

	pRing->pass_counter += 16;
	// return to normal status
	if (pRing->pass_counter >= 768){
		pRing->state = RING_NORMAL_STATE;
		pRing->pass_counter = 0;
	}

	cnt = pRing->pass_counter & 0xff;
	pRing->vx = 0;//sin_tbl[cnt]/32;
	pRing->vy = cos_tbl[cnt]/32;
}


//------------------------------------------------------------------//
//			Status Dolphin Hits Ring                    //
//------------------------------------------------------------------//

void RingHit(Ring *pRing, u8 i)
{

}
