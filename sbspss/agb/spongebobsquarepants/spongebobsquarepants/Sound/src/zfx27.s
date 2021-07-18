	.include "MPlayDef.s"

	.equ	zfx27_grp, voicegroup000
	.equ	zfx27_pri, 128
	.equ	zfx27_rev, reverb_set+50
	.equ	zfx27_mvl, 127
	.equ	zfx27_key, 0
	.equ	zfx27_tbs, 1
	.equ	zfx27_exg, 0
	.equ	zfx27_cmp, 1

	.section .rodata
	.global	zfx27
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx27_1:
	.byte		VOL   , 127*zfx27_mvl/mxv
	.byte	KEYSH , zfx27_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx27_tbs/2
	.byte		VOICE , 10
	.byte		N04   , Fs2 , v108
	.byte	W04
	.byte		        Fs2 , v116
	.byte	W04
	.byte		        Fs2 , v108
	.byte	W04
	.byte		        Fs2 , v092
	.byte	W04
	.byte		        Fs2 , v108
	.byte	W04
	.byte		        Fs2 , v068
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx27:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx27_pri	@ Priority
	.byte	zfx27_rev	@ Reverb.

	.word	zfx27_grp

	.word	zfx27_1

	.end
