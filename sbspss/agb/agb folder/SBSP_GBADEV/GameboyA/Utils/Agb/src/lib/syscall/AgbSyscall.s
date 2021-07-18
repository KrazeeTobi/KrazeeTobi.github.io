@********************************************************************
@*          AgbSyscall.s                                            *
@*            AGB system call functions (for GAS)                   *
@*                                                                  *
@*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
@********************************************************************
		.INCLUDE	"AgbDefine.s"
		.INCLUDE	"AgbMemoryMap.s"
		.TEXT
		.CODE 16

@--------------------------------------------------------------------
@-				Software reset 										-
@--------------------------------------------------------------------
		.GLOBAL	SoftReset
		.THUMB_FUNC
SoftReset:
				ldr		r3, =REG_IME
				mov		r2, #1
				strb	r2, [r3, #0]
				ldr		r1, =0x3007f00
				mov		sp, r1
				swi		1
				swi		0
				bx		lr

@--------------------------------------------------------------------
@-				Register & RAM reset 							-
@--------------------------------------------------------------------
		.GLOBAL	RegisterRamReset
		.THUMB_FUNC
RegisterRamReset:
				swi		1
				bx		lr

@--------------------------------------------------------------------
@-				Interrupt wait 									-
@--------------------------------------------------------------------
		.GLOBAL	IntrWait
		.THUMB_FUNC
IntrWait:		mov		r2, #0
				swi		4
				bx		lr

@--------------------------------------------------------------------
@-				Signed division (quotient) 							    -
@--------------------------------------------------------------------
		.GLOBAL	Div
		.GLOBAL	DivArm
		.THUMB_FUNC
Div:			swi		6
				bx		lr
		.THUMB_FUNC
DivArm:			swi		7
				bx		lr

@--------------------------------------------------------------------
@-				Signed division (remainder)							    -
@--------------------------------------------------------------------
		.GLOBAL	DivRem
		.GLOBAL	DivRemArm
		.THUMB_FUNC
DivRem:		swi		6
				mov		r0, r1
				bx		lr
		.THUMB_FUNC
DivRemArm:		swi		7
				mov		r0, r1
				bx		lr

@--------------------------------------------------------------------
@-				Square root											    -
@--------------------------------------------------------------------
		.GLOBAL	Sqrt
		.THUMB_FUNC
Sqrt:			swi		8
				bx		lr

@--------------------------------------------------------------------
@-				Arc tangent											    -
@--------------------------------------------------------------------
		.GLOBAL	ArcTan
		.THUMB_FUNC
ArcTan:			swi		9
				bx		lr

@--------------------------------------------------------------------
@-				Arc tangent 2 										    -
@--------------------------------------------------------------------
		.GLOBAL	ArcTan2
		.THUMB_FUNC
ArcTan2:		swi		10
				bx		lr

@--------------------------------------------------------------------
@-				CPU set (DMA set compatible)  				    -
@--------------------------------------------------------------------
		.GLOBAL	CpuSet
		.THUMB_FUNC
CpuSet:			swi		11
				bx		lr

@--------------------------------------------------------------------
@-				CPU high-speed set (DMA set compatible) -
@--------------------------------------------------------------------
		.GLOBAL	CpuFastSet
		.THUMB_FUNC
CpuFastSet:		swi		12
				bx		lr

@--------------------------------------------------------------------
@-				BG affine conversion set 							    -
@--------------------------------------------------------------------
		.GLOBAL	BgAffineSet
		.THUMB_FUNC
BgAffineSet:	swi		14
				bx		lr

@--------------------------------------------------------------------
@-				OBJ affine conversion set -
@--------------------------------------------------------------------
		.GLOBAL	ObjAffineSet
		.THUMB_FUNC
ObjAffineSet:	swi		15
				bx		lr

@--------------------------------------------------------------------
@-				Decompress Bit compressed data 								    -
@--------------------------------------------------------------------
		.GLOBAL	BitUnPack
		.THUMB_FUNC
BitUnPack:		swi		16
				bx		lr

@--------------------------------------------------------------------
@-				Decompress LZ77 compressed data (-->Working RAM) 		    -
@--------------------------------------------------------------------
		.GLOBAL	LZ77UnCompWram
		.THUMB_FUNC
LZ77UnCompWram:
				swi		17
				bx		lr

@--------------------------------------------------------------------
@-				Decompress LZ77 compressed data  (-->VRAM)    -
@--------------------------------------------------------------------
		.GLOBAL	LZ77UnCompVram
		.THUMB_FUNC
LZ77UnCompVram:
				swi		18
				bx		lr

@--------------------------------------------------------------------
@-				Decompress Huffman coded data 							    -
@--------------------------------------------------------------------
		.GLOBAL	HuffUnComp
		.THUMB_FUNC
HuffUnComp:		swi		19
				bx		lr

@--------------------------------------------------------------------
@-				Decompress run length compressed data (-->Working RAM)   	    -
@--------------------------------------------------------------------
		.GLOBAL	RLUnCompWram
		.THUMB_FUNC
RLUnCompWram:	swi		20
				bx		lr

@--------------------------------------------------------------------
@-				Decompress run length compressed data (-->VRAM)     -
@--------------------------------------------------------------------
		.GLOBAL	RLUnCompVram
		.THUMB_FUNC
RLUnCompVram:	swi		21
				bx		lr

@--------------------------------------------------------------------
@-				Decompress differential filter (8Bit-->Working RAM)			    -
@--------------------------------------------------------------------
		.GLOBAL	Diff8bitUnFilterWram
		.THUMB_FUNC
Diff8bitUnFilterWram:
				swi		22
				bx		lr

@--------------------------------------------------------------------
@-				Decompress differential filter (8Bit-->VRAM)				    -
@--------------------------------------------------------------------
		.GLOBAL	Diff8bitUnFilterVram
		.THUMB_FUNC
Diff8bitUnFilterVram:
				swi		23
				bx		lr

@--------------------------------------------------------------------
@-				Decompress differential filter (16Bit)						    -
@--------------------------------------------------------------------
		.GLOBAL	Diff16bitUnFilter
		.THUMB_FUNC
Diff16bitUnFilter:
				swi		24
				bx		lr

@--------------------------------------------------------------------
@-			       Sound BIAS change
							    -
@--------------------------------------------------------------------
		.GLOBAL	SoundBiasChange
		.THUMB_FUNC
SoundBiasChange:
				swi		25
				bx		lr

@--------------------------------------------------------------------
@-				Sound BIAS set 							    -
@--------------------------------------------------------------------
		.GLOBAL	SoundBiasSet
		.THUMB_FUNC
SoundBiasSet:	mov		r0, #1
				swi		25
				bx		lr

@--------------------------------------------------------------------
@-				Sound BIAS reset						    -
@--------------------------------------------------------------------
		.GLOBAL	SoundBiasReset
		.THUMB_FUNC
SoundBiasReset:
				mov		r0, #0
				swi		25
				bx		lr

@--------------------------------------------------------------------
@-				Initialize sound driver							    -
@--------------------------------------------------------------------
		.GLOBAL	SoundDriverInit
		.THUMB_FUNC
SoundDriverInit:
				swi		26
				bx		lr

@--------------------------------------------------------------------
@-				Sound driver working mode   						    -
@--------------------------------------------------------------------
		.GLOBAL	SoundDriverMode
		.THUMB_FUNC
SoundDriverMode:
				swi		27
				bx		lr

@--------------------------------------------------------------------
@-				Sound driver main 							    -
@--------------------------------------------------------------------
		.GLOBAL	SoundDriverMain
		.THUMB_FUNC
SoundDriverMain:
				swi		28
				bx		lr

@--------------------------------------------------------------------
@-				Sound driver DMA reset					    -
@--------------------------------------------------------------------
		.GLOBAL	SoundDriverVSync
		.THUMB_FUNC
SoundDriverVSync:
				swi		29
				bx		lr

@--------------------------------------------------------------------
@-				Sound channel clear 						    -
@--------------------------------------------------------------------
		.GLOBAL	SoundChannelClear
		.THUMB_FUNC
SoundChannelClear:
				swi		30
				bx		lr

@--------------------------------------------------------------------
@-				Stop sound DMA 			 					-
@--------------------------------------------------------------------
		.GLOBAL	_SoundDriverVSyncOff
		.THUMB_FUNC
_SoundDriverVSyncOff:
				swi		40
				bx		lr

@--------------------------------------------------------------------
@-				Resume sound DMA 			 					-
@--------------------------------------------------------------------
		.GLOBAL	_SoundDriverVSyncOn
		.THUMB_FUNC
_SoundDriverVSyncOn:
				swi		41
				bx		lr

@--------------------------------------------------------------------
@-				Calculate musical interval by MIDI key 	    -
@--------------------------------------------------------------------
		.GLOBAL	MidiKey2Freq
		.THUMB_FUNC
MidiKey2Freq:
				swi		31
				bx		lr

@--------------------------------------------------------------------
@-				Open Music Player   -
@--------------------------------------------------------------------
		.GLOBAL	MusicPlayerOpen
		.THUMB_FUNC
MusicPlayerOpen:
				swi		32
				bx		lr

@--------------------------------------------------------------------
@-				Start playing music 									    -
@--------------------------------------------------------------------
		.GLOBAL	MusicPlayerStart
		.THUMB_FUNC
MusicPlayerStart:
				swi		33
				bx		lr

@--------------------------------------------------------------------
@-				Stop (temporarily) playing music 			    -
@--------------------------------------------------------------------
		.GLOBAL	MusicPlayerStop
		.THUMB_FUNC
MusicPlayerStop:
				swi		34
				bx		lr

@--------------------------------------------------------------------
@-				Resume playing music 									    -
@--------------------------------------------------------------------
		.GLOBAL	MusicPlayerContinue
		.THUMB_FUNC
MusicPlayerContinue:
				swi		35
				bx		lr

@--------------------------------------------------------------------
@-				Fade out music 								    -
@--------------------------------------------------------------------
		.GLOBAL	MusicPlayerFadeOut
		.THUMB_FUNC
MusicPlayerFadeOut:
				swi		36
				bx		lr


@--------------------------------------------------------------------
@-				Multi play boot 								    -
@--------------------------------------------------------------------
		.GLOBAL	MultiBoot
		.THUMB_FUNC
MultiBoot:
				mov		r1, #1
				swi		37
				bx		lr


		.END

