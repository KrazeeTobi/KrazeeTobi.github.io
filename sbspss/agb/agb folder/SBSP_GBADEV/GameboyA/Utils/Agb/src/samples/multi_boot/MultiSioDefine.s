@********************************************************************
@*          MultiSioDefine.s                                        *
@*            Multi-play Communication Library Constant ( GAS)                *
@*            ( Timer Interrupt Send Version)                     *
@*                                                                  *
@*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
@********************************************************************


@ Optimize the set values below according to the software specification.

@ If communication data block size is small, 
@ drop rate to decrease the number of interrupts.
MULTI_SIO_BAUD_RATE             =   SIO_115200_BPS  @ Baud rate

MULTI_SIO_BLOCK_SIZE            =   32      @ Communication data block size

MULTI_SIO_SYNC_DATA             =   0xfefe  @ Synchronous data ( 0x0000 and 0xffff are prohibited) 

@ Comment out if there is no space in CPU internal work RAM.
MULTI_SIO_DI_FUNC_FAST:                     @ SIO interrupt inhibit function high-speed flag ( CPU internal RAM execution) 


MULTI_SIO_TIMER_NO              =   3               @ Timer No.
MULTI_SIO_TIMER_COUNT           =   0x3000          @ Timer count number
MULTI_SIO_TIMER_INTR_FLAG       =   (TIMER0_INTR_FLAG << MULTI_SIO_TIMER_NO)
                                                    @ Timer interrupt flag
REG_MULTI_SIO_TIMER             =   (REG_TM0CNT + MULTI_SIO_TIMER_NO * 4)
                                                    @ Timer register


@ Multi-play communication packet structure* offset

OFS_MSP_FRAME_COUNTER           =   0       @ Frame counter
OFS_MSP_STATE                   =   1       @ Status of communication function (not utilized in samples) 
OFS_MSP_CHECK_SUM               =   2       @ Check sum
OFS_MSP_DATA                    =   4       @ Communication data
OFS_MSP_OVERRUN_CATCH           =   OFS_MSP_DATA + MULTI_SIO_BLOCK_SIZE
                                            @ Overrun protected area

MULTI_SIO_PACKET_SIZE           =   OFS_MSP_OVERRUN_CATCH + 4
                                            @ Size of structure


@ Multi-play communication work area structure* offset

OFS_MS_TYPE                     =   0       @ Connection between master and slaves
OFS_MS_STATE                    =   1       @ Status of communication function
OFS_MS_CONNECTED_FLAG           =   2       @ Connection history flag
OFS_MS_RECV_SUCCESS_FLAGS       =   3       @ Receiving success flag

OFS_MS_SYNC_RECV_FLAG           =   4       @ Synchronous data recieving verification flag
OFS_MS_SYNC_RECV_ADJUST_COUNTER =   8       @ Synchronous adjustment counter

OFS_MS_SYNC_SEND_FRAME_COUNTER  =   11      @ Send frame counter
OFS_MS_SYNC_RECV_FRAME_COUNTER  =   12      @ Receive frame counter

OFS_MS_SEND_BUF_COUNTER         =   20      @ Send buffer counter
OFS_MS_RECV_BUF_COUNTER         =   24      @ Receive buffer counter

OFS_MS_NEXT_SEND_BUF_P          =   40      @ Send buffer pointer
OFS_MS_CURRENT_SEND_BUF_P       =   44
OFS_MS_CURRENT_RECV_BUF_P       =   48      @ Receive buffer pointer
OFS_MS_LAST_RECV_BUF_P          =   64
OFS_MS_RECV_CHECK_BUF_P         =   80

OFS_MS_SEND_BUF                 =   96      @ Send buffer (double buffer)
OFS_MS_RECV_BUF                 =   OFS_MS_SEND_BUF + MULTI_SIO_PACKET_SIZE * 2
                                            @ Receive buffer (triple buffer)

MULTI_SIO_AREA_SIZE             =   OFS_MS_RECV_BUF + MULTI_SIO_PACKET_SIZE * 4 * 3
                                            @ Size of structure


    .EXTERN RecvFuncBuf                     @ CPU internal RAM exeuction buffer
    .EXTERN IntrFuncBuf


@--------------------------------------------------------------------
@-                      Initialize Multi-play Communication                       -
@--------------------------------------------------------------------

    .EXTERN MultiSioInit

@* Set serial communication mode as multi-play mode.
@* Initializes register and buffer.

@--------------------------------------------------------------------
@-                      Multi-play Communication Main                      -
@--------------------------------------------------------------------

    .EXTERN MultiSioMain

@* Starts communication when master is recognized.
@* Calls MultiSioSendDataSet() and sets send data.
@* Calls MultiSioRecvDataCheck(), checks if data is received normally and copies
@  received data to Recvp.
@
@* Set it so that it is called in the closest timing in 1 frame.
@* It may take a while for synchronous adjustment.
@* It is safe not to send the data that matches flag dat (SIO_SYNC_DATA) during synchronous adjustment.
@  
@* Once response ceases from the recognized unit, it continues synchronous adjustment, which
@ causes receiving to be unstable.
@
@* Arguments: 
@    r0:  User send buffer pointer
@    r1:  User receive buffer pointer

@--------------------------------------------------------------------
@-                      Multi-play Communication Interrupt                    -
@--------------------------------------------------------------------

    .EXTERN MultiSioIntr

@* Stores the data received from each unit during communication interrupt to each receive buffer, and 
@  sets the data of send buffer to register.
@* After waiting in Loop No. SIO_SEND_WAIT_COUNT, master restarts sending data.
@
@* Program it so that it is called during communication interrupt.
@* Adjust the set value so that 1 packet (other than OverRunCatch[]) is certainly transferred in 1 frame.


@--------------------------------------------------------------------
@-                      Set Send Data                           -
@--------------------------------------------------------------------

    .EXTERN MultiSioSendDataSet

@* Set the data of user send buffer to send buffer.
@
@* Called from MultiSioMain().
@* It is not necessary to call directly.
@
@* Arguments: 
@    r0:  User send buffer pointer

@--------------------------------------------------------------------
@-                     Checks Recieved Data                         -
@--------------------------------------------------------------------

    .EXTERN MultiSioRecvDataCheck

@* Check if data is received normally, and if so, copies the received data to user recieve buffer.
@
@* Called from MultiSioMain().
@* It is not necessary to call directly.
@
@* Arguments: 
@    r0:  User receive buffer pointer


