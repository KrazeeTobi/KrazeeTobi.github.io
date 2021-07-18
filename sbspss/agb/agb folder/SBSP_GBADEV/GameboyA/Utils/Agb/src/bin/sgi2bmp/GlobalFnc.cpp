//======================================================
//    globalfnc.cpp                                           
//    Frequently used functions                       
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include	"GlobalFnc.h"

void	setByte(u8 data,u8** ppBuf)
{
	**ppBuf = data;
	(*ppBuf)++;
}

void	setWord(u16 data,u8** ppBuf)
{
	setByte((u8)(data/0x100),ppBuf);
	setByte((u8)(data&0xff),ppBuf);
}

void	setDword(u32 data,u8** ppBuf)
{
	setByte((u8)(data/0x1000000),ppBuf);
	setByte((u8)((data&0xff0000)/0x10000),ppBuf);
	setByte((u8)((data&0xff00)/0x100),ppBuf);
	setByte((u8)(data&0xff),ppBuf);
}


//
//	getByte,getWord,getUint,getChar,getShort,getLong
//
//	Convert each from an unsigned char buffer
//
void	getByte(u8* data,u8** ppBuf)
{
	*data = **ppBuf;
	(*ppBuf)++;
}

void	getChar(char* data,u8** ppBuf)
{
	u8	dataTmp;
	getByte(&dataTmp,ppBuf);
	*data = (char)dataTmp;
}

void	getWord(u16* data,u8** ppBuf)
{
	u8	dataTmp[2];
	getByte(&dataTmp[0],ppBuf);
	getByte(&dataTmp[1],ppBuf);
	*data = (u16)(dataTmp[0]*0x100+dataTmp[1]);
}

void	getShort(short* data,u8** ppBuf)
{
	u16	dataTmp;
	getWord( &dataTmp , ppBuf );
	*data = (short)dataTmp;
}

void	getDword(u32* data,u8** ppBuf)
{
	u8	dataTmp[4];
	getByte(&dataTmp[0],ppBuf);
	getByte(&dataTmp[1],ppBuf);
	getByte(&dataTmp[2],ppBuf);
	getByte(&dataTmp[3],ppBuf);
	*data = (u32)(u8)dataTmp[0]*0x1000000+(u32)(u8)dataTmp[1]*0x10000
			+(u32)(u8)dataTmp[2]*0x100+(u32)(u8)dataTmp[3];
}

void	getLong(long* data,u8** ppBuf)
{
	u32	dataTmp;
	getDword(&dataTmp,ppBuf);
	*data = (long)dataTmp;
}

