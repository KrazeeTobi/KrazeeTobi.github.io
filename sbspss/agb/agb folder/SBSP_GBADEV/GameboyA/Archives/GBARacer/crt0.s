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
_start:
    .INCLUDE    "rom_header.s"

@--------------------------------------------------------------------
@-                          Reset                                   -
@--------------------------------------------------------------------
    .EXTERN     AgbMain
    .GLOBAL     _start_vector
    .CODE 32
_start_vector:
        mov     r0, #PSR_IRQ_MODE       @ Switch to IRQ Mode
        msr     cpsr, r0
        ldr     sp, sp_irq              @ Set SP_irq 
        mov     r0, #PSR_SYS_MODE       @ Switch to System Mode
        msr     cpsr, r0
        ldr     sp, sp_usr              @ Set SP_usr 
        ldr     r1, =INTR_VECTOR_BUF    @ Set Interrupt Address
        adr     r0, intr_main
        str     r0, [r1]
        ldr     r1, =AgbMain            @ Start & Switch to 16bit Code
        mov     lr, pc
        bx      r1
        b       _start_vector           @ Reset

    .ALIGN
sp_usr: .word   WRAM_END - 0x100
sp_irq: .word   WRAM_END - 0x60

@--------------------------------------------------------------------
@-          Interrupt Branch Process (Drawing from Table) 32Bit            27-68c -
@--------------------------------------------------------------------
    .EXTERN     _IntrTable
    .GLOBAL     intr_main
    .ALIGN
    .CODE 32

intr_main:
        stmfd   sp!, {lr}

        ldr     r3, =REG_IE             @ Check IE/IF 
        ldr     r2, [r3]
        and     r1, r2, r2, lsr #16

		@@@
		@@@ Check for H blank first, since that's the most likely:
		@@@

		ands    r0, r1, #H_BLANK_INTR_FLAG   @ H Blanc Interrupt
		bne		handle_hblank

        mov     r2, #0
        ands    r0, r1, #V_BLANK_INTR_FLAG   @ V Blanc Interrupt
        bne     jump_intr
        add     r2, r2, #4

@@@@@@@	ands    r0, r1, #H_BLANK_INTR_FLAG   @ H Blanc Interrupt
@@@@@@@	bne     jump_intr

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
        ands    r0, r1, #CASSETTE_INTR_FLAG  @ Cassette Interrupt

jump_intr:
        strh    r0, [r3, #2]            @ IF Clear           12c
        ldr     r1, =IntrTable         @ Jump to User IRQ Process
        add     r1, r1, r2
        ldr     r0, [r1]
        mov     lr, pc                  @ Set Return Address
        bx      r0

        ldmfd   sp!, {lr}
        bx      lr                      @ Return to before Interrupt

		@
		@
		@

handle_hblank:

        strh    r0, [r3, #2]            @ IF Clear

		@
		@ For now, we'll hardwire it to set Mode 7 stuff:
		@

@		ldr		r1, =REG_BG2PA
@
@		ldr		r3, =REG_VCOUNT
@		ldrb	r3, [r3]				@ Only want the low byte!
@		add		r3, r3, #1
@
@
@		ldr		r2, =_Dmt_U_Table
@		ldr		r0,[r2, r3, lsl #2]
@
@		add		r0, r0, #0x00008000
@		str		r0,[r1, #8]
@
@
@		ldr		r2, =_Dmt_V_Table
@		ldr		r0,[r2, r3, lsl #2]
@
@		rsb		r0, r0, #0x00008000
@		str		r0,[r1, #12]
@
@		add		r3, r3, r3
@
@		ldr		r2, =_Dmt_DU_Table
@		ldrh	r0,[r2, r3]
@		strh	r0,[r1]
@
@		ldr		r2, =_Dmt_DV_Table
@		ldrh	r0,[r2, r3]
@		strh	r0,[r1, #4]
@
@		@
@		@

		ldr		r1, =REG_BG2PA

		ldr		r3, =REG_VCOUNT
		ldrb	r3, [r3]				@ Only want the low byte!
		add		r3, r3, #1

		ldr		r2, =p_rend_Mode7_FBuffer
		ldr		r2,[r2]
		add		r2, r2, r3, lsl #4
		ldr		r0,[r2]
		str		r0,[r1, #8]
		
		ldr		r0,[r2, #4]
		str		r0,[r1, #12]
		
		ldr		r0,[r2, #8]
		strh	r0,[r1]
		
		ldr		r0,[r2, #12]
		strh	r0,[r1, #4]

		@
		@

        ldmfd   sp!, {lr}
        bx      lr                      @ Return to before Interrupt



@   .ORG    0x200

@--------------------------------------------------------------------
@-           Fill from buckets 32Bit            
@--------------------------------------------------------------------

    .EXTERN     _s_left_bucket
    .EXTERN     _s_right_bucket
    .EXTERN     _rend_Back_Screen
    .EXTERN     _s_fill_colour_long
    .EXTERN     _Rend_Head_Masks
    .EXTERN     _Rend_Tail_Masks

    .EXTERN     _rend_DPE_dsy
    .EXTERN     _rend_DPE_p_sx  
    .EXTERN     _rend_DPE_ival  
    .EXTERN     _rend_DPE_istep 
    .EXTERN     _rend_DPE_fval  
    .EXTERN     _rend_DPE_fstep 
    .EXTERN     _rend_DPE_ifstep
    .EXTERN     _rend_DPE_delta_y

    .GLOBAL     rend_fill_from_bux
    .GLOBAL     _rend_edge_to_bux
    .GLOBAL     _rend_clear_screen
    .ALIGN
    .CODE 32

rend_fill_from_bux:

	stmfd	sp!, { r0-r12, r14 }

    ldr	r3, =s_left_bucket             @ r3 -> min_y
	ldr r4, [r3], #4					@ r4 = sy_min, r3 ->max_y
	ldr r5, [r3], #4					@ r5 = sy_max, r3 -> s_left_bucket.x[0]

	subs r5, r5, r4						@ r5 = dsy
	bls done_with_fill

    ldr	r6, =s_right_bucket + 8        @ r6 -> s_right_bucket.x[0]

	ldr r1, =s_fill_colour_long
	ldr r7,[r1]							@ r7 = s_fill_colour_long

	ldr r8, =rend_Back_Screen

	add r3, r3, r4, lsl #2
	add r6, r6, r4, lsl #2
	add r8, r8, r4, lsl #2

outer_fill_loop:

	ldr r9, [r3], #4					@ r9 = sx_min
	ldr r10, [r6], #4					@ r10 = sx_max 

	cmp r9, r10
	beq done_with_line

	mov r11, r9, lsr #7					@ r11 = ax_min
	mov r12, r10, lsr #7				@ r12 = ax_max

	add r0, r11, r11, lsl #2			@ r0 = ax_min * 5
	add r14, r8, r0, lsl #7				@ r14 = start of screen line + 640 * ax_min
	
	and r9, r9, #112	
	ldr r0, =Rend_Head_Masks
	ldr r9, [ r0, r9, lsr #2 ]			@ r9 = head mask

	and r10, r10, #112	
	ldr r0, =Rend_Tail_Masks
	ldr r10, [ r0, r10, lsr #2 ]		@ r10 = tail mask

	subs r12, r12, r11
	bne different_words

	@
	@ Head and tail lie in the same word
	@

	and r2, r9, r10
	and r1, r2, r7
	ldr r0, [r14]
	bic r0, r0, r2
	orr r0, r0, r1
	str r0, [r14]

	b done_with_line

different_words:

	@
	@ Head and tail lie in different words
	@
	
	@ Head:

	and r1, r9, r7
	ldr r0, [r14]
	bic r0, r0, r9
	orr r0, r0, r1
	str r0, [r14], #640

	@ Middle (if any):

	subs r12, r12, #1
	beq no_middle

middle_loop:

	str r7, [r14], #640
	subs r12, r12, #1
	bne middle_loop

no_middle:

	@ Tail:

	and r1, r10, r7
	ldr r0, [r14]
	bic r0, r0, r10
	orr r0, r0, r1
	str r0, [r14]

done_with_line:

	add r8, r8, #4

	subs r5, r5, #1
	bne outer_fill_loop

done_with_fill:
	
	ldmfd	sp!, { r0-r12, r14 }
	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@

_rend_edge_to_bux:
	
	stmfd	sp!, { r0-r8 }

    ldr r0, =rend_DPE_dsy
	ldr r1,[ r0 ]

    ldr r0, =rend_DPE_p_sx  
	ldr r2,[ r0 ]

    ldr r0, =rend_DPE_ival  
	ldr r3,[ r0 ]

    ldr r0, =rend_DPE_istep 
	ldr r4,[ r0 ]

    ldr r0, =rend_DPE_fval  
	ldr r5,[ r0 ]

    ldr r0, =rend_DPE_fstep 
	ldr r6,[ r0 ]

    ldr r0, =rend_DPE_ifstep
	ldr r7,[ r0 ]

    ldr r0, =rend_DPE_delta_y
	ldr r8,[ r0 ]

edge_loop:

	str r3,[ r2 ], #4
	add r3, r3, r4
	adds r5, r5, r6
	addpl r3, r3, r7
	subpl r5, r5, r8
	subs r1, r1, #1
	bne edge_loop

	ldmfd	sp!, { r0-r8 }
	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@

_rend_clear_screen:

	stmfd	sp!, { r0-r10 }

    ldr r8, =s_fill_colour_long
	ldr r0, [r8]
	mov r1, r0
	mov r2, r0
	mov r3, r0
	mov r4, r0
	mov r5, r0
	mov r6, r0
	mov r7, r0
	ldr r8, =rend_Back_Screen
	mov r9, #60

rcs_l1:

	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }
	stmia r8!, { r0-r7 }

	subs r9, r9, #1
	bne	rcs_l1

	ldmfd	sp!, { r0-r10 }
	bx lr

@   .ORG    0x200


    .END

