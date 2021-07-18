	.include "MPlayDef.s"

	.equ	zfx15_grp, voicegroup000
	.equ	zfx15_pri, 128
	.equ	zfx15_rev, reverb_set+50
	.equ	zfx15_mvl, 127
	.equ	zfx15_key, 0
	.equ	zfx15_tbs, 1
	.equ	zfx15_exg, 0
	.equ	zfx15_cmp, 1

	.section .rodata
	.global	zfx15
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx15_1:
	.byte		VOL   , 127*zfx15_mvl/mxv
	.byte	KEYSH , zfx15_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx15_tbs/2
	.byte		VOICE , 116
	.byte		N20   , Cs3 , v108
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx15:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx15_pri	@ Priority
	.byte	zfx15_rev	@ Reverb.

	.word	zfx15_grp

	.word	zfx15_1

	.end
