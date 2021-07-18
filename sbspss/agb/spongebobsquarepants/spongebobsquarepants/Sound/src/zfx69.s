	.include "MPlayDef.s"

	.equ	zfx69_grp, voicegroup000
	.equ	zfx69_pri, 128
	.equ	zfx69_rev, reverb_set+50
	.equ	zfx69_mvl, 127
	.equ	zfx69_key, 0
	.equ	zfx69_tbs, 1
	.equ	zfx69_exg, 0
	.equ	zfx69_cmp, 1

	.section .rodata
	.global	zfx69
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx69_1:
	.byte		VOL   , 127*zfx69_mvl/mxv
	.byte	KEYSH , zfx69_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx69_tbs/2
	.byte		VOICE , 115
	.byte		N32   , As2 , v108
	.byte	W32
	.byte	FINE

@******************************************************@
	.align	2

zfx69:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx69_pri	@ Priority
	.byte	zfx69_rev	@ Reverb.

	.word	zfx69_grp

	.word	zfx69_1

	.end
