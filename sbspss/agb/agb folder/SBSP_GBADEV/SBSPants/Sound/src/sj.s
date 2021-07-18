#TONE NAME     : sj
#FREQUENCY     : 11025
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 001560
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	sj
	.align	2

sj:
	.short	0x0000
	.short	0x0000
	.int	22579200
	.int	0
	.int	1560

	.byte	0x00,0x01,0x01,0x01,0x01,0x00,0xFF,0xFE
	.byte	0xFE,0xFF,0x01,0x03,0x04,0x04,0x03,0x01
	.byte	0xFE,0xFC,0xFB,0xFC,0xFF,0x03,0x07,0x09
	.byte	0x09,0x06,0x01,0xFC,0xF7,0xF5,0xF7,0xFD
	.byte	0x04,0x0A,0x0D,0x0C,0x08,0x01,0xFA,0xF5
	.byte	0xF5,0xF9,0x00,0x06,0x0C,0x0D,0x0B,0x04
	.byte	0xFC,0xF5,0xF4,0xF8,0x00,0x08,0x0D,0x0D
	.byte	0x09,0x02,0xF9,0xF4,0xF5,0xFB,0x04,0x0A
	.byte	0x0C,0x0A,0x03,0xFC,0xF6,0xF5,0xF9,0x02
	.byte	0x0B,0x0F,0x0E,0x08,0xFF,0xF6,0xF0,0xF1
	.byte	0xF9,0x05,0x0F,0x13,0x10,0x08,0xFD,0xF3
	.byte	0xED,0xEF,0xF9,0x06,0x11,0x15,0x12,0x0A
	.byte	0xFE,0xF3,0xED,0xEF,0xF9,0x06,0x11,0x14
	.byte	0x10,0x07,0xFC,0xF2,0xED,0xF0,0xFC,0x09
	.byte	0x12,0x14,0x0F,0x05,0xF9,0xF0,0xEF,0xF5
	.byte	0xFE,0x0A,0x11,0x11,0x0B,0x01,0xF7,0xF3
	.byte	0xF3,0xFA,0x03,0x0A,0x0D,0x0B,0x05,0xFF
	.byte	0xF9,0xF6,0xFA,0x00,0x06,0x08,0x07,0x03
	.byte	0xFD,0xF9,0xFA,0xFE,0x05,0x0B,0x0C,0x08
	.byte	0xFF,0xF7,0xF4,0xF6,0xFD,0x07,0x10,0x13
	.byte	0x0D,0x02,0xF4,0xEC,0xED,0xF7,0x05,0x12
	.byte	0x18,0x15,0x09,0xF9,0xEA,0xE6,0xEF,0xFE
	.byte	0x0F,0x1A,0x1C,0x11,0xFF,0xEC,0xE2,0xE6
	.byte	0xF6,0x0A,0x1A,0x20,0x19,0x08,0xF2,0xE2
	.byte	0xE1,0xEE,0x02,0x16,0x21,0x1D,0x0D,0xF8
	.byte	0xE6,0xE1,0xEA,0xFC,0x11,0x1E,0x1D,0x11
	.byte	0xFD,0xEB,0xE4,0xEA,0xF9,0x0C,0x1A,0x1B
	.byte	0x11,0x00,0xF0,0xEA,0xED,0xF8,0x08,0x12
	.byte	0x14,0x0D,0x00,0xF5,0xF2,0xF6,0xFE,0x06
	.byte	0x0B,0x0B,0x05,0xFC,0xF9,0xFB,0xFF,0x05
	.byte	0x07,0x04,0x00,0xFA,0xF8,0xFD,0x04,0x0A
	.byte	0x0C,0x07,0xFE,0xF5,0xF0,0xF5,0x01,0x0E
	.byte	0x16,0x12,0x06,0xF7,0xE9,0xE7,0xF3,0x05
	.byte	0x18,0x1F,0x17,0x05,0xEF,0xE0,0xE3,0xF2
	.byte	0x09,0x1E,0x24,0x19,0x02,0xE9,0xDD,0xE3
	.byte	0xF3,0x0D,0x21,0x24,0x17,0xFD,0xE6,0xDF
	.byte	0xE6,0xF8,0x11,0x21,0x21,0x10,0xF7,0xE6
	.byte	0xE3,0xEB,0xFF,0x14,0x1F,0x1A,0x07,0xF3
	.byte	0xEA,0xE9,0xF2,0x05,0x14,0x1A,0x10,0xFE
	.byte	0xF3,0xEE,0xEE,0xFA,0x0A,0x13,0x13,0x07
	.byte	0xFB,0xF6,0xF3,0xF6,0x01,0x0B,0x0F,0x09
	.byte	0xFF,0xFA,0xF9,0xF8,0xFE,0x05,0x0A,0x09
	.byte	0x00,0xFA,0xFB,0xFB,0xFF,0x04,0x07,0x08
	.byte	0x01,0xF9,0xFB,0xFE,0x00,0x06,0x08,0x07
	.byte	0x00,0xF7,0xF6,0xFC,0x01,0x07,0x0B,0x09
	.byte	0x03,0xF7,0xF2,0xF8,0xFF,0x06,0x0E,0x0E
	.byte	0x08,0xFD,0xF1,0xF2,0xF9,0x01,0x0B,0x0F
	.byte	0x0C,0x04,0xF7,0xF0,0xF6,0xFD,0x05,0x0E
	.byte	0x0E,0x08,0xFC,0xF1,0xF4,0xFB,0x02,0x0C
	.byte	0x0F,0x0B,0x00,0xF2,0xEF,0xF8,0x00,0x0A
	.byte	0x10,0x0E,0x06,0xF7,0xED,0xF3,0xFB,0x05
	.byte	0x0F,0x10,0x0B,0xFF,0xF1,0xF1,0xFA,0x01
	.byte	0x0B,0x0E,0x0A,0x02,0xF5,0xF0,0xF9,0x02
	.byte	0x0A,0x0F,0x0A,0x02,0xF5,0xED,0xF4,0x00
	.byte	0x0B,0x13,0x10,0x07,0xF9,0xEB,0xEC,0xF9
	.byte	0x06,0x13,0x16,0x0F,0x00,0xEE,0xE7,0xF1
	.byte	0xFE,0x0E,0x18,0x15,0x09,0xF6,0xE7,0xE9
	.byte	0xF6,0x05,0x14,0x18,0x11,0x01,0xEE,0xE9
	.byte	0xF0,0xFC,0x0C,0x15,0x14,0x09,0xF6,0xEC
	.byte	0xF0,0xF8,0x05,0x10,0x11,0x0B,0xFC,0xF0
	.byte	0xF2,0xF9,0x03,0x0E,0x0F,0x0A,0xFE,0xF1
	.byte	0xF1,0xF9,0x02,0x0D,0x0F,0x0B,0x00,0xF2
	.byte	0xF0,0xF8,0x01,0x0C,0x10,0x0C,0x02,0xF3
	.byte	0xEE,0xF6,0x00,0x0B,0x12,0x0D,0x04,0xF5
	.byte	0xEB,0xF2,0xFE,0x0A,0x13,0x10,0x07,0xF8
	.byte	0xEA,0xEE,0xFA,0x08,0x15,0x15,0x0D,0xFD
	.byte	0xEB,0xE8,0xF4,0x01,0x11,0x17,0x11,0x04
	.byte	0xF1,0xE9,0xF1,0xFC,0x0B,0x13,0x10,0x06
	.byte	0xF6,0xEC,0xF3,0xFD,0x09,0x12,0x0F,0x05
	.byte	0xF6,0xEB,0xF1,0xFD,0x09,0x13,0x11,0x07
	.byte	0xF9,0xEA,0xED,0xFB,0x07,0x13,0x14,0x0A
	.byte	0xFB,0xEB,0xEA,0xF8,0x06,0x14,0x18,0x0F
	.byte	0xFE,0xEB,0xE5,0xF1,0x01,0x12,0x1A,0x14
	.byte	0x05,0xF1,0xE5,0xED,0xFB,0x0B,0x17,0x14
	.byte	0x09,0xF6,0xE9,0xED,0xFA,0x08,0x14,0x14
	.byte	0x0A,0xF9,0xEA,0xEB,0xF8,0x06,0x13,0x15
	.byte	0x0E,0xFF,0xEE,0xEB,0xF4,0x00,0x0D,0x12
	.byte	0x0E,0x02,0xF3,0xEE,0xF6,0x00,0x0B,0x0E
	.byte	0x0B,0x01,0xF4,0xF0,0xF8,0x03,0x0D,0x0E
	.byte	0x08,0xFF,0xF2,0xEE,0xF8,0x05,0x11,0x12
	.byte	0x0A,0xFE,0xEE,0xE8,0xF3,0x04,0x13,0x19
	.byte	0x10,0x02,0xEF,0xE4,0xEC,0xFD,0x10,0x1B
	.byte	0x16,0x09,0xF6,0xE5,0xE7,0xF6,0x09,0x18
	.byte	0x18,0x0E,0xFC,0xE9,0xE7,0xF3,0x04,0x15
	.byte	0x18,0x0F,0x00,0xEC,0xE7,0xF2,0x02,0x12
	.byte	0x18,0x10,0x02,0xEF,0xE7,0xF0,0xFF,0x0F
	.byte	0x17,0x11,0x04,0xF2,0xE9,0xF0,0xFE,0x0D
	.byte	0x15,0x10,0x04,0xF3,0xEA,0xF1,0xFF,0x0F
	.byte	0x17,0x10,0x02,0xF1,0xE6,0xEE,0xFF,0x11
	.byte	0x1D,0x16,0x05,0xF0,0xE1,0xE7,0xFA,0x0F
	.byte	0x1F,0x1D,0x0D,0xF5,0xE1,0xE1,0xF1,0x07
	.byte	0x1C,0x1F,0x14,0xFE,0xE9,0xE3,0xEE,0x00
	.byte	0x14,0x19,0x12,0x02,0xF0,0xEA,0xF2,0x00
	.byte	0x10,0x13,0x0C,0xFD,0xEF,0xED,0xF8,0x06
	.byte	0x15,0x15,0x09,0xF7,0xE9,0xE8,0xF6,0x09
	.byte	0x1A,0x1C,0x0E,0xF8,0xE5,0xE2,0xF0,0x06
	.byte	0x1B,0x21,0x14,0xFC,0xE5,0xE0,0xEB,0x01
	.byte	0x19,0x22,0x18,0x01,0xE9,0xE0,0xE9,0xFC
	.byte	0x15,0x21,0x1A,0x06,0xED,0xE1,0xE7,0xF9
	.byte	0x10,0x1E,0x1A,0x08,0xF1,0xE4,0xE8,0xF7
	.byte	0x0E,0x1C,0x19,0x08,0xF2,0xE6,0xE9,0xF7
	.byte	0x0D,0x1B,0x19,0x08,0xF2,0xE6,0xE9,0xF7
	.byte	0x0E,0x1C,0x1A,0x09,0xF2,0xE5,0xE8,0xF5
	.byte	0x0C,0x1B,0x1B,0x0B,0xF4,0xE6,0xE8,0xF4
	.byte	0x09,0x19,0x18,0x0C,0xF7,0xEB,0xEC,0xF5
	.byte	0x08,0x16,0x15,0x09,0xF6,0xEC,0xEE,0xF8
	.byte	0x08,0x15,0x13,0x06,0xF5,0xED,0xF2,0xFD
	.byte	0x0B,0x15,0x0F,0x00,0xF0,0xEB,0xF3,0x02
	.byte	0x12,0x1A,0x11,0xFD,0xE9,0xE5,0xEF,0x00
	.byte	0x15,0x1F,0x17,0x02,0xEB,0xE4,0xEB,0xFB
	.byte	0x11,0x1D,0x18,0x04,0xEE,0xE7,0xED,0xFC
	.byte	0x10,0x1A,0x14,0x01,0xED,0xE8,0xF0,0xFF
	.byte	0x13,0x1C,0x14,0x00,0xEA,0xE5,0xEF,0x00
	.byte	0x14,0x1D,0x14,0xFF,0xEA,0xE6,0xF0,0x02
	.byte	0x16,0x1E,0x12,0xFB,0xE6,0xE3,0xF0,0x05
	.byte	0x1B,0x23,0x15,0xFA,0xE3,0xDF,0xEA,0x02
	.byte	0x1B,0x26,0x1A,0xFF,0xE6,0xDF,0xE7,0xFD
	.byte	0x17,0x23,0x1A,0x02,0xEA,0xE3,0xE9,0xFB
	.byte	0x14,0x1F,0x18,0x01,0xEB,0xE7,0xEE,0xFE
	.byte	0x14,0x1C,0x13,0xFD,0xEA,0xE9,0xF1,0x02
	.byte	0x15,0x1B,0x10,0xFB,0xEA,0xE9,0xF2,0x03
	.byte	0x15,0x1A,0x10,0xFC,0xEC,0xEA,0xF1,0x01
	.byte	0x12,0x18,0x0F,0xFF,0xF2,0xEE,0xF2,0xFE
	.byte	0x0D,0x12,0x0C,0xFF,0xF7,0xF5,0xF6,0xFF
	.byte	0x09,0x0C,0x06,0xFD,0xF8,0xF9,0xFC,0x04
	.byte	0x0A,0x09,0x01,0xF9,0xF8,0xFB,0xFF,0x05
	.byte	0x0A,0x07,0xFF,0xF7,0xF7,0xFD,0x02,0x08
	.byte	0x0A,0x06,0xFD,0xF6,0xF6,0xFC,0x03,0x09
	.byte	0x0B,0x07,0xFD,0xF5,0xF5,0xFA,0x01,0x08
	.byte	0x0A,0x08,0x01,0xF9,0xF7,0xFA,0xFF,0x05
	.byte	0x06,0x05,0x01,0xFD,0xFD,0xFE,0x01,0x04
	.byte	0x03,0x00,0xFD,0xFC,0xFD,0x01,0x03,0x05
	.byte	0x03,0xFF,0xFC,0xFB,0xFC,0x00,0x03,0x06
	.byte	0x06,0x02,0xFE,0xFB,0xF9,0xFB,0x00,0x04
	.byte	0x08,0x06,0x02,0xFD,0xF9,0xF9,0xFC,0x02
	.byte	0x06,0x08,0x05,0x00,0xFA,0xF8,0xFA,0xFF
	.byte	0x05,0x08,0x07,0x03,0xFD,0xF9,0xF8,0xFC
	.byte	0x02,0x07,0x07,0x04,0xFE,0xFA,0xF9,0xFD
	.byte	0x03,0x07,0x07,0x03,0xFD,0xF9,0xF8,0xFD
	.byte	0x04,0x09,0x09,0x05,0xFD,0xF7,0xF5,0xFA
	.byte	0x02,0x09,0x0C,0x09,0x00,0xF9,0xF5,0xF7
	.byte	0xFE,0x06,0x0A,0x09,0x03,0xFC,0xF7,0xF8
	.byte	0xFE,0x05,0x09,0x08,0x02,0xFB,0xF7,0xF6
	.byte	0xFD,0x05,0x0A,0x0B,0x05,0xFD,0xF7,0xF5
	.byte	0xFA,0x02,0x08,0x0A,0x07,0x00,0xFB,0xF9
	.byte	0xFA,0xFF,0x03,0x05,0x03,0xFF,0xFD,0xFE
	.byte	0xFF,0x02,0x04,0x03,0x00,0xFB,0xFA,0xFE
	.byte	0x02,0x07,0x07,0x04,0xFF,0xF9,0xF6,0xFB
	.byte	0x02,0x08,0x0B,0x07,0x01,0xF9,0xF4,0xF8
	.byte	0x00,0x07,0x0B,0x08,0x02,0xFA,0xF5,0xF8
	.byte	0x00,0x08,0x0B,0x07,0x00,0xF9,0xF4,0xF7
	.byte	0x01,0x0A,0x0E,0x0A,0x00,0xF6,0xF0,0xF3
	.byte	0xFE,0x0B,0x12,0x10,0x05,0xF9,0xEF,0xEE
	.byte	0xF8,0x06,0x10,0x12,0x0B,0xFE,0xF4,0xEF
	.byte	0xF4,0x00,0x0A,0x0F,0x0B,0x02,0xFA,0xF5
	.byte	0xF7,0xFF,0x06,0x09,0x06,0x00,0xFB,0xFA
	.byte	0xFD,0x02,0x07,0x07,0x03,0xFC,0xF8,0xF9
	.byte	0xFE,0x05,0x0A,0x09,0x04,0xFC,0xF6,0xF7
	.byte	0xFD,0x04,0x09,0x08,0x03,0xFC,0xF7,0xF9
	.byte	0xFF,0x06,0x0A,0x08,0x01,0xF9,0xF5,0xF7
	.byte	0x00,0x09,0x0E,0x0B,0x02,0xF8,0xF2,0xF4
	.byte	0xFD,0x09,0x0F,0x0E,0x04,0xFA,0xF3,0xF3
	.byte	0xFB,0x06,0x0E,0x0D,0x06,0xFC,0xF5,0xF4
	.byte	0xFB,0x05,0x0C,0x0C,0x05,0xFC,0xF6,0xF5
	.byte	0xFC,0x06,0x0C,0x0C,0x04,0xFA,0xF4,0xF4
	.byte	0xFC,0x07,0x0E,0x0E,0x06,0xFA,0xF2,0xF1
	.byte	0xF8,0x05,0x0D,0x10,0x0A,0xFF,0xF6,0xF2
	.byte	0xF6,0x00,0x08,0x0C,0x0A,0x02,0xFA,0xF7
	.byte	0xF9,0xFF,0x05,0x07,0x06,0x01,0xFD,0xFC
	.byte	0xFE,0x01,0x03,0x02,0x00,0xFD,0xFC,0xFF
	.byte	0x04,0x07,0x07,0x03,0xFD,0xF8,0xF7,0xFC
	.byte	0x04,0x0A,0x0C,0x08,0xFF,0xF7,0xF4,0xF7
	.byte	0x00,0x08,0x0C,0x0A,0x02,0xFA,0xF5,0xF7
	.byte	0xFF,0x06,0x09,0x09,0x03,0xFC,0xF7,0xF8
	.byte	0xFF,0x06,0x09,0x08,0x02,0xFC,0xF7,0xF8
	.byte	0xFE,0x05,0x08,0x08,0x03,0xFD,0xF9,0xF9
	.byte	0xFE,0x04,0x06,0x06,0x03,0xFE,0xFC,0xFC
	.byte	0xFF,0x04,0x05,0x03,0x00,0xFD,0xFC,0xFE
	.byte	0x01,0x05,0x07,0x04,0x00,0xFB,0xF9,0xFC
	.byte	0x00,0x05,0x08,0x06,0x02,0xFE,0xFB,0xFB
	.byte	0xFD,0x01,0x05,0x06,0x03,0x01,0xFE,0xFE
	.byte	0xFE,0xFF,0x01,0x02,0x01,0x01,0x00,0x01
	.byte	0x02,0x00,0x00,0x00,0xFE,0xFE,0xFF,0x02
	.byte	0x04,0x03,0x02,0x00,0xFE,0xFC,0xFD,0x00
	.byte	0x04,0x04,0x03,0x02,0xFF,0xFD,0xFC,0xFE
	.byte	0x02,0x04,0x04,0x03,0x01,0xFE,0xFD,0xFE
	.byte	0x00,0x02,0x03,0x02,0x01,0xFF,0xFE,0xFF
	.byte	0x00,0x01,0x02,0x02,0x01,0x00,0xFF,0xFF
	.byte	0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00
	.byte	0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00
	.byte	0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00
	.byte	0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00
	.byte	0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01
	.byte	0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01
	.byte	0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01

	.byte	0x00

	.end
