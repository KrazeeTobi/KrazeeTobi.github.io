//======================================================
//    maptextunit.h                                           
//    Class to express the data of 1 unit when handling 
//    AGB text BG.  All the members are public and can be 
//    handled in the same manner as a structure.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_MAPTEXTUNIT_
#define	_MAPTEXTUNIT_

#include <agbtypes.h>

__MAGBX__START

#define	MT_NONE_FLIP	(0)
#define	MT_H_FLIP	(1)
#define	MT_V_FLIP	(2)
#define	MT_HV_FLIP	(3)

class MapTextUnit
{
protected :

public :

    typedef MapTextUnit _Myt;

    u16 Number;
    u8  Palette;
    u8  Flip;

    MapTextUnit( u16 number=0 , u8 flip=MT_NONE_FLIP , u8 palette=0 ) :
	Number( number ), Flip( flip ), Palette(palette) {}
    ~MapTextUnit(){}

    void Set( u16 number=0 , u8 flip=MT_NONE_FLIP , u8 palette=0 );
    void Set( const _Myt& _X );
    u16 Get( void );

};

bool operator==(const MapTextUnit &_L , const MapTextUnit &_R);
bool operator!=(const MapTextUnit &_L , const MapTextUnit &_R);
bool operator<(const MapTextUnit &_L , const MapTextUnit &_R);
bool operator>(const MapTextUnit &_L , const MapTextUnit &_R);
bool operator<=(const MapTextUnit &_L , const MapTextUnit &_R);
bool operator>=(const MapTextUnit &_L , const MapTextUnit &_R);

__MAGBX__END

#endif	//  _MAPTEXTUNIT_

//
//
