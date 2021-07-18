	.include "MPlayDef.s"

	.equ	zfx72_grp, voicegroup000
	.equ	zfx72_pri, 128
	.equ	zfx72_rev, reverb_set+50
	.equ	zfx72_mvl, 127
	.equ	zfx72_key, 0
	.equ	zfx72_tbs, 1
	.equ	zfx72_exg, 0
	.equ	zfx72_cmp, 1

	.section .rodata
	.global	zfx72
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx72_1:
	.byte		VOL   , 127*zfx72_mvl/mxv
	.byte	KEYSH , zfx72_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx72_tbs/2
	.byte		VOICE , 107
	.byte		N05   , Fs4 , v108
	.byte	W05
	.byte		        Dn4 , v060
	.byte	W05
	.byte	FINE

@******************************************************@
	.align	2

zfx72:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx72_pri	@ Priority
	.byte	zfx72_rev	@ Reverb.

	.word	zfx72_grp

	.word	zfx72_1

	.end
