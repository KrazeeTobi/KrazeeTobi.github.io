	.include "MPlayDef.s"

	.equ	zfx05_grp, voicegroup000
	.equ	zfx05_pri, 128
	.equ	zfx05_rev, reverb_set+50
	.equ	zfx05_mvl, 127
	.equ	zfx05_key, 0
	.equ	zfx05_tbs, 1
	.equ	zfx05_exg, 0
	.equ	zfx05_cmp, 1

	.section .rodata
	.global	zfx05
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx05_1:
	.byte		VOL   , 127*zfx05_mvl/mxv
	.byte	KEYSH , zfx05_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx05_tbs/2
	.byte		VOICE , 105
	.byte		N15   , Cs3 , v108
	.byte	W15
	.byte	FINE

@******************************************************@
	.align	2

zfx05:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx05_pri	@ Priority
	.byte	zfx05_rev	@ Reverb.

	.word	zfx05_grp

	.word	zfx05_1

	.end
