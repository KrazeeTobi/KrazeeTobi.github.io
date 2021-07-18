	.include "MPlayDef.s"

	.equ	zfx31_grp, voicegroup000
	.equ	zfx31_pri, 128
	.equ	zfx31_rev, reverb_set+50
	.equ	zfx31_mvl, 127
	.equ	zfx31_key, 0
	.equ	zfx31_tbs, 1
	.equ	zfx31_exg, 0
	.equ	zfx31_cmp, 1

	.section .rodata
	.global	zfx31
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx31_1:
	.byte		VOL   , 127*zfx31_mvl/mxv
	.byte	KEYSH , zfx31_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx31_tbs/2
	.byte		VOICE , 48
	.byte		N05   , An2 , v108
	.byte	W05
	.byte		        An2 , v056
	.byte	W06
	.byte		        An2 , v088
	.byte	W06
	.byte		        An2 , v108
	.byte	W06
	.byte		        An2 , v056
	.byte	W05
	.byte		        An2 , v108
	.byte	W06
	.byte		        An2 , v088
	.byte	W06
	.byte		        An2 , v056
	.byte	W06
	.byte		        An2 , v108
	.byte	W05
	.byte		        An2 , v088
	.byte	W06
	.byte		N17   , An2 , v108
	.byte	W17
	.byte	FINE

@******************************************************@
	.align	2

zfx31:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx31_pri	@ Priority
	.byte	zfx31_rev	@ Reverb.

	.word	zfx31_grp

	.word	zfx31_1

	.end
