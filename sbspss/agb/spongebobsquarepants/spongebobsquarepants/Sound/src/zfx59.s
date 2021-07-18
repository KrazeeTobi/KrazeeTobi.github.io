	.include "MPlayDef.s"

	.equ	zfx59_grp, voicegroup000
	.equ	zfx59_pri, 128
	.equ	zfx59_rev, reverb_set+50
	.equ	zfx59_mvl, 127
	.equ	zfx59_key, 0
	.equ	zfx59_tbs, 1
	.equ	zfx59_exg, 0
	.equ	zfx59_cmp, 1

	.section .rodata
	.global	zfx59
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx59_1:
	.byte		VOL   , 127*zfx59_mvl/mxv
	.byte	KEYSH , zfx59_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx59_tbs/2
	.byte		VOICE , 107
	.byte		N04   , Fs3 , v108
	.byte	W04
	.byte		        Gs4 
	.byte	W04
	.byte		N12   , Gs4 , v048
	.byte	W12
	.byte	FINE

@******************************************************@
	.align	2

zfx59:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx59_pri	@ Priority
	.byte	zfx59_rev	@ Reverb.

	.word	zfx59_grp

	.word	zfx59_1

	.end
