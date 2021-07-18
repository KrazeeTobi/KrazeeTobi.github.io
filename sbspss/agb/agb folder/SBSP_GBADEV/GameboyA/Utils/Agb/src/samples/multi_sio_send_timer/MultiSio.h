/********************************************************************/
/*          MultiSio.h                                              */
/*            Multi-Play Communication Library External Declaration                    */
/*            ( Timer Interrupt Send version)                     */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _MULTI_SIO_H
#define _MULTI_SIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>


// Optimize the set values below according to the specification of game pak.

// If communication data block size is small, 
// drop rate to reduce the number of interrupts.
#define MULTI_SIO_BAUD_RATE         SIO_115200_BPS  // Baud rate

#define MULTI_SIO_BLOCK_SIZE        32      // Communication data block size

#define MULTI_SIO_SYNC_DATA         0xfefe  // Synchronous data ( 0x0000 and 0xffff are prohibited) 

// Comment out if there is no space in CPU internal work RAM.
#define MULTI_SIO_DI_FUNC_FAST              // SIO interrupt inhibit function high-speed flag ( CPU internal RAM execution) 


#define MULTI_SIO_TIMER_NO          3                   // Timer No.
#define MULTI_SIO_TIMER_COUNT       0x3000              // Timer count number
#define MULTI_SIO_TIMER_INTR_FLAG   \
            (TIMER0_INTR_FLAG << MULTI_SIO_TIMER_NO)    // Timer interrupt flag
#define REG_MULTI_SIO_TIMER         \
            (REG_TM0CNT + MULTI_SIO_TIMER_NO * 4)       // Timer register


// Multi-play communication packet structure
typedef struct {
    u8  FrameCounter;                       // Frame counter
    u8  State;                              // Status of communication function (not utilized in sample)
    u16 CheckSum;                           // Check sum
	u16 Data[MULTI_SIO_BLOCK_SIZE/2];       // Communication data
	u16 OverRunCatch[2];                    // Overrun protected area
} MultiSioPacket;


// Multi-play communication work area structure
typedef struct {
    s8  Type;                               // Connection betwen master and slave
    s8  State;                              // Status of communication function 
    u8  ConnectedFlags;                     // Connection history flag
    u8  RecvSuccessFlags;                   // Receiving success flag

    u8  SyncRecvFlag[4];                    // Synchronous data receiving verification flag
    u8  SyncAdjustCounter;                  // Synchronous adjustment counter

	u8  Padding0[2];

    u8  SendFrameCounter;                   // Send frame counter
    u8  RecvFrameCounter[4][2];             // Receive frame counter

    s32 SendBufCounter;                     // Send buffer counter
    s32 RecvBufCounter[4];                  // Receive buffer counter

    u16 *NextSendBufp;                      // Send buffer pointer
    u16 *CurrentSendBufp;
    u16 *CurrentRecvBufp[4];                // Receive buffer pointer
    u16 *LastRecvBufp[4];
    u16 *RecvCheckBufp[4];

    MultiSioPacket  SendBuf[2];             // Send buffer (double buffer)
    MultiSioPacket  RecvBuf[4][3];          // Receive buffer (triple buffer)
} MultiSioArea;


extern u32 RecvFuncBuf[];                   // Buffer for CPU internal RAM execution
extern u32 IntrFuncBuf[];


/*------------------------------------------------------------------*/
/*                     Initialize Multi-Play Communication                       */
/*------------------------------------------------------------------*/

extern void MultiSioInit(void);

//* Set serial communication mode to multi-play mode.
//* Initialize register and buffer.

/*------------------------------------------------------------------*/
/*                     Multi-Play Communication Main                      */
/*------------------------------------------------------------------*/

extern u32  MultiSioMain(void *Sendp, void *Recvp);

//* Determines whether or not the unit is master or slave, then starts communication once master is recognized.
//* Calls MultiSioSendDataSet() and sets send data.
//* Calls MultiSioRecvDataCheck(), checks if data has been received normally, and 
// copies the received data to Recvp.
//
//* Set it so that it is called at the closest timing in 1 frame.
//* It may take a little while for synchronous adjustment.
//* It is safe not to send the data that matches flag data (SIO_SYNC_DATA) during synchronous adjustment.
//* Once response from the recognized unit ceases, it continues synchronous adjustment, which 
//  causes recieving to be unstable.
//
//* Arguments: 
//    void *Sendp  User send buffer pointer
//    void *Recvp  User receive buffer pointer

/*------------------------------------------------------------------*/
/*    		 	Multi-Play Communication Interrupt                   */
/*------------------------------------------------------------------*/

extern void MultiSioIntr(void);

//* Stores the data received from each unit to each receive buffer during communication interrupt, 
//  and sets the data of send buffer to register.
//* After waiting in the loop No. SIO_SEND_WAIT_COUNT, master restarts sending data.
//
//* Program it so that it is called during communication interrupt.
//* Adjust the set values so that 1 packet (other than OverRunCatch[])  can be certainly transferred in 1 frame.


/*------------------------------------------------------------------*/
/*                      Set Send Data                           */
/*------------------------------------------------------------------*/

extern void MultiSioSendDataSet(void *Sendp);

//* Set the data of user send buffer to send buffer.
//
//* Called from MultiSioMain().
//* It is not necessary to call directly.
//
//* Arguments: 
//    void *Sendp  User send buffer pointer

/*------------------------------------------------------------------*/
/*                      Check Received Data                         */
/*------------------------------------------------------------------*/

extern u32  MultiSioRecvDataCheck(void *Recvp);

//* Check if data has been received normally, and if so, copies the received data to user receive buffer.
//
//* Called from MultiSioMain().
//* It is not necessary to call directly.
//
//* Arguments: 
//    void *Recvp  User receive buffer pointer


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* _MULTI_SIO_H */
