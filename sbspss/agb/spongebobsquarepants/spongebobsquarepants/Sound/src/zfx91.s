	.include "MPlayDef.s"

	.equ	zfx91_grp, voicegroup000
	.equ	zfx91_pri, 128
	.equ	zfx91_rev, reverb_set+50
	.equ	zfx91_mvl, 127
	.equ	zfx91_key, 0
	.equ	zfx91_tbs, 1
	.equ	zfx91_exg, 0
	.equ	zfx91_cmp, 1

	.section .rodata
	.global	zfx91
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx91_1:
	.byte		VOL   , 127*zfx91_mvl/mxv
	.byte	KEYSH , zfx91_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx91_tbs/2
	.byte		VOICE , 19
	.byte		N04   , As2 , v108
	.byte	W04
	.byte		        Dn3 
	.byte	W04
	.byte		N08   , Fn3 
	.byte	W08
	.byte		        Fn3 , v048
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx91:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx91_pri	@ Priority
	.byte	zfx91_rev	@ Reverb.

	.word	zfx91_grp

	.word	zfx91_1

	.end
