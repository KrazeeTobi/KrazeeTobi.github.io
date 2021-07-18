/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _UNITS_H
#define _UNITS_H

/*-------------------------- defines ------------------------------ */
#define MAX_ANIM_FRAMES		(18)

typedef enum UNIT_SLOT_ID
{
	UNIT_SLOT_0 = 0,
	UNIT_SLOT_1,
	UNIT_SLOT_2,
	UNIT_SLOT_3,
	UNIT_SLOT_4,
	UNIT_SLOT_5,
	UNIT_SLOT_6,
	MAX_UNIT_SLOTS,

}	UNIT_SLOT_ID;

typedef enum UNIT_ID
{
	PIKEMAN	= 0,
	HALBERDIER,
	ARCHER,
	MARKSMAN,
	GRIFFIN,
	ROYAL_GRIFFIN,
	SWORDSMAN,
	CRUSADER,
	MONK,
	ZEALOT,
	CAVALIER,
	CHAMPION,
	ANGEL,
	ARCH_ANGEL,
	MAX_UNIT_ID,

} UNIT_ID;

typedef enum UNIT_ANIM_ID
{
	UNIT_IDLE_ANIM = 0,
	UNIT_IDLE_TO_WALK_ANIM,
	UNIT_WALK_ANIM,
	UNIT_WALK_TO_IDLE_ANIM,
	UNIT_RANGED_ATTACK_ANIM,
	UNIT_MELEE_ATTACK_ANIM,
	UNIT_DEFEND_ANIM,
	UNIT_HIT_ANIM,
	UNIT_DIE_ANIM,
	UNIT_MAX_ANIM,

} UNIT_ANIM_ID;

typedef enum UNIT_ACTION_ID
{
	UNIT_ACTION_NONE = 0,
	UNIT_ACTION_DEFEND,
	UNIT_ACTION_WALK,
	UNIT_ACTION_MELEE,
	UNIT_ACTION_SHOOT,
	UNIT_ACTION_WALK_MELEE,
	UNIT_ACTION_EXIT,
	UNIT_ACTION_MAX,

}	UNIT_ACTION_ID;

/*-------------------------- structs ------------------------------ */
typedef struct _unit_stats
{
	UNIT_ID	unitID;

	char 		attack;						//Attack str
	char 		defense;          //Defense str
	char 		shots;            //num shots
	u_char 	damageMin;        //Min damage
	u_char 	damageMax;        //Max damage
	u_char 	health;           //Health
	char 		unknown;          //
	char 		speed;            //Speed
	short 	unitCost;					//Unit cost

} UNIT_STATS;

typedef struct _unit_anim_info
{
	u_char 	*animFramePtr;
	u_char 	numFrames;
	char 		animSeq[MAX_ANIM_FRAMES];

} UNIT_ANIM_INFO;

typedef struct _unit_projectile
{
	u_char *charDataPtr;

	short frameSize;
	char objShape;
	char objSize;

} UNIT_PROJECTILE;

typedef struct _unit_info
{
	UNIT_STATS 			*unitStatPtr;
	UNIT_ANIM_INFO 	*animInfoPtr;
	UNIT_PROJECTILE *unitProjectilePtr;

	u_char 	*paletteData;
	short frameSize;
	char objShape;
	char objSize;

} UNIT_INFO;

typedef struct _unit_slot
{
	UNIT_INFO 	*unitInfoPtr;			//Unit info Ptr
	long 				unitSize;					//Unit size

} UNIT_SLOT;

//Hero structs
typedef struct _hero_info
{
	char attack;
	char defense;
	char spellPower;
	char knowledge;
	char speed;
	char spellPoints;

} HERO_INFO;

typedef struct _hero_actor
{
	HERO_INFO	heroInfo;
	UNIT_SLOT	unitSlots[MAX_UNIT_SLOTS];

  SPACE3D s3d;

	long xPosOffset;
	long yPosOffset;

	long mapXPos;
	long mapYPos;

	short mapScrollX;
	short mapScrollY;

	short direction;
	short destDirection;

	short animFrame;
	short animIndex;
	short animTick;

	char hFlip;
	char vFlip;

	short moveTick;
	short projectileDelay;

	short oamIndex;

	short flag;

} HERO_ACTOR;

/*-------------------------- external functs -----------------------*/
extern BOOL addUnitToHero(HERO_ACTOR *heroPtr, UNIT_SLOT_ID slotID, UNIT_ID unitID, short unitSize);

/*-------------------------- external vars -------------------------*/
extern UNIT_INFO unitInfo[MAX_UNIT_ID];

/*-------------------------- end -----------------------------------*/
#endif // _UNITS_H

