	.include "MPlayDef.s"

	.equ	zfx08_grp, voicegroup000
	.equ	zfx08_pri, 128
	.equ	zfx08_rev, reverb_set+50
	.equ	zfx08_mvl, 127
	.equ	zfx08_key, 0
	.equ	zfx08_tbs, 1
	.equ	zfx08_exg, 0
	.equ	zfx08_cmp, 1

	.section .rodata
	.global	zfx08
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx08_1:
	.byte		VOL   , 127*zfx08_mvl/mxv
	.byte	KEYSH , zfx08_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx08_tbs/2
	.byte		VOICE , 27
	.byte		N12   , Fn2 , v108
	.byte	W12
	.byte		        En2 
	.byte	W12
	.byte		        Ds2 
	.byte	W12
	.byte		        Dn2 
	.byte	W12
	.byte		N16   , Cs2 
	.byte	W16
	.byte		        Cs2 , v056
	.byte	W16
	.byte		        Cs2 , v040
	.byte	W16
@ 001   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

zfx08:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx08_pri	@ Priority
	.byte	zfx08_rev	@ Reverb.

	.word	zfx08_grp

	.word	zfx08_1

	.end
