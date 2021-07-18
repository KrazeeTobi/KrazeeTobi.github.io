;********************************************************************
;*          AgbSyscallArm.s                                         *
;*            AGB system call functions (for ARMASM)                *
;*                                                                  *
;*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
;********************************************************************

		AREA	AgbSysCall, CODE, READONLY
		INCLUDE	AgbDefineArm.s
		INCLUDE	AgbMemoryMapArm.s

		CODE16

;--------------------------------------------------------------------
;-				Software reset										-
;--------------------------------------------------------------------
		GLOBAL	SoftReset
SoftReset
				ldr		r3, =REG_IME
				mov		r2, #1
				strb	r2, [r3, #0]
				ldr		r1, =0x3007f00
				mov		sp, r1
				swi		1
				swi		0
				bx		lr

;--------------------------------------------------------------------
;-				Register & RAM reset							-
;--------------------------------------------------------------------
		GLOBAL	RegisterRamReset
RegisterRamReset
				swi		1
				bx		lr

;--------------------------------------------------------------------
;-				Interrupt wait									-
;--------------------------------------------------------------------
		GLOBAL	IntrWait
IntrWait		swi		4
				bx		lr

;--------------------------------------------------------------------
;-				Signed division (quotient)							    -
;--------------------------------------------------------------------
		GLOBAL	Div
Div				swi		6
				bx		lr

		GLOBAL	DivArm
DivArm			swi		7
				bx		lr

;--------------------------------------------------------------------
;-				Signed division (remainder)							    -
;--------------------------------------------------------------------
		GLOBAL	DivRem
DivRem			swi		6
				mov		r0, r1
				bx		lr

		GLOBAL	DivRemArm
DivRemArm		swi		7
				mov		r0, r1
				bx		lr

;--------------------------------------------------------------------
;-				Square root											    -
;--------------------------------------------------------------------
		GLOBAL	Sqrt
Sqrt			swi		8
				bx		lr

;--------------------------------------------------------------------
;-				Arc tangent											    -
;--------------------------------------------------------------------
		GLOBAL	ArcTan
ArcTan			swi		9
				bx		lr

;--------------------------------------------------------------------
;-				Arc tangent 2										    -
;--------------------------------------------------------------------
		GLOBAL	ArcTan2
ArcTan2			swi		10
				bx		lr

;--------------------------------------------------------------------
;-				CPU set (DMA set compatible)				    -
;--------------------------------------------------------------------
		GLOBAL	CpuSet
CpuSet			swi		11
				bx		lr

;--------------------------------------------------------------------
;-				CPU high-speed set (DMA set compatible)   			    -
;--------------------------------------------------------------------
		GLOBAL	CpuFastSet
CpuFastSet		swi		12
				bx		lr

;--------------------------------------------------------------------
;-				BG affine conversion set 							    -
;--------------------------------------------------------------------
		GLOBAL	BgAffineSet
BgAffineSet		swi		14
				bx		lr

;--------------------------------------------------------------------
;-				OBJ affine conversion set						    -
;--------------------------------------------------------------------
		GLOBAL	ObjAffineSet
ObjAffineSet	swi		15
				bx		lr

;--------------------------------------------------------------------
;-				Decompress Bit compressed data 							    -
;--------------------------------------------------------------------
		GLOBAL	BitUnPack
BitUnPack		swi		16
				bx		lr

;--------------------------------------------------------------------
;-				Decompress LZ77 compressed data (-->Working RAM) 		    -
;--------------------------------------------------------------------
		GLOBAL	LZ77UnCompWram
LZ77UnCompWram	swi		17
				bx		lr

;--------------------------------------------------------------------
;-				Decompress LZ77 compressed data(-->RAM)  			    -
;--------------------------------------------------------------------
		GLOBAL	LZ77UnCompVram
LZ77UnCompVram	swi		18
				bx		lr

;--------------------------------------------------------------------
;-				Decompress Huffman coded data							    -
;--------------------------------------------------------------------
		GLOBAL	HuffUnComp
HuffUnComp		swi		19
				bx		lr

;--------------------------------------------------------------------
;-				Decompress run length compressed data  (-->Working RAM)  	    -
;--------------------------------------------------------------------
		GLOBAL	RLUnCompWram
RLUnCompWram	swi		20
				bx		lr

;--------------------------------------------------------------------
;-				Decompress run length compressed data (-->VRAM)		    -
;--------------------------------------------------------------------
		GLOBAL	RLUnCompVram
RLUnCompVram	swi		21
				bx		lr

;--------------------------------------------------------------------
;-				Decompress differential filter (8Bit-->Working RAM)			    -
;--------------------------------------------------------------------
		GLOBAL	Diff8bitUnFilterWram
Diff8bitUnFilterWram
				swi		22
				bx		lr

;--------------------------------------------------------------------
;-				Decompress differential filter (8Bit-->VRAM)				    -
;--------------------------------------------------------------------
		GLOBAL	Diff8bitUnFilterVram
Diff8bitUnFilterVram
				swi		23
				bx		lr

;--------------------------------------------------------------------
;-				Decompress differential filter (16Bit)						    -
;--------------------------------------------------------------------
		GLOBAL	Diff16bitUnFilter
Diff16bitUnFilter
				swi		24
				bx		lr

;--------------------------------------------------------------------
;-				Sound BIAS change  							    -
;--------------------------------------------------------------------
		GLOBAL	SoundBiasChange
SoundBiasChange	swi		25
				bx		lr

;--------------------------------------------------------------------
;-				Sound BIAS set 							    -
;--------------------------------------------------------------------
		GLOBAL	SoundBiasSet
SoundBiasSet	mov		r0, #1
				swi		25
				bx		lr

;--------------------------------------------------------------------
;-				Sound BIAS reset 						    -
;--------------------------------------------------------------------
		GLOBAL	SoundBiasReset
SoundBiasReset	mov		r0, #0
				swi		25
				bx		lr

;--------------------------------------------------------------------
;-				Initialize sound driver 							    -
;--------------------------------------------------------------------
		GLOBAL	SoundDriverInit
SoundDriverInit	swi		26
				bx		lr

;--------------------------------------------------------------------
;-				Sound driver working mode     -
;--------------------------------------------------------------------
		GLOBAL	SoundDriverMode
SoundDriverMode	swi		27
				bx		lr

;--------------------------------------------------------------------
;-				Sound driver main  							    -
;--------------------------------------------------------------------
		GLOBAL	SoundDriverMain
SoundDriverMain	swi		28
				bx		lr

;--------------------------------------------------------------------
;-				Sound driver DMA reset  			    -
;--------------------------------------------------------------------
		GLOBAL	SoundDriverVSync
SoundDriverVSync
				swi		29
				bx		lr

;--------------------------------------------------------------------
;-				Sound channel clear						    -
;--------------------------------------------------------------------
		GLOBAL	SoundChannelClear
SoundChannelClear
				swi		30
				bx		lr

;--------------------------------------------------------------------
;-				Stop sound DMA			 					-
;--------------------------------------------------------------------
		GLOBAL	SoundDriverVSyncOff
SoundDriverVSyncOff
				swi		40
				bx		lr

;--------------------------------------------------------------------
;-				Resume sound DMA 			 					-
;--------------------------------------------------------------------
		GLOBAL	SoundDriverVSyncOn
SoundDriverVSyncOn
				swi		41
				bx		lr

;--------------------------------------------------------------------
;-				Calculate musical interval by MIDI key  						    -
;--------------------------------------------------------------------
		GLOBAL	MidiKey2Freq
MidiKey2Freq	swi		31
				bx		lr

;--------------------------------------------------------------------
;-				Open Music Player  				    -
;--------------------------------------------------------------------
		GLOBAL	MusicPlayerOpen
MusicPlayerOpen	swi		32
				bx		lr

;--------------------------------------------------------------------
;-				Start playing music       							    -
;--------------------------------------------------------------------
		GLOBAL	MusicPlayerStart
MusicPlayerStart
				swi		33
				bx		lr

;--------------------------------------------------------------------
;-				Stop (temporarily) playing music  					    -
;--------------------------------------------------------------------
		GLOBAL	MusicPlayerStop
MusicPlayerStop
				swi		34
				bx		lr

;--------------------------------------------------------------------
;-				Resume playing music 									    -
;--------------------------------------------------------------------
		GLOBAL	MusicPlayerContinue
MusicPlayerContinue
				swi		35
				bx		lr

;--------------------------------------------------------------------
;-				Fade out music  								    -
;--------------------------------------------------------------------
		GLOBAL	MusicPlayerFadeOut
MusicPlayerFadeOut
				swi		36
				bx		lr


;--------------------------------------------------------------------
;-				Multi play boot								    -
;--------------------------------------------------------------------
		GLOBAL	MultiBoot
MultiBoot
				mov		r1, #1
				swi		37
				bx		lr


		END

