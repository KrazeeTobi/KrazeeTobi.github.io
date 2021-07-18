	.include "MPlayDef.s"

	.equ	zfx57_grp, voicegroup000
	.equ	zfx57_pri, 128
	.equ	zfx57_rev, reverb_set+50
	.equ	zfx57_mvl, 127
	.equ	zfx57_key, 0
	.equ	zfx57_tbs, 1
	.equ	zfx57_exg, 0
	.equ	zfx57_cmp, 1

	.section .rodata
	.global	zfx57
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx57_1:
	.byte		VOL   , 127*zfx57_mvl/mxv
	.byte	KEYSH , zfx57_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx57_tbs/2
	.byte		VOICE , 114
	.byte		N02   , Cs2 , v036
	.byte	W02
	.byte		        Gn2 , v052
	.byte	W02
	.byte		        Gs2 , v060
	.byte	W02
	.byte		        An2 , v080
	.byte	W03
	.byte		        As2 , v088
	.byte	W02
	.byte		        Bn2 , v096
	.byte	W02
	.byte		VOICE , 110
	.byte		N04   , Cn3 , v112
	.byte	W05
	.byte		        Cs3 , v088
	.byte	W04
	.byte		        Dn3 , v060
	.byte	W05
	.byte		        Ds3 , v056
	.byte	W04
	.byte		N24   , En3 , v048
	.byte	W24
	.byte	W01
	.byte	FINE

@******************************************************@
	.align	2

zfx57:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx57_pri	@ Priority
	.byte	zfx57_rev	@ Reverb.

	.word	zfx57_grp

	.word	zfx57_1

	.end
