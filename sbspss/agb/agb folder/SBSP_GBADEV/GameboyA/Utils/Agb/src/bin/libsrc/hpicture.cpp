//======================================================
//    hpicture.cpp                                           
//    Class to use an image without a palette.
//    Class to exchange images of Windows Bitmap and AGB 
//    bit map mode.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <CString>
#include <filename.h>
#include <agbtypes.h>
#include <hpicture.h>
#include <util.h>
#include <bmpstruct.h>

__MAGBX__START

//----------------------------------------------------------------------
bool HPicture::load_bmp_file_header( std::ifstream &in )
{
    if( !in.is_open() ) return false;
    bmp_file_header bmfh;
    memset( &bmfh , 0 , sizeof( bmp_file_header ) );
    if( !in.read( (char*)&bmfh , sizeof( bmp_file_header ) ) )
    {
	std::cerr << "Failed to Read" << std::endl;
	return false;
    }
    if( 0x4d42 != bmfh.bfType )
    {
	std::cerr << "This is not Windows Bitmap File" << std::endl;
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
u32 HPicture::get_num_of_colors( bmp_info_header& bmih )
{
    if( 0 != bmih.biClrImportant ) return (u32)bmih.biClrImportant;
    if( 0 != bmih.biClrUsed )
	return	(u32)(bmih.biClrUsed);
    else
	return	(u32)(1<<bmih.biBitCount);
}
//----------------------------------------------------------------------
bool HPicture::load_bmp( std::ifstream& in )
{
    if( !in.is_open() ) return false;
    if( false == load_bmp_file_header(in) ) return false;
    bmp_info_header bmih;
    memset( &bmih , 0 , sizeof( bmp_info_header ) );
    if( !in.read( (char*)&bmih , sizeof( bmp_info_header ) ) )
    {
	std::cerr << "Failed to Read" << std::endl;
	return false;
    }
    if( bmih.biBitCount != 24 )
    {
	std::cerr << "Error:Bitcount is " << bmih.biBitCount << "." << std::endl;
	return false;
    }
    if( bmih.biCompression != BMP_COMP_RGB )
    {
	std::cerr << "Cannot Read this Format" << std::endl;
	return false;
    }
    u32 width = bmih.biWidth;
    u32 height = bmih.biHeight;
    if(false == Resize( width , height ) )
    {
	std::cerr << "Cannnot Resize" << std::endl;
	return false;
    }
    u32 pitch = (u32)(((width*bmih.biBitCount+31)/8)&-4);
    u8* pixel_ptr = new u8[pitch*height];
    if( NULL == pixel_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	return false;
    }
    if( !in.read( (char*)pixel_ptr , pitch*height ) )
    {
	delete[] pixel_ptr;
	std::cerr << "Failed to Read Pixel Data" << std::endl;
	return false;
    }
    u32 w_loop , h_loop;
    u8 red , green , blue;
    u8* tmp_ptr=NULL;
    Color color;
    for( h_loop = 0 ; h_loop < height ; ++h_loop )
    {
	tmp_ptr = &pixel_ptr[(height-1-h_loop)*pitch];
	for( w_loop = 0 ; w_loop < width ; ++w_loop )
	{
	    blue = *tmp_ptr++;
	    green = *tmp_ptr++;
	    red = *tmp_ptr++;
	    color.Set( red , green , blue );
	    Set( color,w_loop,h_loop );
	}
    }
    delete[] pixel_ptr;
    return true;
}
//----------------------------------------------------------------------
bool HPicture::save_bmp( std::ofstream &out )
{
    u32 width = m_image.Width();
    u32 height = m_image.Height();
    if( (width==0)&&(height==0) )
    {
	std::cerr << "No Image Exists" << std::endl;
	return false;
    }
    u32 PixelSize = 0;
    u32 PaletteSize = 0;
    bmp_file_header bmfh;
    memset( &bmfh , 0 , sizeof( bmp_file_header ) );
    bmp_info_header bmih;
    memset( &bmih , 0 , sizeof( bmp_info_header ) );
    bmfh.bfType = 0x4d42;
    bmih.biWidth = width;
    bmih.biHeight = height;
    bmih.biBitCount = 24;
    bmih.biSize = 0x28;
    bmih.biPlanes = 1;
    u32 pitch = (u32)(((width*24+31)/8)&-4);
    PixelSize = pitch * height;
    bmfh.bfOffBits = sizeof(bmp_file_header)+ sizeof(bmp_info_header);
    bmfh.bfSize = bmfh.bfOffBits + PixelSize;
    bmih.biSizeImage = PixelSize;
    bmih.biCompression = BMP_COMP_RGB;
    if( !out.write( (char*)&bmfh , sizeof( bmp_file_header ) ) )
    {
	std::cerr << "Cannot Write FileHeader" << std::endl;
	return false;
    }
    if( !out.write( (char*)&bmih , sizeof( bmp_info_header ) ) )
    {
	std::cerr << "Cannot Write InfoHeader" << std::endl;
	return false;
    }
    u8* pixel_ptr = new u8[PixelSize];
    if( NULL == pixel_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	return false;
    }

    ::memset( pixel_ptr , 0 , PixelSize );
    u32 w_loop , h_loop;
    u8* tmp_ptr=NULL;
    for( h_loop = 0 ; h_loop < height ; ++h_loop )
    {
	tmp_ptr = &pixel_ptr[(height-h_loop-1)*pitch];
	for( w_loop = 0 ; w_loop < width ; ++w_loop )
	{
	    *tmp_ptr++ = ((Color&)Get(w_loop,h_loop)).Blue();
	    *tmp_ptr++ = ((Color&)Get(w_loop,h_loop)).Green();
	    *tmp_ptr++ = ((Color&)Get(w_loop,h_loop)).Red();
	}
    }
    if( !out.write( (char*)pixel_ptr , PixelSize ) )
    {
	delete[] pixel_ptr;
	std::cerr << "Cannot Write Pixel Data" << std::endl;
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
u16* HPicture::create_out_buffer( void )
{
    u16* ret_ptr = new u16[m_image.Size()];
    if( NULL == ret_ptr ) return NULL;
    u16* tmp_ptr = ret_ptr;
    for( u32 h_loop = 0 ; h_loop < m_image.Height() ; ++h_loop )
    {
	for( u32 w_loop = 0 ; w_loop < m_image.Width() ; ++w_loop )
	{
	    *tmp_ptr++ = ((Color&)Get(w_loop,h_loop)).Get();
	}
    }
    return ret_ptr;
}
//----------------------------------------------------------------------
bool HPicture::LoadBmp( const FileName& fname )
{
    std::ifstream in( fname.c_str() , std::ios::in | std::ios::binary );
    return load_bmp( in );
}
//----------------------------------------------------------------------
bool HPicture::SaveBmp( const FileName& fname )
{
    std::ofstream out( fname.c_str() , std::ios::out | std::ios::binary );
    return save_bmp( out );
}
//----------------------------------------------------------------------
bool HPicture::Output( std::ofstream& out )
{
    u16* tmp_ptr = create_out_buffer();
    if( NULL == tmp_ptr ) return false;
    bool ret_value = ::OutputArray( out , tmp_ptr , m_image.Size() );
    delete_out_buffer( tmp_ptr );
    return ret_value;
}
//----------------------------------------------------------------------
bool HPicture::Outtxt( std::ofstream& out )
{
    u16* tmp_ptr = create_out_buffer();
    if( NULL == tmp_ptr ) return false;
    bool ret_value = ::OuttxtArray( out , tmp_ptr , m_image.Size() );
    delete_out_buffer( tmp_ptr );
    return ret_value;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//

