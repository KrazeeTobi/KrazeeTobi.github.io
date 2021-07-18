	.include "MPlayDef.s"

	.equ	zfx28_grp, voicegroup000
	.equ	zfx28_pri, 128
	.equ	zfx28_rev, reverb_set+50
	.equ	zfx28_mvl, 127
	.equ	zfx28_key, 0
	.equ	zfx28_tbs, 1
	.equ	zfx28_exg, 0
	.equ	zfx28_cmp, 1

	.section .rodata
	.global	zfx28
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx28_1:
	.byte		VOL   , 127*zfx28_mvl/mxv
	.byte	KEYSH , zfx28_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx28_tbs/2
	.byte		VOICE , 123
	.byte		N12   , As3 , v108
	.byte	W12
	.byte		N20   , As3 , v052
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx28:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx28_pri	@ Priority
	.byte	zfx28_rev	@ Reverb.

	.word	zfx28_grp

	.word	zfx28_1

	.end
