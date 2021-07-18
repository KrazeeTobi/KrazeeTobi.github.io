;********************************************************************
;*          MultiSioDefineArm.s                                     *
;*            Multi-Play Communication Library Constant ( ARMASM)             *
;*            ( Communication Error Countermeasure version)                           *
;*                                                                  *
;*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
;********************************************************************


; Optimize the set values below according to the software specification.

; If communication data block size is small, 
; drop rate to reduce the number of interrupts.
MULTI_SIO_BAUD_RATE             *   SIO_115200_BPS  ; Baud rate

MULTI_SIO_BLOCK_SIZE            *   16      ; Communication data block size

MULTI_SIO_SYNC_DATA             *   0xfefe  ; Synchronous data (0x0000 and 0xffff are prohibited) 

; Comment out if there is no space in CPU internal work RAM.
MULTI_SIO_DI_FUNC_FAST                      ; SIO interrupt inhibit function high-speed flag ( CPU internal RAM execution) 

    IF :DEF: MULTI_SIO_DI_FUNC_FAST
MULTI_SIO_SEND_WAIT_COUNT       *   25      ; Send wait loop number when RAM is executed.
    ELSE
MULTI_SIO_SEND_WAIT_COUNT       *   8       ;                         when ROM is executed
    ENDIF


; Multi-play communication packet structure offset

OFS_MSP_FRAME_COUNTER           *   0       ; Frame counter
OFS_MSP_STATE                   *   1       ; Status of communication function (not utilized in sample) 
OFS_MSP_CHECK_SUM               *   2       ; Check sum 
OFS_MSP_DATA                    *   4       ; Communication data
OFS_MSP_OVERRUN_CATCH           *   OFS_MSP_DATA + MULTI_SIO_BLOCK_SIZE * 2
                                            ; Overrun protected area

MULTI_SIO_PACKET_SIZE           *   OFS_MSP_OVERRUN_CATCH + 4
                                            ; Structure size


; Multi-play communication work area structure offset

OFS_MS_TYPE                     *   0       ; Connection between master and slave
OFS_MS_STATE                    *   1       ; Status of communication function 
OFS_MS_CONNECTED_FLAG           *   2       ; Connection history flag
OFS_MS_RECV_SUCCESS_FLAGS       *   3       ; Receiving success flag

OFS_MS_SYNC_RECV_FLAG           *   4       ; Synchronous data receiving verification flag
OFS_MS_SYNC_RECV_ADJUST_COUNTER *   8       ; Synchronous adjustment counter

OFS_MS_SYNC_SEND_FRAME_COUNTER  *   11      ; Send frame counter
OFS_MS_SYNC_RECV_FRAME_COUNTER  *   12      ; Receive frame counter

OFS_MS_SEND_BUF_COUNTER         *   20      ; Send buffer counter
OFS_MS_RECV_BUF_COUNTER         *   24      ; Receive buffer counter

OFS_MS_NEXT_SEND_BUF_P          *   40      ; Send buffer pointer
OFS_MS_CURRENT_SEND_BUF_P       *   44
OFS_MS_CURRENT_RECV_BUF_P       *   48      ; Receive buffer pointer
OFS_MS_LAST_RECV_BUF_P          *   64
OFS_MS_RECV_CHECK_BUF_P         *   80
OFS_MS_RECV_BAK_BUF_P           *   96

OFS_MS_RECV_BLOCK_OFFSET        *   112     ; Received data block assignment

OFS_MS_RECV_CHECK_SUM_BAK       *   116     ; Previously received data check sum

OFS_MS_SEND_BUF                 *   124     ; Send buffer (double buffer)
OFS_MS_RECV_BUF                 *   OFS_MS_SEND_BUF + MULTI_SIO_PACKET_SIZE * 2
                                            ; Receive buffer (four-fold buffer)

MULTI_SIO_AREA_SIZE             *   OFS_MS_RECV_BUF + MULTI_SIO_PACKET_SIZE * 4 * 4
                                            ; Structure size


    EXTERN RecvFuncBuf                      ; CPU internal RAM execution buffer
    EXTERN IntrFuncBuf


;--------------------------------------------------------------------
;-                      Initialize Multi-Play Communication                      -
;--------------------------------------------------------------------

;   EXTERN MultiSioInit

;* Set serial communication mode to multi-play mode.
;* Initialize register and buffer.

;--------------------------------------------------------------------
;-                      Multi-Play Communication Main                      -
;--------------------------------------------------------------------

;   EXTERN MultiSioMain

;* Determines if unit is master or slave, then starts communication upon recognizing master.
;* Calls MultiSioSendDataSet() and sets send data.
;* Calls MultiSioRecvDataCheck(), checks if data has been received normally, then 
;  copies the received data to Recvp.
;
;* Set it so that it is called at the closest timing in 1 frame. 
;* It may take a little while for synchronous adjustment. 
;* It is safe not to send the data that matches flag data (SIO_SYNC_DATA) during synchronous adjustment. 
;* Once response from recognized unit ceases, it continues synchronous adjustment, which causes
;  receiving to be unstable.
;
;* Arguments: 
;    r0:  User send buffer pointer
;    r1:  User receive buffer pointer

;--------------------------------------------------------------------
;-                     Multi-Play Communication Interrupt                    -
;--------------------------------------------------------------------

;   EXTERN MultiSioIntr

;* Stores the data received from each unit to each receive buffer during communication interrupt, 
; and sets the data of send buffer to register.
;* After waiting in the loop No. SIO_SEND_WAIT_COUNT, master restarts sending data.
;
;* Program it so that it is called during communication interrupt.
;* Adjust the set values so that 1 packet (other than OverRunCatch[]) can be certainly transferred in 1 frame.


;--------------------------------------------------------------------
;-                      Set Send Data                           -
;--------------------------------------------------------------------

;   EXTERN MultiSioSendDataSet

;* Set the data of user send buffer to send buffer.
;
;* Called from MultiSioMain().
;* It is necessary to call directly.
;
;* Arguments: 
;    r0:  User send buffer pointer

;--------------------------------------------------------------------
;-                      Check Received Data                         -
;--------------------------------------------------------------------

;   EXTERN MultiSioRecvDataCheck

;* Check if data has been received normally, and if so, copies the received data to user receive buffer.
;* If it is a failure of 1 frame, makes a copy from the same data that was sent in the previous frame. 
; However, it cannot recover if frame counter area is destroyed.
;
;* Called from MultiSioMain().
;* It is not necessary to call directly.
;
;* Arguments: 
;    r0:  User receive buffer pointer


