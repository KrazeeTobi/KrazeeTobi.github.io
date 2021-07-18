//======================================================
//    character16.cpp                                           
//    16 color character class for BG Using Character16.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <character.h>
#include <character16.h>

__MAGBX__START

//----------------------------------------------------------------------
u8* Character16::create_out_buffer( void )
{
    u8* ret_buffer = new u8[32];
    if( NULL == ret_buffer ) return NULL;
    for( int i=0 ; i<32 ; ++i )
    {
	ret_buffer[i] = ((u8)(m_image.Get( (i%4)*2,i/4 ) & 0x0f)
		   | (u8)( (m_image.Get( (i%4)*2+1,i/4 ) & 0x0f) << 4 ) );
    }
    return ret_buffer;
}
//----------------------------------------------------------------------
bool Character16::Output( std::ofstream &out )
{
    bool fret = false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    fret = ::OutputArray( out , out_buffer , 32 );
    delete_out_buffer( out_buffer );
    return fret;
}
//----------------------------------------------------------------------
bool Character16::Outtxt( std::ofstream &out )
{
    bool fret = false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    fret = ::OuttxtArray( out , out_buffer , 32 );
    delete_out_buffer( out_buffer );
    return fret;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
