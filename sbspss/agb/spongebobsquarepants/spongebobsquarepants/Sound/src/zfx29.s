	.include "MPlayDef.s"

	.equ	zfx29_grp, voicegroup000
	.equ	zfx29_pri, 128
	.equ	zfx29_rev, reverb_set+50
	.equ	zfx29_mvl, 127
	.equ	zfx29_key, 0
	.equ	zfx29_tbs, 1
	.equ	zfx29_exg, 0
	.equ	zfx29_cmp, 1

	.section .rodata
	.global	zfx29
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx29_1:
	.byte		VOL   , 127*zfx29_mvl/mxv
	.byte	KEYSH , zfx29_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx29_tbs/2
	.byte		VOICE , 64
	.byte		N20   , Cs1 , v108
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx29:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx29_pri	@ Priority
	.byte	zfx29_rev	@ Reverb.

	.word	zfx29_grp

	.word	zfx29_1

	.end
