	.include "MPlayDef.s"

	.equ	zfx89_grp, voicegroup000
	.equ	zfx89_pri, 128
	.equ	zfx89_rev, reverb_set+50
	.equ	zfx89_mvl, 127
	.equ	zfx89_key, 0
	.equ	zfx89_tbs, 1
	.equ	zfx89_exg, 0
	.equ	zfx89_cmp, 1

	.section .rodata
	.global	zfx89
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx89_1:
	.byte		VOL   , 127*zfx89_mvl/mxv
	.byte	KEYSH , zfx89_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx89_tbs/2
	.byte		VOICE , 53
	.byte		N06   , Cs3 , v108
	.byte	W06
	.byte		N16   , Cs3 , v044
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx89:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx89_pri	@ Priority
	.byte	zfx89_rev	@ Reverb.

	.word	zfx89_grp

	.word	zfx89_1

	.end
