	.include "MPlayDef.s"

	.equ	zfx77_grp, voicegroup000
	.equ	zfx77_pri, 128
	.equ	zfx77_rev, reverb_set+50
	.equ	zfx77_mvl, 127
	.equ	zfx77_key, 0
	.equ	zfx77_tbs, 1
	.equ	zfx77_exg, 0
	.equ	zfx77_cmp, 1

	.section .rodata
	.global	zfx77
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx77_1:
	.byte		VOL   , 127*zfx77_mvl/mxv
	.byte	KEYSH , zfx77_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx77_tbs/2
	.byte		VOICE , 83
	.byte		N03   , Fs3 , v108
	.byte	W03
	.byte		        As3 , v092
	.byte	W03
	.byte		        Fs3 , v060
	.byte	W03
	.byte		        As3 , v052
	.byte	W04
	.byte		        Fs3 , v108
	.byte	W03
	.byte		        As3 , v092
	.byte	W03
	.byte		        Fs3 , v084
	.byte	W03
	.byte		        As3 , v068
	.byte	W04
	.byte		        Fs3 , v060
	.byte	W03
	.byte		        As3 , v052
	.byte	W03
	.byte		        Fs3 , v040
	.byte	W03
	.byte		        As3 , v036
	.byte	W04
	.byte		        Fs3 
	.byte	W03
	.byte		        As3 , v032
	.byte	W03
	.byte		        Fs3 
	.byte	W03
	.byte		        As3 , v028
	.byte	W03
	.byte	FINE

@******************************************************@
	.align	2

zfx77:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx77_pri	@ Priority
	.byte	zfx77_rev	@ Reverb.

	.word	zfx77_grp

	.word	zfx77_1

	.end
