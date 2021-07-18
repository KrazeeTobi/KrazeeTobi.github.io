	.include "MPlayDef.s"

	.equ	zfx83_grp, voicegroup000
	.equ	zfx83_pri, 128
	.equ	zfx83_rev, reverb_set+50
	.equ	zfx83_mvl, 127
	.equ	zfx83_key, 0
	.equ	zfx83_tbs, 1
	.equ	zfx83_exg, 0
	.equ	zfx83_cmp, 1

	.section .rodata
	.global	zfx83
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx83_1:
	.byte		VOL   , 127*zfx83_mvl/mxv
	.byte	KEYSH , zfx83_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx83_tbs/2
	.byte		VOICE , 121
	.byte		N08   , Cs3 , v056
	.byte	W08
	.byte		        Cs3 , v116
	.byte	W08
	.byte		        Cs3 , v040
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx83:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx83_pri	@ Priority
	.byte	zfx83_rev	@ Reverb.

	.word	zfx83_grp

	.word	zfx83_1

	.end
