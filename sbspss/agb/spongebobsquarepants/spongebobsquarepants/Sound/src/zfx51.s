	.include "MPlayDef.s"

	.equ	zfx51_grp, voicegroup000
	.equ	zfx51_pri, 128
	.equ	zfx51_rev, reverb_set+50
	.equ	zfx51_mvl, 127
	.equ	zfx51_key, 0
	.equ	zfx51_tbs, 1
	.equ	zfx51_exg, 0
	.equ	zfx51_cmp, 1

	.section .rodata
	.global	zfx51
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx51_1:
	.byte		VOL   , 127*zfx51_mvl/mxv
	.byte	KEYSH , zfx51_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx51_tbs/2
	.byte		VOICE , 75
	.byte		N05   , Cn4 , v108
	.byte	W05
	.byte		        Cn4 , v068
	.byte	W05
	.byte		        Cn4 , v056
	.byte	W05
	.byte		        Cn4 , v048
	.byte	W05
	.byte		        Cn4 , v040
	.byte	W05
	.byte		        Cn4 , v032
	.byte	W05
	.byte	FINE

@******************************************************@
	.align	2

zfx51:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx51_pri	@ Priority
	.byte	zfx51_rev	@ Reverb.

	.word	zfx51_grp

	.word	zfx51_1

	.end
