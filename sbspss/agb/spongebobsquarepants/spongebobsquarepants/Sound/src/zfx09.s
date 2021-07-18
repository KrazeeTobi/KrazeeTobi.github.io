	.include "MPlayDef.s"

	.equ	zfx09_grp, voicegroup000
	.equ	zfx09_pri, 128
	.equ	zfx09_rev, reverb_set+50
	.equ	zfx09_mvl, 127
	.equ	zfx09_key, 0
	.equ	zfx09_tbs, 1
	.equ	zfx09_exg, 0
	.equ	zfx09_cmp, 1

	.section .rodata
	.global	zfx09
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx09_1:
	.byte		VOL   , 127*zfx09_mvl/mxv
	.byte	KEYSH , zfx09_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx09_tbs/2
	.byte		VOICE , 73
	.byte		N04   , An1 , v108
	.byte	W04
	.byte		        As1 
	.byte	W04
	.byte		        Bn1 
	.byte	W04
	.byte		        Cn2 
	.byte	W04
	.byte		        Cs2 
	.byte	W04
	.byte		        Dn2 
	.byte	W04
	.byte		        Ds2 
	.byte	W04
	.byte		        En2 
	.byte	W04
	.byte		N12   , Fn2 
	.byte	W12
	.byte		        Fn2 , v056
	.byte	W12
	.byte		N16   , Fn2 , v040
	.byte	W16
	.byte	FINE

@******************************************************@
	.align	2

zfx09:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx09_pri	@ Priority
	.byte	zfx09_rev	@ Reverb.

	.word	zfx09_grp

	.word	zfx09_1

	.end
