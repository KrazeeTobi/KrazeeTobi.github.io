@********************************************************************
@*          crt0.s                                                  *
@*            �X�^�[�g�A�b�v���[�`���iGAS�p�j                       *
@*                                                                  *
@*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
@********************************************************************
    .INCLUDE    "AgbDefine.s"
    .INCLUDE    "AgbMemoryMap.s"
    .INCLUDE    "AgbMacro.s"
    .TEXT

    .GLOBAL     _start
_start:
    .INCLUDE    "rom_header.s"

@--------------------------------------------------------------------
@-                          ���Z�b�g                                -
@--------------------------------------------------------------------
    .EXTERN     AgbMain
    .GLOBAL     start_vector
    .CODE 32
start_vector:
        mov     r0, #PSR_IRQ_MODE       @ IRQ���[�h�֐؂芷��
        msr     cpsr, r0
        ldr     sp, sp_irq              @ SP_irq �̃Z�b�g
        mov     r0, #PSR_SYS_MODE       @ �V�X�e�����[�h�֐؂芷��
        msr     cpsr, r0
        ldr     sp, sp_usr              @ SP_usr �̃Z�b�g
        ldr     r1, =INTR_VECTOR_BUF    @ ���荞�݃A�h���X�̃Z�b�g
        adr     r0, intr_main
        str     r0, [r1]
        ldr     r1, =AgbMain            @ �X�^�[�g �� 16bit�R�[�h�ւ̐؊�
        mov     lr, pc
        bx      r1
        b       start_vector            @ ���Z�b�g

    .ALIGN
sp_usr: .word   WRAM_END - 0x100
sp_irq: .word   WRAM_END - 0x60


@--------------------------------------------------------------------
@-          ���荞�ݕ��򏈗��i�e�[�u�������j32Bit            23-61c -
@--------------------------------------------------------------------
    .EXTERN     IntrTable
    .GLOBAL     intr_main
    .ALIGN
    .CODE 32
intr_main:
        mov     r3, #REG_BASE           @ IE/IF �`�F�b�N
        add     r3, r3, #OFFSET_REG_IE  @ r3: REG_IE
        ldr     r2, [r3]
        and     r1, r2, r2, lsr #16     @ r1: IE & IF
        mov     r2, #0
        ands    r0, r1, #V_BLANK_INTR_FLAG   @ V�u�����N ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #H_BLANK_INTR_FLAG   @ H�u�����N ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #V_COUNT_INTR_FLAG   @ V�J�E���^ ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER0_INTR_FLAG    @ �^�C�}�[0 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER1_INTR_FLAG    @ �^�C�}�[1 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER2_INTR_FLAG    @ �^�C�}�[2 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER3_INTR_FLAG    @ �^�C�}�[3 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #SIO_INTR_FLAG       @ �V���A���ʐM ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA0_INTR_FLAG      @ DMA0 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA1_INTR_FLAG      @ DMA1 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA2_INTR_FLAG      @ DMA2 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA3_INTR_FLAG      @ DMA3 ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #KEY_INTR_FLAG       @ �L�[ ���荞��
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #CASSETTE_INTR_FLAG  @ �J�Z�b�g ���荞��
jump_intr:
        strh    r0, [r3, #2]            @ IF �N���A           11c
        ldr     r1, =IntrTable          @ ���[�UIRQ�����փW�����v
        add     r1, r1, r2
        ldr     r0, [r1]
        bx      r0


@   .ORG    0x200


    .END

