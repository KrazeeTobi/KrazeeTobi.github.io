	.include "MPlayDef.s"

	.equ	zfx81_grp, voicegroup000
	.equ	zfx81_pri, 128
	.equ	zfx81_rev, reverb_set+50
	.equ	zfx81_mvl, 127
	.equ	zfx81_key, 0
	.equ	zfx81_tbs, 1
	.equ	zfx81_exg, 0
	.equ	zfx81_cmp, 1

	.section .rodata
	.global	zfx81
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx81_1:
	.byte		VOL   , 127*zfx81_mvl/mxv
	.byte	KEYSH , zfx81_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx81_tbs/2
	.byte		VOICE , 11
	.byte		N32   , An1 , v108
	.byte	W32
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx81:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx81_pri	@ Priority
	.byte	zfx81_rev	@ Reverb.

	.word	zfx81_grp

	.word	zfx81_1

	.end
