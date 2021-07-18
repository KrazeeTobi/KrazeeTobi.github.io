//
//	RgbLoader.cpp
//
//	Load SGI image and convert to texture data.
//
#include	"RgbLoader.h"

DELIVER* sgiCreateDeliver( unsigned long width , unsigned long height );
bool LoadHeader(IMAGEHEADER *pimh , MCFile* pfile);
BOOL	sgiCreateImage( DELIVER *pdlv , IMAGEHEADER* pimh ,
		        unsigned char *pSrc );

//	tvIsExtention
//
BOOL WINAPI tvIsExtension(const char* pchExt)
{
    if( NULL == pchExt )return	FALSE;
    CString	cstrExt = pchExt;
    if(0 == cstrExt.CompareNoCase("rgb"))  return TRUE;
    if(0 == cstrExt.CompareNoCase("rgba")) return TRUE;
    if(0 == cstrExt.CompareNoCase("int"))  return TRUE;
    if(0 == cstrExt.CompareNoCase("inta")) return TRUE;
    if(0 == cstrExt.CompareNoCase("sgi"))  return TRUE;
    return	FALSE;
}

//
//	tvImageToTexture
//
DELIVER* WINAPI tvImageToTexture(const char* pchFileName)
{
    if( NULL == pchFileName )return	NULL;
    CString	cstrFileName = pchFileName;
    BOOL	bFlag = FALSE;
    BOOL	bRet = FALSE;
    IMAGEHEADER	imh;
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
    DELIVER*		pdlv = NULL;
    DWORD*		pDestPixel = NULL;
    DWORD*		plRleTable = NULL;
    DWORD*		plRleOffset= NULL;
    int i;
    MCFile			infile;

    for(;;)
    {
		//Open file first. 
	bRet = infile.Open((LPCTSTR)cstrFileName,GENERIC_READ,OPEN_EXISTING,0 );
	if(FALSE == bRet)
	{
	    printf("Cannot open file.\n");
	    break;
	}
	infile.SetFilePointer( 0 );

	    //Read image header.

	if( false == LoadHeader(&imh , &infile) ) break;
	alreadyReadSize += sizeof( IMAGEHEADER );

	    //
	    //	Read pixel data.
	    //

	width	= scanlinesize = imh.xsize;
	height	= imh.ysize;
	depth	= imh.zsize;
	scanlinenum = height * depth;
	DWORD	dwNumOfPixel = width*height;
	DWORD	dwNumOfRead = scanlinesize*scanlinenum;

	    //Complete reading file. Create data to return.  
	    //Create DELIVER structure. 

	pdlv = sgiCreateDeliver((DWORD)width , (DWORD)height);
	if( NULL == pdlv ) break;

	pDestPixel = (DWORD*)pdlv->pPixel;
	pcSrc = new unsigned char[dwNumOfRead];
	if( NULL == pcSrc ) break;
	BOOL	bSwRet = FALSE;
	DWORD* pDestTmp = pDestPixel;
	switch( imh.type/0x100 )
	{

		//If noncompressed,   

	    case 0 :
		bSwRet = infile.Read(dwNumOfRead , (char*)pcSrc);
		alreadyReadSize += dwNumOfRead;
		break;

		//If RLE compressed,  

	    case 1 :
		plRleOffset = new unsigned long[scanlinenum];
		plRleTable = new unsigned long[scanlinenum];
		if( NULL == plRleTable || plRleOffset == NULL ) break;
//		bRet = infile.Read( scanlinenum*sizeof(long) ,
//				    (char*)plRleTable );
//		alreadyRead += scanlinenum*sizeof(long);

		    //Read byte size every line. 

		for( i=0 ; i<scanlinenum ; ++i )
		{
		    BufTmp = Buf;
		    bRet = infile.Read( sizeof(long),(char*)Buf );
		    alreadyReadSize += sizeof(long);
		    if( FALSE == bRet )
		    {
			delete[] plRleTable;
			delete[] plRleOffset;
			break;
		    }
		    getDword( &plRleOffset[i] ,&BufTmp );
		}

		    //Read byte size every line. 

		for( i=0 ; i<scanlinenum ; ++i )
		{
		    BufTmp = Buf;
		    bRet = infile.Read( sizeof(long),(char*)Buf );
		    alreadyReadSize += sizeof( long );
		    if( FALSE == bRet )
		    {
			delete[] plRleTable;
			delete[] plRleOffset;
			break;
		    }
		    getDword( &plRleTable[i] ,&BufTmp );
		}
		if( FALSE == bRet ) break;

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
		bRet = infile.Read(dwReadSize , (char*)pcRleSrc);
		if( FALSE == bRet ) break;

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
		bSwRet = TRUE;
		break;
	    default :
		break;
	}
	if( FALSE == bSwRet )break;

	bFlag = sgiCreateImage( pdlv , &imh , pcSrc );

	delete[] pcSrc;
	infile.Close();
	break;
    }
	    //Error processing by reading file. 
    if( FALSE == bFlag )
    {
	infile.Close();
	if( NULL != pcSrc )delete[] pcSrc;
	if( NULL != pRleSrc )delete[] pRleSrc;
	if( NULL != plRleTable )delete[] plRleTable;
	if( NULL != pdlv )DeleteDeliver(pdlv);
	return	NULL;
    }
	    //Name the texture last.  
    CString	cstrBase = GetBaseName(&cstrFileName);
    int	iBaseLength = cstrBase.GetLength();
    if( iBaseLength>8 )iBaseLength=8;
    for( i=0;i<iBaseLength;i++ ){
	pdlv->ptxHeader->name[i] = cstrBase[i];
    }
    return	pdlv;
}
//-----------------------------------------------------------------------
BOOL	sgiCreateImage( DELIVER *pdlv , IMAGEHEADER* pimh ,
		        unsigned char *pSrc )
{
    if( NULL == pdlv || NULL == pimh || NULL == pSrc ) return FALSE;
    int i,j;
    int width  = (int)pimh->xsize;
    int height = (int)pimh->ysize;
    int depth  = (int)pimh->zsize;
    DWORD	dwNumOfPixels = width*height;
    unsigned long *pDestTmp = pdlv->pPixel;
    BOOL    bFlag = FALSE;
    switch( depth )
    {
	case 1 : //If saved in unicolor, convert to black and white.
	    for( i=height-1 ; i>=0 ; i-- )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    *pDestTmp++ = _SETRGBA32(pSrc[i*width+j],
					     pSrc[i*width+j],
					     pSrc[i*width+j],
					     0xff);
		}
	    }
	    bFlag = TRUE;
	    break;
	case 2 : //If saved in two colors, save in such a format as IA.
	    for( i=height-1 ; i>=0 ; i-- )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    *pDestTmp++ = _SETRGBA32(pSrc[i*width+j],
					     pSrc[i*width+j],
					     pSrc[i*width+j],
					     pSrc[i*width+j+dwNumOfPixels]);
		}
	    }
	    bFlag = TRUE;
	    break;
	case 3 : //If saved in RGB, set Alpha for 255.   
	    for( i=height-1 ; i>=0 ; i-- )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    *pDestTmp++ = _SETRGBA32(pSrc[i*width+j],
					     pSrc[i*width+j+dwNumOfPixels],
					     pSrc[i*width+j+dwNumOfPixels*2],
					     0xff);
		}
	    }
	    bFlag = TRUE;
	    break;
	case 4 : //If saved in RGBA,  
	    for( i=height-1 ; i>=0 ; i-- )
	    {
		for( j=0 ; j<width ; j++ )
		{
		    *pDestTmp++ = _SETRGBA32(pSrc[i*width+j],
					     pSrc[i*width+j+dwNumOfPixels],
					     pSrc[i*width+j+dwNumOfPixels*2],
					     pSrc[i*width+j+dwNumOfPixels*3]);
		}
	    }
	    bFlag = TRUE;
	    break;
	default :
	    break;
    }
    return bFlag;
}
//-----------------------------------------------------------------------
DELIVER* sgiCreateDeliver( unsigned long width , unsigned long height )
{
    TEXTUREHEADER txHeader;
    memset(&txHeader,0,sizeof(TEXTUREHEADER));
    txHeader.width = width;
    txHeader.height = height;
    txHeader.fmt = G_IM_FMT_RGBA;
    txHeader.siz = G_IM_SIZ_32b;
    txHeader.pal = 0;
    txHeader.mipmapnum = 0;
    txHeader.tlutmode = G_TT_NONE;
    txHeader.tf = G_TF_POINT;
    txHeader.LoadMode = LOADMODE_TILE;
	//Create DELIVER structure.   
    return CreateDeliver(txHeader);
}
//-----------------------------------------------------------------------
bool LoadHeader(IMAGEHEADER *pimh , MCFile* pfile)
{
    if( NULL == pfile || NULL == pimh )return false;
    unsigned char	Buf[512];
    unsigned char*	BufTmp;
	//Read image header.  
    pfile->SetFilePointer(0);
    if( FALSE == pfile->Read( 512 , (char*)&Buf[0] ) ) return false;
    BufTmp = &Buf[0];
    getWord(&pimh->imagic,&BufTmp);
    getWord(&pimh->type,&BufTmp);
    getWord(&pimh->dim,&BufTmp);
    getWord(&pimh->xsize,&BufTmp);
    getWord(&pimh->ysize,&BufTmp);
    getWord(&pimh->zsize,&BufTmp);
    getDword((DWORD*)&pimh->min,&BufTmp);
    getDword((DWORD*)&pimh->max,&BufTmp);
    getDword((DWORD*)&pimh->wastebytes,&BufTmp);
    BufTmp += 80;
    getDword(&pimh->colormap,&BufTmp);
    return ( 1 == (pimh->type & 0xff) );
}

//---------------------------------------------------------------------

#if 0
void mtvSgiImage::InitParameter()
{
    m_type = 0;
    m_dim = 0;
    m_width = 0;
    m_height = 0;
    m_depth = 0;
    m_min = 0;
    m_max = 255;
    m_name[0] = '\0';
    m_colormap = 0;
    m_plPixelData = NULL;
}

bool mtvSgiImage::LoadHeader(MCFile* pfile)
{
    if( NULL == pfile )return false;
    unsigned char	Buf[512];
    unsigned char*	BufTmp;
    unsigned short	magic;
    unsigned long	dummy;
    //Read image header.
    pfile->SetFilePointer(0);
    bool bRet = (bool)pfile->Read( 512 , (char*)&Buf[0] );
    if( false == bRet )return false;
    BufTmp = &Buf[0];
    getWord(&magic,&BufTmp);
    getWord(&m_type,&BufTmp);
    getWord(&m_dim,&BufTmp);
    getWord(&m_width,&BufTmp);
    getWord(&m_height,&BufTmp);
    getWord(&m_depth,&BufTmp);
    getDword((unsigned long*)&m_min,&BufTmp);
    getDword((unsigned long*)&m_max,&BufTmp);
    getDword(&dummy,&BufTmp);
    BufTmp += 80;
    getDword(&m_colormap,&BufTmp);
    return ( 1 == (m_type & 0xff) );
}

mtvSgiImage::mtvSgiImage()
{
    InitParameter();
}

mtvSgiImage::mtvSgiImage(const char* pchFileName)
{
    Load( pchFileName );
}

mtvSgiImage::~mtvSgiImage()
{
    if( m_plPixelData ) delete[] m_plPixelData;
}

bool	mtvSgiImage::Load( const char* pchFileName )
{
    MCFile file;
    file.Open( pchFileName , GENERIC_READ , OPEN_EXISTING ,0 );
    LoadHeader( &file );
    return true;
}
#endif

//
//
//
//
//