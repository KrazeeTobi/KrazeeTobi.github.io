	.include "MPlayDef.s"

	.equ	zfx62_grp, voicegroup000
	.equ	zfx62_pri, 128
	.equ	zfx62_rev, reverb_set+50
	.equ	zfx62_mvl, 127
	.equ	zfx62_key, 0
	.equ	zfx62_tbs, 1
	.equ	zfx62_exg, 0
	.equ	zfx62_cmp, 1

	.section .rodata
	.global	zfx62
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx62_1:
	.byte		VOL   , 127*zfx62_mvl/mxv
	.byte	KEYSH , zfx62_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx62_tbs/2
	.byte		VOICE , 19
	.byte		N04   , Fs3 , v116
	.byte	W04
	.byte		        Cs4 
	.byte	W04
	.byte		        As3 
	.byte	W04
	.byte		        As3 , v056
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx62:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx62_pri	@ Priority
	.byte	zfx62_rev	@ Reverb.

	.word	zfx62_grp

	.word	zfx62_1

	.end
