	.include "MPlayDef.s"

	.equ	zfx38_grp, voicegroup000
	.equ	zfx38_pri, 128
	.equ	zfx38_rev, reverb_set+50
	.equ	zfx38_mvl, 127
	.equ	zfx38_key, 0
	.equ	zfx38_tbs, 1
	.equ	zfx38_exg, 0
	.equ	zfx38_cmp, 1

	.section .rodata
	.global	zfx38
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx38_1:
	.byte		VOL   , 127*zfx38_mvl/mxv
	.byte	KEYSH , zfx38_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx38_tbs/2
	.byte		VOICE , 52
	.byte		N03   , Cs5 , v108
	.byte	W03
	.byte		        Cn5 
	.byte	W03
	.byte		        Cs5 , v092
	.byte	W03
	.byte		        Cn5 , v108
	.byte	W04
	.byte		        Cs5 
	.byte	W03
	.byte		        Cn5 , v092
	.byte	W03
	.byte		        Cs5 , v108
	.byte	W03
	.byte		N06   , Cn5 , v092
	.byte	W07
	.byte	FINE

@******************************************************@
	.align	2

zfx38:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx38_pri	@ Priority
	.byte	zfx38_rev	@ Reverb.

	.word	zfx38_grp

	.word	zfx38_1

	.end
