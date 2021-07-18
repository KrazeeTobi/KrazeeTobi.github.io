	.include "MPlayDef.s"

	.equ	zfx71_grp, voicegroup000
	.equ	zfx71_pri, 128
	.equ	zfx71_rev, reverb_set+50
	.equ	zfx71_mvl, 127
	.equ	zfx71_key, 0
	.equ	zfx71_tbs, 1
	.equ	zfx71_exg, 0
	.equ	zfx71_cmp, 1

	.section .rodata
	.global	zfx71
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx71_1:
	.byte		VOL   , 127*zfx71_mvl/mxv
	.byte	KEYSH , zfx71_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx71_tbs/2
	.byte		VOICE , 107
	.byte		N06   , Cs4 , v108
	.byte	W06
	.byte		N13   , Cs4 , v040
	.byte	W13
	.byte	FINE

@******************************************************@
	.align	2

zfx71:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx71_pri	@ Priority
	.byte	zfx71_rev	@ Reverb.

	.word	zfx71_grp

	.word	zfx71_1

	.end
