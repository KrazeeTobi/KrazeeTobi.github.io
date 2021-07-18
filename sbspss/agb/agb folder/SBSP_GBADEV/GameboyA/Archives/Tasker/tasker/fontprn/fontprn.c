//======================================================
//    fontprn.c
//    コンソールに文字列を出力するルーチン
//
//    Copyright (C) 1999,NINTENDO Co.,Ltd.
//======================================================

#define	_FONTPRN_C_

#include <agb.h>
#include "fontprn.h"
#include "font8.h"

//-------------------------- 定数 ------------------------------

#define	fpOBJSIZE	64				// OBJのサイズ
#define	fpFONTSIZE	8				// フォントサイズ
#define	fpMAXOBJS	4*3				// 最大OBJ数
#define	fpMAXCOL	30				// 最大桁数
#define	fpMAXROW	20				// 最大行数

//------------------------- マクロ -----------------------------

#define fontInit	fpdata.init
#define fontColor	fpdata.color
#define fontVram	fpdata.obj_vram_adr
#define fontChar	fpdata.char_st
#define fontOamAdr	fpdata.oam_adr
#define fontOam		fpdata.oam_dt

//------------------------- 構造体 -----------------------------

typedef struct
{
	u8		init;					// 初期化フラグ
	u8		color;					// 現在の色
	u32		obj_vram_adr;			// 転送先VRAM位置
	u16		char_st;				// キャラクタ番号の開始位置
	u32		oam_adr;				// 転送先OAM位置
	OamData	oam_dt[fpMAXOBJS];		// OAMデータ
	u32		adr[fpMAXCOL*fpMAXROW];
} fpData;

//------------------------- OAM雛型 ----------------------------

const u32 fontOamData[1][2] = {
		{ OAM_COLOR_16
//		| OAM_H_SIZE_64DOT
//		| OAM_V_SIZE_64DOT
		| OAM_SIZE_64x64

		| 0 << OAM_H_POS_SHIFT
		| 0 << OAM_V_POS_SHIFT,
		 0},
	};

//---------------------- ローカル変数 --------------------------

static fpData	fpdata;

//-------------------- サブルーチン宣言 ------------------------

static void put_font_1d(u8 x,u8 y,u8 *str,u16 len);
static void put_font_2d(u8 x,u8 y,u8 *str,u16 len);

//==============================================================
//	FontPrintInit
//	フォント初期化処理
//
//	引数
//		x,y		表示位置
//		col		表示桁数（現在未使用）
//		row		表示行数（現在未使用）
//		vram	VRAM使用開始位置
//		pltno	パレット番号
//	戻り値
//		なし
//==============================================================
void FontPrintInit(u8 x,u8 y,u8 col,u8 row,u32 vram,u8 pltno)
{
	u8	i;
	u8	objs;

	// 複数初期化防止
	if(fontInit==1)
		return;

	fontInit=1;
	fontColor=0x0f;

	// 最大値への丸め
	if(col>30)	col=30;
	if(row>20)	row=20;

	// ＯＢＪの使用数を求める
	objs=(col/fpFONTSIZE)*(row/fpFONTSIZE);

	// 表示文字数設定
	// 表示位置設定

	fontVram=vram;
	fontChar=(fontVram-OBJ_MODE0_VRAM)/32;
	//fontChar=(fontVram-OBJ_MODE4_VRAM)/32;

	// ＯＡＭ設定
	for(i=0;i<fpMAXOBJS;i++)
	{
		fontOam[i] = *(OamData *)fontOamData;
		fontOam[i].CharNo = fontChar+i*64;
		fontOam[i].HPos = x+(i%4)*64;
		fontOam[i].VPos = y+(i/4)*64;
		fontOam[i].Pltt = pltno;

		//fpdata.oam_dt[i].ObjMode = 1;


	}
	fontOamAdr=(OAM+OAM_SIZE)-(8*fpMAXOBJS);
	DmaArrayCopy(3,fontOam,fontOamAdr,32);

	*(vu16 *)REG_DISPCNT |= DISP_OBJ_ON;		// OBJ ON
}

//==============================================================
//	FontPalletLoad
//	サンプルパレットのロード
//
//	引数
//		pltno	パレット番号
//	戻り値
//		なし
//==============================================================
void FontPalletLoad(u8 pltno)
{
	// パレットデータ
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
//	フォントカラーの変更
//
//	引数
//		color	色番号（色はパレットに依存）
//	戻り値
//		なし
//==============================================================
void FontColor(u8 color)
{
	fontColor=color;
}


//==============================================================
//	FontPrint
//	フォントセット処理
//
//	引数
//		x,y		表示位置
//		str		表示文字列
//	戻り値
//		なし
//==============================================================
void FontPrint(u8 x,u8 y,u8 *str)
{
	u16	len,i;

	if(!fontInit)	return;
	if(!fontColor)	return;

	// 文字数をカウントする（strlen）
	for(len=0;;len++)
	{	if(!str[len])	break;	}
	if(!len)	return;

	// ＯＢＪキャラクタのマッピングモードに応じた表示
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
//	フォントセット処理（数値用）
//
//	引数
//		x,y		表示位置
//		val		表示値
//		dig		表示桁数
//	戻り値
//		なし
//==============================================================
void NumPrint(u8 x,u8 y,s16 val,s16 dig)
{
	char buf[8];
	fp_itoa(val,buf,dig);
	FontPrint(x,y,buf);
}


//==============================================================
//	put_font_1d
//	フォント表示処理（１Ｄ版）
//
//	引数
//		x,y		表示位置
//		str		表示文字列
//		len		文字列の長さ
//	戻り値
//		なし
//==============================================================
static void put_font_1d(u8 x,u8 y,u8 *str,u16 len)
{
	u16	i;
	u8	px,py;

	px=x,py=y;
	for(i=0;i<len;i++)
	{
		// 改行
		if(str[i]=='\n')
		{
			px=x,py++;
			continue;
		}

		// ＯＢＪキャラクタセット
		DmaCopy(3,font8[fontColor-1]+(u32)(str[i]*8),
			fontVram+((px%8)+(px>>3)*64+(py%8)*8+(py/8)*256)*32,32,32);
		px++;

		// 内部的な改行
		if(!(px%fpMAXCOL))
		{
			px=x,py++;
		}
	}
}


//==============================================================
//	put_font_2d
//	フォント表示処理（２Ｄ版）
//
//	引数
//		x,y		表示位置
//		str		表示文字列
//		len		文字列の長さ
//	戻り値
//		なし
//==============================================================
static void put_font_2d(u8 x,u8 y,u8 *str,u16 len)
{
	u16	i;
	u8	px,py;

	px=x,py=y;
	for(i=0;i<len;i++)
	{
		// 改行
		if(str[i]=='\n')
		{
			px=x,py++;
			continue;
		}

		// ＯＢＪキャラクタセット
		DmaCopy(3,font8[fontColor-1]+(u32)(str[i]*8),
			fontVram+((px)+(py*0x20))*32,32,32);
		px++;

		// 内部的な改行
		if(!(px%fpMAXCOL))
		{
			px=x,py++;
		}
	}
}


//==============================================================
//	FontPrintC
//	フォントセット処理（色付き）
//
//	引数
//		x,y		表示位置
//		color	色番号
//		str		表示文字列
//	戻り値
//		なし
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
//	フォントセット処理（数値用色付き）
//
//	引数
//		x,y		表示位置
//		color	色番号
//		val		表示値
//		dig		表示桁数
//	戻り値
//		なし
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
//	フォントクリア処理
//
//	引数
//		なし
//	戻り値
//		なし
//==============================================================
void FontPrintCls(void)
{
	if(!fontInit)	return;

	DmaClear(3,0,fontVram,(OBJ_VRAM_END-fontVram),16);
}


//==============================================================
//	FontPrintSync
//	VSync処理
//
//	引数
//		なし
//	戻り値
//		なし
//==============================================================
void FontPrintSync(void)
{
	if(!fontInit)	return;

	// フラグの補正
	if(!(*(vu16 *)REG_WININ &  WIN_OBJ_ON))			*(vu16 *)REG_WININ|=WIN_OBJ_ON;
	if(!(*(vu16 *)REG_WININ & (WIN_OBJ_ON<<8)))		*(vu16 *)REG_WININ|=(WIN_OBJ_ON<<8);

	if(!(*(vu16 *)REG_WINOUT &  WIN_OBJ_ON))		*(vu16 *)REG_WINOUT|=WIN_OBJ_ON;
	if(!(*(vu16 *)REG_WINOUT & (WIN_OBJ_ON<<8)))	*(vu16 *)REG_WINOUT|=(WIN_OBJ_ON<<8);

	if(!(*(vu16 *)REG_DISPCNT & DISP_OBJ_ON))		*(vu16 *)REG_DISPCNT|=DISP_OBJ_ON;

	// ＯＡＭの転送
	DmaArrayCopy(3,fontOam,fontOamAdr,32);
}


//==============================================================
//	fp_itoa
//	itoa処理（FONTPRN用）
//
//	引数
//		val		変換する値
//		str		変換された文字列
//		dig		桁数
//	戻り値
//		変換された文字列のポインタ
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
//	文字列変換処理（内部用）
//
//	引数
//		val		変換する値
//		str		変換された文字列
//		radix	進数
//	戻り値
//		変換された文字列のポインタ
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
//	累乗処理（内部用）
//
//	引数
//		x		基数
//		n		べき数
//	戻り値
//		計算後の値
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
