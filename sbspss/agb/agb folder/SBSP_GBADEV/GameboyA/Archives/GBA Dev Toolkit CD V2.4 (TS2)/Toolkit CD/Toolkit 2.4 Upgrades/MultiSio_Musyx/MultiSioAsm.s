@********************************************************************
@*          MultiSioAsm.s                                           *
@*            Multi-play Communication Library (GAS)                *
@*            (Timer Interrupt Sending Version)                     *
@*                                                                  *
@*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
@********************************************************************
    .INCLUDE    "AgbDefine.s"
    .INCLUDE    "AgbMemoryMap.s"
    .INCLUDE    "AgbSyscallDefine.s"
    .INCLUDE    "AgbMacro.s"
    .TEXT

    .INCLUDE    "MultiSioDefine.s"


    .ifdef MULTI_SIO_DI_FUNC_FAST

@--------------------------------------------------------------------
@-               Routine to Update Received Data Check Buffer       -
@--------------------------------------------------------------------

    .EXTERN     Ms
    .GLOBAL     MultiSioRecvBufChange
    .CODE 32
MultiSioRecvBufChange:
        stmfd   sp!, {r4-r11}

        mov     r12, #REG_BASE                      @ r12: REG_BASE
        ldr     r11, =Ms                            @ r11: &Ms
        add     r10, r11, #OFS_MS_LAST_RECV_BUF_P   @ r10: &Ms.LastRecvBufp[0]
        mov     r9,  #1                             @ r9:  1
        mov     r8,  #0                             @ r8:  0


        @ *(vu8 *)REG_IME = 0   Disables interrupt (29 clocks)

        strb    r8,  [r12, #OFFSET_REG_IME]

        @ Ms.RecvCheckBufp[i] <--> Ms.LastRecvBufp[i]

        ldmia   r10,  {r0-r7}
        stmia   r10!, {r4-r7}
        stmia   r10!, {r0-r3}

        @ SyncRecvFlagBak[i] = Ms.SyncRecvFlag[i]
        @ Ms.SyncRecvFlag[i] = 0

        ldr     r0,  [r11, #OFS_MS_SYNC_RECV_FLAG]
        str     r8,  [r11, #OFS_MS_SYNC_RECV_FLAG]

        @ *(vu8 *)REG_IME = 1   Enables interrupt

        strb    r9,  [r12, #OFFSET_REG_IME]

        @ return  Ms.SyncRecvFlag[i]

        ldmfd   sp!, {r4-r11}
        bx      lr

	.LTORG                                          @ Creates literal pool


@--------------------------------------------------------------------
@-   		 Multi-play Communication Interrupt Routine         -
@--------------------------------------------------------------------

    .GLOBAL     MultiSioIntr
    .CODE 32
MultiSioIntr:

        @ Saves received data

        @ *(u64 *)RecvTmp = *(u64 *)REG_SIOMLT_RECV

        mov     r12, #REG_BASE                           @ r12: REG_SIOMLT_RECV
        add     r12, r12, #OFFSET_REG_SIOMLT_RECV
        ldmia   r12, {r0-r1}

        @ Saves the stack of register

        stmfd   sp!, {r7-r11}


        ldr     r11, =Ms                                @ r11: &Ms
        mov     r9,     #MULTI_SIO_SYNC_DATA & 0x00ff   @ r9:  MULTI_SIO_SYNC_DATA
        add     r9, r9, #MULTI_SIO_SYNC_DATA & 0xff00


        @ Send data process

        @ if  (Ms.SendBufCounter == -1) {

        ldr     r10, [r11, #OFS_MS_SEND_BUF_COUNTER]    @ r10: Ms.SendBufCounter
        adds    r3,  r10, #1
        blt     3f
        bne     2f

        @     REG_SIOCNT->Data = MULTI_SIO_SYNC_DATA          Sets synchronous data

        strh    r9, [r12, #REG_SIOMLT_SEND - REG_SIOMLT_RECV]

        @     Ms.CurrentSendBufp <--> Ms.NextSendBufp         Changes send buffer

        add     r8,  r11, #OFS_MS_NEXT_SEND_BUF_P
        ldmia   r8, {r2,r3}
        mov     r7,  r2
        stmia   r8, {r3,r7}
        b       3f
2:
        @ } else if (Ms.SendBufCounter >= 0) {
        @     REG_SIOCNT->Data = Ms.CurrentSendBufp[Ms.SendBufCounter]
        @                                                     Sets sending data

        ldr     r3, [r11, #OFS_MS_CURRENT_SEND_BUF_P]
        ldr     r2, [r3,  r10, lsl #1]
        strh    r2, [r12, #REG_SIOMLT_SEND - REG_SIOMLT_RECV]
3:
        @ }

        @ if (Ms.SendBufCounter < sizeof(MultiSioPacket)/2 - 1)
        @     Ms.SendBufCounter++;

        cmp     r10, #MULTI_SIO_PACKET_SIZE/2 - 1
        addlt   r10, r10, #1
        strlt   r10, [r11, #OFS_MS_SEND_BUF_COUNTER]

        @ Saves received data and the stack of register

        stmfd   sp!, {r0-r1, r5-r6}



        @ Received data process (included in maximum 160 clocks/wait period)

        @ for (i=0; i<4; i++) {

        mov     r6, #3                                  @ r6:  i
4:
        add     r8, r11, #OFS_MS_RECV_BUF_COUNTER       @ r8: &Ms.RecvBufCounter[i]
        add     r8, r8, r6, lsl #2
        ldr     r10, [r8, #0]                           @ r10: Ms.RecvBufCounter[i]
        mov     r3, r6, lsl #1                          @ r5:  RecvTmp[i]
        ldrh    r5,  [sp, r3]

        @ if ( RecvTmp[i] == MULTI_SIO_SYNC_DATA
        @   && Ms.RecvBufCounter[i] > sizeof(MultiSioPacket)/2 - 3) {

        cmp     r5, r9
        bne     6f
        cmp     r10, #MULTI_SIO_PACKET_SIZE/2 - 3
        ble     6f

        @      Ms.SyncRecvFlag[i] = 1

        add     r3, r11, #OFS_MS_SYNC_RECV_FLAG
        mov     r0, #1
        strb    r0, [r3, r6]

        @      Ms.RecvBufCounter[i] = -1

        sub     r10, r0, #2

        b       7f
6:
        @ } else {
        @     Ms.CurrentRecvBufp[i][Ms.RecvBufCounter[i]] = RecvTmp[i]
        @                                                     Stores received data

        ldr     r0, [r8, #OFS_MS_CURRENT_RECV_BUF_P - OFS_MS_RECV_BUF_COUNTER]
        mov     r3, r10, lsl #1
        strh    r5, [r0, r3]

        @ if (Ms.RecvBufCounter[i] == sizeof(MultiSioPacket)/2 - 3)

        cmp     r10, #MULTI_SIO_PACKET_SIZE/2 - 3
        bne     7f

        @     Ms.CurrentRecvBufp[i] <--> Ms.LastRecvBufp[i]   Changes receive buffer

        ldr     r1, [r8, #OFS_MS_LAST_RECV_BUF_P    - OFS_MS_RECV_BUF_COUNTER]
        str     r0, [r8, #OFS_MS_LAST_RECV_BUF_P    - OFS_MS_RECV_BUF_COUNTER]
        str     r1, [r8, #OFS_MS_CURRENT_RECV_BUF_P - OFS_MS_RECV_BUF_COUNTER]
7:
        @ }

        @ if (Ms.RecvBufCounter[i] < sizeof(MultiSioPacket)/2 - 1)
        @     Ms.RecvBufCounter[i]++;

        cmp     r10, #MULTI_SIO_PACKET_SIZE/2 - 1
        addlt   r10, r10, #1
        str     r10, [r8, #0]

        subs    r6, r6, #1
        bge     4b

        @ }



        @ Master starts to send data

        @ if (Ms.Type == SIO_MULTI_PARENT)

        ldrb    r0, [r11,#OFS_MS_TYPE]
        cmp     r0, #0
        beq     11f

        @     *(vu16 *)REG_SIOCNT |= SIO_ENABLE;

        ldrh    r0, [r12, #REG_SIOCNT - REG_SIOMLT_RECV]
        orr     r0, r0, #SIO_ENABLE
        strh    r0, [r12, #REG_SIOCNT - REG_SIOMLT_RECV]

11:
        add     sp, sp, #8
        ldmfd   sp!, {r5-r11}
        bx      lr


    .endif


    .END

