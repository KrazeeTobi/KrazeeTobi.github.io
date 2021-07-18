//======================================================
//    image.cpp
//    Output Image Class
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agbtypes.h>
#include <util.h>
#include <image.h>

__USING__MAGBX

u8* create_data_array_from_image4b( const Image<u8>& image );
u8* create_data_array_from_image8b( const Image<u8>& image );
u16* create_data_array_from_image16b( const Image<u16>& image );
u32* create_data_array_from_image32b( const Image<u32>& image );
u32 get_array_count_4b( const Image<u8>& image );
u32 get_array_count_8b( const Image<u8>& image );
u32 get_array_count_16b( const Image<u16>& image );
u32 get_array_count_32b( const Image<u32>& image );

bool OutputImage4b( const Image<u8>& image , std::ofstream& out )
{
    u8* data_ptr = create_data_array_from_image4b( image );
    bool ret = ::OutputArray(out,data_ptr,get_array_count_4b(image));
    delete[] data_ptr;
    return ret;
}
bool OutputImage8b( const Image<u8>& image , std::ofstream& out )
{
    u8* data_ptr = create_data_array_from_image8b( image );
    bool ret = ::OutputArray(out,data_ptr,get_array_count_8b(image));
    delete[] data_ptr;
    return ret;
}
bool OutputImage16b( const Image<u16>& image , std::ofstream& out )
{
    u16* data_ptr = create_data_array_from_image16b( image );
    bool ret = ::OutputArray(out,data_ptr,get_array_count_16b(image));
    delete[] data_ptr;
    return ret;
}
bool OutputImage32b( const Image<u32>& image , std::ofstream& out )
{
    u32* data_ptr = create_data_array_from_image32b( image );
    bool ret = ::OutputArray(out,data_ptr,get_array_count_32b(image));
    delete[] data_ptr;
    return ret;
}
bool OuttxtImage4b( const Image<u8>& image , std::ofstream& out )
{
    u8* data_ptr = create_data_array_from_image4b( image );
    bool ret = ::OuttxtArray(out,data_ptr,get_array_count_4b(image));
    delete[] data_ptr;
    return ret;
}
bool OuttxtImage8b( const Image<u8>& image , std::ofstream& out )
{
    u8* data_ptr = create_data_array_from_image8b( image );
    bool ret = ::OuttxtArray(out,data_ptr,get_array_count_8b(image));
    delete[] data_ptr;
    return ret;
}
bool OuttxtImage16b( const Image<u16>& image , std::ofstream& out )
{
    u16* data_ptr = create_data_array_from_image16b( image );
    bool ret = ::OuttxtArray(out,data_ptr,get_array_count_16b(image));
    delete[] data_ptr;
    return ret;
}
bool OuttxtImage32b( const Image<u32>& image , std::ofstream& out )
{
    u32* data_ptr = create_data_array_from_image32b( image );
    bool ret = ::OuttxtArray(out,data_ptr,get_array_count_32b(image));
    delete[] data_ptr;
    return ret;
}

u8* create_data_array_from_image4b( const Image<u8>& image )
{
	u8* ret_buffer = new u8[get_array_count_4b( image )];
	if( NULL == ret_buffer ) return ret_buffer;
	u8* tmp = ret_buffer;
	for( u32 h_loop=0 ; h_loop<((Image<u8>&)image).Height() ; ++h_loop )
	{
		for( u32 w_loop=0 ; w_loop<((Image<u8>&)image).Width() ; w_loop+=2 )
		{
			*tmp = (((Image<u8>&)image).Get(w_loop,h_loop)) << 4;
			*tmp |= ((Image<u8>&)image).Get(w_loop+1,h_loop);
			++tmp;
		}
	}
	return ret_buffer;
}

u8* create_data_array_from_image8b( const Image<u8>& image )
{
	u8* ret_buffer = new u8[get_array_count_8b( image )];
	if( NULL == ret_buffer ) return ret_buffer;
	u8* tmp = ret_buffer;
	for( u32 h_loop=0 ; h_loop<((Image<u8>&)image).Height() ; ++h_loop )
	{
		for( u32 w_loop=0 ; w_loop<((Image<u8>&)image).Width() ; ++w_loop )
		{
			*tmp++ = ((Image<u8>&)image)(w_loop,h_loop);
		}
	}
	return ret_buffer;
}

u16* create_data_array_from_image16b( const Image<u16>& image )
{
	u16* ret_buffer = new u16[get_array_count_16b( image )];
	if( NULL == ret_buffer ) return ret_buffer;
	u16* tmp = ret_buffer;
	for( u32 h_loop=0 ; h_loop<((Image<u16>&)image).Height() ; ++h_loop )
	{
		for( u32 w_loop=0 ; w_loop<((Image<u16>&)image).Width() ; ++w_loop )
		{
			*tmp++ = ((Image<u16>&)image)(w_loop,h_loop);
		}
	}
	return ret_buffer;
}

u32* create_data_array_from_image32b( const Image<u32>& image )
{
	u32* ret_buffer = new u32[get_array_count_32b( image )];
	if( NULL == ret_buffer ) return ret_buffer;
	u32* tmp = ret_buffer;
	for( u32 h_loop=0 ; h_loop<((Image<u32>&)image).Height() ; ++h_loop )
	{
		for( u32 w_loop=0 ; w_loop<((Image<u32>&)image).Width() ; ++w_loop )
		{
			*tmp++ = ((Image<u32>&)image)(w_loop,h_loop);
		}
	}
	return ret_buffer;
}

u32 get_array_count_4b( const Image<u8>& image )
{
    return (u32)(((Image<u8>&)image).Width()*((Image<u8>&)image).Height()/2);
}
u32 get_array_count_8b( const Image<u8>& image )
{
    return (u32)(((Image<u8>&)image).Width()*((Image<u8>&)image).Height());
}
u32 get_array_count_16b( const Image<u16>& image )
{
    return (u32)(((Image<u16>&)image).Width()*((Image<u16>&)image).Height());
}
u32 get_array_count_32b( const Image<u32>& image )
{
    return (u32)(((Image<u32>&)image).Width()*((Image<u32>&)image).Height());
}

//
//
