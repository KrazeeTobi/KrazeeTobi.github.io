	.include "MPlayDef.s"

	.equ	zfx25_grp, voicegroup000
	.equ	zfx25_pri, 128
	.equ	zfx25_rev, reverb_set+50
	.equ	zfx25_mvl, 127
	.equ	zfx25_key, 0
	.equ	zfx25_tbs, 1
	.equ	zfx25_exg, 0
	.equ	zfx25_cmp, 1

	.section .rodata
	.global	zfx25
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx25_1:
	.byte		VOL   , 127*zfx25_mvl/mxv
	.byte	KEYSH , zfx25_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx25_tbs/2
	.byte		VOICE , 113
	.byte		N02   , Ds3 , v108
	.byte	W02
	.byte		N04   , Gn3 
	.byte	W04
	.byte		N06   , Gn3 , v048
	.byte	W07
	.byte		N15   , Gn3 , v040
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx25:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx25_pri	@ Priority
	.byte	zfx25_rev	@ Reverb.

	.word	zfx25_grp

	.word	zfx25_1

	.end
