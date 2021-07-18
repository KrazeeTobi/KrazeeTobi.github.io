	.include "MPlayDef.s"

	.equ	zfx45_grp, voicegroup000
	.equ	zfx45_pri, 128
	.equ	zfx45_rev, reverb_set+50
	.equ	zfx45_mvl, 127
	.equ	zfx45_key, 0
	.equ	zfx45_tbs, 1
	.equ	zfx45_exg, 0
	.equ	zfx45_cmp, 1

	.section .rodata
	.global	zfx45
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx45_1:
	.byte		VOL   , 127*zfx45_mvl/mxv
	.byte	KEYSH , zfx45_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx45_tbs/2
	.byte		VOICE , 111
	.byte		N10   , Gs3 , v108
	.byte	W10
	.byte		N20   , Gs3 , v036
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx45:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx45_pri	@ Priority
	.byte	zfx45_rev	@ Reverb.

	.word	zfx45_grp

	.word	zfx45_1

	.end
