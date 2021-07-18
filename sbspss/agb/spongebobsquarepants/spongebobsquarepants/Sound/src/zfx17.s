	.include "MPlayDef.s"

	.equ	zfx17_grp, voicegroup000
	.equ	zfx17_pri, 128
	.equ	zfx17_rev, reverb_set+50
	.equ	zfx17_mvl, 127
	.equ	zfx17_key, 0
	.equ	zfx17_tbs, 1
	.equ	zfx17_exg, 0
	.equ	zfx17_cmp, 1

	.section .rodata
	.global	zfx17
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx17_1:
	.byte		VOL   , 127*zfx17_mvl/mxv
	.byte	KEYSH , zfx17_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx17_tbs/2
	.byte		VOICE , 8
	.byte		N02   , Dn3 , v052
	.byte	W02
	.byte		        Dn3 , v060
	.byte	W02
	.byte		        Dn3 , v092
	.byte	W02
	.byte		N04   , Dn3 , v108
	.byte	W05
	.byte		N02   , Dn3 , v052
	.byte	W02
	.byte		N04   , Dn3 , v092
	.byte	W05
	.byte		N02   , Dn3 , v052
	.byte	W02
	.byte		N04   , Dn3 , v060
	.byte	W04
	.byte		N02   , Dn3 , v040
	.byte	W03
	.byte		N04   , Dn3 , v052
	.byte	W04
	.byte		N09   , Dn3 , v036
	.byte	W09
	.byte	FINE

@******************************************************@
	.align	2

zfx17:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx17_pri	@ Priority
	.byte	zfx17_rev	@ Reverb.

	.word	zfx17_grp

	.word	zfx17_1

	.end
