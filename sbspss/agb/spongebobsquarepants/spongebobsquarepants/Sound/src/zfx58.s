	.include "MPlayDef.s"

	.equ	zfx58_grp, voicegroup000
	.equ	zfx58_pri, 128
	.equ	zfx58_rev, reverb_set+50
	.equ	zfx58_mvl, 127
	.equ	zfx58_key, 0
	.equ	zfx58_tbs, 1
	.equ	zfx58_exg, 0
	.equ	zfx58_cmp, 1

	.section .rodata
	.global	zfx58
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx58_1:
	.byte		VOL   , 127*zfx58_mvl/mxv
	.byte	KEYSH , zfx58_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx58_tbs/2
	.byte		VOICE , 108
	.byte		N08   , Gs3 , v068
	.byte	W08
	.byte		        Gs3 , v080
	.byte	W08
	.byte		        Gs3 , v068
	.byte	W08
	.byte		        Gs3 , v108
	.byte	W08
	.byte		        Gs3 , v080
	.byte	W08
	.byte		        Gs3 , v068
	.byte	W08
	.byte		        Gs3 , v108
	.byte	W08
	.byte		        Gs3 , v068
	.byte	W08
	.byte		        Gs3 , v108
	.byte	W08
	.byte		        An2 , v056
	.byte	W08
	.byte	FINE

@******************************************************@
	.align	2

zfx58:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx58_pri	@ Priority
	.byte	zfx58_rev	@ Reverb.

	.word	zfx58_grp

	.word	zfx58_1

	.end
