	.include "MPlayDef.s"

	.equ	zfx44_grp, voicegroup000
	.equ	zfx44_pri, 128
	.equ	zfx44_rev, reverb_set+50
	.equ	zfx44_mvl, 127
	.equ	zfx44_key, 0
	.equ	zfx44_tbs, 1
	.equ	zfx44_exg, 0
	.equ	zfx44_cmp, 1

	.section .rodata
	.global	zfx44
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx44_1:
	.byte		VOL   , 127*zfx44_mvl/mxv
	.byte	KEYSH , zfx44_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx44_tbs/2
	.byte		VOICE , 11
	.byte		N15   , Cs2 , v108
	.byte	W15
	.byte		N24   , Cs2 , v056
	.byte	W24
	.byte	W01
	.byte	FINE

@******************************************************@
	.align	2

zfx44:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx44_pri	@ Priority
	.byte	zfx44_rev	@ Reverb.

	.word	zfx44_grp

	.word	zfx44_1

	.end
