	.include "MPlayDef.s"

	.equ	zfx48_grp, voicegroup000
	.equ	zfx48_pri, 128
	.equ	zfx48_rev, reverb_set+50
	.equ	zfx48_mvl, 127
	.equ	zfx48_key, 0
	.equ	zfx48_tbs, 1
	.equ	zfx48_exg, 0
	.equ	zfx48_cmp, 1

	.section .rodata
	.global	zfx48
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx48_1:
	.byte		VOL   , 127*zfx48_mvl/mxv
	.byte	KEYSH , zfx48_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx48_tbs/2
	.byte		VOICE , 123
	.byte		N36   , Cs3 , v108
	.byte	W36
	.byte	FINE

@******************************************************@
	.align	2

zfx48:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx48_pri	@ Priority
	.byte	zfx48_rev	@ Reverb.

	.word	zfx48_grp

	.word	zfx48_1

	.end
