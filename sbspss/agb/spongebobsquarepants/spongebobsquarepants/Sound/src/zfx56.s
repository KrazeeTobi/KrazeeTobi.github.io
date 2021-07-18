	.include "MPlayDef.s"

	.equ	zfx56_grp, voicegroup000
	.equ	zfx56_pri, 128
	.equ	zfx56_rev, reverb_set+50
	.equ	zfx56_mvl, 127
	.equ	zfx56_key, 0
	.equ	zfx56_tbs, 1
	.equ	zfx56_exg, 0
	.equ	zfx56_cmp, 1

	.section .rodata
	.global	zfx56
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx56_1:
	.byte		VOL   , 127*zfx56_mvl/mxv
	.byte	KEYSH , zfx56_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx56_tbs/2
	.byte		VOICE , 73
	.byte		N02   , Cn4 , v032
	.byte	W02
	.byte		        Cn4 , v036
	.byte	W02
	.byte		        Cn4 , v040
	.byte	W02
	.byte		        Cn4 , v044
	.byte	W03
	.byte		        Cn4 , v060
	.byte	W02
	.byte		        Cn4 , v080
	.byte	W02
	.byte		        Cn4 , v088
	.byte	W02
	.byte		        Cn4 , v096
	.byte	W03
	.byte		        Cn4 , v116
	.byte	W02
	.byte		        Cn4 , v124
	.byte	W02
	.byte		        Cn4 , v108
	.byte	W02
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W02
	.byte		N02   
	.byte	W02
	.byte		N02   
	.byte	W02
	.byte		        Cn4 , v116
	.byte	W03
	.byte		        Cn4 , v100
	.byte	W02
	.byte		        Cn4 , v088
	.byte	W02
	.byte		        Cn4 , v076
	.byte	W02
	.byte		        Cn4 , v060
	.byte	W03
	.byte		        Cn4 , v052
	.byte	W02
	.byte		        Cn4 , v040
	.byte	W02
	.byte		        Cn4 , v036
	.byte	W02
	.byte	FINE

@******************************************************@
	.align	2

zfx56:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx56_pri	@ Priority
	.byte	zfx56_rev	@ Reverb.

	.word	zfx56_grp

	.word	zfx56_1

	.end
