	.include "MPlayDef.s"

	.equ	m_Sample_01_grp, voicegroup003
	.equ	m_Sample_01_pri, 0
	.equ	m_Sample_01_rev, 0
	.equ	m_Sample_01_mvl, 120
	.equ	m_Sample_01_key, 0
	.equ	m_Sample_01_tbs, 1
	.equ	m_Sample_01_exg, 0
	.equ	m_Sample_01_cmp, 1

	.section .rodata
	.global	m_Sample_01
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

m_Sample_01_1:
	.byte	KEYSH , m_Sample_01_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 69*m_Sample_01_tbs/2
	.byte		VOICE , 1
	.byte		VOL   , 100*m_Sample_01_mvl/mxv
	.byte		PAN   , c_v-54
	.byte		TUNE  , c_v-59
	.byte		N12   , Cn3 , v100
	.byte	W24
m_Sample_01_1_B1:
	.byte		N12   , Cs3 , v100
	.byte	W23
	.byte		PAN   , c_v+0
	.byte	W01
	.byte		N12   , Dn3 
	.byte	W23
	.byte		VOICE , 4
	.byte	W01
	.byte		N36   , Ds3 
	.byte	W05
	.byte		BENDR , 4
	.byte		BEND  , c_v-16
	.byte	W05
	.byte		        c_v-32
	.byte	W05
	.byte		        c_v-47
	.byte	W05
	.byte		        c_v-24
	.byte	W04
@ 001   ----------------------------------------
	.byte		        c_v+0
	.byte	W05
	.byte		        c_v+15
	.byte	W05
	.byte		        c_v+31
	.byte	W05
	.byte		        c_v+46
	.byte	W05
	.byte		        c_v+62
	.byte	W03
	.byte		        c_v+0
	.byte	W01
	.byte		N48   , En3 
	.byte	W05
	.byte		LFOS  , 100
	.byte		LFODL , 10
	.byte		MOD   , 120
	.byte		MODT  , 2
	.byte	W66
	.byte	TEMPO , 69*m_Sample_01_tbs/2
	.byte	W01
@ 002   ----------------------------------------
	.byte	TEMPO , 80*m_Sample_01_tbs/2
	.byte		XCMD  , xIECV , 20
	.byte		        xIECL , 20
	.byte		N12   , Fn3 
	.byte	W48
	.byte		XCMD  , xIECV , 40
	.byte		        xIECL , 40
	.byte		N12   
	.byte	W48
@ 003   ----------------------------------------
	.byte		XCMD  , xIECV , 80
	.byte		        xIECL , 80
	.byte		N12   
	.byte	W48
	.byte		XCMD  , xIECV , 100
	.byte		        xIECL , 100
	.byte		N12   
	.byte	W48
@ 004   ----------------------------------------
m_Sample_01_1_004:
	.byte		N24   , Cn3 , v080
	.byte	W48
	.byte		        En3 , v060
	.byte	W48
	.byte	PEND
@ 005   ----------------------------------------
	.byte	PATT
	 .word	m_Sample_01_1_004
@ 006   ----------------------------------------
	.byte		TIE   , Gn3 , v060
	.byte	W96
@ 007   ----------------------------------------
	.byte	W48
	.byte		EOT   
	.byte	W48
	.byte	GOTO
	 .word	m_Sample_01_1_B1
m_Sample_01_1_B2:
@ 008   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

m_Sample_01:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	m_Sample_01_pri	@ Priority
	.byte	m_Sample_01_rev	@ Reverb.

	.word	m_Sample_01_grp

	.word	m_Sample_01_1

	.end
