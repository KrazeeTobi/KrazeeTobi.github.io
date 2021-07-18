//======================================================
//    charset.cpp                                           
//    BG Character Set Class CharSet.
//    Set of characters used in BG 256 color 
//    expansion/reduction screen mode.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <list>
#include <fstream>
#include <iostream>
#include <agbtypes.h>
#include <character.h>
#include <maptextunit.h>
#include <filename.h>
#include <picture.h>
#include <palette.h>
#include <charset.h>

__MAGBX__START

//----------------------------------------------------------------------
bool CharSet::true_add( MapTextUnit &_ut , const Character& _P )
{
    if( false == true_add( _P ) ) return false;
    _ut.Number = m_char_list.size()-1;
    _ut.Flip = 0;
    return true;
}
//----------------------------------------------------------------------
bool CharSet::true_add( const Character& _P )
{
    Character* tmp_ptr = CreateCharacter();
    if( NULL == tmp_ptr ) return false;
    tmp_ptr->Set( _P );
    m_char_list.push_back( tmp_ptr );
    return true;
}
//----------------------------------------------------------------------
void CharSet::Set( const CharSet& _X )
{
    if( this == &_X ) return;
    Clear();
    Add( _X );
}
//----------------------------------------------------------------------
bool CharSet::Unit( MapTextUnit& _ut , const Character& _P )
{
    int ret_value = 0;
    ch_list::iterator ch_it;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	if( *(*ch_it) == _P )
	{
	    _ut.Number = ret_value;
	    return true;
	}
	++ret_value;
    }
    return false;
}
//----------------------------------------------------------------------
bool CharSet::Add( MapTextUnit& _ut , const Character& _P )
{
    if( true == Unit( _ut , _P ) ) return true;
    return true_add( _ut , _P );
}
//----------------------------------------------------------------------
bool CharSet::Add( const Character& _P )
{
    MapTextUnit ut;
    if( true == Unit( ut , _P ) ) return true;
    return true_add( _P );
}
//----------------------------------------------------------------------
bool CharSet::Add( const CharSet& _X )
{
    ch_list::const_iterator ch_it;
    for( ch_it = ((CharSet&)_X).c_list().begin() ;
	ch_it != ((CharSet&)_X).c_list().end() ;
	++ch_it )
    {
	if( false == true_add( *(*ch_it) ) ) return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool CharSet::AddNoCheck( const Character& _P )
{
    return true_add( _P );
}
//----------------------------------------------------------------------
void CharSet::Clear( void )
{
    ch_list::iterator ch_it;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	delete (*ch_it);
    }
    m_char_list.resize(0);
}
//----------------------------------------------------------------------
bool CharSet::Output( std::ofstream &out )
{
    ch_list::iterator ch_it;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	if( false == (*ch_it)->Output(out) ) return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool CharSet::Outtxt( std::ofstream &out )
{
    ch_list::iterator ch_it;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	if( false == (*ch_it)->Outtxt(out) ) return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool CharSet::OutCSource( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    out << "const u8 " << m_name.c_str() << "_Character[";
    out << "8*8*" << (u32)m_char_list.size() << "] = {" << std::endl;
    ch_list::iterator ch_it;
    u32 count=0;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	out << "/*  " << count++ << "  */" << std::endl;
	if( false == (*ch_it)->Outtxt(out) ) return false;
	out << std::endl;
    }
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool CharSet::SaveBmp( const FileName& fname )
{
    Picture* pic_ptr = new Picture(128, ((m_char_list.size()+15)/16)*8);
    if( NULL == pic_ptr ) return false;
    u32 loop=0;
    ch_list::iterator ch_it;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	pic_ptr->Set( (*ch_it)->GetImage() ,
		(loop & 0xf)*8 , (loop >>4)*8 ,8 , 8);
	++loop;
    }
    pic_ptr->SetPalette( m_palette );
    bool ret_value = pic_ptr->SaveBmp( fname );

    delete pic_ptr;
    return ret_value;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
