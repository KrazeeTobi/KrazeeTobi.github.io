	.include "MPlayDef.s"

	.equ	zfx49_grp, voicegroup000
	.equ	zfx49_pri, 128
	.equ	zfx49_rev, reverb_set+50
	.equ	zfx49_mvl, 127
	.equ	zfx49_key, 0
	.equ	zfx49_tbs, 1
	.equ	zfx49_exg, 0
	.equ	zfx49_cmp, 1

	.section .rodata
	.global	zfx49
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx49_1:
	.byte		VOL   , 127*zfx49_mvl/mxv
	.byte	KEYSH , zfx49_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx49_tbs/2
	.byte		VOICE , 124
	.byte		N08   , Cs2 , v108
	.byte	W08
	.byte		        Cn2 
	.byte	W08
	.byte		        Bn1 , v092
	.byte	W08
	.byte		        As1 , v080
	.byte	W08
	.byte		        An1 , v068
	.byte	W08
	.byte		        Fs1 , v056
	.byte	W08
	.byte		        Ds1 , v048
	.byte	W08
	.byte		        Cn1 , v040
	.byte	W08
	.byte		        Gn0 , v036
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx49:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx49_pri	@ Priority
	.byte	zfx49_rev	@ Reverb.

	.word	zfx49_grp

	.word	zfx49_1

	.end
