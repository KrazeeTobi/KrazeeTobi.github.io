	.include "MPlayDef.s"

	.equ	zfx43_grp, voicegroup000
	.equ	zfx43_pri, 128
	.equ	zfx43_rev, reverb_set+50
	.equ	zfx43_mvl, 127
	.equ	zfx43_key, 0
	.equ	zfx43_tbs, 1
	.equ	zfx43_exg, 0
	.equ	zfx43_cmp, 1

	.section .rodata
	.global	zfx43
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx43_1:
	.byte		VOL   , 127*zfx43_mvl/mxv
	.byte	KEYSH , zfx43_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx43_tbs/2
	.byte		VOICE , 114
	.byte		N09   , Bn2 , v108
	.byte	W09
	.byte		        Bn2 , v056
	.byte	W10
	.byte		        Bn2 , v040
	.byte	W10
	.byte	FINE

@******************************************************@
	.align	2

zfx43:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx43_pri	@ Priority
	.byte	zfx43_rev	@ Reverb.

	.word	zfx43_grp

	.word	zfx43_1

	.end
