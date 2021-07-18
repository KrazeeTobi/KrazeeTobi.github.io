	.include "MPlayDef.s"

	.equ	zfx88_grp, voicegroup000
	.equ	zfx88_pri, 128
	.equ	zfx88_rev, reverb_set+50
	.equ	zfx88_mvl, 127
	.equ	zfx88_key, 0
	.equ	zfx88_tbs, 1
	.equ	zfx88_exg, 0
	.equ	zfx88_cmp, 1

	.section .rodata
	.global	zfx88
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx88_1:
	.byte		VOL   , 127*zfx88_mvl/mxv
	.byte	KEYSH , zfx88_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx88_tbs/2
	.byte		VOICE , 52
	.byte		N03   , Cs4 , v108
	.byte	W03
	.byte		        Fs3 
	.byte	W03
	.byte		        Fs3 , v044
	.byte	W03
	.byte		N13   , Fs3 , v040
	.byte	W13
	.byte	FINE

@******************************************************@
	.align	2

zfx88:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx88_pri	@ Priority
	.byte	zfx88_rev	@ Reverb.

	.word	zfx88_grp

	.word	zfx88_1

	.end
