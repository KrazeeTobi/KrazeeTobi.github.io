//======================================================
//    ndmapcharacter.cpp                                   
//    Character data for BG (it is treated as an image node)
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include <filename.h>
#include <pathname.h>
#include <image.h>
#include <picture.h>
#include <charset.h>
#include <char16set.h>
#include <char256set.h>
#include <character.h>
#include <character16.h>
#include <character256.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "ndimage.h"
#include "nodemagic.h"
#include "ndcharacter.h"
#include "ndmapcharacter.h"
#include "prev_util.h"

//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
AGBNode* CreateMapCharacter( NodeMagic* node_magic_ptr ,
	 NodeManager* node_manager_ptr )
{
    AGBNode* node_ptr = new ndMapCharacter( node_magic_ptr,node_manager_ptr );
    if( NULL == node_ptr ) return NULL;
    node_ptr->SetMagic( magic_image );
    return node_ptr;
}
//----------------------------------------------------------------------
bool ndMapCharacter::check_width( u16 width )
{
    return (width == 8);
}
//----------------------------------------------------------------------
bool ndMapCharacter::check_height( u16 height )
{
    return check_width( height );
}
//----------------------------------------------------------------------
bool ndMapCharacter::check_bit_count( u16 bit_count )
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
bool ndMapCharacter::out_c_source_image( std::ofstream& out )
{
    out << std::endl << "const u8 ";
    out << get_c_image_name().c_str() << "[";
    out << get_image_size() << "] = {" << std::endl;
    std::list<AGBObject*>::iterator im_it;
    u32 count = 0;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	out << std::endl;
	out << "//  " << count++ << std::endl;
	if( false == (*im_it)->Outtxt( out ) )
	{
	    return false;
	}
	out << std::endl;
    }
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ndMapCharacter::output_image( std::ofstream& out )
{
    std::list<AGBObject*>::iterator im_it;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	if( false == (*im_it)->Output( out ) )
	{
	    return false;
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ndMapCharacter::load_file( const FileName& file_name )
{
    Picture pic;
    Character *ch_ptr=NULL;
    CharSet *ch_set_ptr=NULL;
    Rect rc;
    int w_loop , h_loop;

	//  Read bmp to Picture class

    if(false == pic.LoadBmp( file_name ) )
    {
	std::cerr << "\"" << ((FileName&)file_name).c_str() << "\"";
	std::cerr << ":Cannot open file" << std::endl;
	exit( 1 );
    }

    m_bit_count = pic.BitCount();

	//  Obtains CharSet pointer

    if( pic.BitCount() == 4 )
    {
	m_mode = 1;
	ch_set_ptr = new Char16Set;
    }
    else
    {
	if( m_mode )
	{
	    ch_set_ptr = new Char256Set;
	}
	else
	{
	    ch_set_ptr = new CharSet;
	}
    }
    if( NULL == ch_set_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	exit(1);
    }

	//  Creates Character class from CharSet

    ch_ptr = ch_set_ptr->CreateCharacter();
    if( NULL == ch_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	exit( 1 );
    }

	//  Divides .bmp, and registers as a character  

    for( h_loop = 0 ; h_loop < pic.Height() ; h_loop += 8 )
    {
	for( w_loop = 0 ; w_loop < pic.Width() ; w_loop += 8 )
	{
	    rc.Set( h_loop , h_loop+7 , w_loop , w_loop+7 );
	    ch_ptr->Set( pic.GetImage() , 0 , 0 , rc );
	    if( false == ch_set_ptr->Add( *ch_ptr ) )
	    {
		std::cerr << "Could not add a character" << std::endl;
		exit( 1 );
	    }
	}
    }
    delete ch_ptr ;
    std::list<Character*>::const_iterator ch_ptr_it;
    for(ch_ptr_it = ch_set_ptr->c_list().begin() ;
	ch_ptr_it!= ch_set_ptr->c_list().end() ;
	++ch_ptr_it )
    {
	if( NULL == *ch_ptr_it ) return false;
	ch_ptr = ch_set_ptr->CreateCharacter();
	if( NULL == ch_ptr ) return false;
	ch_ptr->Set( *(*ch_ptr_it) );
	m_image_list.push_back( ch_ptr );
    }
    return true;
}
//----------------------------------------------------------------------
bool ndMapCharacter::parse_member( TokenList& token_list ,
			   const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "Mode" )
    {
	ret_value = parse_mode( token_list );
    }
    if( identifier == "Files" )
    {
	ret_value = parse_files( token_list );
    }

    return ret_value;
}
//----------------------------------------------------------------------
bool ndMapCharacter::parse_mode( TokenList& token_list )
{
    std::string parse_str;
    if( false == ParseString( token_list , parse_str ) )
    {
	return false;
    }
    if( parse_str == "Text" )
    {
	m_mode = 1;
	return true;
    }
    return false;
}
//----------------------------------------------------------------------
bool ndMapCharacter::Outtxt( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------------
__MAGBX__END

