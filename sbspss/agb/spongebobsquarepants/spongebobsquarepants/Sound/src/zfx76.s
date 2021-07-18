	.include "MPlayDef.s"

	.equ	zfx76_grp, voicegroup000
	.equ	zfx76_pri, 128
	.equ	zfx76_rev, reverb_set+50
	.equ	zfx76_mvl, 127
	.equ	zfx76_key, 0
	.equ	zfx76_tbs, 1
	.equ	zfx76_exg, 0
	.equ	zfx76_cmp, 1

	.section .rodata
	.global	zfx76
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx76_1:
	.byte		VOL   , 127*zfx76_mvl/mxv
	.byte	KEYSH , zfx76_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx76_tbs/2
	.byte		VOICE , 115
	.byte		N04   , An4 , v116
	.byte	W04
	.byte		        An4 , v056
	.byte	W04
	.byte		        An4 , v088
	.byte	W04
	.byte		        An4 , v048
	.byte	W04
	.byte		        An4 , v112
	.byte	W04
	.byte		        An4 , v088
	.byte	W04
	.byte	FINE

@******************************************************@
	.align	2

zfx76:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx76_pri	@ Priority
	.byte	zfx76_rev	@ Reverb.

	.word	zfx76_grp

	.word	zfx76_1

	.end
