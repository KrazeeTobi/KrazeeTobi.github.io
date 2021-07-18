	.include "MPlayDef.s"

	.equ	zfx06_grp, voicegroup000
	.equ	zfx06_pri, 128
	.equ	zfx06_rev, reverb_set+50
	.equ	zfx06_mvl, 127
	.equ	zfx06_key, 0
	.equ	zfx06_tbs, 1
	.equ	zfx06_exg, 0
	.equ	zfx06_cmp, 1

	.section .rodata
	.global	zfx06
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx06_1:
	.byte		VOL   , 127*zfx06_mvl/mxv
	.byte	KEYSH , zfx06_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx06_tbs/2
	.byte		VOICE , 52
	.byte		N02   , Fs6 , v080
	.byte	W02
	.byte		N04   , Fs6 , v040
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx06:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx06_pri	@ Priority
	.byte	zfx06_rev	@ Reverb.

	.word	zfx06_grp

	.word	zfx06_1

	.end
