	.include "MPlayDef.s"

	.equ	zfx46_grp, voicegroup000
	.equ	zfx46_pri, 128
	.equ	zfx46_rev, reverb_set+50
	.equ	zfx46_mvl, 127
	.equ	zfx46_key, 0
	.equ	zfx46_tbs, 1
	.equ	zfx46_exg, 0
	.equ	zfx46_cmp, 1

	.section .rodata
	.global	zfx46
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx46_1:
	.byte		VOL   , 127*zfx46_mvl/mxv
	.byte	KEYSH , zfx46_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx46_tbs/2
	.byte		VOICE , 2
	.byte		N02   , Ds4 , v112
	.byte	W02
	.byte		        Dn4 , v080
	.byte	W02
	.byte		        Cs4 , v064
	.byte	W02
	.byte		        Cn4 , v056
	.byte	W02
	.byte		        Bn3 , v044
	.byte	W02
	.byte		        As3 , v036
	.byte	W02
	.byte		        An3 , v032
	.byte	W02
	.byte		        Gs3 , v028
	.byte	W02
	.byte	FINE

@******************************************************@
	.align	2

zfx46:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx46_pri	@ Priority
	.byte	zfx46_rev	@ Reverb.

	.word	zfx46_grp

	.word	zfx46_1

	.end
