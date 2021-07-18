/********************************************************************/
/*          player.c                                                */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>

#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ring.h"
#include "bg.h"

//---------------------- OAM data -----------------------------//

typedef struct {
    u16 default_oam0;	//  default of OAM attribute 0
    u16 default_oam1;	//  default of OAM attribute 1
    u16 default_oam2;	//  default of OAM attribute 2
}oam_def;


//------------------------------------------------------------------//
//		External Reference Declaration                      //
//------------------------------------------------------------------//

extern u32 Oam_8x8dot[1][2];
extern u16 r_kihon1_Palette[256];
extern sin_tbl[];
extern cos_tbl[];
extern ObjBuf Oam;
extern u32	Oam_def[1][2];
extern Ring ring[RING_MAX_NUM];

extern u8 *r_kihon_pixel_tbl[];
extern u8 *r_attack_pixel_tbl[];
extern u8 *r_down_pixel_tbl[];
extern u8 *r_up_down_pixel_tbl[];
extern u8 *r_jump_pixel_tbl[];
extern AnmTable rick_kihon_fast_pat[];
extern AnmTable rick_attack_pat[];
extern AnmTable rick_jump_pat[];

extern AnmTable2 rick_kihon_idle_pat[];
extern AnmTable2 rick_normal_move_pat[];
extern u32 Oam_32x32dot[1][2];
extern u32 OamData_Sample[1][2];

//------------------------------------------------------------------//
//			Global Variable                             //
//------------------------------------------------------------------//

Player player;
Player_Awa player_awa[PLAYER_AWA_MAX_NUM];

//------------------------------------------------------------------//
//			Initialize Dolphin                          //
//------------------------------------------------------------------//

void InitPlayer()
{
	OamData* pOam;

	player.mapX = 0; player.mapY = 0;

	player.x = 0;   player.y = 96;
	player.dx = 0;  player.dy = 0;
	player.vx = 0;  player.vy = 0;	// speed
	player.ax = 0;  player.ay = 0;	// acceleration
	player.char_no = 0;
	player.counter = 0;

	player.anim_type = R_KIHON_ANM;
	player.anim_interval = 0;
	player.anim_counter  = 0;
	player.up_down_anm_pat = 15;

	player.enemy_hit = 0;
	player.timer = 0;
	player.state = MOVE;
	player.dir = RIGHT;
	player.auto_flg = OFF;
	player.pAnmtbl2 = rick_normal_move_pat;
	player.blinkflg = OFF;
	player.water_speed = WATER_SPEED_SLOW;
	player.water_counter = 0;

	// OBJ character set
	DmaArrayCopy(3, r_kihon1_Char,    DOLPHIN_VRAM_POS, 16);
	// OBJ palette set
	DmaArrayCopy(3, r_kihon1_Palette, OBJ_PLTT, 16);

	// initialize animation
	InitPlayerAnim();
}


//------------------------------------------------------------------//
//			Main Routine of Dolphin                     //
//------------------------------------------------------------------//

void PlayerProc()
{
	player.water_counter++;

	// action control
	PlayerActionControl();
	// execute current action
	(*pPlayer_action_tbl[player.state])();

	// control dolphin animation
	PlayerAnim();

	// move range limit
	RestrictPlayerPosition(&player);

	// change water speed
	ChangeWaterSpeed();
	// adjust light reflection
	Ajust_Light_Reflection(&player);

	// collision detection of ring and dolphin
	//Ring2Dolphin(ring, &player);

	// draw dolphin
	DrawPlayer();

	player.oldx = player.mapX;
	player.oldy = player.mapY;
}


//------------------------------------------------------------------//
//			Display Player                              //
//------------------------------------------------------------------//
void DrawPlayer()
{
	OamData* pOam;
	#define LIMIT 8
//	if (player.mapY > LIMIT + 32) {
	if (player.mapY > LIMIT) {
		// use OBJ window and normal OBJ
		pOam = &Oam.Objbuf[0];

		*pOam = *(OamData *)OamData_Sample;
		pOam->CharNo = player.char_no;
		pOam->HPos   = player.x;
		pOam->VPos   = player.y;

		pOam->VFlip  = OFF;
		if (player.dir == RIGHT)
			pOam->HFlip  = ON;
		else
			pOam->HFlip  = OFF;

		pOam->Priority = 0x01;
		pOam->ObjMode = 2;		// OBJ window

		pOam = &Oam.Objbuf[1];

		*pOam = Oam.Objbuf[0];
		pOam->Priority = 0x02;
		pOam->ObjMode = 0;		// normal OBJ
		*(vu16 *)REG_BLDCNT = BLD_BG0_2ND | BLD_OBJ_1ST | BLD_A_BLEND_MODE;
		// use OBJ window and window function
		*(vu16 *)REG_WINOUT = (WIN_OBJ_ON << 8) | (WIN_BG0_ON << 8)
							| (WIN_BLEND_ON << 8) | WIN_OBJ_ON | WIN_BG1_ON | WIN_BG2_ON;

	} else if (player.mapY <= LIMIT) {
		pOam = &Oam.Objbuf[0];

		*pOam = *(OamData *)OamData_Sample;
		pOam->CharNo = player.char_no;
		pOam->HPos   = player.x;
		pOam->VPos   = player.y;

		pOam->VFlip  = OFF;
		if (player.dir == RIGHT)
			pOam->HFlip  = ON;
		else
			pOam->HFlip  = OFF;

		pOam->Priority = 0x02;
		pOam->ObjMode = 0;		// normal OBJ

		pOam = &Oam.Objbuf[1];

		*pOam = Oam.Objbuf[0];
		pOam->Priority = 0x03;
		pOam->ObjMode = 0;		// normal OBJ
		*(vu16 *)REG_BLDCNT = BLD_BG2_1ST | BLD_OBJ_2ND | BLD_A_BLEND_MODE;
//		*(vu16 *)REG_WINOUT = (WIN_OBJ_ON << 8) | (WIN_BLEND_ON << 8)
//							| WIN_OBJ_ON | WIN_BG1_ON | WIN_BG2_ON;
		*(vu16 *)REG_WINOUT = (WIN_OBJ_ON << 8) | (WIN_BG0_ON << 8) 
				| WIN_OBJ_ON | WIN_BG1_ON | WIN_BG2_ON | WIN_BLEND_ON;
	}
}


//------------------------------------------------------------------//
//		Control Display Area of Dolphin                     //
//------------------------------------------------------------------//

void RestrictPlayerPosition(Player* pPlayer)
{
	if (pPlayer->state != JUMP){
		// map limit
		if (pPlayer->mapX < 0){
			pPlayer->mapX = 0;
			// bounce
			pPlayer->vx = -(pPlayer->vx);
		}
		if (pPlayer->mapX > MAP_WIDTH){
			pPlayer->mapX = MAP_WIDTH;
			// bounce
			pPlayer->vx = -(pPlayer->vx);
		}
		if (pPlayer->mapY > MAP_HEIGHT)	{
			pPlayer->mapY = MAP_HEIGHT;
		}
		if (pPlayer->mapY < 0){
			pPlayer->mapY = 0;
		}

		if (pPlayer->mapX > 80 && pPlayer->mapX < MAP_WIDTH - 80) {
			// check X coordinate range on the screen
			if (pPlayer->dir == RIGHT) {
				if (pPlayer->x > 90){
					pPlayer->x = 90;
				}
				if (pPlayer->x < 70){
					pPlayer->x = 70;
				}
			}
			if (pPlayer->dir == LEFT) {
				if (pPlayer->x > 110){
					pPlayer->x = 110;
				}
				if (pPlayer->x < 90){
					pPlayer->x = 90;
				}
			}
		}
		if (pPlayer->mapX > MAP_WIDTH - 80) {
			if (pPlayer->x > 256 - 80){
				pPlayer->x = 256 - 80;
			}
		}
		if (pPlayer->mapX < 80) {
			if (pPlayer->x < 0){
				pPlayer->x = 0;
			}
		}

#define Y_TOP_LIMIT 64
		// check LCD Y coordinate range
		pPlayer->y = Y_TOP_LIMIT;
	}
}


//------------------------------------------------------------------//
//			Control Dolphin Action                      //
//------------------------------------------------------------------//

void PlayerActionControl()
{
	if (Trg & A_BUTTON && player.state != ACTION1)	{
	}
	// jump
	if (Trg & B_BUTTON && player.state != JUMP)	{
		if (player.mapY >= 0 && player.mapY < 64 && 
			player.mapX >= 64) {
			player.counter = 0;
			player.state = JUMP;
			player.anim_type = R_JUMP_ANM;
			player.anim_pat = 0;
			player.anim_interval = 8;
			player.pAnmtbl = rick_jump_pat;
		}
	}else{
	}

	if (Trg & R_BUTTON && player.state != ACTION3)	{
	}

	// change direction
	if (player.state != JUMP)	{
		Chang_Dir(&player);
	}
}


//------------------------------------------------------------------//
//			Change Direction of Dolphin                 //
//------------------------------------------------------------------//

void Chang_Dir(Player* pPlayer)
{
	if (Trg & L_KEY)	{
		// change direction (left --> right)
		if (pPlayer->dir != LEFT){
			pPlayer->dir = LEFT;

			pPlayer->anim_pat = 0;
			pPlayer->anim_interval = 6;
			pPlayer->anim_type = R_ATTACK_ANM;
			pPlayer->pAnmtbl = &rick_attack_pat[0];
			pPlayer->state = ACTION1;
		}
	}else if (Trg & R_KEY)	{
		// change direction (right --> left)
		if (pPlayer->dir != RIGHT){
			pPlayer->dir = RIGHT;
			pPlayer->anim_pat = 0;
			pPlayer->anim_interval = 6;
			pPlayer->anim_type = R_ATTACK_ANM;
			pPlayer->pAnmtbl = &rick_attack_pat[0];
			pPlayer->state = ACTION1;
		}
	}
}


//------------------------------------------------------------------//
//			Normal Move of Dolphin                      //
//------------------------------------------------------------------//

#define BRAKE_X 0x02
#define BRAKE_Y 0x06

void MovePlayer()
{
	// Up
	if (Cont & U_KEY){
		player.vy -= ACCEL_Y;
		if (player.vy < -SPEED_MAX_Y)
			player.vy = -SPEED_MAX_Y;
		player.anim_type = R_UP_DOWN_ANM;
		player.anim_interval = ANIM_TIME_MIDDLE;
	}
	// Down
	if (Cont & D_KEY){
		player.vy += ACCEL_Y;
		if (player.vy > SPEED_MAX_Y)
			player.vy = SPEED_MAX_Y;
		player.anim_type = R_UP_DOWN_ANM;
		player.anim_interval = ANIM_TIME_MIDDLE;
	}
	// Left
	if (Cont & L_KEY){
		player.dir = LEFT;
		player.vx -= ACCEL_X;
		if (player.vx < -SPEED_MAX_X)
			player.vx = -SPEED_MAX_X;
		if (player.anim_type == R_KIHON_ANM)
			player.anim_interval = ANIM_FAST;
	}
	// Right
	if (Cont & R_KEY)	{
		player.dir = RIGHT;
		player.vx += ACCEL_X;
		if (player.vx > SPEED_MAX_X)
			player.vx = SPEED_MAX_X;
		if (player.anim_type == R_KIHON_ANM)
			player.anim_interval = ANIM_FAST;
	}

	// No key down
	if ( (Cont & PLUS_KEY_MASK) == 0 )	{
		player.anim_interval = ANIM_NORMAL;

		if (player.vx > 0x00)
			player.vx -= BRAKE_X;
		if (player.vx < 0x00)
			player.vx += BRAKE_X;

		if (player.vy > 0x00)
			player.vy -= BRAKE_Y;
		if (player.vy < 0x00)
			player.vy += BRAKE_Y;
	}

	// update coordinate
	player.x += Dec2Int(player.vx);
	player.y += Dec2Int(player.vy);
	player.mapX += Dec2Int(player.vx);
	player.mapY += Dec2Int(player.vy);
}


void ChangeWaterSpeed()
{
	// change water speed
	if (player.vx > -0x100 & player.vx < 0x000){
		player.water_speed = WATER_SPEED_SLOW;
	}
	if (player.vx > -0x200 & player.vx < -0x100){
		player.water_speed = WATER_SPEED_NORM;
	}
	if (player.vx > -0x300 & player.vx < -0x200){
		player.water_speed = WATER_SPEED_FAST;
	}

	if (player.vx > 0x000 & player.vx < 0x100){
		player.water_speed = WATER_SPEED_SLOW;
	}
	if (player.vx > 0x100 & player.vx < 0x200){
		player.water_speed = WATER_SPEED_NORM;
	}
	if (player.vx > 0x200 & player.vx < 0x300){
		player.water_speed = WATER_SPEED_FAST;
	}
}

//------------------------------------------------------------------//
//			Dolphin Action 1                            //
//------------------------------------------------------------------//

void Action1()
{
	// Up
	if (Cont & U_KEY)	{
		player.vy -= ACCEL_Y;
		if (player.vy < -SPEED_MAX_Y)
			player.vy = -SPEED_MAX_Y;
	}
	// Down
	if (Cont & D_KEY)	{
		player.vy += ACCEL_Y;
		if (player.vy > SPEED_MAX_Y)
			player.vy = SPEED_MAX_Y;
	}
	// Left
	if (Cont & L_KEY)	{
		player.dir = LEFT;
		player.vx -= ACCEL_X;
		if (player.vx < -SPEED_MAX_X)
			player.vx = -SPEED_MAX_X;
	}
	// Right
	if (Cont & R_KEY)	{
		player.dir = RIGHT;
		player.vx += ACCEL_X;
		if (player.vx > SPEED_MAX_X)
			player.vx = SPEED_MAX_X;
	}

	// update coordinate
	player.x += Dec2Int(player.vx);
	player.y += Dec2Int(player.vy);
	player.mapX += Dec2Int(player.vx);
	player.mapY += Dec2Int(player.vy);
}


//------------------------------------------------------------------//
//			Dolphin Jump                                //
//------------------------------------------------------------------//

void JumpPlayer()
{
	s16 cnt, div;
	s16 vy;

	player.counter+=2;
	// end jump
	if (player.counter > 128)	{
		player.counter = 0;
		player.state = MOVE;
		return;
	}

	player.y -= 2*sin_tbl[player.counter]/128;

	if (Cont & L_KEY)	{
		if(player.dir == LEFT){
			player.vx -= ACCEL_X;
			if (player.vx < -SPEED_MAX_X)
				player.vx = -SPEED_MAX_X;
		}
	}
	if (Cont & R_KEY)	{
		if(player.dir == RIGHT){
			player.vx += ACCEL_X;
			if (player.vx > SPEED_MAX_X)
				player.vx = SPEED_MAX_X;
		}
	}
	player.mapX += Dec2Int(player.vx);
}


//------------------------------------------------------------------//
//			Dolphin Action 3                            //
//------------------------------------------------------------------//

void Action3()
{

}


//------------------------------------------------------------------//
//			Initialize Dolphin Animation                //
//------------------------------------------------------------------//

void InitPlayerAnim()
{
	player.anim_pat = 0;
	player.anim_counter = 0;
	player.anim_interval = ANIM_NORMAL;
}


//------------------------------------------------------------------//
//			Animation Main Processing                   //
//------------------------------------------------------------------//

void PlayerAnim()
{
	(*pRick_anm_tbl[player.anim_type])();
}


//------------------------------------------------------------------//
//			Basic Animation of Dolphin                  //
//------------------------------------------------------------------//

void Player_kihon_anm()
{
	if (++player.anim_counter > player.pAnmtbl2->delay)
	{
		player.anim_counter = 0;
		player.pAnmtbl2++;
		if (player.pAnmtbl2->delay == -1) {
			player.pAnmtbl2 = &rick_normal_move_pat[0];
		}
	}
	DmaCopy(3, player.pAnmtbl2->img,
			OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16);
}


//------------------------------------------------------------------//
//		Operation Stanby Animation of Dolphin               //
//------------------------------------------------------------------//
void Player_kihon_idle_anm()
{
	if (++player.anim_counter > player.pAnmtbl2->delay)
	{
		player.anim_counter = 0;
		player.pAnmtbl2++;
		if (player.pAnmtbl2->delay == -1) {
			player.pAnmtbl2 = &rick_kihon_idle_pat[0];
		}
	}
	DmaCopy(3, player.pAnmtbl2->img,
			OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16);
}

//------------------------------------------------------------------//
//		Going Up/Down Animation of Dolphin                  //
//------------------------------------------------------------------//

void Player_updown_anm()
{
	player.anim_interval = 2;

	if ((Cont & U_KEY))	{
		if (++player.anim_counter > player.anim_interval) {
			player.anim_counter = 0;
			if (--player.up_down_anm_pat < 4)	{
				player.up_down_anm_pat = 11;
			}
		}
	}else if (Cont & D_KEY)	{
		if (++player.anim_counter > player.anim_interval) {
			player.anim_counter = 0;
			if (++player.up_down_anm_pat > 23)	{
				player.up_down_anm_pat = 19;
			}
		}
	}else {
		// processing to return to horizontal
		if (++player.anim_counter > player.anim_interval) {
			player.anim_counter = 0;
			if (player.up_down_anm_pat > 15)	{
				player.up_down_anm_pat--;
			}else if (player.up_down_anm_pat < 15)	{
				player.up_down_anm_pat++;
			}
		}
		// return to basic animation
		if (player.up_down_anm_pat == 15)	{
			player.anim_type = R_KIHON_ANM;
		}
	}

	DmaCopy(3, r_up_down_pixel_tbl[player.up_down_anm_pat], OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16)
}


//------------------------------------------------------------------//
//			Jump Animation of Dolphin                   //
//------------------------------------------------------------------//

void Player_jump_anm()
{
	if (++player.anim_counter > player.pAnmtbl->delay)
	{
		player.anim_counter = 0;
		player.pAnmtbl++;

		// return to basic animation 
		if (player.pAnmtbl->anm_ptn > RICK_JUMP_ANM_NUM - 1) {
			player.anim_type = R_KIHON_ANM;
			player.anim_interval = ANIM_NORMAL;
			player.state = MOVE;
		}
	}
	DmaCopy(3, r_jump_pixel_tbl[player.pAnmtbl->anm_ptn], 
				OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16)
}


//------------------------------------------------------------------//
//			Idling Animation of Dolphin                 //
//------------------------------------------------------------------//

void Player_idle_anm()
{
	if (++player.anim_counter > player.anim_interval)
	{
		player.anim_counter = 0;
		player.anim_pat++;
		if (player.anim_pat > 8) {
			player.anim_type = R_KIHON_ANM;
			player.anim_pat = 0;
			player.anim_interval = ANIM_NORMAL;
		}
	}
	DmaCopy(3, r_down_pixel_tbl[player.anim_pat],
		OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16)
}


//------------------------------------------------------------------//
//		Attacking Animation of Dolphin                      //
//------------------------------------------------------------------//

void Player_attack_anm()
{
	if (++player.anim_counter > player.pAnmtbl->delay)
	{
		player.anim_counter = 0;
		player.pAnmtbl++;

		// return to basic animation
		if (player.pAnmtbl->anm_ptn > RICK_ATTACK_ANM_NUM - 1) {
			player.anim_type = R_KIHON_ANM;
			player.anim_interval = ANIM_NORMAL;
			player.state = MOVE;
			player.pAnmtbl2 = &rick_normal_move_pat[0];
		}
	}
	DmaCopy(3, r_attack_pixel_tbl[player.pAnmtbl->anm_ptn],
		OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16)
}



void Player_move_rl_anm()
{

}


//------------------------------------------------------------------//
//			Butting Animation                           //
//------------------------------------------------------------------//

void Player_head_attack_anm()
{
	player.anim_pat--;
	if (player.anim_pat < 0) {
		player.anim_type = R_KIHON_ANM;
		player.anim_pat = 0;
		player.anim_interval = ANIM_NORMAL;
	}
	DmaCopy(3, r_up_down_pixel_tbl[player.anim_pat], 
		OBJ_MODE0_VRAM, sizeof(r_kihon1_Char), 16)
}


//------------------------------------------------------------------//
//			Adjust Amount of Light Reflection           //
//------------------------------------------------------------------//

void Ajust_Light_Reflection(Player* pPlayer)
{
	int dolval = pPlayer->mapY / 70;
	int seaval = pPlayer->mapY / 70;

	// no reflection during jump
	if (player.anim_type == R_JUMP_ANM){
		if (player.pAnmtbl->anm_ptn > 4 && player.pAnmtbl->anm_ptn < 10) {
			*(vu16 *)REG_BLDALPHA = (0x0f);
			return;
		}
	// if on sea surface
	} else if (player.mapY < 16) {
		*(vu16 *)REG_BLDALPHA = (0x0f) | (0x07) << 8;
		return;
	}
	*(vu16 *)REG_BLDALPHA = (0x0f) | ((0x0f-0x04) - seaval) << 8;
}


//------------------------------------------------------------------//
//			Player Blink                                //
//------------------------------------------------------------------//

void BlinkPlayer(Player* pPlayer)
{
}


//------------------------------------------------------------------//
//			Initialize Bubbles                          //
//------------------------------------------------------------------//

void InitPlayer_Awa()
{
	u8 i;
	Player_Awa *pAwa;
	
	pAwa = player_awa;

	for (i = 0; i < PLAYER_AWA_MAX_NUM; i++)	{
		pAwa->flg = 0;
		pAwa->x = 0;
		pAwa->y = 0;;
		pAwa->oldx = 0;
		pAwa->oldy = 0;;
		pAwa++;
	}
}


//------------------------------------------------------------------//
//			Bubble Main                                 //
//------------------------------------------------------------------//

void Player_AwaProc()
{
	int i;
	Player_Awa *pAwa;

	pAwa = player_awa;

	for(i = 0; i < PLAYER_AWA_MAX_NUM; i++, pAwa++) {
//		if (pAwa->flg != 0)
			Player_AwaMove(pAwa, &player);
	}

	// draw bubble
	DrawPlayer_Awa(&Oam.Objbuf[PLAYER_AWA_OAM_POS], player_awa);

}

//------------------------------------------------------------------//
//			Create Bubbles                              //
//------------------------------------------------------------------//

void CreatePlayer_Awa(Player_Awa *pAwa, Player *pPlayer)
{
	u8 i;

	for(i = 0; i < PLAYER_AWA_MAX_NUM; i++, pAwa++) {
		if (pAwa->flg == 0)	{
			if (pPlayer->dir == RIGHT)
				pAwa->x = pPlayer->x;
			else
				pAwa->x = pPlayer->x+64;
			pAwa->y = pPlayer->y+24;
			pAwa->timer = 0;
			pAwa->flg = 1;
			break;
		}
	}
}

//------------------------------------------------------------------//
//			Move Bubbles                                //
//------------------------------------------------------------------//

void Player_AwaMove(Player_Awa *pAwa, Player *pPlayer)
{
	s16 cnt, amp, div;
	s32 newx, newy;
	s32 dx, dy;

	newx = pPlayer->mapX;
	newy = pPlayer->mapY;

	dx = newx - pAwa->oldx;
	dy = newy - pAwa->oldy;

	pAwa->counter += 1;
	div = 128;

	cnt = pAwa->counter & 0xff;

	if(pAwa->flg != 0){
		pAwa->x -= dx - sin_tbl[cnt]/div;
		pAwa->y -= dy;
	}else{
		pAwa->x -= dx;
		pAwa->y -= dy;
	}

	pAwa->oldx = newx;
	pAwa->oldy = newy;
}


//------------------------------------------------------------------//
//			Draw Bubbles                                //
//------------------------------------------------------------------//

void DrawPlayer_Awa(OamData* pOam, Player_Awa *pAwa)
{
	int i;

	for(i = 0; i < PLAYER_AWA_MAX_NUM; i++, pAwa++, pOam++) {
		if(pAwa->flg != 0)	{			// alive
			if (++pAwa->timer > 64)
				pAwa->flg = 0;
			*pOam = *(OamData *)Oam_8x8dot;
			pOam->CharNo = AWA_CHAR_NO;
			pOam->HPos   = pAwa->x;
			pOam->VPos   = pAwa->y;
			pOam->Priority    = 0x00;
		} else {
			*pOam = *(OamData *)Oam_def;
		}
	}
}

