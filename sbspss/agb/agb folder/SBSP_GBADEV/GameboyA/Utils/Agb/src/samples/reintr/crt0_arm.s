;********************************************************************
;*          crt0Arm.s                                               *
;*            Start Up Routine (for ARMASM                          *
;*                                                                  *
;*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
;********************************************************************
    INCLUDE     AgbDefineArm.s
    INCLUDE     AgbMemoryMapArm.s
    INCLUDE     AgbMacroArm.s
    AREA        Init, CODE, READONLY

    ENTRY
start
    INCLUDE     rom_header_arm.s

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
sp_usr  DCD     WRAM_END - 0x100
sp_irq  DCD     WRAM_END - 0x60

;--------------------------------------------------------------------
;-   Interrupt Branch Process (Multiple Interrupt) (Draw from Table) 43-81c -
;--------------------------------------------------------------------
    EXTERN      IntrTable
    GLOBAL      intr_main
    ALIGN
    CODE32
intr_main
        mov     r3, #REG_BASE           ; Read in IE/IF
        add     r3, r3, #OFFSET_REG_IE  ; r3: REG_IE
        ldr     r2, [r3]
        mov     r1, r2, lsl #16         ; r1: IE
        mov     r1, r1, lsr #16

        mrs     r0, spsr                ; Save Register (IRQ Mode)
        stmfd   sp!, {r0, r1, r3, lr}   ; {spsr, IE, REG_IE, lr}

        and     r1, r2, r2, lsr #16     ; Check IE/IF
        mov     r2, #0
        ands    r0, r1, #TIMER0_INTR_FLAG    ; Timer 0 interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #V_BLANK_INTR_FLAG   ; V Blank interrupt
        bne     jump_intr
        add     r2, r2, #4

        ands    r0, r1, #H_BLANK_INTR_FLAG   ; H Blank interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #V_COUNT_INTR_FLAG   ; V Counter interrupt
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
        ands    r0, r1, #CASSETTE_INTR_FLAG  ; Cassette interrupt
jump_intr
        strh    r0, [r3, #2]                    ; Clear IF         22c
        ldr     r1, =IME_FLAG | TIMER0_INTR_FLAG    ; Set IE <- Multiple Interrupt Choice
        strh    r1, [r3]
        mrs     r3, cpsr                            ; Multiple Interrupt Permission & Switched to System Mode
        bic     r3, r3, #PSR_CPU_MODE_MASK | PSR_IRQ_DISABLE | PSR_FIQ_DISABLE
        orr     r3, r3, #PSR_SYS_MODE
        msr     cpsr, r3
;--------------------------------------------------------------------- System Mode
        ldr     r1, =IntrTable                      ; Jump to User IRQ Process
        add     r1, r1, r2
        ldr     r0, [r1]

        stmfd   sp!, {lr}                           ; Save Register (System Mode)
        adr     lr, intr_return                     ; Set Return Address
        bx      r0
intr_return
        ldmfd   sp!, {lr}                           ; Return to Register (System Mode)

        mrs     r3, cpsr                            ; Multiple Interrupt Not Permitted & Switch to IRQ Mode
        bic     r3, r3, #PSR_CPU_MODE_MASK | PSR_IRQ_DISABLE | PSR_FIQ_DISABLE
        orr     r3, r3, #PSR_IRQ_MODE      | PSR_IRQ_DISABLE
        msr     cpsr, r3
;---------------------------------------------------------------------IRQ Mode
        ldmfd   sp!, {r0, r1, r3, lr}           ; Return Register (IRQ Mode)
        strh    r1, [r3]                        ; {spsr, IE, REG_IE, lr}
        msr     spsr, r0
        bx      lr                              ; Return to prior to interrupt


    END

