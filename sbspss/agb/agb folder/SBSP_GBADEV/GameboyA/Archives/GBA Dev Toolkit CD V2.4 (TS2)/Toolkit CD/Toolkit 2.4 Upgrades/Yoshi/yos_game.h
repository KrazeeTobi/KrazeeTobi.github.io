//======================================================
//    yos_game.h
//    Sample Yoshi Game Main Routine Header
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef YOS_GAME_H
#define YOS_GAME_H
#include "yos_type.h"

#define SPEED_CHK //For Speed Check
                  //When defined, start button can display egg
                  //The X coordinate of the center of the egg which uses the left side of the screen 
                  //as 0, shows the raster position at end of game processing


#define DISP_X (120<<16)//Center Location of Screen
#define DISP_Y ( 80<<16)

#define BG_LIMIT_Y_TOP    (  0<<16)//Limit Value of Scroll
//#define BG_LIMIT_Y_BOTTOM (154<<16)//
#define BG_LIMIT_Y_BOTTOM (150<<16)//Consideration of Shakes

#define ZOOM_1   (0x10000)
#define ZOOM_MAX (0x20000)//Maximum Zoom of Screen
#define ZOOM_SPEED (0x400)//Speed of Screen Zooming

#define BG_L     (1920)//Width of BG

//Main Status
enum
{
	GMAIN_ST_INIT0,		//Initialization 0
	GMAIN_ST_INIT1,		//Initialization 1(Start from here when Yoshi crashes and dies)
	GMAIN_ST_GAME_MAIN,	//During game
	GMAIN_ST_GAME_OVER0,    //Take away
};

// Global Variable Structure
typedef struct gGames_tag
{
	s32 disp_x;        //X Coordinate in the center of Screen
	s32 disp_y;        //Y Coordinate in the center of screen
	s32 zoom;          //Enlargement of screen
	s32 gnd_bias;      //Length of the vertical shaking of ground
	u32 game_timer;    //For Counter
	u16 rand_val;      //Random Number Work
	s16 kumo_x;        //X Coordinate of cloud
	s16 bgm_count;     //Wait Value for Castle BGM 
	u8  contKey;       //Direction of the pressed key 
	s8  egg_bias_count;//Vertical shaking of egg 
	s8  gnd_bias_count;//Count of Vertical shaking of Ground
	s8  siro_flg;      //Flag for the display of shaking castle 
//	u8  pad;
}gGames;

#define EGG_BIAS       ( 8)//Width of vertical shaking of egg
#define EGG_BIAS_COUNT (30)//Duration of vertical shaking of egg
#define HAKO_ROT_ANGLE ( 9)//Rotation Angle of box
#define GND_BIAS_FRM   (30)//Duration of vertical shaking
#define GND_BIAS_FRM_2 (15)//Duration of vertical shaking/2

//Structure for Initialization of OBJ Character Data
typedef struct ObjChr_tag
{
	const void *pSource;//Source of transfer
	u16 chrNo;          //Character Number destination
	u8 size;            //Size of transfer char unit
	u8 pad;             //Padding
}ObjChr;


//Data of appearing characters (Constant Data)
typedef struct CharMapData_tag
{
	xyPos start_pos;//Location to appear
	s8    char_type;//Type 
	s8    status;   //Status
	s16   dat0;     //General Purpose
	s16   dat1;
	s16   dat2;
	s16   dat3;
}CharMapData;

//Characteristics of Characters (Constant Data)
typedef struct CharSpecData_tag
{
	u32 oam01;     //Default OAM 0,1
	u16 oam2;      //              2
	s8xyPos col[2];//Relative Coordinate of Upper Left/Lower Bottom of Collision
	xyPos mid;     //Relative Coordinate from upper left of the central image 
	u8 affine_num; //Number of Affine Parameter used in this program
	s8 priority;   //Priority of Display
	u8 hit_flg;    //Evaluation of hit against Yoshi
	u8 pad;        //Padding
}CharSpecData;
//Character
//heiho     a:zoom work0:x0 work1:x1 work2:work_num work3:color work4:timer
//5t        work4:timer
//toge      work0:hang_flg work1:rot_flg work2:dir_flg
//kokamek0  work0:x0 work1:x2 work2:hang_flg
typedef struct CharacterWork_tag
{
	xyPos pos;    //Central Coordinate
	xyPos v;      //Speed
	xyPos a;      //Various uses such as Acceleration 
	s16 work0;    //General Purpose
	s16 work1;    //
	s16 work2;    //
	s16 work3;    //
	s16 work4;    //
	s16 rot;      //Angle
	s8  status;   //Status
	s8  dir;      //Direction
	s8  char_type;//Character type
	u8  anim_ptn; //Animation Pattern Number
	
	u8 hit_flg;   //Hit Quality
	u8 pad[3];    //Padding
}CharacterWork;
//#define CHARACTER_WORK_MAX (64)
#define CHARACTER_WORK_MAX (48)

#define YOS_HISTORY_MAX  (85)       //Coordinate Data Number for the Egg Coordinate
#define YOS_EGG_DIFF     (15)       //Space between Eggs
#define EGG_WORK_MAX     ( 3)       //Work Number of Eggs
#define YOSHI_DEAD_LIMIT (256<<16)  //The height at which Yoshi dies if he goes any lower

#define YOSHI_MUTEKI_TIME      (240)//Duration of Invincible time after death
#define KURURINHA_KOTYOKU_TIME ( 30)//Duration of stiffness after Hip Drop

//Work of Yoshi
typedef struct YoshiWork_tag
{
	xyPos pos;          //Central Coordinate
	xyPos pos_old;      //
	xyPos v;            //Speed
	xyPos mid;	    //Relative Coordinate from the upper left of the central image
	xyPos posOn;	    //Coordinate which has the center of the riding character as zero 
	xyPos zoom;         //Zoom
	s16 history_cur;    //Current location of history
	s16 muteki_timer;   //Rest of the Invincible time
	s16 koutyoku_timer; //Duration of Stiffness
	s16 work0;          //General Purpose
	s16 rot;            //Angle
	s8xyPos col[2];		//Relative Coordinates of Upper Left/Lower Right of collision
	s16xyPos pos_history[YOS_HISTORY_MAX];//Past Location of Yoshi(Ring Buffer)
	
	u8 funbari_timer;	//Time Yoshi can flutter jump
	u8 jump_timer;		//Time Yoshi can jump
	u8 anm_ptn_new;		//Pattern Number of Animation 
	s8 on;			//Characters that Yoshi rides
	
	s8 on_old;		//Characters that Yoshi rides
	s8 egg_num;		//Number of eggs Yoshi has
	u8 funbari_flg;		//Flag to indicate the ability to flutter jump
	u8 tyouhatu_flg;	//Flag to indicate provocation 
	
	u8 tatenobi;		//Flag that appears when stretched vertically
	s8 dir;                 //Direction
	s8 status;              //Status
	s8 kururin_se;		//Flag for SE of Ground Pound
	
	s8 fall_timer;		//Timer for Falling SE
	u8 pad[3];//Padding
}YoshiWork;
#define YOS_ON_NONE (-1)

//Status of Yoshi
enum
{
	YOSHI_ST_NONE,
	YOSHI_ST_NORMAL,	//Normal
	YOSHI_ST_JUMPING,	//Jumping
	YOSHI_ST_KURUN,		//Revolving before Ground Pound
	YOSHI_ST_KURURIN,	//Ground Pound
	YOSHI_ST_MOUNT,		//Riding other characters
	YOSHI_ST_TYOUHATU,	//Provocation
	YOSHI_ST_DIE,		//Die
	YOSHI_ST_,	//
};

//Status commmon among characters
#define CHAR_ST_NONE     (-1)
#define CHAR_ST_NA       ( 0)
#define CHAR_ST_NORMAL   ( 1)

//Status of Shy Guy
enum
{
	HEIHO_ST_NONE=-1,
	HEIHO_ST_NA,		//Not Active
	HEIHO_ST_NORMAL,	//Normal
	HEIHO_ST_DYING,		//Die after stomped on from above
};
//Status of Killer S
enum
{
	KILLERS_ST_NONE=-1,
	KILLERS_ST_NA,		//Not Active
	KILLERS_ST_NORMAL,	//Normal
	KILLERS_ST_DYING,	//when dying after stomped on from above
};

//Status of Balloon
enum
{
	BALLOON_ST_NONE = -1,
	BALLOON_ST_NA,
	BALLOON_ST_NORMAL,
	BALLOON_ST_HARETU,
};

enum
{
	BOMB_ST_DYING=2,
};

//Status of Egg
enum
{
	EGG_ST_NONE,
	EGG_ST_NORMAL,	//Normal
	EGG_ST_SURI,	//Yoshi drags
	EGG_ST_JUMP,
};

//Status of Box
enum
{
	HAKO_ST_NONE,	//
	HAKO_ST_NORMAL,	//Normal
	HAKO_ST_ROT,	//Pushed up from underneath while revolving
};

#define EFF_WORK_MAX    (32)//Number of Work of Effect
#define KOKAMEK_MAX     ( 4)//Number of Kokameks
#define HANABIRA_MAX    ( 8)//Number of Petals

//Work of Effect
typedef struct EffectWork_tag
{
	xyPos pos;		//Coordinate
	xyPos v;		//Velocity
	xyPos a;
	s16 chr;		//Character
	s16 count;		//Time remaining for this effect
	s16 *pPtn;		//Pointer for Animation Array
	s8 status;
	s8 eff_type;	//Type of Effect
	s8 time;		//Remaining Time of Pattern
	u8 pad;			//Padding
}EffectWork;

//Type of Effect
enum
{
	EFF_TYPE_DASH,		//Dash Smoke
	EFF_TYPE_SMOKE,		//Ground Pound Smoke
	EFF_TYPE_COINS,		//Star when get coins
	EFF_TYPE_HEIS,		//Star when step on Shy Guy
};


//Pattern for Function Table
typedef void (*func_ptr)(void);

#define YOSHI_MOV_SPEED       (0x10000)	//Moving Speed of Yoshi
#define YOSHI_JUMP_MOV_SPEED  (0x20000)	//Moving Speed of Yoshi when jumping
#define YOSHI_MOV_MAX_SPEED   (0x20000)	//Maximum Moving Speed of Yoshi
#define YOSHI_MOV_RUN_SPEED   (0x18000)	//Speed when Yoshi starts running
#define YOSHI_FALL_ACC        ( 0x2800)	//Acceleration Speed of Yoshi Falling
#define YOSHI_FALL_MAX_SPEED  ( 0x20000)//Maximum Falling Speed of Yoshi
#define YOSHI_JMP_SPEED       (-0x30000)//Jumping Speed of Yoshi
#define FUNBARI_TIME          (60)		//Time to flutter jump
#define YOSHI_JMP_TIME        (60)		//Duration of Upward Jump
#define YOSHI_JMP_ACC         (-0x2000)	//Acceleration of Upward Jump
#define FUNBARI_ACC           (-0x3200)	//Acceleration going upwards after flutter Jump
#define FUNBARI_ACC2          (-0x3400)	//Acceleration of Flutter jump+ up button rising
#define FUNBARI_LIMIT         (0x2000)	//Speed to start flutter jump
#define YOSHI_HANE_SPEED_LR   (0x10000)	//Speed of Yoshi Flipping
#define YOSHI_HANE_SPEED_D    (0x10000)	//Speed of Yoshi Flipping
#define YOSHI_HANE_SPEED_U    (-0x20000)//Speed of Yoshi Flipping
#define HEIHO_MOV_SPEED       (0x8000)	//Moving Speed of Shy Guy
#define YOSHI_KURU_FALL_SPEED (0x40000)	//Falling speed of Ground Pound
#define KILLER_MOV_SPEED      (0x18000)//Moving Speed of Killer S
#define KILLERS_FALL_ACC      (0x2000)

#define CHR_DIR_TL1 (-3)//Turn to Left1
#define CHR_DIR_TL0 ( 2)//Turn to Left0
#define CHR_DIR_L   (-1)//Facing Left
#define CHR_DIR_R   ( 1)//Facing Right
#define CHR_DIR_TR0 (-2)//Turn to Right0
#define CHR_DIR_TR1 ( 3)//Turn to Right1


//Work of Animation
enum
{
	ANM_WORK_YOSHI,	//0
	ANM_WORK_KURUKEMU,
	ANM_WORK_HEIHO0,
	ANM_WORK_HEIHO1,
	ANM_WORK_HEIHO2,
	
	ANM_WORK_HEIHO3,
	ANM_WORK_HEIHO4,
	ANM_WORK_HEIHO5,
	ANM_WORK_HEIHOL,
	ANM_WORK_MBOX,
	
	ANM_WORK_SUN,
	ANM_WORK_SMOKE,
	ANM_WORK_KILLERS0,
	ANM_WORK_BALLOON,
	
	ANM_WORK_BOMB,
	
	ANM_WORK_G_MAX//Number of articles
};

#define HEIHO_MAX (6)
#define KILLERS_MAX (2)

//Number of Character Type
enum
{
	CHR_TYPE_YOSHI,		//Yoshi
	CHR_TYPE_HEIHO,		//Shy Guy
	CHR_TYPE_HAKO,		//Box
	CHR_TYPE_EGG,		//Egg
	CHR_TYPE_SUN,		//Sunflower Gauge
	CHR_TYPE_KILLER_S,	//Killer Small
	CHR_TYPE_KILLER_L,	//Killer Large
	CHR_TYPE_KOKAMEK0,	//Kokamek0
	CHR_TYPE_KOKAMEK1,	//Kokamek1
	CHR_TYPE_HEIHOL,	//Shy Guy Large
	CHR_TYPE_HANABIRA0,	//Petals0
	CHR_TYPE_HANABIRA1,	//Petals1
	CHR_TYPE_HANABIRA2,	//Petals2
	CHR_TYPE_HANABIRA3,	//Petals3
	CHR_TYPE_HANABIRA4,	//Petals4
	CHR_TYPE_HANABIRA5,	//Petals5
	CHR_TYPE_HANABIRA6,	//Petals6
	CHR_TYPE_HANABIRA7,	//Petals7
	CHR_TYPE_HANABIRA8,	//For Revolving
	CHR_TYPE_KOUMORI,	//Bat
	CHR_TYPE_KUMO0,		//Cloud (Left)
	CHR_TYPE_KUMO1,		//Cloud (Right)
	CHR_TYPE_HOSI,		//Star
	CHR_TYPE_KURUKEMU,	//Ground Pound Smoke
	CHR_TYPE_KAGE0,		//Shadow
	CHR_TYPE_BATABATA,	//Dash Smoke
	CHR_TYPE_KAGEL,		//Shadow (Large)
	CHR_TYPE_BALLOON,	//Balloon
	CHR_TYPE_5T,	//5t
	CHR_TYPE_BOMB,	//Bob-omb
	CHR_TYPE_DOKAN,	//
	CHR_TYPE_HANA,	//
	CHR_TYPE_KUKI,	//
	CHR_TYPE_TOGE,	//
};

#define YOS_CWORK (0)

//Work of Affine Parameter
#define AFN_WORK_KOUMORI0  (16)
#define AFN_WORK_HANABIRA0 ( 0)
#define AFN_WORK_HANABIRA1 ( 1)
#define AFN_WORK_HANABIRA2 ( 2)
#define AFN_WORK_HANABIRA3 ( 3)
#define AFN_WORK_HANABIRA4 ( 4)
#define AFN_WORK_HANABIRA5 ( 5)
#define AFN_WORK_HANABIRA6 ( 6)
#define AFN_WORK_HANABIRA7 ( 7)
#define AFN_WORK_HANABIRA8 ( 8)
#define AFN_WORK_HEIHO0    ( 9)
#define AFN_WORK_HEIHO1    (10)
#define AFN_WORK_HEIHO2    (11)
#define AFN_WORK_HEIHO3    (12)
#define AFN_WORK_HEIHO4    (13)
#define AFN_WORK_HEIHO5    (14)

#define AFN_WORK_HEI_K0    (15)
#define AFN_WORK_HANA      (16)
#define AFN_WORK_TOGE_L    (17)
#define AFN_WORK_TOGE_R    (18)

#define AFN_WORK_HEIHOL    (23)
#define AFN_WORK_BALLOON   (24)
#define AFN_WORK_HAKO      (25)
#define AFN_WORK_KAGE      (26)

#define AFN_WORK_GL        (27) //Left Normal
#define AFN_WORK_GR        (28) //Right Normal
#define AFN_WORK_KOKAMEK_R (29)
#define AFN_WORK_KOKAMEK_L (30)
#define AFN_WORK_YOS       (31)
#define AFN_WORK_EGG       (AFN_WORK_GL)

//SW to switch OBJ Mode with 16, 256 colors
//#define OBJ_COLOR (1) //16 colors
#define OBJ_COLOR (2) //256 colors

//Mapping of VRAM (Character Number)
#define CNUM_HEIHO0    (  0*OBJ_COLOR)	//Shy Guy 32x32
#define CNUM_HEIHO1    ( 16*OBJ_COLOR)	//Shy Guy 32x32
#define CNUM_HEIHO2    ( 32*OBJ_COLOR)	//Shy Guy 32x32
#define CNUM_HEIHO3    ( 48*OBJ_COLOR)	//Shy Guy 32x32
#define CNUM_HEIHO4    ( 64*OBJ_COLOR)	//Shy Guy 32x32
#define CNUM_HEIHO5    ( 80*OBJ_COLOR)	//Shy Guy 32x32
#define CNUM_HAKO      ( 96*OBJ_COLOR)	//Box     32x32
#define CNUM_EGG       (112*OBJ_COLOR)	//Egg     16x16
#define CNUM_SUN       (116*OBJ_COLOR)	//Gauge    32x32
#define CNUM_KILLER_S0 (132*OBJ_COLOR)	//Killer  32x32
#define CNUM_KILLER_L  (148*OBJ_COLOR)	//Killer  64x64
#define CNUM_HANA      (148*OBJ_COLOR)	//Flower  32x32
#define CNUM_KUKI      (164*OBJ_COLOR)	//Stem    32x32
#define CNUM_TOGE      (180*OBJ_COLOR)	//Thorn   32x32

#define CNUM_HEIHOL    (212*OBJ_COLOR)	//Shy Guy Large 64x64
#define CNUM_HANABIRA0 (276*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA1 (280*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA2 (284*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA3 (288*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA4 (292*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA5 (296*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA6 (300*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA7 (304*OBJ_COLOR)	//Petal    16x16
#define CNUM_HANABIRA8 (308*OBJ_COLOR)	//Petal    16x16
#define CNUM_HOSI      (312*OBJ_COLOR)	//Star
#define CNUM_HOSI1     (313*OBJ_COLOR)	//Star
#define CNUM_HOSI2     (314*OBJ_COLOR)	//Star
#define CNUM_HOSI3     (315*OBJ_COLOR)	//Star
#define CNUM_HOSI4     (316*OBJ_COLOR)	//Star
#define CNUM_HOSI5     (317*OBJ_COLOR)	//Star
#define CNUM_HOSI6     (318*OBJ_COLOR)	//Star
#define CNUM_HOSI7     (319*OBJ_COLOR)	//Star
#define CNUM_KURUKEMU  (320*OBJ_COLOR)	//Ground Pound Smoke
#define CNUM_BATABATA0 (336*OBJ_COLOR)	//Dash Smoke   16x16
#define CNUM_BATABATA1 (340*OBJ_COLOR)	//Dash Smoke1
#define CNUM_BATABATA2 (344*OBJ_COLOR)	//Dash Smoke2
#define CNUM_BATABATA3 (348*OBJ_COLOR)	//Dash Smoke3
#define CNUM_BATABATA4 (352*OBJ_COLOR)	//Dash Smoke4
#define CNUM_BATABATA5 (356*OBJ_COLOR)	//Dash Smoke5
#define CNUM_BATABATA6 (360*OBJ_COLOR)	//Dash Smoke6
#define CNUM_BATABATA7 (364*OBJ_COLOR)	//Dash Smoke7
#define CNUM_KAGE0     (368*OBJ_COLOR)	//Shadow
#define CNUM_KAGEL     (370*OBJ_COLOR)	//Shadow Large    32x8
#define CNUM_BALLOON   (374*OBJ_COLOR)	//Balloon    32x32
#define CNUM_5T        (390*OBJ_COLOR)	//5t    32x32
#define CNUM_BOMB      (406*OBJ_COLOR)	//Bob-omb 32x32
#define CNUM_DOKAN     (422*OBJ_COLOR)	//Pipe    32x32

#define CNUM_KOKAMEK0  (448*OBJ_COLOR)	//Kokamek Front 32x32
#define CNUM_KOKAMEK1  (464*OBJ_COLOR)	//Kokamek Back
#define CNUM_YOSHI     (480*OBJ_COLOR)	//Yoshi


#define CNUM_KUMO0     (256*OBJ_COLOR)	//Cloud Left
#define CNUM_KUMO1     (320*OBJ_COLOR)	//Cloud Right
#define CNUM_KOUMORI   (384*OBJ_COLOR)	//Bat
#define CNUM_          (0)//

//Flag
#define HIT_LR   (0x1) //From Left and Right
#define HIT_T    (0x2) //From Above
#define HIT_B    (0x4) //From Underneath
#define HIT_YLR  (0x8) //Yoshi Dies (when hit from left or right)
#define HIT_D_H  (0x10) //Yoshi flips when hit from underneath

#define HOSI_MAX (12)//Number of Stars
#define HOSI_R_  (25)//Radius of Stars/0x10000

enum
{
	HANABIRA_ST_NONE,
	HANABIRA_ST_NORMAL,
	HANABIRA_ST_FALL,
};

#define HANABIRA_FALL_ACC (0x800)
#define HANABIRA_FALL_TIME (0x40)


//Priority of Characters
//Sun          0
//Effect       1 
//Kokamek Back 1
//5t           1
//Thorn        1
//Yoshi        3
//Egg          4
//Others       5

//Box          6
//Shadow       7
//Flower       7
//Stem         8

#define PRI_GAGE      (0)
#define PRI_EFFECT    (1)
#define PRI_KOKAMEK_U (1)
#define PRI_5T        (1)
#define PRI_TOGE      (1)
#define PRI_YOSHI     (3)
#define PRI_EGG       (4)
#define PRI_HEIHO     (5)
#define PRI_KILLER    (5)
#define PRI_KOKAMEK_D (5)
#define PRI_OT        (5)
#define PRI_HAKO      (6)
#define PRI_KAGE      (7)
#define PRI_HANA      (7)
#define PRI_KUKI      (8)

#define KOUMORI_NUM    (4)
#define KUMO_MOV_SPEED (0x20)
#define BALLOON_MASATU_ACC (0x2000)
#define BALLOON_HANE_SPEED (0x10000)
#define BALLOON_RAND_V (0x8000)

#define RAND_SEED (0x34567)
#define YOSHI_MASATU_ACC (0x2000)

#ifdef SPEED_CHK
#define CHR_WORK_BALLOON (1)
#else
#define CHR_WORK_BALLOON (0)
#endif

#define HEIHO_COLOR_NUM (4)

#define ANM_FLG_NEW (1)
#define ANM_FLG_PIX_CHG (2)
#define TOGE_MOV_SPEED (0x10000)

//Range of Yoshi on screen
#define D_LIMIT_X (50*0x10000)
#define D_LIMIT_Y (70*0x10000)

#endif//_YOS_GAME_H
