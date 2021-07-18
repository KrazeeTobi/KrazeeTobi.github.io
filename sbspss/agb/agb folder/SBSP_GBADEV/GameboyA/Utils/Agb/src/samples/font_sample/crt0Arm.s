;********************************************************************
;*          crt0Arm.s                                               *
;*            Start Up Routine (for ARMASM)                         *
;*                                                                  *
;*          Copyright (C) 1999,NINTENDO Co.,Ltd.                    *
;********************************************************************
    INCLUDE     AgbDefineArm.s
    INCLUDE     AgbMemoryMapArm.s
    INCLUDE     AgbMacroArm.s
    AREA        Init, CODE, READONLY
    ENTRY
start
;--------------------------------------------------------------------
;-                      Reset                                       -
;--------------------------------------------------------------------
    EXTERN      AgbMain
    CODE32
start_vector
        mov     r0, #PSR_IRQ_MODE       ; Switch to IRQ Mode
        msr     cpsr, r0
        ldr     sp, sp_irq              ; Set SP_irq
        mov     r0, #PSR_SYS_MODE       ; Switch to System Mode
        msr     cpsr, r0
        ldr     sp, sp_usr              ; Set SP_usr
        ldr     r1, =INTR_VECTOR_BUF    ; Set Interrupt Address
        adr     r0, intr_main
        str     r0, [r1]
        ldr     r1, =AgbMain            ; Start & Switch to 16bit Code
        mov     lr, pc
        bx      r1
        b       start_vector            ; Reset

    ALIGN
sp_usr  DCD     USR_BUF_END - 4*32
sp_irq  DCD     USR_BUF_END

;--------------------------------------------------------------------
;-  Interrupt Branch Process (Multiple Interrupt) (Draw from Table) 32Bit            27-68c -
;--------------------------------------------------------------------
    EXTERN      IntrTable
    GLOBAL      intr_main
    ALIGN
    CODE32
intr_main
        stmfd   sp!, {lr}

        ldr     r3, =REG_IE             ; Check IE/IF
        ldr     r2, [r3]
        and     r1, r2, r2, lsr #16
        mov     r2, #0
        ands    r0, r1, #V_BLANK_INTR_FLAG   ; V Blank interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #H_BLANK_INTR_FLAG   ; H Blank interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #V_COUNT_INTR_FLAG   ; V Blank interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER0_INTR_FLAG    ; Timer 0 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER1_INTR_FLAG    ; Timer 1 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER2_INTR_FLAG    ; Timer 2 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER3_INTR_FLAG    ; Timer 3 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #SIO_INTR_FLAG       ; Serial communication interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA0_INTR_FLAG      ; DMA0 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA1_INTR_FLAG      ; DMA1 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA2_INTR_FLAG      ; DMA2 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA3_INTR_FLAG      ; DMA3 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #KEY_INTR_FLAG       ; Key interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #IR_INTR_FLAG        ; Infrared communication interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #CASSETTE_INTR_FLAG  ; Cassette interrupt
jump_intr
        strh    r0, [r3, #2]            ; Clear IF           12c
        ldr     r1, =IntrTable          ; Jump to user IRQ process
        add     r1, r1, r2
        ldr     r0, [r1]
        mov     lr, pc                  ; Set return address
        bx      r0

        ldmfd   sp!, {lr}
        bx      lr                      ; Return to prior to interrupt

    END

