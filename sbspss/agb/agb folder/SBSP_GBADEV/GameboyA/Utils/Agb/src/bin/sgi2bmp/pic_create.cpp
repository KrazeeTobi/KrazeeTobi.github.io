//======================================================
//    pic_create.cpp                                           
//    sgi2bmp SGI format load & save                           
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <windows.h>
#include <iostream>
#include <filename.h>
#include <agbtypes.h>
#include <color.h>
#include <hpicture.h>
#include "globalfnc.h"
#include "pic_create.h"

__USING__MAGBX;
//--------------------------------------------------------------------------
static bool sgiLoadHeader(IMAGEHEADER& imh , std::ifstream& in);
static bool sgiCreateImage( HPicture &pic , IMAGEHEADER& imh ,
		        unsigned char *pSrc ,
			char flag , short tp , Color& color);
//--------------------------------------------------------------------------
HPicture* sgiImageLoad( FileName &filename , char flag , short tp , Color& color )
{
    bool	bFlag = false;
    IMAGEHEADER	imh;
    std::ifstream   in;
    bool	bRet = true;

    DWORD	NumOfColors = 0;
    DWORD	dwFromBegin = 0;
    DWORD	alreadyReadSize=0;
    static	unsigned char	Buf[512];
    unsigned char*	BufTmp = Buf;
    unsigned short	scanlinesize,scanlinenum,width,height,depth;
    unsigned char*	pcSrc = NULL;
    unsigned char*	pRleSrc = NULL;
    unsigned char*	pcRleTmp = NULL;
    unsigned char*	pcSrcTmp = NULL;
    unsigned char*	pcRleSrc = NULL;
    DWORD*		plRleTable = NULL;
    DWORD*		plRleOffset= NULL;
    int i;
    HPicture*	pic_ptr = NULL;

    for(;;)
    {
		//Open file first.
	in.open(filename.c_str(),std::ios::in|std::ios::binary );
	if( !in.is_open() )
	{
	    std::cerr << "Cannot open file." << std::endl;
	    break;
	}

	    //Read image header. 

	if( false == sgiLoadHeader(imh , in) ) break;
	alreadyReadSize += sizeof( IMAGEHEADER );

	    //
	    //	Read pixel data. 
	    //

	width	= scanlinesize = imh.xsize;
	height	= imh.ysize;
	pic_ptr = new HPicture( width,height );
	if( NULL == pic_ptr ) break;
	depth	= imh.zsize;
	scanlinenum = height * depth;
	DWORD	dwNumOfPixel = width*height;
	DWORD	dwNumOfRead = scanlinesize*scanlinenum;

	    //Complete reading file. Create data to return.  
	    //Create DELIVER structure. 

	pcSrc = new unsigned char[dwNumOfRead];
	if( NULL == pcSrc ) break;
	switch( imh.type/0x100 )
	{

		//If noncompressed,

	    case 0 :
		bFlag = !(!(in.read( (char*)pcSrc , dwNumOfRead )));
		break;

		//If RLE compressesd,  

	    case 1 :
		plRleOffset = new unsigned long[scanlinenum];
		plRleTable = new unsigned long[scanlinenum];
		if( NULL == plRleTable || plRleOffset == NULL ) break;

		    //Read byte size every line.  

		for( i=0 ; i<scanlinenum ; ++i )
		{
		    BufTmp = Buf;
		    if( !in.read( (char*)Buf,sizeof(long) ) )
		    {
			delete[] plRleTable;
			delete[] plRleOffset;
			bRet = false;
			break;
		    }
		    alreadyReadSize += sizeof(long);
		    getDword( &plRleOffset[i] ,&BufTmp );
		}
		if( false == bRet ) break;

		    //Read byte size every line.

		for( i=0 ; i<scanlinenum ; ++i )
		{
		    BufTmp = Buf;
		    if( !in.read( (char*)Buf,sizeof(long) ) )
		    {
			delete[] plRleTable;
			delete[] plRleOffset;
			bRet = false;
			break;
		    }
		    alreadyReadSize += sizeof(long);
		    getDword( &plRleTable[i] ,&BufTmp );
		}
		if( false == bRet ) break;

		for( i=0 ; i<scanlinenum ; ++i )
		{
		    plRleOffset[i] -= alreadyReadSize;
		}
		    //Read all the compressed data.

		DWORD dwReadSize;
		dwReadSize = 0;

		    //Calculate data size. 

		for( i=0 ; i<scanlinenum ; i++ )
		{
		    dwReadSize += (unsigned long)(plRleTable[i]);
		}
		    //Free unneeded memory.

		delete[] plRleTable;

		    //Reserve RLE read area.  

		pcRleSrc = new unsigned char[dwReadSize];
		if( NULL == pcRleSrc ) break;
		if( !in.read( (char*)pcRleSrc,dwReadSize) )
		{
		    bRet = false;
		}
		if( false == bRet ) break;

		    //Decompress  

		pcRleTmp = pcRleSrc;
		pcSrcTmp = pcSrc;
		unsigned char pixel,count;
		for( i=0 ; i<scanlinenum ; i++ )
		{
		    pcRleTmp = pcRleSrc + plRleOffset[i];
 		    while(1)
		    {
 			pixel = *pcRleTmp++;
 			count = pixel & 0x7f;
 			    /*Continue till 0.*/
 			if ( !count ) break;
 			if(pixel & 0x80)
			{
			    while(count--) *pcSrcTmp++ = *pcRleTmp++;
 			}
			else
			{
			    pixel = *pcRleTmp++;
			    while(count--) *pcSrcTmp++ = pixel;
			}//else
		    }//while
		}//for
		delete[] pcRleSrc;
		delete[] plRleOffset;
		bFlag = true;
		break;
	    default :
		break;
	}
	if( false == bFlag ) break;

	bFlag = sgiCreateImage( *pic_ptr , imh , pcSrc, flag , tp , color );

	delete[] pcSrc;
	in.close();
	break;
    }

    in.close();
    if( NULL != pcSrc )delete[] pcSrc;
    if( NULL != pRleSrc )delete[] pRleSrc;
    if( NULL != plRleTable )delete[] plRleTable;
    if( NULL != plRleOffset )delete[] plRleOffset;
    if( false == bFlag )
    {
	delete pic_ptr;
	return NULL;
    }

    return pic_ptr;
}
//-----------------------------------------------------------------------
static bool	sgiCreateImage( HPicture& pic , IMAGEHEADER& imh ,
		        unsigned char *pSrc , char flag , short tp , Color& bkcolor)
{
    if( NULL == pSrc ) return FALSE;
    int i,j;
    int width  = (int)imh.xsize;
    int height = (int)imh.ysize;
    int depth  = (int)imh.zsize;
    u32	dwNumOfPixels = width*height;
    pic.Resize( (u32)width, (u32)height );

    Color color;
    unsigned char red , green , blue;
    red = bkcolor.Red();
    green = bkcolor.Green();
    blue = bkcolor.Blue();

    bool    bFlag = false;
    switch( depth )
    {
	case 1 : //If saved in unicolor, convert to black and white.
	    for( i=0 ; i<height ; ++i )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    color.Set( pSrc[i*width+j],pSrc[i*width+j],pSrc[i*width+j]);
		    pic.Set( color,j,height-i-1);
		}
	    }
	    bFlag = true;
	    break;
	case 2 : //If saved in two colors, save in such a format as IA.  
	    for( i=0 ; i<height ; ++i )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    if( flag )
		    {
			if( pSrc[i*width+j+dwNumOfPixels*3] <= tp )
			{
			    pic.Set( bkcolor,j,height-i-1);
			    continue;
			}
		    } 
		    color.Set( pSrc[i*width+j],pSrc[i*width+j],pSrc[i*width+j]);
		    pic.Set( color,j,height-i-1);
		}
	    }
	    bFlag = true;
	    break;
	case 3 : //If saved in RGB, set Alpha for 255.  
	    for( i=0 ; i<height ; ++i )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    color.Set( pSrc[i*width+j] ,
			     pSrc[i*width+j+dwNumOfPixels] ,
			     pSrc[i*width+j+dwNumOfPixels*2] );
		    pic.Set( color,j,height-i-1);
		}
	    }
	    bFlag = true;
	    break;
	case 4 : //If saved in RGBA,   
	    for( i=0 ; i<height ; ++i )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    if( flag )
		    {
			if( pSrc[i*width+j+dwNumOfPixels*3] <= tp )
			{
			    pic.Set( bkcolor,j,height-i-1);
			    continue;
			}
		    } 
		    color.Set( pSrc[i*width+j] ,
			     pSrc[i*width+j+dwNumOfPixels] ,
			     pSrc[i*width+j+dwNumOfPixels*2] );
		    pic.Set( color,j,height-i-1);
		}
	    }
	    bFlag = true;
	    break;
	default :
	    break;
    }
    return bFlag;
}
//-----------------------------------------------------------------------
static bool sgiLoadHeader(IMAGEHEADER& imh , std::ifstream& in)
{
    if( false == in.is_open() ) return false;
    unsigned char	Buf[512];
    unsigned char*	BufTmp;
	//Read image header.
    if( !(in.read( (char*)Buf, 512)) ) return false;
    BufTmp = &Buf[0];
    getWord(&imh.imagic,&BufTmp);
    if( imh.imagic != 0x01da )
    {
	std::cout << "Not SGI format" << std::endl;
	return false;
    }
    getWord(&imh.type,&BufTmp);
    getWord(&imh.dim,&BufTmp);
    getWord(&imh.xsize,&BufTmp);
    getWord(&imh.ysize,&BufTmp);
    getWord(&imh.zsize,&BufTmp);
    getDword((u32*)&imh.min,&BufTmp);
    getDword((u32*)&imh.max,&BufTmp);
    getDword((u32*)&imh.wastebytes,&BufTmp);
    BufTmp += 80;
    getDword(&imh.colormap,&BufTmp);
    return ( 1 == (imh.type & 0xff) );
}
//-----------------------------------------------------------------------

//
//
//
