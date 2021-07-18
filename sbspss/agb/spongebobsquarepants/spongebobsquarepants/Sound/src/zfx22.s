	.include "MPlayDef.s"

	.equ	zfx22_grp, voicegroup000
	.equ	zfx22_pri, 128
	.equ	zfx22_rev, reverb_set+50
	.equ	zfx22_mvl, 127
	.equ	zfx22_key, 0
	.equ	zfx22_tbs, 1
	.equ	zfx22_exg, 0
	.equ	zfx22_cmp, 1

	.section .rodata
	.global	zfx22
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx22_1:
	.byte		VOL   , 127*zfx22_mvl/mxv
	.byte	KEYSH , zfx22_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx22_tbs/2
	.byte		VOICE , 18
	.byte		N03   , Dn2 , v052
	.byte	W03
	.byte		        Fn2 , v068
	.byte	W03
	.byte		        Gs2 , v092
	.byte	W03
	.byte		        An2 , v124
	.byte	W04
	.byte		N06   , As2 , v108
	.byte	W06
	.byte		N03   , An2 
	.byte	W03
	.byte		        Gs2 , v100
	.byte	W04
	.byte		        Fn2 , v076
	.byte	W03
	.byte		        Dn2 , v056
	.byte	W03
	.byte		        Cn2 , v048
	.byte	W03
	.byte		        As1 , v040
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx22:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx22_pri	@ Priority
	.byte	zfx22_rev	@ Reverb.

	.word	zfx22_grp

	.word	zfx22_1

	.end
