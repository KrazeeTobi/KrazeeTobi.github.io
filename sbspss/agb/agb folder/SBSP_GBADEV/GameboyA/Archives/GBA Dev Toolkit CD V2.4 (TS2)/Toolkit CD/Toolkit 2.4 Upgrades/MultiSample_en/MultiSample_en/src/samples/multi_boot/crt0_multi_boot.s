@======================================================
@    crt0_multi_boot.s (crt0.s that is compatible with MultiBoot)
@    AGB Startup Routine
@
@    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
@======================================================

	.INCLUDE	"AgbDefine.s"
	.INCLUDE	"AgbMemoryMap.s"
    .INCLUDE    "AgbSyscallDefine.s"
	.INCLUDE	"AgbMacro.s"
	.TEXT

	.GLOBAL		_start
_start:
	.INCLUDE	"rom_header.s"

	b	start_vector

@ Declare as the following examples from C program:
@ extern u8 boot_method, boot_channel;
@
@ boot_method: 0=ROM boot
@              (1=Reserve)
@              (2=Reserve)
@              3=Multi-play boot
@
@ boot_channel: 0=Master (a value that is not possible in serial boot)
@               1-3: Slave No. 1 to 3.

	.globl	boot_method
	.globl	boot_channel
boot_method:	.byte	0	@ boot method = ROM if it stays as the initial value 0
boot_channel:	.byte	0

	.byte	0	@ reserved
	.byte	0	@ reserved

@ The parameter area from host
@ Declare as the following examples from C program:
@ extern u32 bootparam[6];
@
@ Each parameter that is determined at the time of execution can be sent to slaves by setting here.
@ If there are no parameters that change by the time of execution, it will be sent to slaves as in its initial value.

        .globl  bootparam
bootparam:
        .word   0	@ bootparam[0]
        .word   0	@ bootparam[1]

        .word   0
        .word   0
        .word   0
        .word   0


@--------------------------------------------------------------------
@-                          Expand Program                          -
@--------------------------------------------------------------------
    .EXTERN     _binary_demo_LZ_bin_start
    .GLOBAL     start_vector
    .CODE 32
start_vector:
        ldr     r0, =_binary_demo_LZ_bin_start
        ldr     r1, =EX_WRAM + 0x10000
        swi     SWI_NO_LZ77_UNCOMP_WRAM << 16   @ bl  LZ77UnCompWram

        ldr     lr, =EX_WRAM + 0x10000
        bx      lr


	.END


