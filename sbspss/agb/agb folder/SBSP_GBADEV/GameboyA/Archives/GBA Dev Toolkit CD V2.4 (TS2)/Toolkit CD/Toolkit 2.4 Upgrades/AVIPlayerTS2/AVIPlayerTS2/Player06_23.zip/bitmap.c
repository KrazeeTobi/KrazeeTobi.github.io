//==============================================================
//  bitmap.c                                                  
//  Sample main routine for bitmap mode (3~5)                 
//                                                             
//  Copyright (C) 1999, NINTENDO Co., Ltd.  
//	Last updated by James Verhaeghe on 5/16/00
//  Developer Support Group - Nintendo of America
//==============================================================

#include <agb.h>
#include "share.h"
#include "data.h"

//-------------------- Local functions  --------------------------
static void bm_init();
static int  bm_key();
static void bm_rotate(s32 zoom);
static void bm_v_blank_inter();
static void Init_Profiler();
static void Update_Profiler();

//-------------------- Bitmap data  ---------------------
#include "bmpdata.h"

//-------------------- Local variables  --------------------------
u32		Zoom;						// Zoom ratio
s32		start_x, start_y;       	// BG reference starting point
u16		bg2pa, bg2pb, bg2pc, bg2pd;	// BG data reference direction
vs32	bg2_center_x, bg2_center_y;	// Cordinates center
vu16	rotate_value;              	// 1 rotation = 256
u8		VBLCounter;					// Count the number of V Blank processed

// Profiler variables
#ifdef _DEBUG
u8		VBLused;    				// Used to calculate FPS
u8		VCountStart, VCountEnd;		// Vertical line counter for profiler
s32		ProfileData;				// Profiler data calculation
s32		PlayCount;					// # of times AVI played through  
u32		avg;						// average time to load a frame
s32		maxframe, minframe;			// Maximum and Minimum times to load a frame
OamData	OamBak[128];				// OAM backup - write OAM data here
#endif


//==============================================================
//                 Main routine                               
//==============================================================
void bm_Main()
{
    // Initialize
    SetVBlankFunc(bm_v_blank_inter);
    //SetT3Func(bm_timer_3_inter);
    
	#ifdef _DEBUG
		Init_Profiler();
	#endif
	
    bm_init(); 
	
	// Set V Blank interrupt flag
    *(vu16 *)REG_IE |= V_BLANK_INTR_FLAG;
    *(vu16 *)REG_DISPCNT = BG_STATE | DISP_OBJ_BG_ALL_ON;

   	while(1) {
   	
    	if (bm_key())
        	return;
        	
		if (VBLCounter >= FRAME_WAIT) {
		
			// Set up the debug profiler, count the number of vertical lines and 
			// V-blank periods needed to de-compress a frame.
  			#ifdef _DEBUG
	        	Update_Profiler();
  				VCountStart = *(u8*)REG_VCOUNT;
				VBLused = VBLCounter;
	       	#endif
			
			// Reset the Vertical Blank counter
  			VBLCounter = 0;
	        
	        // Swap out the frame
        	FrameSwap();
        		
        	// Finish the profiling, get vertical line counter and calculate time taken
	        #ifdef _DEBUG
	        	VCountEnd = *(u8*)REG_VCOUNT;
				
				// (Using V-Blank counter and V-count difference)
				ProfileData = (16743000*VBLCounter)/1000 +((VCountEnd-VCountStart)*73433)/1000;
				
				// Update max time for all frames if necessary
				if (ProfileData > maxframe)
					maxframe = ProfileData;

				// Update min time for all frames if necessary
				if (ProfileData < minframe)
					minframe = ProfileData;

				avg += ProfileData;
			#endif
			
        } // end if

		if (REG_DISPCNT & 0x0001)
			V_Wait();
	    	
    } // end while
    
} // end bm_main


//==================================================================
//                Interrupt processes                        
//==================================================================
static void bm_v_blank_inter()
{
	// Rewrite OAM first (All changes should be in OamBak
	#ifdef _DEBUG
		DmaArrayCopy(3, OamBak, OAM, 32);
	#endif
	
    // Store results
    *(vu16 *)REG_BG2PA = (u16)bg2pa;
    *(vu16 *)REG_BG2PB = (u16)bg2pb;
    *(vu16 *)REG_BG2PC = (u16)bg2pc;
    *(vu16 *)REG_BG2PD = (u16)bg2pd;

    *(vu16 *)REG_BG2X_L = (start_x & 0xffff);
    *(vu16 *)REG_BG2X_H = (u16)(u32)((start_x & 0x0fff0000)>>16);
    *(vu16 *)REG_BG2Y_L = (start_y & 0xffff);
    *(vu16 *)REG_BG2Y_H = (u16)(u32)((start_y & 0x0fff0000)>>16);
    
    // Switch to the correct buffer depending on which fram we are on
    // Odd Frames are in buffer 1, even in buffer 0
    if (!(Frame & 0x1)) {
    	*(vu16 *)REG_DISPCNT = BG_STATE | DISP_OBJ_BG_ALL_ON | DISP_BMP_FRAME_NO;
    } else {
    	*(vu16 *)REG_DISPCNT = BG_STATE | DISP_OBJ_BG_ALL_ON;
    }
    
    VBLCounter++;
    
} // end bm_v_blank_inter


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
    Frame = 0;
    VBLCounter = 0;
    
    #ifdef _DEBUG
	    VCountStart = 0;
	    VCountEnd = 0;
        VBLused = 0;
        ProfileData = 0;
    	maxframe = 0;
		minframe = 0xEFFFFF;
		avg = 0;
    	PlayCount = 0;
    #endif
    
    bg2_center_x = BG_CENTER_X;
    bg2_center_y = BG_CENTER_Y;
    
	DataInit();
	
} // end bm_init


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

    if(Trg & START_BUTTON) 
    {
    	// Not used
    }

    if(Cont & R_BUTTON)
        Zoom++;
    if(Cont & L_BUTTON)
        Zoom--;

    if(Trg & A_BUTTON) // Start AVI (Not currently used - 5/8 JV)
    {
    	// Not used
    }
    
    if(Trg & B_BUTTON) // Stop AVI (Not currently used - 5/8 JV)
    {
        // Not used
    }

    if (Trg & SELECT_BUTTON) // exit the function. 
    {
    	ClearVram();
    	*(vu16 *)REG_IE &= ~(V_BLANK_INTR_FLAG);
        return 1;
    }

} // end bm_key


//--------------------------------------------------------------
//           Set BG data reference starting point               
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
        
} // end bm_rotate


//--------------------------------------------------------------
//           		Set Profiler data to OAM               
//--------------------------------------------------------------

#ifdef _DEBUG
static void Init_Profiler()
{
	// Local variables
	u8	i=0;	// object counter
	u8	j=0;	// space counter
	u8	k=0;	// line offset counter
	
	// load font data to print profiler information to screen
	DmaArrayCopy(3, CharData_Sample, OBJ_MODE5_VRAM, 16);  // Set OBJ character
	DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       16);  // Set OBJ palette
	DmaArrayCopy(3, OamData_Sample,  OamBak,         16);  // Set OAM
	
	// Set up initial profiler data and send it to OAM
	// F - OBJ 0
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x246;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;

	// p - OBJ 1
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x270;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // s - OBJ 2
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x273;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
    // 0 - OBJ 3
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 4
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k=21;
    j=0;
    
	// F - OBJ 5
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x246;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
	// r - OBJ 6
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x272;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
	// a - OBJ 7
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x261;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
	// m - OBJ 8
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x26D;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
	// e - OBJ 9
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x265;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
	// 0 - OBJ 10
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
	// 0 - OBJ 11
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
	// 0 - OBJ 12
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 152;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
	k=0;
    j=0;
       
    // D - OBJ 13
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x244;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // t - OBJ 14
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x274;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
    // 0 - OBJ 15
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 16
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 17
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 18
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 19
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 20
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // u - OBJ 21
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x275;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // s - OBJ 22
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x273;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k = 18;
    j = 0;
       
    // M - OBJ 23
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x24D;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // a - OBJ 24
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x261;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // x - OBJ 25
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x278;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
    // 0 - OBJ 26
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 27
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 28
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 29
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 30
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 31
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // u - OBJ 32
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x275;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // s - OBJ 33
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x273;
    OamBak[i].VPos = 0;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k=18;
    j=0;
       
    // M - OBJ 34
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x24D;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // i - OBJ 35
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x269;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // n - OBJ 36
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x26E;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
    // 0 - OBJ 37
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 38
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 39
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 40
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 41
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 42
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // u - OBJ 43
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x275;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // s - OBJ 44
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x273;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k=0;
    j=0;
       
    // A - OBJ 45
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x241;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // v - OBJ 46
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x276;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // g - OBJ 47
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x267;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
    // 0 - OBJ 48
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 49
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 50
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 51
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 52
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // 0 - OBJ 53
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x230;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // u - OBJ 54
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x275;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    
    // s - OBJ 55
    OamBak[i] = *(OamData *)OamData_Sample;
    OamBak[i].CharNo = 0x273;
    OamBak[i].VPos = 8;
    OamBak[i].HPos = 0 + k*8 + j*8;
    i++;
    k++;
    j++;
    
    DmaArrayCopy(3, OamBak, OAM, 32);
    
} // end Init_Profiler
#endif

#ifdef _DEBUG
static void Update_Profiler()
{
	// Local variables (currently none)
	
	// Update Frames per second
    // OBJ 3
    OamBak[3].CharNo = 0x230 + ((60/VBLused)/10)%10;
	    
    // OBJ 4
    OamBak[4].CharNo = 0x230 + (60/VBLused)%10;
	
	// Update Frame number on screen
	// OBJ 10
    OamBak[10].CharNo = 0x230 + ((Frame)/100)%10;
    
	// OBJ 11
    OamBak[11].CharNo = 0x230 + ((Frame)/10)%10;
    
	// OBJ 12
	if (Frame == 0)
		OamBak[12].CharNo = 0x230;
	else
		OamBak[12].CharNo = 0x230 + ((Frame)%10);
		
	// Update Decompression time on screen (objects 15~20)
	// OBJ 15 
	OamBak[15].CharNo = 0x230 + (ProfileData/100000)%10;
	
	// OBJ 16
	OamBak[16].CharNo = 0x230 + (ProfileData/10000)%10;
	
	// OBJ 17
	OamBak[17].CharNo = 0x230 + (ProfileData/1000)%10;
	
	// OBJ 18 
	OamBak[18].CharNo = 0x230 + (ProfileData/100)%10;
	
	// OBJ 19
	OamBak[19].CharNo = 0x230 + (ProfileData/10)%10;
	
	// OBJ 20
	OamBak[20].CharNo = 0x230 + ProfileData%10;
		
	// Update Maximum time on screen (objects 26~31)
	// OBJ 26 
	OamBak[26].CharNo = 0x230 + (maxframe/100000)%10;
	
	// OBJ 27
	OamBak[27].CharNo = 0x230 + (maxframe/10000)%10;
	
	// OBJ 28
	OamBak[28].CharNo = 0x230 + (maxframe/1000)%10;
	
	// OBJ 29 
	OamBak[29].CharNo = 0x230 + (maxframe/100)%10;
	
	// OBJ 30
	OamBak[30].CharNo = 0x230 + (maxframe/10)%10;
	
	// OBJ 31
	OamBak[31].CharNo = 0x230 + maxframe%10;
		
	// Update Minimum time on screen (objects 37~42)
	// OBJ 37 
	OamBak[37].CharNo = 0x230 + (minframe/100000)%10;
	
	// OBJ 38
	OamBak[38].CharNo = 0x230 + (minframe/10000)%10;
	
	// OBJ 39
	OamBak[39].CharNo = 0x230 + (minframe/1000)%10;
	
	// OBJ 40 
	OamBak[40].CharNo = 0x230 + (minframe/100)%10;
	
	// OBJ 41
	OamBak[41].CharNo = 0x230 + (minframe/10)%10;
	
	// OBJ 42
	OamBak[42].CharNo = 0x230 + minframe%10;

	// Update Average time on screen (objects 48~53)
	// (only after all frames have been loaded)
	if (Frame == 0) {

		avg = avg/AVI_LENGTH;
	
		// OBJ 48 
		OamBak[48].CharNo = 0x230 + (avg/100000)%10;
	
		// OBJ 49
		OamBak[49].CharNo = 0x230 + (avg/10000)%10;
	
		// OBJ 50
		OamBak[50].CharNo = 0x230 + (avg/1000)%10;
	
		// OBJ 51 
		OamBak[51].CharNo = 0x230 + (avg/100)%10;
	
		// OBJ 52
		OamBak[52].CharNo = 0x230 + (avg/10)%10;
	
		// OBJ 53
		OamBak[53].CharNo = 0x230 + avg%10;

		PlayCount++;
		avg = 0;
	}
		
} // end Update_Profiler
#endif
