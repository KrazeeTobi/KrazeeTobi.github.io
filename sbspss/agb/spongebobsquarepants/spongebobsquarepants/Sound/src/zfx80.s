	.include "MPlayDef.s"

	.equ	zfx80_grp, voicegroup000
	.equ	zfx80_pri, 128
	.equ	zfx80_rev, reverb_set+50
	.equ	zfx80_mvl, 127
	.equ	zfx80_key, 0
	.equ	zfx80_tbs, 1
	.equ	zfx80_exg, 0
	.equ	zfx80_cmp, 1

	.section .rodata
	.global	zfx80
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx80_1:
	.byte		VOL   , 127*zfx80_mvl/mxv
	.byte	KEYSH , zfx80_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx80_tbs/2
	.byte		VOICE , 123
	.byte		N60   , Fs2 , v108
	.byte	W60
	.byte	FINE

@******************************************************@
	.align	2

zfx80:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx80_pri	@ Priority
	.byte	zfx80_rev	@ Reverb.

	.word	zfx80_grp

	.word	zfx80_1

	.end
