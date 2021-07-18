//======================================================
//    fontprn.c
//    �R���\�[���ɕ�������o�͂��郋�[�`��
//
//    Copyright (C) 1999,NINTENDO Co.,Ltd.
//======================================================

#define	_FONTPRN_C_

#include <agb.h>
#include "fontprn.h"
#include "font8.h"

//-------------------------- �萔 ------------------------------

#define	fpOBJSIZE	64				// OBJ�̃T�C�Y
#define	fpFONTSIZE	8				// �t�H���g�T�C�Y
#define	fpMAXOBJS	4*3				// �ő�OBJ��
#define	fpMAXCOL	30				// �ő包��
#define	fpMAXROW	20				// �ő�s��

//------------------------- �}�N�� -----------------------------

#define fontInit	fpdata.init
#define fontColor	fpdata.color
#define fontVram	fpdata.obj_vram_adr
#define fontChar	fpdata.char_st
#define fontOamAdr	fpdata.oam_adr
#define fontOam		fpdata.oam_dt

//------------------------- �\���� -----------------------------

typedef struct
{
	u8		init;					// �������t���O
	u8		color;					// ���݂̐F
	u32		obj_vram_adr;			// �]����VRAM�ʒu
	u16		char_st;				// �L�����N�^�ԍ��̊J�n�ʒu
	u32		oam_adr;				// �]����OAM�ʒu
	OamData	oam_dt[fpMAXOBJS];		// OAM�f�[�^
	u32		adr[fpMAXCOL*fpMAXROW];
} fpData;

//------------------------- OAM���^ ----------------------------

const u32 fontOamData[1][2] = {
		{ OAM_COLOR_16
//		| OAM_H_SIZE_64DOT
//		| OAM_V_SIZE_64DOT
		| OAM_SIZE_64x64

		| 0 << OAM_H_POS_SHIFT
		| 0 << OAM_V_POS_SHIFT,
		 0},
	};

//---------------------- ���[�J���ϐ� --------------------------

static fpData	fpdata;

//-------------------- �T�u���[�`���錾 ------------------------

static void put_font_1d(u8 x,u8 y,u8 *str,u16 len);
static void put_font_2d(u8 x,u8 y,u8 *str,u16 len);

//==============================================================
//	FontPrintInit
//	�t�H���g����������
//
//	����
//		x,y		�\���ʒu
//		col		�\�������i���ݖ��g�p�j
//		row		�\���s���i���ݖ��g�p�j
//		vram	VRAM�g�p�J�n�ʒu
//		pltno	�p���b�g�ԍ�
//	�߂�l
//		�Ȃ�
//==============================================================
void FontPrintInit(u8 x,u8 y,u8 col,u8 row,u32 vram,u8 pltno)
{
	u8	i;
	u8	objs;

	// �����������h�~
	if(fontInit==1)
		return;

	fontInit=1;
	fontColor=0x0f;

	// �ő�l�ւ̊ۂ�
	if(col>30)	col=30;
	if(row>20)	row=20;

	// �n�a�i�̎g�p�������߂�
	objs=(col/fpFONTSIZE)*(row/fpFONTSIZE);

	// �\���������ݒ�
	// �\���ʒu�ݒ�

	fontVram=vram;
	fontChar=(fontVram-OBJ_MODE0_VRAM)/32;
	//fontChar=(fontVram-OBJ_MODE4_VRAM)/32;

	// �n�`�l�ݒ�
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
//	�T���v���p���b�g�̃��[�h
//
//	����
//		pltno	�p���b�g�ԍ�
//	�߂�l
//		�Ȃ�
//==============================================================
void FontPalletLoad(u8 pltno)
{
	// �p���b�g�f�[�^
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
//	�t�H���g�J���[�̕ύX
//
//	����
//		color	�F�ԍ��i�F�̓p���b�g�Ɉˑ��j
//	�߂�l
//		�Ȃ�
//==============================================================
void FontColor(u8 color)
{
	fontColor=color;
}


//==============================================================
//	FontPrint
//	�t�H���g�Z�b�g����
//
//	����
//		x,y		�\���ʒu
//		str		�\��������
//	�߂�l
//		�Ȃ�
//==============================================================
void FontPrint(u8 x,u8 y,u8 *str)
{
	u16	len,i;

	if(!fontInit)	return;
	if(!fontColor)	return;

	// ���������J�E���g����istrlen�j
	for(len=0;;len++)
	{	if(!str[len])	break;	}
	if(!len)	return;

	// �n�a�i�L�����N�^�̃}�b�s���O���[�h�ɉ������\��
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
//	�t�H���g�Z�b�g�����i���l�p�j
//
//	����
//		x,y		�\���ʒu
//		val		�\���l
//		dig		�\������
//	�߂�l
//		�Ȃ�
//==============================================================
void NumPrint(u8 x,u8 y,s16 val,s16 dig)
{
	char buf[8];
	fp_itoa(val,buf,dig);
	FontPrint(x,y,buf);
}


//==============================================================
//	put_font_1d
//	�t�H���g�\�������i�P�c�Łj
//
//	����
//		x,y		�\���ʒu
//		str		�\��������
//		len		������̒���
//	�߂�l
//		�Ȃ�
//==============================================================
static void put_font_1d(u8 x,u8 y,u8 *str,u16 len)
{
	u16	i;
	u8	px,py;

	px=x,py=y;
	for(i=0;i<len;i++)
	{
		// ���s
		if(str[i]=='\n')
		{
			px=x,py++;
			continue;
		}

		// �n�a�i�L�����N�^�Z�b�g
		DmaCopy(3,font8[fontColor-1]+(u32)(str[i]*8),
			fontVram+((px%8)+(px>>3)*64+(py%8)*8+(py/8)*256)*32,32,32);
		px++;

		// �����I�ȉ��s
		if(!(px%fpMAXCOL))
		{
			px=x,py++;
		}
	}
}


//==============================================================
//	put_font_2d
//	�t�H���g�\�������i�Q�c�Łj
//
//	����
//		x,y		�\���ʒu
//		str		�\��������
//		len		������̒���
//	�߂�l
//		�Ȃ�
//==============================================================
static void put_font_2d(u8 x,u8 y,u8 *str,u16 len)
{
	u16	i;
	u8	px,py;

	px=x,py=y;
	for(i=0;i<len;i++)
	{
		// ���s
		if(str[i]=='\n')
		{
			px=x,py++;
			continue;
		}

		// �n�a�i�L�����N�^�Z�b�g
		DmaCopy(3,font8[fontColor-1]+(u32)(str[i]*8),
			fontVram+((px)+(py*0x20))*32,32,32);
		px++;

		// �����I�ȉ��s
		if(!(px%fpMAXCOL))
		{
			px=x,py++;
		}
	}
}


//==============================================================
//	FontPrintC
//	�t�H���g�Z�b�g�����i�F�t���j
//
//	����
//		x,y		�\���ʒu
//		color	�F�ԍ�
//		str		�\��������
//	�߂�l
//		�Ȃ�
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
//	�t�H���g�Z�b�g�����i���l�p�F�t���j
//
//	����
//		x,y		�\���ʒu
//		color	�F�ԍ�
//		val		�\���l
//		dig		�\������
//	�߂�l
//		�Ȃ�
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
//	�t�H���g�N���A����
//
//	����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//==============================================================
void FontPrintCls(void)
{
	if(!fontInit)	return;

	DmaClear(3,0,fontVram,(OBJ_VRAM_END-fontVram),16);
}


//==============================================================
//	FontPrintSync
//	VSync����
//
//	����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//==============================================================
void FontPrintSync(void)
{
	if(!fontInit)	return;

	// �t���O�̕␳
	if(!(*(vu16 *)REG_WININ &  WIN_OBJ_ON))			*(vu16 *)REG_WININ|=WIN_OBJ_ON;
	if(!(*(vu16 *)REG_WININ & (WIN_OBJ_ON<<8)))		*(vu16 *)REG_WININ|=(WIN_OBJ_ON<<8);

	if(!(*(vu16 *)REG_WINOUT &  WIN_OBJ_ON))		*(vu16 *)REG_WINOUT|=WIN_OBJ_ON;
	if(!(*(vu16 *)REG_WINOUT & (WIN_OBJ_ON<<8)))	*(vu16 *)REG_WINOUT|=(WIN_OBJ_ON<<8);

	if(!(*(vu16 *)REG_DISPCNT & DISP_OBJ_ON))		*(vu16 *)REG_DISPCNT|=DISP_OBJ_ON;

	// �n�`�l�̓]��
	DmaArrayCopy(3,fontOam,fontOamAdr,32);
}


//==============================================================
//	fp_itoa
//	itoa�����iFONTPRN�p�j
//
//	����
//		val		�ϊ�����l
//		str		�ϊ����ꂽ������
//		dig		����
//	�߂�l
//		�ϊ����ꂽ������̃|�C���^
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
//	������ϊ������i�����p�j
//
//	����
//		val		�ϊ�����l
//		str		�ϊ����ꂽ������
//		radix	�i��
//	�߂�l
//		�ϊ����ꂽ������̃|�C���^
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
//	�ݏ揈���i�����p�j
//
//	����
//		x		�
//		n		�ׂ���
//	�߂�l
//		�v�Z��̒l
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