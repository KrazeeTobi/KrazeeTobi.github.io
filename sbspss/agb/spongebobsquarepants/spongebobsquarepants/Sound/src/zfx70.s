	.include "MPlayDef.s"

	.equ	zfx70_grp, voicegroup000
	.equ	zfx70_pri, 128
	.equ	zfx70_rev, reverb_set+50
	.equ	zfx70_mvl, 127
	.equ	zfx70_key, 0
	.equ	zfx70_tbs, 1
	.equ	zfx70_exg, 0
	.equ	zfx70_cmp, 1

	.section .rodata
	.global	zfx70
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx70_1:
	.byte		VOL   , 127*zfx70_mvl/mxv
	.byte	KEYSH , zfx70_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx70_tbs/2
	.byte		VOICE , 117
	.byte		N19   , Cs3 , v108
	.byte	W19
	.byte	FINE

@******************************************************@
	.align	2

zfx70:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx70_pri	@ Priority
	.byte	zfx70_rev	@ Reverb.

	.word	zfx70_grp

	.word	zfx70_1

	.end
