#TONE NAME     : inst2f
#FREQUENCY     : 8000
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 001437
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	inst2f
	.align	2

inst2f:
	.short	0x0000
	.short	0x0000
	.int	16384000
	.int	0
	.int	1437

	.byte	0x01,0x08,0x0B,0x06,0xEE,0xE6,0xF4,0xF8
	.byte	0x21,0x27,0x15,0x19,0xDF,0xD6,0x09,0x30
	.byte	0x17,0xCA,0xF4,0x0A,0x09,0xEE,0xEC,0xD6
	.byte	0xF5,0x35,0xFC,0xE9,0x06,0x00,0xE3,0xFB
	.byte	0x2D,0x3A,0x00,0xEF,0xE6,0xF9,0x09,0x2B
	.byte	0xFB,0xEB,0x10,0x05,0x01,0xFC,0x2E,0x12
	.byte	0xEB,0xEB,0xE1,0xFB,0xFE,0x11,0xED,0xF6
	.byte	0x16,0x0B,0xF4,0xF0,0x09,0xF3,0xF1,0xFA
	.byte	0xFD,0x08,0x0F,0x0A,0x02,0x02,0x16,0x04
	.byte	0xDE,0xE5,0x02,0x0F,0x0B,0x1C,0x06,0xFB
	.byte	0x02,0xFB,0xFE,0xFF,0x07,0xF5,0xF6,0xFA
	.byte	0x09,0x11,0x0B,0x07,0xEB,0xEC,0xF2,0x00
	.byte	0xFE,0x08,0x0E,0x01,0xFD,0xFD,0x08,0xFF
	.byte	0x01,0xF5,0xEB,0xF3,0x0A,0x15,0x0B,0x0A
	.byte	0x01,0xFA,0xF5,0xF8,0x02,0x04,0xF8,0xFB
	.byte	0xFB,0x03,0x11,0x0E,0x03,0xF5,0xF3,0xF1
	.byte	0xFB,0x06,0x0A,0x09,0x00,0xFE,0xF7,0x03
	.byte	0x0A,0xFF,0xF8,0xFB,0xFC,0xF9,0x06,0x0D
	.byte	0x0C,0x02,0xF6,0xF5,0xFA,0x03,0x03,0xFF
	.byte	0xFD,0x02,0x03,0x05,0x02,0xFF,0xFA,0xF7
	.byte	0xF9,0x00,0x06,0x07,0x00,0xFA,0x00,0x04
	.byte	0x03,0xFF,0xFB,0xFE,0xFB,0x02,0x03,0x08
	.byte	0x04,0x01,0xF8,0xFA,0x09,0x14,0x01,0xE6
	.byte	0xE4,0xE6,0xFF,0x32,0x27,0x2A,0x03,0xC4
	.byte	0xD8,0x1A,0x2E,0xEE,0xE5,0x08,0x0B,0xE6
	.byte	0xF0,0xEA,0xF6,0x30,0x1F,0xDB,0xF2,0x11
	.byte	0xE9,0xEB,0x12,0x37,0x19,0xF0,0xF0,0xF0
	.byte	0x00,0x0D,0x0B,0xD5,0x03,0x12,0x0B,0xF7
	.byte	0x0A,0x23,0xEF,0xF5,0xF0,0xFD,0x07,0x08
	.byte	0xFE,0xE3,0x13,0x1A,0x07,0xEC,0xFE,0x00
	.byte	0xEE,0xF9,0xFD,0x03,0x0D,0x0E,0x00,0xF9
	.byte	0x0A,0x14,0xEF,0xE0,0xF2,0x05,0x00,0x10
	.byte	0x1B,0xFE,0x00,0xF6,0xF4,0xFE,0x0D,0x04
	.byte	0xF1,0xF4,0xFB,0x12,0x10,0x11,0xF8,0xE9
	.byte	0xED,0xFB,0x06,0xFF,0x10,0x09,0xFF,0xF9
	.byte	0x05,0x08,0xFD,0xFE,0xF0,0xEE,0xFB,0x12
	.byte	0x0D,0x06,0x06,0xFB,0xF7,0xF7,0x02,0x08
	.byte	0xFF,0xF4,0xF8,0xFB,0x0F,0x16,0x0B,0xF8
	.byte	0xF1,0xF2,0xF7,0x04,0x06,0x06,0xFE,0x01
	.byte	0x02,0x01,0x0B,0xFE,0xF3,0xF4,0x00,0x00
	.byte	0x01,0x04,0x05,0x09,0x03,0x00,0xFC,0xFE
	.byte	0x00,0xFE,0xF9,0xFE,0x02,0x01,0x04,0x01
	.byte	0x02,0xFE,0xF9,0xFB,0x01,0x05,0x05,0xFE
	.byte	0xFC,0x06,0x06,0x01,0xFE,0xFC,0xF9,0xFC
	.byte	0x02,0x0A,0x08,0x01,0xFC,0xF7,0xFA,0x05
	.byte	0x06,0xFD,0xFB,0xFE,0x00,0x01,0x05,0x08
	.byte	0x04,0x00,0xFB,0xF9,0x01,0x09,0x02,0xFB
	.byte	0xFE,0x00,0x01,0x02,0x02,0xFE,0xFA,0xFA
	.byte	0xFE,0x04,0x08,0x06,0xFD,0xFA,0x01,0x05
	.byte	0x04,0x02,0xFF,0xFD,0xFC,0xFD,0x04,0x04
	.byte	0x00,0xFD,0xFC,0xFD,0x04,0x06,0x04,0x01
	.byte	0xFE,0xFE,0xFE,0x00,0x05,0x05,0x01,0xFF
	.byte	0xFC,0xFD,0x03,0x05,0x03,0x01,0xFF,0xFD
	.byte	0xFA,0xFE,0x04,0x04,0x00,0x00,0xFF,0x02
	.byte	0x04,0x01,0xFD,0xFC,0x00,0x05,0x05,0x05
	.byte	0x02,0xFB,0xFA,0x00,0x03,0x01,0x02,0xFF
	.byte	0xFD,0x00,0x03,0x02,0x04,0xFF,0xFC,0xFD
	.byte	0xFF,0xFF,0x01,0x06,0x06,0x02,0xFF,0xFE
	.byte	0xFF,0x03,0x03,0xFD,0xFB,0xFD,0x00,0x05
	.byte	0x09,0x05,0x00,0xFD,0xFC,0xFD,0x01,0x03
	.byte	0x03,0x01,0x00,0x00,0x00,0x02,0x00,0xFD
	.byte	0xFD,0xFF,0x01,0xFE,0x04,0x02,0x01,0x02
	.byte	0x02,0x02,0x00,0x00,0xFB,0xFF,0x03,0x04
	.byte	0x03,0x02,0x01,0xFF,0xFE,0xFE,0xFE,0xFE
	.byte	0x04,0x03,0x02,0x04,0x02,0xFF,0xFF,0xFE
	.byte	0xFC,0x01,0xFF,0x01,0x00,0xFF,0x02,0x00
	.byte	0x01,0x01,0x01,0x03,0x03,0x00,0xFE,0xFF
	.byte	0xFE,0x01,0x04,0x03,0x02,0x01,0xFE,0xFD
	.byte	0xFD,0x02,0x01,0x00,0x03,0x03,0x01,0x02
	.byte	0x00,0xFB,0xFF,0x02,0x02,0x02,0x01,0x00
	.byte	0xFD,0xFF,0x01,0x02,0x03,0x01,0x00,0xFE
	.byte	0x00,0x01,0x00,0x03,0x02,0x03,0x01,0xFE
	.byte	0xFF,0x02,0x00,0x02,0x01,0xFE,0x02,0x02
	.byte	0x01,0xFF,0xFE,0xFF,0xFF,0x00,0x03,0xFF
	.byte	0xFC,0x00,0xFF,0xFF,0x03,0x06,0x02,0x02
	.byte	0x01,0x01,0xFE,0xFD,0x02,0x01,0x02,0x04
	.byte	0x03,0xFE,0x02,0x01,0xFD,0xFD,0xFD,0x02
	.byte	0x02,0x03,0x02,0xFF,0xFD,0x00,0x00,0xFE
	.byte	0x03,0x02,0x00,0xFF,0x01,0x01,0x01,0x00
	.byte	0x01,0x02,0xFF,0x01,0xFF,0xFF,0x00,0x00
	.byte	0x01,0x03,0x04,0x01,0x01,0xFD,0x00,0xFD
	.byte	0xFD,0x03,0x06,0x05,0x01,0x01,0xFF,0xFE
	.byte	0xFD,0x01,0x01,0x02,0x01,0x00,0x01,0x03
	.byte	0x03,0xFD,0xFE,0x00,0x00,0xFE,0x01,0x02
	.byte	0x00,0x03,0x04,0x01,0x00,0x01,0xFD,0xFC
	.byte	0x00,0x02,0x01,0x02,0x04,0x01,0xFF,0xFF
	.byte	0xFE,0xFC,0x01,0x06,0x01,0x00,0x02,0x03
	.byte	0x01,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE
	.byte	0x04,0x03,0x00,0x00,0x03,0x01,0xFF,0xFF
	.byte	0xFF,0x03,0x01,0x00,0xFD,0x00,0x06,0x05
	.byte	0x00,0xFF,0x00,0x00,0x00,0xFF,0x01,0x01
	.byte	0x00,0x01,0x00,0x01,0x01,0x00,0xFD,0x01
	.byte	0x03,0x03,0xFF,0xFD,0x01,0x03,0x04,0x00
	.byte	0xFE,0x00,0x03,0x02,0xFF,0x01,0xFE,0xFE
	.byte	0xFF,0x00,0x02,0x04,0x02,0x01,0x00,0xFD
	.byte	0x01,0xFF,0xFF,0x02,0x02,0x03,0x02,0xFF
	.byte	0xFF,0x01,0x00,0x02,0x00,0xFF,0x02,0x02
	.byte	0xFF,0x02,0x02,0x01,0x02,0xFE,0xFF,0xFF
	.byte	0xFF,0x00,0x02,0x04,0x04,0x02,0xFD,0xFF
	.byte	0xFF,0x01,0x01,0xFD,0xFF,0x00,0x01,0x03
	.byte	0x03,0xFF,0x00,0x00,0xFE,0x00,0x02,0x03
	.byte	0x02,0x01,0x00,0x03,0x01,0x00,0x02,0x01
	.byte	0xFF,0xFC,0xFC,0xFF,0x06,0x06,0x05,0x00
	.byte	0xFE,0xFE,0xFB,0x00,0x02,0x02,0x01,0x00
	.byte	0x00,0x01,0x04,0x02,0xFF,0xFE,0x00,0xFF
	.byte	0x01,0x02,0x01,0x01,0xFF,0x00,0x00,0x01
	.byte	0x02,0x03,0xFD,0xFF,0x03,0x03,0x03,0x04
	.byte	0x01,0xFE,0x00,0x00,0xFF,0x00,0x02,0xFF
	.byte	0xFC,0x02,0x05,0x04,0x00,0x00,0xFE,0xFE
	.byte	0x03,0x03,0x01,0xFF,0x00,0xFE,0xFF,0x02
	.byte	0x05,0x02,0x00,0x01,0xFF,0xFE,0x01,0x01
	.byte	0x00,0x01,0x00,0xFE,0xFF,0x01,0x02,0x00
	.byte	0x02,0x01,0xFF,0x00,0x03,0x03,0x00,0x00
	.byte	0xFF,0x00,0x01,0x04,0x02,0x00,0xFF,0xFD
	.byte	0xFF,0x03,0x04,0x01,0xFF,0xFF,0x01,0xFF
	.byte	0x03,0x02,0xFF,0xFF,0x00,0x01,0x01,0x03
	.byte	0x01,0xFD,0xFD,0x00,0x02,0x03,0x05,0x03
	.byte	0x00,0xFD,0xFD,0x00,0x00,0x04,0x00,0xFD
	.byte	0x00,0x02,0x02,0x01,0x03,0x01,0x01,0x00
	.byte	0xFF,0xFF,0xFE,0x01,0x03,0x02,0x04,0x01
	.byte	0xFF,0xFF,0x00,0x02,0x01,0x01,0x01,0x01
	.byte	0x02,0x03,0x00,0xFE,0x00,0x00,0x00,0x01
	.byte	0x00,0xFE,0x00,0x01,0x00,0x01,0x00,0xFF
	.byte	0x00,0x01,0x02,0x03,0x01,0xFF,0xFF,0x02
	.byte	0x03,0x03,0x02,0xFF,0xFF,0xFE,0x01,0x04
	.byte	0x05,0x04,0x01,0xFF,0xFF,0xFF,0xFE,0xFF
	.byte	0x00,0x02,0x00,0x00,0x00,0x02,0x02,0xFF
	.byte	0xFE,0xFE,0x01,0x02,0x01,0xFF,0x01,0x00
	.byte	0xFF,0x02,0x03,0x03,0x01,0xFE,0xFE,0x01
	.byte	0x03,0x03,0x02,0x00,0x02,0x00,0xFE,0xFF
	.byte	0x00,0x02,0x01,0x01,0x00,0x00,0xFF,0x01
	.byte	0x02,0x03,0x02,0xFE,0xFD,0x00,0x01,0x01
	.byte	0x01,0x00,0xFF,0x00,0x02,0x02,0x02,0x01
	.byte	0xFF,0xFF,0xFF,0x01,0x02,0x00,0x00,0x01
	.byte	0x02,0x03,0x01,0x00,0x01,0x01,0x01,0x00
	.byte	0x00,0xFF,0xFF,0xFF,0x02,0x05,0x04,0x02
	.byte	0xFE,0xFC,0xFC,0xFF,0x04,0x05,0x02,0x00
	.byte	0x00,0xFF,0x00,0x04,0x02,0x01,0x00,0xFE
	.byte	0xFE,0x01,0x03,0x01,0xFF,0xFF,0x00,0x00
	.byte	0x01,0x03,0x01,0xFF,0xFF,0x00,0x01,0x02
	.byte	0x02,0xFF,0xFF,0x01,0x01,0x02,0x03,0x01
	.byte	0x00,0x00,0x01,0x01,0x00,0xFF,0x00,0x00
	.byte	0x01,0x01,0x00,0x02,0x02,0x00,0x00,0xFF
	.byte	0x00,0x00,0x02,0x02,0x02,0x00,0xFE,0xFF
	.byte	0x00,0x02,0x02,0x00,0x00,0x00,0xFF,0x01
	.byte	0x04,0x05,0x02,0x01,0x00,0x00,0x01,0x01
	.byte	0xFF,0xFD,0x02,0x03,0x01,0x00,0xFF,0x00
	.byte	0x00,0x02,0x01,0x02,0x00,0xFF,0x00,0x03
	.byte	0x03,0x01,0xFE,0x00,0x01,0x01,0x02,0x02
	.byte	0x01,0xFF,0x00,0x00,0x00,0x03,0x02,0x00
	.byte	0xFE,0x00,0x01,0x02,0x03,0x01,0xFF,0x00
	.byte	0x02,0x01,0x00,0x02,0x01,0xFF,0x01,0x02
	.byte	0x02,0x02,0x00,0xFE,0xFF,0x01,0x01,0x00
	.byte	0x00,0x02,0x02,0x01,0x02,0x00,0x01,0x02
	.byte	0x02,0xFF,0x00,0x00,0x00,0x01,0x01,0x01
	.byte	0x00,0xFF,0xFF,0x00,0x01,0x01,0x01,0x00
	.byte	0x01,0x01,0x01,0x02,0x02,0xFF,0xFF,0xFE
	.byte	0x01,0x04,0x03,0x00,0xFF,0x00,0x02,0x03
	.byte	0x02,0x01,0x01,0xFF,0xFF,0x00,0x02,0x02
	.byte	0x00,0xFF,0x01,0x01,0x01,0x00,0x00,0x02
	.byte	0x02,0x01,0x00,0x01,0x01,0xFF,0xFE,0xFF
	.byte	0x00,0x02,0x04,0x03,0x02,0x00,0xFD,0xFE
	.byte	0x02,0x02,0x02,0x02,0x02,0x00,0xFF,0x00
	.byte	0x01,0x03,0x01,0xFF,0xFE,0x01,0x02,0x02
	.byte	0x02,0x02,0xFF,0xFE,0xFE,0x00,0x02,0x01
	.byte	0xFF,0xFE,0x01,0x02,0x02,0x02,0x01,0x00
	.byte	0xFF,0x00,0x00,0x01,0x02,0x02,0x00,0x00
	.byte	0x01,0x00,0x00,0x01,0x02,0x00,0x01,0x00
	.byte	0x01,0x02,0x02,0x00,0xFE,0x01,0x01,0x00
	.byte	0xFF,0x01,0x01,0x01,0x02,0x01,0x01,0x01
	.byte	0x00,0xFF,0x00,0x01,0x01,0xFF,0x00,0x01
	.byte	0x01,0x02,0x00,0x00,0xFF,0x00,0x01,0x01
	.byte	0x02,0x01,0x01,0x00,0x01,0x01,0x00,0xFF
	.byte	0xFF,0x00,0x01,0x02,0x00,0x00,0x00,0x01
	.byte	0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x01
	.byte	0x01,0x00,0x01,0x01,0x01,0x00,0x00,0x00
	.byte	0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x01
	.byte	0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x01
	.byte	0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01
	.byte	0x00,0x00,0x00,0x01,0x01

	.byte	0x00

	.end
