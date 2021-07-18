	.include "MPlayDef.s"

	.equ	zfx35_grp, voicegroup000
	.equ	zfx35_pri, 128
	.equ	zfx35_rev, reverb_set+50
	.equ	zfx35_mvl, 127
	.equ	zfx35_key, 0
	.equ	zfx35_tbs, 1
	.equ	zfx35_exg, 0
	.equ	zfx35_cmp, 1

	.section .rodata
	.global	zfx35
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx35_1:
	.byte		VOL   , 127*zfx35_mvl/mxv
	.byte	KEYSH , zfx35_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx35_tbs/2
	.byte		VOICE , 115
	.byte		N13   , En3 , v108
	.byte	W13
	.byte		        Cn3 , v092
	.byte	W13
	.byte		        Gn2 , v076
	.byte	W13
	.byte		        Dn2 , v056
	.byte	W13
	.byte		N32   , As1 , v040
	.byte	W32
	.byte	FINE

@******************************************************@
	.align	2

zfx35:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx35_pri	@ Priority
	.byte	zfx35_rev	@ Reverb.

	.word	zfx35_grp

	.word	zfx35_1

	.end
