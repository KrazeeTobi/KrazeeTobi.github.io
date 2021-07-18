//======================================================
//    map256.h
//    Class to handle a map using AGB 256-color text BG.  
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_MAP256_
#define	_AGB_MAP256_

#include <agbtypes.h>
#include <character.h>
#include <character256.h>
#include <maptextunit.h>
#include <palette.h>
#include <charset.h>
#include <maptextunit.h>
#include <maptextimage.h>
#include <mapsrimage.h>
#include <map.h>

__MAGBX__START

class Map256 : public Map
{
public :
    typedef Character _Ch;
protected :

    virtual bool alloc(u32 width , u32 height);
    virtual bool is_character_over( void );
    virtual u32 get_bit_count(void){return 16;}

public :

    Map256(u32 width=0 , u32 height=0);

    virtual _Ch* CreateCharacter( void );
    virtual bool SetCharacter( u32 _x , u32 _y , const _Ch& _P );
    virtual bool SetCharacter( const _Ch& _P );
};

__MAGBX__END

#endif	//  _AGB_MAP256_

//
//
