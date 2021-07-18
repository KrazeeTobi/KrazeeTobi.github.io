	.include "MPlayDef.s"

	.equ	zfx16_grp, voicegroup000
	.equ	zfx16_pri, 128
	.equ	zfx16_rev, reverb_set+50
	.equ	zfx16_mvl, 127
	.equ	zfx16_key, 0
	.equ	zfx16_tbs, 1
	.equ	zfx16_exg, 0
	.equ	zfx16_cmp, 1

	.section .rodata
	.global	zfx16
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx16_1:
	.byte		VOL   , 127*zfx16_mvl/mxv
	.byte	KEYSH , zfx16_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx16_tbs/2
	.byte		VOICE , 103
	.byte		N32   , Cs3 , v108
	.byte	W32
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx16:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx16_pri	@ Priority
	.byte	zfx16_rev	@ Reverb.

	.word	zfx16_grp

	.word	zfx16_1

	.end
