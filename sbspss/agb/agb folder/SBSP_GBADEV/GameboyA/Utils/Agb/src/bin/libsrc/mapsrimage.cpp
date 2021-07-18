//======================================================
//    mapsrimage.cpp                                           
//    Class to use image of expansion/reduction BG.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <image.h>
#include <maptextunit.h>
#include <maptextimage.h>
#include <mapsrimage.h>

__MAGBX__START

//----------------------------------------------------------------------
u8* MapSRImage::create_out_buffer( void )
{
    u8* ret_buffer = new u8[m_image.Size()];
    if( NULL == ret_buffer ) return NULL;
    u8* tmp_ptr = ret_buffer;
    for( u32 h_loop = 0 ; h_loop < m_image.Height() ; ++h_loop )
    {
	for( u32 w_loop = 0 ; w_loop < m_image.Width() ; ++w_loop )
	{
	   *tmp_ptr++ = (u8)((MapTextUnit&)Get(w_loop,h_loop)).Get();
	}
    }
    return ret_buffer;
}
//----------------------------------------------------------------------
void MapSRImage::delete_out_buffer( u8* buffer_ptr )
{
    delete[] buffer_ptr;
}
//----------------------------------------------------------------------
bool MapSRImage::Output( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    bool ret_value = ::OutputArray( out , out_buffer , m_image.Size());
    delete_out_buffer( out_buffer );
    return ret_value;
}
//----------------------------------------------------------------------
bool MapSRImage::Outtxt( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    bool ret_value = ::OuttxtArray( out , out_buffer , m_image.Size());
    delete_out_buffer( out_buffer );
    return ret_value;
}
//----------------------------------------------------------------------
bool MapSRImage::OutCSource( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u8* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    out << "const u8 " << m_name.c_str() << "_Map[";
    out << m_image.Width() << "*" << m_image.Height() << "] = {" << std::endl;
    bool ret_value = ::OuttxtArray( out , out_buffer , m_image.Size());
    if( true == ret_value )
    {
	out << std::endl << "};" << std::endl;
    }
    delete_out_buffer( out_buffer );
    return ret_value;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
