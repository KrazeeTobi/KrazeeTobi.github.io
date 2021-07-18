/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "main.h"
#include "cursor.h"
#include "units.h"
#include "heros.h"
#include "battle.h"

#include "art\heroart.h"
#include "art\cursors\icons_16.c"

/*
 Obj VRAM:
	14 Units @ 64x32x16 = 1024/unit 	= 14336	(0x3800)
	2  Heros @ 16x32x16 = 256/heros 	= 512  	(0x0200)
	8 Cursors    @ 16x16x16 					= 1024 	(0x0400)
	1 Projectile @ 32x32x16 			   	= 512  	(0x0200)
														 ----------------
															Total = 16384	(0x4000)
*/

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================
extern char _binary_grass_chr_start[26880];
extern char _binary_grass_map_start[2048];
extern char _binary_grass_pal_start[512];

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
//battle horse defs
#define BATTLE_HORSE_CHR_SIZE			(256)

#define BATTLE_HORSE_1_X_POS			(1)
#define BATTLE_HORSE_1_Y_POS			(7)
#define BATTLE_HORSE_1_OAM_INDEX 	(7)
#define BATTLE_HORSE_1_OBJ_OFFSET	(224*2)
#define BATTLE_HORSE_1_CHR_ADDR		(OBJ_MODE0_VRAM + (BATTLE_HORSE_1_OBJ_OFFSET * 32))
#define BATTLE_HORSE_1_PAL_INDEX	(12)
#define BATTLE_HORSE_1_PAL_ADDR		(OBJ_PLTT + (BATTLE_HORSE_1_PAL_INDEX * PAL_16_SIZE))

#define BATTLE_HORSE_2_X_POS			(223)
#define BATTLE_HORSE_2_Y_POS			(7)
#define BATTLE_HORSE_2_OAM_INDEX  (BATTLE_HORSE_1_OAM_INDEX + 1)
#define BATTLE_HORSE_2_OBJ_OFFSET	(BATTLE_HORSE_1_OBJ_OFFSET       + 8)
#define BATTLE_HORSE_2_CHR_ADDR		(OBJ_MODE0_VRAM + (BATTLE_HORSE_2_OBJ_OFFSET * 32))
#define BATTLE_HORSE_2_PAL_INDEX	(BATTLE_HORSE_1_PAL_INDEX + 1)
#define BATTLE_HORSE_2_PAL_ADDR		(OBJ_PLTT + (BATTLE_HORSE_2_PAL_INDEX * PAL_16_SIZE))

//battle cursor defs
#define BATTLE_CURSOR_CHR_SIZE		(1024) //8 cursors @ 16x16x16
#define BATTLE_CURSOR_OAM_INDEX		(9)
#define BATTLE_CURSOR_OBJ_OFFSET	(256*2)
#define BATTLE_CURSOR_CHR_ADDR		(OBJ_MODE0_VRAM + (BATTLE_CURSOR_OBJ_OFFSET * 32))
#define BATTLE_CURSOR_PAL_INDEX		(14)
#define BATTLE_CURSOR_PAL_ADDR		(OBJ_PLTT + (BATTLE_CURSOR_PAL_INDEX * PAL_16_SIZE))
#define BATTLE_CURSOR_X_OFFSET		(8  << FIXED_POINT_SHIFT)
#define BATTLE_CURSOR_Y_OFFSET		(16 << FIXED_POINT_SHIFT)

#define BATTLE_CURSOR_MOVE_VEL		(1 << FIXED_POINT_SHIFT)

#define CURSOR_COLLISION_OFFSET 	(16 << FIXED_POINT_SHIFT)


//projectile defs
#define PROJECTILE_OAM_INDEX				(6)
#define PROJECTILE_OAM_CHAR_OFFSET	(240*2)
#define PROJECTILE_VELOCITY					(2 << FIXED_POINT_SHIFT)

//misc defs
#define BATTLE_OAM_INDEX_START		(10)
#define BATTLE_OAM_CHAR_OFFSET		(32)
#define BATTLE_OBJ_VRAM_OFFSET		(BATTLE_OAM_CHAR_OFFSET * BATTLE_OAM_CHAR_OFFSET)

#define BATTLE_ATTACKER_VRAM_START (OBJ_MODE0_VRAM)
#define BATTLE_DEFENDER_VRAM_START (BATTLE_ATTACKER_VRAM_START + (MAX_UNIT_SLOTS * BATTLE_OBJ_VRAM_OFFSET))

#define ATTACKER_X_POS						(18)
#define DEFENDER_X_POS						(190)
#define UNIT_Y_POS								(6)
#define UNIT_Y_OFFSET							(24)

#define UNIT_FLASH_DELAY					(15)
#define UNIT_ANIM_DELAY						(8)
#define UNIT_MOVE_VELOCITY 				(1 << 11)

#define UNIT_SPEED_MODIFIER				(8 		<< FIXED_POINT_SHIFT)
#define MAX_EFFECTIVE_SHOT_RANGE 	(130 	<< FIXED_POINT_SHIFT)
#define MIN_EFFECTIVE_SHOT_RANGE 	(24 	<< FIXED_POINT_SHIFT)


// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================
static void battleVBlankSyncFunction(void);

static void initHeroForBattle(HERO_ACTOR *heroPtr, BATTLE_STATUS battleStatus);
static void initHeroBattleHorse(HERO_ACTOR *hero, BATTLE_STATUS battleStatus);
static void updateBattleUnitsOam(void);

static void initBattleCursor(void);
static BATTLE_UNIT *updateBattleCursor(BATTLE_UNIT *attackerPtr);
static BATTLE_UNIT *getBattleCursorTarget(void);

static void initProjectile(PROJECTILE *projectilePtr, BATTLE_UNIT *shooterPtr, BATTLE_UNIT *targetPtr);
static void updateBattleProjectiles(PROJECTILE *projectilePtr);

static void setBattleUnitAnim(BATTLE_UNIT *battleUnitPtr, UNIT_ANIM_ID animID);
static void setBattleUnitAnimImmediate(BATTLE_UNIT *battleUnitPtr, UNIT_ANIM_ID animID);
static void updateBattleUnitAnims(void);

static UNIT_ACTION_ID getBattleUnitAction(BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT **targetUnitPtr);
static void doBattleUnitAction(UNIT_ACTION_ID actionID, BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT *targetUnitPtr);
static void resolveMeleeDamage(BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT *targetUnitPtr);

static void moveUnitToCursor(BATTLE_UNIT *battleUnitPtr);

//static void debug_moveBattleUnitWithController(BATTLE_UNIT *battleUnitPtr);


// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================
static PROJECTILE projectile;
static BATTLE_GROUP battleGroups[MAX_BATTLE_STATUS];

static const U8_XY_POS battlePositions[MAX_BATTLE_STATUS][MAX_UNIT_SLOTS] =
{
	//ATTACKER
	{
		//UNIT_SLOT_0
		{
			ATTACKER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 0),
		},
		//UNIT_SLOT_1
		{
			ATTACKER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 1),
		},
		//UNIT_SLOT_2
		{
			ATTACKER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 2),
		},
		//UNIT_SLOT_3
		{
			ATTACKER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 3),
		},
		//UNIT_SLOT_4
		{
			ATTACKER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 4),
		},
		//UNIT_SLOT_5
		{
			ATTACKER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 5),
		},
		//UNIT_SLOT_6
		{
			ATTACKER_X_POS - 10,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 3),
		}
	},

	//DEFENDER
	{
		//UNIT_SLOT_0
		{
			DEFENDER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 0),
		},
		//UNIT_SLOT_1
		{
			DEFENDER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 1),
		},
		//UNIT_SLOT_2
		{
			DEFENDER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 2),
		},
		//UNIT_SLOT_3
		{
			DEFENDER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 3),
		},
		//UNIT_SLOT_4
		{
			DEFENDER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 4),
		},
		//UNIT_SLOT_5
		{
			DEFENDER_X_POS,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 5),
		},
		//UNIT_SLOT_6
		{
			DEFENDER_X_POS - 10,
			UNIT_Y_POS + (UNIT_Y_OFFSET * 3),
		},
	},
};

static const BATTLE_HORSE_INFO battleHorseInfo[MAX_BATTLE_STATUS] =
{
	//Horse Icon 1
	{
		BATTLE_HORSE_1_OAM_INDEX,
		BATTLE_HORSE_1_X_POS,
		BATTLE_HORSE_1_Y_POS,
		BATTLE_HORSE_1_OBJ_OFFSET,
		BATTLE_HORSE_1_PAL_INDEX,
	},
	//Horse Icon 2
	{
		BATTLE_HORSE_2_OAM_INDEX,
		BATTLE_HORSE_2_X_POS,
		BATTLE_HORSE_2_Y_POS,
		BATTLE_HORSE_2_OBJ_OFFSET,
		BATTLE_HORSE_2_PAL_INDEX,
	},
};


/*
 *	void beginBattle(HERO_ACTOR *attackerPtr, HERO_ACTOR *defenderPtr)
 *
 *  PARAMETERS:		attacker:	Attacking hero
 *                defender:	Defending hero
 *
 *  DESCRIPTION:	Begins test battle
 *
 *  RETURNS:			Nothing
 */
void beginBattle(HERO_ACTOR *attackerPtr, HERO_ACTOR *defenderPtr)
{
	long i;
	BATTLE_UNIT *targetUnitPtr = NULL;
	UNIT_ACTION_ID actionID;
	long doBattle = 1;

	setVBlankFunction(battleVBlankSyncFunction);

	*(vu16 *) REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_BG_ALL_ON | DISP_OBJ_CHAR_1D_MAP;

	//DMA BG
	DmaCopy(3, _binary_grass_pal_start, BG_PLTT, PAL_256_SIZE, 16);
	DmaCopy(3, _binary_grass_chr_start, BG_VRAM+(1024*16), 26880, 16);
	DmaCopy(3, _binary_grass_map_start, BG_VRAM, 2048, 16);

	//set BG0
	*(vu16 *) REG_BG0CNT = ((1 << BG_CHAR_BASE_SHIFT) | (BG_COLOR_256));

	//init cursor
	initBattleCursor();

	setOamIndexOff(BATTLE_CURSOR_OAM_INDEX);

	//init battle groups
	memset(battleGroups, 0, sizeof(BATTLE_GROUP) * MAX_BATTLE_STATUS);

	//add units to attacker
	addUnitToHero(attackerPtr, UNIT_SLOT_0, ARCHER,   20);
	addUnitToHero(attackerPtr, UNIT_SLOT_2, CAVALIER, 20);
	addUnitToHero(attackerPtr, UNIT_SLOT_3, MONK, 	  20);
	initHeroForBattle(attackerPtr, ATTACKING);

	//add units to defender
	addUnitToHero(defenderPtr, UNIT_SLOT_0, CAVALIER,  5);
	addUnitToHero(defenderPtr, UNIT_SLOT_2, ARCHER,   15);
	addUnitToHero(defenderPtr, UNIT_SLOT_4, SWORDSMAN, 20);
	initHeroForBattle(defenderPtr, DEFENDING);

	//allow OAM updates
	global_systemInfoPtr->updateOAM = 1;

	//fade in
	fadeIn(BLD_ALL);

	//turn cursor on and activate
	setOamIndexOn(BATTLE_CURSOR_OAM_INDEX);
	global_cursorActorPtr->cursorActive = 1;

	while (doBattle) {

		for (i=0; i<MAX_UNIT_SLOTS; i++) {

			if (battleGroups[ATTACKING].battleUnits[i].unitActive) {

				actionID = getBattleUnitAction(&battleGroups[ATTACKING].battleUnits[i], &targetUnitPtr);

				//cheesy exit for now
				if (actionID == UNIT_ACTION_EXIT)	{
					doBattle = 0;
					break;
				}

				doBattleUnitAction(actionID, &battleGroups[ATTACKING].battleUnits[i], targetUnitPtr);
			}
		}
	}

	setVBlankFunction(NULL);

	//fade out
	fadeOut(BLD_ALL);

	//init OAM to default
	initOamBuffer();

}

/*
 *	static void battleVBlankSyncFunction(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Battle sequence VBlank function
 *
 *  RETURNS:			Nothing
 */
static void battleVBlankSyncFunction(void)
{
	//update units
	updateBattleUnitAnims();
	updateBattleUnitsOam();

	//update cursor if active
	if (global_cursorActorPtr->cursorActive) {

		global_cursorActorPtr->oamDataPtr->HPos 		= FIXED_PT_DN(global_cursorActorPtr->xPos);
		global_cursorActorPtr->oamDataPtr->VPos 		= FIXED_PT_DN(global_cursorActorPtr->yPos);
		global_cursorActorPtr->oamDataPtr->CharNo 	= (global_cursorActorPtr->cursorType + BATTLE_CURSOR_OBJ_OFFSET);

		if (global_cursorActorPtr->onOffFlag == ON) {
			setOamIndexOn(BATTLE_CURSOR_OAM_INDEX);
		}
		else {
			setOamIndexOff(BATTLE_CURSOR_OAM_INDEX);
		}
	}
}

/*
 *	static void initHeroForBattle(HERO_ACTOR *heroPtr, BATTLE_STATUS battleStatus)
 *
 *  PARAMETERS:		heroPtr:			Hero to init for battle
 *								battleStatus:	Hero's battleStatus (ATTACKING or DEFENDING)
 *
 *  DESCRIPTION:	Inits hero for battle
 *
 *  RETURNS:			Nothing
 */
static void initHeroForBattle(HERO_ACTOR *heroPtr, BATTLE_STATUS battleStatus)
{
	BATTLE_UNIT *battleUnitPtr;
	UNIT_SLOT 	*unitSlotsPtr;
	long i;
	long oamOffset;
	long palette;
	long charIndex;
	long vramAddr;

	//init Hero's Horse
	initHeroBattleHorse(heroPtr, battleStatus);

	//set hero ptr
	battleGroups[battleStatus].heroPtr = heroPtr;

	//init ptrs
	battleUnitPtr = battleGroups[battleStatus].battleUnits;
	unitSlotsPtr 	= heroPtr->unitSlots;

	//which side are we setting up?
	if (battleStatus == ATTACKING) {
		oamOffset 		= BATTLE_OAM_INDEX_START;
		palette 			= 0;
		charIndex			= 0;
		vramAddr			= OBJ_MODE0_VRAM;
	}
	else {
		oamOffset 		= (BATTLE_OAM_INDEX_START + MAX_UNIT_SLOTS);
		palette 			= MAX_UNIT_SLOTS;
		charIndex			= (BATTLE_OAM_CHAR_OFFSET * MAX_UNIT_SLOTS);
		vramAddr			= OBJ_MODE0_VRAM + (MAX_UNIT_SLOTS * BATTLE_OBJ_VRAM_OFFSET);
	}

	//loop through all slots and init units
	for (i=0; i<MAX_UNIT_SLOTS; i++, battleUnitPtr++, unitSlotsPtr++) {

		//make sure we have units
		if (unitSlotsPtr->unitSize) {

			//init ptrs
			battleUnitPtr->unitSlot	 	 = unitSlotsPtr;
			battleUnitPtr->animInfoPtr = unitSlotsPtr->unitInfoPtr->animInfoPtr;
			battleUnitPtr->unitStatPtr = unitSlotsPtr->unitInfoPtr->unitStatPtr;

			//init unit info
			battleUnitPtr->oamSlot			= oamOffset;
			battleUnitPtr->animID     	= UNIT_IDLE_ANIM;
			battleUnitPtr->onOffFlag		= ON;
			battleUnitPtr->animFrame		= 0;
			battleUnitPtr->animDelay		= UNIT_ANIM_DELAY;
			battleUnitPtr->unitActive		= ON;
			battleUnitPtr->defending		= OFF;
			battleUnitPtr->battleStatus = battleStatus;
			battleUnitPtr->shotsLeft		= battleUnitPtr->unitStatPtr->shots;
			battleUnitPtr->health				= battleUnitPtr->unitStatPtr->health;

			//init pos
			battleUnitPtr->xPos					= FIXED_PT_UP(battlePositions[battleStatus][i].x);
			battleUnitPtr->yPos					= FIXED_PT_UP(battlePositions[battleStatus][i].y);

			//compensate for 64x32 sprites by adjusting xpos
			if (battleUnitPtr->unitSlot->unitInfoPtr->objShape == (OAM_H_RECTANGLE >> OAM_SHAPE_SHIFT)) {

				if (battleUnitPtr->unitSlot->unitInfoPtr->objSize == (OAM_SIZE_64x32  >> OAM_SIZE_SHIFT)) {
					battleUnitPtr->xPos -= FIXED_PT_UP(16);
				}
			}

			//update OAM
			global_oamData[battleUnitPtr->oamSlot].Shape 		= unitSlotsPtr->unitInfoPtr->objShape;
			global_oamData[battleUnitPtr->oamSlot].Size			= unitSlotsPtr->unitInfoPtr->objSize;
			global_oamData[battleUnitPtr->oamSlot].CharNo		= charIndex;
			global_oamData[battleUnitPtr->oamSlot].Pltt 		= palette;

			if (battleStatus == DEFENDING) {
				global_oamData[battleUnitPtr->oamSlot].HFlip = 1;
			}

			//DMA data
			DmaCopy(3, unitSlotsPtr->unitInfoPtr->paletteData, OBJ_PLTT + (palette * PAL_16_SIZE), PAL_16_SIZE, 16);
			DmaCopy(3, battleUnitPtr->animInfoPtr[UNIT_IDLE_ANIM].animFramePtr, vramAddr, unitSlotsPtr->unitInfoPtr->frameSize, 16);
		}

		//no units in slot
		else {
			//mark as un-used
			battleUnitPtr->onOffFlag  = OFF;
			battleUnitPtr->unitActive = OFF;
		}

		//inc for next oam slot
		oamOffset++;

		//and update data offsets
		vramAddr 	+= BATTLE_OBJ_VRAM_OFFSET;
		charIndex += BATTLE_OAM_CHAR_OFFSET;
		palette++;
	}
}

/*
 *	static void initHeroBattleHorse(HERO_ACTOR *hero, BATTLE_STATUS battleStatus)
 *
 *  PARAMETERS:		heroPtr:			Hero
 *								battleStatus:	Hero's battleStatus (ATTACKING or DEFENDING)
 *
 *  DESCRIPTION:	Inits horse for hero
 *
 *  RETURNS:			Nothing
 */
static void initHeroBattleHorse(HERO_ACTOR *hero, BATTLE_STATUS battleStatus)
{
	OamData *oamPtr;

	oamPtr = &global_oamData[	battleHorseInfo[battleStatus].oamIndex ];

	//init OAM
	oamPtr->HPos 		= battleHorseInfo[battleStatus].xPos;
	oamPtr->VPos 		= battleHorseInfo[battleStatus].yPos;
	oamPtr->CharNo	= battleHorseInfo[battleStatus].charIndex;
	oamPtr->Pltt 		= battleHorseInfo[battleStatus].paletteIndex;
	oamPtr->Shape		= (OAM_V_RECTANGLE >> OAM_SHAPE_SHIFT);
	oamPtr->Size		= (OAM_SIZE_16x32  >> OAM_SIZE_SHIFT);

	//turn OBJ on
	setOamIndexOn(battleHorseInfo[battleStatus].oamIndex);

	//DMA battle horse
	if (battleStatus == ATTACKING) {
		DmaCopy(3,  _binary_female_battle_horse_bin_start,  BATTLE_HORSE_1_PAL_ADDR, PAL_16_SIZE, 16);
		DmaCopy(3, (_binary_female_battle_horse_bin_start + PAL_16_SIZE), BATTLE_HORSE_1_CHR_ADDR, BATTLE_HORSE_CHR_SIZE, 16);
	}
	else {
		DmaCopy(3,  _binary_female_goblin_battle_horse_bin_start,  BATTLE_HORSE_2_PAL_ADDR, PAL_16_SIZE, 16);
		DmaCopy(3, (_binary_female_goblin_battle_horse_bin_start + PAL_16_SIZE), BATTLE_HORSE_2_CHR_ADDR, BATTLE_HORSE_CHR_SIZE, 16);
	}
}

/*
 *	static void setBattleUnitAnim(BATTLE_UNIT *battleUnitPtr, UNIT_ANIM_ID animID)
 *
 *  PARAMETERS:		battleUnitPtr:	Unit to set anim
 *                animID:					Anim to set
 *
 *  DESCRIPTION:	Sets battle unit's anim
 *
 *  RETURNS:			Nothing
 */
static void setBattleUnitAnim(BATTLE_UNIT *battleUnitPtr, UNIT_ANIM_ID animID)
{
	battleUnitPtr->animID 		= animID;
	battleUnitPtr->animDelay 	= UNIT_ANIM_DELAY;
	battleUnitPtr->animFrame	= 0;
}

/*
 *	static void setBattleUnitAnimImmediate(BATTLE_UNIT *battleUnitPtr, UNIT_ANIM_ID animID)
 *
 *  PARAMETERS:		battleUnitPtr:	Unit to set anim
 *                animID:					Anim to set
 *
 *  DESCRIPTION:	Sets battle unit's anim with no anim delay
 *
 *  RETURNS:			Nothing
 */
static void setBattleUnitAnimImmediate(BATTLE_UNIT *battleUnitPtr, UNIT_ANIM_ID animID)
{
	battleUnitPtr->animID 		= animID;
	battleUnitPtr->animDelay 	= 1;
	battleUnitPtr->animFrame	= 0;
}

/*
 *	static void updateBattleUnitAnims(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Updates current battle unit's anims
 *
 *  RETURNS:			Nothing
 */
static void updateBattleUnitAnims(void)
{
	long i;
	long animFrame;
	BATTLE_UNIT *battleUnitPtr;
	BATTLE_STATUS battleStatus = ATTACKING;

	while (battleStatus < MAX_BATTLE_STATUS) {

		//grab unit ptr
		battleUnitPtr = battleGroups[battleStatus].battleUnits;

		for (i=0; i<MAX_UNIT_SLOTS; i++, battleUnitPtr++) {

			if (battleUnitPtr->unitActive) {

				battleUnitPtr->animDelay--;

				if (battleUnitPtr->animDelay == 0) {

					battleUnitPtr->animDelay = UNIT_ANIM_DELAY;

					battleUnitPtr->animFrame++;

					if (battleUnitPtr->animFrame >= battleUnitPtr->animInfoPtr[battleUnitPtr->animID].numFrames) {

						//check for anim transitions...
						if (battleUnitPtr->animID == UNIT_IDLE_TO_WALK_ANIM) {
							battleUnitPtr->animID = UNIT_WALK_ANIM;
						}

						//if dead, then deactivate and continue
						else if (battleUnitPtr->animID == UNIT_DIE_ANIM) {
							battleUnitPtr->unitActive = OFF;

							//HACK: flag as idle, but is really dead
							battleUnitPtr->animID = UNIT_IDLE_ANIM;
							continue;
						}

						else if (battleUnitPtr->animID != UNIT_WALK_ANIM) {
							battleUnitPtr->animID = UNIT_IDLE_ANIM;
						}

						battleUnitPtr->animFrame = 0;
					}

					animFrame = battleUnitPtr->animInfoPtr[battleUnitPtr->animID].animSeq[battleUnitPtr->animFrame];

					if (battleStatus == ATTACKING) {
						DmaCopy(3, battleUnitPtr->animInfoPtr[battleUnitPtr->animID].animFramePtr + (animFrame * battleUnitPtr->unitSlot->unitInfoPtr->frameSize),
											BATTLE_ATTACKER_VRAM_START + (i * BATTLE_OBJ_VRAM_OFFSET), battleUnitPtr->unitSlot->unitInfoPtr->frameSize, 16);
					}

					else {
						DmaCopy(3, battleUnitPtr->animInfoPtr[battleUnitPtr->animID].animFramePtr + (animFrame * battleUnitPtr->unitSlot->unitInfoPtr->frameSize),
											BATTLE_DEFENDER_VRAM_START + (i * BATTLE_OBJ_VRAM_OFFSET), battleUnitPtr->unitSlot->unitInfoPtr->frameSize, 16);
					}
				}
			}
		}

		//inc battlestatus
		battleStatus++;
	}
}

/*
 *	static void updateBattleUnitsOam(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Updates battle unit's OAM
 *
 *  RETURNS:			Nothing
 */
static void updateBattleUnitsOam(void)
{
	long i;
	BATTLE_UNIT *battleUnitPtr;
	OamData 		*oamPtr;
	BATTLE_STATUS battleStatus = ATTACKING;

	while (battleStatus < MAX_BATTLE_STATUS) {

		//grab ptrs
		battleUnitPtr = battleGroups[battleStatus].battleUnits;
		oamPtr 				= &global_oamData[battleUnitPtr->oamSlot];

		//update OAM pos
		for (i=0; i<MAX_UNIT_SLOTS; i++, battleUnitPtr++, oamPtr++) {

			oamPtr->HPos = FIXED_PT_DN(battleUnitPtr->xPos);
			oamPtr->VPos = FIXED_PT_DN(battleUnitPtr->yPos);

			//update ON/OFF
			if (battleUnitPtr->onOffFlag == OFF) {
				setOamIndexOff(battleUnitPtr->oamSlot);
			}
			else {
				setOamIndexOn(battleUnitPtr->oamSlot);
			}
		}

		//inc battlestatus
		battleStatus++;
	}
}

/*
 *	static void initBattleCursor(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Init's the cursor for battle
 *
 *  RETURNS:			Nothing
 */
static void initBattleCursor(void)
{
	OamData *oamPtr;

	//DMA cursor data
	DmaCopy(3, icons_16_Palette, BATTLE_CURSOR_PAL_ADDR, PAL_16_SIZE, 16);
	DmaCopy(3, icons_16_Char, BATTLE_CURSOR_CHR_ADDR, BATTLE_CURSOR_CHR_SIZE, 16);

	//init OAM for cursor
	oamPtr = &global_oamData[BATTLE_CURSOR_OAM_INDEX];

	oamPtr->Shape				= (OAM_SQUARE >> OAM_SHAPE_SHIFT);
	oamPtr->Size 				= (OAM_SIZE_16x16 >> OAM_SIZE_SHIFT);
	oamPtr->AffineMode 	= 0;
	oamPtr->Pltt 				= BATTLE_CURSOR_PAL_INDEX;

	//Set global cursor ptr
	global_cursorActorPtr = &global_cursorActor;

	//default cursor to no good
	global_cursorActorPtr->cursorType = NO_SYMBOL_CURSOR;
	//global_cursorActorPtr->cursorActive = 1;

	//init cursor
	initCursor(global_cursorActorPtr, FIXED_PT_UP(120), FIXED_PT_UP(80), MOVE_CURSOR, BATTLE_CURSOR_OAM_INDEX);
}

/*
 *	static BATTLE_UNIT *updateBattleCursor(BATTLE_UNIT *attackerPtr)
 *
 *  PARAMETERS:		attackerPtr: Unit that is targeting
 *
 *  DESCRIPTION:	Determines appropriate targeting icon
 *
 *  RETURNS:			Pointer to unit currently targeted
 */
static BATTLE_UNIT *updateBattleCursor(BATTLE_UNIT *attackerPtr)
{

	BATTLE_UNIT *targetUnitPtr;
	long xDist, yDist;
	long unitSpeed;
	BOOL inRange = FALSE;

	//get distance from cursor
	xDist = (global_cursorActorPtr->xPos - BATTLE_CURSOR_X_OFFSET) - attackerPtr->xPos;
	yDist = (global_cursorActorPtr->yPos - BATTLE_CURSOR_Y_OFFSET) - attackerPtr->yPos;

	//determine unit speed
	unitSpeed = (attackerPtr->unitStatPtr->speed * UNIT_SPEED_MODIFIER);

	//check if in walking range
	if ( (abs(xDist) < unitSpeed) && (abs(yDist) < unitSpeed) ) {
		inRange = TRUE;
	}

	//get cursor target (if any)
	targetUnitPtr = getBattleCursorTarget();

	//default cursor to no good
	global_cursorActorPtr->cursorType = NO_SYMBOL_CURSOR;

	if (targetUnitPtr) {

		//check if targeting self or friendly unit
		if ( (targetUnitPtr == attackerPtr) || (targetUnitPtr->battleStatus == attackerPtr->battleStatus) ) {
			global_cursorActorPtr->cursorType = QUESTION_CURSOR;
		}

		//any ranged weapons left?
		else if (attackerPtr->shotsLeft) {

			//too close for shots?
			if ( (abs(xDist) < MIN_EFFECTIVE_SHOT_RANGE) && (abs(yDist) < MIN_EFFECTIVE_SHOT_RANGE) ) {
				//sword cursor
				global_cursorActorPtr->cursorType = SWORD_CURSOR_DIAG;
			}

			//in effective range?
			else if ( (abs(xDist) < MAX_EFFECTIVE_SHOT_RANGE) && (abs(yDist) < MAX_EFFECTIVE_SHOT_RANGE) ) {
				//arrow cursor
				global_cursorActorPtr->cursorType = ARROW_CURSOR;
			}

			//out of effective range, but can still shoot
			else {
				//broken arrow cursor
				global_cursorActorPtr->cursorType = BROKEN_ARROW_CURSOR;
			}
		}

		//in range to attack or move then attack
		else if (inRange) {
			//sword cursor
			global_cursorActorPtr->cursorType = SWORD_CURSOR_DIAG;
		}
	}

	//no target and in range to move
	else if (inRange) {
		//set cursor to move
		global_cursorActorPtr->cursorType = MOVE_CURSOR;
	}

	return (targetUnitPtr);
}

/*
 *	static BATTLE_UNIT *getBattleCursorTarget(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Checks if a unit is currently targeted
 *
 *  RETURNS:			Returns unit targeted, NULL if no target
 */
static BATTLE_UNIT *getBattleCursorTarget(void)
{
	BATTLE_STATUS battleStatus = ATTACKING;
	BATTLE_UNIT *battleUnitPtr;

	long xMin, xMax;
	long yMin, yMax;

	long cX, cY;
	long xSize, ySize;

	long i;

	xMin = global_cursorActorPtr->xPos;
	xMax = global_cursorActorPtr->xPos + CURSOR_COLLISION_OFFSET;

	yMin = global_cursorActorPtr->yPos;
	yMax = global_cursorActorPtr->yPos + CURSOR_COLLISION_OFFSET;

	while (battleStatus < MAX_BATTLE_STATUS) {

		//grab ptrs
		battleUnitPtr = battleGroups[battleStatus].battleUnits;

		//check each unit
		for (i=0; i<MAX_UNIT_SLOTS; i++, battleUnitPtr++) {

			if (battleUnitPtr->unitActive) {

				//compute X center pt of target (assuming 32 pixels wide)
				cX = battleUnitPtr->xPos;

				if (battleUnitPtr->unitSlot->unitInfoPtr->unitStatPtr->unitID == CAVALIER) {
					cX += FIXED_PT_UP(32);
					xSize = FIXED_PT_UP(16);
				}
				else {
					cX += FIXED_PT_UP(16);
					xSize = FIXED_PT_UP(8);
				}

				//compute Y center pt of target (assuming 32 pixels tall)
				cY = battleUnitPtr->yPos;
				cY += FIXED_PT_UP(16);
				ySize = FIXED_PT_UP(8);

				if ((	(cY + ySize) > yMin) && ((cY - ySize) < yMax)) {
					if ((	(cX + xSize) > xMin) && ((cX - xSize) < xMax)) {

						//return TARGET
						return (battleUnitPtr);
					}
				}
			}
		}

		//inc battlestatus
		battleStatus++;
	}

	//no target
	return (NULL);
}

/*
 *	static UNIT_ACTION_ID getBattleUnitAction(BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT **targetUnitPtr)
 *
 *  PARAMETERS:		battleUnitPtr:	Acting unit
 *								targetUnitPtr:  Acting unit's target
 *
 *  DESCRIPTION:	Determines unit's battle action
 *
 *  RETURNS:			Unit action
 */
static UNIT_ACTION_ID getBattleUnitAction(BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT **targetUnitPtr)
{
	long flashDelay = UNIT_FLASH_DELAY;
	UNIT_ACTION_ID unitAction = UNIT_ACTION_NONE;

	*targetUnitPtr = NULL;

	while (!unitAction) {

		//flash active unit for now
		if (--flashDelay == 0) {
			flashDelay = UNIT_FLASH_DELAY;
			battleUnitPtr->onOffFlag ^= 1;
		}

		//DEBUG
		#if 0
		if (global_systemInfoPtr->controlPad & L_BUTTON) {
			debug_moveBattleUnitWithController(battleUnitPtr);
		}
		else if (global_systemInfoPtr->controlPad & R_BUTTON) {
			debug_moveBattleUnitWithController(&battleGroups[DEFENDING].battleUnits[0]);
		}
		else {
			updateCursor(global_cursorActorPtr, global_systemInfoPtr->controlPad, FIXED_PT_UP(1));
		}
		#endif
		//DEBUG
		
		//check for fast cursor movement
		if (global_systemInfoPtr->controlPad & R_BUTTON) {
			updateCursor(global_cursorActorPtr, global_systemInfoPtr->controlPad, (BATTLE_CURSOR_MOVE_VEL * 2));
		}
		
		//update cursor at normal speed
		else {
			updateCursor(global_cursorActorPtr, global_systemInfoPtr->controlPad, BATTLE_CURSOR_MOVE_VEL);
		}

		//get target and update cursor
		*targetUnitPtr = updateBattleCursor(battleUnitPtr);

		//selection action
		if (global_systemInfoPtr->controlPadTrigger & A_BUTTON) {

			//walking
			if (global_cursorActorPtr->cursorType == MOVE_CURSOR) {
				unitAction = UNIT_ACTION_WALK;
			}

			//fighting
			else if (global_cursorActorPtr->cursorType == SWORD_CURSOR_DIAG) {
				unitAction = UNIT_ACTION_MELEE;
			}

			//shooting
			else if ( (global_cursorActorPtr->cursorType == ARROW_CURSOR) || (global_cursorActorPtr->cursorType == BROKEN_ARROW_CURSOR)) {
				unitAction = UNIT_ACTION_SHOOT;
			}

			//STILL NEED WALK->MELEE option
		}

		//unit defend
		else if (global_systemInfoPtr->controlPadTrigger & B_BUTTON) {
			unitAction = UNIT_ACTION_DEFEND;
		}

		//exit to map screen
		else if (global_systemInfoPtr->controlPadTrigger & START_BUTTON) {
			unitAction = UNIT_ACTION_EXIT;
		}

		waitForVBlank();
	}

	//force unit back on
	battleUnitPtr->onOffFlag = ON;

	//return current action
	return (unitAction);
}

/*
 *	void doBattleUnitAction(UNIT_ACTION_ID actionID, BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT *targetUnitPtr)
 *
 *  PARAMETERS:		actionID:				Action to perform
 *                battleUnitPtr:	Acting unit
 *                targetUnitPtr:	Acting unit's target
 *
 *  DESCRIPTION:	Performs unit action
 *
 *  RETURNS:			Nothing
 */
static void doBattleUnitAction(UNIT_ACTION_ID actionID, BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT *targetUnitPtr)
{
	long frameToReaction = 0;

	//Defending
	if (actionID == UNIT_ACTION_DEFEND) {
		battleUnitPtr->defending = ON;
		return;
	}

	//Walking
	else if (actionID == UNIT_ACTION_WALK) {
		moveUnitToCursor(battleUnitPtr);
		return;
	}

	//Meleeing
	else if (actionID == UNIT_ACTION_MELEE) {

		global_cursorActorPtr->onOffFlag = OFF;

		setBattleUnitAnim(battleUnitPtr, UNIT_MELEE_ATTACK_ANIM);
		frameToReaction = 4;

		while (battleUnitPtr->animFrame != frameToReaction) {
			waitForVBlank();
		}

		resolveMeleeDamage(battleUnitPtr, targetUnitPtr);

		global_cursorActorPtr->onOffFlag = ON;
	}

	//Shooting
	else if (actionID == UNIT_ACTION_SHOOT) {

		global_cursorActorPtr->onOffFlag = OFF;
		initProjectile(&projectile, battleUnitPtr, targetUnitPtr);

		while (projectile.onOffFlag) {
			updateBattleProjectiles(&projectile);
			waitForVBlank();
		}

		global_cursorActorPtr->onOffFlag = ON;
	}
}

/*
 *	static void resolveMeleeDamage(BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT *targetUnitPtr)
 *
 *  PARAMETERS:		battleUnitPtr:	Attacking unit
 *								targetUnitPtr:	targeted unit
 *
 *  DESCRIPTION:	Resolves damage to target
 *
 *  RETURNS:			Nothing
 */
static void resolveMeleeDamage(BATTLE_UNIT *battleUnitPtr, BATTLE_UNIT *targetUnitPtr)
{
	long damage = 0;
	long numKilled;
	long remainder;
	long i;

	//loop through all units and accum total damage
	for	(i=0; i<battleUnitPtr->unitSlot->unitSize; i++) {

		//need to figure out random gen. probs
		//damage += rangedRandom(battleUnitPtr->unitStatPtr->damageMin, battleUnitPtr->unitStatPtr->damageMax);

		//use min damage for now
		damage += battleUnitPtr->unitStatPtr->damageMin;
	}

	//get num units killed
	numKilled = damage / targetUnitPtr->unitStatPtr->health;
	remainder = damage % targetUnitPtr->unitStatPtr->health;

	//if nobody was killed, subtract damage from unit's health
	if (numKilled == 0) {
		targetUnitPtr->health -= damage;
	}

	//only a few were killed
	else if (numKilled < targetUnitPtr->unitSlot->unitSize) {
		targetUnitPtr->unitSlot->unitSize -= numKilled;
		targetUnitPtr->health -= remainder;
	}

	//unit wiped out completely
	else {

		//mark unit as empty
		targetUnitPtr->unitSlot->unitSize = 0;

		//mark unit no longer active
		//targetUnitPtr->unitActive = OFF;

		setBattleUnitAnim(targetUnitPtr, UNIT_DIE_ANIM);

		while (targetUnitPtr->animID != UNIT_IDLE_ANIM) {
			waitForVBlank();
		}

		return;
	}

	//start reaction
	if (targetUnitPtr->defending)
		setBattleUnitAnim(targetUnitPtr, UNIT_DEFEND_ANIM);
	else
		setBattleUnitAnim(targetUnitPtr, UNIT_HIT_ANIM);

	//wait for idle
	while (targetUnitPtr->animID != UNIT_IDLE_ANIM) {
		waitForVBlank();
	}
}

/*
 *	static void moveUnitToCursor(BATTLE_UNIT *battleUnitPtr)
 *
 *  PARAMETERS:		battleUnitPtr:	Unit moving
 *
 *  DESCRIPTION:	Moves unit to cursor
 *
 *  RETURNS:			Nothing
 */
static void moveUnitToCursor(BATTLE_UNIT *battleUnitPtr)
{

	long destX, destY;
	long xDist, yDist;
	long xVel, yVel;
	long timer;
	BOOL flipped = FALSE;

	destX = global_cursorActorPtr->xPos - BATTLE_CURSOR_X_OFFSET;
	destY = global_cursorActorPtr->yPos - BATTLE_CURSOR_Y_OFFSET;

	if (battleUnitPtr->unitSlot->unitInfoPtr->unitStatPtr->unitID == CAVALIER) {
		destX -= FIXED_PT_UP(16);
	}

	xDist = destX - battleUnitPtr->xPos;
	yDist = destY - battleUnitPtr->yPos;

	if (abs(xDist) > abs(yDist)) {
		timer = (abs(xDist) / UNIT_MOVE_VELOCITY);
		yVel  = (yDist / timer);

		if (xDist < 0) {
			xVel  = -UNIT_MOVE_VELOCITY;
		}
		else {
			xVel  = UNIT_MOVE_VELOCITY;
		}
	}
	else {
		timer = (abs(yDist) / UNIT_MOVE_VELOCITY);
		xVel  = (xDist / timer);

		if (yDist < 0) {
			yVel  = -UNIT_MOVE_VELOCITY;
		}
		else {
			yVel  = UNIT_MOVE_VELOCITY;
		}
	}

	//cheesy flip for now
	//since I don't have battlestatus right now, determine current facing dir
	//and check xvel...

	//if xvel < 0, and we are currently not flipped then flip to travel in neg x dir
	if ( (xVel < 0) && (global_oamData[battleUnitPtr->oamSlot].HFlip == 0)) {
		global_oamData[battleUnitPtr->oamSlot].HFlip ^= 1;
		flipped = TRUE;
	}

	//if xvel > 0, and we are currently flipped then flip to travel in pos x dir
	else if ( (xVel > 0) && (global_oamData[battleUnitPtr->oamSlot].HFlip == 1)) {
		global_oamData[battleUnitPtr->oamSlot].HFlip ^= 1;
		flipped = TRUE;
	}

	setBattleUnitAnim(battleUnitPtr, UNIT_IDLE_TO_WALK_ANIM);

	while (timer) {

		battleUnitPtr->xPos += xVel;
		battleUnitPtr->yPos += yVel;

		if (timer == 3) {
			setBattleUnitAnim(battleUnitPtr, UNIT_WALK_TO_IDLE_ANIM);
		}

		timer--;
		waitForVBlank();
	}

	//flip back if we flipped...
	if (flipped) {
		global_oamData[battleUnitPtr->oamSlot].HFlip ^= 1;
	}

	battleUnitPtr->xPos	= destX;
	battleUnitPtr->yPos = destY;
}

/*
 *	static void initProjectile(PROJECTILE *projectilePtr, BATTLE_UNIT *shooterPtr, BATTLE_UNIT *targetPtr)
 *
 *  PARAMETERS:		projectilePtr:	Projectile ptr
 *                shooterPtr:			Unit who is shooting
 *                targetPtr:			Unit targeted
 *
 *  DESCRIPTION:	Inits projectile fired from shooter to target
 *
 *  RETURNS:			Nothing
 */
static void initProjectile(PROJECTILE *projectilePtr, BATTLE_UNIT *shooterPtr, BATTLE_UNIT *targetPtr)
{
	long xDist, yDist;

	projectilePtr->shooterPtr = shooterPtr;
	projectilePtr->targetPtr  = targetPtr;

	projectilePtr->xPos = shooterPtr->xPos;
	projectilePtr->yPos = shooterPtr->yPos;

	xDist = targetPtr->xPos - projectilePtr->xPos;
	yDist = targetPtr->yPos - projectilePtr->yPos;

	if (abs(xDist) > abs(yDist)) {
		projectilePtr->timer 	= (abs(xDist) /  PROJECTILE_VELOCITY);
		projectilePtr->xVel 	= PROJECTILE_VELOCITY;
		projectilePtr->yVel 	= (yDist / projectilePtr->timer);
	}
	else {
		projectilePtr->timer 	= (abs(yDist) /  PROJECTILE_VELOCITY);
		projectilePtr->yVel 	= PROJECTILE_VELOCITY;
		projectilePtr->xVel 	= (xDist / projectilePtr->timer);
	}

	projectilePtr->onOffFlag 	= ON;
	projectilePtr->animFrame	= 0;
	projectilePtr->animDelay	= 0;

	DmaCopy(3, _binary_arrow_bin_start, OBJ_MODE0_VRAM + (PROJECTILE_OAM_CHAR_OFFSET * 32), 128, 16);

	global_oamData[PROJECTILE_OAM_INDEX].Shape	= (OAM_SQUARE >> OAM_SHAPE_SHIFT);
	global_oamData[PROJECTILE_OAM_INDEX].Size 	= (OAM_SIZE_16x16 >> OAM_SIZE_SHIFT);
	global_oamData[PROJECTILE_OAM_INDEX].CharNo	= PROJECTILE_OAM_CHAR_OFFSET;
	global_oamData[PROJECTILE_OAM_INDEX].Pltt 	= 0;

	setOamIndexOn(PROJECTILE_OAM_INDEX);

	setBattleUnitAnimImmediate(shooterPtr, UNIT_RANGED_ATTACK_ANIM);
}

/*
 *	static void updateBattleProjectiles(PROJECTILE *projectilePtr)
 *
 *  PARAMETERS:		projectilePtr:	Projectile pointer
 *
 *  DESCRIPTION:	Updates projectile
 *
 *  RETURNS:			Nothing
 */
static void updateBattleProjectiles(PROJECTILE *projectilePtr)
{
	if (projectilePtr->onOffFlag == ON) {

		if (projectilePtr->timer) {

			projectilePtr->timer--;

			projectilePtr->xPos += projectilePtr->xVel;
			projectilePtr->yPos += projectilePtr->yVel;

			global_oamData[PROJECTILE_OAM_INDEX].HPos = FIXED_PT_DN(projectilePtr->xPos) + 8;
			global_oamData[PROJECTILE_OAM_INDEX].VPos = FIXED_PT_DN(projectilePtr->yPos) + 8;
		}

		else {
			projectilePtr->onOffFlag = OFF;
			setOamIndexOff(PROJECTILE_OAM_INDEX);

			resolveMeleeDamage(projectilePtr->shooterPtr, projectilePtr->targetPtr);
		}
	}
}


#if 0
/*
 *	static void debug_moveBattleUnitWithController(BATTLE_UNIT *battleUnitPtr)
 *
 *  PARAMETERS:		battleUnitPtr:
 *
 *  DESCRIPTION:	Debug function to move battle unit
 *
 *  RETURNS:			Nothing
 */
static void debug_moveBattleUnitWithController(BATTLE_UNIT *battleUnitPtr)
{
	if (global_systemInfoPtr->controlPad & U_KEY) {
		battleUnitPtr->yPos -= FIXED_PT_UP(1);
	}

	else if (global_systemInfoPtr->controlPad & D_KEY) {
		battleUnitPtr->yPos += FIXED_PT_UP(1);
	}

	if (global_systemInfoPtr->controlPad & R_KEY) {
		battleUnitPtr->xPos += FIXED_PT_UP(1);
	}

	else if (global_systemInfoPtr->controlPad & L_KEY) {
		battleUnitPtr->xPos -= FIXED_PT_UP(1);
	}
}
#endif

