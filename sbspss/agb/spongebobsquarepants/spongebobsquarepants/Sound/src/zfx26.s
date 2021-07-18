	.include "MPlayDef.s"

	.equ	zfx26_grp, voicegroup000
	.equ	zfx26_pri, 128
	.equ	zfx26_rev, reverb_set+50
	.equ	zfx26_mvl, 127
	.equ	zfx26_key, 0
	.equ	zfx26_tbs, 1
	.equ	zfx26_exg, 0
	.equ	zfx26_cmp, 1

	.section .rodata
	.global	zfx26
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx26_1:
	.byte		VOL   , 127*zfx26_mvl/mxv
	.byte	KEYSH , zfx26_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx26_tbs/2
	.byte		VOICE , 103
	.byte		N56   , Gn2 , v108
	.byte	W56
	.byte	FINE

@******************************************************@
	.align	2

zfx26:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx26_pri	@ Priority
	.byte	zfx26_rev	@ Reverb.

	.word	zfx26_grp

	.word	zfx26_1

	.end
