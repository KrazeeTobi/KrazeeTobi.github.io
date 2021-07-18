//======================================================
//    globalfnc.h                                           
//    Read sgi2bmp big endian                        
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#ifndef	_GLOBALFNC
#define	_GLOBALFNC

#include <agbtypes.h>

void	setByte(u8 data,u8** ppBuf);
void	setWord(u16 data,u8** ppBuf);
void	setDword(u32 data,u8** ppBuf);
void	getByte(u8* data,u8** ppBuf);
void	getChar(char* data,u8** ppBuf);
void	getWord(u16* data,u8** ppBuf);
void	getShort(short* data,u8** ppBuf);
void	getDword(u32* data,u8** ppBuf);
void	getLong(long* data,u8** ppBuf);


#endif	//_GLOBALFNC