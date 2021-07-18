//======================================================
//    map256.cpp                                           
//    Class to use map by using 256 color text BG of AGB
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agbtypes.h>
#include <character.h>
#include <character256.h>
#include <charset.h>
#include <char256set.h>
#include <palette.h>
#include <maptextunit.h>
#include <maptextimage.h>
#include <mapsrimage.h>
#include <map.h>
#include <map256.h>

__MAGBX__START

//----------------------------------------------------------------------
bool Map256::alloc(u32 width , u32 height)
{
    if( NULL == m_chset_ptr )
	m_chset_ptr = new Char256Set;
    if( NULL == m_palette_ptr )
	m_palette_ptr = new Palette;
    if( NULL == m_mti_ptr )
	m_mti_ptr = new MapTextImage(width , height);
    return is_alloc();
}
//----------------------------------------------------------------------
bool Map256::is_character_over( void )
{
    if( m_chset_ptr == NULL ) return false;
    return ( m_chset_ptr->Size() <= 1024 );
}
//----------------------------------------------------------------------
Map256::Map256(u32 width /* =0 */ , u32 height /* =0 */ )
{
    m_chset_ptr=NULL;
    m_palette_ptr=NULL;
    m_mti_ptr = NULL;
    alloc(width , height);
}
//----------------------------------------------------------------------
Character* Map256::CreateCharacter( void )
{
    return new Character256;
}
//----------------------------------------------------------------------
bool Map256::SetCharacter( u32 _x , u32 _y , const Character& _P )
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
    unit.Palette = 0;
    m_mti_ptr->Set( unit , _x , _y );
    return true;
}
//----------------------------------------------------------------------
bool Map256::SetCharacter( const Character& _P )
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
