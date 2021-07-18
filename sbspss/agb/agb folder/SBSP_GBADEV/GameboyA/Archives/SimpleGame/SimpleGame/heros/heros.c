/*============================================================================
	Nintendo of America Developer Support
	Scott Perras

	hblank interval = 73.433us
	vblank interval = 16.743ms

 	DMA Transfer of:
		38400bytes (240x160) in 62 scan lines (62 * 57.221us = 3547.702us)

============================================================================*/
#include "main.h"
#include "cursor.h"
#include "units.h"
#include "battle.h"
#include "heros.h"

#include "art\heroart.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================
extern const u8 _binary_map_scaled_bin_start[];
extern const u8 _binary_horse1_bin_start[];

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================
#define HERO_HORSE_OAM_INDEX 	(0)
#define MAX_MAP_WIDTH					(240)

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================
static void initHero(HERO_ACTOR *hero);
static void initHeroDisplay(void);

static void updateHero(void);
static void herosVBlankSyncFunction(void);
static void updateMap(void);

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================
HERO_ACTOR heroActor;
HERO_ACTOR enemyHeroActor;

long disableVCountProcessing;
long debugFlag;


/*
 *	void doHeros(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Starts hero test
 *
 *  RETURNS:			Nothing
 */
void doHeros(void)
{

	//init heros
	initHero(&heroActor);
	initHero(&enemyHeroActor);

	//disable cursor
	global_cursorActor.cursorActive = OFF;

	//init for map display
	initHeroDisplay();

	//enable OAM updates
	global_systemInfoPtr->updateOAM = 1;
	disableVCountProcessing = 0;

	while (1) {

		
		//DEBUG
		#if 0
		if (global_systemInfoPtr->controlPad & R_BUTTON) {

			if (global_systemInfoPtr->controlPad & U_KEY) {
				if (heroActor.mapYPos) {
					heroActor.mapYPos -= 4;
				}
			}

			else if (global_systemInfoPtr->controlPad & D_KEY) {
				if (heroActor.mapYPos < 2064) {
					heroActor.mapYPos += 4;
				}
			}

			if (global_systemInfoPtr->controlPad & R_KEY) {

				if (heroActor.mapXPos < 2064) {
					heroActor.mapXPos += 4;
				}
			}

			else if (global_systemInfoPtr->controlPad & L_KEY) {
				if (heroActor.mapXPos) {
					heroActor.mapXPos -= 4;
				}
			}
		}

		else {
			updateHero();
		}
		#endif
		//DEBUG
		
		//update controller input for hero
		updateHero();

		//do battle
		if (global_systemInfoPtr->controlPadTrigger & START_BUTTON) {

			//disable VCount IRQ
			disableVCountInterrupt();

			//fade out
			fadeOut(BLD_ALL);

			//turn horse off
			setOamIndexOff(HERO_HORSE_OAM_INDEX);

			//do battle
			beginBattle(&heroActor, &enemyHeroActor);

			//init for map display
			initHeroDisplay();

			//turn horse on
			setOamIndexOn(HERO_HORSE_OAM_INDEX);

			//fade out
			fadeIn(BLD_ALL);
		}

		global_systemInfoPtr->cycleCount++;
		waitForVBlank();

	}
}

/*
 *	static void initHeroDisplay(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Init for map display
 *
 *  RETURNS:			Nothing
 */
static void initHeroDisplay(void)
{
	//set BG mode
	*(vu16 *) REG_DISPCNT = DISP_MODE_4 | DISP_OBJ_BG_ALL_ON | DISP_OBJ_CHAR_2D_MAP;

	//DMA map palette
	DmaCopy(3, _binary_map_scaled_bin_start, BG_PLTT, PAL_256_SIZE, 16);

	//DMA horse pal/char
	DmaCopy(3, _binary_horse1_bin_start, OBJ_PLTT, PAL_16_SIZE, 16);
	DmaCopy(3, (_binary_horse1_bin_start + PAL_16_SIZE), OBJ_MODE4_VRAM, 16416-32, 16);

	//set default horse dir
	heroActor.direction = 0;

	//init OAM
	global_oamData[HERO_HORSE_OAM_INDEX].AffineMode = 0;
	global_oamData[HERO_HORSE_OAM_INDEX].CharNo 		= 512;

	//enable VCoutn function
	enableVCountInterrupt(85);
	setVCountFunction(updateMap);

	//set VBlank function
	setVBlankFunction(herosVBlankSyncFunction);
}

/*
 *	void herosVBlankSyncFunction(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Map scene VBlank function
 *
 *  RETURNS:			Nothing
 */
static void herosVBlankSyncFunction(void)
{
	//update hero's OAM
	global_oamData[HERO_HORSE_OAM_INDEX].HPos = heroActor.s3d.pos.x;
	global_oamData[HERO_HORSE_OAM_INDEX].VPos = heroActor.s3d.pos.y;
}

/*
 *	static void initHero(HERO_ACTOR *hero)
 *
 *  PARAMETERS:		hero:	Hero to init
 *
 *  DESCRIPTION:	Init's hero struct
 *
 *  RETURNS:			Nothing
 */
static void initHero(HERO_ACTOR *hero)
{
	long i;

	hero->s3d.pos.x = 100;
	hero->s3d.pos.y = 37;

	hero->xPosOffset = 0;
	hero->yPosOffset = 0;

	hero->mapXPos = 0;
	hero->mapYPos = 0;

	hero->mapScrollX = 0;
	hero->mapScrollY = 0;

	hero->direction = 0;

	//no units for hero
	for (i=0; i<MAX_UNIT_SLOTS; i++) {
		hero->unitSlots[i].unitSize = 0;
	}
}

/*
 *	static void updateHero(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Updates hero
 *
 *  RETURNS:			Nothing
 */
static void updateHero(void)
{
	short newDir;
	short xVel, yVel;

	//horse OAM frames
	char frames[8] =
	{
		0,		//0 Front
		4,		//1 Back
		8,		//2 Diag up/right
		12,		//3 Diag dw/right
		16,		//4 Right
		8,		//5 Diag up/left (FLIP)
		12,		//6 Diag dw/left (FLIP)
		16,		//7 Left (FLIP)
	};

	//init to no dir
	newDir = -1;

	//init vels
	xVel = yVel = 0;

	if (global_systemInfoPtr->controlPad & U_KEY) {
		newDir = 1;
		yVel = -1;
	}

	else if (global_systemInfoPtr->controlPad & D_KEY) {
		newDir = 0;
		yVel = 1;
	}

	if (global_systemInfoPtr->controlPad & L_KEY) {

		//up and left
		if (newDir == 1) {
			newDir = 5;
		}

		//down left
		else if (newDir == 0) {
			newDir = 6;
		}

		//left
		else {
			newDir = 7;
		}

		xVel = -1;
	}

	else if (global_systemInfoPtr->controlPad & R_KEY) {

		//up and right
		if (newDir == 1) {
			newDir = 2;
		}

		//down right
		else if (newDir == 0) {
			newDir = 3;
		}

		//right
		else {
			newDir = 4;
		}

		xVel = 1;
	}

	//no update if no dir change
	if (newDir != -1) {

		//change of dir?
		if (newDir != heroActor.direction) {

			heroActor.direction = newDir;

			global_oamData[HERO_HORSE_OAM_INDEX].CharNo = 512 + frames[newDir];

			if (heroActor.direction > 4) {
				global_oamData[HERO_HORSE_OAM_INDEX].HFlip = 1;
			}
			else {
				global_oamData[HERO_HORSE_OAM_INDEX].HFlip = 0;
			}
		}

		//apply movement vel
		else {

			heroActor.s3d.pos.x += xVel;
			heroActor.s3d.pos.y += yVel;

			//clamp X dir
			if (heroActor.s3d.pos.x <= 8) {
				heroActor.s3d.pos.x = 8;
			}
			else if ((heroActor.s3d.pos.x + heroActor.xPosOffset) >= 2250) {
				heroActor.s3d.pos.x = 2250;
			}
			else if (heroActor.s3d.pos.x >= 144) {
				heroActor.mapScrollX = 64;
			}

			else if (heroActor.s3d.pos.x <= 60) {
				heroActor.mapScrollX = -64;
			}

			//clamp Y dir
			if (heroActor.s3d.pos.y <= 8) {
				heroActor.s3d.pos.y = 8;
			}
			else if ((heroActor.s3d.pos.y + heroActor.yPosOffset) >= 2192) {
				heroActor.s3d.pos.y = 2192;
			}
			else if (heroActor.s3d.pos.y >= 116) {
				heroActor.mapScrollY = 64;
			}

			else if (heroActor.s3d.pos.y <= 32) {
				heroActor.mapScrollY = -64;
			}

		}
	}
}

/*
 *	static void updateMap(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	VCount IRQ function to update map
 *
 *  RETURNS:			Nothing
 */
static void updateMap(void)
{
	long y;
	long tempPos;
	GENPTR imagePtr;
	GENPTR vramPtr;
	long vramOffset = 240;
	long imageOffset = 2304;

	if (!disableVCountProcessing) {

		//if (mapLCDFlag)
		//	setLCDOff();

		//update map X dir
		if (heroActor.mapScrollX) {

			if (heroActor.mapScrollX > 0)
				y = 4;
			else
				y = -4;

			tempPos = (heroActor.mapXPos + y);

			//did we scroll over?
			if (tempPos > 2064) {

				//set map to max pos
				heroActor.mapXPos = 2064;
				heroActor.mapScrollX = 0;
			}

			else if (tempPos < 0) {

				//set map to min pos
				heroActor.mapXPos = 0;
				heroActor.mapScrollX = 0;
			}

			else {

				heroActor.mapXPos 		 = tempPos;
				heroActor.s3d.pos.x 	-= y;
				heroActor.xPosOffset 	+= y;
				heroActor.mapScrollX 	-= y;
			}
		}

		//update map Y dir
		if (heroActor.mapScrollY) {

			if (heroActor.mapScrollY > 0)
				y = 4;
			else
				y = -4;

			tempPos = (heroActor.mapYPos + y);

			//did we scroll over?
			if (tempPos > 2064) {

				//set map to max pos
				heroActor.mapYPos = 2064;
				heroActor.mapScrollY = 0;
			}

			else if (tempPos < 0) {

				//set map to min pos
				heroActor.mapYPos = 0;
				heroActor.mapScrollY = 0;
			}

			else {

				heroActor.mapYPos 		= tempPos;
				heroActor.s3d.pos.y 	-= y;
				heroActor.yPosOffset 	+= y;
				heroActor.mapScrollY 	-= y;
			}
		}

		imagePtr.uc = (u_char *) _binary_map_scaled_bin_start + PAL_256_SIZE;

		imagePtr.uc += (heroActor.mapYPos * imageOffset);

		vramPtr.l = (long *) BG_BITMAP0_VRAM;

		for (y=0; y<160; y++) {

			//0
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//1
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//2
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//3
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//4
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//5
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//6
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;

			y++;

			//7
			DmaCopy(3, imagePtr.c + heroActor.mapXPos, vramPtr.c, MAX_MAP_WIDTH, 16);
			imagePtr.uc += imageOffset;
			vramPtr.c 	+= vramOffset;
		}

		//if (mapLCDFlag)
		//	setLCDOn();
	}
}

