	.include "MPlayDef.s"

	.equ	zfx85_grp, voicegroup000
	.equ	zfx85_pri, 128
	.equ	zfx85_rev, reverb_set+50
	.equ	zfx85_mvl, 127
	.equ	zfx85_key, 0
	.equ	zfx85_tbs, 1
	.equ	zfx85_exg, 0
	.equ	zfx85_cmp, 1

	.section .rodata
	.global	zfx85
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx85_1:
	.byte		VOL   , 127*zfx85_mvl/mxv
	.byte	KEYSH , zfx85_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx85_tbs/2
	.byte		VOICE , 10
	.byte		N08   , Fn2 , v108
	.byte	W08
	.byte		VOICE , 11
	.byte		N16   
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx85:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx85_pri	@ Priority
	.byte	zfx85_rev	@ Reverb.

	.word	zfx85_grp

	.word	zfx85_1

	.end
