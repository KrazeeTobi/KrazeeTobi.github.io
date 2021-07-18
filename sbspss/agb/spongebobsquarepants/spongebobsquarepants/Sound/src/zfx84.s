	.include "MPlayDef.s"

	.equ	zfx84_grp, voicegroup000
	.equ	zfx84_pri, 128
	.equ	zfx84_rev, reverb_set+50
	.equ	zfx84_mvl, 127
	.equ	zfx84_key, 0
	.equ	zfx84_tbs, 1
	.equ	zfx84_exg, 0
	.equ	zfx84_cmp, 1

	.section .rodata
	.global	zfx84
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx84_1:
	.byte		VOL   , 127*zfx84_mvl/mxv
	.byte	KEYSH , zfx84_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx84_tbs/2
	.byte		VOICE , 113
	.byte		N04   , Fn3 , v056
	.byte	W04
	.byte		        As3 , v108
	.byte	W04
	.byte		        Fn4 , v056
	.byte	W04
	.byte		N20   , As4 , v036
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx84:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx84_pri	@ Priority
	.byte	zfx84_rev	@ Reverb.

	.word	zfx84_grp

	.word	zfx84_1

	.end
