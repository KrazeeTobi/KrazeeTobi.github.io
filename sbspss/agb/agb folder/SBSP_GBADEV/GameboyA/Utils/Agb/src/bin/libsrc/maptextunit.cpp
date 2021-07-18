//======================================================
//    maptextunit.cpp                                           
//    All the class members that display 1 square of data 
//    for using Text BG of AGB are defined as public and 
//    can be treated the same as a structure.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agbtypes.h>
#include <maptextunit.h>

__MAGBX__START

//----------------------------------------------------------------------
void MapTextUnit::Set( u16 number /* =0 */ ,
		       u8 flip /* =MT_NONE_FLIP */ ,
		       u8 palette /* =0 */ )
{
    Number = number;
    Flip = flip;
    Palette = palette;
}
//----------------------------------------------------------------------
void MapTextUnit::Set( const MapTextUnit& _X )
{
    if( this == &_X ) return;
    Set( ((MapTextUnit&)_X).Number ,
	 ((MapTextUnit&)_X).Flip ,
	 ((MapTextUnit&)_X).Palette );
}
//----------------------------------------------------------------------
u16 MapTextUnit::Get( void )
{
    return (u16)((u16)(Number & 0x03ff)
	  |(u16)(((u16)Palette & 0xf) << 12 )
	  |(u16)(((u16)Flip & 0x3) << 10 ) );
}
//----------------------------------------------------------------------
bool operator==(const MapTextUnit &_L , const MapTextUnit &_R)
{
    return ( ((MapTextUnit&)_L).Get() ==((MapTextUnit&)_R).Get() );
}
//----------------------------------------------------------------------
bool operator!=(const MapTextUnit &_L , const MapTextUnit &_R)
{
    return !(_L==_R);
}
//----------------------------------------------------------------------
bool operator<(const MapTextUnit &_L , const MapTextUnit &_R)
{
    if( ((MapTextUnit)_L).Number < ((MapTextUnit)_R).Number ) return true;
    if( ((MapTextUnit)_L).Number == ((MapTextUnit)_R).Number )
    {
	if(((MapTextUnit)_L).Palette < ((MapTextUnit)_R).Palette) return true;
	if(((MapTextUnit)_L).Palette == ((MapTextUnit)_R).Palette)
	{
	    return ( ((MapTextUnit)_L).Flip < ((MapTextUnit)_R).Flip );
	}
    }
    return false;
}
//----------------------------------------------------------------------
bool operator>(const MapTextUnit &_L , const MapTextUnit &_R)
{
    if( ((MapTextUnit)_L).Number > ((MapTextUnit)_R).Number ) return true;
    if( ((MapTextUnit)_L).Number == ((MapTextUnit)_R).Number )
    {
	if(((MapTextUnit)_L).Palette > ((MapTextUnit)_R).Palette) return true;
	if(((MapTextUnit)_L).Palette == ((MapTextUnit)_R).Palette)
	{
	    return ( ((MapTextUnit)_L).Flip > ((MapTextUnit)_R).Flip );
	}
    }
    return false;
}
//----------------------------------------------------------------------
bool operator<=(const MapTextUnit &_L , const MapTextUnit &_R)
{
    return !(_L>_R);
}
//----------------------------------------------------------------------
bool operator>=(const MapTextUnit &_L , const MapTextUnit &_R)
{
    return !(_L<_R);
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
