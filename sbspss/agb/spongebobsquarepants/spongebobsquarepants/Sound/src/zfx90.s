	.include "MPlayDef.s"

	.equ	zfx90_grp, voicegroup000
	.equ	zfx90_pri, 128
	.equ	zfx90_rev, reverb_set+50
	.equ	zfx90_mvl, 127
	.equ	zfx90_key, 0
	.equ	zfx90_tbs, 1
	.equ	zfx90_exg, 0
	.equ	zfx90_cmp, 1

	.section .rodata
	.global	zfx90
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx90_1:
	.byte		VOL   , 127*zfx90_mvl/mxv
	.byte	KEYSH , zfx90_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx90_tbs/2
	.byte		VOICE , 47
	.byte		N08   , As2 , v108
	.byte	W08
	.byte		        En2 
	.byte	W08
	.byte		        En2 , v040
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx90:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx90_pri	@ Priority
	.byte	zfx90_rev	@ Reverb.

	.word	zfx90_grp

	.word	zfx90_1

	.end
