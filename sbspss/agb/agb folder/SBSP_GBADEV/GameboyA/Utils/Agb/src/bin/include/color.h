//======================================================
//    color.h                                           
//    Class for AGB colors.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_COLOR_
#define	_AGB_COLOR_

#include <agbtypes.h>

__MAGBX__START

class Color
{
protected :
    u8 m_red;
    u8 m_green;
    u8 m_blue;
public :
    typedef Color _Myt;

    Color( u8 red=0 , u8 green=0 , u8 blue=0 ) :
	m_red(red) , m_green(green) , m_blue( blue ){}
    Color( const _Myt& _X ) :
	m_red( ((_Myt&)_X).Red() ) ,
	m_green( ((_Myt&)_X).Green() ) ,
	m_blue( ((_Myt&)_X).Blue() ) {}
    ~Color(){}

	//  Functions to get colors  

    u16 Get( void );
    u8  Red( void ){return m_red;}
    u8  Green( void ){return m_green;}
    u8  Blue( void ){return m_blue;}

	//  Functions to set colors

    _Myt& operator=(const _Myt& _Ty);
    void Set( u8 _r , u8 _g , u8 _b );
    void Set( const _Myt& _X );
    void SetRed( u8 _r ){m_red = _r;}
    void SetGreen( u8 _g ){m_green = _g;}
    void SetBlue( u8 _b ){m_blue = _b;}

    u32 SquareDistance( const _Myt& _X );
};

bool operator==(const Color& _L , const Color& _R );
bool operator!=(const Color& _L , const Color& _R );

__MAGBX__END

#endif	//  _AGB_COLOR_

//
//
