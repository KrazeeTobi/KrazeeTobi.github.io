	.include "MPlayDef.s"

	.equ	zfx67_grp, voicegroup000
	.equ	zfx67_pri, 128
	.equ	zfx67_rev, reverb_set+50
	.equ	zfx67_mvl, 127
	.equ	zfx67_key, 0
	.equ	zfx67_tbs, 1
	.equ	zfx67_exg, 0
	.equ	zfx67_cmp, 1

	.section .rodata
	.global	zfx67
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx67_1:
	.byte		VOL   , 127*zfx67_mvl/mxv
	.byte	KEYSH , zfx67_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx67_tbs/2
	.byte		VOICE , 110
	.byte		N12   , Cs3 , v108
	.byte	W12
	.byte		N20   , Cs3 , v040
	.byte	W20
	.byte	FINE

@******************************************************@
	.align	2

zfx67:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx67_pri	@ Priority
	.byte	zfx67_rev	@ Reverb.

	.word	zfx67_grp

	.word	zfx67_1

	.end
