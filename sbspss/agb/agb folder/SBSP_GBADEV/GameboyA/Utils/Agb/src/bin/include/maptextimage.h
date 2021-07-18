//======================================================
//    maptextimage.h                                           
//    Class to handle images of AGB text BG.  
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_MAPTEXTIMAGE_
#define	_AGB_MAPTEXTIMAGE_

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <image.h>
#include <maptextunit.h>

__MAGBX__START

class MapTextImage : public AGBObject
{
public :
    typedef MapTextImage _Myt;
    typedef MapTextUnit	 _Ut;
    typedef Image<_Ut> _Im;

private :
    u16* create_out_buffer( void );
    void delete_out_buffer( u16* buffer_ptr );
protected :
    _Im	m_image;
public :
    typedef MapTextImage _Myt;

    MapTextImage( u32 width=0 , u32 height=0 ) :
       m_image(width , height){}
    MapTextImage( const _Myt& _X ) :
       m_image( ((_Myt&)_X).GetImage() ){}

    virtual bool Output( std::ofstream &out );
    virtual bool Outtxt( std::ofstream &out );
    virtual bool OutCSource( std::ofstream &out );

//
//
//	Launcher for Image 
//
//

    virtual u32 Width(){return m_image.Width();}
    virtual u32 Height(){return m_image.Height();}
    virtual void Set(const _Ut& _P,u32 _x,u32 _y)
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
	{m_image.Set( ((_Myt&)_X).GetImage() );}
    virtual _Myt& operator=(const _Myt& _X)
	{
	    m_image.Duplicate( ((_Myt&)_X).GetImage() );
	    return (*this);
	}

    virtual bool Resize( u32 _width, u32 _height )
	{return m_image.Resize( _width, _height );}

	//  Get elements

    virtual const _Ut& Get( u32 _x , u32 _y )
	{
	    return m_image.Get( _x, _y );
	}

    virtual _Im GetImage(){return m_image;}

};

__MAGBX__END

#endif	//  _AGB_MAPTEXTIMAGE_

//
//
