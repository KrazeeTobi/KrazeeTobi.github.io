//======================================================
//    picture.h                                           
//    Class to handle an image with a palette.
//    Class for transactions between Windows Bitmap and 
//    AGB images.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_PICTURE_
#define	_AGB_PICTURE_

#include <CString>
#include <agbtypes.h>
#include <palette.h>
#include <filename.h>
#include <character.h>
#include <bmpstruct.h>
#include <util.h>

__MAGBX__START

class Picture : public AGBObject
{
public :
    typedef Picture _Myt;
    typedef Image<u8> _Im;

protected :
    Palette m_palette;
    u8 m_bit_count;
    _Im m_image;

    virtual u32 get_num_of_colors( bmp_info_header& bmih );
    virtual bool load_palette( std::ifstream& in , u32 num_of_colors );

    virtual bool load_bmp_rle8b( std::ifstream& in, u8* pixel_ptr,
				 u32 width, u32 height);
    virtual bool load_bmp_rle4b( std::ifstream& in, u8* pixel_ptr,
				 u32 width, u32 height);
    virtual void rle4b_set_pixel( u8** pixel_pptr, u32* x_ptr, u8 pixel_data );
    virtual void rle4b_set_pixel_2dot( u8** pixel_pptr, u32* x_ptr, u8 pixel_data );

    virtual bool load_bmp( std::ifstream& in );
    virtual bool save_bmp( std::ofstream &out );

public :
    Picture( u32 width=0 , u32 height=0 ) :
       m_image(width , height) , m_palette( 256 ){}
    Picture( const _Myt& _X ) :
	m_image( ((_Myt&)_X).GetImage() ) , m_palette(((_Myt&)_X).GetPalette()) ,
	m_bit_count( ((_Myt&)_X).BitCount() )
	    {}
    Picture( const FileName& fname ){LoadBmp( fname );}

    virtual ~Picture(){}

    virtual bool LoadBmp( const FileName& fname );
    virtual bool LoadBmp( const std::string& fname );
    virtual bool LoadBmp( const char* fname );
    virtual bool SaveBmp( const FileName& fname );
    virtual bool SaveBmp( const std::string& fname );
    virtual bool SaveBmp( const char* fname );

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );

//
//
//	Launcher for Image 
//
//

    virtual u32 Width(){return m_image.Width();}
    virtual u32 Height(){return m_image.Height();}
    virtual void Set(u8 _P,u32 _x,u32 _y){m_image.Set( _P, _x, _y);}
    virtual void Set(const _Im& _X,u32 _x,u32 _y,u32 wd=0,u32 ht=0)
	{ m_image.Set( _X, _x, _y, wd , ht );}
    virtual void Set( const _Im& _X, u32 _x, u32 _y ,const Rect& rc )
	{ m_image.Set( _X, _x, _y, rc );}
    virtual void Set( const _Im& _X ){m_image.Set( _X );}
    virtual _Myt& operator=(const _Im& _X)
	{
	    m_image.Duplicate( _X );
	    return (*this);
	}
    virtual void Set(const _Myt& _X,u32 _x,u32 _y,u32 wd=0,u32 ht=0)
	{m_image.Set( ((_Myt&)_X).GetImage(), _x, _y, wd , ht );}
    virtual void Set( const _Myt& _X, u32 _x, u32 _y ,const Rect& rc )
	{m_image.Set( ((_Myt&)_X).GetImage(), _x, _y, rc );}
    virtual void Set( const _Myt& _X );
    virtual _Myt& operator=(const _Myt& _X)
	{
	    m_image.Set( ((_Myt&)_X).GetImage() );
	    return (*this);
	}

	//  Get elements

    virtual u8 Get( u32 _x , u32 _y )
	{
	    u8 ret_value = m_image.Get( _x, _y );
	    return ret_value;
	}

    virtual bool Resize(u32 _width,u32 _height)
	{return m_image.Resize(_width,_height);}
    virtual u8 operator()( u32 _x , u32 _y ){return Get( _x, _y );}

    virtual Character* CreateCharacter( u32 _x=0 , u32 _y=0 );
    virtual void DeleteCharacter( Character *ch_ptr ){delete ch_ptr;}

    virtual Palette& GetPalette(void){return m_palette;}
    virtual u8 BitCount(void){return m_bit_count;}
    virtual void SetPalette(const Palette& Pal );

    virtual _Im& GetImage( void ){return m_image;}

};

__MAGBX__END

#endif	//  _AGB_PICTURE_

//
//

