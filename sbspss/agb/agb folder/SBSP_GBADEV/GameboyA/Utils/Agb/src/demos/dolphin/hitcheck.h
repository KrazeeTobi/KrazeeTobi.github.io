/********************************************************************/
/*          hitcheck.h                                              */
/*                 Data external declaration                        */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef	_HITCHECK_H
#define	_HITCHECK_H

// Collision detection of blowgun and dolphin 
void Fukiya2Dolphin(Player *pPlayer, Fukiya *pFukiya);
// Collision detection of dolphin and enemy   
void Dolphin2Enemy(Player *pPlayer, Enemy *pTeki);
// Collision detection of ring and dolphin  
void Ring2Dolphin(Ring *pRing, Player *pPlayer);
// Check if dolphin passed through ring  
u8 RingPass(Ring *pRing, Player *pPlayer);

#endif
