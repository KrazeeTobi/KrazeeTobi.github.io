	.include "MPlayDef.s"

	.equ	zfx42_grp, voicegroup000
	.equ	zfx42_pri, 128
	.equ	zfx42_rev, reverb_set+50
	.equ	zfx42_mvl, 127
	.equ	zfx42_key, 0
	.equ	zfx42_tbs, 1
	.equ	zfx42_exg, 0
	.equ	zfx42_cmp, 1

	.section .rodata
	.global	zfx42
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx42_1:
	.byte		VOL   , 127*zfx42_mvl/mxv
	.byte	KEYSH , zfx42_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx42_tbs/2
	.byte		VOICE , 114
	.byte		N06   , Fs2 , v108
	.byte	W06
	.byte		VOICE , 63
	.byte		N06   , Cs3 
	.byte	W07
	.byte		        Cs3 , v056
	.byte	W06
	.byte		N09   , Cs3 , v040
	.byte	W10
	.byte	FINE

@******************************************************@
	.align	2

zfx42:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx42_pri	@ Priority
	.byte	zfx42_rev	@ Reverb.

	.word	zfx42_grp

	.word	zfx42_1

	.end
