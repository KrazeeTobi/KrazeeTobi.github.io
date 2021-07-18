//======================================================
//    bmpstruct.h
//    Structure to handle bitmaps. Be cautious when using 
//    this header file as the alignment of the structure 
//    is set 2 bytes initially.
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_BMPSTRUCT_
#define	_BMPSTRUCT_

#include <agbtypes.h>

#define	BMP_COMP_RGB	(0)
#define	BMP_COMP_RLE8	(1)
#define	BMP_COMP_RLE4	(2)
#define	BMP_COMP_BITFIELDS	(3)

#pragma pack(2)

typedef struct
{
    u16 bfType;
    u32 bfSize;
    u16 bfReserved1;
    u16 bfReserved2;
    u32 bfOffBits;
} bmp_file_header;

#pragma pack()

typedef struct
{
    u32 biSize;
    s32 biWidth;
    s32 biHeight;
    u16 biPlanes;
    u16 biBitCount;
    u32 biCompression;
    u32 biSizeImage;
    s32 biXPelsPerMeter;
    s32 biYPelsPerMeter;
    u32 biClrUsed;
    u32 biClrImportant;
} bmp_info_header;

typedef struct
{
    u8 rgbBlue;
    u8 rgbGreen;
    u8 rgbRed;
    u8 rgbReserved;
} rgb_quad;

#endif	//  _BMPSTRUCT_

//
//
