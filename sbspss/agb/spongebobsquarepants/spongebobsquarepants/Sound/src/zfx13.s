	.include "MPlayDef.s"

	.equ	zfx13_grp, voicegroup000
	.equ	zfx13_pri, 128
	.equ	zfx13_rev, reverb_set+50
	.equ	zfx13_mvl, 127
	.equ	zfx13_key, 0
	.equ	zfx13_tbs, 1
	.equ	zfx13_exg, 0
	.equ	zfx13_cmp, 1

	.section .rodata
	.global	zfx13
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx13_1:
	.byte		VOL   , 127*zfx13_mvl/mxv
	.byte	KEYSH , zfx13_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx13_tbs/2
	.byte		VOICE , 111
	.byte		N20   , Cs3 , v108
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx13:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx13_pri	@ Priority
	.byte	zfx13_rev	@ Reverb.

	.word	zfx13_grp

	.word	zfx13_1

	.end
