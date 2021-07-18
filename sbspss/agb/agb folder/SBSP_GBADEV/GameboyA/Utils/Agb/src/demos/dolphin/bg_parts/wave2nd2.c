#include <AgbTypes.h>


const u16 wave2nd2_Palette[256] = {
0x0000,0x8421,0x9440,0x8842,0x9460,0x0c62,0x1880,0xa460,
0x0c83,0x1881,0x20a0,0x10a3,0x3c61,0x1084,0x24c0,0x90a3,
0x8ce1,0xa4a2,0xc461,0xa084,0xa4c0,0x3c83,0x5061,0xc481,
0x98c4,0x9887,0x2ce1,0x5c42,0x18c5,0xd081,0x2ce3,0xd862,
0x1903,0xad00,0xcca1,0xb887,0xd881,0x9ce5,0x6063,0x1ce7,
0x24aa,0x3503,0xd0c1,0x9160,0xc8a4,0x2ce7,0xa105,0xdca1,
0x3140,0x6484,0xd4e1,0x2126,0x5ce1,0x9cea,0xb0ac,0x3d24,
0x91a0,0xe484,0x2945,0x1964,0xb960,0xd901,0x48e7,0x5103,
0xb4e9,0x2547,0xe8a5,0x6121,0x11a4,0x15e0,0x4544,0xa965,
0x30cf,0xc945,0x39c0,0xecc6,0xa949,0x4583,0xad66,0xd507,
0xbcee,0xbd29,0x252d,0x91c4,0x04f4,0xcd65,0x21a6,0x1620,
0x70e7,0x34f1,0x4d85,0xb186,0x2d89,0x51a4,0xc90f,0x7507,
0xc5e1,0xa5c6,0x9a40,0x416b,0x9205,0xb5a8,0x51a6,0x51c4,
0x3913,0xb18b,0xf508,0x2d6f,0x1a80,0xb9c8,0x55e4,0x29e8,
0x4a40,0x1645,0x8956,0xf929,0x35cb,0x1aa0,0x59c7,0x3de9,
0xd132,0xda04,0x4135,0x9665,0x49ad,0x1ec0,0xb9cc,0xb591,
0xfd4a,0xde23,0xbe09,0xdde8,0x5280,0x5555,0xde43,0x7d6b,
0xbded,0x1f00,0x1aa6,0x4958,0x422b,0x6283,0xfd8c,0xd557,
0x420f,0xe20a,0x62a3,0x55ef,0xa320,0xda67,0x05bb,0x3dd4,
0x5ee0,0xe6a2,0x1ae6,0x4e4b,0xfdad,0xe6a3,0x462f,0xeac2,
0xe6c3,0xd17a,0x7dce,0xa360,0x5a6c,0x6ae2,0x6ee2,0x9f07,
0x6ae3,0xca6d,0x7def,0x6f02,0xeae3,0x4615,0x6b02,0x27a0,
0xef02,0xef03,0x6a30,0x2729,0xd6ab,0xf321,0xd99c,0x6f22,
0x7e10,0x7722,0x4e90,0xef22,0xa7c0,0x861e,0xf741,0xfb23,
0xe6e8,0xfe31,0xab2a,0xf342,0xfb24,0xce56,0x52cf,0x5ddd,
0x7b80,0x7e52,0x334c,0xfb26,0xdb0d,0x7e73,0x5298,0xdad2,
0x7b49,0xbf4e,0x7e94,0x3b32,0x7bc3,0xfb4b,0x56b9,0xe311,
0xfb4c,0x7eb5,0xbf70,0x7b6d,0x7b6e,0x6334,0xdada,0x7b6f,
0x7ef7,0xbf93,0x7b70,0x7b70,0xfb71,0xfb71,0x7f18,0x631a,
0xfb72,0xfb72,0x6b76,0x7b93,0x37f3,0x7f39,0x7b93,0xfb94,
0xe73c,0xfb95,0x7f59,0xfb96,0x7f7a,0x7fb7,0x6b7d,0xffb8,
0x7f9c,0xffb9,0x7fda,0x7fbd,0x7fdb,0xffdd,0xffde,0x7fff,
};


const u8 wave2nd2_Char[8*8*(32/8/1/1)*(8/8) + 0] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0  0
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0xff,0x00,
0x00,0xff,0xff,0xb5,0xff,0xff,0xc0,0xff,
0xff,0xb5,0xc0,0xc0,0xb5,0xc0,0xc0,0xb5,
0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0x80,0xc0,
0xb5,0xc0,0x80,0xc0,0x80,0x8e,0xc0,0xc0,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 1
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0xff,0xff,0xb5,0xff,0x00,0x00,0x00,
0xff,0xc0,0xc0,0x8e,0xff,0xff,0x00,0x00,
0xc0,0xb5,0xb5,0xb5,0xc0,0xb5,0xff,0x00,
0xb5,0xc0,0xb5,0xc0,0xb5,0xc0,0xb5,0xff,
0xb5,0xc0,0xc0,0x80,0xb5,0xc0,0xb5,0x8e,
0xc0,0x80,0x80,0xc0,0x80,0xc0,0xc0,0xc0,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 2
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
0x00,0x00,0x00,0xff,0x00,0xff,0xc0,0x8e,
0x00,0xff,0xff,0xb5,0xff,0x8e,0x8e,0xc0,
0x00,0xb5,0xc0,0xc0,0x8e,0xc0,0xc0,0xc0,
0xff,0xb5,0xc0,0xc0,0xc0,0xb5,0xc0,0xb5,
0xc0,0xc0,0x80,0xc0,0x80,0xc0,0xc0,0xc0,
0xc0,0x9c,0xc0,0xc0,0xc0,0x80,0xc0,0x80,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 3
0xff,0xff,0x00,0xff,0x00,0x00,0x00,0x00,
0xc0,0xc0,0xb5,0xc0,0xff,0x00,0xff,0x00,
0xc0,0x8e,0x8e,0xb5,0x8e,0xc0,0xb5,0x00,
0xc0,0x8e,0xc0,0x8e,0xc0,0x8e,0xc0,0xff,
0x8e,0xc0,0xc0,0xc0,0xc0,0xc0,0xb5,0xff,
0xc0,0xc0,0xc0,0xc0,0x80,0xc0,0xc0,0xb5,
0xc0,0xc0,0x80,0xc0,0xc0,0x80,0xc0,0xc0,

};
