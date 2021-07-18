	.include "MPlayDef.s"

	.equ	zfx24_grp, voicegroup000
	.equ	zfx24_pri, 128
	.equ	zfx24_rev, reverb_set+50
	.equ	zfx24_mvl, 127
	.equ	zfx24_key, 0
	.equ	zfx24_tbs, 1
	.equ	zfx24_exg, 0
	.equ	zfx24_cmp, 1

	.section .rodata
	.global	zfx24
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx24_1:
	.byte		VOL   , 127*zfx24_mvl/mxv
	.byte	KEYSH , zfx24_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx24_tbs/2
	.byte		VOICE , 111
	.byte		N03   , Fs3 , v108
	.byte	W03
	.byte		        Fn3 , v092
	.byte	W03
	.byte		        En3 , v080
	.byte	W03
	.byte		        Ds3 , v076
	.byte	W04
	.byte		        Dn3 , v064
	.byte	W03
	.byte		        Cs3 , v056
	.byte	W03
	.byte		        Cn3 , v048
	.byte	W03
	.byte		        Bn2 , v044
	.byte	W04
	.byte		        As2 , v040
	.byte	W03
	.byte		        An2 , v036
	.byte	W03
	.byte		        Gs2 , v032
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx24:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx24_pri	@ Priority
	.byte	zfx24_rev	@ Reverb.

	.word	zfx24_grp

	.word	zfx24_1

	.end
