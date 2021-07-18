//======================================================
//    ndcharacter.cpp                                   
//    Character node (handled as image node)  
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include <filename.h>
#include <pathname.h>
#include <image.h>
#include <picture.h>
#include <character16.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "ndimage.h"
#include "nodemagic.h"
#include "ndcharacter.h"

//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
AGBNode* CreateCharacter( NodeMagic* node_magic_ptr ,
	 NodeManager* node_manager_ptr )
{
    AGBNode* node_ptr = new ndCharacter( node_magic_ptr,node_manager_ptr );
    if( NULL == node_ptr ) return NULL;
    node_ptr->SetMagic( magic_image );
    return node_ptr;
}
//----------------------------------------------------------------------
bool ndCharacter::check_width( u16 width )
{
    switch( width )
    {
	case 8 :
	case 16 :
	case 32 :
	case 64 :
	    return true;
	default :
	    break;
    }
    return false;
}
//----------------------------------------------------------------------
bool ndCharacter::check_height( u16 height )
{
    return check_width( height );
}
//----------------------------------------------------------------------
bool ndCharacter::check_bit_count( u16 bit_count )
{
    switch( bit_count )
    {
	case 4 :
	case 8 :
	    return true;
	default :
	    break;
    }
    return true;
}
//----------------------------------------------------------------------
bool ndCharacter::load_file( const FileName& file_name )
{
	//  First, load.
    Picture pic;
    if(false == pic.LoadBmp( file_name ) )
    {
	return false;
    }

	//  Use bit depth of bitmap.

    if( 0 == m_bit_count ) m_bit_count = pic.BitCount();

	//  Divide by character size.  

    Rect rc;
    Image<u8>* im_ptr=NULL;
    for( u32 h_loop = 0 ; h_loop < pic.Height() ; h_loop += m_height )
    {
	for( u32 w_loop = 0 ; w_loop < pic.Width() ; w_loop += m_width )
	{
	    im_ptr = new Image<u8>(m_width,m_height);
	    if( NULL == im_ptr )
	    {
		return false;
	    }
	    rc.top = h_loop;
	    rc.bottom = rc.top + m_height - 1;
	    rc.left = w_loop ;
	    rc.right = rc.left + m_width - 1;
	    im_ptr->Set( pic.GetImage() , 0 , 0 , rc );
	    m_image_list.push_back( im_ptr );
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ndCharacter::parse_images( TokenList& token_list )
{
    return false;
}
//----------------------------------------------------------------------
bool ndCharacter::out_c_source_image_4b( std::ofstream& out, Image<u8>& im)
{
    Rect rc;
    Character16 ch;
    for( u32 h_loop = 0 ; h_loop < m_height ; h_loop += 8 )
    {
	for( u32 w_loop = 0 ; w_loop < m_width ; w_loop += 8 )
	{
	    out << "//  (" << w_loop/8 << "," << h_loop/8 << ")" << std::endl;
	    rc.top = h_loop;
	    rc.bottom = rc.top + 7;
	    rc.left = w_loop ;
	    rc.right = rc.left + 7;
	    ch.Set( im , 0 , 0 , rc );
	    ch.Outtxt( out );
	    out << std::endl << std::endl;
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ndCharacter::out_c_source_image_8b( std::ofstream& out, Image<u8>& im)
{
    Rect rc;
    Character ch;	//  Only this line is different from the above.
    for( u32 h_loop = 0 ; h_loop < m_height ; h_loop += 8 )
    {
	for( u32 w_loop = 0 ; w_loop < m_width ; w_loop += 8 )
	{
	    out << "//  (" << w_loop/8 << "," << h_loop/8 << ")" << std::endl;
	    rc.top = h_loop;
	    rc.bottom = rc.top + 7;
	    rc.left = w_loop ;
	    rc.right = rc.left + 7;
	    ch.Set( im , 0 , 0 , rc );
	    ch.Outtxt( out );
	    out << std::endl << std::endl;
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ndCharacter::out_c_source_image_16b( std::ofstream& out, Image<u16>& im)
{
    return false;
}
//----------------------------------------------------------------------
bool ndCharacter::output_image_4b( std::ofstream& out, Image<u8>& im)
{
    Rect rc;
    Character16 ch;
    for( u32 h_loop = 0 ; h_loop < m_height ; h_loop += 8 )
    {
	for( u32 w_loop = 0 ; w_loop < m_width ; w_loop += 8 )
	{
	    rc.top = h_loop;
	    rc.bottom = rc.top + 7;
	    rc.left = w_loop ;
	    rc.right = rc.left + 7;
	    ch.Set( im , 0 , 0 , rc );
	    ch.Output( out );
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ndCharacter::output_image_8b( std::ofstream& out, Image<u8>& im)
{
    Rect rc;
    Character ch;	//  Only this line is different from the above.
    for( u32 h_loop = 0 ; h_loop < m_height ; h_loop += 8 )
    {
	for( u32 w_loop = 0 ; w_loop < m_width ; w_loop += 8 )
	{
	    rc.top = h_loop;
	    rc.bottom = rc.top + 7;
	    rc.left = w_loop ;
	    rc.right = rc.left + 7;
	    ch.Set( im , 0 , 0 , rc );
	    ch.Output( out );
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ndCharacter::output_image_16b( std::ofstream& out, Image<u16>& im)
{
    return false;
}
//----------------------------------------------------------------------
bool ndCharacter::Outtxt( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------------
__MAGBX__END

//
//
