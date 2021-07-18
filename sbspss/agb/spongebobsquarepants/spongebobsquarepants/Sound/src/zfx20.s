	.include "MPlayDef.s"

	.equ	zfx20_grp, voicegroup000
	.equ	zfx20_pri, 128
	.equ	zfx20_rev, reverb_set+50
	.equ	zfx20_mvl, 127
	.equ	zfx20_key, 0
	.equ	zfx20_tbs, 1
	.equ	zfx20_exg, 0
	.equ	zfx20_cmp, 1

	.section .rodata
	.global	zfx20
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx20_1:
	.byte		VOL   , 127*zfx20_mvl/mxv
	.byte	KEYSH , zfx20_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx20_tbs/2
	.byte		VOICE , 107
	.byte		N04   , As3 , v108
	.byte	W04
	.byte		        Gn3 
	.byte	W04
	.byte		        Cs4 , v052
	.byte	W04
	.byte		        Gn3 
	.byte	W04
	.byte		        Cs4 , v040
	.byte	W04
	.byte		        Gn3 
	.byte	W04
	.byte		        Cs4 , v032
	.byte	W04
	.byte		N16   , Gn3 
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx20:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx20_pri	@ Priority
	.byte	zfx20_rev	@ Reverb.

	.word	zfx20_grp

	.word	zfx20_1

	.end
