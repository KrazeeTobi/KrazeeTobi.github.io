	.include "MPlayDef.s"

	.equ	zfx21_grp, voicegroup000
	.equ	zfx21_pri, 128
	.equ	zfx21_rev, reverb_set+50
	.equ	zfx21_mvl, 127
	.equ	zfx21_key, 0
	.equ	zfx21_tbs, 1
	.equ	zfx21_exg, 0
	.equ	zfx21_cmp, 1

	.section .rodata
	.global	zfx21
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx21_1:
	.byte		VOL   , 127*zfx21_mvl/mxv
	.byte	KEYSH , zfx21_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx21_tbs/2
	.byte		VOICE , 104
	.byte		N03   , Cs5 , v108
	.byte	W03
	.byte		        As4 , v096
	.byte	W03
	.byte		        An4 , v076
	.byte	W03
	.byte		        Gs4 , v056
	.byte	W04
	.byte		N13   , Fs4 , v044
	.byte	W13
	.byte	FINE

@******************************************************@
	.align	2

zfx21:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx21_pri	@ Priority
	.byte	zfx21_rev	@ Reverb.

	.word	zfx21_grp

	.word	zfx21_1

	.end
