//======================================================
//    maptextimage.cpp                                           
//    Class to use image of AGB Text BG.
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

__MAGBX__START

//----------------------------------------------------------------------
u16* MapTextImage::create_out_buffer( void )
{
    u16* ret_buffer = new u16[m_image.Size()];
    if( NULL == ret_buffer ) return NULL;
    u16* tmp_ptr = ret_buffer;
    for( u32 h_loop = 0 ; h_loop < m_image.Height() ; ++h_loop )
    {
	for( u32 w_loop = 0 ; w_loop < m_image.Width() ; ++w_loop )
	{
	   *tmp_ptr++ = ((MapTextUnit&)Get(w_loop,h_loop)).Get();
	}
    }
    return ret_buffer;
}
//----------------------------------------------------------------------
void MapTextImage::delete_out_buffer( u16* buffer_ptr )
{
    delete[] buffer_ptr;
}
//----------------------------------------------------------------------
bool MapTextImage::Output( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u16* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    bool ret_value = ::OutputArray( out , out_buffer , m_image.Size());
    delete_out_buffer( out_buffer );
    return ret_value;
}
//----------------------------------------------------------------------
bool MapTextImage::Outtxt( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u16* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    bool ret_value = ::OuttxtArray( out , out_buffer , m_image.Size());
    delete_out_buffer( out_buffer );
    return ret_value;
}
//----------------------------------------------------------------------
bool MapTextImage::OutCSource( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u16* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    out << "const u16 " << m_name.c_str() << "_Map[";
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
