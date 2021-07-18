@********************************************************************
@*          crt0.s                                                  *
@*            Start Up Routine (For GAS)                            *
@*                                                                  *
@*          Copyright (C) 1999,NINTENDO Co.,Ltd.                    *
@********************************************************************
    .INCLUDE    "AgbDefine.s"
    .INCLUDE    "AgbMemoryMap.s"
    .INCLUDE    "AgbMacro.s"
    .TEXT

    .GLOBAL     _start
    .GLOBAL     _start_vector
_start:
@--------------------------------------------------------------------
@-                          Reset                                   -
@--------------------------------------------------------------------
    .EXTERN     _main
    .CODE 32
_start_vector:
        mov     r0, #PSR_IRQ_MODE       @ Switch to IRQ Mode
        msr     cpsr, r0
        ldr     sp, sp_irq              @ Set SP_irq 
        mov     r0, #PSR_SYS_MODE       @ Switch to System Mode
        msr     cpsr, r0
        ldr     sp, sp_usr              @ Set SP_usr 
        ldr     r1, =INTR_VECTOR_BUF    @ Set Interrupt Address
        adr     r0, _intr_main
        str     r0, [r1]
        ldr     r1, =_main              @ Start & Switch to 16bit Code
        mov     lr, pc
        bx      r1
        b       _start_vector           @ Reset

    .ALIGN
sp_usr: .word   USR_BUF_END - 4*32
sp_irq: .word   USR_BUF_END


@--------------------------------------------------------------------
@-          Interrupt Branch Process (Drawing from Table) 32Bit            27-68c -
@--------------------------------------------------------------------
    .EXTERN     _IntrTable
    .GLOBAL     _intr_main
    .ALIGN
    .CODE 32
_intr_main:
        stmfd   sp!, {lr}

        ldr     r3, =REG_IE             @ Check IE/IF 
        ldr     r2, [r3]
        and     r1, r2, r2, lsr #16
        mov     r2, #0
        ands    r0, r1, #V_BLANK_INTR_FLAG   @ V Blanc Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #H_BLANK_INTR_FLAG   @ H Blanc Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #V_COUNT_INTR_FLAG   @ V Counter Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER0_INTR_FLAG    @ Timer 0 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER1_INTR_FLAG    @ Timer 1 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER2_INTR_FLAG    @ Timer 2 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER3_INTR_FLAG    @ Timer 3 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #SIO_INTR_FLAG       @ Serial Communication Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA0_INTR_FLAG      @ DMA0 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA1_INTR_FLAG      @ DMA1 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA2_INTR_FLAG      @ DMA2 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA3_INTR_FLAG      @ DMA3 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #KEY_INTR_FLAG       @ Key Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #IR_INTR_FLAG        @ Infrared Communication Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #CASSETTE_INTR_FLAG  @ Cassette Interrupt
jump_intr:
        strh    r0, [r3, #2]            @ IF Clear           12c
        ldr     r1, =_IntrTable         @ Jump to User IRQ Process
        add     r1, r1, r2
        ldr     r0, [r1]
        mov     lr, pc                  @ Set Return Address
        bx      r0

        ldmfd   sp!, {lr}
        bx      lr                      @ Return to before Interrupt


@   .ORG    0x200


    .END

