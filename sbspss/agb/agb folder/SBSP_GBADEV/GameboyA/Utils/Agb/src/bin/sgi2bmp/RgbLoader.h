//
//
//
//
//
//
//
#ifndef	_RGBLOADER
#define	_RGBLOADER

//#include	<windows.h>
#include	<afx.h>
#include	<string.h>
#include	"../GlobalStruct.h"
#include	"../GlobalFnc.h"
#include	"../Dos/FileName.h"
#include	"../Dos/MCFile.h"
#include	"../../image64/image64.h"

#ifndef	_DLLAPI
#define	_DLLAPI(ret)	extern "C" __declspec(dllexport) ret WINAPI
#endif

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

#if 0

class mtvSgiImage
{
protected :
	unsigned short	m_type;
	unsigned short	m_dim;
	unsigned short	m_width;
	unsigned short	m_height;
	unsigned short	m_depth;
	unsigned long	m_min;
	unsigned long	m_max;
	char			m_name[80];
	unsigned long	m_colormap;
	unsigned long*	m_plPixelData;
private :
	void	InitParameter();
	bool	LoadHeader(MCFile* pfile);
	bool	LoadPixelData(MCFile* pfile);
public :
	mtvSgiImage();
	mtvSgiImage( const char* pchFileName );
	~mtvSgiImage();

	bool	Load( const char* pchFileName );

	const unsigned short&	GetWidth(){return m_width;};
	void	SetWidth(const unsigned short& width){m_width=width;};
	const unsigned short&	GetHeight(){return m_height;};
	void	SetHeight(const unsigned short& height){m_height=height;};
	const unsigned short&	GetDepth(){return m_depth;};
	void	SetDepth(const unsigned short& depth){m_depth=depth;};
};

#endif


	//Verify if the extension is for this module. 
_DLLAPI(BOOL) tvIsExtension(const char*);
	//Convert to texture data.  
_DLLAPI(DELIVER*) tvImageToTexture(const char*);

#endif	//_RGBLOADER
//
//
//
//
//
