	.include "MPlayDef.s"

	.equ	zfx37_grp, voicegroup000
	.equ	zfx37_pri, 128
	.equ	zfx37_rev, reverb_set+50
	.equ	zfx37_mvl, 127
	.equ	zfx37_key, 0
	.equ	zfx37_tbs, 1
	.equ	zfx37_exg, 0
	.equ	zfx37_cmp, 1

	.section .rodata
	.global	zfx37
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx37_1:
	.byte		VOL   , 127*zfx37_mvl/mxv
	.byte	KEYSH , zfx37_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx37_tbs/2
	.byte		VOICE , 64
	.byte		N02   , Cs3 , v108
	.byte	W02
	.byte		        Cs3 , v056
	.byte	W02
	.byte		N15   , Fs3 , v108
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx37:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx37_pri	@ Priority
	.byte	zfx37_rev	@ Reverb.

	.word	zfx37_grp

	.word	zfx37_1

	.end
