	.include "MPlayDef.s"

	.equ	zfx41_grp, voicegroup000
	.equ	zfx41_pri, 128
	.equ	zfx41_rev, reverb_set+50
	.equ	zfx41_mvl, 127
	.equ	zfx41_key, 0
	.equ	zfx41_tbs, 1
	.equ	zfx41_exg, 0
	.equ	zfx41_cmp, 1

	.section .rodata
	.global	zfx41
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx41_1:
	.byte		VOL   , 127*zfx41_mvl/mxv
	.byte	KEYSH , zfx41_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx41_tbs/2
	.byte		VOICE , 12
	.byte		N04   , An2 , v108
	.byte	W04
	.byte		        An2 , v056
	.byte	W04
	.byte		        An2 , v044
	.byte	W04
	.byte		        An2 , v036
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx41:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx41_pri	@ Priority
	.byte	zfx41_rev	@ Reverb.

	.word	zfx41_grp

	.word	zfx41_1

	.end
