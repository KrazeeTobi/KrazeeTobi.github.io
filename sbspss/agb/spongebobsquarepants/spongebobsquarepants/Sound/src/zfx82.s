	.include "MPlayDef.s"

	.equ	zfx82_grp, voicegroup000
	.equ	zfx82_pri, 128
	.equ	zfx82_rev, reverb_set+50
	.equ	zfx82_mvl, 127
	.equ	zfx82_key, 0
	.equ	zfx82_tbs, 1
	.equ	zfx82_exg, 0
	.equ	zfx82_cmp, 1

	.section .rodata
	.global	zfx82
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx82_1:
	.byte		VOL   , 127*zfx82_mvl/mxv
	.byte	KEYSH , zfx82_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx82_tbs/2
	.byte		VOICE , 123
	.byte		N44   , En3 , v108
	.byte	W44
	.byte	W02
	.byte	FINE

@******************************************************@
	.align	2

zfx82:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx82_pri	@ Priority
	.byte	zfx82_rev	@ Reverb.

	.word	zfx82_grp

	.word	zfx82_1

	.end
