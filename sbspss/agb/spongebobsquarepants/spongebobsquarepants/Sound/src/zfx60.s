	.include "MPlayDef.s"

	.equ	zfx60_grp, voicegroup000
	.equ	zfx60_pri, 128
	.equ	zfx60_rev, reverb_set+50
	.equ	zfx60_mvl, 127
	.equ	zfx60_key, 0
	.equ	zfx60_tbs, 1
	.equ	zfx60_exg, 0
	.equ	zfx60_cmp, 1

	.section .rodata
	.global	zfx60
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx60_1:
	.byte		VOL   , 127*zfx60_mvl/mxv
	.byte	KEYSH , zfx60_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx60_tbs/2
	.byte		VOICE , 64
	.byte		N08   , Fs2 , v108
	.byte	W08
	.byte		VOICE , 11
	.byte		N04   , Cs2 , v088
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx60:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx60_pri	@ Priority
	.byte	zfx60_rev	@ Reverb.

	.word	zfx60_grp

	.word	zfx60_1

	.end
