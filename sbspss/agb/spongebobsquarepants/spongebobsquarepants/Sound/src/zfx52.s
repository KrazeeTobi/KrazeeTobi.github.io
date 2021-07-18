	.include "MPlayDef.s"

	.equ	zfx52_grp, voicegroup000
	.equ	zfx52_pri, 128
	.equ	zfx52_rev, reverb_set+50
	.equ	zfx52_mvl, 127
	.equ	zfx52_key, 0
	.equ	zfx52_tbs, 1
	.equ	zfx52_exg, 0
	.equ	zfx52_cmp, 1

	.section .rodata
	.global	zfx52
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx52_1:
	.byte		VOL   , 127*zfx52_mvl/mxv
	.byte	KEYSH , zfx52_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx52_tbs/2
	.byte		VOICE , 122
	.byte		N40   , Cs3 , v108
	.byte	W40
	.byte	FINE

@******************************************************@
	.align	2

zfx52:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx52_pri	@ Priority
	.byte	zfx52_rev	@ Reverb.

	.word	zfx52_grp

	.word	zfx52_1

	.end
