	.include "MPlayDef.s"

	.equ	zfx68_grp, voicegroup000
	.equ	zfx68_pri, 128
	.equ	zfx68_rev, reverb_set+50
	.equ	zfx68_mvl, 127
	.equ	zfx68_key, 0
	.equ	zfx68_tbs, 1
	.equ	zfx68_exg, 0
	.equ	zfx68_cmp, 1

	.section .rodata
	.global	zfx68
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx68_1:
	.byte		VOL   , 127*zfx68_mvl/mxv
	.byte	KEYSH , zfx68_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx68_tbs/2
	.byte		VOICE , 121
	.byte		N32   , Cs3 , v108
	.byte	W32
	.byte	FINE

@******************************************************@
	.align	2

zfx68:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx68_pri	@ Priority
	.byte	zfx68_rev	@ Reverb.

	.word	zfx68_grp

	.word	zfx68_1

	.end
