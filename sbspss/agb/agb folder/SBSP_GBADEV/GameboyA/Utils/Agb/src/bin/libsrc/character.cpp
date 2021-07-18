//======================================================
//    character.cpp                                           
//    Character class for BG using Character.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <image.h>
#include <character.h>

__MAGBX__START

//----------------------------------------------------------------------
u8* Character::create_out_buffer( void )
{
    u8* ret_buffer = new u8[64];
    if( NULL == ret_buffer ) return NULL;
    for( int i=0 ; i<64 ; ++i )
    {
	ret_buffer[i] = m_image.Get( i%8,i/8 );
    }
    return ret_buffer;
}
//----------------------------------------------------------------------
void Character::delete_out_buffer( u8* out_buffer )
{
    delete[] out_buffer;
}
//----------------------------------------------------------------------
bool Character::Output( std::ofstream& out )
{
    bool fret = false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    fret = ::OutputArray( out , out_buffer , 64 );
    delete_out_buffer( out_buffer );
    return fret;
}
//----------------------------------------------------------------------
bool Character::Outtxt( std::ofstream& out )
{
    bool fret = false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    fret = ::OuttxtArray( out , out_buffer , 64 );
    delete_out_buffer( out_buffer );
    return fret;
}
//----------------------------------------------------------------------
bool Character::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    bool fret = false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    out << "{" << std::endl;
    fret = ::OuttxtArray( out , out_buffer , 64 );
    if( true == fret ) out << "}" << std::endl;
    delete_out_buffer( out_buffer );
    return fret;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
