	.include "MPlayDef.s"

	.equ	zfx55_grp, voicegroup000
	.equ	zfx55_pri, 128
	.equ	zfx55_rev, reverb_set+50
	.equ	zfx55_mvl, 127
	.equ	zfx55_key, 0
	.equ	zfx55_tbs, 1
	.equ	zfx55_exg, 0
	.equ	zfx55_cmp, 1

	.section .rodata
	.global	zfx55
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx55_1:
	.byte		VOL   , 127*zfx55_mvl/mxv
	.byte	KEYSH , zfx55_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx55_tbs/2
	.byte		VOICE , 63
	.byte		N04   , Gs3 , v108
	.byte	W04
	.byte		        Gs3 , v056
	.byte	W05
	.byte		        Gs3 , v040
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx55:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx55_pri	@ Priority
	.byte	zfx55_rev	@ Reverb.

	.word	zfx55_grp

	.word	zfx55_1

	.end
