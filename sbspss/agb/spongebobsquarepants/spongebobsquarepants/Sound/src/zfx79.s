	.include "MPlayDef.s"

	.equ	zfx79_grp, voicegroup000
	.equ	zfx79_pri, 128
	.equ	zfx79_rev, reverb_set+50
	.equ	zfx79_mvl, 127
	.equ	zfx79_key, 0
	.equ	zfx79_tbs, 1
	.equ	zfx79_exg, 0
	.equ	zfx79_cmp, 1

	.section .rodata
	.global	zfx79
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx79_1:
	.byte		VOL   , 127*zfx79_mvl/mxv
	.byte	KEYSH , zfx79_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx79_tbs/2
	.byte		VOICE , 120
	.byte		N05   , Fs1 , v108
	.byte	W05
	.byte		        Cs2 
	.byte	W05
	.byte		        Cs2 , v044
	.byte	W05
	.byte	FINE

@******************************************************@
	.align	2

zfx79:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx79_pri	@ Priority
	.byte	zfx79_rev	@ Reverb.

	.word	zfx79_grp

	.word	zfx79_1

	.end
