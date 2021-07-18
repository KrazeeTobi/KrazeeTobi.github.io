#TONE NAME     : snd_net
#FREQUENCY     : 8000
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 001602
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	snd_net
	.align	2

snd_net:
	.short	0x0000
	.short	0x0000
	.int	16384000
	.int	0
	.int	1602

	.byte	0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00
	.byte	0x01,0x01,0x01,0x00,0x01,0x01,0x00,0x00
	.byte	0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	.byte	0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00
	.byte	0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00
	.byte	0x01,0x00,0x00,0x00,0x00,0x01,0x01,0x01
	.byte	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00
	.byte	0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00
	.byte	0x00,0x00,0x01,0x01,0x02,0x02,0x02,0x01
	.byte	0x02,0x01,0x01,0x01,0x01,0x00,0x00,0x00
	.byte	0x02,0x01,0x02,0x01,0x00,0xFE,0xFE,0xFD
	.byte	0xFF,0x02,0x05,0x07,0x07,0x06,0x03,0xFE
	.byte	0xFA,0xF9,0xFB,0x00,0x05,0x09,0x0A,0x06
	.byte	0x02,0xFB,0xF6,0xF6,0xFA,0x01,0x09,0x0C
	.byte	0x0D,0x08,0x00,0xF6,0xF2,0xF6,0x02,0x0C
	.byte	0x10,0x08,0xFC,0xED,0xE9,0xF2,0x08,0x19
	.byte	0x1C,0x13,0x00,0xE9,0xE7,0xF4,0x0B,0x10
	.byte	0x03,0xF9,0xF2,0xF6,0x0C,0x21,0x23,0x02
	.byte	0xE4,0xD4,0xE2,0x05,0x2C,0x34,0x19,0xF1
	.byte	0xC4,0xC6,0xF0,0x20,0x3C,0x2A,0xFE,0xDA
	.byte	0xE4,0xF4,0x03,0x0A,0x07,0x03,0xF5,0x02
	.byte	0x09,0x19,0xFB,0xF7,0xEB,0xE2,0xFF,0x22
	.byte	0x3D,0x0E,0xFC,0xD5,0xE1,0x08,0x0F,0x08
	.byte	0x05,0x1E,0xED,0xEB,0x0A,0x0C,0xF3,0x00
	.byte	0xFE,0xE5,0x0D,0x09,0xF2,0x22,0x21,0xF1
	.byte	0x04,0xE0,0xBF,0x2F,0x50,0x08,0xDE,0xA5
	.byte	0xCA,0x3C,0x63,0x35,0xCA,0x98,0xDD,0x56
	.byte	0x5A,0xFB,0xA8,0xA2,0x0E,0x65,0x5A,0x22
	.byte	0x98,0xBC,0x2D,0x5F,0xF4,0xB1,0xA3,0x38
	.byte	0x58,0x61,0xE5,0xA5,0x9E,0x04,0x60,0x58
	.byte	0x01,0xA6,0xA4,0xFC,0x5E,0x4F,0xDC,0xAA
	.byte	0x9E,0xE5,0x5E,0x5A,0x2B,0xB2,0x9E,0xD4
	.byte	0x56,0x62,0x12,0x9D,0xA7,0xF9,0x70,0x3B
	.byte	0xC1,0x9C,0xAB,0x05,0x70,0x1B,0x69,0x05
	.byte	0xAA,0x9B,0xD2,0x50,0x66,0xF7,0x98,0xBC
	.byte	0x40,0x68,0x27,0xA4,0xA9,0x12,0x76,0x1D
	.byte	0xB3,0x96,0xE4,0x57,0x62,0xE2,0x9F,0xA6
	.byte	0x1F,0x68,0x4E,0xCE,0x98,0xB9,0x37,0x6D
	.byte	0x20,0xA6,0xA8,0x1F,0x71,0x1F,0xAF,0x9C
	.byte	0xE8,0x58,0x60,0xFA,0x98,0xB6,0x32,0x68
	.byte	0xD8,0x9A,0xF0,0x6C,0xFE,0x9D,0xD0,0x60
	.byte	0x41,0xC0,0x96,0xDC,0x54,0x63,0xF9,0x9B
	.byte	0xB0,0x2A,0x6E,0x06,0x97,0xF3,0x65,0xDC
	.byte	0x96,0xE0,0x5A,0x5D,0xEB,0x96,0xB4,0x1F
	.byte	0x75,0x1E,0xB0,0x9D,0x24,0x62,0x51,0xD1
	.byte	0x9A,0xCC,0x59,0x40,0xBB,0xCE,0x4B,0xF4
	.byte	0xE7,0xB7,0x20,0x1C,0xF5,0xD6,0x20,0x53
	.byte	0xDD,0x9A,0x21,0x09,0x20,0xC9,0xC3,0x4F
	.byte	0x62,0x14,0x9C,0xAF,0x21,0x6B,0x46,0xCD
	.byte	0x93,0xF1,0x67,0x2B,0xAA,0xB9,0x38,0x30
	.byte	0x9B,0xBC,0x34,0x6D,0xFC,0xA6,0xA8,0x2D
	.byte	0x68,0x3B,0xB8,0x9C,0xDB,0x60,0x4E,0xEC
	.byte	0x91,0xE1,0x4F,0x5E,0xE5,0xA3,0xA5,0xD9
	.byte	0x4C,0x4F,0x4D,0xCB,0x9A,0xC2,0x3D,0x69
	.byte	0x21,0xAD,0x9F,0xC3,0x48,0x68,0x15,0xA0
	.byte	0xA5,0xFE,0x71,0x35,0xC3,0x93,0xE8,0x53
	.byte	0x61,0xE8,0x9F,0xA8,0x05,0x60,0x4C,0xD4
	.byte	0x9E,0xDC,0x44,0x66,0x12,0xAB,0xA7,0x03
	.byte	0x5B,0x44,0xC2,0xB3,0xDF,0x39,0x69,0x24
	.byte	0xAE,0x9F,0xD7,0x54,0x5E,0x41,0xB6,0xA2
	.byte	0xB5,0x41,0x63,0x40,0xB8,0xA0,0xBA,0x47
	.byte	0x61,0x42,0xB2,0xA7,0xA3,0x1A,0x66,0x46
	.byte	0xE2,0x9A,0xBF,0x0A,0xFC,0xA5,0x03,0x5F
	.byte	0x51,0x05,0xAB,0xA1,0xDB,0x53,0x5C,0x43
	.byte	0xEF,0xA5,0xA9,0xA3,0x08,0x5E,0x5D,0x15
	.byte	0xA1,0xA9,0xB2,0x3F,0x60,0x3B,0xCE,0xC1
	.byte	0x14,0x18,0xD1,0xAC,0xD9,0x54,0x56,0x58
	.byte	0xD4,0xA2,0xAD,0x29,0x62,0x42,0xD6,0xA3
	.byte	0xB0,0x20,0x5B,0x39,0xD6,0xC4,0x0D,0x29
	.byte	0xD5,0xE2,0x32,0x2E,0x28,0xED,0xB8,0xBC
	.byte	0xF8,0x1D,0x59,0x41,0x14,0xDB,0xAC,0xB6
	.byte	0xDD,0x46,0x5A,0x23,0xF6,0xE4,0xEF,0x07
	.byte	0xF9,0xC1,0xD9,0x2E,0x56,0x52,0x08,0xBB
	.byte	0xA9,0xDA,0x02,0x32,0x45,0x4A,0x15,0xD0
	.byte	0xC7,0x04,0x01,0xE3,0xDA,0xFC,0x32,0x44
	.byte	0x3D,0x1D,0xE2,0xBF,0xA6,0xCC,0x26,0x5D
	.byte	0x4A,0x2A,0xF5,0xC0,0xBB,0xC9,0xEA,0x2B
	.byte	0x52,0x4E,0x10,0xE4,0xD3,0xF8,0xFC,0xE0
	.byte	0xEC,0xF6,0x0B,0x47,0x53,0x1C,0xCB,0xAB
	.byte	0xD2,0x24,0x3F,0x16,0xE3,0xF8,0x0D,0x17
	.byte	0x01,0xDC,0xE8,0x07,0x39,0x3C,0x03,0xCC
	.byte	0xC3,0xDB,0x11,0x30,0x32,0x1E,0x01,0xE4
	.byte	0xD3,0xD3,0xFE,0x2A,0x3A,0x1A,0xD0,0xC9
	.byte	0x0B,0x3B,0x3E,0xF0,0xB4,0xD1,0x08,0x22
	.byte	0x0D,0xFA,0xFF,0x0B,0x13,0x11,0x03,0xFB
	.byte	0xFB,0x09,0x01,0xEB,0xDA,0xE8,0x10,0x31
	.byte	0x29,0x02,0xEB,0xE8,0xFB,0x03,0x02,0xFF
	.byte	0xFD,0x06,0xFB,0x07,0x1E,0x24,0x0A,0xE3
	.byte	0xE4,0xF3,0x05,0x07,0x03,0x09,0x0D,0x02
	.byte	0xF8,0xED,0x05,0x14,0x05,0x08,0xFA,0x02
	.byte	0x09,0xFF,0xF6,0xFF,0x0B,0x01,0x03,0x0A
	.byte	0x0B,0x03,0xFB,0xF0,0x02,0x16,0x0F,0x02
	.byte	0xF1,0xFB,0x07,0x06,0x0C,0x00,0xFB,0xFF
	.byte	0xFD,0x0C,0x0F,0xFF,0xEA,0xEA,0x05,0x23
	.byte	0x22,0x0E,0xF7,0xF0,0x01,0x07,0x08,0x00
	.byte	0xF0,0xFF,0x09,0x13,0x17,0xFF,0xF0,0xEE
	.byte	0x0B,0x1F,0x0F,0xF8,0xEB,0x01,0x17,0x18
	.byte	0xFE,0xEC,0xF8,0x0E,0x18,0x0A,0xED,0xED
	.byte	0x07,0x14,0x14,0x09,0xFB,0xFB,0x00,0x05
	.byte	0x03,0x03,0x04,0x04,0x09,0x12,0x12,0x01
	.byte	0xF0,0xF3,0x04,0x10,0x0A,0x02,0x04,0x0C
	.byte	0x06,0xFB,0xF3,0x07,0x0F,0xFF,0xFA,0xFE
	.byte	0x0F,0x13,0xFD,0xF2,0xFE,0x16,0x18,0xFF
	.byte	0xEC,0xF2,0x02,0x13,0x14,0x00,0xF4,0xF9
	.byte	0x07,0x0D,0x05,0xFC,0xF8,0x02,0x0A,0x07
	.byte	0xFA,0xF5,0x05,0x14,0x0A,0xF8,0xEE,0xFD
	.byte	0x12,0x0E,0xFE,0xF8,0xF5,0xFA,0x09,0x14
	.byte	0x15,0x05,0xEB,0xE5,0xFD,0x17,0x18,0xF9
	.byte	0xE5,0x00,0x14,0x0D,0xF6,0xEF,0xFC,0x0B
	.byte	0x0A,0x00,0x01,0x00,0xFF,0xFE,0xF9,0xFA
	.byte	0x00,0x01,0x04,0x03,0x02,0x00,0xFB,0xFF
	.byte	0xFE,0x02,0xFF,0x02,0x04,0x00,0xF8,0xF6
	.byte	0x01,0x05,0x06,0x01,0xFD,0xFD,0xFC,0x02
	.byte	0x04,0xFB,0xFA,0xFC,0x03,0x03,0x01,0xFE
	.byte	0xF8,0xFD,0xFE,0x01,0x03,0xFE,0xF8,0xFA
	.byte	0x02,0x08,0x08,0xF9,0xF4,0xF9,0xFE,0x06
	.byte	0x02,0x04,0xFE,0xFB,0xFD,0xFE,0x00,0xFE
	.byte	0xFF,0x00,0xFE,0xFF,0xFF,0xFF,0x00,0x00
	.byte	0xFA,0xFC,0xFA,0x00,0x02,0x03,0x05,0x03
	.byte	0xFA,0xF1,0xF5,0x05,0x0E,0x08,0xF9,0xF1
	.byte	0xFB,0x03,0x06,0x03,0xF6,0xFC,0x01,0x01
	.byte	0xFF,0xFA,0x02,0x07,0x00,0xF6,0xF6,0x00
	.byte	0x0A,0x07,0xFF,0xF8,0xF5,0xFB,0x03,0x02
	.byte	0x00,0x02,0x01,0x00,0xF8,0xFB,0xFD,0x05
	.byte	0x07,0x03,0xFB,0xF7,0xFD,0x05,0x08,0x00
	.byte	0xF9,0xF9,0x04,0x0A,0x06,0xFD,0xF7,0xF9
	.byte	0x01,0x07,0x06,0x02,0xFF,0xFC,0xFD,0x00
	.byte	0x04,0x05,0x02,0xFD,0xFD,0x00,0x04,0x03
	.byte	0x01,0xFD,0xFC,0x00,0x05,0x07,0x03,0xFF
	.byte	0xFC,0xFF,0x04,0x02,0x00,0xFE,0x03,0x08
	.byte	0x08,0xFF,0xF8,0xF9,0x04,0x0B,0x08,0xFF
	.byte	0xFB,0xFF,0x02,0x04,0x03,0x06,0x05,0xFF
	.byte	0xFB,0xFF,0x03,0x07,0x07,0x04,0x00,0xFB
	.byte	0x00,0x04,0x04,0x02,0x00,0x00,0x01,0x02
	.byte	0x04,0x05,0x02,0x00,0xFF,0x00,0x05,0x06
	.byte	0x03,0xFF,0xFE,0x04,0x08,0x01,0xFD,0x00
	.byte	0x04,0x06,0x04,0xFE,0xFE,0x03,0x08,0x06
	.byte	0x01,0xFC,0xFF,0x02,0x03,0x04,0x04,0x03
	.byte	0x01,0x02,0x00,0x01,0x03,0x04,0x03,0x02
	.byte	0x01,0xFF,0x02,0x06,0x05,0x01,0xFD,0xFF
	.byte	0x04,0x07,0x04,0xFF,0x01,0x04,0x04,0x01
	.byte	0x00,0x01,0x04,0x07,0x04,0xFE,0xFD,0x01
	.byte	0x06,0x06,0x02,0x00,0x00,0x03,0x05,0x04
	.byte	0x00,0xFF,0x04,0x06,0x04,0x00,0x00,0x03
	.byte	0x05,0x02,0x01,0x01,0x04,0x07,0x04,0x01
	.byte	0xFF,0x00,0x00,0x02,0x05,0x06,0x05,0x00
	.byte	0xFF,0x02,0x04,0x04,0x00,0xFF,0x01,0x03
	.byte	0x04,0x02,0x00,0x00,0x03,0x04,0x05,0x04
	.byte	0x01,0xFF,0x03,0x04,0x02,0x00,0x00,0x02
	.byte	0x06,0x04,0x02,0xFE,0xFF,0x01,0x05,0x05
	.byte	0x01,0xFF,0x02,0x03,0x03,0x01,0x00,0x02
	.byte	0x03,0x03,0x01,0x01,0x01,0x02,0x03,0x02
	.byte	0x02,0x01,0x00,0x01,0x02,0x02,0x00,0x02
	.byte	0x04,0x04,0x00,0xFF,0x00,0x03,0x06,0x03
	.byte	0xFF,0xFF,0x02,0x05,0x03,0x01,0xFF,0x00
	.byte	0x02,0x02,0x03,0x03,0x01,0x00,0x01,0x01
	.byte	0x01,0x02,0x01,0x03,0x02,0x02,0x01,0x01
	.byte	0x00,0x01,0x01,0x02,0x01,0x01,0x01,0x02
	.byte	0x02,0x01,0x00,0x00,0x01,0x02,0x02,0x01
	.byte	0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x01
	.byte	0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x02
	.byte	0x01,0xFF,0x00,0x01,0x02,0x02,0x01,0x01
	.byte	0x00,0x01,0x01,0x02,0x02,0x01,0x00,0x00
	.byte	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
	.byte	0x01,0x01,0x00,0x00,0x00,0x01,0x02,0x00
	.byte	0x02,0x01,0x01,0x01,0x00,0x00,0x00,0x02
	.byte	0x02,0x01,0x00,0xFF,0x01,0x02,0x02,0xFF
	.byte	0x00,0x02,0x04,0x02,0x00,0xFE,0xFF,0x01
	.byte	0x03,0x02,0x00,0x00,0x00,0x00,0x01,0x01
	.byte	0x01,0x01,0x00,0x00,0x00,0x01,0x00,0x00
	.byte	0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01
	.byte	0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01
	.byte	0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00
	.byte	0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00
	.byte	0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01
	.byte	0x01,0x01,0x01,0x00,0xFF,0xFF,0x01,0x01
	.byte	0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00
	.byte	0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x00
	.byte	0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01
	.byte	0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x01
	.byte	0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01
	.byte	0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x01
	.byte	0x01,0x00,0x00,0x00,0x00,0x01,0x01,0x00
	.byte	0x00,0x00,0x01,0x01,0x00,0x00,0x01,0x01
	.byte	0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x00
	.byte	0x00,0x00,0x01,0x01,0x00,0x00,0xFF,0x00
	.byte	0x01,0x01,0x01,0x00,0x00,0x01,0x00,0x00
	.byte	0x00,0x01,0x01,0x00,0xFF,0x00,0x00,0x01
	.byte	0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x01
	.byte	0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x00
	.byte	0xFF,0x00,0x01,0x01,0x01,0x00,0x00,0x00
	.byte	0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x00
	.byte	0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00
	.byte	0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00
	.byte	0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x01
	.byte	0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x00
	.byte	0x00,0x00,0x01,0x01,0x00,0x01,0x01,0x00
	.byte	0x00,0x01,0x01,0x01,0x00,0x00,0x01,0x01
	.byte	0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x01
	.byte	0x01,0x00,0x00,0x01,0x01,0x01,0x01,0x00
	.byte	0x00,0x00

	.byte	0x00

	.end
