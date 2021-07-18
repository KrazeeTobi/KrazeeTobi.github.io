	.include "MPlayDef.s"

	.equ	zfx54_grp, voicegroup000
	.equ	zfx54_pri, 128
	.equ	zfx54_rev, reverb_set+50
	.equ	zfx54_mvl, 127
	.equ	zfx54_key, 0
	.equ	zfx54_tbs, 1
	.equ	zfx54_exg, 0
	.equ	zfx54_cmp, 1

	.section .rodata
	.global	zfx54
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx54_1:
	.byte		VOL   , 127*zfx54_mvl/mxv
	.byte	KEYSH , zfx54_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx54_tbs/2
	.byte		VOICE , 63
	.byte		N01   , Gs3 , v108
	.byte	W01
	.byte		        Fs3 , v124
	.byte	W01
	.byte		        Cs3 , v108
	.byte	W01
	.byte		        Cn4 , v104
	.byte	W01
	.byte		        Gs3 , v088
	.byte	W01
	.byte		        As3 , v080
	.byte	W01
	.byte		        Cs3 , v076
	.byte	W01
	.byte		        Fs3 , v068
	.byte	W01
	.byte		        As3 , v056
	.byte	W01
	.byte		        Bn3 , v048
	.byte	W01
	.byte		        Gs3 , v044
	.byte	W01
	.byte		        As3 , v040
	.byte	W01
	.byte		        Cs3 , v036
	.byte	W01
	.byte		        Cs4 
	.byte	W01
	.byte		        Fs3 , v032
	.byte	W01
	.byte	FINE

@******************************************************@
	.align	2

zfx54:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx54_pri	@ Priority
	.byte	zfx54_rev	@ Reverb.

	.word	zfx54_grp

	.word	zfx54_1

	.end
