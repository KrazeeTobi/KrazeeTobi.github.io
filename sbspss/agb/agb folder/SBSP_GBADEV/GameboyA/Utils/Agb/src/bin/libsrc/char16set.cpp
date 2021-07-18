//======================================================
//    char16set.cpp                                           
//    BG character set class Char16Set.
//    Set of characters used in 16 color text mode.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <list>
#include <fstream>
#include <iostream>
#include <agbtypes.h>
#include <character16.h>
#include <maptextunit.h>
#include <charset.h>
#include <char16set.h>

__MAGBX__START

//----------------------------------------------------------------------
Character* Char16Set::CreateCharacter( void )
{
    return new Character16;
}
//----------------------------------------------------------------------
bool Char16Set::Unit( _Ut& _ut , const _Ty& _P )
{
    int number = 0;
    int flip;
    std::list<Character*>::iterator ch_it;
    for(ch_it = m_char_list.begin() ;
	ch_it != m_char_list.end() ;
	++ch_it )
    {
	flip = (*ch_it)->CompareFlip( (_Ty&)_P );
	if( flip >= 0 )
	{
	    _ut.Number = number;
	    _ut.Flip = flip;
	    return true;
	}
	++number;
    }
    return false;
}
//----------------------------------------------------------------------
bool Char16Set::OutCSource( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    out << "const u8 " << m_name.c_str() << "_Character[";
    out << "8*8/2*" << (u32)m_char_list.size() << "] = {" << std::endl;
    std::list<Character*>::iterator ch_it;
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

__MAGBX__END

//
//
//
