#TONE NAME     : inst5c
#FREQUENCY     : 8000
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 005230
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	inst5c
	.align	2

inst5c:
	.short	0x0000
	.short	0x0000
	.int	16384000
	.int	0
	.int	5230

	.byte	0x01,0x00,0x01,0x00,0x01,0x01,0x00,0x00
	.byte	0x01,0x01,0x01,0x00,0x01,0x01,0x00,0x00
	.byte	0x01,0x01,0x00,0x01,0x01,0x00,0x01,0x00
	.byte	0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01
	.byte	0x01,0x01,0x00,0x00,0x00,0x00,0x01,0x01
	.byte	0x01,0x00,0x00,0x00,0x00,0x01,0x01,0x02
	.byte	0x01,0x00,0xFF,0xFF,0x00,0x01,0x00,0x01
	.byte	0x01,0x00,0x00,0x00,0x01,0x02,0x03,0x03
	.byte	0x00,0xFE,0xFE,0xFF,0x01,0x01,0x01,0x01
	.byte	0x01,0x00,0x00,0x01,0x01,0x03,0x03,0x01
	.byte	0xFE,0xFE,0xFF,0x00,0x01,0x00,0x01,0x01
	.byte	0x00,0x00,0x01,0x01,0x03,0x03,0x01,0xFF
	.byte	0xFD,0xFF,0x00,0x01,0x01,0x01,0x00,0x00
	.byte	0x00,0x01,0x01,0x04,0x06,0x03,0xFE,0xFB
	.byte	0xFC,0x00,0x01,0x01,0x01,0x02,0x00,0xFF
	.byte	0x00,0x01,0x04,0x09,0x06,0xFE,0xF8,0xFA
	.byte	0xFE,0x01,0x01,0x01,0x02,0x01,0xFF,0x00
	.byte	0x00,0x03,0x0A,0x08,0x00,0xF8,0xF7,0xFC
	.byte	0x01,0x01,0x01,0x02,0x02,0x00,0x00,0x01
	.byte	0x02,0x0A,0x09,0x02,0xF8,0xF5,0xFA,0x00
	.byte	0x02,0x01,0x02,0x02,0x00,0x00,0x01,0x01
	.byte	0x09,0x0B,0x05,0xF9,0xF4,0xF7,0xFF,0x02
	.byte	0x01,0x01,0x03,0x02,0xFF,0x01,0x00,0x08
	.byte	0x0D,0x08,0xFC,0xF4,0xF5,0xFC,0x02,0x02
	.byte	0x01,0x02,0x01,0x00,0x02,0x00,0x05,0x0F
	.byte	0x0C,0xFF,0xF3,0xF2,0xF9,0x02,0x03,0x01
	.byte	0x00,0x01,0x00,0x03,0x02,0x04,0x0F,0x0F
	.byte	0x02,0xF4,0xEF,0xF5,0x00,0x04,0x02,0x00
	.byte	0x00,0xFF,0x02,0x02,0x03,0x0E,0x13,0x07
	.byte	0xF7,0xEF,0xF2,0xFC,0x03,0x02,0x00,0x01
	.byte	0x00,0x02,0x03,0x02,0x0B,0x13,0x0B,0xFA
	.byte	0xF0,0xEF,0xF8,0x01,0x03,0xFF,0xFF,0x00
	.byte	0x02,0x05,0x02,0x09,0x14,0x11,0xFD,0xF0
	.byte	0xEC,0xF5,0x00,0x04,0x01,0xFF,0x00,0x00
	.byte	0x05,0x03,0x08,0x13,0x13,0x00,0xF1,0xEB
	.byte	0xF0,0xFD,0x06,0x05,0x00,0x00,0xFE,0x04
	.byte	0x04,0x06,0x11,0x16,0x05,0xF2,0xEB,0xED
	.byte	0xFA,0x04,0x08,0x01,0x00,0xFE,0x02,0x03
	.byte	0x04,0x0E,0x18,0x0C,0xF4,0xEB,0xEA,0xF6
	.byte	0x04,0x0A,0x03,0x00,0xFE,0x00,0x04,0x03
	.byte	0x0B,0x16,0x11,0xF7,0xEB,0xE9,0xF5,0x02
	.byte	0x08,0x04,0x00,0xFF,0xFD,0x05,0x04,0x0A
	.byte	0x13,0x15,0xFD,0xEC,0xE9,0xF2,0x01,0x08
	.byte	0x06,0x00,0x00,0xFA,0x04,0x04,0x09,0x12
	.byte	0x17,0x04,0xEC,0xE8,0xED,0xFE,0x08,0x09
	.byte	0x01,0x02,0xFA,0xFE,0x03,0x05,0x11,0x18
	.byte	0x0E,0xF0,0xE7,0xE9,0xFB,0x07,0x0A,0x01
	.byte	0x02,0xF9,0xFB,0x04,0x04,0x10,0x19,0x14
	.byte	0xF5,0xE6,0xE6,0xF6,0x06,0x0D,0x04,0x01
	.byte	0xFA,0xF5,0x03,0x04,0x0E,0x1A,0x19,0xFD
	.byte	0xE7,0xE5,0xF1,0x05,0x0C,0x05,0x00,0xFC
	.byte	0xF3,0x02,0x05,0x0C,0x18,0x1C,0x05,0xE8
	.byte	0xE4,0xED,0x01,0x0B,0x08,0x00,0xFF,0xF3
	.byte	0x00,0x07,0x07,0x16,0x1D,0x0D,0xEE,0xE3
	.byte	0xE7,0xFB,0x09,0x0A,0x02,0x03,0xF6,0xF9
	.byte	0x08,0x06,0x12,0x1B,0x14,0xF5,0xE4,0xE2
	.byte	0xF5,0x09,0x0E,0x05,0x06,0xF9,0xF0,0x05
	.byte	0x05,0x0D,0x1B,0x1B,0xFD,0xE4,0xDF,0xED
	.byte	0x05,0x11,0x08,0x05,0xFF,0xEE,0x01,0x07
	.byte	0x0A,0x19,0x1F,0x03,0xE6,0xDD,0xE8,0x02
	.byte	0x11,0x0C,0x02,0x01,0xEE,0xFD,0x0A,0x08
	.byte	0x14,0x1F,0x0D,0xEB,0xDE,0xE5,0xFE,0x0E
	.byte	0x0F,0x02,0x01,0xF2,0xF8,0x0B,0x08,0x0F
	.byte	0x1B,0x13,0xF1,0xE1,0xE0,0xF7,0x0C,0x11
	.byte	0x04,0x01,0xF8,0xF4,0x09,0x0A,0x0B,0x17
	.byte	0x1A,0xFA,0xE3,0xE0,0xF1,0x08,0x11,0x08
	.byte	0x00,0xFB,0xF3,0x05,0x0A,0x07,0x11,0x1E
	.byte	0x07,0xE6,0xDE,0xEA,0x02,0x10,0x0E,0x01
	.byte	0xFD,0xF3,0xFF,0x0B,0x09,0x0D,0x1B,0x0F
	.byte	0xEB,0xDC,0xE5,0xFE,0x11,0x11,0x03,0xFA
	.byte	0xF4,0xFA,0x0B,0x0A,0x0A,0x18,0x16,0xF4
	.byte	0xDD,0xE2,0xF9,0x0F,0x12,0x04,0xFA,0xF6
	.byte	0xF9,0x0A,0x0C,0x0A,0x15,0x18,0xFC,0xDF
	.byte	0xDF,0xF2,0x0A,0x11,0x08,0xFA,0xF6,0xF9
	.byte	0x07,0x0F,0x08,0x12,0x1A,0x06,0xE5,0xDE
	.byte	0xEB,0x04,0x10,0x0D,0xFC,0xF5,0xF8,0x05
	.byte	0x0F,0x07,0x0D,0x19,0x10,0xEF,0xE0,0xE4
	.byte	0xFC,0x0D,0x0F,0x02,0xF4,0xF8,0x01,0x0D
	.byte	0x06,0x09,0x16,0x16,0xF7,0xE3,0xE2,0xF7
	.byte	0x0B,0x0E,0x06,0xF6,0xF6,0xFE,0x0C,0x07
	.byte	0x08,0x12,0x18,0xFF,0xE6,0xE2,0xF1,0x0C
	.byte	0x0F,0x08,0xF7,0xF4,0xFB,0x0A,0x09,0x06
	.byte	0x0E,0x18,0x07,0xEB,0xE4,0xEE,0x0B,0x0F
	.byte	0x07,0xF8,0xF2,0xF8,0x07,0x0B,0x05,0x0B
	.byte	0x15,0x0F,0xF1,0xE8,0xEA,0x05,0x12,0x06
	.byte	0xF9,0xF2,0xF5,0x03,0x0C,0x07,0x09,0x12
	.byte	0x14,0xFA,0xEC,0xE9,0xFD,0x11,0x08,0xF9
	.byte	0xF5,0xF5,0xFD,0x0B,0x08,0x07,0x10,0x16
	.byte	0x01,0xEE,0xE8,0xF6,0x0F,0x0C,0xF9,0xF4
	.byte	0xF5,0xFB,0x08,0x0A,0x08,0x0D,0x17,0x07
	.byte	0xF1,0xE9,0xF2,0x0C,0x11,0xFA,0xF3,0xF5
	.byte	0xF8,0x06,0x0A,0x09,0x09,0x16,0x0A,0xF6
	.byte	0xEB,0xF2,0x07,0x12,0xFE,0xEF,0xF5,0xF6
	.byte	0x04,0x0A,0x0A,0x07,0x13,0x0E,0xFB,0xED
	.byte	0xF0,0x05,0x11,0x01,0xED,0xF3,0xF5,0x02
	.byte	0x09,0x0B,0x07,0x0F,0x11,0xFF,0xF1,0xEF
	.byte	0x05,0x11,0x06,0xEE,0xEF,0xF4,0x00,0x06
	.byte	0x0A,0x09,0x0C,0x13,0x04,0xF4,0xEC,0x02
	.byte	0x13,0x0B,0xF1,0xEB,0xF4,0xFC,0x04,0x06
	.byte	0x0C,0x0C,0x14,0x09,0xF6,0xEB,0xFD,0x15
	.byte	0x10,0xF6,0xE7,0xF0,0xF9,0x02,0x03,0x0C
	.byte	0x0D,0x13,0x0F,0xFA,0xEB,0xF5,0x15,0x16
	.byte	0xFE,0xE8,0xED,0xF5,0x00,0x00,0x08,0x0F
	.byte	0x12,0x12,0xFF,0xED,0xEF,0x0F,0x19,0x04
	.byte	0xEA,0xE9,0xF2,0xFE,0xFF,0x02,0x10,0x11
	.byte	0x16,0x05,0xF2,0xEB,0x08,0x1B,0x0A,0xEF
	.byte	0xE7,0xF1,0xFD,0x00,0xFD,0x0C,0x0F,0x17
	.byte	0x0B,0xF5,0xEB,0xFF,0x19,0x10,0xF6,0xE6
	.byte	0xEF,0xFA,0x00,0xFA,0x08,0x0F,0x17,0x11
	.byte	0xFA,0xEC,0xF9,0x16,0x15,0xFB,0xE6,0xED
	.byte	0xF8,0x00,0xFA,0x02,0x0E,0x15,0x17,0x01
	.byte	0xEC,0xF3,0x10,0x1A,0x03,0xE9,0xEB,0xF5
	.byte	0xFE,0xF9,0xFC,0x0B,0x14,0x1B,0x09,0xF1
	.byte	0xEE,0x08,0x1A,0x0C,0xED,0xEA,0xF4,0xFB
	.byte	0xF9,0xF7,0x08,0x10,0x1C,0x11,0xF7,0xEB
	.byte	0x00,0x17,0x13,0xF4,0xE9,0xF3,0xF9,0xF9
	.byte	0xF4,0x03,0x0C,0x19,0x19,0x01,0xED,0xF8
	.byte	0x12,0x15,0xFB,0xE8,0xF2,0xF9,0xFB,0xF2
	.byte	0xFE,0x08,0x14,0x1D,0x0B,0xF3,0xF4,0x0C
	.byte	0x13,0x01,0xE9,0xF0,0xF8,0xFB,0xF1,0xF9
	.byte	0x06,0x0F,0x1E,0x15,0xFC,0xEF,0x06,0x11
	.byte	0x07,0xEB,0xEE,0xF9,0xFA,0xF2,0xF4,0x05
	.byte	0x0C,0x1A,0x1A,0x06,0xF0,0x02,0x10,0x0A
	.byte	0xF1,0xE9,0xF9,0xFB,0xF3,0xEF,0x01,0x09
	.byte	0x16,0x1B,0x10,0xF3,0xFD,0x0E,0x0C,0xF9
	.byte	0xE7,0xF6,0xFD,0xF6,0xED,0xFC,0x05,0x10
	.byte	0x1B,0x18,0xFA,0xF7,0x0B,0x0E,0x01,0xE8
	.byte	0xF1,0xFC,0xFA,0xEC,0xF9,0x03,0x0C,0x18
	.byte	0x1D,0x03,0xF4,0x08,0x0E,0x06,0xED,0xED
	.byte	0xF9,0xFB,0xEC,0xF3,0x00,0x08,0x14,0x1E
	.byte	0x11,0xF5,0x05,0x0E,0x0A,0xF2,0xEA,0xF4
	.byte	0xFD,0xEF,0xF1,0xFD,0x04,0x0E,0x1C,0x1B
	.byte	0xFB,0x02,0x0D,0x0C,0xF8,0xEA,0xF0,0xFC
	.byte	0xF4,0xEF,0xFB,0x00,0x0A,0x18,0x21,0x01
	.byte	0xFE,0x0A,0x0E,0xFC,0xEB,0xEC,0xF9,0xF9
	.byte	0xEF,0xF9,0xFE,0x08,0x14,0x25,0x09,0xFC
	.byte	0x06,0x0F,0x02,0xED,0xEB,0xF5,0xFE,0xEF
	.byte	0xF4,0xFB,0x05,0x10,0x26,0x12,0xFB,0x03
	.byte	0x0B,0x09,0xF2,0xEC,0xF0,0xFF,0xF3,0xF3
	.byte	0xF8,0x03,0x0C,0x22,0x1B,0xFD,0x01,0x04
	.byte	0x0D,0xF9,0xF1,0xED,0xFB,0xF6,0xF0,0xF5
	.byte	0xFE,0x0A,0x1F,0x24,0x02,0x01,0x00,0x0C
	.byte	0x00,0xF3,0xEA,0xF5,0xFA,0xF1,0xF4,0xF8
	.byte	0x05,0x19,0x2B,0x0A,0x00,0xFE,0x07,0x06
	.byte	0xF7,0xEC,0xF0,0xFC,0xF3,0xF4,0xF5,0x00
	.byte	0x10,0x2C,0x15,0x02,0x00,0x01,0x06,0xFA
	.byte	0xF0,0xED,0xFA,0xF6,0xF3,0xF3,0xF9,0x09
	.byte	0x27,0x21,0x06,0x02,0xFF,0x06,0xFD,0xF3
	.byte	0xEB,0xF6,0xFA,0xF2,0xF2,0xF5,0x04,0x22
	.byte	0x28,0x0D,0x03,0xFD,0x03,0x00,0xF5,0xEE
	.byte	0xF1,0xFF,0xF2,0xF0,0xF3,0xFE,0x1A,0x2A
	.byte	0x15,0x06,0xFE,0x01,0x04,0xF8,0xF3,0xED
	.byte	0xFE,0xF5,0xEC,0xF1,0xF8,0x13,0x28,0x1F
	.byte	0x09,0xFF,0xFD,0x07,0xFA,0xF7,0xEC,0xF9
	.byte	0xFC,0xEA,0xF1,0xF3,0x0C,0x23,0x26,0x0F
	.byte	0x00,0xFB,0x07,0xFD,0xF8,0xF0,0xF2,0x01
	.byte	0xEC,0xF0,0xF2,0x03,0x1D,0x27,0x19,0x04
	.byte	0xFA,0x03,0x01,0xF8,0xF5,0xED,0x03,0xF2
	.byte	0xEA,0xF1,0xFB,0x17,0x25,0x22,0x08,0xFA
	.byte	0x00,0x02,0xF7,0xF9,0xEE,0xFF,0xFB,0xE7
	.byte	0xF0,0xF5,0x12,0x21,0x28,0x10,0xFB,0xFD
	.byte	0x03,0xF9,0xFB,0xF1,0xF8,0x03,0xE6,0xEF
	.byte	0xF1,0x0B,0x1C,0x26,0x1B,0xFC,0xFD,0xFF
	.byte	0xFD,0xF9,0xF7,0xF2,0x06,0xEC,0xEB,0xF1
	.byte	0x03,0x1A,0x21,0x25,0x02,0xFD,0xFB,0xFF
	.byte	0xFB,0xFB,0xF1,0x03,0xF2,0xE3,0xEF,0xFA
	.byte	0x18,0x1D,0x2A,0x0A,0xFE,0xFA,0xFE,0xFE
	.byte	0xFD,0xF4,0xFD,0xFB,0xDF,0xEE,0xF4,0x16
	.byte	0x19,0x29,0x15,0xFF,0xF9,0xF8,0x01,0xFD
	.byte	0xF8,0xF7,0x01,0xE1,0xE9,0xEF,0x0E,0x1A
	.byte	0x25,0x1D,0x04,0xFC,0xF4,0x02,0xFE,0xFD
	.byte	0xF6,0x02,0xE6,0xE3,0xEC,0x07,0x1A,0x20
	.byte	0x23,0x0A,0x00,0xF0,0xFE,0xFF,0xFF,0xF8
	.byte	0x02,0xED,0xE1,0xE9,0xFF,0x17,0x1D,0x26
	.byte	0x10,0x05,0xEF,0xF8,0x00,0x00,0xFB,0x02
	.byte	0xF4,0xDF,0xE5,0xF8,0x14,0x18,0x25,0x15
	.byte	0x0B,0xF2,0xF2,0xFF,0x02,0x00,0x02,0xF9
	.byte	0xE0,0xE2,0xF1,0x11,0x15,0x25,0x1A,0x0F
	.byte	0xF9,0xEF,0xFB,0x02,0x04,0x00,0xFD,0xE2
	.byte	0xDF,0xEA,0x0D,0x13,0x20,0x1F,0x13,0x01
	.byte	0xEC,0xF8,0x01,0x08,0xFF,0x01,0xE7,0xDC
	.byte	0xE3,0x07,0x14,0x1C,0x22,0x14,0x09,0xEF
	.byte	0xF3,0xFB,0x0C,0x00,0x03,0xF1,0xDB,0xDE
	.byte	0xFC,0x15,0x18,0x24,0x17,0x0F,0xF6,0xF0
	.byte	0xF4,0x08,0x06,0x02,0xF9,0xDF,0xDB,0xF2
	.byte	0x13,0x14,0x21,0x1B,0x13,0xFD,0xEF,0xEE
	.byte	0x00,0x0C,0x04,0x00,0xE4,0xD9,0xE8,0x0F
	.byte	0x13,0x1C,0x1E,0x18,0x06,0xF4,0xED,0xF6
	.byte	0x0D,0x06,0x04,0xEB,0xD9,0xE2,0x05,0x12
	.byte	0x15,0x1F,0x1D,0x0C,0xF6,0xEE,0xEE,0x0C
	.byte	0x0C,0x07,0xF2,0xDA,0xDD,0xFD,0x11,0x0F
	.byte	0x1C,0x22,0x14,0xFA,0xF1,0xE7,0x03,0x10
	.byte	0x09,0xFA,0xDE,0xD8,0xF3,0x11,0x0D,0x17
	.byte	0x25,0x1D,0xFF,0xF4,0xE8,0xF9,0x12,0x0A
	.byte	0x01,0xE3,0xD4,0xE9,0x0D,0x0E,0x10,0x24
	.byte	0x25,0x07,0xF4,0xE8,0xEF,0x0E,0x0D,0x06
	.byte	0xED,0xD6,0xDF,0x07,0x13,0x0A,0x1E,0x2A
	.byte	0x11,0xF6,0xEB,0xE8,0x06,0x10,0x0A,0xF6
	.byte	0xDA,0xD8,0xFD,0x14,0x0B,0x15,0x2C,0x1C
	.byte	0xFB,0xEC,0xE5,0xFD,0x0F,0x0D,0xFC,0xE2
	.byte	0xD5,0xF1,0x11,0x0E,0x0D,0x28,0x27,0x02
	.byte	0xEE,0xE4,0xF5,0x0B,0x10,0x00,0xE9,0xD6
	.byte	0xE8,0x0C,0x12,0x0A,0x21,0x2E,0x0A,0xF0
	.byte	0xE3,0xEF,0x05,0x12,0x06,0xF0,0xDA,0xDE
	.byte	0x03,0x12,0x09,0x19,0x33,0x17,0xF5,0xE2
	.byte	0xE8,0x01,0x10,0x0B,0xF5,0xE2,0xD9,0xFC
	.byte	0x11,0x0A,0x10,0x31,0x22,0xF9,0xE4,0xE2
	.byte	0xFD,0x0D,0x0F,0xFC,0xEA,0xD8,0xF1,0x0F
	.byte	0x0F,0x0C,0x27,0x2E,0x01,0xE8,0xDB,0xF7
	.byte	0x07,0x10,0x02,0xF0,0xDC,0xE5,0x0B,0x0F
	.byte	0x0D,0x1C,0x36,0x0A,0xEC,0xD9,0xEF,0x07
	.byte	0x0E,0x09,0xF6,0xE5,0xDC,0x03,0x0D,0x0E
	.byte	0x14,0x35,0x18,0xF1,0xDB,0xE5,0x06,0x0A
	.byte	0x0E,0xF9,0xEF,0xD8,0xF8,0x0A,0x0E,0x12
	.byte	0x31,0x28,0xF7,0xE0,0xDA,0x02,0x09,0x0F
	.byte	0xFC,0xF6,0xDD,0xEB,0x08,0x0B,0x10,0x25
	.byte	0x34,0x02,0xE9,0xD5,0xF9,0x09,0x10,0x01
	.byte	0xF7,0xE5,0xDF,0x04,0x09,0x10,0x1B,0x38
	.byte	0x10,0xF0,0xD8,0xEC,0x07,0x0E,0x07,0xF6
	.byte	0xEF,0xD9,0xFB,0x06,0x0F,0x14,0x35,0x1F
	.byte	0xF7,0xDF,0xE1,0x03,0x0C,0x0B,0xF6,0xF6
	.byte	0xDA,0xF1,0x06,0x0D,0x0F,0x2E,0x2C,0x00
	.byte	0xE7,0xDA,0xFA,0x0B,0x10,0xF8,0xF8,0xE0
	.byte	0xE7,0x03,0x0B,0x0C,0x24,0x34,0x0A,0xF0
	.byte	0xD9,0xEF,0x08,0x13,0xFB,0xF7,0xE8,0xE0
	.byte	0xFD,0x0B,0x09,0x1B,0x37,0x17,0xF8,0xDE
	.byte	0xE5,0x00,0x13,0x00,0xF7,0xEF,0xDF,0xF4
	.byte	0x0A,0x08,0x11,0x36,0x22,0x02,0xE6,0xE1
	.byte	0xF6,0x11,0x07,0xF7,0xF2,0xE1,0xED,0x06
	.byte	0x08,0x08,0x30,0x2A,0x0B,0xEF,0xDF,0xEE
	.byte	0x0B,0x0B,0xF8,0xF4,0xE5,0xEA,0x02,0x0B
	.byte	0x02,0x27,0x2E,0x14,0xF9,0xE2,0xE6,0x03
	.byte	0x10,0xFB,0xF5,0xE7,0xE9,0xFC,0x0D,0xFF
	.byte	0x1C,0x30,0x1E,0x04,0xE7,0xE2,0xFA,0x11
	.byte	0xFF,0xF6,0xE9,0xE7,0xF5,0x0D,0x00,0x11
	.byte	0x2D,0x23,0x0F,0xEE,0xE1,0xF0,0x0D,0x03
	.byte	0xFA,0xEB,0xE7,0xEF,0x0C,0x05,0x07,0x28
	.byte	0x24,0x19,0xF5,0xE2,0xE9,0x08,0x05,0xFD
	.byte	0xF0,0xE7,0xEB,0x05,0x0B,0x02,0x22,0x23
	.byte	0x20,0xFF,0xE4,0xE4,0x03,0x08,0xFF,0xF5
	.byte	0xE7,0xEA,0xFB,0x0F,0xFF,0x18,0x21,0x24
	.byte	0x0D,0xEA,0xE1,0xFB,0x09,0xFF,0xFB,0xE9
	.byte	0xE9,0xF5,0x10,0x01,0x10,0x1D,0x23,0x19
	.byte	0xF1,0xE0,0xF2,0x07,0x00,0x00,0xED,0xE8
	.byte	0xF1,0x0B,0x05,0x07,0x1A,0x1E,0x21,0xFC
	.byte	0xE3,0xEC,0x05,0x00,0x02,0xF4,0xE7,0xED
	.byte	0x07,0x0A,0x04,0x14,0x18,0x24,0x08,0xE8
	.byte	0xE7,0x00,0x02,0x03,0xFB,0xE8,0xEA,0x00
	.byte	0x0B,0x02,0x10,0x14,0x23,0x14,0xF0,0xE6
	.byte	0xFA,0x03,0x04,0xFF,0xE9,0xE6,0xFA,0x0B
	.byte	0x02,0x0C,0x0F,0x1E,0x1C,0xFA,0xE7,0xF4
	.byte	0x03,0x04,0x03,0xEF,0xE4,0xF4,0x0A,0x04
	.byte	0x09,0x0D,0x18,0x21,0x03,0xEB,0xEF,0x00
	.byte	0x04,0x05,0xF5,0xE3,0xEE,0x05,0x06,0x08
	.byte	0x0C,0x11,0x21,0x0E,0xEF,0xED,0xFC,0x06
	.byte	0x06,0xFB,0xE7,0xEA,0x00,0x04,0x05,0x0B
	.byte	0x0D,0x1F,0x16,0xF6,0xEC,0xF6,0x04,0x08
	.byte	0x01,0xEB,0xE6,0xFA,0x03,0x07,0x0A,0x0B
	.byte	0x1A,0x1D,0xFD,0xEB,0xF3,0x03,0x0A,0x04
	.byte	0xF1,0xE2,0xF7,0x00,0x05,0x0A,0x07,0x15
	.byte	0x1F,0x06,0xEF,0xF1,0xFF,0x0C,0x05,0xF6
	.byte	0xE1,0xF3,0xFE,0x03,0x0A,0x06,0x10,0x20
	.byte	0x10,0xF1,0xF1,0xF9,0x0B,0x08,0xFB,0xE3
	.byte	0xEE,0xFD,0xFE,0x0A,0x03,0x0D,0x1E,0x18
	.byte	0xF6,0xF1,0xF6,0x09,0x0C,0xFF,0xE9,0xE9
	.byte	0xFD,0xFA,0x09,0x04,0x07,0x1A,0x1D,0xFE
	.byte	0xF0,0xF4,0x03,0x0E,0x02,0xEF,0xE6,0xFB
	.byte	0xF7,0x04,0x06,0x04,0x16,0x20,0x07,0xF1
	.byte	0xF4,0xFE,0x0D,0x05,0xF4,0xE6,0xF9,0xF8
	.byte	0xFE,0x06,0x01,0x11,0x20,0x11,0xF3,0xF4
	.byte	0xFB,0x0C,0x08,0xF9,0xE7,0xF5,0xFB,0xF8
	.byte	0x05,0x00,0x0C,0x1E,0x18,0xF8,0xF2,0xF9
	.byte	0x08,0x0B,0xFE,0xEB,0xF0,0xFB,0xF6,0x03
	.byte	0x02,0x08,0x19,0x1D,0xFF,0xF2,0xF8,0x05
	.byte	0x0B,0x02,0xF0,0xED,0xFC,0xF4,0xFE,0x02
	.byte	0x06,0x13,0x21,0x08,0xF1,0xF5,0x02,0x0C
	.byte	0x05,0xF4,0xEA,0xFC,0xF5,0xFA,0x02,0x04
	.byte	0x0D,0x21,0x13,0xF2,0xF4,0xFE,0x0B,0x06
	.byte	0xFB,0xEA,0xFB,0xF6,0xF6,0xFF,0x04,0x08
	.byte	0x1C,0x1C,0xF7,0xF3,0xFB,0x0B,0x05,0x00
	.byte	0xEB,0xF8,0xF8,0xF3,0xFD,0x04,0x07,0x15
	.byte	0x25,0xFD,0xF1,0xF7,0x0B,0x06,0x03,0xEE
	.byte	0xF3,0xFD,0xF1,0xFB,0x02,0x06,0x0D,0x29
	.byte	0x06,0xF1,0xF3,0x08,0x09,0x04,0xF5,0xED
	.byte	0xFE,0xF1,0xFA,0xFF,0x09,0x06,0x27,0x11
	.byte	0xF4,0xF0,0x03,0x0C,0x03,0xFD,0xEA,0xFF
	.byte	0xF3,0xF6,0xFB,0x08,0x02,0x21,0x1E,0xF5
	.byte	0xF1,0xFD,0x10,0x01,0x02,0xE8,0xFC,0xF6
	.byte	0xF5,0xFA,0x06,0x03,0x15,0x28,0xFA,0xF0
	.byte	0xF6,0x11,0x06,0x07,0xEE,0xF4,0xF8,0xF2
	.byte	0xF7,0x01,0x07,0x09,0x2C,0x05,0xF1,0xF3
	.byte	0x0D,0x0A,0x06,0xF4,0xEF,0xFC,0xF2,0xF9
	.byte	0xFB,0x0B,0x03,0x28,0x10,0xF0,0xF0,0x07
	.byte	0x0F,0x09,0xFE,0xEC,0xFB,0xF1,0xF9,0xF7
	.byte	0x0A,0x03,0x1D,0x1D,0xF4,0xEE,0x00,0x11
	.byte	0x0A,0x03,0xEB,0xF9,0xF2,0xF9,0xF8,0x06
	.byte	0x07,0x11,0x22,0xFA,0xEB,0xF9,0x11,0x0D
	.byte	0x09,0xEE,0xF6,0xF3,0xF6,0xF9,0xFE,0x0B
	.byte	0x0A,0x22,0x05,0xED,0xF3,0x0F,0x11,0x0C
	.byte	0xF2,0xF0,0xF5,0xF2,0xFD,0xF8,0x09,0x08
	.byte	0x1D,0x0F,0xF0,0xEE,0x09,0x14,0x0E,0xFB
	.byte	0xEC,0xF7,0xF0,0xFE,0xF7,0x05,0x0A,0x18
	.byte	0x15,0xF6,0xED,0x00,0x15,0x11,0x02,0xEA
	.byte	0xF5,0xEF,0xFC,0xFB,0xFF,0x0C,0x12,0x18
	.byte	0xFD,0xEC,0xF9,0x14,0x13,0x09,0xEE,0xF2
	.byte	0xEF,0xF8,0x00,0xF8,0x0A,0x0F,0x19,0x05
	.byte	0xEE,0xF3,0x0F,0x13,0x0C,0xF3,0xEF,0xF1
	.byte	0xF2,0x03,0xF9,0x06,0x0E,0x15,0x0D,0xF3
	.byte	0xEE,0x08,0x16,0x11,0xFA,0xED,0xF2,0xEE
	.byte	0x04,0xFA,0x01,0x0C,0x12,0x12,0xFB,0xEC
	.byte	0xFF,0x13,0x14,0x02,0xEC,0xF1,0xEC,0x02
	.byte	0x02,0xFD,0x0B,0x0E,0x12,0x02,0xED,0xF7
	.byte	0x0F,0x16,0x0B,0xEF,0xF0,0xEB,0xFB,0x05
	.byte	0xFC,0x07,0x0D,0x11,0x0A,0xF2,0xF1,0x0B
	.byte	0x15,0x13,0xF3,0xEE,0xEC,0xF5,0x07,0xFD
	.byte	0x04,0x0A,0x0E,0x0D,0xFA,0xED,0x04,0x12
	.byte	0x18,0xFC,0xEC,0xED,0xEF,0x05,0x00,0x01
	.byte	0x09,0x0B,0x0E,0x03,0xED,0xFC,0x0D,0x1C
	.byte	0x07,0xEF,0xED,0xEC,0x00,0x03,0x01,0x06
	.byte	0x09,0x0C,0x0B,0xF2,0xF6,0x07,0x1A,0x10
	.byte	0xF3,0xEE,0xE9,0xFA,0x04,0x03,0x04,0x08
	.byte	0x07,0x10,0xF9,0xF3,0xFF,0x15,0x19,0xFA
	.byte	0xEE,0xE7,0xF6,0x03,0x05,0x03,0x07,0x03
	.byte	0x0E,0x03,0xF2,0xFB,0x0E,0x1E,0x01,0xF2
	.byte	0xE5,0xF2,0x00,0x08,0x04,0x06,0x01,0x08
	.byte	0x0B,0xF5,0xF7,0x04,0x1E,0x0A,0xF9,0xE6
	.byte	0xEC,0xFE,0x08,0x07,0x04,0x02,0x00,0x0F
	.byte	0xFB,0xF7,0xFD,0x1A,0x11,0xFF,0xEB,0xE7
	.byte	0xFB,0x05,0x0A,0x03,0x04,0xFB,0x0F,0x02
	.byte	0xF8,0xF7,0x11,0x15,0x05,0xF4,0xE2,0xF9
	.byte	0x03,0x0C,0x01,0x04,0xF7,0x0A,0x09,0xFB
	.byte	0xF6,0x06,0x17,0x09,0xFF,0xE2,0xF3,0x00
	.byte	0x0C,0x02,0x04,0xF8,0x01,0x0E,0xFE,0xF9
	.byte	0xFC,0x14,0x0C,0x08,0xE7,0xEE,0xFE,0x0B
	.byte	0x05,0x03,0xFC,0xF7,0x0F,0x01,0xFD,0xF7
	.byte	0x0F,0x0E,0x0F,0xF0,0xE7,0xFA,0x07,0x09
	.byte	0x00,0x01,0xF1,0x0C,0x05,0x00,0xF7,0x07
	.byte	0x0D,0x11,0xFE,0xE5,0xF8,0x03,0x0D,0xFE
	.byte	0x03,0xEF,0x03,0x0A,0x04,0xFA,0x01,0x0B
	.byte	0x0D,0x0A,0xE7,0xF5,0x00,0x0F,0xFF,0x02
	.byte	0xF3,0xFA,0x0B,0x03,0xFF,0xFC,0x09,0x09
	.byte	0x13,0xF0,0xF0,0xFD,0x0C,0x05,0xFF,0xF7
	.byte	0xF1,0x09,0x06,0x04,0xFA,0x06,0x04,0x15
	.byte	0xFE,0xEC,0xFC,0x08,0x09,0xFF,0xFB,0xED
	.byte	0x03,0x07,0x07,0xFC,0x01,0x03,0x10,0x0C
	.byte	0xEC,0xFA,0x06,0x0A,0xFF,0xFC,0xEC,0xFC
	.byte	0x09,0x07,0x01,0xFE,0x02,0x07,0x14,0xF2
	.byte	0xF5,0x08,0x0A,0x02,0xFD,0xEF,0xF3,0x09
	.byte	0x07,0x05,0xFC,0x02,0x03,0x15,0xFE,0xEF
	.byte	0x08,0x09,0x02,0xFD,0xF3,0xEB,0x07,0x08
	.byte	0x07,0xFD,0x00,0x02,0x0F,0x0B,0xEE,0x05
	.byte	0x0B,0x04,0xFC,0xF9,0xE7,0xFE,0x0B,0x06
	.byte	0x02,0xFC,0x02,0x08,0x15,0xF2,0x00,0x0C
	.byte	0x05,0xFC,0xFB,0xEA,0xF1,0x0D,0x05,0x08
	.byte	0xFC,0x02,0x02,0x15,0xFB,0xF9,0x0F,0x06
	.byte	0xFD,0xF9,0xF2,0xE6,0x0B,0x07,0x09,0xFF
	.byte	0x00,0x00,0x10,0x06,0xF3,0x0F,0x07,0xFF
	.byte	0xF6,0xF8,0xE2,0x03,0x0C,0x07,0x04,0xFD
	.byte	0xFF,0x0A,0x10,0xF2,0x0D,0x0B,0x00,0xF3
	.byte	0xF9,0xE7,0xF5,0x10,0x06,0x08,0xFC,0xFF
	.byte	0x04,0x15,0xF5,0x07,0x11,0x01,0xF5,0xF6
	.byte	0xF0,0xE9,0x0E,0x08,0x0A,0xFE,0xFE,0x00
	.byte	0x14,0xFE,0xFD,0x17,0x04,0xF8,0xF0,0xF5
	.byte	0xE5,0x06,0x0C,0x0A,0x04,0xFC,0x00,0x0E
	.byte	0x07,0xF7,0x17,0x0B,0xFA,0xED,0xF5,0xE8
	.byte	0xFA,0x0F,0x09,0x08,0xF9,0xFD,0x0A,0x0C
	.byte	0xF6,0x10,0x14,0xFD,0xEE,0xF1,0xEE,0xF0
	.byte	0x0E,0x0B,0x0D,0xFD,0xFA,0x07,0x0F,0xFA
	.byte	0x07,0x1B,0x04,0xEF,0xED,0xF3,0xEC,0x07
	.byte	0x0D,0x0E,0x03,0xF4,0x03,0x0E,0xFF,0x00
	.byte	0x1B,0x0C,0xF3,0xEA,0xF3,0xED,0xFE,0x0F
	.byte	0x0F,0x09,0xF3,0xFD,0x0D,0x04,0xFB,0x15
	.byte	0x16,0xF8,0xE8,0xF0,0xEF,0xF6,0x0F,0x10
	.byte	0x0F,0xF6,0xF4,0x0A,0x09,0xFB,0x0C,0x1D
	.byte	0x02,0xEA,0xED,0xF1,0xF1,0x0B,0x13,0x11
	.byte	0xFD,0xEC,0x04,0x0B,0xFD,0x03,0x1D,0x0D
	.byte	0xEE,0xE9,0xF0,0xEF,0x03,0x16,0x14,0x06
	.byte	0xEB,0xFA,0x0D,0x02,0xFD,0x18,0x17,0xF4
	.byte	0xE8,0xED,0xEF,0xFB,0x15,0x17,0x0D,0xEF
	.byte	0xF0,0x0A,0x08,0xFB,0x0E,0x1E,0xFE,0xEA
	.byte	0xE9,0xEF,0xF6,0x10,0x1A,0x11,0xF8,0xE8
	.byte	0x01,0x0C,0xFF,0x05,0x1F,0x09,0xED,0xE7
	.byte	0xEC,0xF5,0x08,0x1B,0x14,0x01,0xE7,0xF6
	.byte	0x0C,0x05,0xFD,0x1A,0x14,0xF4,0xE7,0xE7
	.byte	0xF3,0x01,0x1B,0x19,0x08,0xEC,0xEC,0x07
	.byte	0x0A,0xFB,0x10,0x1C,0xFD,0xEB,0xE3,0xF2
	.byte	0xFD,0x15,0x1D,0x0E,0xF3,0xE5,0xFF,0x0E
	.byte	0xFF,0x05,0x1F,0x07,0xF0,0xE2,0xED,0xFB
	.byte	0x0E,0x20,0x14,0xFD,0xE4,0xF4,0x0D,0x04
	.byte	0xFD,0x1A,0x13,0xF6,0xE3,0xE4,0xFA,0x08
	.byte	0x1E,0x1A,0x05,0xE8,0xE9,0x07,0x0A,0xFB
	.byte	0x11,0x1B,0xFD,0xE6,0xE0,0xF6,0x06,0x19
	.byte	0x1E,0x0B,0xF0,0xE3,0xFE,0x0D,0xFE,0x06
	.byte	0x1E,0x07,0xEB,0xDF,0xEE,0x04,0x15,0x20
	.byte	0x11,0xF8,0xE2,0xF4,0x0C,0x04,0xFF,0x1A
	.byte	0x13,0xF0,0xDF,0xE6,0x01,0x12,0x20,0x16
	.byte	0xFF,0xE4,0xEB,0x05,0x0B,0xFB,0x10,0x1B
	.byte	0xFA,0xE2,0xE2,0xFA,0x10,0x1E,0x1B,0x06
	.byte	0xEA,0xE6,0xFC,0x0E,0xFF,0x06,0x1F,0x04
	.byte	0xE5,0xDF,0xF1,0x0B,0x1E,0x1C,0x0C,0xF0
	.byte	0xE5,0xF1,0x0C,0x06,0xFE,0x1B,0x0F,0xEC
	.byte	0xDE,0xEC,0x05,0x1E,0x1E,0x12,0xF6,0xE6
	.byte	0xEB,0x04,0x0C,0xF9,0x15,0x17,0xF5,0xDF
	.byte	0xE7,0xFB,0x1C,0x23,0x17,0xFF,0xE9,0xE8
	.byte	0xF9,0x0F,0xFA,0x0E,0x1C,0xFD,0xE1,0xE4
	.byte	0xF3,0x14,0x26,0x19,0x07,0xEE,0xE8,0xEE
	.byte	0x0E,0xFF,0x03,0x1D,0x06,0xE7,0xE2,0xEE
	.byte	0x0B,0x26,0x1C,0x0D,0xF4,0xEA,0xE7,0x06
	.byte	0x07,0xFB,0x1C,0x0F,0xEB,0xE0,0xEA,0x02
	.byte	0x24,0x20,0x11,0xFA,0xED,0xE5,0xFA,0x0D
	.byte	0xF8,0x16,0x18,0xF2,0xE2,0xE8,0xFD,0x1E
	.byte	0x24,0x14,0xFF,0xEF,0xE6,0xEF,0x0E,0xFC
	.byte	0x0C,0x1F,0xFA,0xE3,0xE4,0xF7,0x16,0x25
	.byte	0x19,0x06,0xF2,0xE8,0xE8,0x08,0x03,0x01
	.byte	0x21,0x04,0xE7,0xE3,0xF3,0x10,0x21,0x1D
	.byte	0x0C,0xF6,0xEA,0xE5,0xFE,0x09,0xFC,0x1D
	.byte	0x0F,0xEC,0xE1,0xED,0x0B,0x1C,0x1F,0x12
	.byte	0xFD,0xED,0xE5,0xF4,0x0A,0xFB,0x15,0x1A
	.byte	0xF4,0xE1,0xE7,0x06,0x17,0x1D,0x17,0x03
	.byte	0xF0,0xE6,0xED,0x07,0xFE,0x0C,0x20,0xFE
	.byte	0xE3,0xE2,0x00,0x15,0x19,0x1A,0x09,0xF5
	.byte	0xE9,0xE9,0x02,0x00,0x03,0x1F,0x0C,0xE7
	.byte	0xDD,0xF8,0x14,0x15,0x19,0x0F,0xFB,0xED
	.byte	0xE6,0xFD,0x03,0xFF,0x18,0x16,0xEF,0xDB
	.byte	0xEF,0x11,0x14,0x16,0x15,0x00,0xF3,0xE4
	.byte	0xF6,0x04,0xFF,0x10,0x1D,0xFA,0xDB,0xE7
	.byte	0x0B,0x16,0x10,0x18,0x06,0xF8,0xE7,0xF0
	.byte	0x03,0xFF,0x09,0x1D,0x08,0xDD,0xE1,0x01
	.byte	0x17,0x0C,0x15,0x0D,0xFD,0xEC,0xEA,0x01
	.byte	0x00,0x05,0x18,0x15,0xE5,0xDD,0xF8,0x15
	.byte	0x0E,0x0F,0x14,0x02,0xF2,0xE6,0xFB,0x00
	.byte	0x04,0x11,0x1C,0xF2,0xD9,0xEF,0x0E,0x14
	.byte	0x08,0x15,0x0A,0xF9,0xE6,0xF5,0x00,0x04
	.byte	0x0D,0x1D,0x01,0xD8,0xE8,0x03,0x17,0x07
	.byte	0x0F,0x11,0xFF,0xEA,0xEF,0xFE,0x03,0x0A
	.byte	0x19,0x10,0xDD,0xE1,0xFB,0x15,0x0D,0x07
	.byte	0x14,0x07,0xF0,0xEB,0xFB,0x02,0x07,0x13
	.byte	0x19,0xEA,0xDB,0xF3,0x0E,0x14,0x03,0x10
	.byte	0x10,0xF6,0xEA,0xF7,0x00,0x07,0x0F,0x1C
	.byte	0xF8,0xD9,0xEC,0x04,0x16,0x06,0x09,0x17
	.byte	0x00,0xEA,0xF3,0xFE,0x05,0x0D,0x1B,0x05
	.byte	0xDC,0xE4,0xFD,0x12,0x0C,0x02,0x15,0x0E
	.byte	0xEC,0xEF,0xFB,0x02,0x0B,0x18,0x10,0xE4
	.byte	0xDE,0xF6,0x0D,0x11,0x02,0x0E,0x18,0xF5
	.byte	0xEB,0xF9,0xFE,0x09,0x16,0x15,0xEF,0xDC
	.byte	0xEE,0x07,0x11,0x05,0x05,0x1C,0x05,0xE9
	.byte	0xF5,0xFA,0x05,0x14,0x19,0xF9,0xDD,0xE6
	.byte	0x02,0x11,0x08,0x00,0x16,0x14,0xED,0xF1
	.byte	0xF9,0xFF,0x11,0x1C,0x03,0xE3,0xE0,0xF8
	.byte	0x0F,0x0A,0x00,0x0E,0x1E,0xF9,0xED,0xF8
	.byte	0xFC,0x0A,0x1C,0x0C,0xE9,0xDF,0xEF,0x0B
	.byte	0x0C,0x01,0x07,0x1F,0x07,0xEC,0xF5,0xF9
	.byte	0x05,0x19,0x13,0xF0,0xDF,0xE7,0x04,0x0E
	.byte	0x03,0x03,0x1C,0x15,0xF3,0xF2,0xF7,0x00
	.byte	0x15,0x18,0xF7,0xE1,0xE2,0xFA,0x0F,0x05
	.byte	0x00,0x15,0x1C,0xFC,0xF0,0xF3,0xFE,0x11
	.byte	0x1C,0x00,0xE4,0xE0,0xF1,0x0C,0x0A,0xFF
	.byte	0x0E,0x20,0x07,0xF4,0xEE,0xF7,0x0D,0x1B
	.byte	0x0A,0xE7,0xDF,0xEA,0x08,0x0D,0x01,0x08
	.byte	0x1E,0x10,0xFA,0xED,0xF1,0x09,0x1A,0x12
	.byte	0xEE,0xDF,0xE4,0xFF,0x0F,0x04,0x03,0x1A
	.byte	0x18,0x02,0xF2,0xE9,0x03,0x17,0x17,0xF7
	.byte	0xE0,0xE0,0xF6,0x0E,0x09,0x02,0x15,0x1C
	.byte	0x09,0xFA,0xE5,0xF9,0x15,0x1A,0x00,0xE2
	.byte	0xDE,0xED,0x0A,0x0C,0x03,0x0F,0x1D,0x0E
	.byte	0x01,0xE6,0xEE,0x10,0x1A,0x09,0xE7,0xDD
	.byte	0xE6,0x04,0x0F,0x05,0x0A,0x1B,0x13,0x09
	.byte	0xEE,0xE5,0x08,0x1C,0x11,0xED,0xDD,0xE0
	.byte	0xFA,0x0F,0x09,0x09,0x18,0x16,0x0D,0xF6
	.byte	0xE0,0xFD,0x19,0x19,0xF6,0xDE,0xDC,0xF1
	.byte	0x0C,0x0C,0x09,0x15,0x16,0x11,0x02,0xE1
	.byte	0xF1,0x14,0x1E,0x00,0xE0,0xD9,0xE7,0x07
	.byte	0x0F,0x0A,0x12,0x16,0x12,0x0A,0xE8,0xE7
	.byte	0x0A,0x21,0x0C,0xE6,0xD9,0xDF,0x00,0x10
	.byte	0x0D,0x10,0x16,0x11,0x11,0xF3,0xE3,0xFF
	.byte	0x1E,0x17,0xED,0xD9,0xD9,0xF5,0x10,0x11
	.byte	0x10,0x16,0x11,0x11,0xFD,0xE4,0xF2,0x16
	.byte	0x20,0xF7,0xDC,0xD4,0xEB,0x0C,0x14,0x10
	.byte	0x14,0x12,0x10,0x06,0xEA,0xEA,0x0A,0x24
	.byte	0x03,0xE0,0xD3,0xE0,0x05,0x16,0x13,0x13
	.byte	0x14,0x10,0x0B,0xF1,0xE8,0xFE,0x22,0x12
	.byte	0xE7,0xD4,0xD7,0xFC,0x14,0x17,0x14,0x14
	.byte	0x0F,0x0D,0xF8,0xE8,0xF4,0x19,0x1D,0xF0
	.byte	0xD7,0xD0,0xF0,0x12,0x1A,0x16,0x14,0x0F
	.byte	0x0E,0xFE,0xEA,0xEF,0x0D,0x22,0xFD,0xDD
	.byte	0xCE,0xE3,0x0C,0x1B,0x19,0x14,0x10,0x0E
	.byte	0x06,0xED,0xED,0x01,0x21,0x0A,0xE4,0xCF
	.byte	0xD7,0x03,0x1B,0x1E,0x17,0x10,0x0E,0x0A
	.byte	0xF1,0xEB,0xF9,0x19,0x16,0xEC,0xD4,0xCF
	.byte	0xF7,0x19,0x20,0x19,0x11,0x0C,0x0D,0xF7
	.byte	0xEC,0xF6,0x0E,0x1D,0xF7,0xD9,0xCC,0xE8
	.byte	0x13,0x22,0x1F,0x14,0x0B,0x0C,0xFD,0xEA
	.byte	0xF4,0x04,0x1D,0x04,0xDE,0xCE,0xDC,0x08
	.byte	0x20,0x23,0x18,0x0C,0x0B,0x04,0xEC,0xF1
	.byte	0xFF,0x17,0x12,0xE4,0xD1,0xD6,0xFA,0x1B
	.byte	0x25,0x1D,0x0E,0x09,0x07,0xF2,0xED,0xFE
	.byte	0x0E,0x1A,0xF0,0xD3,0xD4,0xED,0x14,0x25
	.byte	0x22,0x10,0x08,0x08,0xFA,0xEA,0xFB,0x08
	.byte	0x19,0xFF,0xD5,0xD5,0xE4,0x09,0x23,0x27
	.byte	0x15,0x07,0x06,0x01,0xEB,0xF5,0x07,0x14
	.byte	0x0E,0xDB,0xD5,0xE0,0xFC,0x1C,0x2A,0x1C
	.byte	0x0A,0x03,0x04,0xF2,0xEE,0x07,0x0F,0x16
	.byte	0xE8,0xD0,0xDF,0xF2,0x13,0x27,0x23,0x0E
	.byte	0x03,0x02,0xF9,0xEA,0x02,0x0E,0x17,0xF7
	.byte	0xCF,0xDD,0xED,0x08,0x23,0x29,0x14,0x05
	.byte	0x00,0xFD,0xEA,0xFA,0x0F,0x16,0x05,0xD3
	.byte	0xD7,0xEB,0xFF,0x1A,0x2B,0x1B,0x09,0xFE
	.byte	0xFE,0xEF,0xF2,0x0D,0x16,0x0F,0xDD,0xD2
	.byte	0xE8,0xF9,0x10,0x28,0x23,0x0E,0x01,0xFC
	.byte	0xF4,0xED,0x08,0x16,0x15,0xEB,0xCF,0xE5
	.byte	0xF5,0x08,0x20,0x29,0x14,0x04,0xFB,0xF6
	.byte	0xEB,0xFF,0x16,0x19,0xF8,0xD1,0xDE,0xF1
	.byte	0x00,0x17,0x2A,0x1C,0x08,0xFC,0xF5,0xED
	.byte	0xF7,0x14,0x1E,0x04,0xD5,0xD9,0xEE,0xFC
	.byte	0x0E,0x27,0x23,0x0C,0xFE,0xF5,0xEF,0xF1
	.byte	0x0E,0x21,0x10,0xDE,0xD4,0xEA,0xF7,0x06
	.byte	0x1E,0x27,0x14,0x02,0xF5,0xF1,0xEE,0x07
	.byte	0x20,0x1B,0xEA,0xD0,0xE6,0xF4,0x00,0x15
	.byte	0x29,0x1B,0x07,0xF6,0xF0,0xED,0xFE,0x1F
	.byte	0x24,0xFB,0xD0,0xE0,0xF0,0xFA,0x0C,0x23
	.byte	0x23,0x0E,0xF9,0xEE,0xED,0xF5,0x1A,0x27
	.byte	0x0B,0xD5,0xDA,0xED,0xF5,0x05,0x1C,0x26
	.byte	0x16,0xFF,0xED,0xED,0xEF,0x13,0x2B,0x1A
	.byte	0xE1,0xD1,0xEC,0xEF,0xFE,0x13,0x27,0x1C
	.byte	0x07,0xEF,0xEC,0xEB,0x09,0x2B,0x24,0xF2
	.byte	0xCC,0xE7,0xED,0xF7,0x0D,0x24,0x22,0x0E
	.byte	0xF3,0xEC,0xED,0xFE,0x27,0x2A,0x05,0xCE
	.byte	0xDE,0xED,0xEF,0x04,0x1D,0x26,0x16,0xFA
	.byte	0xEB,0xEE,0xF4,0x20,0x2E,0x16,0xD8,0xD2
	.byte	0xED,0xEA,0xFC,0x15,0x27,0x1E,0x03,0xEB
	.byte	0xF0,0xEF,0x14,0x2F,0x22,0xEC,0xC9,0xE8
	.byte	0xE8,0xF5,0x0B,0x24,0x23,0x0F,0xEF,0xEE
	.byte	0xEE,0x05,0x2D,0x29,0x03,0xC8,0xDE,0xE8
	.byte	0xEF,0x03,0x1C,0x26,0x19,0xF9,0xEA,0xF0
	.byte	0xF9,0x28,0x2D,0x15,0xD3,0xD3,0xE8,0xE8
	.byte	0xFD,0x13,0x26,0x1F,0x07,0xE8,0xF1,0xF1
	.byte	0x1D,0x30,0x20,0xE7,0xC8,0xE5,0xE6,0xF6
	.byte	0x0B,0x24,0x21,0x13,0xED,0xED,0xEE,0x0E
	.byte	0x31,0x27,0xFE,0xC6,0xDC,0xE5,0xF0,0x03
	.byte	0x20,0x23,0x1C,0xF9,0xE8,0xF0,0x00,0x2E
	.byte	0x2A,0x10,0xD2,0xD1,0xE5,0xEB,0xFA,0x18
	.byte	0x24,0x1F,0x08,0xE6,0xEF,0xF6,0x25,0x30
	.byte	0x1C,0xE4,0xC9,0xE0,0xE8,0xF3,0x0F,0x25
	.byte	0x1E,0x16,0xEB,0xEB,0xF2,0x18,0x33,0x22
	.byte	0xF7,0xCA,0xD9,0xE6,0xEC,0x04,0x23,0x1E
	.byte	0x1E,0xF7,0xE7,0xF1,0x0A,0x31,0x28,0x08
	.byte	0xD4,0xCF,0xE4,0xEA,0xFA,0x1C,0x1F,0x1F
	.byte	0x08,0xE6,0xEE,0xFF,0x2A,0x2D,0x12,0xE3
	.byte	0xCB,0xE0,0xE7,0xF1,0x13,0x21,0x1F,0x14
	.byte	0xEB,0xEA,0xF9,0x1E,0x31,0x1A,0xF4,0xCC
	.byte	0xD8,0xE7,0xEB,0x0A,0x21,0x1E,0x1B,0xF9
	.byte	0xE4,0xF4,0x11,0x30,0x23,0x03,0xD5,0xD0
	.byte	0xE5,0xE5,0xFE,0x1C,0x1F,0x1D,0x07,0xE5
	.byte	0xEE,0x09,0x2A,0x28,0x0C,0xE3,0xCC,0xE2
	.byte	0xE2,0xF3,0x17,0x20,0x1D,0x13,0xEE,0xE8
	.byte	0x02,0x20,0x2D,0x16,0xF1,0xCF,0xDC,0xE2
	.byte	0xE9,0x0E,0x20,0x1D,0x18,0xFA,0xE4,0xFC
	.byte	0x16,0x2B,0x1E,0xFB,0xD4,0xD8,0xE4,0xE2
	.byte	0x01,0x1E,0x1F,0x1B,0x08,0xE6,0xF5,0x0F
	.byte	0x24,0x23,0x07,0xDE,0xD4,0xE4,0xE0,0xF6
	.byte	0x18,0x20,0x1A,0x11,0xEE,0xEF,0x0A,0x1C
	.byte	0x24,0x11,0xEA,0xD4,0xE3,0xE0,0xEC,0x0E
	.byte	0x21,0x1A,0x16,0xF8,0xEA,0x07,0x15,0x22
	.byte	0x19,0xF6,0xD6,0xE2,0xE1,0xE4,0x03,0x1D
	.byte	0x1E,0x17,0x05,0xE9,0x02,0x12,0x1C,0x1C
	.byte	0x02,0xDD,0xDF,0xE4,0xDD,0xF9,0x14,0x20
	.byte	0x19,0x0E,0xEC,0xFB,0x13,0x16,0x1D,0x0B
	.byte	0xE7,0xDE,0xE7,0xD9,0xEE,0x0B,0x1F,0x1B
	.byte	0x14,0xF6,0xF3,0x13,0x13,0x1A,0x11,0xF1
	.byte	0xDD,0xE9,0xDB,0xE5,0x02,0x19,0x1F,0x18
	.byte	0x01,0xEE,0x10,0x12,0x16,0x14,0xFA,0xE1
	.byte	0xE9,0xE0,0xDB,0xFB,0x11,0x21,0x1C,0x0B
	.byte	0xED,0x08,0x15,0x10,0x16,0x00,0xEA,0xE8
	.byte	0xE8,0xD6,0xF3,0x09,0x1C,0x1E,0x12,0xF3
	.byte	0xFF,0x18,0x0D,0x14,0x05,0xF1,0xE9,0xEC
	.byte	0xD7,0xE6,0x04,0x16,0x21,0x17,0xFB,0xF5
	.byte	0x19,0x0E,0x10,0x07,0xF6,0xEE,0xED,0xE0
	.byte	0xDB,0xFD,0x0E,0x20,0x1B,0x05,0xF1,0x12
	.byte	0x14,0x0B,0x0C,0xF9,0xF3,0xEE,0xE7,0xD5
	.byte	0xF5,0x09,0x1B,0x1E,0x0E,0xF3,0x06,0x1B
	.byte	0x09,0x0A,0xFC,0xF8,0xF1,0xEE,0xD7,0xE8
	.byte	0x05,0x15,0x1F,0x14,0xFC,0xFA,0x1B,0x0D
	.byte	0x08,0xFF,0xF7,0xF3,0xF2,0xDF,0xDE,0x00
	.byte	0x0E,0x1D,0x17,0x06,0xF4,0x13,0x15,0x05
	.byte	0x03,0xFA,0xF5,0xF5,0xE8,0xD7,0xF6,0x0A
	.byte	0x1B,0x1A,0x0E,0xF7,0x06,0x1B,0x05,0x02
	.byte	0xFD,0xF6,0xF6,0xF0,0xD8,0xEC,0x07,0x15
	.byte	0x1B,0x12,0xFF,0xFA,0x1A,0x0B,0xFF,0x01
	.byte	0xF9,0xF6,0xF8,0xDE,0xE1,0xFF,0x10,0x19
	.byte	0x15,0x09,0xF6,0x13,0x15,0xFD,0x02,0xFD
	.byte	0xF5,0xFA,0xE6,0xD8,0xF7,0x0C,0x18,0x14
	.byte	0x10,0xFA,0x08,0x1A,0xFE,0xFD,0x02,0xF8
	.byte	0xFB,0xF0,0xD6,0xEC,0x07,0x16,0x17,0x16
	.byte	0x01,0xFE,0x1B,0x05,0xF7,0x01,0xFD,0xFA
	.byte	0xFA,0xD9,0xE2,0x01,0x11,0x17,0x17,0x0A
	.byte	0xF8,0x16,0x0F,0xF6,0xFD,0x02,0xF9,0xFD
	.byte	0xE4,0xDA,0xFB,0x0C,0x15,0x17,0x12,0xF8
	.byte	0x0C,0x16,0xFA,0xF7,0x05,0xFB,0xFD,0xF0
	.byte	0xD5,0xF1,0x09,0x13,0x16,0x15,0xFC,0x01
	.byte	0x18,0x03,0xF3,0x03,0x04,0xFB,0xF9,0xD9
	.byte	0xE5,0x04,0x11,0x14,0x18,0x03,0xF9,0x15
	.byte	0x0C,0xF5,0xFD,0x0A,0xFC,0xFD,0xE2,0xDC
	.byte	0xFB,0x0D,0x12,0x17,0x0A,0xF7,0x0F,0x13
	.byte	0xF9,0xF5,0x0C,0x02,0xFC,0xEB,0xD7,0xF1
	.byte	0x0B,0x10,0x17,0x11,0xF7,0x09,0x17,0x03
	.byte	0xF0,0x06,0x09,0xFC,0xF3,0xDA,0xE6,0x04
	.byte	0x0F,0x14,0x17,0xFA,0x01,0x18,0x0C,0xF2
	.byte	0xFC,0x0F,0x00,0xF7,0xE1,0xDE,0xFB,0x0C
	.byte	0x11,0x1A,0x00,0xFA,0x16,0x14,0xF8,0xF2
	.byte	0x0D,0x06,0xF8,0xE8,0xDB,0xF2,0x09,0x10
	.byte	0x19,0x09,0xF5,0x0F,0x1A,0x02,0xEF,0x07
	.byte	0x0B,0xFB,0xEE,0xDC,0xE8,0x02,0x0E,0x17
	.byte	0x11,0xF6,0x06,0x1D,0x0B,0xF1,0xFF,0x10
	.byte	0xFE,0xF2,0xE0,0xE3,0xF9,0x0B,0x15,0x15
	.byte	0xFC,0xFC,0x1C,0x14,0xF6,0xF9,0x10,0x04
	.byte	0xF4,0xE4,0xDF,0xF1,0x05,0x14,0x18,0x04
	.byte	0xF7,0x15,0x1D,0xFE,0xF3,0x0C,0x0C,0xF7
	.byte	0xE7,0xDE,0xEC,0xFD,0x0D,0x18,0x0B,0xF6
	.byte	0x0B,0x20,0x09,0xF4,0x05,0x11,0xFC,0xEB
	.byte	0xDD,0xE7,0xF8,0x06,0x15,0x12,0xFA,0x03
	.byte	0x20,0x12,0xF7,0xFD,0x13,0x03,0xEF,0xDF
	.byte	0xE2,0xF4,0xFF,0x10,0x16,0x00,0xFA,0x1B
	.byte	0x1B,0x00,0xF6,0x0E,0x0B,0xF4,0xE3,0xDE
	.byte	0xEF,0xFA,0x09,0x17,0x09,0xF7,0x12,0x1F
	.byte	0x0B,0xF7,0x06,0x12,0xFA,0xE7,0xDC,0xEB
	.byte	0xF7,0x01,0x12,0x12,0xF9,0x09,0x1F,0x13
	.byte	0xFE,0xFD,0x13,0x03,0xEB,0xDC,0xE4,0xF4
	.byte	0xFD,0x0B,0x16,0xFF,0x00,0x1D,0x18,0x05
	.byte	0xF8,0x0F,0x0E,0xF0,0xDF,0xDE,0xF0,0xFA
	.byte	0x05,0x16,0x09,0xFC,0x16,0x19,0x0E,0xFA
	.byte	0x07,0x14,0xF8,0xE2,0xDA,0xEA,0xF7,0x00
	.byte	0x11,0x11,0xFE,0x0F,0x19,0x13,0x02,0xFD
	.byte	0x16,0x02,0xE7,0xDA,0xE4,0xF3,0xFC,0x0C
	.byte	0x15,0x02,0x09,0x17,0x15,0x0A,0xF9,0x13
	.byte	0x0C,0xED,0xDC,0xDE,0xF0,0xF8,0x06,0x13
	.byte	0x07,0x05,0x16,0x16,0x11,0xFB,0x0B,0x15
	.byte	0xF5,0xDF,0xD9,0xEA,0xF4,0x00,0x13,0x0D
	.byte	0x04,0x13,0x16,0x16,0xFF,0x02,0x18,0xFD
	.byte	0xE4,0xD7,0xE4,0xF3,0xFB,0x0E,0x10,0x05
	.byte	0x10,0x15,0x18,0x07,0xFD,0x16,0x06,0xE9
	.byte	0xD9,0xDE,0xF1,0xF8,0x08,0x13,0x07,0x0E
	.byte	0x13,0x17,0x0E,0xFB,0x11,0x0E,0xF1,0xDD
	.byte	0xD9,0xEB,0xF6,0x02,0x14,0x09,0x09,0x11
	.byte	0x14,0x13,0xFE,0x0D,0x14,0xF8,0xE1,0xD8
	.byte	0xE5,0xF5,0xFC,0x11,0x0C,0x07,0x11,0x10
	.byte	0x18,0x02,0x08,0x16,0x01,0xE8,0xDA,0xE0
	.byte	0xF0,0xFA,0x0C,0x10,0x05,0x0F,0x0E,0x17
	.byte	0x07,0x03,0x17,0x09,0xEF,0xDB,0xDB,0xEA
	.byte	0xF8,0x06,0x14,0x06,0x0C,0x0E,0x13,0x0C
	.byte	0xFE,0x17,0x10,0xF6,0xDF,0xDC,0xE4,0xF5
	.byte	0x02,0x13,0x0B,0x08,0x0E,0x10,0x10,0xFD
	.byte	0x10,0x16,0xFF,0xE6,0xE0,0xE4,0xF1,0x00
	.byte	0x0D,0x0F,0x05,0x0A,0x0C,0x0D,0xFF,0x07
	.byte	0x14,0x05,0xEF,0xE6,0xE9,0xF0

	.byte	0x00

	.end
