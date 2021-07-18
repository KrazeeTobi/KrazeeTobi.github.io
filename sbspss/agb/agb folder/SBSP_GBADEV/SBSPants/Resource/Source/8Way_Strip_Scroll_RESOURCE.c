//***************************************************************************************************

// Put in 'Scroll_Engine.h'.

/////////////////////////////////////////////////
// Defines.
/////////////////////////////////////////////////

#define	MAX_PIXEL_SCROLL_PER_FRAME 16		// Max number of _PIXELS_ scroll can move in one pass.
#define SCREEN_X_CHARS 30			// Size of GBA screen in 8*8 characters.
#define SCREEN_Y_CHARS 20

/////////////////////////////////////////////////
// Global Variables.
/////////////////////////////////////////////////

s32 map_xpos;					// Map x-axis co-ordinate.
s32 map_ypos;					// Map y-axis co-ordinate.
s32 old_map_xpos_bg1;				// (Previous) map x-axis co-ordinate (bg1).
s32 old_map_ypos_bg1;				// (Previous) map y-axis co-ordinate (bg1).
s32 old_map_xpos_bg2;				// (Previous) map x-axis co-ordinate (bg2).
s32 old_map_ypos_bg2;				// (Previous) map y-axis co-ordinate (bg2).

u8 x_shift1;					// Map x-axis fine shift store (bg1).
u8 y_shift1;					// Map y-axis fine shift store (bg1).
u8 x_shift2;					// Map x-axis fine shift store (bg2).
u8 y_shift2;					// Map y-axis fine shift store (bg2).

/////////////////////////////////////////////////
// Global Functions.
/////////////////////////////////////////////////

extern void BuildScreen();
extern void Scroll2Position(int Layer,s32 old_map_xpos,s32 old_map_ypos,s32 new_map_xpos,s32 new_map_ypos);

//***************************************************************************************************

// Put in 'Scroll_Engine.c'.

/////////////////////////////////////////////////
// Function Definitions.
/////////////////////////////////////////////////

static void DBlockVerticalStrip(int Layer,int Dir);
static void DBlockHorizontalStrip(int Layer,int Dir);

//***************************************************************************************************

// Init. screen using current map position before we start using the 8-way strip scroll.

void BuildScreen(void)
{
	int x;					// Local variable.
	s32 Temp;

	Temp=map_xpos;				// Store original co-ord.

	for(x=0;x<SCREEN_X_CHARS*8;x++;)	// Draw a screenfull of map to the screen buffer.
	{
		old_map_xpos_bg2=map_xpos>>1;	// Update map co-ords store (bg2) (half scroll speed !).
		old_map_ypos_bg2=map_ypos>>1;

		Scroll2Position(2,old_map_xpos_bg2,old_map_ypos_bg2,map_xpos>>1,map_ypos>>1) // Update the screen buffer (bg2).

		old_map_xpos_bg1=map_xpos;	// Update map co-ords store (bg1).
		old_map_ypos_bg1=map_ypos;

		Scroll2Position(1,old_map_xpos_bg1,old_map_ypos_bg1,map_xpos,map_ypos) // Update the screen buffer (bg1).

		map_xpos++;			// Scroll map right.
	}

	map_xpos=Temp;				// Restore original co-ord.

	old_map_xpos_bg2=map_xpos>>1;		// Update map co-ords store (bg2).
	old_map_ypos_bg2=map_ypos>>1;

	old_map_xpos_bg1=map_xpos;		// Update map co-ords store (bg1).
	old_map_ypos_bg1=map_ypos;
}

//***************************************************************************************************

// Update the screen buffer(s) (8-way strip scroll routine).

void Scroll2Position(int Layer,s32 old_map_xpos,s32 old_map_ypos,s32 new_map_xpos,s32 new_map_ypos)
{
	int i=0,Dir=-1;				// Local variables.
	u16 DBlockVal=7;
	s32 TempX,TempY;

	if(old_map_xpos<new_map_xpos)		// X scroll.
	{
		Dir=1;				// -1=scroll left / +1=scroll right.
		DBlockVal=1;
	}

	while(old_map_xpos!=new_map_xpos)
	{
		old_map_xpos+=Dir;

		if((old_map_xpos&0x00000007)==DBlockVal)
		{
			DBlockVerticalStrip(Layer,Dir);
		}
		if(++i>MAX_PIXEL_SCROLL_PER_FRAME){break;}
	}

	i=0;
	Dir=-1;
	DBlockVal=7;

	if(old_map_ypos<new_map_ypos)		// Y scroll.
	{
		Dir=1;				// -1=scroll up / +1=scroll down.
		DBlockVal=1;
	}
		
	while(old_map_ypos!=new_map_ypos)
	{
		old_map_ypos+=Dir;

		if((old_map_ypos&0x00000007)==DBlockVal)
		{
			DBlockHorizontalStrip(Layer,Dir);
		}
		if(++i>MAX_PIXEL_SCROLL_PER_FRAME){break;}
	}

	TempX=(s32) old_map_xpos;		// Calc. hardware x scroll register value.
	TempX&=0x000000ff;
	TempY=(s32) old_map_ypos;		// Calc. hardware y scroll register value.
	TempY&=0x000000ff;
	if(Layer==2)				// Update which parallax layer ?.
	{
		x_shift2=(u8) TempX;
		y_shift2=(u8) TempY;

		*(vu16*)REG_BG1HOFS=x_shift2;	// Update fine scroll offset regs.
		*(vu16*)REG_BG1VOFS=y_shift2;

		DmaArrayCopy(3,Bg2_ScreenDat,MAP_BASE_ADDR+0x0800,16); // DMA copy 'bg2' buffer to vram.
	}
	else
	{
		x_shift1=(u8) TempX;
		y_shift1=(u8) TempY;

		*(vu16*)REG_BG2HOFS=x_shift1;	// Update fine scroll offset regs.
		*(vu16*)REG_BG2VOFS=y_shift1;

		*(vu16*)REG_BG0HOFS=map_xpos>>2; // Update fine scroll offset regs. (compute 'bg3' rear parallax scroll ratio too !).
		*(vu16*)REG_BG0VOFS=map_ypos>>3;

//		*(vu16*)REG_BG3HOFS=0;		// 'Speech Bubble' layer use only.
//		*(vu16*)REG_BG3VOFS=0;

		DmaArrayCopy(3,Bg1_ScreenDat,MAP_BASE_ADDR+0x1000,16); // DMA copy 'bg1' buffer to vram.
	}
}

//---------------------------------------------------------------------------------------------------

//	Calculate place to draw vertical strip (left or right of screen based on dir).

static void DBlockVerticalStrip(int Layer,int Dir)
{
	int x,y;				// Local variables.
	u16 RealMapX,RealMapY,RealScreenPosX,RealScreenPosY;
	u16 ScreenSide;

	if(Dir==1)				// Draw to either the left or right of the screen depending on scroll direction.
	{
		ScreenSide=SCREEN_X_CHARS*8;
	}
	else
	{
		ScreenSide=0;
	}						

	// Obtain map position to draw from (shifting current_map right(>>) by 3 bits gives us a character value within the mapdata.
	// i.e.	MapX = 8	= %00000000 00001000 >> 3 = %(000)00000 00000001 = character 1.
	//	MapX = 77	= %00000000 01001101 >> 3 = %(000)00000 00001001 = character 9.
	//	MapX = 400	= %00000001 10010000 >> 3 = %(000)00000 00110010 = character 50.
	
	RealMapX=(CurrentMapX+ScreenSide)>>3; 	
	RealMapY=CurrentMapY>>3;

	// The easy way to work out where you need to draw to, given the positions are always the same, is to simply
	// look at the bottom 5 bits of your character scroll position to give you the place on the screen you need to
	// draw to, this does work ! -5 bits = %00011111 = 31, if you draw pos was character 32 if you look at the 5 bits
	// your draw pos would be 0, if it was 33, the bottom 5 bits would be 1, if it was 34 it would be 2 etc etc !
	// this also works for the y value ! :O)

	RealScreenPosX=RealMapX&0x001f;
	RealScreenPosY=RealMapY&0x001f;

	// Draw strip...
	// When drawing strip, to obtain next y pos just do a y++ then &0x001f - when you get to the bottom of the screen the y
	// pos will auto wrap back to the top (if you imagine all you are doing is drawing a vertical strip).

	for(y=0;y<21;y++;)			// Draw vertical strip with vram buffer wrap.
	{
		if(Layer==2)			// Update which parallax layer ?.
		{
			Bg2_ScreenDat[RealScreenPosX+((RealScreenPosY+y)&0x001f)*32)]=pMid_Map[RealMapX+(RealMapY+(y*map_x_size_tiles))];
		}
		else
		{
			Bg1_ScreenDat[RealScreenPosX+((RealScreenPosY+y)&0x001f)*32)]=pAction_Map[RealMapX+(RealMapY+(y*map_x_size_tiles))];
		}
	}
}

//---------------------------------------------------------------------------------------------------

//	Calculate place to draw horizontal strip (top or bottom of screen based on dir).

static void DBlockHorizontalStrip(int Layer,int Dir)
{
	int x,y;				// Local variables.
	u16 RealMapX,RealMapY,RealScreenPosX,RealScreenPosY;
	u16 ScreenSide;

	if(Dir==1)				// Draw to either the top or bottom of the screen depending on scroll direction.
	{
		ScreenSide=SCREEN_Y_CHARS*8;
	}
	else
	{
		ScreenSide=0;
	}						
	
	RealMapX=CurrentMapX>>3;
	RealMapY=(CurrentMapY+ScreenSide)>>3;

	RealScreenPosX=RealMapX&0x001f;
	RealScreenPosY=RealMapY&0x001f;

	for(x=0;x<31;x++;)			// Draw horizontal strip with vram buffer wrap.
	{
		if(Layer==2)			// Update which parallax layer ?.
		{
			Bg2_ScreenDat[((RealScreenPosX+x)&0x001f)+(RealScreenPosY*32)]=pMid_Map[(RealMapX+x)+(RealMapY*map_x_size_tiles)];
		}
		else
		{
			Bg1_ScreenDat[((RealScreenPosX+x)&0x001f)+(RealScreenPosY*32)]=pAction_Map[(RealMapX+x)+(RealMapY*map_x_size_tiles)];
		}	
	}
}

//***************************************************************************************************
