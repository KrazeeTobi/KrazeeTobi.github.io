	.include "MPlayDef.s"

	.equ	zfx04_grp, voicegroup000
	.equ	zfx04_pri, 128
	.equ	zfx04_rev, reverb_set+50
	.equ	zfx04_mvl, 127
	.equ	zfx04_key, 0
	.equ	zfx04_tbs, 1
	.equ	zfx04_exg, 0
	.equ	zfx04_cmp, 1

	.section .rodata
	.global	zfx04
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx04_1:
	.byte		VOL   , 127*zfx04_mvl/mxv
	.byte	KEYSH , zfx04_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx04_tbs/2
	.byte		VOICE , 113
	.byte		N15   , Cs3 , v108
	.byte	W15
	.byte	FINE

@******************************************************@
	.align	2

zfx04:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx04_pri	@ Priority
	.byte	zfx04_rev	@ Reverb.

	.word	zfx04_grp

	.word	zfx04_1

	.end
