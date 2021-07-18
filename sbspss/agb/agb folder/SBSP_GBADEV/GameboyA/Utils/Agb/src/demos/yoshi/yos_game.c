//======================================================
//    yos_game.c
//    Sample Yoshi Game Main Routine 
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <Agb.h>
#include "yos_main.h"
#include "yos_main.ext"
#include "yos_type.h"
#include "yos_game.h"
#include "yos_bmp.h"
#include "etc_bmp.h"
#include "oam_proc.h"
#include "yos_anm.h"
#include "yos_main_dat.h"
#include "yos_game_dat.h"
#include "yos_game_sub.h"
#include "yos_game_mov.h"
#include "yos_game_pr.h"

#include "yos_sound.h"

//bg Related Process
extern void bg_modified(s32 x, s32 y,s32 zoom);
extern void bg_init(s8 mode);

////////////////////////////////////////////////////////////////////////////
//Local Function
static void VIntrFunc(void);		//Function called in from main in V Blank
static void game_init0(void);		//Initialization0
static void game_init1(void);		//Initialization1
static void game_main(void);		//Main part of Game
static void game_over0(void);		//Game Over0

////////////////////////////////////////////////////////////////////////////
//Global Variable
gGames          p1_gGame;                       //Global Variable in Game
u8              p1_sub_status;                  //Substatus
s32             p1_line_count;                  //For Speed Check
YoshiWork       p1_yoshiWork;                   //Work unique to Yoshi
EffectWork      p1_effWork[EFF_WORK_MAX];       //Effect Work
CharacterWork   p1_eggWork[EGG_WORK_MAX];       //Egg Work  
CharacterWork   p1_kokamekWork[KOKAMEK_MAX];    //Kokamek Work
CharacterWork   p1_hanabiraWork[HANABIRA_MAX];  //Petals Work 
CharacterWork   p1_charWork[CHARACTER_WORK_MAX];//Characters Work

////////////////////////////////////////////////////////////////////////////
//Function Table
//Call based on value of main_status
static const func_ptr func_tbl[]=
{
	game_init0,//Initialization to go through one time only
	game_init1,//Start from here when Yoshi crashes and is killed
	game_main, //During game
	game_over0,//When Game Over
};

////////////////////////////////////////////////////////////////////////////
//Main Routine
void yos_game(void)
{
	clear_OamList();//Initialize OamList
	dmaReqNum = 0;//Clear Request Number of DMA Transfer
	p1_key_chk();//Obtain the direction the key is pressed for
	
	func_tbl[gMain.main_status]();//Process according to Function Table
	
//	while((*(vu16*)REG_VCOUNT & 0xff)>=160);//wait (For Test)
	make_OamBuf();//Create OamBuf
}

////////////////////////////////////////////////////////////////////////////
//Function called in after V Blank Interrupt
static void VIntrFunc(void)
{
	u16 i;
	
	if(!oamWaitFlg)DmaArrayCopy(3, gMain.OamBuf, OAM, 32);// OAM set
	
	//Transfer Rewritable Data 
	for(i=0; i<dmaReqNum; i++)
		DmaCopy(3, dmaReqArray[i].addr_from, dmaReqArray[i].addr_dest, dmaReqArray[i].size, 16);
	
	dmaReqNum=0;//Clear DMA Transfer Request Number
	
	//BG Process(Set BG in the current map location)
	if(gMain.main_status == GMAIN_ST_GAME_MAIN)
	{
		if(p1_gGame.disp_x<0)
			bg_modified((p1_gGame.disp_x>>16)+BG_L, (p1_gGame.disp_y+p1_gGame.gnd_bias)>>16, p1_gGame.zoom);//bg set
		else if(p1_gGame.disp_x>(BG_L<<16))
			bg_modified((p1_gGame.disp_x>>16)-BG_L, (p1_gGame.disp_y+p1_gGame.gnd_bias)>>16, p1_gGame.zoom);//bg set
		else
			bg_modified(p1_gGame.disp_x>>16, (p1_gGame.disp_y+p1_gGame.gnd_bias)>>16, p1_gGame.zoom);//bg set
	}
	if(p1_gGame.siro_flg>0)
	{
		bg_init(1);
		p1_gGame.siro_flg = -1;
	}
}

////////////////////////////////////////////////////////////////////////////
//Initialization 0
//Once only at beginning of game
static void game_init0(void)
{
	u16 i;
#ifdef SOUND_ON
#ifdef BGM_ON
	m4aSongNumStart(YOS_BGM_GAME);//BGM Start
#endif
#endif
	
	gMain.pVBlankFunc = 0;//Clear the pointer of function that is called in after V Blank Interrupt 
	
	*(vu16 *)REG_DISPCNT = DISP_MODE_1 | DISP_LCDC_OFF;	// LCDC OFF
	
	bg_init(0);//BG Initialization (bg_proc.c)
	
	//Set OBJ Characters
	for(i=0;p1_objChrTbl[i].size!=255;i++)
	{
		DmaCopy(3, p1_objChrTbl[i].pSource, OBJ_MODE0_VRAM+32*p1_objChrTbl[i].chrNo
		         ,32*OBJ_COLOR*p1_objChrTbl[i].size, 16);
	}
	
//	DmaCopy(3, ps_hey1_Palette, OBJ_PLTT, sizeof(ps_hey1_Palette), 16);	// OBJ Palette Set
	DmaCopy(3, p1_obj_Palette, OBJ_PLTT, sizeof(p1_obj_Palette), 16);	// OBJ Palette Set
	
	// OAM Initialization
	for (i=0; i<128; i++)
	{
		gMain.OamBuf[i] = *(OamData *)p1_OamData_Sample;
		gMain.OamBuf[i].AffineParam = ((i%2) ==0) ? 0x0100 : 0;
	}
	DmaArrayCopy(3, gMain.OamBuf, OAM, 32);//Transfer to OAM
	
	//The Second Pixel, Type of Special Effect, The First Pixel
	*(vu16*)REG_BLDCNT   = BLD_2ND_ALL|BLD_NORMAL_MODE|BLD_ALL;//No Special Effects
	*(vu16*)REG_BLDALPHA = 0x0808;//Coefficient EVB EVA
	*(vu16*)REG_BLDY     = 8;//Coefficient EVY
	
	p1_workInit0();//Initialization of Work
	
	oamWaitFlg = 0;//Flag to prevent transferring to OAM when being created
	gMain.pVBlankFunc = VIntrFunc;//(This is to be set at the end)
	p1_line_count=0;
	
	*(vu16 *)REG_IME = 1;						// IME Set
//	*(vu16 *)REG_IE	  |= IME_FLAG;				// IME Set
	*(vu16 *)REG_IE   |= V_BLANK_INTR_FLAG;		// Set V Blank Interrupt Enable Flag
	*(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;
	
	p1_sub_status = 0;
	gMain.main_status++;//Next is Initialization 1
}

////////////////////////////////////////////////////////////////////////////
//Initialization1
//Start from here when Yoshi crashes and is killed
static void game_init1(void)
{
	s16 i;
	
	//The Second Pixel, Type of Special Effect, The First Pixel
	*(vu16*)REG_BLDCNT   = BLD_2ND_ALL|BLD_NORMAL_MODE|BLD_ALL;//No Special Effects
	*(vu16*)REG_BLDALPHA = 0x0808;//Coefficient EVB EVA
	*(vu16*)REG_BLDY     = 8;//Coefficient EVY
	
	p1_gGame.disp_x      = 0;//Location of the screen at the time of start
	p1_gGame.disp_y      = DISP_Y;
	p1_gGame.zoom        = ZOOM_1;// Zoom Value of Screen(x 1)
	
	bg_init(2);//BG Initialization Set to Start Position
	
	p1_yoshi_init1();//Initialization of Yoshi
	
	for(i=0; i<ANM_WORK_MAX; i++)
	{//Initialization of Animation Work
		anmWork[i].flg     = -1;
		anmWork[i].pTbl    = 0;
		anmWork[i].anm_ptn = 0;
	}
	anmWork[ANM_WORK_YOSHI].flg    = 0;//Yoshi Animation Clear
	anmWork[ANM_WORK_MBOX ].flg    = ANM_FLG_NEW;//Box Animation Start
	anmWork[ANM_WORK_SUN  ].flg    = ANM_FLG_NEW;//Sun Animation Start
	anmWork[ANM_WORK_KILLERS0].flg = ANM_FLG_NEW;//Killer Animation Start
	
	for(i=0; i<EFF_WORK_MAX; i++)p1_effWork[i].status = 0;//Initialization of Effect Work
	
	p1_gGame.gnd_bias_count = 0;//Clear Count with Shaking of Ground
	p1_gGame.gnd_bias       = 0;//Clear Gap in Ground
	p1_gGame.game_timer     = 0;//Clear Timer
	
	//Start Screen Display
//	*(vu16 *)REG_DISPCNT = DISP_MODE_1 | DISP_OBJ_ON | DISP_OBJ_CHAR_1D_MAP;
	*(vu16 *)REG_DISPCNT = DISP_MODE_1 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_BG2_ON | DISP_BG3_ON | DISP_OBJ_CHAR_1D_MAP;
	p1_sub_status = 0;
	gMain.main_status++;
}

////////////////////////////////////////////////////////////////////////////
//Game Main
static void game_main(void)
{
//	while((*(vu16*)REG_VCOUNT & 0xff)>160);//wait for Speed Check
	p1_gGame.game_timer++;
	p1_charMove();        //Move other characters
	p1_yoshiMove();       //Move Yoshi
	p1_effectMove();      //Effect Processing
	p1_hanabiraMove();    //Processing of petals
	p1_eggMove();         //Processing of Egg
	p1_anim_work_proc();  //Processing of Animation
	
	p1_calcDispPosition();//Set the central location of Screen
	
#ifdef SPEED_CHK
	if(gMain.Cont & START_BUTTON)
	{//Display the egg to indicate process time when start button is pressed
		p1_charWork[0].pos.x = (p1_line_count << 16)+p1_gGame.disp_x-(DISP_X);//Speed check
		p1_charWork[0].pos.y = p1_gGame.disp_y;//Speed Check
	}else
	{//No Display
		p1_charWork[0].pos.y = (100<<16)+p1_gGame.disp_y;//Speed Check
	}
#endif
	
	p1_eggPrint();      //Display Egg
	p1_charPrint();     //Display Other Characters
	p1_gagePrint();     //Display Sunflower gauge
	p1_yoshiPrint();    //Display Yoshi
	p1_yoshiKagePrint();//Display Yoshi's Shadow
	p1_effectPrint();   //Display Effect
	
#ifdef SPEED_CHK
	//Check the location of rendered line when game processing is completed
	p1_line_count = *(vu8 *)REG_VCOUNT;//Obtain the current number of lines (for Speed Check)
#endif
}

////////////////////////////////////////////////////////////////////////////
//Game Over0
// Processing
//   Yoshi lifted up by Kokamek and goes out of the screen
//   Screen fades out into black
//   Image of castle is gradually displayed from the center of BG Window
//   Taken into castle
//   Tower shakes
static void game_over0(void)
{
	s16 i;
	s16 rot,rval;
	
	p1_gGame.bgm_count--;
	
	switch(p1_sub_status)
	{
	case 0://init
#ifdef SOUND_ON
#ifdef BGM_ON
			m4aSongNumStart(YOS_BGM_GAMEOVER);//BGM Start
#endif
#endif
		p1_gGame.bgm_count = 320;
		for(i=1; i<ANM_WORK_MAX; i++)//Stop Animation except for Yoshi (No.0)
			anmWork[i].flg = -1;
		
		for(i=0; i<4; i++)
		{
			p1_kokamekWork[i].status = 1;
		}
		p1_kokamekWork[0].char_type = 
		p1_kokamekWork[1].char_type = CHR_TYPE_KOKAMEK0;
		p1_kokamekWork[2].char_type = 
		p1_kokamekWork[3].char_type = CHR_TYPE_KOKAMEK1;
		
		//Set (Vector from Yoshi's location to the location where turtle appears)/0x100 in a.
		p1_kokamekWork[0].a.x = ((p1_gGame.disp_x-DISP_X           )-(p1_yoshiWork.pos.x+p1_kokamekPos[0].x))/0x100;
		p1_kokamekWork[0].a.y = ((p1_gGame.disp_y-DISP_Y-32*0x10000)-(p1_yoshiWork.pos.y+p1_kokamekPos[0].y))/0x100;
		p1_kokamekWork[1].a.x = ((p1_gGame.disp_x+DISP_X           )-(p1_yoshiWork.pos.x+p1_kokamekPos[1].x))/0x100;
		p1_kokamekWork[1].a.y = ((p1_gGame.disp_y-DISP_Y-32*0x10000)-(p1_yoshiWork.pos.y+p1_kokamekPos[1].y))/0x100;
		p1_kokamekWork[2].a.x = ((p1_gGame.disp_x-DISP_X/2         )-(p1_yoshiWork.pos.x+p1_kokamekPos[2].x))/0x100;
		p1_kokamekWork[2].a.y = ((p1_gGame.disp_y-DISP_Y-32*0x10000)-(p1_yoshiWork.pos.y+p1_kokamekPos[2].y))/0x100;
		p1_kokamekWork[3].a.x = ((p1_gGame.disp_x+DISP_X/2         )-(p1_yoshiWork.pos.x+p1_kokamekPos[3].x))/0x100;
		p1_kokamekWork[3].a.y = ((p1_gGame.disp_y-DISP_Y-32*0x10000)-(p1_yoshiWork.pos.y+p1_kokamekPos[3].y))/0x100;
		
		//Location of Kokamek Display
		p1_kokamekWork[0].dir =-1;
		p1_kokamekWork[1].dir = 1;
		p1_kokamekWork[2].dir = 1;
		p1_kokamekWork[3].dir =-1;
		p1_anim_work_proc();//Animation Processing
		
		
		p1_sub_status++;
		p1_gGame.game_timer=0;
		//break;
	case 1://Kokamek Falls
		//If the screen is zoomed, gradually return to its original size
		if(p1_gGame.zoom > ZOOM_1)
		{
			p1_gGame.zoom -= 0x100;
			if(p1_gGame.zoom < ZOOM_1)p1_gGame.zoom=ZOOM_1;
		}
		
		rot = 0x40-p1_gGame.game_timer;
		for(i=0; i<4; i++)
		{
			p1_kokamekWork[i].pos.x = p1_yoshiWork.pos.x+p1_kokamekPos[i].x+fix_sin[rot  ]*p1_kokamekWork[i].a.x;
			p1_kokamekWork[i].pos.y = p1_yoshiWork.pos.y+p1_kokamekPos[i].y-fix_sin[rot*3]*p1_kokamekWork[i].a.y;
		}
		
		//zoom out
		p1_kokamekWork[0].v.x=ZOOM_1+(rot)*0x100;
		
		p1_yoshiPrint();    //Display Yoshi
		p1_gagePrint();     //Display gauge
		p1_charPrint();     //Display Other Characters
		p1_kokamekPrint();  //Display Kokamek
		p1_anim_work_proc();//Animation Processing
		if(++p1_gGame.game_timer > 0x40)
		{
			p1_yoshiWork.v.y = 0;
			anmWork[ANM_WORK_YOSHI].anm_ptn = YOS_ANM_BRING1;
			anmWork[ANM_WORK_YOSHI].flg = ANM_FLG_NEW;
			p1_sub_status++;
			p1_gGame.game_timer = 0;
		}
		break;
	case 2://Ascend
		p1_gGame.game_timer++;
		p1_yoshiWork.v.y -= 0x800;
		p1_yoshiWork.pos.y += p1_yoshiWork.v.y;
//		p1_kokamekWork[0].v.x = 0x8000+p1_gGame.game_timer*0x100;
		p1_kokamekWork[0].v.x = ZOOM_1+p1_gGame.game_timer*0x200;
		if(p1_kokamekWork[0].v.x > 0x20000)p1_kokamekWork[0].v.x = 0x20000;//Enlargement is up to 2 times
		for(i=0; i<4; i++)
		{
			p1_kokamekWork[i].pos.x = p1_yoshiWork.pos.x+(p1_kokamekPos[i].x>>8)*(p1_kokamekWork[0].v.x>>8);
			p1_kokamekWork[i].pos.y = p1_yoshiWork.pos.y+(p1_kokamekPos[i].y>>8)*(p1_kokamekWork[0].v.x>>8);
		}
		p1_yoshiWork.zoom.x =
		p1_yoshiWork.zoom.y = p1_kokamekWork[0].v.x;
		p1_gagePrint();     //Display gauge
		p1_charPrint();     //Display Other Characters
		p1_yoshiPrint();    //Display Yoshi
		p1_kokamekPrint();  //Display Kokamek
		p1_anim_work_proc();//Animation Processing
		if(p1_kokamekWork[2].pos.y+32*0x10000 < p1_gGame.disp_y-DISP_Y)
		{
			p1_sub_status++;
			p1_gGame.game_timer = 0;
			*(vu16*)REG_BLDCNT = BLD_2ND_ALL|BLD_DOWN_MODE|BLD_ALL;//Brightness Down
			*(vu16*)REG_BLDY = 0;
		}
		break;
	case 3://Black Fade Out
		p1_gGame.game_timer++;
		*(vu16*)REG_BLDY  = p1_gGame.game_timer>>2;//Increase Down in Brightness
		if(p1_gGame.game_timer >= 0x40)
		{
			p1_sub_status++;
			p1_gGame.game_timer = 0;
			
//			bg_init(1);//Drawing of BG Castle
			p1_gGame.siro_flg=1;
			*(vu16 *)REG_DISPCNT = DISP_MODE_3 | DISP_BG2_ON | DISP_OBJ_ON | DISP_OBJ_CHAR_1D_MAP;
			
			//Clear Animation
			p1_clear_anm();
			anmWork[ANM_WORK_YOSHI].anm_ptn = YOS_ANM_BRING2;
			anmWork[ANM_WORK_YOSHI].flg = ANM_FLG_NEW;
			
			//Set OBJ Characters
			for(i=0; p1_objChrTbl2[i].size!=255; i++)
			{
				DmaCopy(3, p1_objChrTbl2[i].pSource, OBJ_MODE0_VRAM+32*p1_objChrTbl2[i].chrNo
				         ,32*OBJ_COLOR*p1_objChrTbl2[i].size, 16);
			}
			p1_gGame.kumo_x = 0;//Set Coordinates of Clouds
			//Window Set(Enlarge window from one point of the central screen)
			*(vu16*)REG_WIN0H  = (120<<WIN_START_POS_SHIFT)|(120);
			*(vu16*)REG_WIN0V  = ( 80<<WIN_START_POS_SHIFT)|( 80);
			*(vu16*)REG_WINOUT = 0;
			*(vu16*)BG_PLTT    = 0;//Uses black as the first color
			*(vu16*)REG_WININ  = WIN_ALL_ON;
			*(vu16*)REG_DISPCNT |= DISP_WIN0_ON;
			//Reset the brightness of screen
			*(vu16*)REG_BLDCNT= BLD_2ND_ALL|BLD_NORMAL_MODE|BLD_ALL;//No Special Effects
			*(vu16*)REG_BLDALPHA = 0x1004;//coefficient EVB EVA
			*(vu16*)REG_BLDY  = 0;
		}
		break;
	case 4://Enlargement of BGWindow
		p1_gGame.game_timer++;
		
		//Enlargement of BGWindow
		rot = 120 * p1_gGame.game_timer/0x40;
		*(vu16*)REG_WIN0H  = ((120-rot) <<WIN_START_POS_SHIFT)|(120+rot);
		rot =  80 * p1_gGame.game_timer/0x40;
		*(vu16*)REG_WIN0V  = (( 80-rot) <<WIN_START_POS_SHIFT)|( 80+rot);
		
		p1_kumoPrint();   //Display cloud
		p1_koumoriPrint();//Display bat
		if(p1_gGame.game_timer >= 0x40)
		{
			//Removal of BGWindow
			*(vu16*)REG_DISPCNT &= ~(DISP_WIN0_ON);
			*(vu16*)REG_WIN0H  = (120<<WIN_START_POS_SHIFT)|(120);
			*(vu16*)REG_WIN0V  = ( 80<<WIN_START_POS_SHIFT)|( 80);
			*(vu16*)REG_WINOUT = 0;
			*(vu16*)REG_WININ  = 0;
			p1_gGame.game_timer = 0;
			p1_sub_status++;
		}
		break;
	case 5://wait
//		p1_gGame.game_timer++;
		p1_gGame.kumo_x += KUMO_MOV_SPEED;
		p1_kumoPrint();     //Display cloud
		p1_koumoriPrint();  //Display bat
//		if(p1_gGame.game_timer >= 0x20)
		if(p1_gGame.bgm_count<0)
		{
			p1_gGame.game_timer=0;
			p1_sub_status++;
		}
		break;
	case 6://Taken into castle
		p1_gGame.game_timer++;
		p1_gGame.kumo_x += KUMO_MOV_SPEED;
		rval = p1_turekomi_fly_pos_set(p1_gGame.game_timer);
		p1_yoshiPrint();    //Display Yoshi
		p1_kumoPrint();     //Display cloud
		p1_koumoriPrint();  //Display bat
		p1_kokamekPrint();  //Display Kokamek
		p1_anim_work_proc();//Display Animation
		if(rval == -1)
		{
			p1_gGame.game_timer=0;
			p1_sub_status++;
		}
		break;
	case 7://Tower of castle shakes
		p1_gGame.game_timer++;
		p1_gGame.kumo_x += KUMO_MOV_SPEED;
		
//		bg_init(1); //Animation processing of shaking of BG castle tower
		p1_gGame.siro_flg=1;
		
		p1_kumoPrint();   //Display cloud
		p1_koumoriPrint();//Display bat
		if(p1_gGame.game_timer >= 0x80-10)
		{
			p1_gGame.game_timer = 0;
			p1_sub_status++;
			*(vu16*)REG_BLDCNT = BLD_2ND_ALL|BLD_DOWN_MODE|BLD_ALL;//Brightness Down
			*(vu16*)REG_BLDY = 0;
		}
		break;
	case 8://wait
		p1_gGame.game_timer++;
		p1_kumoPrint();   //Display of cloud
		p1_koumoriPrint();//Display of bat
		if(p1_gGame.game_timer >= 0x40)
		{
			p1_sub_status++;
		}
		break;
	case 9://Place 1 frame
		*(vu16 *)REG_DISPCNT = DISP_MODE_3 | DISP_BG2_ON | DISP_OBJ_CHAR_1D_MAP;//OBJ_OFF
		*(vu16*)REG_BLDCNT = BLD_2ND_ALL|BLD_DOWN_MODE|BLD_ALL;//Brightness Down
		*(vu16*)REG_BLDY = 0x10;
#ifdef SOUND_ON
#ifdef BGM_ON
//		MPlayStop(&music);
#endif
#endif
		gMain.proc_num = PROC_0;//To Process 0
		gMain.main_status = 0;
		break;
	}
}
