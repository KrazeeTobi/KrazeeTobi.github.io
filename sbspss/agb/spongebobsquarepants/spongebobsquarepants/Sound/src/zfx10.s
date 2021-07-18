	.include "MPlayDef.s"

	.equ	zfx10_grp, voicegroup000
	.equ	zfx10_pri, 128
	.equ	zfx10_rev, reverb_set+50
	.equ	zfx10_mvl, 127
	.equ	zfx10_key, 0
	.equ	zfx10_tbs, 1
	.equ	zfx10_exg, 0
	.equ	zfx10_cmp, 1

	.section .rodata
	.global	zfx10
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx10_1:
	.byte		VOL   , 127*zfx10_mvl/mxv
	.byte	KEYSH , zfx10_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx10_tbs/2
	.byte		VOICE , 75
	.byte		N02   , Cn1 , v056
	.byte	W02
	.byte		        Gn1 , v080
	.byte	W02
	.byte		        An1 , v108
	.byte	W02
	.byte		        Cn2 , v127
	.byte	W03
	.byte		N04   , Gn2 , v108
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx10:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx10_pri	@ Priority
	.byte	zfx10_rev	@ Reverb.

	.word	zfx10_grp

	.word	zfx10_1

	.end
