//======================================================
//    ndpalette.cpp                                   
//    Palette for AGB color format (it is treated as image node)
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include <filename.h>
#include <image.h>
#include <color.h>
#include <picture.h>
#include "ex_reference.h"
#include "nodemagic.h"
#include "nodemanager.h"
#include "token_list.h"
#include "ndimage.h"
#include "token_type.h"
#include "prev_util.h"
#include "ndpalette.h"
#include "agbnode.h"
//----------------------------------------------------------------------
const char* ndpalette_valname_colors = "NumOfColors";
//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
AGBNode* CreatePalette( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr )
{
    AGBNode* node_ptr = new ndPalette( node_magic_ptr,node_manager_ptr );
    if( NULL == node_ptr ) return NULL;
    node_ptr->SetMagic( magic_image );
    return node_ptr;
}
//----------------------------------------------------------------------
bool ndPalette::load_act( const FileName& file_name )
{
    Palette pal(256);
    if( false == pal.LoadACT( file_name ) ) return false;

    Color color;
    color = pal[255];
    u32 loop;

    if( m_width == 16 )
    {
	for( loop=254 ; loop > 0 ; --loop )
	{
	    if( color != pal[loop] ) break;
	}
	if( (loop & 0xf) != 0 ) ++loop;
	pal.Resize( loop );
    }
    set_palette( pal );
    return true;
}
//----------------------------------------------------------------------
bool ndPalette::load_bmp( const FileName& file_name )
{
	//  Load 

    Picture pic;
    if(false == pic.LoadBmp( file_name ) )
    {
	return false;
    }

    set_palette( pic.GetPalette() );

    return true;
}
//----------------------------------------------------------------------
void ndPalette::set_palette( Palette& pal )
{
    Palette* pal_ptr=NULL;
    u32 loop,w_loop;
    if( m_width == 16 )
    {
	for( loop=0 ; loop<pal.Size() ; loop += m_width )
	{
	    pal_ptr = new Palette( m_width );
	    if( NULL == pal_ptr )
	    {
		return;
	    }
	    for( w_loop=0 ; w_loop<m_width ; ++w_loop )
	    {
		pal_ptr->Set( pal[loop+w_loop] , w_loop );
	    }
	    m_image_list.push_back( pal_ptr );
	}
    }
    else
    {
	if( (m_tmp_num == 0) || (pal.NumOfColors() == 256) )
	{
	    pal_ptr = new Palette( m_width );
	    if( NULL == pal_ptr ) return;
	    m_image_list.push_back( pal_ptr );
	}
	pal_ptr = (Palette*)( *( m_image_list.rbegin() ) );
	for( loop=0 ; loop<pal.Size() ; ++loop )
	{
	    pal_ptr->Set( pal[loop] , m_tmp_num + loop );
	}
	m_tmp_num = loop;
	if( m_tmp_num >= 256 )
	{
	    m_tmp_num = 0;
	}
    }
}
//----------------------------------------------------------------------
bool ndPalette::check_width( u16 width )
{
    if( width == 16 ) return true;
    return ( width == 256 );
}
//----------------------------------------------------------------------
bool ndPalette::check_height( u16 height )
{
    return ( height == 1 );
}
//----------------------------------------------------------------------
bool ndPalette::check_bit_count( u16 bit_count )
{
    return (bit_count == 16);
}
//----------------------------------------------------------------------
bool ndPalette::parse_member( TokenList& token_list ,
			     const std::string& identifier )
{
    bool ret_value = false;
    if( identifier == ndpalette_valname_colors )
    {
	ret_value = parse_width( token_list );
    }
    if( identifier == "Files" )
    {
	ret_value = parse_files( token_list );
    }

    return ret_value;
}
//----------------------------------------------------------------------
bool ndPalette::load_file( const FileName& file_name )
{
    if( ((FileName&)file_name).is_extension("act") )
    {
	return load_act( file_name );
    }
    if( ((FileName&)file_name).is_extension("bmp") )
    {
	return load_bmp( file_name );
    }
    return false;
}
//----------------------------------------------------------------------
bool ndPalette::out_c_source_image( std::ofstream& out )
{
    out << std::endl << "const u16";
    out << " " << get_c_image_name().c_str() << "[";
    out << get_image_size()/2 << "] = {" << std::endl;
    std::list<AGBObject*>::iterator im_it;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	if( false == (*im_it)->Outtxt( out ) )
	    return false;
	out << std::endl;
    }
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ndPalette::output_image( std::ofstream& out )
{
    if( false == ::Output( out , (u16)m_image_list.size() ) )
    {
	return false;
    }
    std::list<AGBObject*>::iterator im_it;
    for( im_it = m_image_list.begin() ;
	 im_it != m_image_list.end() ;
	 ++im_it )
    {
	if( false == (*im_it)->Output( out ) )
	    return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool ndPalette::Outtxt( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------------
__MAGBX__END

//
//
