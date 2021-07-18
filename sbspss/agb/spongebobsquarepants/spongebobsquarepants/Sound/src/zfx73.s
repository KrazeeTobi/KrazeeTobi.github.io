	.include "MPlayDef.s"

	.equ	zfx73_grp, voicegroup000
	.equ	zfx73_pri, 128
	.equ	zfx73_rev, reverb_set+50
	.equ	zfx73_mvl, 127
	.equ	zfx73_key, 0
	.equ	zfx73_tbs, 1
	.equ	zfx73_exg, 0
	.equ	zfx73_cmp, 1

	.section .rodata
	.global	zfx73
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx73_1:
	.byte		VOL   , 127*zfx73_mvl/mxv
	.byte	KEYSH , zfx73_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx73_tbs/2
	.byte		VOICE , 115
	.byte		N30   , En3 , v108
	.byte	W30
	.byte	FINE

@******************************************************@
	.align	2

zfx73:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx73_pri	@ Priority
	.byte	zfx73_rev	@ Reverb.

	.word	zfx73_grp

	.word	zfx73_1

	.end
