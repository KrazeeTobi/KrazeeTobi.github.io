#TONE NAME     : sk
#FREQUENCY     : 11025
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 001795
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	sk
	.align	2

sk:
	.short	0x0000
	.short	0x0000
	.int	22579200
	.int	0
	.int	1795

	.byte	0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01
	.byte	0x02,0x02,0x02,0x02,0x02,0x02,0x01,0x01
	.byte	0x00,0xFF,0xFF,0xFE,0xFD,0xFD,0xFC,0xFC
	.byte	0xFC,0xFD,0xFD,0xFE,0xFF,0x00,0x01,0x03
	.byte	0x04,0x05,0x06,0x07,0x07,0x07,0x07,0x07
	.byte	0x06,0x05,0x03,0x02,0x00,0xFE,0xFD,0xFB
	.byte	0xFA,0xF8,0xF7,0xF7,0xF7,0xF7,0xF8,0xF9
	.byte	0xFB,0xFE,0x00,0x04,0x06,0x09,0x0B,0x0D
	.byte	0x0F,0x10,0x10,0x0F,0x0F,0x0D,0x0B,0x08
	.byte	0x05,0x02,0xFE,0xFB,0xF7,0xF4,0xF2,0xEF
	.byte	0xEE,0xED,0xEE,0xEF,0xF1,0xF4,0xF8,0xFC
	.byte	0x00,0x04,0x09,0x0D,0x10,0x13,0x14,0x15
	.byte	0x15,0x14,0x12,0x10,0x0D,0x09,0x05,0x00
	.byte	0xFB,0xF7,0xF2,0xEF,0xED,0xEC,0xEC,0xED
	.byte	0xEF,0xF2,0xF6,0xFB,0xFF,0x04,0x08,0x0C
	.byte	0x10,0x13,0x15,0x16,0x16,0x15,0x13,0x10
	.byte	0x0B,0x06,0x01,0xFB,0xF7,0xF2,0xEF,0xEC
	.byte	0xEB,0xEB,0xEC,0xF0,0xF4,0xF9,0xFF,0x04
	.byte	0x0A,0x0E,0x11,0x14,0x16,0x16,0x15,0x14
	.byte	0x11,0x0E,0x08,0x03,0xFD,0xF8,0xF3,0xEF
	.byte	0xEC,0xEB,0xEB,0xED,0xF1,0xF5,0xFB,0x00
	.byte	0x05,0x09,0x0D,0x11,0x12,0x14,0x14,0x12
	.byte	0x0F,0x0B,0x06,0x01,0xFC,0xF8,0xF3,0xF0
	.byte	0xED,0xED,0xED,0xEF,0xF2,0xF7,0xFD,0x03
	.byte	0x09,0x0F,0x14,0x17,0x19,0x19,0x18,0x15
	.byte	0x12,0x0D,0x08,0x02,0xFB,0xF5,0xEF,0xEA
	.byte	0xE6,0xE4,0xE4,0xE5,0xE9,0xEF,0xF6,0xFE
	.byte	0x06,0x0E,0x15,0x1A,0x1E,0x20,0x20,0x1E
	.byte	0x1B,0x16,0x10,0x09,0x00,0xF9,0xF1,0xEA
	.byte	0xE5,0xE1,0xDF,0xDF,0xE1,0xE5,0xEC,0xF4
	.byte	0xFD,0x06,0x0F,0x17,0x1D,0x21,0x23,0x23
	.byte	0x21,0x1E,0x18,0x12,0x0A,0x02,0xFA,0xF2
	.byte	0xEA,0xE4,0xE0,0xDE,0xDF,0xE2,0xE8,0xEF
	.byte	0xF8,0x01,0x0A,0x12,0x18,0x1D,0x20,0x21
	.byte	0x20,0x1C,0x17,0x11,0x09,0x02,0xFA,0xF2
	.byte	0xEB,0xE5,0xE1,0xDE,0xDF,0xE2,0xE7,0xEF
	.byte	0xF9,0x03,0x0C,0x14,0x1A,0x1F,0x21,0x22
	.byte	0x20,0x1C,0x17,0x0F,0x07,0xFF,0xF7,0xEF
	.byte	0xE9,0xE5,0xE2,0xE2,0xE4,0xE8,0xEE,0xF4
	.byte	0xFC,0x05,0x0D,0x14,0x19,0x1C,0x1D,0x1C
	.byte	0x19,0x15,0x0F,0x09,0x01,0xFA,0xF3,0xEE
	.byte	0xEB,0xE9,0xE8,0xEA,0xED,0xF2,0xF9,0xFF
	.byte	0x05,0x0A,0x0E,0x11,0x14,0x15,0x14,0x12
	.byte	0x0E,0x09,0x05,0x01,0xFC,0xF8,0xF4,0xF1
	.byte	0xF0,0xF1,0xF3,0xF7,0xFB,0xFF,0x03,0x08
	.byte	0x0A,0x0C,0x0D,0x0D,0x0B,0x09,0x05,0x02
	.byte	0xFE,0xF9,0xF6,0xF4,0xF3,0xF3,0xF5,0xF7
	.byte	0xFB,0xFF,0x04,0x09,0x0F,0x12,0x14,0x15
	.byte	0x13,0x11,0x0C,0x06,0xFF,0xF9,0xF3,0xEF
	.byte	0xEC,0xEA,0xEA,0xEC,0xF0,0xF5,0xFB,0x02
	.byte	0x09,0x10,0x16,0x1B,0x1E,0x1E,0x1B,0x17
	.byte	0x10,0x08,0xFE,0xF5,0xEC,0xE4,0xE0,0xDE
	.byte	0xDF,0xE2,0xE8,0xF0,0xF9,0x02,0x0C,0x15
	.byte	0x1D,0x23,0x26,0x27,0x25,0x1F,0x17,0x0E
	.byte	0x02,0xF7,0xEB,0xE1,0xD9,0xD6,0xD5,0xD9
	.byte	0xE0,0xE9,0xF3,0xFE,0x0A,0x16,0x20,0x28
	.byte	0x2D,0x2E,0x2D,0x27,0x1E,0x13,0x06,0xF9
	.byte	0xEB,0xDE,0xD5,0xCF,0xCC,0xCF,0xD6,0xE0
	.byte	0xEC,0xFA,0x07,0x15,0x22,0x2C,0x33,0x36
	.byte	0x34,0x2F,0x26,0x1B,0x0D,0xFE,0xEE,0xDF
	.byte	0xD3,0xCB,0xC8,0xC9,0xCF,0xD9,0xE5,0xF3
	.byte	0x02,0x12,0x20,0x2C,0x34,0x38,0x38,0x33
	.byte	0x2B,0x1F,0x11,0x01,0xF1,0xE3,0xD6,0xCD
	.byte	0xC9,0xC9,0xCD,0xD5,0xE0,0xED,0xFD,0x0C
	.byte	0x1A,0x27,0x2F,0x34,0x34,0x31,0x2B,0x21
	.byte	0x15,0x07,0xF8,0xEA,0xDF,0xD8,0xD4,0xD3
	.byte	0xD6,0xDB,0xE3,0xEE,0xFA,0x07,0x13,0x1D
	.byte	0x24,0x27,0x27,0x24,0x1F,0x17,0x0D,0x03
	.byte	0xF8,0xEF,0xE8,0xE5,0xE3,0xE3,0xE5,0xEA
	.byte	0xF1,0xF8,0x00,0x09,0x0F,0x15,0x17,0x18
	.byte	0x16,0x13,0x0D,0x07,0xFF,0xF9,0xF4,0xF2
	.byte	0xF1,0xF1,0xF3,0xF5,0xF9,0xFD,0x02,0x06
	.byte	0x09,0x0C,0x0D,0x0D,0x0B,0x08,0x05,0xFF
	.byte	0xFB,0xF6,0xF4,0xF3,0xF5,0xF7,0xFC,0xFF
	.byte	0x04,0x08,0x0C,0x0E,0x0F,0x0F,0x0C,0x08
	.byte	0x04,0xFE,0xF9,0xF3,0xEF,0xEC,0xEA,0xEB
	.byte	0xF0,0xF5,0xFC,0x03,0x0A,0x10,0x16,0x19
	.byte	0x1B,0x19,0x15,0x0F,0x08,0xFF,0xF7,0xEF
	.byte	0xE7,0xE2,0xDF,0xE0,0xE6,0xEE,0xF7,0x01
	.byte	0x0C,0x15,0x1E,0x24,0x26,0x24,0x1F,0x17
	.byte	0x0E,0x02,0xF7,0xEB,0xDF,0xD7,0xD1,0xD1
	.byte	0xD6,0xDF,0xEA,0xF8,0x06,0x16,0x24,0x30
	.byte	0x38,0x3A,0x36,0x2D,0x22,0x13,0x04,0xF2
	.byte	0xE1,0xD2,0xC7,0xC1,0xC2,0xC7,0xD0,0xDD
	.byte	0xED,0xFF,0x13,0x26,0x36,0x40,0x44,0x42
	.byte	0x3C,0x30,0x20,0x0D,0xF8,0xE4,0xD2,0xC6
	.byte	0xC0,0xBF,0xC2,0xC9,0xD4,0xE4,0xF7,0x0C
	.byte	0x20,0x30,0x3B,0x41,0x42,0x3E,0x34,0x25
	.byte	0x13,0xFF,0xEB,0xDC,0xD1,0xCB,0xC7,0xC8
	.byte	0xCC,0xD5,0xE3,0xF4,0x06,0x16,0x23,0x2C
	.byte	0x32,0x34,0x30,0x29,0x1D,0x10,0x02,0xF6
	.byte	0xEC,0xE6,0xE0,0xDC,0xDB,0xDD,0xE3,0xEB
	.byte	0xF6,0x00,0x09,0x11,0x17,0x1A,0x1B,0x19
	.byte	0x13,0x0D,0x05,0x00,0xFC,0xF9,0xF7,0xF4
	.byte	0xF3,0xF3,0xF5,0xF8,0xFD,0x02,0x05,0x07
	.byte	0x09,0x0A,0x09,0x06,0x02,0xFF,0xFB,0xF9
	.byte	0xF8,0xF9,0xFA,0xFA,0xFA,0xFB,0xFD,0x01
	.byte	0x04,0x08,0x0A,0x0B,0x0C,0x0B,0x08,0x04
	.byte	0xFF,0xFA,0xF6,0xF3,0xF3,0xF4,0xF6,0xF8
	.byte	0xFA,0xFC,0xFF,0x02,0x06,0x09,0x0C,0x0D
	.byte	0x0E,0x0E,0x0B,0x08,0x03,0xFE,0xF9,0xF6
	.byte	0xF4,0xF4,0xF4,0xF5,0xF6,0xF8,0xFA,0xFE
	.byte	0x01,0x04,0x07,0x09,0x0B,0x0B,0x0B,0x09
	.byte	0x06,0x02,0xFE,0xFB,0xF9,0xF9,0xF9,0xF9
	.byte	0xF9,0xFA,0xFB,0xFE,0x00,0x02,0x04,0x05
	.byte	0x06,0x07,0x06,0x04,0x02,0xFF,0xFC,0xFA
	.byte	0xF9,0xF9,0xF9,0xFA,0xFB,0xFC,0xFD,0x00
	.byte	0x02,0x05,0x07,0x08,0x09,0x0A,0x09,0x08
	.byte	0x05,0x02,0xFF,0xFC,0xFA,0xF9,0xF8,0xF7
	.byte	0xF7,0xF7,0xF8,0xF9,0xFB,0xFE,0x00,0x02
	.byte	0x04,0x06,0x07,0x08,0x08,0x07,0x06,0x04
	.byte	0x03,0x01,0x00,0xFE,0xFC,0xFA,0xF9,0xF9
	.byte	0xF9,0xFA,0xFB,0xFC,0xFD,0xFF,0x01,0x03
	.byte	0x04,0x05,0x06,0x06,0x07,0x06,0x06,0x04
	.byte	0x02,0xFF,0xFD,0xFB,0xF9,0xF8,0xF8,0xF8
	.byte	0xF9,0xFB,0xFD,0xFF,0x01,0x03,0x05,0x07
	.byte	0x09,0x0A,0x0B,0x09,0x07,0x04,0x00,0xFD
	.byte	0xFA,0xF7,0xF5,0xF4,0xF3,0xF3,0xF5,0xF7
	.byte	0xFA,0xFD,0x00,0x04,0x08,0x0B,0x0E,0x0F
	.byte	0x10,0x0E,0x0C,0x08,0x05,0x01,0xFD,0xF9
	.byte	0xF6,0xF3,0xF2,0xF1,0xF1,0xF2,0xF4,0xF8
	.byte	0xFB,0xFF,0x04,0x07,0x09,0x0B,0x0C,0x0C
	.byte	0x0C,0x0B,0x09,0x07,0x05,0x02,0x00,0xFD
	.byte	0xFB,0xF9,0xF7,0xF6,0xF7,0xF7,0xF9,0xF9
	.byte	0xFA,0xFB,0xFC,0xFD,0xFE,0x00,0x01,0x03
	.byte	0x04,0x06,0x08,0x09,0x09,0x09,0x09,0x08
	.byte	0x07,0x05,0x03,0x01,0xFE,0xFB,0xF8,0xF6
	.byte	0xF4,0xF3,0xF3,0xF4,0xF6,0xF8,0xFC,0x00
	.byte	0x04,0x08,0x0B,0x0D,0x0F,0x0F,0x0E,0x0C
	.byte	0x08,0x04,0xFF,0xFB,0xF6,0xF3,0xF0,0xEF
	.byte	0xF0,0xF1,0xF4,0xF9,0xFE,0x03,0x08,0x0D
	.byte	0x11,0x14,0x14,0x13,0x10,0x0C,0x06,0x00
	.byte	0xFA,0xF4,0xEF,0xEC,0xE9,0xE9,0xEB,0xEF
	.byte	0xF4,0xF9,0xFF,0x06,0x0D,0x12,0x16,0x17
	.byte	0x17,0x14,0x10,0x0B,0x06,0xFF,0xF9,0xF4
	.byte	0xEF,0xEC,0xEB,0xEC,0xEE,0xF2,0xF7,0xFC
	.byte	0x02,0x07,0x0C,0x0F,0x10,0x10,0x0F,0x0D
	.byte	0x0A,0x06,0x01,0xFC,0xF8,0xF5,0xF3,0xF3
	.byte	0xF4,0xF6,0xF9,0xFD,0x00,0x04,0x07,0x08
	.byte	0x09,0x09,0x09,0x07,0x05,0x03,0x00,0xFC
	.byte	0xF9,0xF7,0xF6,0xF6,0xF7,0xF9,0xFB,0xFF
	.byte	0x02,0x05,0x08,0x0A,0x0A,0x0A,0x08,0x06
	.byte	0x04,0x01,0xFF,0xFC,0xF9,0xF8,0xF7,0xF8
	.byte	0xF9,0xFB,0xFD,0x00,0x02,0x04,0x06,0x07
	.byte	0x08,0x07,0x05,0x03,0x00,0xFD,0xFB,0xF8
	.byte	0xF7,0xF6,0xF7,0xF9,0xFC,0x00,0x03,0x07
	.byte	0x0A,0x0C,0x0E,0x0E,0x0D,0x0B,0x08,0x04
	.byte	0xFF,0xFB,0xF6,0xF2,0xF0,0xEE,0xEF,0xF1
	.byte	0xF4,0xF9,0xFE,0x03,0x09,0x0D,0x11,0x13
	.byte	0x13,0x12,0x0E,0x0A,0x05,0xFF,0xFA,0xF5
	.byte	0xF1,0xEE,0xED,0xEE,0xF1,0xF5,0xFA,0x00
	.byte	0x06,0x0C,0x11,0x14,0x16,0x15,0x13,0x0E
	.byte	0x09,0x02,0xFC,0xF5,0xEF,0xEA,0xE8,0xE7
	.byte	0xE9,0xED,0xF2,0xF9,0x00,0x08,0x0F,0x16
	.byte	0x1B,0x1E,0x1D,0x1B,0x16,0x0F,0x07,0xFF
	.byte	0xF6,0xEE,0xE7,0xE3,0xE1,0xE2,0xE5,0xEA
	.byte	0xF0,0xF9,0x01,0x0B,0x14,0x1A,0x1F,0x21
	.byte	0x21,0x1E,0x18,0x11,0x07,0xFD,0xF4,0xEB
	.byte	0xE5,0xE1,0xDF,0xE1,0xE4,0xEB,0xF2,0xFB
	.byte	0x05,0x0E,0x16,0x1C,0x20,0x21,0x1F,0x1B
	.byte	0x15,0x0C,0x03,0xFA,0xF1,0xEA,0xE4,0xE1
	.byte	0xE1,0xE3,0xE8,0xEE,0xF7,0xFF,0x08,0x10
	.byte	0x17,0x1C,0x1F,0x1F,0x1C,0x17,0x11,0x09
	.byte	0x00,0xF8,0xF0,0xEA,0xE6,0xE4,0xE5,0xE8
	.byte	0xED,0xF4,0xFB,0x02,0x0A,0x10,0x15,0x18
	.byte	0x1A,0x18,0x15,0x10,0x0A,0x04,0xFE,0xF7
	.byte	0xF2,0xEE,0xEB,0xEB,0xED,0xEF,0xF3,0xF8
	.byte	0xFE,0x04,0x09,0x0E,0x11,0x12,0x12,0x10
	.byte	0x0E,0x0A,0x06,0x01,0xFC,0xF8,0xF6,0xF4
	.byte	0xF4,0xF4,0xF5,0xF7,0xFA,0xFD,0x01,0x04
	.byte	0x07,0x09,0x0A,0x0A,0x09,0x08,0x06,0x03
	.byte	0x01,0xFE,0xFD,0xFC,0xFC,0xFC,0xFD,0xFE
	.byte	0xFE,0xFF,0x00,0x01,0x02,0x02,0x02,0x01
	.byte	0x01,0x00,0xFF,0xFE,0xFD,0xFC,0xFD,0xFE
	.byte	0xFF,0x01,0x03,0x05,0x06,0x08,0x08,0x08
	.byte	0x07,0x05,0x03,0x01,0xFE,0xFC,0xFA,0xF8
	.byte	0xF6,0xF6,0xF6,0xF8,0xFA,0xFD,0x00,0x04
	.byte	0x07,0x0A,0x0C,0x0D,0x0D,0x0C,0x0A,0x07
	.byte	0x04,0x00,0xFD,0xF9,0xF6,0xF4,0xF3,0xF4
	.byte	0xF5,0xF7,0xFA,0xFE,0x02,0x05,0x08,0x0A
	.byte	0x0C,0x0C,0x0B,0x09,0x07,0x04,0x01,0xFE
	.byte	0xFB,0xF9,0xF8,0xF7,0xF7,0xF8,0xFA,0xFC
	.byte	0xFF,0x03,0x05,0x07,0x09,0x09,0x09,0x07
	.byte	0x06,0x03,0x01,0xFE,0xFC,0xFA,0xF9,0xF9
	.byte	0xF9,0xF9,0xFB,0xFD,0x00,0x02,0x05,0x07
	.byte	0x09,0x09,0x09,0x08,0x06,0x03,0x01,0xFE
	.byte	0xFC,0xFA,0xF9,0xF9,0xF9,0xFA,0xFB,0xFD
	.byte	0x00,0x02,0x05,0x07,0x09,0x09,0x09,0x09
	.byte	0x07,0x05,0x02,0xFF,0xFC,0xFA,0xF8,0xF7
	.byte	0xF7,0xF8,0xF9,0xFB,0xFE,0x01,0x03,0x05
	.byte	0x07,0x09,0x0A,0x0A,0x09,0x08,0x06,0x03
	.byte	0x01,0xFE,0xFC,0xFA,0xF9,0xF8,0xF8,0xF8
	.byte	0xF9,0xFB,0xFD,0xFF,0x01,0x03,0x05,0x06
	.byte	0x07,0x08,0x07,0x07,0x06,0x05,0x05,0x04
	.byte	0x03,0x01,0x00,0xFF,0xFD,0xFD,0xFC,0xFB
	.byte	0xFA,0xFA,0xFA,0xFA,0xFB,0xFD,0xFE,0xFF
	.byte	0x01,0x03,0x05,0x07,0x09,0x09,0x0A,0x0A
	.byte	0x0A,0x09,0x07,0x04,0x01,0xFE,0xFB,0xF8
	.byte	0xF7,0xF6,0xF5,0xF5,0xF6,0xF8,0xFB,0xFE
	.byte	0x02,0x05,0x08,0x0B,0x0D,0x0E,0x0E,0x0D
	.byte	0x0B,0x08,0x04,0x01,0xFD,0xF9,0xF6,0xF4
	.byte	0xF2,0xF2,0xF4,0xF6,0xF9,0xFD,0x00,0x04
	.byte	0x08,0x0B,0x0D,0x0E,0x0E,0x0D,0x0B,0x07
	.byte	0x04,0x00,0xFD,0xF9,0xF7,0xF5,0xF4,0xF5
	.byte	0xF7,0xF9,0xFB,0xFE,0x02,0x05,0x08,0x0A
	.byte	0x0B,0x0B,0x0B,0x09,0x07,0x05,0x02,0xFE
	.byte	0xFC,0xFA,0xF8,0xF8,0xF8,0xF9,0xFB,0xFD
	.byte	0xFF,0x01,0x03,0x05,0x06,0x07,0x07,0x06
	.byte	0x05,0x03,0x02,0x00,0xFE,0xFD,0xFC,0xFC
	.byte	0xFD,0xFD,0xFE,0x00,0x01,0x02,0x04,0x05
	.byte	0x05,0x05,0x05,0x04,0x02,0x01,0xFF,0xFE
	.byte	0xFC,0xFB,0xFB,0xFB,0xFC,0xFD,0xFE,0x00
	.byte	0x02,0x03,0x05,0x06,0x06,0x06,0x06,0x05
	.byte	0x04,0x02,0x00,0xFF,0xFD,0xFC,0xFB,0xFB
	.byte	0xFB,0xFC,0xFD,0xFE,0x00,0x01,0x03,0x04
	.byte	0x05,0x06,0x06,0x05,0x05,0x04,0x02,0x01
	.byte	0x00,0xFE,0xFD,0xFD,0xFC,0xFC,0xFC,0xFD
	.byte	0xFE,0xFF,0x00,0x02,0x03,0x03,0x04,0x04
	.byte	0x04,0x04,0x03,0x02,0x01,0x01,0x00,0xFF
	.byte	0xFF,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,0x00
	.byte	0x00,0x01,0x01,0x02,0x02,0x02,0x02,0x02
	.byte	0x02,0x01,0x01,0x01,0x00,0x00,0x00,0x00
	.byte	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01
	.byte	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
	.byte	0x01,0x01,0x00

	.byte	0x00

	.end
