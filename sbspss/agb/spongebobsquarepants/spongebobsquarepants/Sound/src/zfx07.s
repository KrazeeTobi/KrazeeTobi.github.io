	.include "MPlayDef.s"

	.equ	zfx07_grp, voicegroup000
	.equ	zfx07_pri, 128
	.equ	zfx07_rev, reverb_set+50
	.equ	zfx07_mvl, 127
	.equ	zfx07_key, 0
	.equ	zfx07_tbs, 1
	.equ	zfx07_exg, 0
	.equ	zfx07_cmp, 1

	.section .rodata
	.global	zfx07
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx07_1:
	.byte		VOL   , 127*zfx07_mvl/mxv
	.byte	KEYSH , zfx07_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx07_tbs/2
	.byte		VOICE , 104
	.byte		N28   , Cs3 , v108
	.byte	W28
	.byte	FINE

@******************************************************@
	.align	2

zfx07:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx07_pri	@ Priority
	.byte	zfx07_rev	@ Reverb.

	.word	zfx07_grp

	.word	zfx07_1

	.end
