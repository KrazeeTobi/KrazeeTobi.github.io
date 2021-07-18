//======================================================
//    map16.h
//    Class to handle a map using AGB 16-color text BG.  
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_MAP16_
#define	_AGB_MAP16_

#include <agbtypes.h>
#include <character.h>
#include <character16.h>
#include <charset.h>
#include <char16set.h>
#include <palette.h>
#include <maptextunit.h>
#include <maptextimage.h>
#include <mapsrimage.h>
#include <map.h>

__MAGBX__START

class Map16 : public Map
{
public :
    typedef Character _Ch;
protected :

    u8  m_palette_number;

    virtual bool alloc(u32 width , u32 height);
    virtual bool is_character_over( void );
    virtual u32 get_bit_count(void){return 16;}

public :

    Map16(u32 width=0 , u32 height=0);

    virtual _Ch* CreateCharacter( void );
    virtual void SetPaletteNumber( u8 palette_number );
    virtual bool SetCharacter( u32 _x , u32 _y , const _Ch& _P );
    virtual bool SetCharacter( const _Ch& _P );
};

__MAGBX__END

#endif	//  _AGB_MAP16_

//
//
