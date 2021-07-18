/********************************************************************/
/*          hitcheck.c                                              */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ring.h"
#include "hitcheck.h"


//------------------------------------------------------------------//
//		External Reference Declaration			    //
//------------------------------------------------------------------//

extern Player player;

extern Enemy   dEnemy[ENEMY_NUM_MAX];
extern Fukiya fukiya[FUKIYA_NUM_MAX];
extern RingMapData ring_map_dat[];

//------------------------------------------------------------------//
//			Global Variable				    //
//------------------------------------------------------------------//


//------------------------------------------------------------------//
//		Collision Detection of Blowgun and Dolphin 	    //
//------------------------------------------------------------------//

void Fukiya2Dolphin(Player *pPlayer, Fukiya *pFukiya)
{
	int i, j;

	for (i = 0; i < FUKIYA_NUM_MAX; i++, pFukiya++)	{	// loop the number of blowguns 
		if (pFukiya->flg == 1) {						// only when blowgun existed
			if ((pFukiya->x - player.mapX) - pPlayer->x > -16 &&	// blowgun is on left of dolphin 
				(pFukiya->x - player.mapX) - pPlayer->x <  56 &&	// blowgun is on right of dolphin 
				(pFukiya->y - player.mapY) - pPlayer->y >  16 &&	// blowgun is above dolphin 
				(pFukiya->y - player.mapY) - pPlayer->y <  38) 		// blowgun is under dolphin 
			{
				pFukiya->flg = 0;	// erase shots  
				pPlayer->hit = 1;	// got hit    
				break;
			}
		}
	}
}


//------------------------------------------------------------------//
//		Collision Detection of Dolphin and Enemy  	    //
//------------------------------------------------------------------//

void Dolphin2Enemy(Player *pPlayer, Enemy *pTeki)
{
	int i, j;

	for (i = 0; i < ENEMY_NUM_MAX; i++, pTeki++)	{	// loop the number of enemies  
		if (pTeki->alive != DEAD) {				// only when enemy existed 
			if (pPlayer->dir == LEFT) {
				if ((pTeki->x - pPlayer->mapX) - pPlayer->x >= -24 &&	// enemy is on left of dolphin
					(pTeki->x - pPlayer->mapX) - pPlayer->x <=  50 &&	// enemy is on right of dolphin 
					(pTeki->y - pPlayer->mapY) - pPlayer->y >=  -4 &&	// enemy is above dolphin 
					(pTeki->y - pPlayer->mapY) - pPlayer->y <=  40)		// enemy is under dolphin
				{
					pTeki->hit = ON;
					pTeki->blinkflg = ON;
					pPlayer->enemy_hit = ON;
					break;
				}
			}
			if (pPlayer->dir == RIGHT) {
				if ((pTeki->x - pPlayer->mapX) - pPlayer->x >= -24 &&	// enemy is on left of dolphin
					(pTeki->x - pPlayer->mapX) - pPlayer->x <=  50 &&	// enemy is on right of dolphin
					(pTeki->y - pPlayer->mapY) - pPlayer->y >=  -4 &&	// enemy is above dolphin
					(pTeki->y - pPlayer->mapY) - pPlayer->y <=  40)		// enemy is under dolphin
				{
					pTeki->hit = ON;
					pTeki->blinkflg = ON;
					pPlayer->enemy_hit = ON;
					break;
				}
			}
		}
	}
}


//------------------------------------------------------------------//
//		Collision Detection of Ring and Dolphin  	    //
//------------------------------------------------------------------//

void Ring2Dolphin(Ring *pRing, Player *pPlayer)
{
	int i, j;
	s32 ring_x, ring_y;

	for (i = 0; i < RING_MAX_NUM; i++, pRing++)	{	// loop the number of rings  
		if (pRing->flg == 1) {					// only when ring existed  
			ring_x = ring_map_dat[i].xPos - player.mapX;
			ring_y = ring_map_dat[i].yPos - player.mapY;

			// dolphin is above ring  
			if (((pPlayer->y + 24 - ring_x) >= 0) && // upper part of dolphin and upper half of ring 
				((pPlayer->y + 24 - ring_y) <= 16)&& 	// upper part of dolphin and upper half of ring
				(ring_x - pPlayer->x >= -8) &&       	// dolphin is on right of ring 
				(ring_x - pPlayer->x <= 56) )        	// dolphin is on left of ring 

			{
				player.vx = -player.vx/2;
				player.vy = -player.vy/2;
				break;
			}

			// dolphin is under ring 
			if (((pPlayer->y + 16) - (ring_map_dat[i].yPos - player.mapY) > 56) &&
				((pPlayer->y + 16) - (ring_map_dat[i].yPos - player.mapY) < 64) &&
				((ring_map_dat[i].xPos - player.mapX) - pPlayer->x > 8) &&
				((ring_map_dat[i].xPos - player.mapX) - pPlayer->x < 56) )

			{
				player.vx = -player.vx/2;
				player.vy = -player.vy/2;
				break;
			}
			// dolphin is on upper end of inside ring 
			if (((pPlayer->y + 16) - (ring_map_dat[i].yPos - player.mapY) > 0) &&
				((pPlayer->y + 16) - (ring_map_dat[i].yPos - player.mapY) < 16) &&
				((ring_map_dat[i].xPos - player.mapX) - pPlayer->x > 8) &&
				((ring_map_dat[i].xPos - player.mapX) - pPlayer->x < 56) )

			{
				pPlayer->hit = HIT_RING_MIDDLE_DOWN;
				break;
			}
			// dolphin is on lower end of inside ring 
			if (((pPlayer->y + 32) - (ring_map_dat[i].yPos - player.mapY) > 48) && // 48
				((pPlayer->y + 32) - (ring_map_dat[i].yPos - player.mapY) < 56) && // 56
				((ring_map_dat[i].xPos - player.mapX) - pPlayer->x > 8) &&
				((ring_map_dat[i].xPos - player.mapX) - pPlayer->x < 56) )
			{
				player.vx = -player.vx;
				player.vy = -player.vy;
				break;
			}
		}
	}
}


//------------------------------------------------------------------//
//		Check if Dolphin Passed Through Ring  		    //
//------------------------------------------------------------------//

u8 RingPass(Ring *pRing, Player *pPlayer)
{
	int i, j;
	s32 ring_x, ring_y;
	for (i = 0; i < RING_MAX_NUM; i++, pRing++)	// loop the number of rings 
	{
		if (pRing->flg == 1)			// only when ring existed 
		{
			ring_x = ring_map_dat[i].xPos - player.mapX;
			ring_y = ring_map_dat[i].yPos - player.mapY;
			// if dolphin is facing to the right 
			if (pPlayer->dir == RIGHT)
			{
				if (((pPlayer->y + 24 - ring_y) >= 16) && // upper part of dolphin and upper half of ring  
					((pPlayer->y + 40 - ring_y) <= 48) && // lower part of dolphin and lower half of ring  
					(ring_x - pPlayer->x >= -8) && // dolphin is on right of ring  
					(ring_x - pPlayer->x <= 56) ) // dolphin is on left of ring 
				{
					pRing->pass_flg = 1;
					pRing->state = RING_PASS_STATE;
					pRing->counter = 0;
					return 1;
				}
			}
			// if dolphin is facing to the left 
			if (pPlayer->dir == LEFT) {
				if (((pPlayer->y + 24 - ring_y) >= 16) && // upper part of dolphin and upper half of ring   
					((pPlayer->y + 40 - ring_y) <= 48) && // lower part of dolphin and lower half of ring  
					(ring_x - pPlayer->x >= -8) && // dolphin is on right of ring 
					(ring_x - pPlayer->x <= 56) ) // dolphin is on left of ring  
				{
					pRing->pass_flg = 1;
					pRing->state = RING_PASS_STATE;
					pRing->counter = 0;
					return 1;
				}
			}
		}
	}
	return 0;
}

