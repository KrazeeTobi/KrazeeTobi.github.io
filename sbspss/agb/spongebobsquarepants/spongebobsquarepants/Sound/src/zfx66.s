	.include "MPlayDef.s"

	.equ	zfx66_grp, voicegroup000
	.equ	zfx66_pri, 128
	.equ	zfx66_rev, reverb_set+50
	.equ	zfx66_mvl, 127
	.equ	zfx66_key, 0
	.equ	zfx66_tbs, 1
	.equ	zfx66_exg, 0
	.equ	zfx66_cmp, 1

	.section .rodata
	.global	zfx66
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx66_1:
	.byte		VOL   , 127*zfx66_mvl/mxv
	.byte	KEYSH , zfx66_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx66_tbs/2
	.byte		VOICE , 124
	.byte		N32   , Cs3 , v108
	.byte	W32
	.byte	FINE

@******************************************************@
	.align	2

zfx66:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx66_pri	@ Priority
	.byte	zfx66_rev	@ Reverb.

	.word	zfx66_grp

	.word	zfx66_1

	.end
