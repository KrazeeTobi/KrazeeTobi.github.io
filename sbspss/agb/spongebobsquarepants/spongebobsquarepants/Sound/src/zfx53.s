	.include "MPlayDef.s"

	.equ	zfx53_grp, voicegroup000
	.equ	zfx53_pri, 128
	.equ	zfx53_rev, reverb_set+50
	.equ	zfx53_mvl, 127
	.equ	zfx53_key, 0
	.equ	zfx53_tbs, 1
	.equ	zfx53_exg, 0
	.equ	zfx53_cmp, 1

	.section .rodata
	.global	zfx53
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx53_1:
	.byte		VOL   , 127*zfx53_mvl/mxv
	.byte	KEYSH , zfx53_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx53_tbs/2
	.byte		VOICE , 104
	.byte		N40   , Cs2 , v108
	.byte	W40
	.byte	FINE

@******************************************************@
	.align	2

zfx53:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx53_pri	@ Priority
	.byte	zfx53_rev	@ Reverb.

	.word	zfx53_grp

	.word	zfx53_1

	.end
