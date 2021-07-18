	.include "MPlayDef.s"

	.equ	zfx32_grp, voicegroup000
	.equ	zfx32_pri, 128
	.equ	zfx32_rev, reverb_set+50
	.equ	zfx32_mvl, 127
	.equ	zfx32_key, 0
	.equ	zfx32_tbs, 1
	.equ	zfx32_exg, 0
	.equ	zfx32_cmp, 1

	.section .rodata
	.global	zfx32
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx32_1:
	.byte		VOL   , 127*zfx32_mvl/mxv
	.byte	KEYSH , zfx32_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx32_tbs/2
	.byte		VOICE , 104
	.byte		N28   , Fs2 , v108
	.byte	W28
	.byte		N44   , Cs2 , v092
	.byte	W44
	.byte	W02
	.byte	FINE

@******************************************************@
	.align	2

zfx32:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx32_pri	@ Priority
	.byte	zfx32_rev	@ Reverb.

	.word	zfx32_grp

	.word	zfx32_1

	.end
