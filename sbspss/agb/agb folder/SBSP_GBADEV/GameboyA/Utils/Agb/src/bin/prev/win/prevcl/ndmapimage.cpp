//======================================================
//    ndmapimage.cpp                                   
//    Mass data for BG (handled as image node)  
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include <filename.h>
#include <pathname.h>
#include <image.h>
#include <picture.h>
#include <character16.h>
#include <map.h>
#include <map16.h>
#include <map256.h>
#include <maptextimage.h>
#include <mapsrimage.h>
#include <maptextunit.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "ndimage.h"
#include "nodemagic.h"
#include "ndcharacter.h"
#include "ndmapimage.h"
#include "prev_util.h"

//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
AGBNode* CreateMapImage( NodeMagic* node_magic_ptr ,
	 NodeManager* node_manager_ptr )
{
    AGBNode* node_ptr = new ndMapImage( node_magic_ptr,node_manager_ptr );
    if( NULL == node_ptr ) return NULL;
    node_ptr->SetMagic( magic_image );
    return node_ptr;
}
//----------------------------------------------------------------------
bool ndMapImage::load_file( const FileName& file_name )
{
    Picture pic;
    Map *map_ptr=NULL;
    Character *ch_ptr=NULL;
    MapTextImage *map_image_ptr=NULL;
    Rect rc;
    int w_loop , h_loop;

    if(false == pic.LoadBmp( file_name ) )
    {
	return false;
    }
	//  Get Map pointer.   
    if( pic.BitCount() == 4 )
    {
	map_ptr = new Map16(pic.Width()/8 , pic.Height()/8);
	if( NULL != map_ptr )
	    ((Map16*)map_ptr)->SetPaletteNumber(m_palette_number);
    }
    else
    {
	if( m_bit_count == 16 )
	{
	    map_ptr = new Map256(pic.Width()/8 , pic.Height()/8);
	}
	else
	{
	    map_ptr = new Map(pic.Width()/8 , pic.Height()/8);
	}
    }
    if( NULL == map_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	exit(1);
    }
	//  Set Map
    ch_ptr = map_ptr->CreateCharacter();
    if( NULL == ch_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	exit( 1 );
    }
    MapTextUnit unit;
    for( h_loop = 0 ; h_loop < pic.Height() ; h_loop += 8 )
    {
	for( w_loop = 0 ; w_loop < pic.Width() ; w_loop += 8 )
	{
	    rc.top = h_loop;
	    rc.bottom = rc.top + 7;
	    rc.left = w_loop;
	    rc.right = rc.left + 7;

	    ch_ptr->Set( pic.GetImage() , 0 , 0 , rc );
	    if( false==map_ptr->SetCharacter( w_loop/8 , h_loop/8 , *ch_ptr) )
	    {
		std::cerr << "Character could not be added." << std::endl;
		exit( 1 );
	    }
	}
    }
    map_ptr->DeleteCharacter( ch_ptr );

    switch( m_bit_count )
    {
	case 8 :
	    map_image_ptr = new MapSRImage(map_ptr->Width(),map_ptr->Height());
	    break;
	case 16 :
	    map_image_ptr=new MapTextImage(map_ptr->Width(),map_ptr->Height());
	    break;
	default :
	    delete map_ptr;
	    return false;
    }
    if( NULL == map_image_ptr )
    {
	std::cerr << "Not enough memory" << std::endl;
	delete map_ptr;
	return false;
    }

    for( h_loop=0 ; h_loop<map_ptr->Height() ; ++h_loop )
    {
	for( w_loop=0 ; w_loop<map_ptr->Width() ; ++w_loop )
	{
	    map_image_ptr->Set( map_ptr->GetUnit( w_loop, h_loop ) ,
				w_loop, h_loop );
	}
    }
    if( 0 == m_width )
    {
	m_width = map_ptr->Width();
    }
    if( 0 == m_height )
    {
	m_height = map_ptr->Height();
    }
    map_image_ptr->Resize( m_width, m_height );

    m_image_list.push_back( map_image_ptr );

    delete map_ptr;

    return true;
}
//----------------------------------------------------------------------
bool ndMapImage::parse_member( TokenList& token_list ,
			   const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "Width" )
    {
	ret_value = parse_width( token_list );
    }
    if( identifier == "Height" )
    {
	ret_value = parse_height( token_list );
    }
    if( identifier == "Mode" )
    {
	ret_value = parse_mode( token_list );
    }
    if( identifier == "PaletteNumber" )
    {
	ret_value = parse_palette_number( token_list );
    }
    if( identifier == "Files" )
    {
	ret_value = parse_files( token_list );
    }

    return ret_value;
}
//----------------------------------------------------------------------
bool ndMapImage::parse_mode( TokenList& token_list )
{
    std::string parse_str;
    if( false == ParseString( token_list , parse_str ) )
    {
	return false;
    }
    if( parse_str == "Text" )
    {
	m_bit_count = 16;
	return true;
    }
    return false;
}
//----------------------------------------------------------------------
bool ndMapImage::parse_palette_number( TokenList& token_list )
{
    std::string parse_str;
    if( false == ParseValue( token_list , m_palette_number ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool ndMapImage::parse_images( TokenList& token_list )
{
    return false;
}
//----------------------------------------------------------------------
bool ndMapImage::out_c_source_image( std::ofstream& out )
{
    out << std::endl << "const ";
    switch( m_bit_count )
    {
	case 8 :
	    out << "u8 ";
	    break;
	case 16 :
	    out << "u16 ";
	    break;
	default :
	    break;
    }
    out << get_c_image_name().c_str() << "[";
    out << get_image_size() << "] = {" << std::endl;
    std::list<AGBObject*>::iterator im_it;
    u32 count = 0;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	if( false == (*im_it)->Outtxt( out ) )
	{
	    return false;
	}
    }
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ndMapImage::output_image( std::ofstream& out )
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
__MAGBX__END

//
//
