	.include "MPlayDef.s"

	.equ	zfx00_grp, voicegroup000
	.equ	zfx00_pri, 128
	.equ	zfx00_rev, reverb_set+50
	.equ	zfx00_mvl, 127
	.equ	zfx00_key, 0
	.equ	zfx00_tbs, 1
	.equ	zfx00_exg, 0
	.equ	zfx00_cmp, 1

	.section .rodata
	.global	zfx00
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx00_1:
	.byte		VOL   , 127*zfx00_mvl/mxv
	.byte	KEYSH , zfx00_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx00_tbs/2
	.byte		VOICE , 8
	.byte		N15   , Fs2 , v080
	.byte	W15
	.byte	FINE

@******************************************************@
	.align	2

zfx00:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx00_pri	@ Priority
	.byte	zfx00_rev	@ Reverb.

	.word	zfx00_grp

	.word	zfx00_1

	.end
