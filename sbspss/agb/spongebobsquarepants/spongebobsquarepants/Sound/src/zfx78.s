	.include "MPlayDef.s"

	.equ	zfx78_grp, voicegroup000
	.equ	zfx78_pri, 128
	.equ	zfx78_rev, reverb_set+50
	.equ	zfx78_mvl, 127
	.equ	zfx78_key, 0
	.equ	zfx78_tbs, 1
	.equ	zfx78_exg, 0
	.equ	zfx78_cmp, 1

	.section .rodata
	.global	zfx78
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx78_1:
	.byte		VOL   , 127*zfx78_mvl/mxv
	.byte	KEYSH , zfx78_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx78_tbs/2
	.byte		VOICE , 106
	.byte		N76   , Fs2 , v108
	.byte	W76
	.byte	FINE

@******************************************************@
	.align	2

zfx78:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx78_pri	@ Priority
	.byte	zfx78_rev	@ Reverb.

	.word	zfx78_grp

	.word	zfx78_1

	.end
