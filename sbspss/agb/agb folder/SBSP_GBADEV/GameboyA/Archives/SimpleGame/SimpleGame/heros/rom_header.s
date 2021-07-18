@********************************************************************
@* ROM registration data (for GAS)                    							*
@********************************************************************
  .ALIGN
  .CODE 32
  @ Start vector
rom_header: b rom_header_end

@ Nintendo logo/character data (8000004h)
  .byte   0x24,0xff,0xae,0x51,0x69,0x9a,0xa2,0x21
  .byte   0x3d,0x84,0x82,0x0a,0x84,0xe4,0x09,0xad
  .byte   0x11,0x24,0x8b,0x98,0xc0,0x81,0x7f,0x21
  .byte   0xa3,0x52,0xbe,0x19,0x93,0x09,0xce,0x20
  .byte   0x10,0x46,0x4a,0x4a,0xf8,0x27,0x31,0xec
  .byte   0x58,0xc7,0xe8,0x33,0x82,0xe3,0xce,0xbf
  .byte   0x85,0xf4,0xdf,0x94,0xce,0x4b,0x09,0xc1
  .byte   0x94,0x56,0x8a,0xc0,0x13,0x72,0xa7,0xfc
  .byte   0x9f,0x84,0x4d,0x73,0xa3,0xca,0x9a,0x61
  .byte   0x58,0x97,0xa3,0x27,0xfc,0x03,0x98,0x76
  .byte   0x23,0x1d,0xc7,0x61,0x03,0x04,0xae,0x56
  .byte   0xbf,0x38,0x84,0x00,0x40,0xa7,0x0e,0xfd
  .byte   0xff,0x52,0xfe,0x03,0x6f,0x95,0x30,0xf1
  .byte   0x97,0xfb,0xc0,0x85,0x60,0xd6,0x80,0x25
  .byte   0xa9,0x63,0xbe,0x03,0x01,0x4e,0x38,0xe2
  .byte   0xf9,0xa2,0x34,0xff,0xbb,0x3e,0x03,0x44
  .byte   0x78,0x00,0x90,0xcb,0x88,0x11,0x3a,0x94
  .byte   0x65,0xc0,0x7c,0x63,0x87,0xf0,0x3c,0xaf
  .byte   0xd6,0x25,0xe4,0x8b,0x38,0x0a,0xac,0x72
  .byte   0x21,0xd4,0xf8,0x07

@ Game title (80000A0h)
  .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  .byte   0x00,0x00,0x00,0x00

@ Game code (80000ACh)
  .byte   0x00,0x00,0x00,0x00

@ Maker code (80000B0h)
  .byte   0x30,0x31

@ Fixed value (80000B2h)
  .byte   0x96

@ Main unit code (80000B3h)
  .byte   0x00

@ Device type (80000B4h)
	.byte   0x00

@ Unused data (7Byte) (80000B5h)
  .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00

@ Software version No (80000BCh)
  .byte   0x00

@ Complement check (80000BDh)
  .byte   0xf0

@ Check sum (80000BEh)
  .byte   0x00,0x00

rom_header_end:
