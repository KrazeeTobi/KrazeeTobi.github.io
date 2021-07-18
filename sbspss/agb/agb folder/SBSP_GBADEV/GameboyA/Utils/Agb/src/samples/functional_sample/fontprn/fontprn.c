//======================================================
//    fontprn.c                                         
//    Routine to output character string to console
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#define	_FONTPRN_C_

#include <Agb.h>
#include "fontprn.h"
#include "font8.h"

//-------------------------- Constant  ------------------------------

#define	fpOBJSIZE	64				// OBJ size
#define	fpFONTSIZE	8				// Font size
#define	fpMAXOBJS	4*3				// Max number of OBJs
#define	fpMAXCOL	30				// Max number of columns
#define	fpMAXROW	20				// Max number of rows

//------------------------- Macro -----------------------------

#define fontInit	fpdata.init
#define fontColor	fpdata.color
#define fontVram	fpdata.obj_vram_adr
#define fontChar	fpdata.char_st
#define fontOamAdr	fpdata.oam_adr
#define fontOam		fpdata.oam_dt

//------------------------- Structure -----------------------------

typedef struct
{
	u8		init;					// Initialization flag
	u8		color;					// Current color
	u32		obj_vram_adr;			// VRAM destination address
	u16		char_st;				// Character num starting address
	u32		oam_adr;				// OAM destination address
	OamData	oam_dt[fpMAXOBJS];		// OAM data
	u32		adr[fpMAXCOL*fpMAXROW];
} fpData;

//------------------------- OAM format  ----------------------------

const u32 fontOamData[1][2] = {
		{ OAM_COLOR_16
		| OAM_SQUARE | OAM_SIZE_64x64
		| 0 << OAM_H_POS_SHIFT
		| 0 << OAM_V_POS_SHIFT,
		 0},
	};

//---------------------- Local variable  --------------------------

static fpData	fpdata;

//-------------------- Subroutine declarations  ------------------------

static void put_font_1d(u8 x,u8 y,u8 *str,u16 len);
static void put_font_2d(u8 x,u8 y,u8 *str,u16 len);

//==============================================================
//	FontPrintInit
//	Font initialization process
//
//	Parameter
//		x,y		display position
//		col		display column (currently not used)
//		row		display row (currently not used)
//		vram	VRAM starting address
//		pltno	palette number
//	Return value
//		None
//==============================================================
void FontPrintInit(u8 x,u8 y,u8 col,u8 row,u32 vram,u8 pltno)
{
	u8	i;
	u8	objs;

	// Prevent from initilizing more than once
	if(fontInit==1)
		return;

	fontInit=1;
	fontColor=0x0f;

	// Round to max numbers
	if(col>30)	col=30;
	if(row>20)	row=20;

	// Find number of OBJ usage
	objs=(col/fpFONTSIZE)*(row/fpFONTSIZE);

	// Set display charcter number
	// Set display position

	fontVram=vram;
	fontChar=(fontVram-OBJ_MODE0_VRAM)/32;

	// Set OAM
	for(i=0;i<fpMAXOBJS;i++)
	{
		fontOam[i] = *(OamData *)fontOamData;
		fontOam[i].CharNo = fontChar+i*64;
		fontOam[i].HPos = x+(i%4)*64;
		fontOam[i].VPos = y+(i/4)*64;
		fontOam[i].Pltt = pltno;
	}
	fontOamAdr=(OAM+OAM_SIZE)-(8*fpMAXOBJS);
	DmaArrayCopy(3,fontOam,fontOamAdr,32);

	*(vu16 *)REG_DISPCNT |= DISP_OBJ_ON;		// OBJ ON
}

//==============================================================
//	FontPalletLoad
//	Sample palette load
//
//	Parameter
//		pltno	palette number
//	Return value
//		None
//==============================================================
void FontPalletLoad(u8 pltno)
{
	// Palette data
	u16 FontPltt[16] = {
		0x0000,		// 00 Black
		0x7c00,		// 01 Blue
		0x03e0,		// 02 Green
		0xffe0,		// 03 Cyan
		0x001f,		// 04 Red
		0x7c1f,		// 05 Magenta
		0x83ff,		// 06 Yellow
		0xffff,		// 07 White
		0x5ad6,		// 08 Glay
		0x2c23,		// 09 Dark Blue
		0xa200,		// 10 Dark Green
		0x6e80,		// 11 Dark Cyan
		0x1018,		// 12 Dark Red
		0x3018,		// 13 Dark Magenta
		0x03bf,		// 14 Dark Yellow
		0xffff,		// 15 White (Default)
	};

	DmaArrayCopy(3,FontPltt,OBJ_PLTT+(sizeof(u16)*16)*pltno,16);
}

//==============================================================
//	FontColor
//	Font color change
//
//	Parameter
//		color	color number (color depends on palette)

//	Return value
//		None
//==============================================================
void FontColor(u8 color)
{
	fontColor=color;
}


//==============================================================
//	FontPrint
//	Font set process
//
//	Parameter
//		x,y		display position
//		str		string displayed
//	Return value
//		None
//==============================================================
void FontPrint(u8 x,u8 y,u8 *str)
{
	u16	len,i;

	if(!fontInit)	return;
	if(!fontColor)	return;

	// Count number of characters (strlen)

	for(len=0;;len++)
	{	if(!str[len])	break;	}
	if(!len)	return;

	// Display according to OBJ character mapping mode
	if(*(vu16 *)REG_DISPCNT&DISP_OBJ_CHAR_1D_MAP)
	{
		for(i=0;i<fpMAXOBJS;i++)
			fontOam[i].CharNo = fontChar+i*64;
		put_font_1d(x,y,str,len);
	}
	else
	{
		for(i=0;i<fpMAXOBJS;i++)
			fontOam[i].CharNo = fontChar+(i%4)*8+(i/4)*256;
		put_font_2d(x,y,str,len);
	}
}

#if 0
// NOT USE THIS: va_list version...
void FontPrint(u8 *fmt, ...)
{
	va_list	argp;
	u8		str[30*20];
	u16		len,i;

	va_start(argp,fmt);
	vsprintf(str,fmt,argp);
	va_end(argp);

	for(len=0;;len++)
	{	if(!str[len])	break;	}
	if(!len)	return;

	if(*(vu16 *)REG_DISPCNT&DISP_OBJ_CHAR_1D_MAP)
	{
		for(i=0;i<fpMAXOBJS;i++)
			fontOam[i].CharNo = fontChar+i*64;
		put_font_1d(x,y,str,len);
	}
	else
	{
		for(i=0;i<fpMAXOBJS;i++)
			fontOam[i].CharNo = fontChar+(i%4)*8+(i/4)*256;
		put_font_2d(x,y,str,len);
	}
}
#endif


//==============================================================
//	NumPrint
//	Font set process (for numbers)
//
//	Parameter
//		x,y		display position
//		val		display value
//		dig		display column number
//	Return value
//		None
//==============================================================
void NumPrint(u8 x,u8 y,s16 val,s16 dig)
{
	char buf[8];
	fp_itoa(val,buf,dig);
	FontPrint(x,y,buf);
}


//==============================================================
//	put_font_1d
//	Font display process (1 D version)
//
//	Parameter
//		x,y		display position
//		str		string displayed
//		len		string length
//	Return value
//		None
//==============================================================
static void put_font_1d(u8 x,u8 y,u8 *str,u16 len)
{
	u16	i;
	u8	px,py;

	px=x,py=y;
	for(i=0;i<len;i++)
	{
		// Change line
		if(str[i]=='\n')
		{
			px=x,py++;
			continue;
		}

		// OBJ character set
		DmaCopy(3,font8[fontColor-1]+(u32)(str[i]*8),
			fontVram+((px%8)+(px>>3)*64+(py%8)*8+(py/8)*256)*32,32,32);
		px++;

		// Internal line change
		if(!(px%fpMAXCOL))
		{
			px=x,py++;
		}
	}
}


//==============================================================
//	put_font_2d
//	Font display process (2D version)
//
//	Parameter
//		x,y		display position
//		str		string displayed
//		len		string length
//	Return value
//		None
//==============================================================
static void put_font_2d(u8 x,u8 y,u8 *str,u16 len)
{
	u16	i;
	u8	px,py;

	px=x,py=y;
	for(i=0;i<len;i++)
	{
		// Line change
		if(str[i]=='\n')
		{
			px=x,py++;
			continue;
		}

		// OBJ character set
		DmaCopy(3,font8[fontColor-1]+(u32)(str[i]*8),
			fontVram+((px)+(py*0x20))*32,32,32);
		px++;

		// Internal line change
		if(!(px%fpMAXCOL))
		{
			px=x,py++;
		}
	}
}


//==============================================================
//	FontPrintC
//	Font set process (color)
//
//	Parameter
//		x,y		display position
//		color	color number
//		str		string displayed
//	Return value
//		None
//==============================================================
void FontPrintC(u8 x,u8 y,u8 color,u8 *str)
{
	u8	bkcolor=fontColor;
	fontColor=color;
	FontPrint(x,y,str);
	fontColor=bkcolor;
}


//==============================================================
//	NumPrintC
//	Font set process (for number, color)
//
//	Parameter
//		x,y		display position
//		color	color number
//		val		display value
//		dig		display column number
//	Return value
//		None
//==============================================================
void NumPrintC(u8 x,u8 y,u8 color,s16 val,s16 dig)
{
	u8	bkcolor=fontColor;
	fontColor=color;
	NumPrint(x,y,val,dig);
	fontColor=bkcolor;
}


//==============================================================
//	FontPrintCls
//	Font clear process
//
//	Parameter
//		None
//	Return value
//		None
//==============================================================
void FontPrintCls(void)
{
	if(!fontInit)	return;

	DmaClear(3,0,fontVram,(OBJ_VRAM_END-fontVram),16);
}


//==============================================================
//	FontPrintSync
//	VSync process
//
//	Parameter
//		None
//	Return value
//		None
//==============================================================
void FontPrintSync(void)
{
	if(!fontInit)	return;

	// Revise flags
	if(!(*(vu16 *)REG_WININ &  WIN_OBJ_ON))			*(vu16 *)REG_WININ|=WIN_OBJ_ON;
	if(!(*(vu16 *)REG_WININ & (WIN_OBJ_ON<<8)))		*(vu16 *)REG_WININ|=(WIN_OBJ_ON<<8);

	if(!(*(vu16 *)REG_WINOUT &  WIN_OBJ_ON))		*(vu16 *)REG_WINOUT|=WIN_OBJ_ON;
	if(!(*(vu16 *)REG_WINOUT & (WIN_OBJ_ON<<8)))	*(vu16 *)REG_WINOUT|=(WIN_OBJ_ON<<8);

	if(!(*(vu16 *)REG_DISPCNT & DISP_OBJ_ON))		*(vu16 *)REG_DISPCNT|=DISP_OBJ_ON;

	// OAM transfer
	DmaArrayCopy(3,fontOam,fontOamAdr,32);
}


//==============================================================
//	fp_itoa
//	itoa process (for FONTPRN)
//
//	Parameter
//		val		value to be converted
//		str		converted character string
//		dig		number of columns
//	Return value
//		Pointer to converted string
//==============================================================
char *fp_itoa(int val,char *str,int dig)
{
	static char *_toa(unsigned int val,char *s,int radix);
	static int _power(int x,int n);
	char	*p;

	p=str;
	if(val<0)
	{
	    *p++='-';
	    val=-val;
	}
	while(dig>1)
	{
		if(val<_power(10,(--dig)))	*p++=0x20;
		else							break;
	}
	*(_toa((unsigned int)val,p,10))='\0';

    return str;
}


//--------------------------------------------------------------
//	_toa
//	Character string conversion process (for internal use)
//
//	Parameter
//		val		value to be converted
//		str		converted string
//		radix	radix
//	Return value
//		Pointer to converted string
//--------------------------------------------------------------
static char *_toa(unsigned int val,char *str,int radix)
{
    char rem;

    rem=val%radix;
    if((val/=radix)!=0)	str=_toa(val,str,radix);
    *str=(rem<10)?(rem+'0'):(rem-10+'a');
    return str+1;
}


//--------------------------------------------------------------
//	_power
//	Raises x to the nth power (for internal use)
//
//	Parameter
//		x		base
//		n		exponent
//	Return value
//		Result of calculation
//--------------------------------------------------------------
static int _power(int x,int n)
{
	int	tmp;
	int	r;

	tmp=(n<0)?-n:n;
	r=1;
	while(tmp)
	{
		if(tmp&1)	r*=x;
		x*=x;	tmp>>=1;
	}
	if(n>=0)	return r;
	else		return 1/r;
}

//--------------------------------------------------------------
