/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "main.h"
#include "units.h"

#include "art\heroart.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================

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

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================

static UNIT_STATS unitStats[MAX_UNIT_ID] =
{
	{
		PIKEMAN,					//Unit ID
		4,                //Attack
		5,                //Defense
		0,                //Shots
		1,                //Damage Min
		3,                //Damage Max
		10,               //Health
		0,                //?
		4,                //Speed
		60,								//Unit Cost
	},

	{
		HALBERDIER,				//Unit ID
		6,                //Attack
		5,                //Defense
		0,                //Shots
		2,                //Damage Min
		3,                //Damage Max
		10,               //Health
		0,                //?
		5,                //Speed
		75,								//Unit Cost

	},

	{
		ARCHER,						//Unit ID
		6,                //Attack
		3,                //Defense
		12,               //Shots
		2,                //Damage Min
		3,                //Damage Max
		10,               //Health
		0,                //?
		4,                //Speed
		100,							//Unit Cost
	},

	{
		MARKSMAN,					//Unit ID
		6,                //Attack
		3,                //Defense
		24,               //Shots
		2,                //Damage Min
		3,                //Damage Max
		10,               //Health
		0,                //?
		6,                //Speed
		150,							//Unit Cost
	},

	{
		GRIFFIN,					//Unit ID
		8,                //Attack
		8,                //Defense
		0,                //Shots
		3,                //Damage Min
		6,                //Damage Max
		25,               //Health
		0,                //?
		6,                //Speed
		200,							//Unit Cost
	},

	{
		ROYAL_GRIFFIN,		//Unit ID
		9,                //Attack
		9,                //Defense
		0,                //Shots
		3,                //Damage Min
		6,                //Damage Max
		25,               //Health
		0,                //?
		9,                //Speed
		240,							//Unit Cost
	},

	{
		SWORDSMAN,				//Unit ID
		10,               //Attack
		12,               //Defense
		0,                //Shots
		6,                //Damage Min
		9,                //Damage Max
		35,               //Health
		0,                //?
		5,                //Speed
		300,							//Unit Cost
	},

	{
		CRUSADER,					//Unit ID
		12,               //Attack
		12,               //Defense
		0,                //Shots
		7,                //Damage Min
		10,               //Damage Max
		35,               //Health
		0,                //?
		6,                //Speed
		400,							//Unit Cost
	},

	{
		MONK, 						//Unit ID
		12,               //Attack
		7,                //Defense
		12,               //Shots
		10,               //Damage Min
		12,               //Damage Max
		30,               //Health
		0,                //?
		5,                //Speed
		400,							//Unit Cost
	},

	{
		ZEALOT, 					//Unit ID
		12,               //Attack
		10,               //Defense
		24,               //Shots
		10,               //Damage Min
		12,               //Damage Max
		30,               //Health
		0,                //?
		7,                //Speed
		450,							//Unit Cost
	},

	{
		CAVALIER, 				//Unit ID
		15,               //Attack
		15,               //Defense
		0,                //Shots
		15,               //Damage Min
		25,               //Damage Max
		100,              //Health
		0,                //?
		7,                //Speed
		1000,							//Unit Cost
	},

	{
		CHAMPION, 				//Unit ID
		16,               //Attack
		16,               //Defense
		0,                //Shots
		20,               //Damage Min
		25,               //Damage Max
		100,              //Health
		0,                //?
		9,                //Speed
		1200,							//Unit Cost
	},

	{
		ANGEL, 						//Unit ID
		20,               //Attack
		20,               //Defense
		0,                //Shots
		50,               //Damage Min
		50,               //Damage Max
		200,              //Health
		0,                //?
		12,               //Speed
		2000,							//Unit Cost
	},

	{
		ARCH_ANGEL,				//Unit ID
		21,               //Attack
		23,               //Defense
		0,                //Shots
		55,               //Damage Min
		55,               //Damage Max
		200,              //Health
		0,                //?
		14,              	//Speed
		2500,							//Unit Cost
	},
};

static UNIT_ANIM_INFO archerAnims[UNIT_MAX_ANIM] =
{
	{
		_binary_archer_idle_bin_start,							//Idle Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},

	{
		_binary_archer_walk_bin_start,							//Idle to Walk Frames
		4,
		{0, 1, 2, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	},

	{
		_binary_archer_walk_bin_start,							//Walk Frames
		6,  //10
		{4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	},

	{
		_binary_archer_walk_bin_start,							//Walk To Idle Frames
		4,
		{3, 2, 1, 0, -1, -1, -1, -1, -1, -1, -1, -1, 12, 13, 14, 15, 16, 17},
	},

	{
		_binary_archer_shoot_bin_start,							//Ranged Frames
		9,  //5
		{0, 1, 2, 3, 4, 3, 2, 1, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0},
	},
	{
		_binary_archer_attack_bin_start,						//Melee Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	{
		_binary_archer_defend_bin_start,						//Defend Frames
		5,
		{0, 1, 2, 3, 4, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	{
		_binary_archer_react_bin_start,							//Hit Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	{
		_binary_archer_die_bin_start,								//Die Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
};

static UNIT_ANIM_INFO cavalierAnims[UNIT_MAX_ANIM] =
{
	{
		_binary_cavalier_idle_bin_start,						//Idle Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cav_walk_bin_start,									//Idle to Walk Frames
		3,
		{0, 1, 2, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cav_walk_bin_start,									//Walk Frames
		14,
		{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cav_walk_bin_start,									//Walk To Idle Frames
		3,
		{2, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cavalier_idle_bin_start,						//Ranged Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cavalier_attack_bin_start,					//Melee Frames
		9,
		{0, 1, 2, 3, 4, 5, 6, 7, 8, -1, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cav_defend_bin_start,								//Defend Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cav_react_bin_start,								//Hit Frames
		7,
		{0, 1, 2, 3, 4, 5, 6, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_cav_die_bin_start,									//Die Frames
		8,
		{0, 1, 2, 3, 4, 5, 6, 7, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
};

static UNIT_ANIM_INFO griffinAnims[UNIT_MAX_ANIM] =
{
	{
		_binary_griffin_idle_bin_start,							//Idle Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_griffin_idle_bin_start,							//Walk Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_griffin_idle_bin_start,							//Ranged Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_griffin_idle_bin_start,							//Melee Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_griffin_idle_bin_start,							//Defend Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_griffin_idle_bin_start,							//Hit Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_griffin_idle_bin_start,							//Die Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
};

static UNIT_ANIM_INFO monkAnims[UNIT_MAX_ANIM] =
{
	{
		_binary_monk_idle_bin_start,								//Idle Frames
		10, //5,
		{0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_walk_bin_start,								//Idle to Walk Frames
		2,
		{0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_walk_bin_start,								//Walk Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_walk_bin_start,								//Walk To Idle Frames
		2,
		{1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_shoot_bin_start,								//Ranged Frames
		5,
		{0, 1, 2, 3, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_shoot_bin_start,								//Melee Frames
		5,
		{0, 1, 2, 3, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_defend_bin_start,							//Defend Frames
		5,
		{0, 1, 2, 3, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_react_bin_start,								//Hit Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_monk_die_bin_start,									//Die Frames
		10,
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, 0, 0, 0, 0, 0, 0, -1},
	},
};

static UNIT_ANIM_INFO pikemanAnims[UNIT_MAX_ANIM] =
{
	{
		_binary_pikeman_idle_bin_start,							//Idle Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Idle to Walk Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Walk Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Walk To Idle Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Ranged Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Melee Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Defend Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Hit Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_pikeman_idle_bin_start,							//Die Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
};

static UNIT_ANIM_INFO swordmanAnims[UNIT_MAX_ANIM] =
{
	{
		_binary_swordman_idle_bin_start,						//Idle Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_walk_bin_start,						//Idle to Walk Frames
		3,
		{0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_walk_bin_start,						//Walk Frames
		6, //9,
		{3, 4, 5, 6, 7, 8, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_walk_bin_start,						//Walk to Idle Frames
		3,
		{2, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_idle_bin_start,						//Ranged Frames
		1,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_attack_bin_start,					//Melee Frames
		6,
		{0, 1, 2, 3, 4, 5, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_defend_bin_start,					//Defend Frames
		4,
		{0, 1, 2, 3, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_react_bin_start,						//Hit Frames
		5,
		{0, 1, 2, 3, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
	{
		_binary_swordman_die_bin_start,							//Die Frames
		5,
		{0, 1, 2, 3, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	},
};

UNIT_PROJECTILE archerProjectile =
{
	_binary_arrow_bin_start,									//CharData
	128,																			//FrameSize
	(OAM_SQUARE			 >> OAM_SHAPE_SHIFT),			//Obj Shape
	(OAM_SIZE_16x16  >> OAM_SIZE_SHIFT),			//Obj Size
};

UNIT_PROJECTILE monkProjectile =
{
	_binary_arrow_bin_start,									//CharData
	128,																			//FrameSize
	(OAM_SQUARE			 >> OAM_SHAPE_SHIFT),			//Obj Shape
	(OAM_SIZE_16x16  >> OAM_SIZE_SHIFT),			//Obj Size
};



UNIT_INFO unitInfo[MAX_UNIT_ID] =
{
	{
		&unitStats[PIKEMAN],										//Unit Stats
		pikemanAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_pikeman_pal_bin_start,					//Palette data
		(16*32)/2,															//FrameSize
		(OAM_V_RECTANGLE >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_16x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[HALBERDIER],									//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(16*32)/2,															//FrameSize
		(OAM_V_RECTANGLE >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_16x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[ARCHER],											//Unit Stats
		archerAnims,														//Anim Info
		&archerProjectile,											//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[MARKSMAN],										//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[GRIFFIN],										//Unit Stats
		griffinAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_griffin_pal_bin_start,					//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[ROYAL_GRIFFIN],							//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[SWORDSMAN],									//Unit Stats
		swordmanAnims,													//Anim Info
		NULL,																		//Projectile Info
		_binary_swordman_pal_bin_start,					//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[CRUSADER],										//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[MONK],												//Unit Stats
		monkAnims,															//Anim Info
		&monkProjectile,												//Projectile Info
		_binary_monk_pal_bin_start,							//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[ZEALOT],											//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[CAVALIER],										//Unit Stats
		cavalierAnims,													//Anim Info
		NULL,																		//Projectile Info
		_binary_cavalier_pal_bin_start,					//Palette data
		(64*32)/2,															//FrameSize
		(OAM_H_RECTANGLE >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_64x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[CHAMPION],										//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[ANGEL],											//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},

	{
		&unitStats[ARCH_ANGEL],									//Unit Stats
		archerAnims,														//Anim Info
		NULL,																		//Projectile Info
		_binary_archer_pal_bin_start,						//Palette data
		(32*32)/2,															//FrameSize
		(OAM_SQUARE 		 >> OAM_SHAPE_SHIFT),		//Obj Shape
		(OAM_SIZE_32x32  >> OAM_SIZE_SHIFT),		//Obj Size
	},
};


/*
 *	BOOL addUnitToHero(HERO_ACTOR *heroPtr, UNIT_SLOT_ID slotID, UNIT_ID unitID, short unitSize)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			True for now
 */
BOOL addUnitToHero(HERO_ACTOR *heroPtr, UNIT_SLOT_ID slotID, UNIT_ID unitID, short unitSize)
{
	//add error checking for currently used slots
	//and when increasing # of same unit type

	//unitSlot->unitInfoPtr = &unitInfo[unitID];
	//unitSlot->unitSize		= unitSize;
	heroPtr->unitSlots[slotID].unitInfoPtr = &unitInfo[unitID];
	heroPtr->unitSlots[slotID].unitSize 	 = unitSize;

	return (TRUE);
}

