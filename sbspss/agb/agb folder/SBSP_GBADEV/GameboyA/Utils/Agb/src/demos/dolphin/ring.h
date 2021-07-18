/********************************************************************/
/*          ring.h                                                  */
/*                 Data external declaration                        */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef	_RING_H
#define	_RING_H

#define RING_MAX_NUM  20
#define RING_OAM_POS  90//100


typedef struct {
	s32 x, y;
	s32 vx, vy;
	u8 state;
	s32 dat;
	u8 flg;
	u8 pass_flg;
	s16 counter;
	s16 pass_counter;
}Ring;

typedef struct
{
	s32   xPos, yPos;//position of appearance 
}RingMapData;


// ring status  
enum {
	RING_NORMAL_STATE,	// normal
	RING_PASS_STATE,	// passed ring 
	RING_HIT_STATE,		// hit ring  
};


// ring status function 
void RingNormal(Ring *pRing, u8 i);
void RingPassed(Ring *pRing, u8 i);
void RingHit(Ring *pRing, u8 i);

// ring status function jump table  
static void (*pRing_state_tbl[])(Ring *, u8) = {
	RingNormal,
	RingPassed,
	RingHit,
};

void InitRing();
void RingStateControl(Ring* pRing);
void RingProc();
void CreateRing(Player *pPlayer);
void DrawRing(Ring *pRing);

#endif