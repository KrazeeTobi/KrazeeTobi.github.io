/********************************************************************/
/*          MultiSio.h                                              */
/*         Multi-play Communication Library External Declaration    */
/*             (Timer Interrupt Send Version)                       */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _MULTI_SIO_H
#define _MULTI_SIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>


// Optimize the setting values below according to the software specification.

// If communication data block size is small, drop the rate to decrease the number of interrupts.
#define MULTI_SIO_BAUD_RATE         SIO_115200_BPS  // Baud rate

#define MULTI_SIO_BLOCK_SIZE        32      // Communication data block size

#define MULTI_SIO_SYNC_DATA         0xfefe  // Synchronous data( 0x0000 and 0xffff are prohibited )

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
    u8  State;                              // Status of communication function (not used in samples)
    u16 CheckSum;                           // Check sum
	u16 Data[MULTI_SIO_BLOCK_SIZE/2];       // Communication data
	u16 OverRunCatch[2];                    // Overrun protected area
} MultiSioPacket;


// Multi-play communication work area structure
typedef struct {
    s8  Type;                               // Connection between master and slaves
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
    MultiSioPacket  RecvBuf[4][3];          // Receive buffer (triple buffer )
} MultiSioArea;


extern u32 RecvFuncBuf[];                   // CPU internal RAM execution buffer
extern u32 IntrFuncBuf[];


/*------------------------------------------------------------------*/
/*                      Initialize Multi-play Communication                       */
/*------------------------------------------------------------------*/

extern void MultiSioInit(void);

//* Set serial communication mode as multi-play mode.
//* Initialize register and buffer.

/*------------------------------------------------------------------*/
/*                      Multi-play Communication Main                      */
/*------------------------------------------------------------------*/

extern u32  MultiSioMain(void *Sendp, void *Recvp);

//* Starts communication when recognizing master.
//* Calls MultiSioSendDataSet() and sets send data.
//* Calls MultiSioRecvDataCheck(), checks if data is received normally and copies received data to Recvp.
//
//* Set it so that it is called in the closest timing in one frame.
//* It may take a while for synchronous adjustment.
//* It is safe not to send the data that matches flag data (SIO_SYNC_DATA) during synchronous adjustment.
//* Once response from the recognized unit ceizes, it continues synchronous adjustment,
//  which causes recieving to be unstable.
//
//* Arguments:
//    void *Sendp  User send buffer pointer
//    void *Recvp  User receive buffer pointer

/*------------------------------------------------------------------*/
/*    		 	Multi-play Communication Interrupt                    */
/*------------------------------------------------------------------*/

extern void MultiSioIntr(void);

//* Stores the data received from each unit during communication interrupt in receive buffer, and 
//  sets the data in send buffer to register.
//* After waiting in the loop No. SIO_SEND_WAIT_COUNT, master restarts sending data.
//
//* Program so that it is called during communication interrupt.
//* Adjust the setting value so that 1 packet ( other than OverRunCatch[] ) is certainly transferred in 1 frame.


/*------------------------------------------------------------------*/
/*                      Sets Send Data                           */
/*------------------------------------------------------------------*/

extern void MultiSioSendDataSet(void *Sendp);

//* Sets the data in user send buffer to send buffer.
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

//* Checks if data is received normally, and if so, copies the received data to user recieve buffer.
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
