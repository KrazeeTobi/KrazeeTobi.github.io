	.include "MPlayDef.s"

	.equ	zfx65_grp, voicegroup000
	.equ	zfx65_pri, 128
	.equ	zfx65_rev, reverb_set+50
	.equ	zfx65_mvl, 127
	.equ	zfx65_key, 0
	.equ	zfx65_tbs, 1
	.equ	zfx65_exg, 0
	.equ	zfx65_cmp, 1

	.section .rodata
	.global	zfx65
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx65_1:
	.byte		VOL   , 127*zfx65_mvl/mxv
	.byte	KEYSH , zfx65_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx65_tbs/2
	.byte		VOICE , 112
	.byte		N04   , Cs3 , v044
	.byte	W04
	.byte		        Cs3 , v068
	.byte	W04
	.byte		        Cs3 , v092
	.byte	W04
	.byte		        Cs3 , v108
	.byte	W04
	.byte		        Cs3 , v092
	.byte	W04
	.byte		        Cs3 , v068
	.byte	W04
	.byte		        Cs3 , v044
	.byte	W04
	.byte		N12   , Cs3 , v036
	.byte	W12
	.byte	FINE

@******************************************************@
	.align	2

zfx65:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx65_pri	@ Priority
	.byte	zfx65_rev	@ Reverb.

	.word	zfx65_grp

	.word	zfx65_1

	.end
