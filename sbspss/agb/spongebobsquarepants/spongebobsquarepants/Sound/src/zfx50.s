	.include "MPlayDef.s"

	.equ	zfx50_grp, voicegroup000
	.equ	zfx50_pri, 128
	.equ	zfx50_rev, reverb_set+50
	.equ	zfx50_mvl, 127
	.equ	zfx50_key, 0
	.equ	zfx50_tbs, 1
	.equ	zfx50_exg, 0
	.equ	zfx50_cmp, 1

	.section .rodata
	.global	zfx50
	.align	2

@**************** Track 1 (Midi-Chn.5) ****************@

zfx50_1:
	.byte		VOL   , 127*zfx50_mvl/mxv
	.byte	KEYSH , zfx50_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 100*zfx50_tbs/2
	.byte		VOICE , 106
	.byte		N20   , Fs3 , v108
	.byte	W20
	.byte		N36   , Dn3 , v056
	.byte	W36
	.byte	FINE

@******************************************************@
	.align	2

zfx50:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	zfx50_pri	@ Priority
	.byte	zfx50_rev	@ Reverb.

	.word	zfx50_grp

	.word	zfx50_1

	.end
