//======================================================
//    image.h                                           
//    sgi2bmp SGI format load & save                           
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_PIC_CREATE_
#define	_PIC_CREATE_

#include <iostream>
#include <filename.h>
#include <pathname.h>
#include <agbtypes.h>
#include <color.h>
#include <hpicture.h>

typedef struct {
    unsigned short	imagic;		/* stuff saved on disk . . */
    unsigned short 	type;
    unsigned short 	dim;
    unsigned short 	xsize;
    unsigned short 	ysize;
    unsigned short 	zsize;
    unsigned long 	min;
    unsigned long 	max;
    unsigned long	wastebytes;	
    char 		name[80];
    unsigned long	colormap;
    char	dummy[404];

//	long 		file;		/* stuff used in core only */
//	unsigned short 	flags;
//	short		dorev;
//	short		x;
//	short		y;
//	short		z;
//	short		cnt;
//	unsigned short	*ptr;
//	unsigned short	*base;
//	unsigned short	*tmpbuf;
//	unsigned long	offset;
//	unsigned long	rleend;		/* for rle images */
//	unsigned long	*rowstart;	/* for rle images */
//	long		*rowsize;	/* for rle images */
} IMAGEHEADER;

__USING__MAGBX;

HPicture* sgiImageLoad(  FileName& filename ,
		   char flag , short tp , Color& color );
//-----------------------------------------------------------------------

#endif	// _PIC_CREATE_
//
//
//

