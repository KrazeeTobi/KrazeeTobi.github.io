//======================================================
//    char256set.cpp                                           
//    BG Character set class Char256Set.
//    Set of characters used in 256 color text mode.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <fstream>
#include <iostream>
#include <agbtypes.h>
#include <character.h>
#include <charset.h>
#include <char16set.h>
#include <char256set.h>

__MAGBX__START

//----------------------------------------------------------------------
Character* Char256Set::CreateCharacter( void )
{
    return new Character;
}
//----------------------------------------------------------------------
bool Char256Set::OutCSource( std::ofstream& out )
{
    return CharSet::OutCSource( out );
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
