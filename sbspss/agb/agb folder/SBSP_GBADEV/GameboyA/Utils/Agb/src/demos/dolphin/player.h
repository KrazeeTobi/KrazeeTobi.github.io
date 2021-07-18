/********************************************************************/
/*          player.h                                                */
/*                 Data external declaration                        */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef	_PLAYER_H
#define	_PLATER_H

// maximum speed  
#define SPEED_MAX_X 0x200
#define SPEED_MAX_Y 0x100

// acceleration
#define ACCEL_X 0x1f
#define ACCEL_Y 0x10

// water speed
#define WATER_SPEED_SLOW 4
#define WATER_SPEED_NORM 2
#define WATER_SPEED_FAST 0

// animation speed
#define ANIM_NORMAL      10
#define ANIM_TIME_MIDDLE  3
#define ANIM_FAST         7

// OAM position
#define PLAYER_OAM_POS     0
#define PLAYER_AWA_OAM_POS 2

// maximum display number of bubbles 
#define PLAYER_AWA_MAX_NUM 4

// starting position
#define START_POS_X 68
#define START_POS_Y 0

// collision detection
#define HIT_RING_TOP         0x10	// top of ring 
#define HIT_RING_BOTTOM      0x20	// bottom of ring 
#define HIT_RING_MIDDLE_UP   0x30	// inside ring 
#define HIT_RING_MIDDLE_DOWN 0x40	// inside ring

// attack graphics number 
#define RICK_ATTACK_ANM_NUM 5
#define RICK_JUMP_ANM_NUM   18

// structure for animation table 
typedef struct {
	u8 anm_ptn;
	s8 delay;
} AnmTable;

typedef struct {
	u8 anm_ptn;
	u8* img;
	s8 delay;
} AnmTable2;


// structure of dolphin 
typedef struct {
	s32 mapX, mapY;
	
	s16		x, y;		// position
	s16 oldx, oldy;
	s16		dx, dy;		// distance moved
	s32		vx, vy;		// speed
	s16		ax, ay;		// acceleration
	u8		char_no;
	s16		counter;
	u32		timer;		// timer
	u8		state;		// status
	s8		dir;		// direction
	u8		hit;		// collision detection
	u8		enemy_hit;
	u8		auto_flg;	// automatic/manual switch  
	AnmTable* pAnmtbl;
	AnmTable2* pAnmtbl2;
	u8		anim_type;	
	s16		anim_pat;
	s16		up_down_anm_pat;
	s16		anim_interval;
	s16		anim_counter;
	u8		blinkflg;
	u8		water_speed;
	u8		water_counter;
} Player;


// structure of bubbles  
typedef struct {
	s32 x, y;
	s32 oldx, oldy;
	u8 flg;
	s16 counter;
	s16 timer;
}Player_Awa;


// bubble control
void InitPlayer_Awa();
void Player_AwaProc();
void CreatePlayer_Awa(Player_Awa *pAwa, Player *pPlayer);
void Player_AwaMove(Player_Awa *pAwa, Player *pPlayer);
void DrawPlayer_Awa(OamData* pOam, Player_Awa *pAwa);

extern u16		Cont, Trg;			// key entry

// player control function   
void InitPlayer();
void PlayerProc();
void ControlPlayer();
void DrawPlayer();
void MovePlayer();
void Chang_Dir(Player* pPlayer);
void InitPlayerAnim();
void PlayerAnim();
void PlayerActionControl();
void RestrictPlayerPosition(Player* pPlayer);
void Ajust_Light_Reflection(Player* pPlayer);
void BlinkPlayer(Player* pPlayer);
void ChangeWaterSpeed();

// OAM number of player  
enum {
	PLAYER_OAM0,
	PLAYER_OAM1,
};

// status of player  
enum {
	MOVE, 
	ACTION1,
	JUMP,
	ACTION3,
};

void Action1();
void JumpPlayer();
void Action3();

// jump table
static void (*pPlayer_action_tbl[])() = {
	MovePlayer,
	Action1,
	JumpPlayer,
	Action3
};


// animation type
enum {
	R_KIHON_ANM,		// basic
	R_KIHON_IDLE_ANM,	// extra
	R_UP_DOWN_ANM,		// going up/down 
	R_JUMP_ANM,		// jump
	R_IDLE_ANM,		// operation stand-by 
	R_ATTACK_ANM,		// tail attack
	R_MOVE_RL,		// horizontal move
	R_HEAD_ATTACK_ANM,	// butt attack
	R_ANM_MAX,		// maximum number
};


void Player_kihon_anm();  	// basic animation
void Player_kihon_idle_anm();
void Player_updown_anm(); 	// going up/down animation  
void Player_jump_anm();   	// jump animation
void Player_idle_anm();   	//
void Player_tail_swim();
void Player_attack_anm();
void Player_move_rl_anm();
void Player_head_attack_anm();


static void (*pRick_anm_tbl[])() = {
	Player_kihon_anm,
	Player_kihon_idle_anm,
	Player_updown_anm,
	Player_jump_anm,
	Player_idle_anm,
	Player_attack_anm,
	Player_move_rl_anm,
	Player_head_attack_anm,
};


//------------------------------------------------------------------//
//		Basic Graphics of Dolphin 			    //
//------------------------------------------------------------------//

extern u8 r_kihon0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_kihon7_Char[8*8*(64/8/1)*(64/8)];


//------------------------------------------------------------------//
//		Attack Graphics of Dolphin 			    //
//------------------------------------------------------------------//
extern u8 r_attack1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_attack2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_attack3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_attack4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_attack5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_attack6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_attack7_Char[8*8*(64/8/1)*(64/8)];


//------------------------------------------------------------------//
//		Upward Move Graphics of Dolphin 		    //
//------------------------------------------------------------------//
extern u8 r_up0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up7_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up8_Char[8*8*(64/8/1)*(64/8)];

extern u8 r_go_up0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_up7_Char[8*8*(64/8/1)*(64/8)];



//------------------------------------------------------------------//
//		Upward Graphics of Dolphin 			    //
//------------------------------------------------------------------//

extern u8 r_up0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up7_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_up8_Char[8*8*(64/8/1)*(64/8)];




//------------------------------------------------------------------//
//		Downward Move Graphics of Dolphin  		    //
//------------------------------------------------------------------//
extern u8 r_go_down0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_go_down7_Char[8*8*(64/8/1)*(64/8)];


//------------------------------------------------------------------//
//		Downward Graphics of Dolphin  			    //
//------------------------------------------------------------------//
extern u8 r_down0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down7_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_down8_Char[8*8*(64/8/1)*(64/8)];

//------------------------------------------------------------------//
//		Jump Move Graphics of Dolphin  			    //
//------------------------------------------------------------------//
extern u8 r_jump0_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump1_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump2_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump3_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump4_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump5_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump6_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump7_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump8_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump9_Char[8*8*(64/8/1)*(64/8)];
extern u8 r_jump10_Char[8*8*(64/8/1)*(64/8)];



#endif