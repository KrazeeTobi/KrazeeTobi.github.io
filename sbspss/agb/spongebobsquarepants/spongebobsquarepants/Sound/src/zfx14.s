	.include "MPlayDef.s"

	.equ	zfx14_grp, voicegroup000
	.equ	zfx14_pri, 128
	.equ	zfx14_rev, reverb_set+50
	.equ	zfx14_mvl, 127
	.equ	zfx14_key, 0
	.equ	zfx14_tbs, 1
	.equ	zfx14_exg, 0
	.equ	zfx14_cmp, 1

	.section .rodata
	.global	zfx14
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx14_1:
	.byte		VOL   , 127*zfx14_mvl/mxv
	.byte	KEYSH , zfx14_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx14_tbs/2
	.byte		VOICE , 35
	.byte		N20   , Gs2 , v068
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx14:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx14_pri	@ Priority
	.byte	zfx14_rev	@ Reverb.

	.word	zfx14_grp

	.word	zfx14_1

	.end
