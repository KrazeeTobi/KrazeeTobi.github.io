	.include "MPlayDef.s"

	.equ	zfx64_grp, voicegroup000
	.equ	zfx64_pri, 128
	.equ	zfx64_rev, reverb_set+50
	.equ	zfx64_mvl, 127
	.equ	zfx64_key, 0
	.equ	zfx64_tbs, 1
	.equ	zfx64_exg, 0
	.equ	zfx64_cmp, 1

	.section .rodata
	.global	zfx64
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx64_1:
	.byte		VOL   , 127*zfx64_mvl/mxv
	.byte	KEYSH , zfx64_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx64_tbs/2
	.byte		VOICE , 83
	.byte		N08   , Cn3 , v108
	.byte	W08
	.byte		N04   , Fn3 
	.byte	W04
	.byte		        Cn3 , v040
	.byte	W04
	.byte		        Gn3 , v108
	.byte	W04
	.byte		        Fn3 , v040
	.byte	W04
	.byte		N08   , An3 , v108
	.byte	W08
	.byte		N04   , Gn3 , v040
	.byte	W04
	.byte		N08   , An3 , v108
	.byte	W08
	.byte		        An3 , v040
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx64:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx64_pri	@ Priority
	.byte	zfx64_rev	@ Reverb.

	.word	zfx64_grp

	.word	zfx64_1

	.end
