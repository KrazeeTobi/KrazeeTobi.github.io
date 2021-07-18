/********************************************************************/
/*          main.c                                                  */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
//#define CODE32
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "bg.h"


//------------------------------------------------------------------//
//			Global Variable                             //
//------------------------------------------------------------------//

vu16		IntrCheck;			// interrupt check
u16			Cont, Trg;		// key entry
u32			IntrMainBuf[0x200];	// interrupt main routine buffer

ObjBuf Oam;					// OAM buffer

// raster scroll
u8 rasttable[256];				// raster table
u8 v_phase;					// phase
s8 amp_r;					// amplitude parameter
s8 hz;						// frequency parameter

u8 state;
s16 counter;
u8 offset;

//------------------------------------------------------------------//
//			External Reference Variable                 //
//------------------------------------------------------------------//

extern	u32	OamData_Sample[1][2];
extern	u32	Oam_8x8dot[1][2];
extern	u32	Oam_32x32dot[1][2];

extern short rsin[];
extern short rcos[];
extern u8 sintable[];

extern Player player;
extern s32 ocean_xPos;
extern Bg bg;
extern u8 DisplayArea;
extern s32 sora_xPos;
extern BgAnm bgtest;
extern BgAnm wave2nd;
extern BgAnm wave3rd;

//------------------------------------------------------------------//
//			External Reference Funtion                  //
//------------------------------------------------------------------//

extern void InitPlayer();
extern void InitEnemy();
extern void DrawAwa();
extern void InitBg();
extern void BgProc(s32 x, s32 y);
extern void UpdateBg(s32 x, s32 y);
extern void InitRing();
extern void RingProc();
extern void InitTama();
extern void TamaProc();

//extern void InitSmoke();
extern void SmokeProc();

extern void InitPlayer_Awa();
extern void Player_AwaProc();

//------------------------------------------------------------------//
//			Prototype Declaration                       //
//------------------------------------------------------------------//

void GameInit();
void GameMain();
void GameOver();
void KeyRead(void);
void KeyDown();

//------------------------------------------------------------------//
//			Process Number                              //
//------------------------------------------------------------------//

enum {
	GAME_MAIN_PROC,
	GAME_OVER_PROC,
};

//------------------------------------------------------------------//
//			Function Table                              //
//------------------------------------------------------------------//

static void (*pGame_func_tbl[])() = {
	GameMain,
	GameOver,
};

//------------------------------------------------------------------//
//			Interrupt Table                             //
//------------------------------------------------------------------//
typedef void (*IntrFuncp)(void);
void IntrDammy(void);
void VBlankIntr(void);
void HBlankIntr(void);
void VCountIntr(void);

const IntrFuncp IntrTable[15] = {
	VBlankIntr,	HBlankIntr,
	VCountIntr,	IntrDammy,
	IntrDammy,	IntrDammy,
	IntrDammy,	IntrDammy,
	IntrDammy,	IntrDammy,
	IntrDammy,	IntrDammy,
	IntrDammy,	IntrDammy,
	IntrDammy,
};


//------------------------------------------------------------------//
//			Main Routine                                //
//------------------------------------------------------------------//
extern void intr_main(void);

void AgbMain(void)
{
	u8 i;

	amp_r = 31;	// amplitude parameter
	hz = 2;		// frequency parameter

	counter = 0;
	state = GAME_MAIN_PROC;

	GameInit();		// initialize game
	offset = 0;
	// initialize raster table
	for(i=0;i<255;i++){
		rasttable[i] = sintable[(i*hz)&255] / (amp_r << 2);
	}

	while(1) {
		(*pGame_func_tbl[state])();

		// stream processing
		if (player.water_counter > player.water_speed){
			player.water_counter = 0;

			if (player.dir == LEFT)
				offset--;
			if (player.dir == RIGHT)
				offset++;
		}

		IntrCheck &= V_BLANK_INTR_FLAG ^ 0xffff;	// V-blank interrupt check/clear flag

		while (1) {
//			Halt();									// CPU stop
			if (IntrCheck & V_BLANK_INTR_FLAG)		// V-blank interrupt processing end
				break;
		}
	}
}


//------------------------------------------------------------------//
/*			Interrupt Routine			    */
//------------------------------------------------------------------//

//------------------------------------------------------------------//
//			V-blank Processing			    //
//------------------------------------------------------------------//

void VBlankIntr(void)
{
	// OBJ set
	DmaArrayCopy(3, Oam.Objbuf,  OAM,         16);
	// BG set
	UpdateBg(player.mapX, player.mapY);		// BG update

	*(vu16 *)REG_BG0VOFS = player.mapY - 88;// Light


	// Coral
	*(vu16 *)REG_BG1VOFS = player.mapY;

	if (DisplayArea == UP)
		// Sky
		*(vu16 *)REG_BG1HOFS = (sora_xPos);
	if (DisplayArea == DOWN)
		// Coral
		*(vu16 *)REG_BG1HOFS = player.mapX;

	// Ocean A, B
	*(vu16 *)REG_BG2HOFS += Dec2Int(ocean_xPos);
	*(vu16 *)REG_BG2VOFS = player.mapY;

	v_phase = (v_phase+1) & 0x7f;	// increase phase
//	v_phase = (v_phase+1) & 0xff;	// increase phase

	*(vu16 *)REG_IF	= V_BLANK_INTR_FLAG;		// clear V-blank interrupt request flag
	IntrCheck	= V_BLANK_INTR_FLAG;		// set V-blank interrupt check flag

}


//------------------------------------------------------------------//
//		H-blank Processing				    //
//------------------------------------------------------------------//

void HBlankIntr(void)
{
	u16 line;

    line = *(vu16*)REG_VCOUNT & 0x7f;
	// Ocean A, B
	*(vu16 *)REG_BG2HOFS = rasttable[(v_phase + line)] + Dec2Int(ocean_xPos);
//	*(vu16 *)REG_BG2HOFS = offset + Dec2Int(ocean_xPos);
	// Light
	*(vu16 *)REG_BG0HOFS = rasttable[(v_phase + line)] + offset;

	*(vu16 *)REG_IF	= H_BLANK_INTR_FLAG;
}


//------------------------------------------------------------------//
//			V Counter Interrupt Processing              //
//------------------------------------------------------------------//

void VCountIntr(void)
{

}


//------------------------------------------------------------------//
//			Interrupt Dummy Routine                     //
//------------------------------------------------------------------//

void IntrDammy(void)
{
}


//------------------------------------------------------------------//
//			Key Entry                                   //
//------------------------------------------------------------------//
void KeyRead(void)
{
	u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
	Trg  = ReadData & (ReadData ^ Cont);		// trigger entry
	Cont = ReadData;								// continuous entry
}


//------------------------------------------------------------------//
//			Game Initialization                         //
//------------------------------------------------------------------//

void GameInit()
{
	DmaClear(3, 0, VRAM, VRAM_SIZE,		  16);	//   VRAM clear
	DmaClear(3, 0, OAM,  OAM_SIZE,		  32);	//    OAM clear
	DmaClear(3, 0, PLTT, PLTT_SIZE,		  16);	//  palette clear

	DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 16);// set interrupt routine
	IntrAddrSet(IntrMainBuf);

    *(vu16 *)REG_IME   = 1;                           // set IME 
	*(vu16 *)REG_IE    = V_BLANK_INTR_FLAG | H_BLANK_INTR_FLAG;	// set Vblank interrupt enable flag
	*(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE | STAT_H_BLANK_IF_ENABLE;

	*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON |
							DISP_BG2_ON | DISP_OBJ_CHAR_1D_MAP | DISP_OBJWIN_ON;

	InitBg();
	InitPlayer();
	InitEnemy();
	InitAwa();
	InitFukiya();
	InitRing();
}


//------------------------------------------------------------------//
//			Game Main                                   //
//------------------------------------------------------------------//

void GameMain()
{
	KeyRead();

	EnemyProc();
	AwaProc();
	FukiyaProc();
	PlayerProc();
	RingProc();
	BgProc(player.mapX, player.mapY);
}


//------------------------------------------------------------------//
//			Game Over Processing                        //
//------------------------------------------------------------------//

void GameOver()
{
	if (++counter % 8 == 0)	{
		amp_r = (amp_r+1) & 0x1f;
		hz = (hz+1) & 0xf;
	}
	
	if (counter > 0xff)	{
		counter = 0;
		state = GAME_MAIN_PROC;
		player.mapX = 0;
	}
}
