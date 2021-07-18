//==============================================================
//    bitmap.c                                                  
//    Sample main routine for bitmap mode (3~5)                                 //                                 
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.                 
//==============================================================

#include <agb.h>
#include "../share.h"

//-------------------- Local functions    --------------------------
static void bm_init();
static void bm_mode_change(u8 Bgmode);
static int  bm_key();
static void bm_rotate(s32 zoom);
static void bm_v_blank_inter();
static void bm_Bgmode3_Test();
static void bm_Bgmode4_Test(void);
static void bm_Bgmode5_Test(void);

//-------------------- Bitmap data    ---------------------
extern u16 umiB_Palette[256];
extern u8 umiB_IndexBitmap[240*160];
extern u16 img24bit_RawBitmap[240*160];
extern u16 img24bit2_RawBitmap[160*128];

//-------------------- Local variables    --------------------------
u8   bm_Bgmode;                   // BG mode
u32  Zoom;                        // Zoom ratio
s32  start_x , start_y;           // BG reference starting point
u16  bg2pa,bg2pb,bg2pc,bg2pd;     // BG data reference direction
vs32 bg2_center_x, bg2_center_y;  // Cordinates center
vu16 rotate_value;                // 1 rotation = 256


//==============================================================
//                 Main routine                                                              
//==============================================================
void bm_Main()
{
    // Initialize
    bm_Bgmode = 3;
    SetVBlankFunc(bm_v_blank_inter);
    bm_init();

    // Set V Blank interrupt flag
    *(vu16 *)REG_IE |= V_BLANK_INTR_FLAG;

    while(1)
    {
        if ( bm_key() ) return;
        bm_mode_change(bm_Bgmode);

        V_Wait();
    }
}


//==================================================================
//                  V Blank interrupt process                                                   
//==================================================================
static void bm_v_blank_inter()
{
    // Store results
    *(vu16 *)REG_BG2PA = (u16)bg2pa;
    *(vu16 *)REG_BG2PB = (u16)bg2pb;
    *(vu16 *)REG_BG2PC = (u16)bg2pc;
    *(vu16 *)REG_BG2PD = (u16)bg2pd;

    *(vu16 *)REG_BG2X_L = (start_x & 0xffff);
    *(vu16 *)REG_BG2X_H = (u16)(u32)((start_x & 0x0fff0000)>>16);
    *(vu16 *)REG_BG2Y_L = (start_y & 0xffff);
    *(vu16 *)REG_BG2Y_H = (u16)(u32)((start_y & 0x0fff0000)>>16);
}


//==============================================================
//                 Subroutines                                 
//==============================================================

//--------------------------------------------------------------
//                 Initialize                                       
//--------------------------------------------------------------
static void bm_init()
{
    rotate_value = 0;
    Zoom = 0x100;
    bg2_center_x = 120;
    bg2_center_y = 80;
}


//--------------------------------------------------------------
//                  Key input                                                                        
//--------------------------------------------------------------
static int bm_key()
{
    KeyRead();

    bm_rotate(Zoom);

    if(Cont & U_KEY) bg2_center_y -= 0x100;
    if(Cont & D_KEY) bg2_center_y += 0x100;
    if(Cont & L_KEY) bg2_center_x -= 0x100;
    if(Cont & R_KEY) bg2_center_x += 0x100;

    if(Trg & START_BUTTON) bm_init();

    if(Cont & R_BUTTON)
        Zoom++;
    if(Cont & L_BUTTON)
        Zoom--;

    if(Trg & A_BUTTON) // Switch BgMode
    {
        bm_init();
        bm_Bgmode++;
        if (bm_Bgmode > 5)
            bm_Bgmode = 3;
    }

    if (Trg & SELECT_BUTTON)
    {
        return 1;
    }

}

//--------------------------------------------------------------
//                 Mode change                                                                     
//--------------------------------------------------------------
static void bm_mode_change(u8 Bgmode)
{
    switch(Bgmode)
    {
    case 3:
        bm_Bgmode3_Test();
        break;
    case 4:
        bm_Bgmode4_Test();
        break;
    case 5:
        bm_Bgmode5_Test();
        break;
    default:
        break;
    }
}


//--------------------------------------------------------------
//                 Set BG data reference starting point                                    
//--------------------------------------------------------------
static void bm_rotate(s32 zoom)
{
    // BG data reference direction set
    bg2pa =  fix_mul( _Cos(0), zoom);
    bg2pb =  fix_mul( _Sin(0), zoom);
    bg2pc =  fix_mul(-_Sin(0), zoom);
    bg2pd =  fix_mul( _Cos(0), zoom);

    // BG data reference starting point set
    start_x = ( 120 * 0x100 - bg2_center_x )
        - ( (bg2pa * 120 )  )
        - ( (bg2pb * 80 )  );

    start_y = ( 80 * 0x100 - bg2_center_y )
        - ( (bg2pc * 120 ) )
        - ( (bg2pd * 80 ) );
}


//--------------------------------------------------------------
//                 BG mode3 test                                                  
//--------------------------------------------------------------
static void bm_Bgmode3_Test()
{
    *(vu16 *)REG_DISPCNT = DISP_MODE_3 | DISP_OBJ_BG_ALL_ON;
    DmaArrayCopy(3, img24bit_RawBitmap, BG_BITMAP0_VRAM, 16);
}


//--------------------------------------------------------------
//                 BG mode4 test                                                  
//--------------------------------------------------------------
static void bm_Bgmode4_Test(void)
{
    *(vu16 *)REG_DISPCNT = DISP_MODE_4 | DISP_OBJ_BG_ALL_ON;
    DmaArrayCopy(3, umiB_Palette, BG_PLTT,        16);
    DmaArrayCopy(3, umiB_IndexBitmap, BG_BITMAP0_VRAM, 16);
}


//--------------------------------------------------------------
//                 BG mode5 test                                                  
//--------------------------------------------------------------
static void bm_Bgmode5_Test(void)
{
    *(vu16 *)REG_DISPCNT = DISP_MODE_5 | DISP_OBJ_BG_ALL_ON;
    DmaArrayCopy(3, img24bit2_RawBitmap, BG_BITMAP0_VRAM, 16);
}
