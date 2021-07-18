/********************************************************************/
/*		AgbIr.h		ver1.0				    */
/*			  AGB IR Communication Library Declaraction */
/*								    */
/*			Copyright (C) 2000 Nintendo of America Inc. */
/********************************************************************/
#ifndef __AGB_IR_H_
#define __AGB_IR_H_

#ifdef __cplusplus
extern "C" {
#endif


/*-------------------------------------------------------------------*/
/*  IR Constant				                             */
/*-------------------------------------------------------------------*/
/***Status***/
#define	IR_SHUTDOWN		0x00
#define IR_DISCONNECT	0xff
#define IR_NORMAL		0x8b	//Normal Value
#define IR_PULSE_ERR	0x01	//When received pulse error
#define IR_BYTES_ERR	0x02	//When received send request for more 
                                //than allowed bytes
#define IR_CODE_ERR		0x04	//Header Code Error
#define	IR_SUM_ERR		0x08	//Checksum Error

/**Communication Mode**/
#define IR_RECEIVER		0x01	//Receiver
#define IR_SENDER		0x02	//Sender
#define IR_UNDEFINED	0x03	//Undefined

/***Data Type**/
#define IR_DATA_RAW		0x5a	//Sent as part of header

/***Function Return Value***/
#define IR_SUCCESS		1		//Success Notification
#define IR_FAILURE		0		//Failure Notification

/***ARM Function Size (WORDS) ***/
#define	IR_ARM_SEND_CORE_SIZE	182	//Words(728Bytes)
#define	IR_ARM_RECV_CORE_SIZE	169	//Words(676Bytes)

/***Communication Speed***/
#define	IR_40kbps_RATE	0x1A3	//Cartridge ROM (4-2 Wait):40000bps
#define IR_47kbps_RATE	0x161   //      Same    (3-1 Wait):47530bps
#define	IR_104kbps_RATE	0x0A1	//Internal RAM:104000bps

/*-------------------------------------------------------------------*/
/*  C Library API        		                             */
/*-------------------------------------------------------------------*/
//IR Communication Parameter Structure
typedef	struct	{
	u16	rate;		//Communication Speed Setting Value
	u8	halfwords;	//Communiction Byte Number
	u8	mode;		//Communication Mode (Sender/Receiver)
	u16	status;		//Communication Status
	u16	sum;		//Communication Checksum Value
}irResult;




/*-------------------------------------------------------------------*/
/*  Communication Start 			                     */
/*-------------------------------------------------------------------*/
extern	void	irBegin( u16 tmrno, irResult* IrResultStr, u8 wait);
/*
Call when infrared communication starts.
Internally the timer controls and content of each of the setup value 
registers for IE, IME, and tmrno is backed up.(backed up content is 
returned by irEnd function)
The IME is disabled and all interrupts are prohibited.
For synchronization of communication, the timer for argument tmrno is 
setup and run.
If you set wait flag, waits until possible for IR Adapter to communicate
(approx. 2ms).

Arguments:
	vu16 		tmrno		Timer number used for communication
	irResult*	IrResultStr	Communication parameter structure
	u8			wait	Wait Flag
*/


/*-------------------------------------------------------------------*/
/*  Communication End         			                     */
/*-------------------------------------------------------------------*/
extern	void	irEnd( void);
/*
Call when infrared communication ends.
Stop timer. Return content of each register saved by irBegin
Also, operate R register and shutdown IR Adapter.
*/


/*-------------------------------------------------------------------*/
/*  Connect Request				                     */
/*-------------------------------------------------------------------*/
extern	u8		irSendConnect( u16 bps);
/*
Do connect request as sender to other unit.
Setup timer control and setup values for registers IE and IME. 
Arguments:
	u16	bps Communication Speed (Use defined constants that 
                                           meet use requirements) 
Return Values:
After sending connect request, if normal connect response from 
other unit, return IR_SUCCESS. If not normal return IR_FAILURE.
*/


/*-------------------------------------------------------------------*/
/*  Connect Response				                     */
/*-------------------------------------------------------------------*/
extern	u8		irRecvConnect( u16 bps);
/*
Do connect response as receiver to other unit.
Setup timer control and setup values for registers IE and IME. 
Arguments:
	u16	bps	Communication Speed (Use defined constants that 
                                           meet use requirements) 
Return Values:
If have normal connect request, send connect response and 
return IR_SUCCESS. If not normal return IR_FAILURE.
*/


/*-------------------------------------------------------------------*/
/*  Communication Initialization		                     */
/*-------------------------------------------------------------------*/
extern	void	irInit( void);
/*
Initialize communication status.
Call each time a communication is done.
*/


/*-------------------------------------------------------------------*/
/*  Send Packet 				                     */
/*-------------------------------------------------------------------*/
extern	u8		irSendPacket( u16* addr, u8 halfwords);
/*
After sending Header + Data + Checksum, receive status.
With one call up to 255 half words are sent. If you want to send more 
data, do more calls.
Arguments:
	u16	addr		Start address of send data
	u8	halfwords	Data Transfer Amount
Return Values:
	If communication is normal return IR_SUCCESS.
	If not normal return IR_FAILURE.
*/


/*-------------------------------------------------------------------*/
/*  Receive Packet 				                     */
/*-------------------------------------------------------------------*/
extern	u8		irRecvPacket( u16* addr, u8 halfwords);
/*
After receiving Header + Data + Checksum, send status.
With one call up to 255 half words are received. If you want to receive 
more data, do more calls.
Arguments:
	u16	addr		Start address of receive data
	u8	halfwords	Data Transfer Amount
Return Values:
	If communication is normal return IR_SUCCESS.
	If not normal return IR_FAILURE.
*/


/*-------------------------------------------------------------------*/
/*  Set up Thumb Code Communication Core		             */
/*-------------------------------------------------------------------*/
extern	void	irMountThumbCore( void);
/*
In the communication after calling this function, the internal ROM 
communication core program is used. (ROM operation).
*/


/*-------------------------------------------------------------------*/
/*  Set up Arm Code Communication Core		                     */
/*-------------------------------------------------------------------*/
extern	void	irMountArmCore( u32* Ram_S_Buf, u32* Ram_R_Buf);
/*
Buffer address where communication core program is stored used as 
argument. In communication after calling this function, the 
communication core program in the buffer is used. (ROM operation).
Make sure you copy the communication core program to the buffer with 
the function, irRamCopy.
Arguments:
    u32*  Ram_S_Buf  Internal RAM Buffer for ARM Code Send Core Storage
    u32*  Ram_R_Buf  Internal RAM Buffer for ARM Code Receive Core Storage	 
*/


/*-------------------------------------------------------------------*/
/*  Copy Arm Code Communication Core    	                     */
/*-------------------------------------------------------------------*/
extern	void	irRamCopy( u32* Ram_S_Buf, u32* Ram_R_Buf);
/*
Transfer send and receive communication core programs (ARM Code) to buffer.
For buffer set aside the following capacity in CPU internal RAM and match up 
with a 32bit boundary.
Word count needed for send buffer (Ram_S_Buf): IR_ARM_SEND_CORE_SIZE
Word count needed for receive buffer (Ram_R_Buf): IR_ARM_RECV_CORE_SIZE
Arguments:
    u32*  Ram_S_Buf  Internal RAM Buffer for ARM Code Send Core Storage
    u32*  Ram_R_Buf  Internal RAM Buffer for ARM Code Receive Core Storage
*/


#ifdef __cplusplus
}
#endif


#endif	/*	__AGB_IR_H_	*/
