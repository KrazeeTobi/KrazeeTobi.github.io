	.include "MPlayDef.s"

	.equ	zfx03_grp, voicegroup000
	.equ	zfx03_pri, 128
	.equ	zfx03_rev, reverb_set+50
	.equ	zfx03_mvl, 127
	.equ	zfx03_key, 0
	.equ	zfx03_tbs, 1
	.equ	zfx03_exg, 0
	.equ	zfx03_cmp, 1

	.section .rodata
	.global	zfx03
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx03_1:
	.byte		VOL   , 127*zfx03_mvl/mxv
	.byte	KEYSH , zfx03_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx03_tbs/2
	.byte		VOICE , 120
	.byte		N15   , Gs2 , v108
	.byte	W15
	.byte	FINE

@******************************************************@
	.align	2

zfx03:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx03_pri	@ Priority
	.byte	zfx03_rev	@ Reverb.

	.word	zfx03_grp

	.word	zfx03_1

	.end
