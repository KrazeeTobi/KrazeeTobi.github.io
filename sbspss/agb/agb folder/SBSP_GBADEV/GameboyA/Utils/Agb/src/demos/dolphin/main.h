/********************************************************************/
/*          main.h                                                  */
/*                 Data external declaration                        */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef	_MAIN_H
#define	_MAIN_H

#define Dec2Int(x)  ((x) >> 8)
#define ABS(N) (N < 0) ? (-N) : (N)

#define MAP_WIDTH   5120-256	// map width
#define MAP_HEIGHT  512-160	// map height

#define DEAD  0
#define ALIVE 1

#define SCREEN_OUT 0
#define SCREEN_IN  1

#define RIGHT  1
#define LEFT  -1

// character database address
#define CHAR_BASE0_ADDR  VRAM+0x0000
#define CHAR_BASE1_ADDR  VRAM+0x4000
#define CHAR_BASE2_ADDR  VRAM+0x8000
#define CHAR_BASE3_ADDR  VRAM+0xc000

// specify character base block
#define CHAR_BASE_0  0
#define CHAR_BASE_1  1
#define CHAR_BASE_2  2
#define CHAR_BASE_3  3

// OBJ VRAM MAP
#define DOLPHIN_VRAM_POS OBJ_MODE0_VRAM			// dolphin
#define SHELL_1_VRAM_POS OBJ_MODE0_VRAM + 0x1000	// Nautilus 1
#define SHELL_2_VRAM_POS OBJ_MODE0_VRAM + 0x1400	// Nautilus 2
#define SHELL_3_VRAM_POS OBJ_MODE0_VRAM + 0x1800	// Nautilus 3
#define SHELL_4_VRAM_POS OBJ_MODE0_VRAM + 0x1c00	// Nautilus 4
#define AWA_VRAM_POS     OBJ_MODE0_VRAM + 0x2000	// bubbles
#define FUKIYA_VRAM_POS  OBJ_MODE0_VRAM + 0x2040	// blowgun
#define RING_L_VRAM_POS  OBJ_MODE0_VRAM + 0x2080	// left side of ring
#define RING_R_VRAM_POS  OBJ_MODE0_VRAM + 0x2880	// right side of ring
#define TAMA_VRAM_POS    OBJ_MODE0_VRAM + 0x3080	// ball
#define SHELL_5_VRAM_POS OBJ_MODE0_VRAM + 0x3000	// Nautilus 5
#define SHELL_6_VRAM_POS OBJ_MODE0_VRAM + 0x3400	// Nautilus 6
#define SHELL_7_VRAM_POS OBJ_MODE0_VRAM + 0x3800	// Nautilus 7
#define SHELL_8_VRAM_POS OBJ_MODE0_VRAM + 0x3c00	// Nautilus 8
#define SHELL_9_VRAM_POS OBJ_MODE0_VRAM + 0x4000	// Nautilus 9
#define SHELL_10_VRAM_POS OBJ_MODE0_VRAM + 0x4400	// Nautilus 10
#define SHELL_11_VRAM_POS OBJ_MODE0_VRAM + 0x4800	// Nautilus 11
#define SHELL_12_VRAM_POS OBJ_MODE0_VRAM + 0x4c00	// Nautilus 12
#define WAVE2_VRAM_POS    OBJ_MODE0_VRAM + 0x5000


// OAM character number
#define DOLPHIN_CHAR_NO    0 // 64x64dot	64
#define SHELL1_CHAR_NO   128 // 32x32dot	32
#define SHELL2_CHAR_NO   160 // 32x32dot	32
#define SHELL3_CHAR_NO   192 // 32x32dot	32
#define SHELL4_CHAR_NO   224 // 32x32dot	32
#define AWA_CHAR_NO      256 // 8x8dot		1
#define FUKIYA_CHAR_NO   258 // 16x16dot    2
#define RING_L_CHAR_NO   260 // 			32
#define RING_R_CHAR_NO   324 // 			32
#define TAMA_CHAR_NO     388 // 8x8dot		1
#define SHELL5_CHAR_NO   448 // 32x32dot	32
#define SHELL6_CHAR_NO   480 // 32x32dot	32
#define SHELL7_CHAR_NO   512 // 32x32dot	32
#define SHELL8_CHAR_NO   544 // 32x32dot	32
#define SHELL9_CHAR_NO   576 // 32x32dot	32
#define SHELL10_CHAR_NO  608 // 32x32dot	32
#define SHELL11_CHAR_NO  640 // 32x32dot	32
#define SHELL12_CHAR_NO  672 // 32x32dot	32
#define WAVE_2_CHAR_NO   704

typedef struct {
	OamData		Objbuf[128];	// OAM backup
	u8			flag[128];
}ObjBuf;

#endif