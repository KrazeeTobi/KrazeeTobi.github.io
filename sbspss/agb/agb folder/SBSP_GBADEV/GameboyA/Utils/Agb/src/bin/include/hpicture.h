//======================================================
//    hpicture.h                                           
//    Class for images which do not use a palette.   
//    Class for transactions between Windows Bitmap images
//    and AGB bitmap mode images.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_HPICTURE_
#define	_AGB_HPICTURE_

#include <CString>
#include <agbtypes.h>
#include <image.h>
#include <filename.h>
#include <bmpstruct.h>
#include <util.h>
#include <color.h>

__MAGBX__START

class HPicture : public AGBObject
{
public :
    typedef HPicture _Myt;
    typedef Image<Color> _Im;

protected :

    _Im	m_image;

    virtual bool load_bmp_file_header( std::ifstream &in );
    virtual u32 get_num_of_colors( bmp_info_header& bmih );

    virtual bool load_bmp( std::ifstream& in );
    virtual bool save_bmp( std::ofstream& out );
    virtual u16* create_out_buffer( void );
    virtual void delete_out_buffer( u16* buffer_ptr ){delete[] buffer_ptr;}

public :
    HPicture( u32 width=0 , u32 height=0 ) :
	m_image(width , height){}
    HPicture( const _Myt& _X ) :
	m_image( ((_Myt&)_X).GetImage() ){}
    HPicture( const FileName& fname ){LoadBmp( fname );}

    virtual ~HPicture(){}

    virtual bool LoadBmp( const FileName& fname );
    virtual bool SaveBmp( const FileName& fname );
    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );

//
//
//	Launcher for image
//
//

    virtual u32 Width(){return m_image.Width();}
    virtual u32 Height(){return m_image.Height();}
    virtual void Set(const Color& _P,u32 _x,u32 _y)
	{m_image.Set( _P, _x, _y);}
    virtual void Set(const _Im& _X,u32 _x,u32 _y,u32 wd=0,u32 ht=0)
	{ m_image.Set( _X, _x, _y, wd , ht );}
    virtual void Set( const _Im& _X, u32 _x, u32 _y ,const Rect& rc )
	{m_image.Set( _X, _x, _y, rc );}
    virtual void Set( const _Im& _X ){m_image.Set( _X );}
    virtual _Myt& operator=(const _Im& _X)
	{
	    m_image.Set( _X );
	    return (*this);
	}
    virtual void Set(const _Myt& _X,u32 _x,u32 _y,u32 wd=0,u32 ht=0)
	{m_image.Set( ((_Myt&)_X).GetImage(), _x, _y, wd , ht );}
    virtual void Set( const _Myt& _X, u32 _x, u32 _y ,const Rect& rc )
	{m_image.Set( ((_Myt&)_X).GetImage(), _x, _y, rc );}
    virtual void Set( const _Myt& _X )
	{m_image.Duplicate(((_Myt&)_X).GetImage());}
    virtual _Myt& operator=(const _Myt& _X)
	{
	    m_image.Duplicate( ((_Myt&)_X).GetImage() );
	    return (*this);
	}

    virtual bool Resize( u32 _width, u32 _height )
	{return m_image.Resize( _width, _height );}

	//  Get elements. 

    virtual Color Get( u32 _x , u32 _y )
	{
	    return m_image.Get( _x , _y );
	}

    virtual _Im GetImage(){return m_image;}

};

__MAGBX__END

#endif	//  _AGB_HPICTURE_

//
//

