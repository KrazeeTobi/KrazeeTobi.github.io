/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _BATTLE_H
#define _BATTLE_H

/*-------------------------- defines ------------------------------ */
typedef enum BATTLE_STATUS
{
	ATTACKING = 0,
	DEFENDING,
	MAX_BATTLE_STATUS,

} BATTLE_STATUS;

/*-------------------------- structs ------------------------------ */
typedef struct _battle_unit
{
	long xPos;
	long yPos;

	//remove this later, we know which slot it is...
	//update slots after battle is complete
	UNIT_SLOT 			*unitSlot;

	UNIT_ANIM_INFO	*animInfoPtr;			//Anim info struct
	UNIT_STATS 			*unitStatPtr;			//Unit stat ptr
	UNIT_ANIM_ID 		animID;						//Current anim ID
	BATTLE_STATUS 	battleStatus;			//Battle status

	//make these chars?
	short	animFrame;
	short animDelay;

	u_char paletteSlot;				//Palette slot
	u_char oamSlot;						//Oam slot
	u_char onOffFlag;					//On/off flag
	u_char unitActive;				//Is unit active
	u_char defending;					//Is unit defending
	u_char shotsLeft;					//Num shots left
	u_char health;						//Current unit health

} BATTLE_UNIT;

typedef struct _battle_group
{
	HERO_ACTOR *heroPtr;
	BATTLE_UNIT battleUnits[MAX_UNIT_SLOTS];

} BATTLE_GROUP;

typedef struct _projectile
{
	BATTLE_UNIT *shooterPtr;
	BATTLE_UNIT *targetPtr;

	long xPos;
	long yPos;

	long xVel;
	long yVel;

	short timer;
	short	animFrame;
	short animDelay;

	u_char paletteSlot;
	u_char onOffFlag;

} PROJECTILE;

typedef struct _battle_horse_info
{
	short oamIndex;
	short xPos;
	short yPos;
	short charIndex;
	short paletteIndex;

} BATTLE_HORSE_INFO;

/*-------------------------- external functs -----------------------*/
extern void beginBattle(HERO_ACTOR *attackerPtr, HERO_ACTOR *defenderPtr);

/*-------------------------- external vars -------------------------*/

/*-------------------------- end -----------------------------------*/
#endif // _BATTLE_H
