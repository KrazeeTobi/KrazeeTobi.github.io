/********************************************************************/
/*          MultiSio.c                                              */
/*            Multi-Play Communication Library                      */
/*            (Timer Interrupt Send version)                        */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "MultiSio.h"


/*-------------------- Global Variables  ----------------------------*/

MultiSioArea     Ms;            // Multi-play communication work area

#ifdef MULTI_SIO_DI_FUNC_FAST
u32 RecvFuncBuf[0x50/4];        // RAM execution buffer for received data check buffer change routine
u32 IntrFuncBuf[0x110/4];       // RAM execution buffer for interrupt routine
#endif


/*------------------------------------------------------------------*/
/*                      Initialize Multi-Play Communication                      */
/*------------------------------------------------------------------*/
extern u32 MultiSioRecvBufChange(void);

void MultiSioInit(void)
{
	int		i;

	*(vu16 *)REG_IME = 0;                               // Disables SIO interrupt
	*(vu16 *)REG_IE &= ~SIO_INTR_FLAG;
	*(vu16 *)REG_IME = 1;

	*(vu16 *)REG_RCNT  = R_SIO_MASTER_MODE;
	*(vu16 *)REG_SIOCNT  = SIO_MULTI_MODE;
	*(vu16 *)REG_SIOCNT |= SIO_IF_ENABLE | MULTI_SIO_BAUD_RATE;

    CpuClear(0, &Ms, sizeof(Ms), 32);                   // Clears multi-play communication work area

#ifdef MULTI_SIO_DI_FUNC_FAST                           // Copies function
    CpuCopy(MultiSioRecvBufChange, RecvFuncBuf, sizeof(RecvFuncBuf), 32);
    CpuCopy(MultiSioIntr,          IntrFuncBuf, sizeof(IntrFuncBuf), 32);
#endif

	Ms.SendBufCounter = -1;

	Ms.NextSendBufp    = (u16 *)&Ms.SendBuf[0];         // Sets send buffer pointer
	Ms.CurrentSendBufp = (u16 *)&Ms.SendBuf[1];

	for (i=0; i<4; i++) {                               // Sets receive buffer pointer
		Ms.CurrentRecvBufp[i] = (u16 *)&Ms.RecvBuf[i][0];
		Ms.LastRecvBufp[i]    = (u16 *)&Ms.RecvBuf[i][1];
		Ms.RecvCheckBufp[i]   = (u16 *)&Ms.RecvBuf[i][2];
	}

	*(vu16 *)REG_IE |= SIO_INTR_FLAG;                   // Enables SIO interrupt
}


/*------------------------------------------------------------------*/
/*                      Multi-Play Communication Main                      */
/*------------------------------------------------------------------*/

u32 MultiSioMain(void *Sendp, void *Recvp)
{
	int		i, ii;

	switch (Ms.State) {
		case 0:	if (!((SioMultiCnt *)REG_SIOCNT)->SD)   // Checks connection
					break;
				if (!((SioMultiCnt *)REG_SIOCNT)->SI && Ms.SendBufCounter == -1) {
					*(vu16 *)REG_IME = 0;
					*(vu16 *)REG_IE &= ~SIO_INTR_FLAG;				// Disables SIO interrupt
					*(vu16 *)REG_IE |=  MULTI_SIO_TIMER_INTR_FLAG;	// Enables timer interrupt
					*(vu16 *)REG_IME = 1;
					*(vu16 *)REG_IF  =  SIO_INTR_FLAG				// Resets IF
									 |  MULTI_SIO_TIMER_INTR_FLAG;

					*(vu32 *)REG_MULTI_SIO_TIMER                    // Starts timer
					                 = (0x10000 - MULTI_SIO_TIMER_COUNT)
									 | TMR_PRESCALER_1CK
									 | TMR_IF_ENABLE | TMR_ENABLE;

					Ms.Type = SIO_MULTI_PARENT;
					((SioMultiCnt *)REG_SIOCNT)->Enable  = 1;
				}
		case 1: 
		case 2:	for (i=0; i<Ms.SyncAdjustCounter; i++)	// Synchronous adjustment wait
					for (ii=0; ii<5; ii++)		;

				MultiSioSendDataSet(Sendp);             // Sets send data

				if (MultiSioRecvDataCheck(Recvp)) {     // Checks received data
					if (Ms.State < 2)		Ms.State++;
				} else						Ms.State = 1;
				break;
	}

	Ms.SendFrameCounter++;

	return	Ms.RecvSuccessFlags;
}


/*------------------------------------------------------------------*/
/*                      Set Send Data                           */
/*------------------------------------------------------------------*/

void MultiSioSendDataSet(void *Sendp)
{
	s32		CheckSum = 0;
	int		i;

	((MultiSioPacket *)Ms.NextSendBufp)->FrameCounter = (u8 )Ms.SendFrameCounter;
	((MultiSioPacket *)Ms.NextSendBufp)->State = Ms.State;
	((MultiSioPacket *)Ms.NextSendBufp)->CheckSum = 0;

	CpuCopy(Sendp, (u8 *)&Ms.NextSendBufp[2], MULTI_SIO_BLOCK_SIZE,   32);  // Sets send data

	for (i=0; i<sizeof(MultiSioPacket)/2 - 2; i++)      // Calculates send data check sum
		CheckSum += Ms.NextSendBufp[i];
	((MultiSioPacket *)Ms.NextSendBufp)->CheckSum = ~CheckSum;

	Ms.SendBufCounter = -1;
}

/*------------------------------------------------------------------*/
/*                      Checks Received Data                         */
/*------------------------------------------------------------------*/

u32 MultiSioRecvDataCheck(void *Recvp)
{
    u32 (*MultiSioRecvBufChangeOnRam)(void) = (u32 (*)(void))RecvFuncBuf;
	s32		 CheckSum;
	u8		 SyncRecvFlagBak[4];
	u8		 CounterDiff;
	u16		*BufpTmp;
	int		 i, ii;


#ifdef MULTI_SIO_DI_FUNC_FAST                           // Updates received data check buffer
	*(u32 *)SyncRecvFlagBak = MultiSioRecvBufChangeOnRam();
#else
	*(vu16 *)REG_IME = 0;                               // Disables interrupt (about 80 clocks)

	for (i=0; i<4; i++) {
		BufpTmp = Ms.RecvCheckBufp[i];                  // Updates received data check buffer
		Ms.RecvCheckBufp[i] = Ms.LastRecvBufp[i];
		Ms.LastRecvBufp[i] = BufpTmp;
	}
	*(u32 *)SyncRecvFlagBak = *(u32 *)Ms.SyncRecvFlag;  // Copies synchronous data receiving verification flag
    *(u32 *)Ms.SyncRecvFlag = 0;

	*(vu16 *)REG_IME = 1;                               // Enables interrupt
#endif

    Ms.RecvSuccessFlags = 0;

	for (i=0; i<4; i++) {
		Ms.RecvFrameCounter[i][1] = Ms.RecvFrameCounter[i][0];
		Ms.RecvFrameCounter[i][0] = ((MultiSioPacket *)Ms.RecvCheckBufp[i])->FrameCounter;
		CounterDiff = Ms.RecvFrameCounter[i][0] - Ms.RecvFrameCounter[i][1];

		CheckSum = 0;                                   // Calculates received data check sum
		for (ii=0; ii<sizeof(MultiSioPacket)/2 - 2; ii++)
			CheckSum +=  Ms.RecvCheckBufp[i][ii];

		if (CounterDiff == 1 && SyncRecvFlagBak[i])    	// When data is successfully received
			if ((s16 )CheckSum == -1) {
				CpuCopy(&((u8 *)Ms.RecvCheckBufp[i])[4],
						&((u8 *)Recvp)[i*MULTI_SIO_BLOCK_SIZE], MULTI_SIO_BLOCK_SIZE, 32);
				Ms.RecvSuccessFlags |= 1 << i;
			}
	}

    Ms.ConnectedFlags |= Ms.RecvSuccessFlags;           // Sets connection end flag

    if (Ms.ConnectedFlags ^ Ms.RecvSuccessFlags)        // Updates synchronous adjustment counter
		Ms.SyncAdjustCounter += 79;

    return Ms.RecvSuccessFlags;
}


/*==================================================================*/
/*    		 	Multi-Play Communication Interrupt Routine               */
/*==================================================================*/

#ifndef MULTI_SIO_DI_FUNC_FAST

void MultiSioIntr(void)
{
	u16		RecvTmp[4];
	u16		*BufpTmp;
	int		i, ii;


	// Saves received data

	*(u64 *)RecvTmp = *(u64 *)REG_SIOMLT_RECV;


	// Send data process

	if (Ms.SendBufCounter != -1) {                      // Sets send data
		((SioMultiCnt *)REG_SIOCNT)->Data = Ms.CurrentSendBufp[Ms.SendBufCounter];
	} else {
		((SioMultiCnt *)REG_SIOCNT)->Data = MULTI_SIO_SYNC_DATA;
		                                                // Sets synchronous data

		BufpTmp = Ms.CurrentSendBufp;                   // Changes send buffer
		Ms.CurrentSendBufp = Ms.NextSendBufp;
		Ms.NextSendBufp = BufpTmp;
	}
	if (Ms.SendBufCounter < (s32 )(sizeof(MultiSioPacket)/2 - 1))	Ms.SendBufCounter++;


	// Received data process (included in the maximum 350 clocks/wait period)

	for (i=0; i<4; i++) {
		if (RecvTmp[i] == MULTI_SIO_SYNC_DATA
		 && Ms.RecvBufCounter[i] > (s32 )(sizeof(MultiSioPacket)/2 - 3)) {
			Ms.RecvBufCounter[i] = -1;
			Ms.SyncRecvFlag[i] = 1;
		} else {
			Ms.CurrentRecvBufp[i][Ms.RecvBufCounter[i]] = RecvTmp[i];
                                                        // Stores received data
			if (Ms.RecvBufCounter[i] == (s32 )(sizeof(MultiSioPacket)/2 - 3)) {
				BufpTmp = Ms.LastRecvBufp[i];           // Changed recieve buffer
				Ms.LastRecvBufp[i] = Ms.CurrentRecvBufp[i];
				Ms.CurrentRecvBufp[i] = BufpTmp;
			}
		}
		if (Ms.RecvBufCounter[i] < (s32 )(sizeof(MultiSioPacket)/2 - 1))	Ms.RecvBufCounter[i]++;
	}


	// Master starts sending data

	if (Ms.Type == SIO_MULTI_PARENT)
		*(vu16 *)REG_SIOCNT |= SIO_ENABLE;
}

#endif

