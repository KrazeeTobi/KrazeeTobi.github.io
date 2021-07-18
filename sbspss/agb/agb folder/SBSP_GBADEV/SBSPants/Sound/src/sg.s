#TONE NAME     : sg
#FREQUENCY     : 11025
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 000662
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	sg
	.align	2

sg:
	.short	0x0000
	.short	0x0000
	.int	22579200
	.int	0
	.int	662

	.byte	0xFF,0x02,0xFF,0x02,0xFE,0x02,0x04,0xF7
	.byte	0x07,0x11,0xBA,0x64,0xEE,0xC0,0x70,0xA8
	.byte	0x13,0x3A,0xA6,0x41,0xFB,0xCA,0x53,0xC5
	.byte	0x06,0x37,0xB9,0x2C,0x0B,0xCD,0x39,0xDC
	.byte	0xFC,0x2A,0xCA,0x21,0x0C,0xD5,0x30,0xEB
	.byte	0xF5,0x21,0xD9,0x16,0x08,0xDE,0x28,0xF0
	.byte	0xF1,0x20,0xE8,0x0A,0x0A,0xE6,0x1C,0xF3
	.byte	0xF2,0x1E,0xEA,0x02,0x12,0xEA,0x12,0xFC
	.byte	0xF6,0x16,0xEE,0x01,0x0F,0xED,0x0B,0x03
	.byte	0xF6,0x0E,0xF8,0x00,0x0B,0xF4,0x08,0x03
	.byte	0xF5,0x0B,0xFC,0xFD,0x08,0xF8,0x07,0x02
	.byte	0xF8,0x09,0xFD,0xFD,0x06,0xFB,0x05,0xFE
	.byte	0xFC,0x09,0xFB,0xFF,0x07,0xFB,0x03,0x01
	.byte	0xFE,0x05,0xFC,0x00,0x05,0xFC,0x02,0x03
	.byte	0xFE,0x02,0x00,0x00,0x02,0xFD,0x02,0x02
	.byte	0xFD,0x03,0x02,0xFE,0x02,0x00,0x01,0x01
	.byte	0xFF,0x02,0x01,0xFE,0x02,0x01,0xFF,0x01
	.byte	0x00,0x00,0x01,0xFF,0x02,0x00,0xFF,0x02
	.byte	0x00,0xFF,0x01,0x00,0x00,0x01,0x00,0x01
	.byte	0x00,0xFF,0x02,0x00,0x00,0x01,0x00,0x00
	.byte	0x01,0x00,0x01,0x00,0x00,0x00,0x02,0x00
	.byte	0x00,0x02,0xFF,0x00,0x01,0xFF,0x01,0x00
	.byte	0x00,0x01,0xFF,0x01,0x01,0xFD,0x06,0xFE
	.byte	0xFF,0x05,0xFC,0x03,0x02,0xFC,0x05,0xFF
	.byte	0xFF,0x04,0xFD,0x01,0x02,0xFE,0x03,0x00
	.byte	0xFF,0x03,0xFF,0x01,0x02,0xFE,0x02,0x00
	.byte	0xFF,0x02,0xFF,0x00,0x02,0xFF,0x02,0x00
	.byte	0x00,0x02,0xFF,0x00,0x02,0xFF,0x01,0x00
	.byte	0x00,0x01,0x00,0x00,0x02,0xFF,0x01,0x01
	.byte	0x01,0xFE,0x02,0x02,0xFD,0x04,0xFF,0xFF
	.byte	0x04,0xFD,0x02,0x02,0xFD,0x04,0xFF,0xFF
	.byte	0x04,0xFD,0x03,0x01,0xFD,0x05,0xFE,0x00
	.byte	0x04,0xFC,0x03,0x02,0xFD,0x04,0xFF,0xFF
	.byte	0x03,0xFD,0x01,0x02,0xFE,0x00,0x02,0xFF
	.byte	0x01,0x01,0x00,0x02,0x00,0x00,0x01,0xFF
	.byte	0x01,0x01,0xFF,0x02,0x00,0xFF,0x04,0xFD
	.byte	0x01,0x03,0xFC,0x04,0x00,0xFE,0x04,0xFE
	.byte	0x00,0x03,0xFD,0x03,0x00,0xFE,0x04,0xFE
	.byte	0x00,0x03,0xFD,0x02,0x01,0xFE,0x04,0xFF
	.byte	0x00,0x03,0xFE,0x02,0x01,0xFF,0x02,0xFF
	.byte	0x02,0xFF,0x00,0x03,0xFE,0x01,0x01,0xFF
	.byte	0x02,0x00,0xFF,0x02,0xFF,0x00,0x02,0x00
	.byte	0xFE,0x03,0x02,0xFD,0x02,0x02,0xFE,0x02
	.byte	0x00,0xFF,0x02,0xFF,0x01,0x01,0xFF,0x01
	.byte	0x01,0x00,0x01,0x01,0xFF,0x02,0x00,0x00
	.byte	0x02,0xFE,0x02,0x01,0xFE,0x03,0x00,0xFF
	.byte	0x03,0xFF,0x00,0x02,0xFF,0x01,0x02,0xFE
	.byte	0x02,0x01,0xFF,0x03,0xFF,0x00,0x01,0xFF
	.byte	0x02,0x01,0xFF,0x02,0x00,0x00,0x01,0x01
	.byte	0x00,0xFF,0x02,0x00,0x00,0x01,0x00,0x00
	.byte	0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x00
	.byte	0x00,0x01,0xFF,0x01,0x01,0xFF,0x02,0x00
	.byte	0x00,0x01,0x00,0xFF,0x03,0x00,0xFE,0x05
	.byte	0xFE,0xFE,0x06,0xFD,0x01,0x03,0xFC,0x04
	.byte	0x00,0xFE,0x05,0xFD,0x01,0x03,0xFB,0x05
	.byte	0xFF,0xFF,0x04,0xFA,0x05,0xFF,0xFD,0x06
	.byte	0xFD,0x01,0x04,0xFC,0x03,0x01,0xFD,0x05
	.byte	0xFF,0xFF,0x04,0xFC,0x02,0x03,0xFC,0x04
	.byte	0xFF,0xFF,0x04,0xFD,0x01,0x03,0xFD,0x03
	.byte	0x00,0xFF,0x04,0xFD,0x02,0x01,0xFC,0x05
	.byte	0xFF,0xFE,0x05,0xFD,0x01,0x03,0xFD,0x03
	.byte	0x00,0xFF,0x04,0xFE,0x00,0x04,0xFD,0x00
	.byte	0x04,0xFD,0x01,0x03,0xFD,0x03,0x00,0xFF
	.byte	0x04,0xFE,0x02,0x01,0xFD,0x04,0xFF,0xFF
	.byte	0x03,0x00,0x01,0x01,0xFF,0x02,0x01,0xFF
	.byte	0x01,0x00,0x00,0x01,0x01,0x01,0x00,0x02
	.byte	0xFF,0x00,0x03,0xFE,0x03,0xFF,0x00,0x03
	.byte	0xFD,0x02,0x01,0xFE,0x03,0x00,0xFF,0x02
	.byte	0xFF,0x01,0x01,0x00,0x01,0x01,0xFF,0x01
	.byte	0x02,0xFE,0x02,0x01,0xFF,0x02,0x00,0x01
	.byte	0x02,0xFE,0x03,0x01,0xFE,0x03,0x00,0x00
	.byte	0x01,0x00,0x00,0x01,0xFF,0x01,0x01,0xFF
	.byte	0x02,0x00,0x00,0x02,0x00,0x00,0x01,0x00
	.byte	0x01,0x00,0xFF,0x02,0xFF,0x00,0x02,0xFF
	.byte	0x01,0x01,0xFE,0x03,0x00,0xFF,0x03,0xFF
	.byte	0x01,0x02,0x00,0x00,0x01,0x00,0x01,0x00
	.byte	0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x01
	.byte	0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01
	.byte	0x01,0x00,0x01,0x00,0x01,0x01,0x00,0x00
	.byte	0x01,0x00,0x01,0x01,0xFF,0x01,0x00,0x00
	.byte	0x01,0x00,0x01,0x01,0x00,0x01,0x00,0x00
	.byte	0x01,0x00,0x01,0x01,0x00,0x01,0x00,0x01
	.byte	0x00,0x00,0x01,0x00,0x00,0x01

	.byte	0x00

	.end
