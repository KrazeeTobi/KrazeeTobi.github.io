	.include "MPlayDef.s"

	.equ	zfx36_grp, voicegroup000
	.equ	zfx36_pri, 128
	.equ	zfx36_rev, reverb_set+50
	.equ	zfx36_mvl, 127
	.equ	zfx36_key, 0
	.equ	zfx36_tbs, 1
	.equ	zfx36_exg, 0
	.equ	zfx36_cmp, 1

	.section .rodata
	.global	zfx36
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx36_1:
	.byte		VOL   , 127*zfx36_mvl/mxv
	.byte	KEYSH , zfx36_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx36_tbs/2
	.byte		VOICE , 123
	.byte		N28   , Fs3 , v108
	.byte	W28
	.byte	W01
	.byte	FINE

@******************************************************@
	.align	2

zfx36:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx36_pri	@ Priority
	.byte	zfx36_rev	@ Reverb.

	.word	zfx36_grp

	.word	zfx36_1

	.end
