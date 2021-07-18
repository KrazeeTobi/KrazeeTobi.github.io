//--------------------------------------//
// Inspired from AGB Header by Nokturn  //
//--------------------------------------//

 // Some types.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

typedef struct _Sprite { u16 Attrib0, Attrib1, Attrib2, RotateScale; } Sprite;

 // Registers
#define DISPCNT		*(u32*)0x04000000
#define DISPSTAT	*(u16*)0x04000004
#define VCOUNT		*(u16*)0x04000006
#define BG0CNT		*(u16*)0x04000008
#define BG1CNT     	*(u16*)0x0400000A
#define BG2CNT     	*(u16*)0x0400000C
#define BG3CNT     	*(u16*)0x0400000E
#define BG0HOFS		*(u16*)0x04000010
#define BG0VOFS		*(u16*)0x04000012
#define MOSAIC		*(u16*)0x0400004C
#define P1			*(u16*)0x04000130
#define DMA3SAD		*(u32*)0x040000d4
#define DMA3DAD		*(u32*)0x040000d8
#define DMA3CNT		*(u32*)0x040000dc
#define DISPLAY_Y   *(u32*)0x04000006

	//bkg scaling starting points
#define	BG2X_L	*(u16*)0x04000028
#define	BG2X_H	*(u16*)0x0400002A
#define	BG2Y_L	*(u16*)0x0400002C
#define	BG2Y_H	*(u16*)0x0400002E
	//bkg scaling movement
#define	BG2PA		*(u16*)0x04000020
#define	BG2PB		*(u16*)0x04000022
#define	BG2PC		*(u16*)0x04000024
#define	BG2PD		*(u16*)0x04000026


#define BG_PLTT		((u16*)0x05000000)
#define OBJ_PLTT	((u16*)0x05000200)

#define VBUFFER		((u16*)0x06000000)
#define OBJCHARDATA	((u8*)0x06010000)
#define OAM		((Sprite*)0x07000000)




 // Function to wait for Vertical Sync. I took Eloist's ASM Version
void WaitForVSync()
{
  __asm
   {
    mov 	r0, #0x4000006
    scanline_wait:
     ldrh	r1, [r0]
     cmp	r1, #160
    bne 	scanline_wait
   }
}

#define J_A		0x0001
#define J_B		0x0002
#define J_SELECT	0x0004
#define J_START		0x0008
#define J_RIGHT		0x0010
#define J_LEFT		0x0020
#define J_UP		0x0040
#define J_DOWN		0x0080
#define J_R		0x0100
#define J_L		0x0200

#define key_reg	(*(u16*)0x04000130)
u16 joypad() 	
{
	u16 j=P1;
	P1 |= 0x03FF;
	return j;
}

#define BIT00 1
#define BIT01 2
#define BIT02 4
#define BIT03 8
#define BIT04 16
#define BIT05 32
#define BIT06 64
#define BIT07 128
#define BIT08 256
#define BIT09 512

