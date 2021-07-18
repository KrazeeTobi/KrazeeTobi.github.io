//======================================================
//    ndimage.cpp                                   
//    Image node
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include <filename.h>
#include <image.h>
#include <util.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "ndimage.h"
#include "token_type.h"
#include "prev_util.h"
#include "c_access.h"
//----------------------------------------------------------------------
const char* ndimage_valname_width = "Width";
const char* ndimage_valname_height = "Height";
const char* ndimage_valname_bit_count = "BitCount";
const char* ndimage_valname_files = "Files";
const char* ndimage_valname_images = "Images";
const char* ndimage_c_struct_name = "nodeImage";
//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------
AGBNode* CreateNdImage( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr )
{
    return new ndImage( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------------
bool ndImage::is_member_ok( void )
{
    if( false == check_width( m_width ) )
    {
	std::cerr << "Error : Width = " << m_width << std::endl;
	return false;
    }
    if( false == check_height( m_height ) )
    {
	std::cerr << "Error : Height = " << m_height << std::endl;
	return false;
    }
    if( false == check_bit_count( m_bit_count ) )
    {
	std::cerr << "Error : BitCount = " << m_bit_count << std::endl;
	return false;
    }
    if(m_image_list.size() == 0)
    {
	std::cerr <<"Error : NumOfImages = "<< m_image_list.size() <<std::endl;
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool ndImage::check_width( u16 width )
{
    return ( width != 0 );
}
//----------------------------------------------------------------------
bool ndImage::check_height( u16 height )
{
    return ( height != 0 );
}
//----------------------------------------------------------------------
bool ndImage::check_bit_count( u16 bit_count )
{
    return ((bit_count == 8) || (bit_count == 16));
}
//----------------------------------------------------------------------
bool ndImage::load_file( const FileName& file_name )
{
    return false;
}
//----------------------------------------------------------------------
bool ndImage::parse_member( TokenList& token_list ,
			   const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == ndimage_valname_width )
    {
	ret_value = parse_width( token_list );
    }
    if( identifier == ndimage_valname_height )
    {
	ret_value = parse_height( token_list );
    }
    if( identifier == ndimage_valname_bit_count )
    {
	ret_value = parse_bit_count( token_list );
    }
    if( identifier == ndimage_valname_files )
    {
	ret_value = parse_files( token_list );
    }
    if( identifier == ndimage_valname_images )
    {
	ret_value = parse_images( token_list );
    }

    return ret_value;
}
//----------------------------------------------------------------------
bool ndImage::parse_width( TokenList& token_list )
{
    u16 set_value;
    std::string error_message( m_name );
    error_message += " : ";
    if( false == ParseValue( token_list , set_value ) )
    {
	error_message += "Width value is not specified.";
	ErrorMessage( error_message.c_str() );
	return false;
    }
    if( false == check_width( set_value ) )
    {
	error_message += "Width value is irregular.";
	ErrorMessage( error_message.c_str() );
	return false;
    }
    m_width = set_value;
    return true;
}
//----------------------------------------------------------------------
bool ndImage::parse_height( TokenList& token_list )
{
    u16 set_value;
    std::string error_message( m_name );
    error_message += " : ";
    if( false == ParseValue( token_list , set_value ) )
    {
	error_message += "Height value is not specified.";
	ErrorMessage( error_message.c_str() );
	return false;
    }

    if( false == check_height( set_value ) )
    {
	error_message += "Height value is irregular. ";
	ErrorMessage( error_message.c_str() );
	return false;
    }
    m_height = set_value;
    return true;
}
//----------------------------------------------------------------------
bool ndImage::parse_bit_count( TokenList& token_list )
{
    u16 set_value;
    std::string error_message( m_name );
    error_message += " : ";
    if( false == ParseValue( token_list , set_value ) )
    {
	error_message += "BitCount value is not specified.";
	ErrorMessage( error_message.c_str() );
	return false;
    }

    if( false == check_bit_count( set_value ) )
    {
	error_message += "BitCount value is irregular.";
	ErrorMessage( error_message.c_str() );
	return false;
    }
    m_height = set_value;
    return true;
}
//----------------------------------------------------------------------
int ndImage::parse_one_image_4b( TokenList& token_list )
{
    u32 w_loop,h_loop;
    u8  value;

    Image<u8>* im_ptr = new Image<u8>(m_width/2,m_height);
    if( NULL == im_ptr ) return -1;

    for( h_loop=0 ; h_loop<m_height ; ++h_loop )
    {
	for( w_loop=0 ; w_loop<m_width/2 ; ++w_loop )
	{
	    if( false == ParseValue( token_list , value ) )
	    {
		if( (h_loop==0) && (w_loop==0) )
		{
		    return 1;
		}
		else
		{
		    return -1;
		}
	    }
	    im_ptr->Set( w_loop*2 , h_loop , (value & 0xf0)>>4 );
	    im_ptr->Set( w_loop*2+1 , h_loop , (value & 0xf) );
	}
    }
    m_image_list.push_back( im_ptr );
    return 0;
}
//----------------------------------------------------------------------
int ndImage::parse_one_image_8b( TokenList& token_list )
{
    u32 w_loop,h_loop;
    u8  value;

    Image<u8>* im_ptr = new Image<u8>(m_width,m_height);
    if( NULL == im_ptr ) return -1;

    for( h_loop=0 ; h_loop<m_height ; ++h_loop )
    {
	for( w_loop=0 ; w_loop<m_width ; ++w_loop )
	{
	    if( false == ParseValue( token_list , value ) )
	    {
		if( (h_loop==0) && (w_loop==0) )
		{
		    return 1;
		}
		else
		{
		    return -1;
		}
	    }
	    im_ptr->Set( w_loop , h_loop , value );
	}
    }
    m_image_list.push_back( im_ptr );
    return 0;
}
//----------------------------------------------------------------------
int ndImage::parse_one_image_16b( TokenList& token_list )
{
    u32 w_loop,h_loop;
    u16  value;

    Image<u16>* im_ptr = new Image<u16>(m_width,m_height);
    if( NULL == im_ptr ) return -1;

    for( h_loop=0 ; h_loop<m_height ; ++h_loop )
    {
	for( w_loop=0 ; w_loop<m_width ; ++w_loop )
	{
	    if( false == ParseValue( token_list , value ) )
	    {
		if( (h_loop==0) && (w_loop==0) )
		{
		    return 1;
		}
		else
		{
		    return -1;
		}
	    }
	    im_ptr->Set( w_loop , h_loop , value );
	}
    }
    m_image_list.push_back( im_ptr );
    return 0;
}
//----------------------------------------------------------------------
bool ndImage::parse_images( TokenList& token_list )
{
    if( false == check_bit_count( m_bit_count ) )
    {
	return false;
    }
    FileName filename;
    u32 load_count = 0;
    int ret_val;
    switch( m_bit_count )
    {
	case 4 :
	    while( 1 )
	    {
		ret_val = parse_one_image_4b(token_list);
		if( -1 == ret_val ) return false;
		if( 1 == ret_val ) return (0!=load_count);
		++load_count;
	    }
	    break;
	case 8 :
	    while( 1 )
	    {
		ret_val = parse_one_image_8b(token_list);
		if( -1 == ret_val ) return false;
		if( 1 == ret_val ) return (0!=load_count);
		++load_count;
	    }
	    break;
	case 16 :
	    while( 1 )
	    {
		ret_val = parse_one_image_16b(token_list);
		if( -1 == ret_val ) return false;
		if( 1 == ret_val ) return (0!=load_count);
		++load_count;
	    }
	    break;
	default :
	    return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool ndImage::parse_files( TokenList& token_list )
{
//    if( (0 == m_width) || (0==m_height) ) return false;
    FileName filename;
    u32 load_count = 0;
    std::string fname_str;
    std::string error_message;
    error_message += " : ";
    while( 1 )
    {
	if( (true == IsNextSemicolon( token_list ))
	 || (false == ParseString( token_list , fname_str ) ) )
	{
	    if( load_count > 0 )
	    {
		return true;
	    }
	    error_message += "Not one Image is specified.";
	    ErrorMessage( error_message.c_str() );
	    return false;
	}
	filename = fname_str;
	m_fname_list.push_back( filename );
	++load_count;
    }
    return true;
}
//----------------------------------------------------------------------
u32  ndImage::get_one_image_size( void )
{
    return (u32)(m_width*m_height*m_bit_count/8);
}
//----------------------------------------------------------------------
u32  ndImage::get_image_size( void )
{
    return (u32)(get_one_image_size()*m_image_list.size());
}
//----------------------------------------------------------------------
bool ndImage::out_c_source_image_4b( std::ofstream& out, Image<u8>& im)
{
    bool ret_value = ::OuttxtImage4b( im , out );
    if( ret_value == true )
    {
	out << ",";
    }
    return ret_value;
}
//----------------------------------------------------------------------
bool ndImage::out_c_source_image_8b( std::ofstream& out, Image<u8>& im)
{
    bool ret_value = ::OuttxtImage8b( im , out );
    if( ret_value == true )
    {
	out << ",";
    }
    return ret_value;
}
//----------------------------------------------------------------------
bool ndImage::out_c_source_image_16b( std::ofstream& out, Image<u16>& im)
{
    bool ret_value = ::OuttxtImage16b( im , out );
    if( ret_value == true )
    {
	out << ",";
    }
    return ret_value;
}
//----------------------------------------------------------------------
bool ndImage::out_c_source_param( std::ofstream& out )
{
    out << std::endl;
    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << "= {" << std::endl;
    out_c_source_node_head( out );
    out << m_width << "," << std::endl;
    out << m_height << "," << std::endl;
    out << m_bit_count << "," << std::endl;
    out << m_image_list.size() << "," << std::endl;
    out << "(u8*)";
    out << get_c_image_name().c_str() << std::endl;
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ndImage::out_c_source_image( std::ofstream& out )
{
    out << std::endl << "const ";
    switch( m_bit_count )
    {
	case 4 :
	case 8 :
	    out << "u8";
	    break;
	case 16 :
	    out << "u16";
	    break;
	default :
	    return false;
    }
    out << " " << get_c_image_name().c_str() << "[";
    out << get_image_size() << "] = {" << std::endl;
    std::list<AGBObject*>::iterator im_it;
    u32 count = 0;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	out << "//\t<" << count++ << ">" << std::endl;
	switch( m_bit_count )
	{
	    case 4 :
		if( false == out_c_source_image_4b( out ,
				*((Image<u8>*)(*im_it)) ) )
		    return false;
		break;
	    case 8 :
		if( false == out_c_source_image_8b( out,
				*((Image<u8>*)(*im_it)) ) )
		    return false;
		break;
	    case 16 :
		if( false == out_c_source_image_16b( out,
				*((Image<u16>*)(*im_it)) ) )
		    return false;
		break;
	    default :
		return false;
	}
    }
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ndImage::output_image_4b( std::ofstream& out, Image<u8>& im)
{
    return ::OutputImage4b( im , out );
}
//----------------------------------------------------------------------
bool ndImage::output_image_8b( std::ofstream& out, Image<u8>& im)
{
    return ::OutputImage8b( im , out );
}
//----------------------------------------------------------------------
bool ndImage::output_image_16b( std::ofstream& out, Image<u16>& im)
{
    return ::OutputImage16b( im , out );
}
//----------------------------------------------------------------------
bool ndImage::output_param( std::ofstream& out )
{
    if( false == output_node_head( out ) ) return false;
    if( false == ::Output( out ,(u16)m_width ) ) return false;
    if( false == ::Output( out ,(u16)m_height ) ) return false;
    return ::Output( out ,(u16)m_bit_count );
}
//----------------------------------------------------------------------
bool ndImage::output_image( std::ofstream& out )
{
    if( false == ::Output( out , (u16)m_image_list.size() ) ) return false;
    std::list<AGBObject*>::iterator im_it;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	switch( m_bit_count )
	{
	    case 4 :
		if( false == output_image_4b( out , *((Image<u8>*)(*im_it)) ) )
		    return false;
		break;
	    case 8 :
		if( false == output_image_8b( out , *((Image<u8>*)(*im_it)) ) )
		    return false;
		break;
	    case 16 :
		if( false == output_image_16b( out,*((Image<u16>*)(*im_it)) ) )
		    return false;
		break;
	    default :
		return false;
	}
    }
    return true;
}
//----------------------------------------------------------------------
std::string ndImage::get_c_image_name(void)
{
    std::string ret_name = GetCName();
    ret_name += "_data";
    return ret_name;
}
//----------------------------------------------------------------------
ndImage::~ndImage()
{
    std::list<AGBObject*>::iterator image_it;
    for( image_it = m_image_list.begin() ;
	 image_it != m_image_list.end() ;
	 ++image_it )
    {
	delete *image_it;
    }
}
//----------------------------------------------------------------------
u32  ndImage::GetSize(void)
{
    u32 ret_size = AGBNODE_HEAD_SIZE;
    ret_size += 8;
    ret_size += get_image_size();
    return ret_size;
}
//----------------------------------------------------------------------
bool ndImage::GetValue( void* dest_ptr, u32 value_id, u32 start, u32 num)
{
    if( NULL == dest_ptr ) return false;
    switch( value_id )
    {
	case NDIMAGE_VALUE_ID_WIDTH :
	    if( (start != 0) || (num != 1) ) return false;
	    (*(u16*)dest_ptr) = m_width;
	    return true;
	case NDIMAGE_VALUE_ID_HEIGHT :
	    if( (start != 0) || (num != 1) ) return false;
	    (*(u16*)dest_ptr) = m_height;
	    return true;
	case NDIMAGE_VALUE_ID_BIT_COUNT :
	    if( (start != 0) || (num != 1) ) return false;
	    (*(u16*)dest_ptr) = m_bit_count;
	    return true;
	default :
	    break;
    }
    return false;
}
//----------------------------------------------------------------------
std::string ndImage::GetCStructName( void )
{
    std::string ret_str(ndimage_c_struct_name);
    return ret_str;
}
//----------------------------------------------------------------------
bool ndImage::Outtxt( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------------
bool ndImage::OutCSource( std::ofstream& out )
{
    if( false == is_member_ok() ) return false;
    if( false == out_c_source_image( out ) ) return false;
    return out_c_source_param( out );
}
//----------------------------------------------------------------------
bool ndImage::Output( std::ofstream& out )
{
    if( false == is_member_ok() ) return false;
    if( false == output_param(out) ) return false;
    return output_image(out);
}
//----------------------------------------------------------------------
__MAGBX__END

//
//
