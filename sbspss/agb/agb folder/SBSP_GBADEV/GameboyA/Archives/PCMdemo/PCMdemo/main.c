/****************************************************************/
/*                      main.c for PCM-demo                     */
/****************************************************************/
//#define CODE32
#include "data.h"
#include "sound.h"

/*-------------------- Global variables  -----------------------*/

    vu16    IntrCheck;
    u16     Cont, Trg;
    u32     IntrMainBuf[0x200];
    u16     BgBak[32*32];
    OamData OamBak[128];


/*---------------------- Subroutines  --------------------------*/

void KeyRead(void);
void ObjSnakeMove(void);


/*--------------------------------------------------------------*/
/*            Interrupt table                */
/*--------------------------------------------------------------*/
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[15] = {
    VBlankIntr,   IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,    IntrDummy,
    soundDmaIrq,  IntrDummy,
    IntrDummy,    IntrDummy,
    IntrDummy,
};


/*==============================================================*/
/*            Main routine                */
/*==============================================================*/
extern void intr_main(void);

#ifdef    __GNUC__
int main(void)
#else
void AgbMain(void)
#endif
{
    u8    i;

    DmaClear(3, 0, WRAM, USR_BUF_SIZE - 4*64, 32);

    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 16);
    IntrAddrSet(IntrMainBuf);

    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 16);
    DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 16);
    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        16);
    DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       16);

    DmaArrayCopy(3, BgScData_Sample, BgBak,   16);
    DmaArrayCopy(3, BgBak,           BG_VRAM, 16);
    DmaArrayCopy(3, OamData_Sample,  OamBak,  16);
    for (i=0; i<128; i++) {
        OamBak[i] = *(OamData *)OamData_Sample;
        OamBak[i].CharNo = i+0x80;
        OamBak[i].VPos += i<<2;
        OamBak[i].HPos += i<<2;
    }
    DmaArrayCopy(3, OamBak, OAM, 32);

    *(vu16 *)REG_BG0CNT =    
              BG_COLOR_16
            | BG_SCREEN_SIZE_0
            | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT
            | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_IE    = IME_FLAG | V_BLANK_INTR_FLAG | DMA2_INTR_FLAG;
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;

    *(vu16 *)REG_DISPCNT =
              DISP_MODE_0
            | DISP_OBJ_ON
            | DISP_BG0_ON;        // LCDC ON

    while(1) {
        KeyRead();
        // If A button is pressed, Initialize and start PCM sound
        if (Trg & A_BUTTON)

// Calling Sound Start Routine here
            soundStart();
        // If B button is pressed, Stop PCM sound
        if (Trg & B_BUTTON)

// CAlling Sound stop routine here
            soundStop();
        if (Cont & PLUS_KEY_MASK)
            ObjSnakeMove();

        IntrCheck &= V_BLANK_INTR_FLAG ^ 0xffff;
        while (1) {

// Never use HALT during playing PCM
//            Halt();
            if (IntrCheck & V_BLANK_INTR_FLAG)
                break;
        }
    }
}


/*--------------------------------------------------------------*/
/*        Vblank interrupt routine            */
/*--------------------------------------------------------------*/

void VBlankIntr(void)
{
    DmaArrayCopy(3, BgBak,  BG_VRAM, 16);
    DmaArrayCopy(3, OamBak, OAM,     32);

    IntrCheck = V_BLANK_INTR_FLAG;

// Call this function at the end of V-blank routine every time
    soundVblank();
}

/*--------------------------------------------------------------*/
/*        Dummy interrupt routine                */
/*--------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*--------------------------------------------------------------*/
/*        Key data reading routine            */
/*--------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);
    Cont = ReadData;
}

/*--------------------------------------------------------------*/
/*        OBJ moving routine                */
/*--------------------------------------------------------------*/

void ObjSnakeMove(void)
{
    u8 i;

    for (i=127; i>0; i--) {
        OamBak[i].VPos = OamBak[i-1].VPos;
        OamBak[i].HPos = OamBak[i-1].HPos;
    }
    if (Cont & U_KEY)    OamBak[0].VPos -= 4;
    if (Cont & D_KEY)    OamBak[0].VPos += 4;
    if (Cont & L_KEY)    OamBak[0].HPos -= 4;
    if (Cont & R_KEY)    OamBak[0].HPos += 4;
}

