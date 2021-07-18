//======================================================
//    character.h                                           
//    Handles BG character class Character. 
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_CHARACTER_
#define	_AGB_CHARACTER_

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <image.h>

__MAGBX__START

class Character : public AGBObject
{
public :

    typedef Character	_Myt;
    typedef Image<u8>	_Im;

protected :

    _Im m_image;

    virtual u8* create_out_buffer( void );
    virtual void delete_out_buffer( u8* out_buffer );

public :

    typedef Character _Myt;

    Character() : m_image( 8 , 8 ) {}
    Character( const _Myt& _X ) : m_image( ((_Myt&)_X).GetImage() ) {}

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );

    virtual u32 Width(){return m_image.Width();}
    virtual u32 Height(){return m_image.Height();}
    virtual u32 Size(){return 64;}


//
//
//	Launcher for the Image 
//

    virtual void Set( u8 _P , u32 _x , u32 _y  )
	{
	    m_image.Set( _P, _x, _y);
	}
    virtual void Set( const _Im& _X , u32 _x , u32 _y ,
			u32 wd = 0 ,u32 ht = 0 )
	{
	    m_image.Set( _X, _x, _y, wd , ht );
	}
    virtual void Set( const _Im& _X, u32 _x, u32 _y ,const Rect& rc )
	{
	    m_image.Set( _X, _x, _y, rc );
	}
    virtual void Set( const _Im& _X )
	{
	    m_image.Set( _X );
	}
    virtual _Myt& operator=(const _Im& _X)
	{
	    m_image.Set( _X );
	    return (*this);
	}
    virtual void Set( const _Myt& _X , u32 _x , u32 _y ,
			u32 wd = 0 ,u32 ht = 0 )
	{
	    m_image.Set( ((_Myt&)_X).GetImage(), _x, _y, wd , ht );
	}
    virtual void Set( const _Myt& _X, u32 _x, u32 _y ,const Rect& rc )
	{
	    m_image.Set( ((_Myt&)_X).GetImage(), _x, _y, rc );
	}
    virtual void Set( const _Myt& _X )
	{
	    m_image.Set( ((_Myt&)_X).GetImage() );
	}
    virtual _Myt& operator=(const _Myt& _X)
	{
	    m_image.Set( ((_Myt&)_X).GetImage() );
	    return (*this);
	}

	//  Get elements.

    virtual u8 Get( u32 _x , u32 _y )
	{
	    u8 ret_value = m_image.Get( _x, _y );
	    return ret_value;
		//  The following is an error. 
		//  Because the type of return value is different. 
	    //  return m_image.Get( _x , _y );
	}

    virtual u8 operator()( u32 _x , u32 _y )
	{
	    return Get( _x, _y );
	}

	//  Comparison function

    virtual bool Compare( const _Myt& _X )
	{
	    return m_image.Compare( ((_Myt&)_X).GetImage() );
	}

	//  Find flip status.  

    virtual int CompareFlip( const _Myt& _X )
	{
	    return m_image.CompareFlip( ((_Myt&)_X).GetImage() );
	}

    virtual bool operator==( const _Myt& _X )
	{
	    return Compare( _X );
	}

    _Im& GetImage( void ){return m_image;}
};

__MAGBX__END

#endif	//  _AGB_CHARACTER_

//
//
