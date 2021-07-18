//======================================================
//    color.cpp                                           
//    Class for using color in AGB.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agbtypes.h>
#include <color.h>

__MAGBX__START

//----------------------------------------------------------------------
u16 Color::Get( void )
{
    return ( ( ((u16)m_red) & 0x00f8 )>>3 )
	  |( ( ((u16)m_green) & 0x00f8 )<<2 )
	  |( ( ((u16)m_blue)  & 0x00f8 )<<7 )
	  |( ( ((u16)m_green) & 0x0004 )<<13 );
}
//----------------------------------------------------------------------
Color& Color::operator=(const Color& _Ty)
{
    Set( _Ty );
    return (*this);
}
//----------------------------------------------------------------------
void Color::Set( u8 _r , u8 _g , u8 _b )
{
    m_red = _r;
    m_green = _g;
    m_blue = _b;
}
//----------------------------------------------------------------------
void Color::Set( const Color& _X )
{
    if( this != &_X )
    {
	Set( ((Color&)_X).Red() , ((Color&)_X).Green() ,
	     ((Color&)_X).Blue() );
    }
}
//----------------------------------------------------------------------
u32 Color::SquareDistance( const Color& _X )
{
    if( this == &_X ) return 0;
    s32 red_distance = m_red - ((Color&)_X).Red();
    red_distance = red_distance * red_distance;
    s32 green_distance = m_green - ((Color&)_X).Green();
    green_distance = green_distance * green_distance;
    s32 blue_distance = m_blue - ((Color&)_X).Blue();
    blue_distance = blue_distance * blue_distance;
    return (u32)( red_distance + green_distance + blue_distance );
}
//----------------------------------------------------------------------
bool operator==(const Color& _L , const Color& _R )
{
    if( ((Color&)_L).Red() != ((Color&)_R).Red() ) return false;
    if( ((Color&)_L).Blue() != ((Color&)_R).Blue() ) return false;
    if( ((Color&)_L).Green() != ((Color&)_R).Green() ) return false;
    return true;
}
//----------------------------------------------------------------------
bool operator!=(const Color& _L , const Color& _R )
{
    return !(_L == _R);
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
