	.include "MPlayDef.s"

	.equ	zfx33_grp, voicegroup000
	.equ	zfx33_pri, 128
	.equ	zfx33_rev, reverb_set+50
	.equ	zfx33_mvl, 127
	.equ	zfx33_key, 0
	.equ	zfx33_tbs, 1
	.equ	zfx33_exg, 0
	.equ	zfx33_cmp, 1

	.section .rodata
	.global	zfx33
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx33_1:
	.byte		VOL   , 127*zfx33_mvl/mxv
	.byte	KEYSH , zfx33_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx33_tbs/2
	.byte		VOICE , 106
	.byte		N12   , En3 , v108
	.byte	W12
	.byte		        Bn2 , v120
	.byte	W12
	.byte		        Fs2 , v092
	.byte	W12
	.byte		        En2 , v080
	.byte	W12
	.byte		        Cs2 , v072
	.byte	W12
	.byte		        Bn1 , v060
	.byte	W12
	.byte		        As1 , v056
	.byte	W12
	.byte		        Gs1 , v048
	.byte	W12
@ 001   ----------------------------------------
	.byte		        Fs1 , v036
	.byte	W12
	.byte	FINE

@******************************************************@
	.align	2

zfx33:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx33_pri	@ Priority
	.byte	zfx33_rev	@ Reverb.

	.word	zfx33_grp

	.word	zfx33_1

	.end
