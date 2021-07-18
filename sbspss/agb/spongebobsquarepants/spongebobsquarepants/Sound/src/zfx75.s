	.include "MPlayDef.s"

	.equ	zfx75_grp, voicegroup000
	.equ	zfx75_pri, 128
	.equ	zfx75_rev, reverb_set+50
	.equ	zfx75_mvl, 127
	.equ	zfx75_key, 0
	.equ	zfx75_tbs, 1
	.equ	zfx75_exg, 0
	.equ	zfx75_cmp, 1

	.section .rodata
	.global	zfx75
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx75_1:
	.byte		VOL   , 127*zfx75_mvl/mxv
	.byte	KEYSH , zfx75_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx75_tbs/2
	.byte		VOICE , 110
	.byte		N12   , Fs3 , v108
	.byte	W12
	.byte		        Dn3 , v048
	.byte	W12
	.byte		N28   , Gs2 , v036
	.byte	W28
	.byte	FINE

@******************************************************@
	.align	2

zfx75:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx75_pri	@ Priority
	.byte	zfx75_rev	@ Reverb.

	.word	zfx75_grp

	.word	zfx75_1

	.end
