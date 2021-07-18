	.include "MPlayDef.s"

	.equ	zfx47_grp, voicegroup000
	.equ	zfx47_pri, 128
	.equ	zfx47_rev, reverb_set+50
	.equ	zfx47_mvl, 127
	.equ	zfx47_key, 0
	.equ	zfx47_tbs, 1
	.equ	zfx47_exg, 0
	.equ	zfx47_cmp, 1

	.section .rodata
	.global	zfx47
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx47_1:
	.byte		VOL   , 127*zfx47_mvl/mxv
	.byte	KEYSH , zfx47_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx47_tbs/2
	.byte		VOICE , 106
	.byte		N52   , Cs3 , v108
	.byte	W52
	.byte	FINE

@******************************************************@
	.align	2

zfx47:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx47_pri	@ Priority
	.byte	zfx47_rev	@ Reverb.

	.word	zfx47_grp

	.word	zfx47_1

	.end
