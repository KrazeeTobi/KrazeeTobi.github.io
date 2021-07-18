	.include "MPlayDef.s"

	.equ	zfx34_grp, voicegroup000
	.equ	zfx34_pri, 128
	.equ	zfx34_rev, reverb_set+50
	.equ	zfx34_mvl, 127
	.equ	zfx34_key, 0
	.equ	zfx34_tbs, 1
	.equ	zfx34_exg, 0
	.equ	zfx34_cmp, 1

	.section .rodata
	.global	zfx34
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx34_1:
	.byte		VOL   , 127*zfx34_mvl/mxv
	.byte	KEYSH , zfx34_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx34_tbs/2
	.byte		VOICE , 118
	.byte		N06   , Ds3 , v108
	.byte	W06
	.byte		        Ds3 , v088
	.byte	W07
	.byte		        Ds3 , v120
	.byte	W06
	.byte		        Ds3 , v096
	.byte	W07
	.byte		        Ds3 , v088
	.byte	W06
	.byte		        Ds3 , v068
	.byte	W07
	.byte		        Ds3 , v080
	.byte	W06
	.byte		        Ds3 , v108
	.byte	W07
	.byte		        Ds3 , v088
	.byte	W06
	.byte		N32   , Ds3 , v096
	.byte	W36
	.byte	FINE

@******************************************************@
	.align	2

zfx34:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx34_pri	@ Priority
	.byte	zfx34_rev	@ Reverb.

	.word	zfx34_grp

	.word	zfx34_1

	.end
