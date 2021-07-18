	.include "MPlayDef.s"

	.equ	zfx74_grp, voicegroup000
	.equ	zfx74_pri, 128
	.equ	zfx74_rev, reverb_set+50
	.equ	zfx74_mvl, 127
	.equ	zfx74_key, 0
	.equ	zfx74_tbs, 1
	.equ	zfx74_exg, 0
	.equ	zfx74_cmp, 1

	.section .rodata
	.global	zfx74
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx74_1:
	.byte		VOL   , 127*zfx74_mvl/mxv
	.byte	KEYSH , zfx74_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx74_tbs/2
	.byte		VOICE , 67
	.byte		N15   , Dn2 , v108
	.byte	W15
	.byte		N20   , Dn2 , v048
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx74:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx74_pri	@ Priority
	.byte	zfx74_rev	@ Reverb.

	.word	zfx74_grp

	.word	zfx74_1

	.end
