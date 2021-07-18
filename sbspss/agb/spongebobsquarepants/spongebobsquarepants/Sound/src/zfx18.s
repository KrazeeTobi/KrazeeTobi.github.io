	.include "MPlayDef.s"

	.equ	zfx18_grp, voicegroup000
	.equ	zfx18_pri, 128
	.equ	zfx18_rev, reverb_set+50
	.equ	zfx18_mvl, 127
	.equ	zfx18_key, 0
	.equ	zfx18_tbs, 1
	.equ	zfx18_exg, 0
	.equ	zfx18_cmp, 1

	.section .rodata
	.global	zfx18
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx18_1:
	.byte		VOL   , 127*zfx18_mvl/mxv
	.byte	KEYSH , zfx18_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx18_tbs/2
	.byte		VOICE , 111
	.byte		N24   , Fs2 , v108
	.byte	W24
	.byte	W01
	.byte	FINE

@******************************************************@
	.align	2

zfx18:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx18_pri	@ Priority
	.byte	zfx18_rev	@ Reverb.

	.word	zfx18_grp

	.word	zfx18_1

	.end
