	.include "MPlayDef.s"

	.equ	zfx01_grp, voicegroup000
	.equ	zfx01_pri, 128
	.equ	zfx01_rev, reverb_set+50
	.equ	zfx01_mvl, 127
	.equ	zfx01_key, 0
	.equ	zfx01_tbs, 1
	.equ	zfx01_exg, 0
	.equ	zfx01_cmp, 1

	.section .rodata
	.global	zfx01
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx01_1:
	.byte		VOL   , 127*zfx01_mvl/mxv
	.byte	KEYSH , zfx01_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx01_tbs/2
	.byte		VOICE , 8
	.byte		N15   , Ds2 , v080
	.byte	W15
	.byte	FINE

@******************************************************@
	.align	2

zfx01:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx01_pri	@ Priority
	.byte	zfx01_rev	@ Reverb.

	.word	zfx01_grp

	.word	zfx01_1

	.end
