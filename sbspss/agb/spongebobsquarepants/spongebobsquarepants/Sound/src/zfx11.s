	.include "MPlayDef.s"

	.equ	zfx11_grp, voicegroup000
	.equ	zfx11_pri, 128
	.equ	zfx11_rev, reverb_set+50
	.equ	zfx11_mvl, 127
	.equ	zfx11_key, 0
	.equ	zfx11_tbs, 1
	.equ	zfx11_exg, 0
	.equ	zfx11_cmp, 1

	.section .rodata
	.global	zfx11
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx11_1:
	.byte		VOL   , 127*zfx11_mvl/mxv
	.byte	KEYSH , zfx11_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx11_tbs/2
	.byte		VOICE , 124
	.byte		N32   , Cs3 , v108
	.byte	W32
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx11:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx11_pri	@ Priority
	.byte	zfx11_rev	@ Reverb.

	.word	zfx11_grp

	.word	zfx11_1

	.end
