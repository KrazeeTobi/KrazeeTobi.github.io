//------------------------------//
//   Rotation example by Warder1     //
//------------------------------//
#include "header.h"
#include "bg.c"
#include <math.h>
#define RADIAN(n) (((float)n)/(float)180*PI)
#define fixed int
#define PI 3.14159

fixed COS[360];
fixed SIN[360];

extern u8 pic;									//adds the pic and palette from data.asm
extern u16 pl;
extern u16 x=0,y=0,xa=0,ya=0;

u16 *pal=(u16*)0x5000000;						//tells the compiler to load all the pallette info into that address
u16 *tmp_pal;

u8 *tiles=(u8*)0x6004000;						//tells the compiler to load all the tile info into that address	
u8 *bg_data;

u8 *m0=(u8*)0x6000000;						//tells the compiler when our bkg map is going to be located

void MakeBKG()
{
	u16 i;									//define some temp variables
	   	bg_data = (u8*)(&pic);					//have bg_data point to our .raw defined in data.asm
	   	tmp_pal = (u16*)(&pl);					//have tmp_pal point to our .pal defined in data.asm

	   	for (i=0;i<256;i++) pal[i]=tmp_pal[i];	//load the pallette info into the desired address

	   	for(i=0;i<64*256;i++) tiles[i]=bg_data[i];//load the bg tiles into the desired address

   		for (i=0;i<256;i++) 
			   m0[i]=i;
}

void Init()
{
	u16 i;
	BG2CNT = 0x2084;							//turn on BG2CNT.  Also tells where the map and tile locations are for this bkg

	DISPCNT = 0x0441;							//sets the display mode to display BKG0 
	//set up sin/cos/tan tables
	
	for(i = 0;i<360;i++)
	{
		SIN[i] = (fixed)(sin(RADIAN(i))*((float)(1<<30)));
		COS[i] = (fixed)(cos(RADIAN(i))*((float)(1<<30)));
	}
}
void DoVblank()
{
		BG2PA = 0x0100-xa;		//stretch in x direction	
		BG2PD = 0x0100-ya;		//stretch in y direction		
		BG2PB = 0x0000+x;
		BG2PC = 0x0000-y;
		BG2Y_L = 0x0000+(y*120);
		BG2X_L = 0x0000-(x*80);		
}

void C_Entry()
{
	u8 btn;

	Init();	
										//call init to set up our screen display
	
	MakeBKG();									//display the background

	while (1)									//loop
	{

	btn=joypad();
	if (btn)
		{
		if (!(btn & J_LEFT))	{
		x-=4;
		y-=4;

		}
		if (!(btn & J_RIGHT))	{
		x+=4;
		y+=4;

		}
		if (!(btn & J_A))	{
		xa+=4;
		ya+=4;	
	
		}
		if (!(btn & J_B))	{
		xa-=4;
		ya-=4;	
		}
	}


	while (DISPLAY_Y < 159) {  
	DoVblank();
	}

	}
  
 }