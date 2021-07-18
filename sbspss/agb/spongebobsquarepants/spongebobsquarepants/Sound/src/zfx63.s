	.include "MPlayDef.s"

	.equ	zfx63_grp, voicegroup000
	.equ	zfx63_pri, 128
	.equ	zfx63_rev, reverb_set+50
	.equ	zfx63_mvl, 127
	.equ	zfx63_key, 0
	.equ	zfx63_tbs, 1
	.equ	zfx63_exg, 0
	.equ	zfx63_cmp, 1

	.section .rodata
	.global	zfx63
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx63_1:
	.byte		VOL   , 127*zfx63_mvl/mxv
	.byte	KEYSH , zfx63_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx63_tbs/2
	.byte		VOICE , 21
	.byte		N04   , Cn4 , v108
	.byte	W04
	.byte		        Dn4 
	.byte	W04
	.byte		        En4 
	.byte	W04
	.byte		        Dn4 
	.byte	W04
	.byte		        Dn4 , v052
	.byte	W04
	.byte		        En4 , v108
	.byte	W04
	.byte		        Cn4 
	.byte	W04
	.byte		        Cn4 , v052
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx63:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx63_pri	@ Priority
	.byte	zfx63_rev	@ Reverb.

	.word	zfx63_grp

	.word	zfx63_1

	.end
