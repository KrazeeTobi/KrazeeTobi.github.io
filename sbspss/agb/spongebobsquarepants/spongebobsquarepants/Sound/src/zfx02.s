	.include "MPlayDef.s"

	.equ	zfx02_grp, voicegroup000
	.equ	zfx02_pri, 128
	.equ	zfx02_rev, reverb_set+50
	.equ	zfx02_mvl, 127
	.equ	zfx02_key, 0
	.equ	zfx02_tbs, 1
	.equ	zfx02_exg, 0
	.equ	zfx02_cmp, 1

	.section .rodata
	.global	zfx02
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx02_1:
	.byte		VOL   , 127*zfx02_mvl/mxv
	.byte	KEYSH , zfx02_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx02_tbs/2
	.byte		VOICE , 120
	.byte		N15   , Cs3 , v108
	.byte	W15
	.byte	FINE

@******************************************************@
	.align	2

zfx02:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx02_pri	@ Priority
	.byte	zfx02_rev	@ Reverb.

	.word	zfx02_grp

	.word	zfx02_1

	.end
