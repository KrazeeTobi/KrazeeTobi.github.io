#TONE NAME     : inst4d
#FREQUENCY     : 8000
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 000992
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	inst4d
	.align	2

inst4d:
	.short	0x0000
	.short	0x0000
	.int	16384000
	.int	0
	.int	992

	.byte	0xFF,0x00,0x06,0x03,0x06,0x05,0x06,0x06
	.byte	0x07,0x09,0x06,0x06,0x02,0x00,0xFB,0xF9
	.byte	0xF9,0xF3,0xF4,0xF4,0xF8,0xFA,0x02,0x02
	.byte	0x05,0x09,0x0B,0x0D,0x0C,0x0E,0x09,0x08
	.byte	0x06,0x02,0xFD,0xF8,0xFC,0xF6,0xF4,0xF3
	.byte	0xF6,0xF7,0xFB,0xFB,0xFD,0x0A,0x07,0x09
	.byte	0x09,0x0C,0x09,0x0E,0x0A,0x02,0x08,0x00
	.byte	0x00,0x02,0xFD,0xF8,0x01,0xFD,0xF8,0xFB
	.byte	0x02,0xF9,0xF8,0xFF,0x00,0x01,0x08,0x03
	.byte	0x08,0x0A,0x00,0xFE,0x08,0x00,0xFA,0xF2
	.byte	0xF8,0xFD,0xEF,0xFB,0xFA,0xFE,0x02,0x05
	.byte	0x03,0x0D,0x11,0x02,0x0A,0x14,0x0A,0x0D
	.byte	0x0C,0x05,0x06,0xFB,0xF9,0xF8,0xF1,0xE9
	.byte	0xEA,0xEC,0xE7,0xE9,0xE8,0xEF,0xF3,0xF9
	.byte	0xFB,0x0F,0x15,0x16,0x1A,0x28,0x2D,0x36
	.byte	0x31,0x2A,0x19,0x05,0x0B,0xF9,0xED,0xDB
	.byte	0xDD,0xD8,0xCD,0xCF,0xCA,0xE3,0xEE,0xF4
	.byte	0xF7,0x03,0x17,0x18,0x23,0x1C,0x26,0x23
	.byte	0x0B,0x06,0x05,0x02,0xE5,0xEF,0xF5,0xE8
	.byte	0xE3,0xEB,0x0B,0x09,0x18,0x19,0x1A,0x18
	.byte	0x1C,0x2A,0x14,0x12,0x07,0x0C,0xFC,0xEA
	.byte	0xEB,0xE9,0xF5,0xE0,0xDC,0xE2,0xED,0xE8
	.byte	0xE1,0xF6,0xF4,0xFD,0xFF,0x0A,0x1E,0x17
	.byte	0x12,0x0D,0x20,0x1B,0x09,0x0F,0x01,0x06
	.byte	0xF6,0xF5,0xFB,0x02,0x03,0xF8,0x07,0x00
	.byte	0x09,0x07,0x0B,0x05,0x0D,0x02,0xF6,0x04
	.byte	0xF9,0xE2,0xEF,0xF0,0xEE,0xE8,0xF1,0xEE
	.byte	0x05,0x0E,0x00,0x01,0x0A,0x0A,0x08,0x0D
	.byte	0x0B,0x10,0x12,0x0B,0x0C,0x0E,0x0E,0x03
	.byte	0x0C,0x00,0xF2,0x01,0xFA,0xF4,0xFA,0xF1
	.byte	0xEA,0x01,0xFB,0xF4,0xF6,0xF9,0x06,0x19
	.byte	0x06,0x01,0x07,0x01,0x02,0xFF,0xF4,0x02
	.byte	0xFC,0xF6,0xFD,0xFD,0xFC,0x07,0x05,0x05
	.byte	0x0E,0x13,0x10,0x0B,0x0C,0x08,0x00,0x02
	.byte	0x06,0xFD,0xEF,0xF3,0xFD,0x00,0xF9,0xEC
	.byte	0xEE,0xF5,0xF7,0xF7,0xF7,0xF8,0x00,0x0A
	.byte	0x0F,0x13,0x13,0x0D,0x12,0x17,0x0B,0x07
	.byte	0x04,0xF5,0xF8,0xFF,0xEF,0xEE,0xF7,0xF3
	.byte	0xF1,0xF7,0xFC,0x06,0x0F,0x0B,0x0C,0x11
	.byte	0x0F,0x12,0x06,0xFF,0x03,0x02,0xF9,0xF8
	.byte	0xF6,0xF0,0xF7,0xFE,0xFC,0xFF,0x00,0xFB
	.byte	0xFF,0x0B,0x04,0xFE,0x00,0x06,0x04,0xFD
	.byte	0xFC,0x05,0x0A,0x06,0xFF,0x01,0x01,0xFF
	.byte	0xF8,0xF8,0xFC,0x01,0x01,0x03,0x0B,0x0A
	.byte	0x07,0x11,0x0F,0x05,0x03,0x01,0xF7,0xFC
	.byte	0xFB,0xEC,0xEB,0xF3,0xEF,0xEF,0xEF,0xF5
	.byte	0x00,0x07,0x06,0x0A,0x0D,0x0F,0x10,0x09
	.byte	0x06,0x0C,0x0C,0x04,0x07,0x08,0x03,0x09
	.byte	0x0A,0x06,0x05,0x05,0xFA,0xFC,0x00,0xF8
	.byte	0xF1,0xF5,0xF9,0xF6,0xEF,0xF4,0xFF,0x02
	.byte	0x00,0xFF,0xFF,0x01,0xFF,0xF9,0xFA,0xFF
	.byte	0x02,0x01,0x04,0x0E,0x0A,0x0A,0x13,0x11
	.byte	0x07,0x09,0x06,0x00,0x04,0x02,0xF6,0xF8
	.byte	0xFC,0xF9,0xF7,0xF5,0xF9,0x00,0x02,0x00
	.byte	0x01,0x01,0x00,0xFF,0xF8,0xF6,0xFD,0xFD
	.byte	0xF6,0xFE,0x01,0xFF,0x07,0x0A,0x06,0x0A
	.byte	0x0A,0x01,0x05,0x09,0x00,0xF9,0x00,0x04
	.byte	0xFE,0xF6,0xFB,0x06,0x07,0x05,0x04,0x04
	.byte	0x05,0x02,0xFF,0x00,0x04,0x05,0x01,0x03
	.byte	0x0A,0x03,0x03,0x09,0x03,0xFA,0xFC,0xF8
	.byte	0xF4,0xF8,0xF7,0xF0,0xF4,0xFA,0xFA,0xF8
	.byte	0xFA,0x01,0x09,0x0C,0x0B,0x0C,0x0D,0x0D
	.byte	0x0A,0x02,0x00,0x04,0x00,0xF9,0x02,0x02
	.byte	0x00,0x06,0x08,0x05,0x08,0x05,0xFF,0x00
	.byte	0x01,0xF7,0xF3,0xF7,0xFA,0xF2,0xEC,0xF2
	.byte	0xFB,0xFB,0xFB,0xFC,0xFF,0xFF,0xFF,0xFF
	.byte	0x02,0x06,0x0B,0x08,0x0F,0x14,0x0F,0x10
	.byte	0x16,0x0F,0x08,0x07,0x02,0xFC,0xFE,0xFA
	.byte	0xF2,0xF4,0xF8,0xF6,0xF3,0xF4,0xFC,0x03
	.byte	0x04,0x04,0x06,0x06,0x05,0x02,0xFC,0xFA
	.byte	0xFF,0xF9,0xF6,0xFF,0xFF,0xFF,0x06,0x08
	.byte	0x08,0x0A,0x07,0x04,0x07,0x07,0x00,0xFD
	.byte	0x03,0x04,0xFD,0xF8,0xFF,0x03,0x01,0xFF
	.byte	0xFE,0xFE,0xFC,0xFA,0xFA,0xFA,0xFE,0x02
	.byte	0xFF,0x05,0x09,0x06,0x07,0x0B,0x06,0x01
	.byte	0x01,0xFD,0xF9,0xFB,0xF8,0xF2,0xF6,0xFA
	.byte	0xF9,0xF6,0xF9,0x03,0x08,0x0A,0x0A,0x0D
	.byte	0x0C,0x0B,0x09,0x02,0x02,0x06,0xFE,0xFC
	.byte	0x03,0x01,0x01,0x05,0x06,0x04,0x03,0x00
	.byte	0xFD,0xFE,0xFE,0xF8,0xF6,0xFC,0xFD,0xF6
	.byte	0xF4,0xFC,0xFF,0xFF,0xFD,0xFD,0xFF,0xFE
	.byte	0xFE,0xFF,0x00,0x05,0x08,0x05,0x0A,0x0E
	.byte	0x0B,0x0C,0x0E,0x09,0x04,0x04,0x00,0xFC
	.byte	0xFD,0xF8,0xF2,0xF6,0xF9,0xF6,0xF2,0xF7
	.byte	0xFE,0x03,0x02,0x04,0x07,0x05,0x04,0x02
	.byte	0xFC,0xFE,0x02,0xFC,0xFD,0x03,0x03,0x05
	.byte	0x0A,0x0C,0x0A,0x09,0x06,0x03,0x03,0x02
	.byte	0xFC,0xFB,0x00,0xFF,0xF8,0xF7,0xFE,0x01
	.byte	0x00,0xFD,0xFD,0xFF,0xFD,0xFE,0xFE,0xFF
	.byte	0x04,0x04,0x02,0x07,0x0A,0x08,0x08,0x0B
	.byte	0x07,0x02,0x02,0xFF,0xFC,0xFE,0xF8,0xF4
	.byte	0xFA,0xFC,0xF8,0xF7,0xFC,0x03,0x06,0x04
	.byte	0x07,0x09,0x05,0x04,0x01,0xFB,0xFC,0xFF
	.byte	0xFB,0xFD,0x02,0x02,0x03,0x07,0x08,0x07
	.byte	0x05,0x02,0xFF,0xFF,0xFE,0xFA,0xFA,0xFF
	.byte	0xFE,0xF8,0xF8,0xFF,0x02,0x01,0xFE,0xFF
	.byte	0x00,0xFF,0x00,0x00,0x02,0x06,0x06,0x03
	.byte	0x08,0x0C,0x08,0x08,0x0C,0x06,0x01,0x00
	.byte	0xFD,0xFB,0xFC,0xF5,0xF3,0xF9,0xF9,0xF6
	.byte	0xF7,0xFD,0x03,0x06,0x04,0x08,0x09,0x05
	.byte	0x05,0x02,0xFD,0xFE,0x01,0xFE,0x00,0x04
	.byte	0x05,0x06,0x09,0x0A,0x08,0x06,0x02,0xFE
	.byte	0xFF,0xFE,0xF9,0xFA,0xFF,0xFC,0xF5,0xF5
	.byte	0xFC,0xFE,0xFC,0xF9,0xFC,0xFD,0xFC,0xFD
	.byte	0xFE,0x01,0x06,0x05,0x04,0x08,0x0C,0x08
	.byte	0x0A,0x0E,0x09,0x04,0x02,0xFF,0xFF,0xFE
	.byte	0xF7,0xF6,0xFB,0xF9,0xF7,0xF9,0xFE,0x04
	.byte	0x05,0x02,0x06,0x06,0x02,0x02,0xFF,0xF9
	.byte	0xFC,0xFF,0xFC,0xFF,0x03,0x04,0x06,0x09
	.byte	0x09,0x08,0x06,0x02,0x00,0x01,0xFF,0xFC
	.byte	0xFE,0x02,0xFF,0xF9,0xFA,0x00,0x02,0xFE
	.byte	0xFD,0x00,0x00,0xFF,0xFF,0xFF,0x02,0x05
	.byte	0x04,0x02,0x06,0x09,0x04,0x07,0x0A,0x04
	.byte	0x00,0xFE,0xFC,0xFC,0xFA,0xF4,0xF5,0xFA
	.byte	0xF7,0xF7,0xFA,0xFF,0x05,0x05,0x04,0x08
	.byte	0x06,0x03,0x04,0x01,0xFC,0x00,0x02,0x00
	.byte	0x02,0x06,0x07,0x08,0x0A,0x09,0x07,0x04
	.byte	0xFF,0xFE,0xFF,0xFC,0xF8,0xFB,0xFE,0xFB
	.byte	0xF6,0xF8,0xFE,0x00,0xFB,0xFC,0xFF,0xFF
	.byte	0xFF,0xFF,0x01,0x03,0x07,0x05,0x04,0x09
	.byte	0x0B,0x07,0x0B,0x0D,0x07,0x03,0x01,0xFE
	.byte	0xFE,0xFB,0xF4,0xF8,0xFA,0xF9,0xF8,0xFB
	.byte	0xFF,0x05,0x04,0x03,0x07,0x04,0x01,0x01
	.byte	0xFD,0xFA,0xFD,0xFF,0xFC,0xFE,0x02,0x01

	.byte	0x00

	.end
