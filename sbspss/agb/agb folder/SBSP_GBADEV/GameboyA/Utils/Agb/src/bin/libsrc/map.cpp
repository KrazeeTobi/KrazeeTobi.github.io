//======================================================
//    map.cpp
//    Class to use map by using expansion/reduction BG 
//    of AGB.
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agbtypes.h>
#include <character.h>
#include <charset.h>
#include <palette.h>
#include <maptextunit.h>
#include <maptextimage.h>
#include <mapsrimage.h>
#include <map.h>

__MAGBX__START

const u32 Map::m_scb_magic = ('S' << 24) | ('c' << 16) | ('r' << 8) | 'B';

//----------------------------------------------------------------------
bool Map::is_alloc( void )
{
    if( NULL == m_chset_ptr ) return false;
    if( NULL == m_palette_ptr ) return false;
    if( NULL == m_mti_ptr ) return false;
    return true;
}
//----------------------------------------------------------------------
bool Map::alloc(u32 width , u32 height)
{
    if( NULL == m_chset_ptr )
	m_chset_ptr = new CharSet;
    if( NULL == m_palette_ptr )
	m_palette_ptr = new Palette;
    if( NULL == m_mti_ptr )
	m_mti_ptr = new MapSRImage(width , height);
    return is_alloc();
}
//----------------------------------------------------------------------
void Map::free(void)
{
    delete m_chset_ptr;
    delete m_palette_ptr;
    delete m_mti_ptr;
}
//----------------------------------------------------------------------
bool Map::is_character_over( void )
{
    if( m_chset_ptr == NULL ) return false;
    return ( m_chset_ptr->Size() <= 256 );
}
//----------------------------------------------------------------------
u32 Map::get_bit_count(void)
{
    return 8;
}
//----------------------------------------------------------------------
bool Map::SetSize( u32 width , u32 height )
{
    if( NULL == m_mti_ptr ) alloc(width , height);
    if( NULL == m_mti_ptr ) return false;
    u32 l_width , l_height;
    l_width = (width == 0) ? Width() : width;
    l_height= (height== 0) ? Height(): height;
    return m_mti_ptr->Resize(l_width , l_height);
}
//----------------------------------------------------------------------
Character* Map::CreateCharacter( void )
{
    return new Character;
}
//----------------------------------------------------------------------
void Map::DeleteCharacter( Character* char_ptr )
{
    delete char_ptr;
}
//----------------------------------------------------------------------
bool Map::SetCharacter( u32 _x , u32 _y , const Character& _P )
{
    if( false == is_alloc() ) return false;
    if( _x >= Width() || _y >= Height() ) return false;
    MapTextUnit unit;
    if( false == m_chset_ptr->Add( unit , _P ) ) return false;
    if( m_chset_ptr->Size() == 257 )
    {
	std::cerr << "Number Of Characters are over 256!!";
	std::cerr << std::endl;
    }
    SetUnit( _x , _y , unit );
    return true;
}
//----------------------------------------------------------------------
bool Map::SetCharacter( const Character& _P )
{
    if( false == is_alloc() ) return false;
    if( false == m_chset_ptr->Add( _P ) ) return false;
    if( m_chset_ptr->Size() == 257 )
    {
	std::cerr << "Number Of Characters are over 256!!";
	std::cerr << std::endl;
    }
    return true;
}
//----------------------------------------------------------------------
bool Map::SetCharSet( const CharSet& _P )
{
    if( false == is_alloc() ) return false;
    m_chset_ptr->Set( _P );
    return true;
}
//----------------------------------------------------------------------
bool Map::SetUnit( u32 _x , u32 _y , const MapTextUnit& _P )
{
    if( false == is_alloc() ) return false;
    if( _x >= Width() || _y >= Height() ) return false;
    m_mti_ptr->Set( _P , _x , _y );
    return true;
}
//----------------------------------------------------------------------
MapTextUnit Map::GetUnit( u32 _x , u32 _y )
{
    MapTextUnit unit;
    if( false == is_alloc() ) return unit;
    if( _x >= Width() || _y >= Height() ) return unit;
    unit = m_mti_ptr->Get( _x , _y );
    return unit;
}
//----------------------------------------------------------------------
bool Map::SetPalette( const Palette &_P )
{
    if( false == is_alloc() ) return false;
    *m_palette_ptr = _P;
    return true;
}
//----------------------------------------------------------------------
void Map::SetName( const char* name )
{
    std::string n_str( name );
    SetName( n_str );
}
//----------------------------------------------------------------------
void Map::SetName( const std::string& name )
{
    m_name = name;
    if( NULL != m_chset_ptr )
	m_chset_ptr->SetName( name );
    if( NULL != m_palette_ptr )
	m_palette_ptr->SetName( name );
    if( NULL != m_mti_ptr )
	m_mti_ptr->SetName( name );
}
//----------------------------------------------------------------------
u32  Map::GetNumOfCharacters(void)
{
    if( false == is_alloc() ) return false;
    return m_chset_ptr->GetNumOfCharacters();
}
//----------------------------------------------------------------------
bool Map::OutCSource( std::ofstream& out )
{
    if( !out ) return false;
    out << "#include <agbtypes.h>" << std::endl << std::endl;
    if( NULL != m_palette_ptr )
    {
	if( false == m_palette_ptr->OutCSource( out ) )
	    return false;
    }
    out << std::endl;
    if( NULL != m_chset_ptr )
    {
	if( false == is_character_over() )
	{
	    std::cerr << "There are too many characters" << std::endl;
	    return false;
	}
	if( false == m_chset_ptr->OutCSource( out ) )
	    return false;
    }
    out << std::endl;
    if( NULL != m_mti_ptr )
    {
	if( false == m_mti_ptr->OutCSource( out ) )
	    return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool Map::OutputScb(std::ofstream& out)
{
    if( false == is_alloc() ) return false;
    if( false == ::Output( out, m_scb_magic ) ) return false;
    if( false == ::Output( out, Width())) return false;
    if( false == ::Output( out, Height())) return false;
    if( false == ::Output( out, get_bit_count() ) ) return false;
    u32 line_byte = (Width() * get_bit_count())/8;
    if( false == ::Output( out, line_byte ) ) return false;
    return m_mti_ptr->Output(out);
}
//----------------------------------------------------------------------
u32 Map::NumOfCharacters( void )
{
    if( NULL == m_chset_ptr ) return 0;
    return m_chset_ptr->Size();
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
