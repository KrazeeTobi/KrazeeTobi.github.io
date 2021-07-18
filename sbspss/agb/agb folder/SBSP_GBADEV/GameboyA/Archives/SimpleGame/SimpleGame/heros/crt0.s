@********************************************************************
@*	crt0.s                                                  				*
@*  Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               				*
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
  .GLOBAL     start_vector
  .CODE 32
start_vector:
  mov		r0, 	#PSR_IRQ_MODE       @swith to IRQ mode
  msr 	cpsr, r0
  ldr 	sp, 	sp_irq              @set SP_irq
  mov 	r0, 	#PSR_SYS_MODE       @switch to sytem mode
  msr 	cpsr, r0
  ldr 	sp, 	sp_usr              @set SP_usr
  ldr 	r1, 	=INTR_VECTOR_BUF    @set interrupt address
  adr 	r0, 	intr_main
  str 	r0, 	[r1]
  ldr 	r1, 	=AgbMain            @start & switch to 16bit code
  mov 	lr, 	pc
  bx  	r1
  b   	start_vector            	@reset

  .ALIGN
sp_usr: .word   WRAM_END - 0x100
sp_irq: .word   WRAM_END - 0x60

@--------------------------------------------------------------------
@-          Interrupt branch process (look-up table) 32Bit   23-61c -
@--------------------------------------------------------------------
  .EXTERN     IRQFunctions
  .GLOBAL     intr_main
  .ALIGN
  .CODE 32
intr_main:
  mov		r3, #REG_BASE           		@check IE/IF
  add   r3, r3, #OFFSET_REG_IE  		@r3: REG_IE
  ldr   r2, [r3]
  and   r1, r2, r2, lsr #16     		@r1: IE & IF
  mov   r2, #0
  ands  r0, r1, #V_BLANK_INTR_FLAG  @V Blank interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #H_BLANK_INTR_FLAG  @H Blank interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #V_COUNT_INTR_FLAG  @V Counter interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #TIMER0_INTR_FLAG   @Timer 0 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #TIMER1_INTR_FLAG   @Timer 1 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #TIMER2_INTR_FLAG   @Timer 2 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #TIMER3_INTR_FLAG   @Timer 3 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #SIO_INTR_FLAG      @SIO interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #DMA0_INTR_FLAG     @DMA0 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #DMA1_INTR_FLAG     @DMA1 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #DMA2_INTR_FLAG     @DMA2 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #DMA3_INTR_FLAG     @DMA3 interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #KEY_INTR_FLAG      @Key interrupt
  bne   jump_intr
  add   r2, r2, #4
  ands  r0, r1, #CASSETTE_INTR_FLAG @Cassette interrupt
jump_intr:
  strh  r0, [r3, #2]            		@IF clear		 12c
  ldr   r1, =IRQFunctions
  add   r1, r1, r2
  ldr   r0, [r1]
  bx    r0													@Jump to user IRQ process

@   .ORG    0x200

	.END

