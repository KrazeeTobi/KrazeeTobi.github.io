/********************************************************************/
/*          main.c                                                  */
/*            simple（基本サンプル）のソース                        */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "data.h"


/*-------------------- グローバル 変数  ----------------------------*/

    u16      Cont, Trg;                  // キー入力

    u32      IntrMainBuf[0x200];         // 割り込みメインルーチン用バッファ

    u16      BgBak[32*32];               // BG  バックアップ
    OamData  OamBak[128];                // OAM バックアップ


/*---------------------- サブルーチン  -----------------------------*/

void KeyRead(void);
void ObjSnakeMove(void);


/*------------------------------------------------------------------*/
/*                      割り込みテーブル                            */
/*------------------------------------------------------------------*/
#if 0
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[14] = {
    VBlankIntr,     // Ｖブランク割り込み
    IntrDummy,      // Ｈブランク割り込み
    IntrDummy,      // Ｖカウンタ一致割り込み
    IntrDummy,      // タイマー０割り込み
    IntrDummy,      // タイマー１割り込み
    IntrDummy,      // タイマー２割り込み
    IntrDummy,      // タイマー３割り込み
    IntrDummy,      // シリアル通信割り込み
    IntrDummy,      // ＤＭＡ０割り込み
    IntrDummy,      // ＤＭＡ１割り込み
    IntrDummy,      // ＤＭＡ２割り込み
    IntrDummy,      // ＤＭＡ３割り込み
    IntrDummy,      // キー割り込み
    IntrDummy,      // カセット割り込み
};
#endif

/*==================================================================*/
/*                      メインルーチン                              */
/*==================================================================*/
extern void intr_main(void);
extern void initVBlank(void);
extern void waitForVBlank(void);


void AgbMain(void)
{
    s32    i;

    DmaClear(3, 0, EX_WRAM,  EX_WRAM_SIZE,          32);   // CPU外部ワークRAM クリア
    DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 0x200, 32);   // CPU内部ワークRAM クリア
//  DmaClear(3, 0, VRAM,     VRAM_SIZE,             32);   //     VRAM クリア
//  DmaClear(3, 0, OAM,      OAM_SIZE,              32);   //      OAM クリア
//  DmaClear(3, 0, PLTT,     PLTT_SIZE,             32);   // パレット クリア

		initVBlank();

    //DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// 割り込みメインルーチン セット
    //*(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 32);  //  BGキャラクタ セット
    DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 32);  // OBJキャラクタ セット
    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        32);  //  BGパレット   セット
    DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       32);  // OBJパレット   セット

    DmaArrayCopy(3, BgScData_Sample, BgBak,          32);  // BGスクリーン  セット
    DmaArrayCopy(3, BgBak,           BG_VRAM,        32);
    DmaArrayCopy(3, OamData_Sample,  OamBak,         32);  //          OAM  セット
    for (i=0; i<94; i++) {                            // OAM 初期化
        OamBak[i] = *(OamData *)OamData_Sample;
        //OamBak[i].CharNo = '@' + DivRem(i, 64);
        OamBak[i].CharNo = '@' + (i % 64);

        OamBak[i].VPos += i<<2;
        OamBak[i].HPos += i<<2;
    }
    DmaArrayCopy(3, OamBak,          OAM,            32);

    *(vu16 *)REG_BG0CNT =                             // BGコントロール セット
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_IME   = 1;                           // IME セット
    *(vu16 *)REG_IE    = V_BLANK_INTR_FLAG;           // Vブランク割込許可
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON; // LCDC ON

    while(1) {
        KeyRead();                                  // キー操作
        if (Trg & A_BUTTON)                         // キャラクタ 変更
            for (i=0; i<128; i++)    OamBak[i].CharNo++;
        if (Trg & B_BUTTON)
            for (i=0; i<128; i++)    OamBak[i].CharNo--;
        if (Cont & PLUS_KEY_MASK)                   // OBJ 移動
            ObjSnakeMove();

        //VBlankIntrWait();                           // Vブランク割込終了待ち
				waitForVBlank();

    }
}


/*==================================================================*/
/*                      割り込みルーチン                            */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Ｖブランク処理                              */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
    DmaArrayCopy(3, BgBak,  BG_VRAM, 32);           // BGスクリーン セット
    DmaArrayCopy(3, OamBak, OAM,     32);           // OAM セット

    *(u16 *)INTR_CHECK_BUF = V_BLANK_INTR_FLAG;     // Vブランク割込チェックのセット
}

/*------------------------------------------------------------------*/
/*                      割り込み ダミールーチン                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                      サブルーチン                                */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      キー読み込み                                */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // トリガ 入力
    Cont = ReadData;                                //   ベタ 入力
}

/*------------------------------------------------------------------*/
/*                      ＯＢＪ移動 ルーチン                         */
/*------------------------------------------------------------------*/

void ObjSnakeMove(void)
{
    u8   i;
    for (i=127; i>0; i--) {
        OamBak[i].VPos = OamBak[i-1].VPos;
        OamBak[i].HPos = OamBak[i-1].HPos;
    }
    if (Cont & U_KEY)    OamBak[0].VPos -= 4;
    if (Cont & D_KEY)    OamBak[0].VPos += 4;
    if (Cont & L_KEY)    OamBak[0].HPos -= 4;
    if (Cont & R_KEY)    OamBak[0].HPos += 4;
}

