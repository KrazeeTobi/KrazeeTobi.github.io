/********************************************************************/
/*          main.c                                                  */
/*            multi_boot (Multi-play Boot Sample) Main		    */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "MultiBoot.h"
#include "MultiSio.h"
#include "types.h"
#include "data.h"


/*-------------------- Global Variables  ----------------------------*/

extern u16      Cont, Trg;                  // Key Input

extern u32      IntrMainBuf[0x100];         // Interrupt main routine buffer

MultiBootParam  multiboot_status;
u8             *demo_bin_start;  // Start address of the client program that is to be downloaded
u32             demo_bin_length; // Size of the client program that is to be downloaded
int             frame_retval;

const u8 * const BgScDatap_ID[] = {"", "2P", "3P", "4P", };

/*---------------------- Subroutine  -----------------------------*/

extern void DemoMain(void);
extern void KeyRead(void);

void BgScSet(u8 *Srcp, u16 *Destp, u8 PlttNo);


/*------------------------------------------------------------------*/
/*                      Interrupt Table                            */
/*------------------------------------------------------------------*/

extern IntrFuncp IntrTable[14];
extern IntrFuncp IntrTableBuf[14];


/*==================================================================*/
/*                      Main Routine                              */
/*==================================================================*/
extern void intr_main(void);

extern u8 _binary_client_bin_start[], _binary_client_bin_end[]; // Defines with client.o

void AgbMain(void)
{
    s32    i;
    char  *StrTmp;
    char   StrTmpBuf[64];

    DmaClear(3, 0,   EX_WRAM,  EX_WRAM_SIZE,            32);// Clears CPU external work RAM
    DmaClear(3, 0,   CPU_WRAM, CPU_WRAM_SIZE - 0x200,   32);// Clears CPU internal work RAM
//  DmaClear(3, 0,   VRAM,     VRAM_SIZE,               32);//     Clears VRAM
//  DmaClear(3, 160, OAM,      OAM_SIZE,                32);//      Clears OAM
//  DmaClear(3, 0,   PLTT,     PLTT_SIZE,               32);// Clears palette

    DmaCopy(3, IntrTable, IntrTableBuf,sizeof(IntrTableBuf),32);// Sets interrupt table
    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// Sets interrupt main routine
    *(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, CharData_Sample,    BG_VRAM+0x8000, 32);//  Sets BG characters
    DmaArrayCopy(3, CharData_Sample,    OBJ_MODE0_VRAM, 32);// Sets OBJ characters
    DmaArrayCopy(3, PlttData_Sample,    BG_PLTT,        32);//  Sets BG palette
    DmaArrayCopy(3, PlttData_Sample,    OBJ_PLTT,       32);// Sets OBJ palette

    DmaArrayCopy(3, BgScData_Sample,    BG_VRAM,        32);// Sets BG screen

    *(vu16 *)REG_BG0CNT =                                   // Sets BG control
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
    *(vu16 *)REG_BG1CNT =
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 1 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_IE    = V_BLANK_INTR_FLAG;                 // Enables V-blank interrupt 
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;
    *(vu16 *)REG_IME   = 1;                                 // Sets IME

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON; // LCDC ON

    demo_bin_start = _binary_client_bin_start;
    demo_bin_length = (u32)_binary_client_bin_end - (u32)_binary_client_bin_start;

    multiboot_status.masterp = demo_bin_start;
    MultiBootInit(&multiboot_status);               // Initializes multi-play boot

    while (1) {
        VBlankIntrWait();                           // Waits for V-blank interrupt to end

        for (i = 1; i < 4; i++) {
            if ((multiboot_status.response_bit & (1 << i)) == 0) {
                        StrTmp = "Not connected";
            } else {
                if ((multiboot_status.client_bit & (1 << i)) == 0)
                        StrTmp = "Checking...  ";
                else    StrTmp = "Ready        ";
            }
            BgScSet((u8 *)BgScDatap_ID[i], &((u16 *)BG_VRAM)[32*(5+i)+ 7], 3);
            BgScSet(StrTmp,                &((u16 *)BG_VRAM)[32*(5+i)+10], 3);
        }

        if (multiboot_status.client_bit  & 0xe)
            switch (multiboot_status.probe_count) {
                case 0x00: StrTmp = "PUSH START    ";   break;
                case 0xfe: StrTmp = "NOW SENDING...";   break;
                default:   StrTmp = "              ";   break;
             }
		else               StrTmp = "              ";
        BgScSet(StrTmp, &((u16 *)BG_VRAM)[32*(7+i)+ 7], 1);

        KeyRead();

        if (Trg & START_BUTTON) {
            MultiBootStartMaster(&multiboot_status,     // Starts transferring multi-play boot
                                 &demo_bin_start[MULTIBOOT_HEADER_SIZE],
                                  demo_bin_length - MULTIBOOT_HEADER_SIZE,
                                  4, 1);
        }
        frame_retval = MultiBootMain(&multiboot_status);// Multi-play boot main
		if (MultiBootCheckComplete(&multiboot_status))  // Checks if transfer of multi-play boot has ended.
                break;
    }

    *(vu16 *)REG_IME = 0;                           // Resets IME
    *(vu16 *)REG_IF  = 0xffff;                      // Resets IF
    *(vu16 *)REG_DISPCNT = DISP_LCDC_OFF;

    DemoMain();										// Start demonstration program
}


/*==================================================================*/
/*                      Subroutine                                */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*     					Sets BG screen					    */
/*------------------------------------------------------------------*/

void BgScSet(u8 *Srcp, u16 *Destp, u8 PlttNo)
{
	while (*Srcp != '\0')
		*Destp++ = (u16 )PlttNo << BG_SC_PLTT_SHIFT | *Srcp++;
}


