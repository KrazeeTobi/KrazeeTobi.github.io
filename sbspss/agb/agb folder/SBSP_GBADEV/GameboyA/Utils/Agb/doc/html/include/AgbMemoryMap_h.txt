/********************************************************************/
/*          AgbMemoryMap.h                                          */
/*            AGB Memory Map Constants                              */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _AGB_MEMORY_MAP_H
#define _AGB_MEMORY_MAP_H

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------*/
/*                      Memory Map                                  */
/*------------------------------------------------------------------*/

#define BOOT_ROM                0x00000000          // Boot ROM
#define BOOT_ROM_END            (BOOT_ROM + 0x4000)
#define EX_WRAM                 0x02000000          // CPU External Work RAM
#define EX_WRAM_END             (EX_WRAM + 0x40000)
#define CPU_WRAM                0x03000000          // CPU Internal Work RAM
#define CPU_WRAM_END            (CPU_WRAM + 0x8000)
#define WRAM                     EX_WRAM            // Entire Work RAM
#define WRAM_END                 CPU_WRAM_END
#define SOUND_AREA_ADDR_BUF     (CPU_WRAM_END - 0x10)//Sound Driver Work Address
#define INTR_CHECK_BUF          (CPU_WRAM_END - 0x8)// Interrupt Check
#define INTR_VECTOR_BUF         (CPU_WRAM_END - 0x4)// Interrupt Branch Address
#define REG_BASE                0x04000000          // Registers
#define REG_END                 (REG_BASE +  0x300)
#define PLTT                    0x05000000          // Palette RAM
#define PLTT_END                (PLTT +      0x400)
#define BG_PLTT                 (PLTT +        0x0) // BG Palette RAM
#define BG_PLTT_END             (PLTT +      0x200)
#define OBJ_PLTT                (PLTT +      0x200) // OBJ Palette RAM
#define OBJ_PLTT_END            (PLTT +      0x400)
#define VRAM                    0x06000000          // VRAM
#define VRAM_END                (VRAM +    0x18000)
#define BG_VRAM                 (VRAM +        0x0) // BG Character/Screen RAM
#define BG_BITMAP0_VRAM         (VRAM +        0x0) // BG Bitmap 0 RAM
#define BG_BITMAP1_VRAM         (VRAM +     0xa000) // BG Bitmap 1 RAM
#define OBJ_MODE0_VRAM          (VRAM +    0x10000) // OBJ Character RAM
#define OBJ_MODE1_VRAM          (VRAM +    0x10000)
#define OBJ_MODE2_VRAM          (VRAM +    0x10000)
#define OBJ_MODE3_VRAM          (VRAM +    0x14000)
#define OBJ_MODE4_VRAM          (VRAM +    0x14000)
#define OBJ_MODE5_VRAM          (VRAM +    0x14000)
#define OBJ_VRAM_END            (VRAM +    0x18000)
#define OAM                     0x07000000          // OAM
#define OAM_END                 (OAM +       0x400)

#define ROM_BANK0               0x08000000          // ROM Bank 0
#define ROM_BANK0_END           0x0a000000
#define ROM_BANK1               0x0a000000          // ROM Bank 1
#define ROM_BANK1_END           0x0c000000
#define ROM_BANK2               0x0c000000          // ROM Bank 2
#define ROM_BANK2_END           0x0e000000
#define RAM_BANK                0x0c000000          // RAM Bank
#define RAM_BANK_END            0x10000000

#define FLASH_1M                0x09fe0000          // 1M Flash Memory
#define FLASH_1M_END            0x0a000000

/*------------------------------------------------------------------*/
/*                      Memory Size                                 */
/*------------------------------------------------------------------*/

#define BOOT_ROM_SIZE           0x4000              // Boot ROM
#define EX_WRAM_SIZE            0x40000             // CPU External Work RAM
#define CPU_WRAM_SIZE           0x8000              // CPU Internal Work RAM
#define WRAM_SIZE               0x48000             // Entire Work RAM
#define PLTT_SIZE               (2*256*2)           // Palette RAM
#define BG_PLTT_SIZE            (2*256)             // BG Palette RAM
#define OBJ_PLTT_SIZE           (2*256)             // OBJ Palette RAM
#define VRAM_SIZE               0x18000             // VRAM
#define BG_MODE0_VRAM_SIZE      0x10000             // BG Character/Screen
#define BG_MODE1_VRAM_SIZE      0x10000
#define BG_MODE2_VRAM_SIZE      0x10000
#define BG_MODE3_VRAM_SIZE      0x14000             // BG Bitmap
#define BG_MODE4_VRAM_SIZE      0x0a000
#define BG_MODE5_VRAM_SIZE      0x0a000
#define OBJ_MODE0_VRAM_SIZE     0x08000             // OBJ Character
#define OBJ_MODE1_VRAM_SIZE     0x08000
#define OBJ_MODE2_VRAM_SIZE     0x08000
#define OBJ_MODE3_VRAM_SIZE     0x04000
#define OBJ_MODE4_VRAM_SIZE     0x04000
#define OBJ_MODE5_VRAM_SIZE     0x04000
#define OAM_SIZE                (8*128)             // OAM

#define ROM_BANK_SIZE           0x02000000          // ROM Bank
#define ROM_BANK0_SIZE          0x02000000          // ROM Bank 0
#define ROM_BANK1_SIZE          0x02000000          // ROM Bank 1
#define ROM_BANK2_SIZE          0x02000000          // ROM Bank 2
#define RAM_BANK_SIZE           0x02000000          // RAM Bank

#define FLASH_1M_SIZE           0x20000             // 1M Flash Memory

/*------------------------------------------------------------------*/
/*                      Register Address                            */
/*------------------------------------------------------------------*/

#define REG_IME         (REG_BASE + 0x208)  // Interrupt Master Enable
#define REG_IE          (REG_BASE + 0x200)  // Interrupt Enable
#define REG_IF          (REG_BASE + 0x202)  // Interrupt Request

#define REG_WAITCNT     (REG_BASE + 0x204)  // Game Pak Wait Control

#define REG_DISPCNT     (REG_BASE + 0x0)    // Display Control

#define REG_STAT        (REG_BASE + 0x4)    // Status
#define REG_VCOUNT      (REG_BASE + 0x6)    // V Counter

#define REG_MOSAIC      (REG_BASE + 0x4c)   // Mosaic Size

#define REG_BLDCNT      (REG_BASE + 0x50)   // Blend Mode Control
#define REG_BLDALPHA    (REG_BASE + 0x52)   // Semi-transparent Parameter
#define REG_BLDY        (REG_BASE + 0x54)   // Brightness Change Parameter

#define REG_WINCNT      (REG_BASE + 0x40)   // Window Control
#define REG_WIN0H       (REG_BASE + 0x40)   // Window 0 Horizontal Area
#define REG_WIN1H       (REG_BASE + 0x42)   // Window 1 Horizontal Area
#define REG_WIN0V       (REG_BASE + 0x44)   // Window 0 Vertical Area
#define REG_WIN1V       (REG_BASE + 0x46)   // WIndow 1 Vertical Area
#define REG_WININ       (REG_BASE + 0x48)   // Internal Window Control
#define REG_WIN0        (REG_BASE + 0x48)   // Window 0 Control
#define REG_WIN1        (REG_BASE + 0x49)   // Window 1 Control
#define REG_WINOUT      (REG_BASE + 0x4a)   // External Window Control
#define REG_OBJWIN      (REG_BASE + 0x4b)   // OBJ Window Control


#define REG_BGCNT       (REG_BASE + 0x8)    // BG Control
#define REG_BG0CNT      (REG_BASE + 0x8)    // BG 0 Control
#define REG_BG1CNT      (REG_BASE + 0xa)    // BG 1 Control
#define REG_BG2CNT      (REG_BASE + 0xc)    // BG 2 Control
#define REG_BG3CNT      (REG_BASE + 0xe)    // BG 3 Control
#define REG_BGOFS       (REG_BASE + 0x10)   // BG Offset
#define REG_BG0HOFS     (REG_BASE + 0x10)   // BG 0 H Offset
#define REG_BG0VOFS     (REG_BASE + 0x12)   // BG 0 V Offset
#define REG_BG1HOFS     (REG_BASE + 0x14)   // BG 1 H Offset
#define REG_BG1VOFS     (REG_BASE + 0x16)   // BG 1 V Offset
#define REG_BG2HOFS     (REG_BASE + 0x18)   // BG 2 H Offset
#define REG_BG2VOFS     (REG_BASE + 0x1a)   // BG 2 V Offset
#define REG_BG3HOFS     (REG_BASE + 0x1c)   // BG 3 H Offset
#define REG_BG3VOFS     (REG_BASE + 0x1e)   // BG 3 V Offset
#define REG_BG2AFFINE   (REG_BASE + 0x20)   // BG 2 Affin Transformation Parameters
#define REG_BG2PA       (REG_BASE + 0x20)   // BG 2 Line Direction X Coordinate Difference
#define REG_BG2PB       (REG_BASE + 0x22)   // BG 3 Vertical Direction X Coordinate Difference
#define REG_BG2PC       (REG_BASE + 0x24)   // BG 2 Line Direction Y coordinate Difference
#define REG_BG2PD       (REG_BASE + 0x26)   // BG 2 Vertical Direction Y Coordinate Difference
#define REG_BG2X        (REG_BASE + 0x28)   // BG 2 Start X Coordinate
#define REG_BG2X_L      (REG_BASE + 0x28)
#define REG_BG2X_H      (REG_BASE + 0x2a)
#define REG_BG2Y        (REG_BASE + 0x2c)   // BG 2 Start Y Coordinate
#define REG_BG2Y_L      (REG_BASE + 0x2c)
#define REG_BG2Y_H      (REG_BASE + 0x2e)
#define REG_BG3AFFINE   (REG_BASE + 0x30)   // BG 3 Affin Transformation Parameters
#define REG_BG3PA       (REG_BASE + 0x30)   // BG 3 Line Direction X Coordinate Difference
#define REG_BG3PB       (REG_BASE + 0x32)   // BG 3 Vertical Direction X Coordinate Difference
#define REG_BG3PC       (REG_BASE + 0x34)   // BG 3 Line Direction Y Coordinate Difference
#define REG_BG3PD       (REG_BASE + 0x36)   // BG 3 Vertical Direction Y Coordinate Difference
#define REG_BG3X        (REG_BASE + 0x38)   // BG 3 Start X Coordinate
#define REG_BG3X_L      (REG_BASE + 0x38)
#define REG_BG3X_H      (REG_BASE + 0x3a)
#define REG_BG3Y        (REG_BASE + 0x3c)   // BG 3 Start Y Coordinate
#define REG_BG3Y_L      (REG_BASE + 0x3c)
#define REG_BG3Y_H      (REG_BASE + 0x3e)


#define REG_SOUNDCNT    (REG_BASE + 0x80)   // Sound Control
#define REG_SOUNDCNT_L  (REG_BASE + 0x80)
#define REG_SOUNDCNT_H  (REG_BASE + 0x82)
#define REG_SOUNDCNT_X  (REG_BASE + 0x84)

#define REG_SOUNDBIAS   (REG_BASE + 0x88)   // Sound BIAS

#define REG_SOUND1CNT   (REG_BASE + 0x60)   // Sound 1 Control
#define REG_SOUND1CNT_L (REG_BASE + 0x60)
#define REG_SOUND1CNT_H (REG_BASE + 0x62)
#define REG_SOUND1CNT_X (REG_BASE + 0x64)
#define REG_SOUND2CNT   (REG_BASE + 0x68)   // Sound 2 Control
#define REG_SOUND2CNT_L (REG_BASE + 0x68)
#define REG_SOUND2CNT_H (REG_BASE + 0x6c)
#define REG_SOUND3CNT   (REG_BASE + 0x70)   // Sound 3 Control
#define REG_SOUND3CNT_L (REG_BASE + 0x70)
#define REG_SOUND3CNT_H (REG_BASE + 0x72)
#define REG_SOUND3CNT_X (REG_BASE + 0x74)
#define REG_SOUND4CNT   (REG_BASE + 0x78)   // Sound 4 Control
#define REG_SOUND4CNT_L (REG_BASE + 0x78)
#define REG_SOUND4CNT_H (REG_BASE + 0x7c)

#define REG_WAVE_RAM    (REG_BASE + 0x90)   // Sound 3 Waveform RAM
#define REG_WAVE_RAM0   (REG_BASE + 0x90)
#define REG_WAVE_RAM0_L (REG_BASE + 0x90)
#define REG_WAVE_RAM0_H (REG_BASE + 0x92)
#define REG_WAVE_RAM1   (REG_BASE + 0x94)
#define REG_WAVE_RAM1_L (REG_BASE + 0x94)
#define REG_WAVE_RAM1_H (REG_BASE + 0x96)
#define REG_WAVE_RAM2   (REG_BASE + 0x98)
#define REG_WAVE_RAM2_L (REG_BASE + 0x98)
#define REG_WAVE_RAM2_H (REG_BASE + 0x9a)
#define REG_WAVE_RAM3   (REG_BASE + 0x9c)
#define REG_WAVE_RAM3_L (REG_BASE + 0x9c)
#define REG_WAVE_RAM3_H (REG_BASE + 0x9e)

#define REG_FIFO        (REG_BASE + 0xa0)   // Sound FIFO
#define REG_FIFO_A      (REG_BASE + 0xa0)
#define REG_FIFO_A_L    (REG_BASE + 0xa0)
#define REG_FIFO_A_H    (REG_BASE + 0xa2)
#define REG_FIFO_B      (REG_BASE + 0xa4)
#define REG_FIFO_B_L    (REG_BASE + 0xa4)
#define REG_FIFO_B_H    (REG_BASE + 0xa6)


#define REG_DMA0        (REG_BASE + 0xb0)   // DMA 0
#define REG_DMA0SAD     (REG_BASE + 0xb0)   // (Internal Memory -> Internal Memory)
#define REG_DMA0SAD_L   (REG_BASE + 0xb0)
#define REG_DMA0SAD_H   (REG_BASE + 0xb2)
#define REG_DMA0DAD     (REG_BASE + 0xb4)
#define REG_DMA0DAD_L   (REG_BASE + 0xb4)
#define REG_DMA0DAD_H   (REG_BASE + 0xb6)
#define REG_DMA0CNT     (REG_BASE + 0xb8)
#define REG_DMA0CNT_L   (REG_BASE + 0xb8)
#define REG_DMA0CNT_H   (REG_BASE + 0xba)
#define REG_DMA1        (REG_BASE + 0xbc)   // DMA 1
#define REG_DMA1SAD     (REG_BASE + 0xbc)   // (Internal Memory -> Sound FIFO/Internal Memory)
#define REG_DMA1SAD_L   (REG_BASE + 0xbc)
#define REG_DMA1SAD_H   (REG_BASE + 0xbe)
#define REG_DMA1DAD     (REG_BASE + 0xc0)
#define REG_DMA1DAD_L   (REG_BASE + 0xc0)
#define REG_DMA1DAD_H   (REG_BASE + 0xc2)
#define REG_DMA1CNT     (REG_BASE + 0xc4)
#define REG_DMA1CNT_L   (REG_BASE + 0xc4)
#define REG_DMA1CNT_H   (REG_BASE + 0xc6)
#define REG_DMA2        (REG_BASE + 0xc8)   // DMA 2
#define REG_DMA2SAD     (REG_BASE + 0xc8)   // (Internal Memory -> Sound FIFO/Internal Memory)
#define REG_DMA2SAD_L   (REG_BASE + 0xc8)
#define REG_DMA2SAD_H   (REG_BASE + 0xca)
#define REG_DMA2DAD     (REG_BASE + 0xcc)
#define REG_DMA2DAD_L   (REG_BASE + 0xcc)
#define REG_DMA2DAD_H   (REG_BASE + 0xce)
#define REG_DMA2CNT     (REG_BASE + 0xd0)
#define REG_DMA2CNT_L   (REG_BASE + 0xd0)
#define REG_DMA2CNT_H   (REG_BASE + 0xd2)
#define REG_DMA3        (REG_BASE + 0xd4)   // DMA 3
#define REG_DMA3SAD     (REG_BASE + 0xd4)   // (Game Pak/Internal Memory <--> Internal Memory)
#define REG_DMA3SAD_L   (REG_BASE + 0xd4)
#define REG_DMA3SAD_H   (REG_BASE + 0xd6)
#define REG_DMA3DAD     (REG_BASE + 0xd8)
#define REG_DMA3DAD_L   (REG_BASE + 0xd8)
#define REG_DMA3DAD_H   (REG_BASE + 0xda)
#define REG_DMA3CNT     (REG_BASE + 0xdc)
#define REG_DMA3CNT_L   (REG_BASE + 0xdc)
#define REG_DMA3CNT_H   (REG_BASE + 0xde)


#define REG_TM0CNT      (REG_BASE + 0x100)  // Timer 0
#define REG_TM0CNT_L    (REG_BASE + 0x100)
#define REG_TM0CNT_H    (REG_BASE + 0x102)
#define REG_TM1CNT      (REG_BASE + 0x104)  // Timer 1
#define REG_TM1CNT_L    (REG_BASE + 0x104)
#define REG_TM1CNT_H    (REG_BASE + 0x106)
#define REG_TM2CNT      (REG_BASE + 0x108)  // Timer 2
#define REG_TM2CNT_L    (REG_BASE + 0x108)
#define REG_TM2CNT_H    (REG_BASE + 0x10a)
#define REG_TM3CNT      (REG_BASE + 0x10c)  // Timer 3
#define REG_TM3CNT_L    (REG_BASE + 0x10c)
#define REG_TM3CNT_H    (REG_BASE + 0x10e)


#define REG_RCNT        (REG_BASE + 0x134)  // General Input/Output Control

#define REG_SIOCNT      (REG_BASE + 0x128)  // Serial Communication Control
#define REG_SIODATA8    (REG_BASE + 0x12a)  // 8bit Serial Communication Data
#define REG_SIODATA32   (REG_BASE + 0x120)  // 32bit Serial Communication Data
#define REG_SIOMLT_RECV (REG_BASE + 0x120)  // Multi-play SIO Receive Data
#define REG_SIOMULTI0   (REG_BASE + 0x120)
#define REG_SIOMULTI1   (REG_BASE + 0x122)
#define REG_SIOMULTI2   (REG_BASE + 0x124)
#define REG_SIOMULTI3   (REG_BASE + 0x126)

#define REG_JOYCNT      (REG_BASE + 0x140)  // JOY Bus Communication Control
#define REG_JOYSTAT     (REG_BASE + 0x158)  // JOY Bus Status
#define REG_JOY_RECV    (REG_BASE + 0x150)  // JOY Bus Receive Data
#define REG_JOY_RECV_L  (REG_BASE + 0x150)
#define REG_JOY_RECV_H  (REG_BASE + 0x152)
#define REG_JOY_TRANS   (REG_BASE + 0x154)  // JOY Bus Send Data
#define REG_JOY_TRANS_L (REG_BASE + 0x154)
#define REG_JOY_TRANS_H (REG_BASE + 0x156)


#define REG_KEYINPUT    (REG_BASE + 0x130)  // Key Input
#define REG_KEYCNT      (REG_BASE + 0x132)  // Key Control


/*------------------------------------------------------------------*/
/*                      Register Offset                             */
/*------------------------------------------------------------------*/

#define OFFSET_REG_IME          0x208       // Interrupt Master Enable
#define OFFSET_REG_IE           0x200       // Interrupt Enable
#define OFFSET_REG_IF           0x202       // Interrupt Request

#define OFFSET_REG_WAITCNT      0x204       // Game Pak Wait Control

#define OFFSET_REG_DISPCNT      0x0         // Display Control

#define OFFSET_REG_STAT         0x4         // Status
#define OFFSET_REG_VCOUNT       0x6         // V Counter

#define OFFSET_REG_MOSAIC       0x4c        // Mosaic Size

#define OFFSET_REG_BLDCNT       0x50        // Blend Mode Control
#define OFFSET_REG_BLDALPHA     0x52        // Semi-trams[aremt Parameter
#define OFFSET_REG_BLDY         0x54        // Brightness Change Parameter

#define OFFSET_REG_WINCNT       0x40        // Window Control
#define OFFSET_REG_WIN0H        0x40        // Window 0 Horizontal Area
#define OFFSET_REG_WIN1H        0x42        // Window 1 Horizontal Area
#define OFFSET_REG_WIN0V        0x44        // Window 0 Vertical Area
#define OFFSET_REG_WIN1V        0x46        // Window 1 Vertical Area
#define OFFSET_REG_WININ        0x48        // Internal Window Control
#define OFFSET_REG_WIN0         0x48        // Window 0 Control
#define OFFSET_REG_WIN1         0x49        // Window 1 Control
#define OFFSET_REG_WINOUT       0x4a        // External Window Control
#define OFFSET_REG_OBJWIN       0x4b        // OBJ Window Control


#define OFFSET_REG_BGCNT        0x8         // BG Control
#define OFFSET_REG_BG0CNT       0x8         // BG 0 Control
#define OFFSET_REG_BG1CNT       0xa         // BG 1 Control
#define OFFSET_REG_BG2CNT       0xc         // BG 2 Control
#define OFFSET_REG_BG3CNT       0xe         // BG 3 Control
#define OFFSET_REG_BGOFS        0x10        // BG Offset
#define OFFSET_REG_BG0HOFS      0x10        // BG 0 H Offset
#define OFFSET_REG_BG0VOFS      0x12        // BG 0 V Offset
#define OFFSET_REG_BG1HOFS      0x14        // BG 1 H Offset
#define OFFSET_REG_BG1VOFS      0x16        // BG 1 V Offset
#define OFFSET_REG_BG2HOFS      0x18        // BG 2 H Offset
#define OFFSET_REG_BG2VOFS      0x1a        // BG 2 V Offset
#define OFFSET_REG_BG3HOFS      0x1c        // BG 3 H Offset
#define OFFSET_REG_BG3VOFS      0x1e        // BG 3 V Offset
#define OFFSET_REG_BG2AFFINE    0x20        // BG 2 Affin Transformation Parameters
#define OFFSET_REG_BG2PA        0x20        // BG 2 Line Direction X Coordinate Difference
#define OFFSET_REG_BG2PB        0x22        // BG 2 Vertical Direction X Coordinate Difference
#define OFFSET_REG_BG2PC        0x24        // BG 2 Line Direction Y Coordinate Difference
#define OFFSET_REG_BG2PD        0x26        // BG 2 Vertical Direction Y Coordinate Difference
#define OFFSET_REG_BG2X         0x28        // BG 2 Start X Coordinate
#define OFFSET_REG_BG2X_L       0x28
#define OFFSET_REG_BG2X_H       0x2a
#define OFFSET_REG_BG2Y         0x2c        // BG 2 Start Y Coordinate
#define OFFSET_REG_BG2Y_L       0x2c
#define OFFSET_REG_BG2Y_H       0x2e
#define OFFSET_REG_BG3AFFINE    0x30        // BG 3 Affin Transformation Parameters
#define OFFSET_REG_BG3PA        0x30        // BG 3 Line Direction X Coordinate Difference
#define OFFSET_REG_BG3PB        0x32        // BG 3 Vertical Direction X Coordinate Difference
#define OFFSET_REG_BG3PC        0x34        // BG 3 Line Direction Y Coordinate Difference
#define OFFSET_REG_BG3PD        0x36        // BG 3 Vertical Direction Y Coordinate Difference
#define OFFSET_REG_BG3X         0x38        // BG 3 Start X Coordinate
#define OFFSET_REG_BG3X_L       0x38
#define OFFSET_REG_BG3X_H       0x3a
#define OFFSET_REG_BG3Y         0x3c        // BG 3 Start Y Coordinate
#define OFFSET_REG_BG3Y_L       0x3c
#define OFFSET_REG_BG3Y_H       0x3e


#define OFFSET_REG_SOUNDCNT     0x80        // Sound Control
#define OFFSET_REG_SOUNDCNT_L   0x80
#define OFFSET_REG_SOUNDCNT_H   0x82
#define OFFSET_REG_SOUNDCNT_X   0x84

#define OFFSET_REG_SOUNDBIAS    0x88        // Sound BIAS

#define OFFSET_REG_SOUND1CNT    0x60        // Sound 1 Control
#define OFFSET_REG_SOUND1CNT_L  0x60
#define OFFSET_REG_SOUND1CNT_H  0x62
#define OFFSET_REG_SOUND1CNT_X  0x64
#define OFFSET_REG_SOUND2CNT    0x68        // Sound 2 Control
#define OFFSET_REG_SOUND2CNT_L  0x68
#define OFFSET_REG_SOUND2CNT_H  0x6c
#define OFFSET_REG_SOUND3CNT    0x70        // Sound 3 Control
#define OFFSET_REG_SOUND3CNT_L  0x70
#define OFFSET_REG_SOUND3CNT_H  0x72
#define OFFSET_REG_SOUND3CNT_X  0x74
#define OFFSET_REG_SOUND4CNT    0x78        // Sound 4 Control
#define OFFSET_REG_SOUND4CNT_L  0x78
#define OFFSET_REG_SOUND4CNT_H  0x7c

#define OFFSET_REG_WAVE_RAM     0x90        // Sound 3 Waveform RAM
#define OFFSET_REG_WAVE_RAM0    0x90
#define OFFSET_REG_WAVE_RAM0_L  0x90
#define OFFSET_REG_WAVE_RAM0_H  0x92
#define OFFSET_REG_WAVE_RAM1    0x94
#define OFFSET_REG_WAVE_RAM1_L  0x94
#define OFFSET_REG_WAVE_RAM1_H  0x96
#define OFFSET_REG_WAVE_RAM2    0x98
#define OFFSET_REG_WAVE_RAM2_L  0x98
#define OFFSET_REG_WAVE_RAM2_H  0x9a
#define OFFSET_REG_WAVE_RAM3    0x9c
#define OFFSET_REG_WAVE_RAM3_L  0x9c
#define OFFSET_REG_WAVE_RAM3_H  0x9e

#define OFFSET_REG_FIFO         0xa0        // Sound FIFO
#define OFFSET_REG_FIFO_A       0xa0
#define OFFSET_REG_FIFO_A_L     0xa0
#define OFFSET_REG_FIFO_A_H     0xa2
#define OFFSET_REG_FIFO_B       0xa4
#define OFFSET_REG_FIFO_B_L     0xa4
#define OFFSET_REG_FIFO_B_H     0xa6


#define OFFSET_REG_DMA0         0xb0        // DMA 0
#define OFFSET_REG_DMA0SAD      0xb0        // (Internal Memory -> Internal Memory)
#define OFFSET_REG_DMA0SAD_L    0xb0
#define OFFSET_REG_DMA0SAD_H    0xb2
#define OFFSET_REG_DMA0DAD      0xb4
#define OFFSET_REG_DMA0DAD_L    0xb4
#define OFFSET_REG_DMA0DAD_H    0xb6
#define OFFSET_REG_DMA0CNT      0xb8
#define OFFSET_REG_DMA0CNT_L    0xb8
#define OFFSET_REG_DMA0CNT_H    0xba
#define OFFSET_REG_DMA1         0xbc        // DMA 1
#define OFFSET_REG_DMA1SAD      0xbc        // (Internal Memory -> Sound FIFO/Internal Memory)
#define OFFSET_REG_DMA1SAD_L    0xbc
#define OFFSET_REG_DMA1SAD_H    0xbe
#define OFFSET_REG_DMA1DAD      0xc0
#define OFFSET_REG_DMA1DAD_L    0xc0
#define OFFSET_REG_DMA1DAD_H    0xc2
#define OFFSET_REG_DMA1CNT      0xc4
#define OFFSET_REG_DMA1CNT_L    0xc4
#define OFFSET_REG_DMA1CNT_H    0xc6
#define OFFSET_REG_DMA2         0xc8        // DMA 2
#define OFFSET_REG_DMA2SAD      0xc8        // (Internal Memory -> Sound FIFO/Internal Memory)
#define OFFSET_REG_DMA2SAD_L    0xc8
#define OFFSET_REG_DMA2SAD_H    0xca
#define OFFSET_REG_DMA2DAD      0xcc
#define OFFSET_REG_DMA2DAD_L    0xcc
#define OFFSET_REG_DMA2DAD_H    0xce
#define OFFSET_REG_DMA2CNT      0xd0
#define OFFSET_REG_DMA2CNT_L    0xd0
#define OFFSET_REG_DMA2CNT_H    0xd2
#define OFFSET_REG_DMA3         0xd4        // DMA 3
#define OFFSET_REG_DMA3SAD      0xd4        // (Game Pak/Internal Memory <--> Internal Memory)
#define OFFSET_REG_DMA3SAD_L    0xd4
#define OFFSET_REG_DMA3SAD_H    0xd6
#define OFFSET_REG_DMA3DAD      0xd8
#define OFFSET_REG_DMA3DAD_L    0xd8
#define OFFSET_REG_DMA3DAD_H    0xda
#define OFFSET_REG_DMA3CNT      0xdc
#define OFFSET_REG_DMA3CNT_L    0xdc
#define OFFSET_REG_DMA3CNT_H    0xde


#define OFFSET_REG_TM0CNT       0x100       // Timer 0
#define OFFSET_REG_TM0CNT_L     0x100
#define OFFSET_REG_TM0CNT_H     0x102
#define OFFSET_REG_TM1CNT       0x104       // Timer 1
#define OFFSET_REG_TM1CNT_L     0x104
#define OFFSET_REG_TM1CNT_H     0x106
#define OFFSET_REG_TM2CNT       0x108       // Timer 2
#define OFFSET_REG_TM2CNT_L     0x108
#define OFFSET_REG_TM2CNT_H     0x10a
#define OFFSET_REG_TM3CNT       0x10c       // Timer 3
#define OFFSET_REG_TM3CNT_L     0x10c
#define OFFSET_REG_TM3CNT_H     0x10e


#define OFFSET_REG_RCNT         0x134       // General Input/Output Control

#define OFFSET_REG_SIOCNT       0x128       // Serial Communication Control
#define OFFSET_REG_SIODATA8     0x12a       // 8 bit Serial Communication Data
#define OFFSET_REG_SIODATA32    0x120       // 32 bit Serial Communication Data
#define OFFSET_REG_SIOMLT_RECV  0x120       // Multi-play SIO Receive Data
#define OFFSET_REG_SIOMULTI0    0x120
#define OFFSET_REG_SIOMULTI1    0x122
#define OFFSET_REG_SIOMULTI2    0x124
#define OFFSET_REG_SIOMULTI3    0x126

#define OFFSET_REG_JOYCNT       0x140       // JOY Bus Communication Control
#define OFFSET_REG_JOYSTAT      0x158       // JOY Bus Status
#define OFFSET_REG_JOY_RECV     0x150       // JOY Bus Receive Data
#define OFFSET_REG_JOY_RECV_L   0x150
#define OFFSET_REG_JOY_RECV_H   0x152
#define OFFSET_REG_JOY_TRANS    0x154       // JOY Bus Send Data
#define OFFSET_REG_JOY_TRANS_L  0x154
#define OFFSET_REG_JOY_TRANS_H  0x156


#define OFFSET_REG_KEYINPUT     0x130       // Key Input
#define OFFSET_REG_KEYCNT       0x132       // Key Control


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* _AGB_MEMORY_MAP_H */
