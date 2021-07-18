	.include "MPlayDef.s"

	.equ	zfx19_grp, voicegroup000
	.equ	zfx19_pri, 128
	.equ	zfx19_rev, reverb_set+50
	.equ	zfx19_mvl, 127
	.equ	zfx19_key, 0
	.equ	zfx19_tbs, 1
	.equ	zfx19_exg, 0
	.equ	zfx19_cmp, 1

	.section .rodata
	.global	zfx19
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx19_1:
	.byte		VOL   , 127*zfx19_mvl/mxv
	.byte	KEYSH , zfx19_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx19_tbs/2
	.byte		VOICE , 107
	.byte		N12   , Cs3 , v108
	.byte	W12
	.byte		N16   , Cs3 , v044
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx19:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx19_pri	@ Priority
	.byte	zfx19_rev	@ Reverb.

	.word	zfx19_grp

	.word	zfx19_1

	.end
