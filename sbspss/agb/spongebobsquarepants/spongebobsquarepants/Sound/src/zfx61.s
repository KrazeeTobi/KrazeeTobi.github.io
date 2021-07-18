	.include "MPlayDef.s"

	.equ	zfx61_grp, voicegroup000
	.equ	zfx61_pri, 128
	.equ	zfx61_rev, reverb_set+50
	.equ	zfx61_mvl, 127
	.equ	zfx61_key, 0
	.equ	zfx61_tbs, 1
	.equ	zfx61_exg, 0
	.equ	zfx61_cmp, 1

	.section .rodata
	.global	zfx61
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx61_1:
	.byte		VOL   , 127*zfx61_mvl/mxv
	.byte	KEYSH , zfx61_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx61_tbs/2
	.byte		VOICE , 7
	.byte		N08   , As2 , v108
	.byte	W08
	.byte		N04   , As2 , v052
	.byte	W04
	.byte		        Cn3 , v108
	.byte	W04
	.byte		N08   , Dn3 
	.byte	W08
	.byte		        As2 
	.byte	W08
	.byte		        Fn3 
	.byte	W08
	.byte		        Fn3 , v052
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx61:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx61_pri	@ Priority
	.byte	zfx61_rev	@ Reverb.

	.word	zfx61_grp

	.word	zfx61_1

	.end
