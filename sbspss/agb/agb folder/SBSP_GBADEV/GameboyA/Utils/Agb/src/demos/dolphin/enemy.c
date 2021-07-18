/********************************************************************/
/*          enemy.c                                                 */
/*                 Source of Dolphin                                  */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "enemy.h"

//------------------------------------------------------------------//
//						External Reference Declaration								//
//------------------------------------------------------------------//
extern u8 *shell_base_pix_tbl[];
extern Anmpat shell_base_anm_pat[];
extern u8 *shell_attack_pix_tbl[];
extern Anmpat shell_attack_anm_pat[];
extern u8 *shell_yarare_pix_tbl[];
extern Anmpat shell_yarare_anm_pat[];
extern CharMapData shell_map_dat[];

extern ObjBuf Oam;
extern u16		Cont, Trg;
extern Player player;
extern AnmTable rick_attack_pat[];

extern short sin_tbl[];
extern short cos_tbl[];

// For 16 x 8 dot
extern u32 Oam_16x8dot[1][2];

//------------------------------------------------------------------//
//						Global Variables								//
//------------------------------------------------------------------//

Enemy   dEnemy[ENEMY_NUM_MAX];
Awa    awa[AWA_NUM_MAX];
Fukiya fukiya[FUKIYA_NUM_MAX];

const	u32	Oam_def[1][2] = {
	{ OAM_OBJ_OFF, 0},
};


// For 32 x 32 dot
const	u32	Oam_32x32dot[1][2] = {
	{ OAM_COLOR_256 | OAM_SQUARE | OAM_SIZE_32x32
	, 0},
};

// For 16 x 16 dot
const	u32	Oam_16x16dot[1][2] = {
	{ OAM_COLOR_256 | OAM_SQUARE | OAM_SIZE_16x16
	, 0},
};


// For 8 x 8 dot
const	u32	Oam_8x8dot[1][2] = {
	{ OAM_COLOR_256 | OAM_SQUARE | OAM_SIZE_8x8
	, 0},
};


u8 anm_state[] = {
	SHELL_BASE, SHELL_ATTACK, SHELL_BASE, SHELL_ATTACK, 
	SHELL_BASE, SHELL_ATTACK, SHELL_BASE, SHELL_ATTACK, 
	SHELL_BASE, SHELL_ATTACK, SHELL_BASE, SHELL_ATTACK, 
};

//------------------------------------------------------------------//
//						Initialize Enemy         							//
//------------------------------------------------------------------//

void InitEnemy()
{
	int i;
	Enemy *pEnemy;
	CharMapData* pInfoTbl;

	pEnemy = dEnemy;
	pInfoTbl = shell_map_dat;

	// Initialize Enemy
	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++, pInfoTbl++) {
		pEnemy->alive = ALIVE;			// Alive
		pEnemy->screen = SCREEN_OUT;

		pEnemy->counter = 0;
		pEnemy->state = SHELL_NORMAL_STATE;
		pEnemy->strength = 10;
		pEnemy->x = pInfoTbl->xPos;
		pEnemy->y = pInfoTbl->yPos;

		pEnemy->vx = 1;
		pEnemy->vy = 0;
		pEnemy->dir = LEFT;

		pEnemy->char_no = pInfoTbl->char_no;
		pEnemy->dst_adr = pInfoTbl->VRAM_ADDR;

		pEnemy->anim_pat = 2;		// Animation Pattern
		pEnemy->anim_interval = 12;	// Animation Interval
		pEnemy->anim_counter = 0;	// Counter
		pEnemy->anim_state = anm_state[i];
		pEnemy->blinkcounter = 0;
		pEnemy->timer = 50 * i;
		pEnemy->hit = OFF;
		pEnemy->drawflg = ON;
		DmaCopy(3, shell_base_pix_tbl[pEnemy->anim_pat],
				pEnemy->dst_adr, sizeof(o_kihon001_Char), 16)
	}
}


//------------------------------------------------------------------//
//						Main Routine of Enemy							//
//------------------------------------------------------------------//

void EnemyProc()
{
	int i;
	OamData* pOam;
	Enemy* pEnemy;

	// Control Move Routine of Enemy
	ControlEnemyMove(dEnemy);

	// Animation Process of Nautilus
	ShellAnim(dEnemy);

	// Collision Check
	HitCheck_Enemy(dEnemy);

	// Check if enemy is in the screen
	LcdCheckEnemy(dEnemy, &player);

	// Drawing Enemy 
	pOam = &Oam.Objbuf[ENEMY_OAM_POS];
	pEnemy = dEnemy;
	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++, pOam++) {
		if (pEnemy->drawflg == ON){
			DrawEnemy(pOam, pEnemy);
		}else if (pEnemy->drawflg == OFF){
			EraseEnemy(pOam, pEnemy);
		}
	}
}


//------------------------------------------------------------------//
//						Create Enemy										//
//------------------------------------------------------------------//

void CreateTeki(Enemy *pEnemy, CharMapData* pInfoTbl)
{
	u8 i;

	// Create Enemy
	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++, pInfoTbl++) {
		pEnemy->alive = ALIVE;			// Alive
		pEnemy->screen = SCREEN_OUT;

		pEnemy->counter = 0;
		pEnemy->state = SHELL_NORMAL_STATE;
		pEnemy->strength = 10;
		pEnemy->x = pInfoTbl->xPos;
		pEnemy->y = pInfoTbl->yPos;

		pEnemy->vx = 1;
		pEnemy->vy = 0;
		pEnemy->dir = LEFT;

		pEnemy->char_no = pInfoTbl->char_no;
		pEnemy->dst_adr = pInfoTbl->VRAM_ADDR;

		pEnemy->anim_pat = 2;		// Animation Pattern
		pEnemy->anim_interval = 12;	// Animation Interval
		pEnemy->anim_counter = 0;	// Counter
		pEnemy->anim_state = anm_state[i];

		pEnemy->timer = 50 * i;
		pEnemy->hit = OFF;
		DmaCopy(3, shell_base_pix_tbl[pEnemy->anim_pat],
				pEnemy->dst_adr, sizeof(o_kihon001_Char), 16)
	}
}


//------------------------------------------------------------------//
//			Collision Check 				                                           //
//------------------------------------------------------------------//

void HitCheck_Enemy(Enemy* pEnemy)
{
	u8 i;

	// Check if Dolphin and Enemy collided with each other
	Dolphin2Enemy(&player, dEnemy);

	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++) {
		// Process in case of Dolphin and Enemy colliding with each other
		if(pEnemy->hit == ON)	{
			HitEnemy(pEnemy);
		}
	}
}


//------------------------------------------------------------------//
//         Process if Enemy is hit by Dolphin's attack 		//
//------------------------------------------------------------------//

void HitEnemy(Enemy* pEnemy)
{
	pEnemy->anim_state = SHELL_DEAD;		// To the animation of character being hit
	pEnemy->state = SHELL_DEAD_STATE;
	pEnemy->hit = OFF;
	pEnemy->anim_interval = 2;
	pEnemy->counter = 96;
	pEnemy->strength -= 2;				// HP -2

	// Switch player animation to attack animation
	// Skip the following routines during attack animation.
	if (player.mapY > 84) {
		if (player.anim_type != R_ATTACK_ANM) {
			player.anim_pat = 0;
			player.anim_interval = 2;
			player.anim_type = R_ATTACK_ANM;
			player.pAnmtbl = &rick_attack_pat[0];
			player.state = ACTION1;
		}
	}
}



//------------------------------------------------------------------//
//			Check whether or not character is alive		                       //
//------------------------------------------------------------------//

void DeadCheckEnemy(Enemy* pEnemy)
{
	int i;

	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++) {
		if(pEnemy->strength < 0)	{
			pEnemy->anim_state = SHELL_DEAD;		// To animation of character being hit
			pEnemy->state = SHELL_DEAD_STATE;
			pEnemy->hit = OFF;
			pEnemy->anim_interval = 2;
			pEnemy->counter = 96;

			player.anim_pat = 0;
			player.anim_interval = 2;
			player.anim_type = R_ATTACK_ANM;
			player.pAnmtbl = &rick_attack_pat[0];
			player.state = ACTION1;
		}
	}
}


//------------------------------------------------------------------//
//						Control Move Routine of Enemy					//
//------------------------------------------------------------------//

void ControlEnemyMove(Enemy *pEnemy)
{
	int i;

	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++) {
		if(pEnemy->alive != DEAD)	{
			// Jump to move routine that corresponds to the type of enemy since it is alive.
			(*pteki_state_tbl[pEnemy->state])(pEnemy, i);
		}
	}
}


//------------------------------------------------------------------//
//						Nautilus Basic Move Routine					//
//------------------------------------------------------------------//

void MoveShell1(Enemy *pEnemy, u8 i)
{
	s16 cnt, div;

	// Does not go above the water
	if (pEnemy->y < 120) {
		pEnemy->y += 2;
	} else {
		pEnemy->counter += 2;
		div = 96;

		cnt = pEnemy->counter & 0xff;
		pEnemy->vy = cos_tbl[cnt]/div;

		pEnemy->y += pEnemy->vy;
	}
}


// Move of Enemy 2
void MoveShell2(Enemy *pEnemy, u8 i)
{
}


//------------------------------------------------------------------//
//						Move Routine during Attack from Nautilus		//
//------------------------------------------------------------------//

void ShellAttackMove(Enemy *pEnemy, u8 i)
{
}


//------------------------------------------------------------------//
//						Nautilus Attacked Move Routine					//
//------------------------------------------------------------------//

void DeadMove(Enemy *pEnemy, u8 i)
{
	s16 cnt, amp, div;
	s16 num;
	pEnemy->counter += 4;
	div = 64;
	cnt = pEnemy->counter & 0xff;

	// Fall after shot out
	if (pEnemy->counter > 0xff) {
		pEnemy->vx = sin_tbl[cnt]/128;
		pEnemy->vy = 1;
	}else{
		pEnemy->vy = 2 * cos_tbl[cnt]/128;
	}
	//pteki->x += pteki->vx;

	pEnemy->x += Dec2Int(player.vx);
	pEnemy->y += pEnemy->vy;
}


//------------------------------------------------------------------//
//						Check inside of the screen						//
//------------------------------------------------------------------//

void LcdCheckEnemy(Enemy* pEnemy, Player* pPlayer)
{
	int i;

	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++) {
		if(pEnemy->alive != DEAD)	{
			if ((pEnemy->x - pPlayer->mapX) > -32 &&
				(pEnemy->x - pPlayer->mapX) < 240 &&
				(pEnemy->y - pPlayer->mapY) > -32 &&
				(pEnemy->y - pPlayer->mapY) < 160)
			{
				// Entered Screen
				pEnemy->screen = SCREEN_IN;
				pEnemy->drawflg == ON;
			} else {
				// Out of Screen
				pEnemy->screen = SCREEN_OUT;
				pEnemy->drawflg == OFF;
			}
		}
	}
}

//------------------------------------------------------------------//
//						Nautilus Animation Control Routine				//
//------------------------------------------------------------------//

void ShellAnim(Enemy *pEnemy)
{
	int i;

	for(i = 0; i < ENEMY_NUM_MAX; i++, pEnemy++) {
		if(pEnemy->alive != DEAD) { // Alive
			(*pShell_Anm_Tbl[pEnemy->anim_state])(pEnemy);  // Animation Process
		}
	}
}


//------------------------------------------------------------------//
//						Nautilus Basic Animation Routine				//
//------------------------------------------------------------------//

void ShellBaseAnim(Enemy *pEnemy)
{
	u8 i;

	if(pEnemy->screen != SCREEN_OUT)
	{
		if (++pEnemy->anim_counter > pEnemy->anim_interval)
		{
			pEnemy->anim_counter = 0;
			pEnemy->anim_pat++;

			// Create bubbles
			if (shell_base_anm_pat[pEnemy->anim_pat].action == SHELL_AWA)
			{
				CreateAwa(pEnemy);
			}

			if (pEnemy->anim_pat == 9)
			{
				pEnemy->anim_pat = 0;
				pEnemy->anim_state = SHELL_ATTACK;
				pEnemy->state = SHELL_ATTACK_STATE;
				return;
			}
			DmaCopy(3, shell_base_pix_tbl[pEnemy->anim_pat],
				pEnemy->dst_adr, sizeof(o_kihon001_Char), 16)
		}
	}
}


//------------------------------------------------------------------//
//						Nautilus Attack Animation Routine				//
//------------------------------------------------------------------//

void ShellAttackAnim(Enemy *pEnemy)
{
	u8 i;

	if(pEnemy->screen != SCREEN_OUT)
	{
		if (++pEnemy->anim_counter > pEnemy->anim_interval)
		{
			pEnemy->anim_counter = 0;
			pEnemy->anim_pat++;

			// Create Blowdart
			if (shell_attack_anm_pat[pEnemy->anim_pat].action == SHELL_ATTACK)	{
					CreateFukiya(fukiya, pEnemy);
			}

			// Return to Normal
			if (pEnemy->anim_pat > 15)	{
				pEnemy->anim_pat = 0;
				pEnemy->anim_state = SHELL_BASE;
				pEnemy->state = SHELL_NORMAL_STATE;
				return;
			}
			DmaCopy(3, shell_attack_pix_tbl[pEnemy->anim_pat],
				pEnemy->dst_adr, sizeof(o_kihon001_Char), 16)
		}
	}
}


//------------------------------------------------------------------//
//					Animation in case of being attacked         			//
//------------------------------------------------------------------//

void ShellDamageAnim(Enemy *pEnemy)
{
	u8 i;

	if (++pEnemy->anim_counter > pEnemy->anim_interval)
	{
		pEnemy->anim_counter = 0;
		pEnemy->anim_pat++;

		if (pEnemy->anim_pat > 20)	{
			pEnemy->anim_pat = 0;
			pEnemy->anim_state = SHELL_BASE;
			pEnemy->state = SHELL_NORMAL_STATE;
			pEnemy->anim_pat = 0;

			pEnemy->anim_interval = 8;
			return;
		}

		DmaCopy(3, shell_yarare_pix_tbl[pEnemy->anim_pat],
			pEnemy->dst_adr, sizeof(o_kihon001_Char), 16)
	}
}


//------------------------------------------------------------------//
//					Animation in case of being hit						//
//------------------------------------------------------------------//

void ShellDeadAnim(Enemy *pEnemy)
{

}



//------------------------------------------------------------------//
//						Nautilus Drawing Routine						//
//------------------------------------------------------------------//

void DrawEnemy(OamData* pOam, Enemy* pEnemy)
{
	*pOam = *(OamData *)Oam_32x32dot;
	pOam->CharNo = pEnemy->char_no;
	pOam->HPos   = (pEnemy->x - player.mapX);
	pOam->VPos   = (pEnemy->y - player.mapY);
	pOam->Priority = 0x00;
	pOam->ObjMode = 0;
	pOam->AffineMode = 0;
	pOam->AffineParamNo_L = 0;
	if (pEnemy->dir == RIGHT)
		pOam->HFlip = ON;
	else
		pOam->HFlip = OFF;

	// Draw if in the screen
	if(pEnemy->screen == SCREEN_IN){
	}else{
		*pOam = *(OamData *)Oam_def;
	}
}


void EraseEnemy(OamData* pOam, Enemy* pEnemy)
{
	*pOam = *(OamData *)Oam_def;
}

//------------------------------------------------------------------//
//						Initialization Routine of Bubble     				//
//------------------------------------------------------------------//

void InitAwa()
{
	int i;

	for(i = 0; i < AWA_NUM_MAX; i++) {
		awa[i].flg = 0;
		awa[i].counter = 0;
	}
	// Transfer the image data of bubble
	DmaArrayCopy(3, awa_Char, AWA_VRAM_POS, 16)
}


//------------------------------------------------------------------//
//						Main Routine of Bubble						//
//------------------------------------------------------------------//

void AwaProc()
{
	int i;
	Awa *pAwa;

	pAwa = awa;

	for(i = 0; i < AWA_NUM_MAX; i++, pAwa++) {
		if (pAwa->flg != 0)
			AwaMove(pAwa);
	}

	DrawAwa(&Oam.Objbuf[AWA_OAM_POS], awa);		// Drawing Bubble
}


//------------------------------------------------------------------//
//						Creation Routine of Bubble						//
//------------------------------------------------------------------//

void CreateAwa(Enemy *pEnemy)
{
	Awa *pAwa;
	u8 i;
	pAwa = awa;

	for(i = 0; i < AWA_NUM_MAX; i++, pAwa++) {
		if (pAwa->flg == 0)	{
			pAwa->x = pEnemy->x;// - player.mapX;
			pAwa->y = pEnemy->y - 8;
			pAwa->flg = 1;
			pAwa->zoom = 0x100;
			pAwa->dat = pEnemy->y;
			break;
		}
	}
}


//------------------------------------------------------------------//
//						Move Routine of Bubble						//
//------------------------------------------------------------------//

void AwaMove(Awa* pAwa)
{
	s16 cnt, amp, div;

	pAwa->counter += 4;
	div = 128;

	cnt = pAwa->counter & 0xff;

	pAwa->x -= cos_tbl[cnt]/div;
	pAwa->y -= 1;

//	if (pAwa->y < pAwa->dat - 128) {
	if (pAwa->y < 92) {
		pAwa->flg = 0;
	}
	
	
}


//------------------------------------------------------------------//
//						Drawing Routine of Bubble						//
//------------------------------------------------------------------//

void DrawAwa(OamData* pOam, Awa* pAwa)
{
	int i;

	for(i = 0; i < AWA_NUM_MAX; i++, pAwa++, pOam++) {
		if(pAwa->flg != 0)	{			// Alive
			*pOam = *(OamData *)Oam_8x8dot;
			pOam->CharNo = AWA_CHAR_NO;
			pOam->HPos   = pAwa->x - player.mapX;
			pOam->VPos   = pAwa->y - player.mapY;
			pOam->Priority    = 0x02;
		} else {
			*pOam = *(OamData *)Oam_def;
		}
	}
}


//------------------------------------------------------------------//
//						Initialization of blowdart						//
//------------------------------------------------------------------//

void InitFukiya()
{
	int i;

	for(i = 0; i < FUKIYA_NUM_MAX; i++) {
		fukiya[i].flg = 0;
		fukiya[i].counter = 0;
	}
	DmaArrayCopy(3, o_fukiya000_Char, FUKIYA_VRAM_POS, 16)
}


//------------------------------------------------------------------//
//						Main of blowdart								//
//------------------------------------------------------------------//

void FukiyaProc()
{
	int i;
	Fukiya *pFukiya;

	pFukiya = fukiya;

	for(i = 0; i < FUKIYA_NUM_MAX; i++, pFukiya++) {
		if (pFukiya->flg != 0)
			FukiyaMove(pFukiya);
	}
	DrawFukiya(&Oam.Objbuf[FUKIYA_OAM_POS], fukiya);
}


//------------------------------------------------------------------//
//						Create blowdart								//
//------------------------------------------------------------------//

void CreateFukiya(Fukiya *pFukiya, Enemy *pEnemy)
{
	u8 i;

	s32 y_table[] = {4,0,4,0,};

	for(i = 0; i < FUKIYA_NUM_MAX; i++, pFukiya++) {
		if (pFukiya->flg == 0)	{
			pFukiya->x = pEnemy->x - 8;
			pFukiya->y = pEnemy->y + y_table[i];
			pFukiya->flg = 1;
			pFukiya->dat = pEnemy->x - 8;
			break;
		}
	}
}


//------------------------------------------------------------------//
//						Move blowdart								//
//------------------------------------------------------------------//

void FukiyaMove(Fukiya *pFukiya)
{
	pFukiya->x -= 2;
	
	// X Coordinate where blowdart disappears
	if(pFukiya->x < pFukiya->dat - 128) {
		pFukiya->flg = 0;
	}
}


//------------------------------------------------------------------//
//						Drawing Routine of blowdart  					//
//------------------------------------------------------------------//

void DrawFukiya(OamData* pOam, Fukiya *pFukiya)
{
	int i;
	
	for(i = 0; i < FUKIYA_NUM_MAX; i++, pFukiya++, pOam++) {
		if(pFukiya->flg != 0)	{	// Alive
			*pOam = *(OamData *)Oam_16x8dot;
			pOam->CharNo = FUKIYA_CHAR_NO;
			pOam->HPos   = pFukiya->x - player.mapX;
			pOam->VPos   = pFukiya->y - player.mapY;
			pOam->Priority = 0x00;
			pOam->ObjMode = 0;
		}else{
			*pOam = *(OamData *)Oam_def;
		}
	}
}


