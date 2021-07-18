/********************************************************************/
/*          enemy.h                                                 */
/*                 Data external declaration                        */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef	_ENEMY_H
#define	_ENEMY_H

// Maximum number of OAM usage by enemy  
#define ENEMY_OAM_NUM_MAX   10

// Maximum number of enemies
#define ENEMY_NUM_MAX   10
// Maximum number of bubbles
#define AWA_NUM_MAX    16
// Maximum number of bubbles Nautilus emits  
#define SHELL_AWA_MAX   3
// Maximum number of blowguns Nautilus blows 
#define FUKIYA_NUM_MAX  4
/*
#define ENEMY_OAM_POS  10
#define AWA_OAM_POS    20
#define FUKIYA_OAM_POS 40
*/
#define ENEMY_OAM_POS   10
#define AWA_OAM_POS     30
#define FUKIYA_OAM_POS  50

// OAM NO of Nautilus, 1 Nautilus, 4 blowguns, 3 bubbles consumed each  
#define SHELL1_OAM_POS 10
#define SHELL2_OAM_POS 18
#define SHELL3_OAM_POS 26
#define SHELL4_OAM_POS 34

// Width and height of Nautilus 
#define SHELL_WIDTH 32
#define SHELL_HEIGHT 32

// Width and height of bubble  
#define AWA_WIDTH 8
#define AWA_HEIGHT 8

// Width and height of blowgun 
#define FUKIYA_WIDTH 16
#define FUKIYA_HEIGHT 16

// Types of enemy  
enum {
	SHELL,  // Nautilus
	ENEMY_2,
	ENEMY_3,
	ENEMY_BOSS,
};

/*
// Condition of enemy
enum {
	TEKI_NORMAL, 
	TEKI_KILLED,
	TEKI_ERASE,
};
*/

// Condition of Nautilus 
enum {
	SHELL_MOVE,				// moving
	SHELL_AWA,				// emitting bubbles 
	SHELL_SPEAR_ATTACK,			// blowgun attack  
};

// Character map data 
typedef struct
{
	s32   xPos, yPos;// position of appearance 
	u8    char_type; // type  
	u8    status;    // status
	u32   VRAM_ADDR; // destination address of graphics 
	u16   char_no;   // character No
}CharMapData;

// OAM data
typedef struct
{
	u32   dest_adr;  // destination address of graphics 
	u16   char_no;   // character No
}Enemy_Oam_Data;



// Enemy character data  
typedef struct {
	s32 screen_X, screen_Y;
	s32		xPos, yPos;	//position of appearance

	s32		x, y;		// position
	s16		dx, dy;		// distance moved
	s16		vx, vy;		// speed
	s16		ax, ay;		// acceleration
	u8		state;		// state

	u16		char_no;		// character No
	u8		anim_state;		// animation state
	s16		anim_pat;		// animation pattern
	s16		anim_interval;	// animation intervals
	s16		anim_counter;	// counter

	s8		dir;			// current direction 
	s8		strength;		// strength
	u8		alive;			// check if dead or alive 
	u8		screen;			// out-of-screen check flag 
	u8		anmflg;			// animation flag
	s16		timer;			// timer
	s16		counter;		// counter
	s16		delay;			// delay
	s32		zoom;			// zoom
	u8		hit;			// collision detection 
	u16		blinkcounter;	// blinking counter 
	u8		blinkflg;
	u8		drawflg;
	u32		dst_adr;		// destination address of graphics  
}Enemy;


// animation pattern data 
typedef struct {
	s16		pat;			// animation pattern
	s16		delay_time;		// animation intervals
	s16		action;			// action pattern
}Anmpat;





// Bit map of bubbles  
extern u8 awa_Char[8*8*(8/8/1)*(8/8)];

// Structure of bubbles
typedef struct {
	s32 x, y;
	u8 flg;
	s16 counter;
	int zoom;
	s32 dat;
}Awa;


// Bit map of blowgun 
extern u8 o_fukiya000_Char[8*8*(16/8/1)*(16/8)];

// Structure of blowgun  
typedef struct {
	s32 x, y;
	u8 flg;
	s16 counter;
	s32 dat;
}Fukiya;


// Basic bit map of Nautilus 
extern u8 o_kihon001_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon002_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon003_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon004_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon005_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon006_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon007_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon008_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon009_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kihon010_Char[8*8*(32/8/1)*(32/8)];

// Bit map for Nautilus attack 
extern u8 o_kougeki000_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki001_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki002_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki003_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki004_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki005_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki006_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki007_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki008_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki009_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki010_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki011_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki012_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki013_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki014_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki015_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki016_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki017_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki018_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki019_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_kougeki020_Char[8*8*(32/8/1)*(32/8)];

// Bit map of rotating Nautilus  
extern u8 o_yarare000_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare001_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare002_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare003_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare004_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare005_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare006_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare007_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare008_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare009_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare010_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare011_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare012_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare013_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare014_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare015_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare016_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare017_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare018_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare019_Char[8*8*(32/8/1)*(32/8)];
extern u8 o_yarare020_Char[8*8*(32/8/1)*(32/8)];


// State of Nautilus 
enum {
	SHELL_NORMAL_STATE,		// normal
	SHELL_NORMAL2_STATE,
	SHELL_ATTACK_STATE,		// attacking
	SHELL_DEAD_STATE,		// rotating
	SHELL_DAMAGE_STATE,		// damaged
};

// Function for enemy's move
void MoveShell1(Enemy *pEnemy, u8 i);		// in case of normal move 
void MoveShell2(Enemy *pEnemy, u8 i);		// 
void ShellAttackMove(Enemy *pEnemy, u8 i);	// in case of attacking 
void DeadMove(Enemy *pEnemy, u8 i);		// in case of being damaged 

// Jump table for enemy's move function 
static void (*pteki_state_tbl[])(Enemy *, u8) = {
	MoveShell1,
	MoveShell2,
	ShellAttackMove,
	DeadMove
};


// Animation status of Nautilus 
enum {
	SHELL_BASE,
	SHELL_ATTACK,
	SHELL_DEAD,
	SHELL_DAMAGE,
};

// Animation function of Nautilus 
void ShellBaseAnim(Enemy *pEnemy);
void ShellAttackAnim(Enemy *pEnemy);
void ShellDamageAnim(Enemy *pEnemy);
void ShellDeadAnim(Enemy *pEnemy);

// Jump table for Nautilus animation function 
static void (*pShell_Anm_Tbl[])(Enemy *pEnemy) = {
	ShellBaseAnim,
	ShellAttackAnim,
	ShellDamageAnim,
	ShellDeadAnim,
};


//------------------------------------------------------------------//
//			Function Prototype Declaration 		    //
//------------------------------------------------------------------//

// Enemy control
void InitEnemy();			//initialize
void EnemyProc();			//main
void CreateTeki(Enemy *pEnemy, CharMapData* pInfoTbl);// create enemy
void ShellAnim(Enemy *pEnemy);

void ControlEnemyMove(Enemy *pEnemy);	
void DrawEnemy(OamData* pOam, Enemy* pEnemy);		// draw enemy
void EraseEnemy(OamData* pOam, Enemy* pEnemy);
void HitEnemy(Enemy* pEnemy);

void LcdCheckEnemy(Enemy* pEnemy, Player* pPlayer);
void DeadCheckEnemy(Enemy* pEnemy);	// check if dead or alive  
void HitCheck_Enemy(Enemy* pEnemy);

// Bubble control
void InitAwa();					// initialize bubble
void AwaProc();					// Bubble main processing 
void CreateAwa(Enemy *pEnemy);			// create bubbles
void AwaMove(Awa* pAwa);			// move bubbles 
void DrawAwa(OamData* pOam, Awa* pAwa);		// draw bubbles

// Blowgun control 
void InitFukiya();					// initialize blowgun
void FukiyaProc();					// Blowgun main processing  
void CreateFukiya(Fukiya *pFukiya, Enemy *pEnemy);	// create blowgun 
void FukiyaMove(Fukiya *pFukiya);			// move blowgun
void DrawFukiya(OamData* pOam, Fukiya *pFukiya);	// draw blowgun


#endif


