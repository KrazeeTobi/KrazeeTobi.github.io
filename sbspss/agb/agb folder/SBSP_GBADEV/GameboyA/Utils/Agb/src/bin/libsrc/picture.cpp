//======================================================
//    picture.cpp
//    picture.cpp                                           
//    Class to handle an image with a palette.
//    Class to exchange the images of Windows Bitmap and AGB.
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <CString>
#include <filename.h>
#include <agbtypes.h>
#include <picture.h>
#include <palette.h>
#include <character.h>
#include <character16.h>
#include <bmpstruct.h>

__MAGBX__START

//--------------------------------------------------------------
u32 Picture::get_num_of_colors( bmp_info_header& bmih )
{
    if( 0 != bmih.biClrImportant ) return (u32)bmih.biClrImportant;
    if( 0 != bmih.biClrUsed )
	return	(u32)(bmih.biClrUsed);
    else
	return	(u32)(1<<bmih.biBitCount);
}
//--------------------------------------------------------------
bool Picture::load_palette( std::ifstream& in , u32 num_of_colors )
{
    if( false == m_palette.Resize( (int)num_of_colors ) )
    {
	return false;
    }
    rgb_quad rgb;
    memset( &rgb , 0 , sizeof( rgb_quad ) );
    Color cl;
    for( u32 c_loop = 0 ; c_loop < num_of_colors ; ++c_loop )
    {
	if( !in.read( (char*)&rgb , sizeof( rgb_quad ) ) )
	{
	    std::cerr << c_loop << std::endl;
	    return false;
	}
	cl.Set( rgb.rgbRed , rgb.rgbGreen , rgb.rgbBlue );
	m_palette.Set( cl , c_loop );
    }
    return true;
}
//--------------------------------------------------------------
bool Picture::load_bmp( std::ifstream& in )
{
	//Read file header

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

    bmp_info_header bmih;
    memset( &bmih , 0 , sizeof( bmp_info_header ) );
    if( !in.read( (char*)&bmih , sizeof( bmp_info_header ) ) )
    {
	std::cerr << "Failed to Read" << std::endl;
	return false;
    }
    if( bmih.biBitCount > 8 )
    {
	return false;
    }
    if( false == load_palette( in , get_num_of_colors( bmih ) ) )
    {
	std::cerr << "Failed to Read Palette" << std::endl;
	return false;
    }
    u32 width,height;
    width = bmih.biWidth;
    height = bmih.biHeight;
    if(false == Resize( width , height ) )
    {
	std::cerr << "Cannnot Resize" << std::endl;
	return false;
    }
    m_bit_count = (u8)bmih.biBitCount;
    u32 pitch = (u32)(((width*m_bit_count+31)/8)&-4);
    u8* pixel_ptr = new u8[pitch*height];
    if( NULL == pixel_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	return false;
    }

	//  Read offset value from File Header to Pixel

    in.seekg( bmfh.bfOffBits , std::ios::beg );

    switch( bmih.biCompression )
    {
	case BMP_COMP_RGB :
	    if( !in.read( (char*)pixel_ptr , pitch*height ) )
	    {
		delete[] pixel_ptr;
		std::cerr << "Failed to Read Pixel Data" << std::endl;
		return false;
	    }
	    break;
	case BMP_COMP_RLE8 :
	    if( false == load_bmp_rle8b( in, pixel_ptr, width, height ) )
	    {
		delete[] pixel_ptr;
		std::cerr << "Failed to Read Pixel Data" << std::endl;
		return false;
	    }
	    break;
	case BMP_COMP_RLE4 :
	    if( false == load_bmp_rle4b( in, pixel_ptr, width, height ) )
	    {
		delete[] pixel_ptr;
		std::cerr << "Failed to Read Pixel Data" << std::endl;
		return false;
	    }
	    break;
	default :
	    std::cerr << "Cannot Read this Format" << std::endl;
	    return false;
    }
    m_bit_count = (u8)bmih.biBitCount;
    u32 w_loop , h_loop;
    switch( m_bit_count )
    {
	case 4 :
	    for( h_loop = 0 ; h_loop < height ; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width/2 ; ++w_loop )
		{
		    Set( (u8)((pixel_ptr[h_loop*pitch+w_loop] & 0xf0)>>4),
			 w_loop*2, height-1-h_loop );
		    Set( (u8)(pixel_ptr[h_loop*pitch+w_loop] & 0xf),
			 w_loop*2+1, height-1-h_loop );
		}
		if( width & 1 )
		    Set( (u8)((pixel_ptr[h_loop*pitch+w_loop] & 0xf0)>>4),
			 w_loop*2, height-1-h_loop );
	    }
	    break;
	case 8 :
	    for( h_loop = 0 ; h_loop < height ; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width ; ++w_loop )
		{
		    Set( (u8)(pixel_ptr[h_loop*pitch+w_loop] ),
			 w_loop, height-1-h_loop );
		}
	    }
	    break;
	default :
	    std::cerr << "Bitcount is too large" << std::endl;
	    delete[] pixel_ptr;
	    return false;
    }
    delete[] pixel_ptr;
    return true;
}
//--------------------------------------------------------------
bool Picture::load_bmp_rle8b( std::ifstream& in, u8* pixel_ptr,
			      u32 width, u32 height)
{
    u32 pitch = (u32)(((m_image.Width()*8+31)/8)&-4);
    u8* pixel_origin = pixel_ptr;
    u8* pixel_tmp = pixel_ptr;
    s16 tmp;
    u8  count;
    u8  loop_num;
    u32 x,y;

    s8  read0;
    s8  read1;

    x = 0;
    y = height-1;
    while(1)
    {
	if( !in.read( &read0,1 ) ) return false;
	if( !in.read( &read1,1 ) ) return false;
	switch( read0 )
	{
	case 0 :
	    switch( read1 )
	    {
	    case 0 :
		--y;
		x = 0;
		pixel_tmp = pixel_origin + (height-y-1)*pitch + x;
		continue;
	    case 1 :
		return true;
	    case 2 :
		if( !in.read( &read0,1 ) ) return false;
		if( !in.read( &read1,1 ) ) return false;
		tmp = (s16)read0;
		if( tmp < 0 ) tmp += 256;
		x = (u32)(x +(s32)tmp);
		tmp = (s16)read1;
		if( tmp < 0 ) tmp += 256;
		y = (u32)(y +(s32)tmp);
		pixel_tmp = pixel_origin + (height-y-1)*pitch + x;
		continue;
	    default :
		tmp = (s16)read1;
		if( tmp < 0 ) tmp += 256;
		loop_num = (u8)tmp;
		for( count=0 ; count<loop_num ; ++count )
		{
		    if( !in.read( &read0,1 ) ) return false;
		    tmp = (s16)read0;
		    if( tmp < 0 ) tmp += 256;
		    *pixel_tmp++ = (u8)tmp;
		    ++x;
		}
		if( loop_num & 1 )
		{
		    if( !in.read( &read0,1 ) ) return false;
		}
		continue;
	    }
	default :
	    tmp = (s16)read0;
	    if( tmp < 0 ) tmp += 256;
	    loop_num = (u8)tmp;
	    tmp = (s16)read1;
	    if( tmp < 0 ) tmp += 256;
	    for( count=0 ; count<loop_num ; ++count )
	    {
		*pixel_tmp++ = (u8)tmp;
		++x;
	    }
	    continue;
	}
    }
    return false;
}
//--------------------------------------------------------------
bool Picture::load_bmp_rle4b( std::ifstream& in, u8* pixel_ptr,
			      u32 width, u32 height)
{
    u32 pitch = (u32)(((m_image.Width()*4+31)/8)&-4);
    u8* pixel_origin = pixel_ptr;
    u8* pixel_tmp = pixel_ptr;
    u8  count;
    u8  loop_num;
    u8  pixel_data;
    s16 tmp;
    u32 x,y;

    s8  read0;
    s8  read1;

    x = 0;
    y = height-1;
    while(1)
    {
	if( !in.read( &read0,1 ) ) return false;
	if( !in.read( &read1,1 ) ) return false;
	switch( read0 )
	{
	case 0 :
	    switch( read1 )
	    {
	    case 0 :
		//  The Line Ends
		--y;
		x = 0;
		pixel_tmp = pixel_origin + (height-y-1)*pitch + x/2;
		continue;
	    case 1 :
		//  RLE File End Code
		return true;
	    case 2 :
		//  Position Change by Offset
		if( !in.read( &read0,1 ) ) return false;
		if( !in.read( &read1,1 ) ) return false;
		tmp = (s16)read0;
		if( tmp < 0 ) tmp += 256;
		x = (u32)(x +(s32)tmp);
		tmp = (s16)read1;
		if( tmp < 0 ) tmp += 256;
		y = (u32)(y +(s32)tmp);
		pixel_tmp = pixel_origin + (height-y-1)*pitch + x/2;
		continue;
	    default :	//  More than 3
		//  read as many there are of read1
		loop_num = *((u8*)(&read1));
		for( count=0 ; count<loop_num/2 ; ++count )
		{
		    if( !in.read( &read0,1 ) ) return false;
		    tmp = (s16)read0;
		    if( tmp < 0 ) tmp += 256;
		    pixel_data = (u8)tmp;
		    rle4b_set_pixel_2dot( &pixel_tmp, &x, pixel_data );
		}
		if( loop_num & 1 )
		{
		    if( !in.read( &read0,1 ) ) return false;
			//  When number of dot to write is odd:
		    tmp = (s16)read0;
		    if( tmp < 0 ) tmp += 256;
		    pixel_data = (u8)tmp;
		    pixel_data &= 0xf0;
		    pixel_data >>= 4;
			//  Branch depend on the upper bits or lower bits
		    rle4b_set_pixel( &pixel_tmp, &x, pixel_data );
		}
		    //  Fix so that the address to be read will not be odd number.
		if( ((loop_num+1)/2) & 1 )
		{
		    if( !in.read( &read0,1 ) ) return false;
		}
		continue;
	    }
	default :   //  Other than 00
	    tmp = (s16)read0;
	    if( tmp < 0 ) tmp += 256;
	    loop_num = (u8)tmp;
	    tmp = (s16)read1;
	    if( tmp < 0 ) tmp += 256;
	    pixel_data = (u8)tmp;
	    for( count=0 ; count<loop_num/2 ; ++count )
	    {
		rle4b_set_pixel_2dot( &pixel_tmp, &x, pixel_data );
	    }
	    if( loop_num & 1 )
	    {
		pixel_data &= 0xf0;
		pixel_data >>= 4;
		rle4b_set_pixel( &pixel_tmp, &x, pixel_data );
	    }
	    continue;
	}
    }
    return false;
}
//--------------------------------------------------------------
void Picture::rle4b_set_pixel( u8** pixel_pptr, u32* x_ptr, u8 pixel_data )
{
	//  Branch depend on the upper bits or lower bits
    if( (*x_ptr) & 1 )
    {
	**pixel_pptr &= 0xf0;
	**pixel_pptr |= (pixel_data & 0x0f);
	*pixel_pptr += 1;
    }
    else
    {
	**pixel_pptr &= 0x0f;
	**pixel_pptr |= ((pixel_data&0x0f)<<4);
    }
    *x_ptr += 1;
}
//--------------------------------------------------------------
void Picture::rle4b_set_pixel_2dot( u8** pixel_pptr, u32* x_ptr, u8 pixel_data )
{
	//  Write upper 4bit
    rle4b_set_pixel( pixel_pptr, x_ptr, (pixel_data & 0xf0)>>4 );
	//  Write lower 4bit
    rle4b_set_pixel( pixel_pptr, x_ptr, pixel_data & 0x0f );
}
//--------------------------------------------------------------
bool Picture::save_bmp( std::ofstream& out )
{
    if( ((m_image.Width()==0)&&(m_image.Height()==0)) )
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
    bmih.biWidth = m_image.Width();
    bmih.biHeight = m_image.Height();
    bmih.biBitCount = m_bit_count;
    bmih.biSize = 0x28;
    bmih.biPlanes = 1;
    u32 width = m_image.Width();
    u32 height = m_image.Height();
    PaletteSize = m_palette.Size() * sizeof( rgb_quad );
    u32 pitch = (u32)(((width*m_bit_count+31)/8)&-4);
    PixelSize = pitch * height;
    bmfh.bfOffBits = sizeof(bmp_file_header)+ sizeof(bmp_info_header)+
		  PaletteSize;
    bmfh.bfSize = bmfh.bfOffBits + PixelSize;
    bmih.biSizeImage = PixelSize;
    bmih.biCompression = BMP_COMP_RGB;
    bmih.biClrUsed = bmih.biClrImportant = m_palette.Size();
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
    rgb_quad *rgb_ptr = new rgb_quad[ m_palette.Size() ];
    if( NULL == rgb_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	return false;
    }
    ::memset( rgb_ptr , 0 , PaletteSize );
    u32 loop;
    for( loop = 0 ; loop < m_palette.Size() ; ++loop )
    {
	rgb_ptr[loop].rgbRed = ((Color&)m_palette[loop]).Red();
	rgb_ptr[loop].rgbGreen = ((Color&)m_palette[loop]).Green();
	rgb_ptr[loop].rgbBlue = ((Color&)m_palette[loop]).Blue();
    }
    if( !out.write( (char*)rgb_ptr , PaletteSize ) )
    {
	std::cerr << "Cannnot Write Palette Data" << std::endl;
	delete[] rgb_ptr;
	return false;
    }
    delete[] rgb_ptr;
    u8* pixel_buffer = new u8[PixelSize];
    if( NULL == pixel_buffer )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	return false;
    }
    ::memset( pixel_buffer , 0 , PixelSize );
    u32 w_loop,h_loop;
    switch( m_bit_count )
    {
	case 4 :
	    for( h_loop = 0 ; h_loop < height ; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width/2 ; ++w_loop )
		{
		    pixel_buffer[pitch*(height-1-h_loop) + w_loop] =
		    ((Get( w_loop*2, h_loop )&0xf) << 4) +
		    (Get( w_loop*2+1, h_loop )&0xf);
		}
		if( width & 1 )
		    pixel_buffer[pitch*(height-1-h_loop) + w_loop] =
		    (Get( w_loop*2, h_loop )&0xf) << 4;
	    }
	    break;
	case 8 :
	    for( h_loop = 0 ; h_loop < height ; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width ; ++w_loop )
		{
		    pixel_buffer[pitch*(height-1-h_loop) + w_loop] =
		    Get( w_loop, h_loop );
		}
	    }
	    break;
	default :
	    delete[] pixel_buffer;
	    std::cerr << "BitCount is Strange" << std::endl;
	    return false;
    }
    if( !out.write( (char*)pixel_buffer , PixelSize ) )
    {
	delete[] pixel_buffer;
	std::cerr << "Cannot Write Pixel Data" << std::endl;
	return false;
    }
    return true;
}
//--------------------------------------------------------------
bool Picture::LoadBmp( const FileName& fname )
{
    std::ifstream in( fname.c_str() , std::ios::in | std::ios::binary );
    return load_bmp( in );
}
//--------------------------------------------------------------
bool Picture::LoadBmp( const std::string& fname )
{
    std::ifstream in( fname.c_str() , std::ios::in | std::ios::binary );
    return load_bmp( in );
}
//--------------------------------------------------------------
bool Picture::LoadBmp( const char* fname )
{
    std::ifstream in( fname , std::ios::in | std::ios::binary );
    return load_bmp( in );
}
//--------------------------------------------------------------
bool Picture::SaveBmp( const FileName& fname )
{
    std::ofstream out( fname.c_str() , std::ios::out | std::ios::binary );
    return save_bmp( out );
}
//--------------------------------------------------------------
bool Picture::SaveBmp( const std::string& fname )
{
    std::ofstream out( fname.c_str() , std::ios::out | std::ios::binary );
    return save_bmp( out );
}
//--------------------------------------------------------------
bool Picture::SaveBmp( const char* fname )
{
    std::ofstream out( fname , std::ios::out | std::ios::binary );
    return save_bmp( out );
}
//--------------------------------------------------------------
bool Picture::Output( std::ofstream& out )
{
    switch( m_bit_count )
    {
	case 4 :
	    return ::OutputImage4b( m_image, out );
	case 8 :
	    return ::OutputImage8b( m_image, out );
	default :
	    break;
    }
    return false;
}
//--------------------------------------------------------------
bool Picture::Outtxt( std::ofstream& out )
{
    switch( m_bit_count )
    {
	case 4 :
	    return ::OuttxtImage4b( m_image, out );
	case 8 :
	    return ::OuttxtImage8b( m_image, out );
	default :
	    break;
    }
    return false;
}
//--------------------------------------------------------------
void Picture::Set( const Picture& _X )
{
    m_image.Set(((Picture&)_X).GetImage());
    m_palette = ((_Myt&)_X).GetPalette();
    m_bit_count = ((_Myt&)_X).BitCount();
}
//--------------------------------------------------------------
void Picture::SetPalette(const __MAGBX::Palette& Pal)
{
    m_palette = (__MAGBX::Palette&)Pal;
    m_bit_count =( m_palette.Size() <= 16 )? 4 : 8;
}
//--------------------------------------------------------------
Character* Picture::CreateCharacter( u32 _x , u32 _y )
{
    Character *ret_ptr=NULL;
    if( m_bit_count == 4 ) ret_ptr = new Character16;
    else ret_ptr = new Character;
    if( NULL == ret_ptr ) return ret_ptr;
    Rect rc;
    rc.top = _y;
    rc.bottom = _y + 7;
    rc.left = _x;
    rc.right = _x + 7;
    ret_ptr->Set( m_image , 0 , 0 , rc );
    return ret_ptr;
}
//--------------------------------------------------------------

__MAGBX__END

//
//

