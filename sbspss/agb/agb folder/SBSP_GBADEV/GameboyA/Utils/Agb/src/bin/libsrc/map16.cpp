//======================================================
//    map16.cpp                                           
//    Class to use map by using 16 color text BG of AGB.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

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
#include <map16.h>

__MAGBX__START

//----------------------------------------------------------------------
bool Map16::alloc(u32 width , u32 height)
{
    if( NULL == m_chset_ptr )
	m_chset_ptr = new Char16Set;
    if( NULL == m_palette_ptr )
	m_palette_ptr = new Palette;
    if( NULL == m_mti_ptr )
	m_mti_ptr = new MapTextImage(width , height);
    return is_alloc();
}
//----------------------------------------------------------------------
bool Map16::is_character_over( void )
{
    if( m_chset_ptr == NULL ) return false;
    return ( m_chset_ptr->Size() <= 1024 );
}
//----------------------------------------------------------------------
Map16::Map16(u32 width /* =0 */ , u32 height /* =0 */ )
{
    m_chset_ptr=NULL;
    m_palette_ptr=NULL;
    m_mti_ptr = NULL;
    alloc(width , height);
}
//----------------------------------------------------------------------
Character* Map16::CreateCharacter( void )
{
    return new Character16;
}
//----------------------------------------------------------------------
void Map16::SetPaletteNumber( u8 palette_number )
{
    if( palette_number < 16 ) m_palette_number = palette_number;
}
//----------------------------------------------------------------------
bool Map16::SetCharacter( u32 _x , u32 _y , const Character& _P )
{
    if( false == is_alloc() ) return false;
    if( _x >= Width() || _y >= Height() ) return false;
    MapTextUnit unit;
    if( false == m_chset_ptr->Add( unit , _P ) ) return false;
    if( m_chset_ptr->Size() == 1025 )
    {
	std::cerr << "Number Of Characters are over 1024!!";
	std::cerr << std::endl;
    }
    unit.Palette = m_palette_number;
    m_mti_ptr->Set( unit , _x , _y );
    return true;
}
//----------------------------------------------------------------------
bool Map16::SetCharacter( const Character& _P )
{
    if( false == is_alloc() ) return false;
    if( false == m_chset_ptr->Add( _P ) ) return false;
    if( m_chset_ptr->Size() == 1025 )
    {
	std::cerr << "Number Of Characters are over 1024!!";
	std::cerr << std::endl;
    }
    return true;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
