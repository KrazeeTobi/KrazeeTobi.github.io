	.include "MPlayDef.s"

	.equ	zfx87_grp, voicegroup000
	.equ	zfx87_pri, 128
	.equ	zfx87_rev, reverb_set+50
	.equ	zfx87_mvl, 127
	.equ	zfx87_key, 0
	.equ	zfx87_tbs, 1
	.equ	zfx87_exg, 0
	.equ	zfx87_cmp, 1

	.section .rodata
	.global	zfx87
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx87_1:
	.byte		VOL   , 127*zfx87_mvl/mxv
	.byte	KEYSH , zfx87_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx87_tbs/2
	.byte		VOICE , 115
	.byte		N56   , Cs2 , v108
	.byte	W56
	.byte	FINE

@******************************************************@
	.align	2

zfx87:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx87_pri	@ Priority
	.byte	zfx87_rev	@ Reverb.

	.word	zfx87_grp

	.word	zfx87_1

	.end
