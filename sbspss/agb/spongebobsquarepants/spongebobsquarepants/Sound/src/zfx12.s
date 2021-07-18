	.include "MPlayDef.s"

	.equ	zfx12_grp, voicegroup000
	.equ	zfx12_pri, 128
	.equ	zfx12_rev, reverb_set+50
	.equ	zfx12_mvl, 127
	.equ	zfx12_key, 0
	.equ	zfx12_tbs, 1
	.equ	zfx12_exg, 0
	.equ	zfx12_cmp, 1

	.section .rodata
	.global	zfx12
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx12_1:
	.byte		VOL   , 127*zfx12_mvl/mxv
	.byte	KEYSH , zfx12_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx12_tbs/2
	.byte		VOICE , 114
	.byte		N20   , Cs3 , v108
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx12:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx12_pri	@ Priority
	.byte	zfx12_rev	@ Reverb.

	.word	zfx12_grp

	.word	zfx12_1

	.end
