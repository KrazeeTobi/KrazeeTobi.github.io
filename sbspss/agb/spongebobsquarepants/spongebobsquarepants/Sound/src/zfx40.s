	.include "MPlayDef.s"

	.equ	zfx40_grp, voicegroup000
	.equ	zfx40_pri, 128
	.equ	zfx40_rev, reverb_set+50
	.equ	zfx40_mvl, 127
	.equ	zfx40_key, 0
	.equ	zfx40_tbs, 1
	.equ	zfx40_exg, 0
	.equ	zfx40_cmp, 1

	.section .rodata
	.global	zfx40
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx40_1:
	.byte		VOL   , 127*zfx40_mvl/mxv
	.byte	KEYSH , zfx40_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx40_tbs/2
	.byte		VOICE , 121
	.byte		N05   , Cs4 , v108
	.byte	W05
	.byte		        Cs4 , v088
	.byte	W05
	.byte		        Cs4 , v068
	.byte	W05
	.byte		        Cs4 , v056
	.byte	W05
	.byte		        Cs4 , v044
	.byte	W05
	.byte	FINE

@******************************************************@
	.align	2

zfx40:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx40_pri	@ Priority
	.byte	zfx40_rev	@ Reverb.

	.word	zfx40_grp

	.word	zfx40_1

	.end
