	.include "MPlayDef.s"

	.equ	zfx86_grp, voicegroup000
	.equ	zfx86_pri, 128
	.equ	zfx86_rev, reverb_set+50
	.equ	zfx86_mvl, 127
	.equ	zfx86_key, 0
	.equ	zfx86_tbs, 1
	.equ	zfx86_exg, 0
	.equ	zfx86_cmp, 1

	.section .rodata
	.global	zfx86
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx86_1:
	.byte		VOL   , 127*zfx86_mvl/mxv
	.byte	KEYSH , zfx86_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx86_tbs/2
	.byte		VOICE , 5
	.byte		N08   , As2 , v108
	.byte	W08
	.byte		        As2 , v068
	.byte	W08
	.byte		N04   , As2 , v080
	.byte	W04
	.byte		        As2 , v092
	.byte	W04
	.byte		N08   , As2 , v108
	.byte	W08
	.byte		        As2 , v068
	.byte	W08
	.byte		N04   , As2 , v080
	.byte	W04
	.byte		        As2 , v092
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx86:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx86_pri	@ Priority
	.byte	zfx86_rev	@ Reverb.

	.word	zfx86_grp

	.word	zfx86_1

	.end
