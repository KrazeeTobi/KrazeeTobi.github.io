	.include "MPlayDef.s"

	.equ	zfx39_grp, voicegroup000
	.equ	zfx39_pri, 128
	.equ	zfx39_rev, reverb_set+50
	.equ	zfx39_mvl, 127
	.equ	zfx39_key, 0
	.equ	zfx39_tbs, 1
	.equ	zfx39_exg, 0
	.equ	zfx39_cmp, 1

	.section .rodata
	.global	zfx39
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx39_1:
	.byte		VOL   , 127*zfx39_mvl/mxv
	.byte	KEYSH , zfx39_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx39_tbs/2
	.byte		VOICE , 52
	.byte		N04   , As3 , v108
	.byte	W04
	.byte		        Bn3 
	.byte	W04
	.byte		        As3 , v092
	.byte	W04
	.byte		        Bn3 , v108
	.byte	W04
	.byte		        As3 
	.byte	W04
	.byte		        Bn3 , v092
	.byte	W04
	.byte		        As3 , v108
	.byte	W04
	.byte		N08   , Bn3 , v092
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx39:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx39_pri	@ Priority
	.byte	zfx39_rev	@ Reverb.

	.word	zfx39_grp

	.word	zfx39_1

	.end
