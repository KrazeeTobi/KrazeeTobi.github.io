	.include "MPlayDef.s"

	.equ	zfx23_grp, voicegroup000
	.equ	zfx23_pri, 128
	.equ	zfx23_rev, reverb_set+50
	.equ	zfx23_mvl, 127
	.equ	zfx23_key, 0
	.equ	zfx23_tbs, 1
	.equ	zfx23_exg, 0
	.equ	zfx23_cmp, 1

	.section .rodata
	.global	zfx23
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx23_1:
	.byte		VOL   , 127*zfx23_mvl/mxv
	.byte	KEYSH , zfx23_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx23_tbs/2
	.byte		VOICE , 109
	.byte		N24   , Cs3 , v108
	.byte	W24
	.byte	W01
	.byte	FINE

@******************************************************@
	.align	2

zfx23:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx23_pri	@ Priority
	.byte	zfx23_rev	@ Reverb.

	.word	zfx23_grp

	.word	zfx23_1

	.end
