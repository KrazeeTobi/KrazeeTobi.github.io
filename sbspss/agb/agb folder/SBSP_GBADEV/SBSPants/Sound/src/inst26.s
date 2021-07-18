#TONE NAME     : inst26
#FREQUENCY     : 8000
#BASE NOTE#    : 48
#START ADDRESS : 000000
#LOOP ADDRESS  : 000000
#END ADDRESS   : 001535
#LOOP MODE     : 1Shot
#FINE TUNE     : 0
#WAVE EXP/COMP : 1
#VOL EXP/COMP  : 1

	.section .rodata
	.global	inst26
	.align	2

inst26:
	.short	0x0000
	.short	0x0000
	.int	16384000
	.int	0
	.int	1535

	.byte	0x00,0x0C,0xF8,0xD8,0xFC,0x04,0xFC,0x04
	.byte	0x14,0x14,0x24,0x18,0xF8,0x08,0x0C,0xF8
	.byte	0xEC,0xF8,0x00,0x04,0x10,0x14,0x1C,0x0C
	.byte	0x00,0xF4,0x04,0xF4,0xF0,0x00,0x08,0x08
	.byte	0x04,0x08,0x08,0x04,0x00,0x04,0xFC,0xF8
	.byte	0xFC,0x00,0xF8,0xF8,0x00,0x00,0x00,0x08
	.byte	0x10,0x14,0x08,0x04,0x04,0xF8,0xEC,0xF4
	.byte	0xFC,0xFC,0x04,0x14,0x14,0x14,0x10,0xFC
	.byte	0xF4,0xF4,0xF0,0xF4,0x00,0x04,0x08,0x18
	.byte	0x18,0x04,0x04,0xF4,0xF4,0xEC,0xEC,0xF4
	.byte	0x00,0x0C,0x1C,0x1C,0x1C,0x10,0xF4,0xF0
	.byte	0xEC,0xE8,0xF0,0x04,0x10,0x14,0x1C,0x18
	.byte	0x08,0xFC,0xF4,0xEC,0xF4,0xF4,0xFC,0x10
	.byte	0x18,0x10,0x14,0x08,0xF4,0xF0,0xEC,0xE8
	.byte	0xF4,0x04,0x0C,0x14,0x1C,0x14,0x04,0x00
	.byte	0xF8,0xE4,0xE8,0xF0,0xF4,0xFC,0x0C,0x18
	.byte	0x18,0x14,0x10,0x00,0xF4,0xEC,0xEC,0xF4
	.byte	0x00,0x04,0x10,0x14,0x18,0x14,0x10,0xFC
	.byte	0xF0,0xE8,0xEC,0xF4,0xFC,0x08,0x14,0x20
	.byte	0x24,0x14,0x04,0xF0,0xE4,0xE4,0xF0,0xF4
	.byte	0x00,0x14,0x1C,0x1C,0x18,0x08,0xF8,0xF0
	.byte	0xF0,0xEC,0xF8,0x00,0x08,0x10,0x14,0x0C
	.byte	0x08,0xFC,0xF0,0xEC,0xF4,0xF8,0x04,0x0C
	.byte	0x14,0x10,0x10,0x08,0x00,0xEC,0xE4,0xE8
	.byte	0xF8,0x0C,0x14,0x10,0x14,0x10,0x04,0x00
	.byte	0xF8,0xF0,0xF8,0x00,0x04,0x04,0x08,0x08
	.byte	0x0C,0x10,0x08,0xF8,0xF8,0xF8,0xFC,0x00
	.byte	0x04,0x04,0x08,0x08,0x08,0x08,0x00,0xFC
	.byte	0xFC,0xF8,0xFC,0xFC,0x00,0x00,0x04,0x08
	.byte	0x0C,0x08,0x0C,0x08,0x00,0xFC,0xF8,0xF4
	.byte	0xF8,0xF8,0x04,0x0C,0x0C,0x08,0x08,0x04
	.byte	0x04,0x00,0xFC,0x00,0xFC,0xFC,0x08,0x0C
	.byte	0x0C,0x04,0xFC,0xF8,0xF8,0xFC,0x04,0x04
	.byte	0x0C,0x0C,0x08,0x00,0x00,0xFC,0xFC,0xF8
	.byte	0x00,0x00,0x00,0x00,0x04,0x08,0x10,0x0C
	.byte	0x00,0xF8,0xF4,0xF4,0x00,0x08,0x0C,0x08
	.byte	0x08,0x04,0xF8,0xF0,0xF4,0xFC,0x04,0x08
	.byte	0x08,0x04,0x00,0x08,0x08,0x04,0x08,0x04
	.byte	0xFC,0xFC,0xFC,0xF8,0x04,0x04,0x04,0x00
	.byte	0xFC,0x00,0x08,0x08,0x0C,0x08,0x00,0x00
	.byte	0x00,0xFC,0xFC,0xFC,0x00,0x00,0x08,0x08
	.byte	0x08,0x08,0x04,0xFC,0x00,0xFC,0xFC,0x00
	.byte	0x04,0x00,0x04,0x08,0x0C,0x08,0x00,0xFC
	.byte	0xFC,0xFC,0x00,0xFC,0x00,0x08,0x08,0x04
	.byte	0x04,0x04,0x04,0x04,0xFC,0xF8,0xFC,0xFC
	.byte	0x04,0x0C,0x0C,0x08,0x08,0x00,0xFC,0xF8
	.byte	0xFC,0x04,0x08,0x0C,0x04,0x04,0x04,0xFC
	.byte	0xF8,0xF8,0xFC,0x04,0x0C,0x0C,0x08,0x00
	.byte	0x04,0x04,0x00,0x00,0xF8,0xFC,0xFC,0xFC
	.byte	0x00,0x08,0x08,0x0C,0x0C,0x00,0xFC,0xF8
	.byte	0xF8,0x00,0x00,0x04,0x00,0x00,0x04,0x04
	.byte	0x00,0x04,0x00,0x00,0x00,0xFC,0x04,0x0C
	.byte	0x10,0x0C,0x04,0x08,0x04,0xFC,0xFC,0xF8
	.byte	0xF0,0xFC,0x08,0x14,0x18,0x10,0x04,0x00
	.byte	0xF8,0xF0,0xF0,0xFC,0x08,0x10,0x14,0x10
	.byte	0x08,0x04,0xFC,0xEC,0xE8,0xF0,0xF8,0x0C
	.byte	0x18,0x1C,0x14,0x0C,0xFC,0xF0,0xEC,0xEC
	.byte	0xEC,0xFC,0x08,0x10,0x18,0x1C,0x10,0x04
	.byte	0xF8,0xF0,0xF0,0xF4,0xF8,0x00,0x10,0x1C
	.byte	0x1C,0x10,0x04,0xFC,0xF0,0xF0,0xF4,0xF8
	.byte	0x04,0x10,0x18,0x1C,0x0C,0x00,0xFC,0xF4
	.byte	0xF4,0xF0,0xF0,0xFC,0x0C,0x18,0x1C,0x1C
	.byte	0x14,0x00,0xF0,0xE8,0xE4,0xF0,0x00,0x0C
	.byte	0x14,0x1C,0x18,0x14,0xFC,0xEC,0xE8,0xE8
	.byte	0xF0,0x00,0x04,0x14,0x20,0x18,0x10,0x00
	.byte	0xE8,0xE8,0xEC,0xF4,0xFC,0x04,0x0C,0x18
	.byte	0x18,0x10,0x04,0x00,0xF8,0xF4,0xFC,0xFC
	.byte	0xFC,0x08,0x0C,0x08,0x08,0x0C,0x04,0x08
	.byte	0x00,0xF8,0xF8,0x00,0x04,0x00,0x00,0x0C
	.byte	0x08,0x0C,0x08,0xF8,0xF4,0xF4,0xF0,0xF8
	.byte	0x00,0x08,0x10,0x14,0x14,0x0C,0xF8,0xF8
	.byte	0xF0,0xEC,0xF0,0xFC,0x08,0x18,0x1C,0x18
	.byte	0x0C,0xFC,0xF4,0xF0,0xF0,0xF8,0x00,0x04
	.byte	0x08,0x10,0x18,0x10,0x08,0x00,0xEC,0xEC
	.byte	0xF8,0xFC,0x04,0x08,0x0C,0x14,0x18,0x0C
	.byte	0x00,0xF8,0xF8,0xF4,0xF0,0xF4,0xFC,0x04
	.byte	0x18,0x20,0x14,0x08,0xFC,0xF4,0xF8,0xF8
	.byte	0xF0,0xF4,0x00,0x0C,0x14,0x14,0x10,0xFC
	.byte	0xF8,0xF0,0xE8,0xF8,0x04,0x0C,0x18,0x14
	.byte	0x0C,0x0C,0x04,0xF0,0xF0,0xF0,0xF4,0x00
	.byte	0x0C,0x14,0x18,0x1C,0x14,0x00,0xF0,0xEC
	.byte	0xF0,0xF8,0x04,0x08,0x0C,0x14,0x18,0x10
	.byte	0xFC,0xF4,0xF0,0xF4,0xFC,0xFC,0x00,0x0C
	.byte	0x10,0x14,0x14,0x08,0xFC,0xF8,0xF4,0xF0
	.byte	0xF4,0xFC,0x04,0x0C,0x14,0x0C,0x08,0x08
	.byte	0x00,0xF8,0xF8,0xF0,0xF4,0x00,0x04,0x0C
	.byte	0x14,0x0C,0x04,0xFC,0xFC,0xFC,0x00,0x08
	.byte	0x08,0x04,0x10,0x08,0x00,0x00,0xFC,0xFC
	.byte	0x00,0x00,0x00,0x00,0x08,0x10,0x0C,0x08
	.byte	0x04,0xF8,0x00,0x00,0xF4,0xFC,0x04,0x04
	.byte	0x10,0x10,0x00,0x00,0x00,0xF8,0xFC,0x00
	.byte	0x00,0x00,0x10,0x08,0x00,0x00,0x04,0x04
	.byte	0x08,0x00,0xF4,0xF8,0xF8,0x00,0x04,0x08
	.byte	0x14,0x0C,0x08,0x00,0xFC,0xF8,0x00,0x00
	.byte	0xFC,0x04,0x0C,0x08,0x04,0x00,0xFC,0x04
	.byte	0x0C,0x08,0x08,0x00,0x00,0x04,0x04,0x00
	.byte	0x04,0x08,0x04,0x04,0x08,0x00,0xFC,0x00
	.byte	0xFC,0x00,0x08,0x08,0x0C,0x0C,0x04,0xF8
	.byte	0xF4,0xFC,0xFC,0xF8,0xFC,0x00,0x00,0x08
	.byte	0x10,0x0C,0x08,0x04,0xF8,0xF0,0xF0,0xFC
	.byte	0x08,0x10,0x14,0x0C,0x04,0xFC,0xF0,0xEC
	.byte	0xF4,0xF8,0x00,0x0C,0x14,0x1C,0x18,0x10
	.byte	0x00,0xF0,0xE4,0xEC,0xFC,0x00,0x0C,0x10
	.byte	0x10,0x14,0x14,0x00,0xF4,0xF8,0xFC,0xFC
	.byte	0xFC,0x00,0x04,0x10,0x1C,0x18,0x00,0xF0
	.byte	0xEC,0xE8,0xF0,0xF8,0x00,0x10,0x20,0x1C
	.byte	0x14,0x00,0xF4,0xEC,0xE8,0xF0,0xFC,0x04
	.byte	0x0C,0x14,0x18,0x10,0x10,0x08,0xF8,0xE8
	.byte	0xF0,0xF8,0x08,0x18,0x18,0x0C,0x0C,0x08
	.byte	0xF8,0xF0,0xF4,0xF4,0xFC,0x08,0x0C,0x10
	.byte	0x18,0x18,0x10,0x04,0xF8,0xEC,0xF0,0xF8
	.byte	0xFC,0x00,0x08,0x0C,0x14,0x10,0x10,0x04
	.byte	0xFC,0xF8,0xF0,0xF0,0xF4,0xFC,0x08,0x10
	.byte	0x10,0x10,0x10,0x00,0xF8,0xF0,0xF0,0xF8
	.byte	0x04,0x08,0x10,0x10,0x10,0x08,0xFC,0xF8
	.byte	0xF4,0xF4,0xFC,0x00,0x08,0x0C,0x0C,0x0C
	.byte	0x0C,0x04,0xFC,0xF8,0xF8,0xFC,0x00,0x08
	.byte	0x08,0x08,0x0C,0x04,0x04,0x04,0xFC,0xFC
	.byte	0xFC,0xFC,0x00,0x08,0x04,0x04,0x08,0x04
	.byte	0x08,0x00,0xF8,0xF4,0xF0,0xF8,0x00,0x04
	.byte	0x10,0x18,0x18,0x14,0x04,0xF4,0xEC,0xE8
	.byte	0xF0,0xF4,0x04,0x10,0x18,0x20,0x1C,0x08
	.byte	0xF8,0xEC,0xE8,0xF4,0xFC,0x08,0x14,0x10
	.byte	0x10,0x0C,0x04,0x04,0xFC,0xEC,0xF0,0xF4
	.byte	0x04,0x14,0x18,0x18,0x10,0x00,0xFC,0xF8
	.byte	0xEC,0xEC,0xF8,0x08,0x0C,0x0C,0x0C,0x04
	.byte	0x04,0x08,0x00,0xF4,0xF4,0xF4,0x00,0x08
	.byte	0x08,0x0C,0x10,0x10,0x0C,0xFC,0xEC,0xEC
	.byte	0xEC,0x00,0x0C,0x18,0x20,0x20,0x14,0x04
	.byte	0xF0,0xE4,0xE4,0xE8,0xFC,0x0C,0x14,0x1C
	.byte	0x1C,0x14,0x08,0xFC,0xEC,0xE8,0xEC,0xF8
	.byte	0x08,0x14,0x1C,0x14,0x0C,0x04,0xF4,0xEC
	.byte	0xE8,0xF0,0xFC,0x0C,0x18,0x1C,0x0C,0x08
	.byte	0x00,0xF4,0xF4,0xF4,0xF4,0xFC,0x04,0x0C
	.byte	0x10,0x10,0x0C,0x04,0xF8,0xFC,0xF8,0xF8
	.byte	0x00,0x08,0x08,0x08,0x08,0x04,0x08,0x08
	.byte	0x04,0xFC,0xF4,0xF4,0xFC,0x08,0x14,0x18
	.byte	0x10,0x0C,0x00,0xFC,0xF4,0xF0,0xF8,0x00
	.byte	0x08,0x10,0x0C,0x0C,0x08,0x04,0x00,0xF8
	.byte	0xF8,0xFC,0xF8,0x00,0x04,0x00,0x04,0x08
	.byte	0x04,0x04,0xFC,0xFC,0xFC,0x00,0x04,0x00
	.byte	0xFC,0x00,0x04,0x08,0x0C,0x04,0x00,0x04
	.byte	0x00,0xFC,0xFC,0xFC,0xFC,0x00,0x0C,0x10
	.byte	0x10,0x10,0x08,0xFC,0xF8,0xF0,0xF0,0xFC
	.byte	0x08,0x10,0x18,0x10,0x08,0x00,0xF4,0xF4
	.byte	0xF8,0xFC,0x04,0x04,0x0C,0x10,0x10,0x10
	.byte	0x00,0xF0,0xEC,0xF0,0xF4,0x00,0x04,0x08
	.byte	0x0C,0x10,0x0C,0x08,0xFC,0xFC,0xF4,0xF0
	.byte	0xF4,0xF8,0x04,0x10,0x14,0x18,0x0C,0x04
	.byte	0x00,0xF8,0xF4,0xF4,0xF8,0x00,0x04,0x10
	.byte	0x10,0x0C,0x0C,0x08,0xFC,0xF8,0xF4,0xF0
	.byte	0xF8,0x00,0x0C,0x18,0x1C,0x18,0x08,0xF8
	.byte	0xEC,0xE8,0xE8,0xFC,0x08,0x14,0x18,0x10
	.byte	0x08,0x04,0xFC,0xF8,0xF4,0xF0,0xF4,0xFC
	.byte	0x08,0x10,0x10,0x14,0x0C,0x00,0xF8,0xF0
	.byte	0xE8,0xF0,0xF8,0x08,0x14,0x18,0x18,0x10
	.byte	0x00,0xF4,0xEC,0xEC,0xF4,0x00,0x08,0x10
	.byte	0x14,0x1C,0x18,0x08,0xFC,0xF0,0xE8,0xEC
	.byte	0xF4,0x00,0x0C,0x18,0x18,0x18,0x0C,0x04
	.byte	0xF8,0xF0,0xF4,0xF0,0xF8,0x08,0x0C,0x10
	.byte	0x10,0x0C,0x00,0xF4,0xEC,0xF0,0xF8,0x08
	.byte	0x10,0x0C,0x08,0x00,0x00,0x04,0x04,0x00
	.byte	0xFC,0xF8,0xFC,0x04,0x00,0x04,0x08,0x08
	.byte	0x0C,0x0C,0x04,0xF8,0xF4,0xF8,0xFC,0x04
	.byte	0x0C,0x0C,0x08,0x0C,0x04,0x00,0xFC,0xF8
	.byte	0xF8,0xF8,0x00,0x08,0x0C,0x18,0x14,0x04
	.byte	0x00,0xF8,0xF0,0xF4,0xF8,0xFC,0x04,0x0C
	.byte	0x10,0x10,0x08,0x04,0x00,0xF8,0xF4,0xF4
	.byte	0xFC,0x04,0x04,0x0C,0x04,0x04,0x08,0x04
	.byte	0x04,0x04,0xFC,0xFC,0xFC,0xFC,0x04,0x0C
	.byte	0x0C,0x0C,0x04,0x04,0xFC,0xF4,0xF4,0xFC
	.byte	0x04,0x08,0x10,0x0C,0x0C,0x0C,0x08,0xF8
	.byte	0xF0,0xF4,0xF8,0x04,0x14,0x10,0x08,0x08
	.byte	0x00,0xFC,0xF8,0xF4,0xF4,0x00,0x0C,0x14
	.byte	0x14,0x0C,0x04,0xF8,0xF0,0xF0,0xF0,0xF8
	.byte	0x04,0x0C,0x10,0x14,0x10,0x08,0xFC,0xF4
	.byte	0xF8,0xF8,0xFC,0x00,0x04,0x08,0x0C,0x08
	.byte	0x04,0xF8,0x00,0x04,0x04,0x08,0x04,0xFC
	.byte	0x00,0x04,0x04,0x04,0x00,0x00,0x04,0x04
	.byte	0x04,0x00,0x00,0x00,0x04,0x08,0x08,0x08
	.byte	0x08,0x00,0xF8,0xFC,0xFC,0x00,0x04,0x00
	.byte	0x00,0x04,0x00,0x00,0x00,0xFC,0x00,0x00
	.byte	0x00,0x04,0x04,0x08,0x0C,0x04,0xFC,0xF8
	.byte	0xF8,0xFC,0x00,0x03,0x03,0x03,0x07,0x06
	.byte	0x03,0x03,0x00,0x03,0x06,0x00,0x00,0xFC
	.byte	0xFD,0x00,0x00,0xFD,0x05,0x08,0x0A,0x0A
	.byte	0x05,0x00,0xFB,0xF8,0xFB,0xFD,0x02,0x04
	.byte	0x06,0x06,0x05,0x01,0x00,0xFC,0xFA,0xFA
	.byte	0xFE,0x03,0x06,0x04,0x04,0x01,0xFE,0xFE
	.byte	0xFE,0xFC,0xFD,0xFE,0x00,0x01,0x02,0x01
	.byte	0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00
	.byte	0x00,0xFF,0xFF,0xFF,0x00,0x00,0xFF

	.byte	0x00

	.end
