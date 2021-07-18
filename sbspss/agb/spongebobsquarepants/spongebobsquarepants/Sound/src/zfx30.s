	.include "MPlayDef.s"

	.equ	zfx30_grp, voicegroup000
	.equ	zfx30_pri, 128
	.equ	zfx30_rev, reverb_set+50
	.equ	zfx30_mvl, 127
	.equ	zfx30_key, 0
	.equ	zfx30_tbs, 1
	.equ	zfx30_exg, 0
	.equ	zfx30_cmp, 1

	.section .rodata
	.global	zfx30
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx30_1:
	.byte		VOL   , 127*zfx30_mvl/mxv
	.byte	KEYSH , zfx30_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx30_tbs/2
	.byte		VOICE , 119
	.byte		N03   , Gn3 , v080
	.byte	W03
	.byte		        Fs3 , v056
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx30:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx30_pri	@ Priority
	.byte	zfx30_rev	@ Reverb.

	.word	zfx30_grp

	.word	zfx30_1

	.end
