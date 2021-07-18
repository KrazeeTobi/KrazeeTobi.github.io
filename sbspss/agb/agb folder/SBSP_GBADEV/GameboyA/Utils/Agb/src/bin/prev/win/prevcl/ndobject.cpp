//======================================================
//    ndobject.cpp                                   
//    Object node
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

//------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include <util.h>
#include "token_list.h"
#include "prev_util.h"
#include "ex_reference.h"
#include "nodemanager.h"
#include "agbnode.h"
#include "ndobject.h"
#include "ndimage.h"
#include "nodeinfo.h"
#include "c_access.h"
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
AGBNode* CreateNdObject( NodeMagic* node_magic_ptr ,
			 NodeManager* node_manager_ptr )
{
    return new ndObject( node_magic_ptr , node_manager_ptr );
}
//------------------------------------------------------------------------
bool ndObject::check_width( u8 width )
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
//------------------------------------------------------------------------
bool ndObject::check_height( u8 height )
{
    return check_width( height);
}
//------------------------------------------------------------------------
bool ndObject::check_bit_count( u8 bit_count )
{
    switch( bit_count )
    {
	case 4 :
	case 8 :
	    return true;
	default :
	    break;
    }
    return false;
}
//------------------------------------------------------------------------
u32 ndObject::get_children_size(void)
{
    std::list<NodeInfo*>::iterator child_it;
    child_it = m_children_list.begin();
    if( child_it == m_children_list.end() ) return 0;
    return (u32)((*child_it)->GetSize() * m_children_list.size());
}
//------------------------------------------------------------------------
u32 ndObject::get_default_size( void )
{
    return AGBNODE_HEAD_SIZE + 20;
}
//------------------------------------------------------------------------
bool ndObject::parse_member( TokenList& token_list ,
			    const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "Width" )
    {
	ret_value =  parse_width( token_list );
    }
    if( identifier == "Height" )
    {
	ret_value =  parse_height( token_list );
    }
    if( identifier == "PaletteNumber" )
    {
	ret_value =  parse_palette_number( token_list );
    }
    if( identifier == "Flip" )
    {
	ret_value =  parse_flip( token_list );
    }
    if( identifier == "Mode" )
    {
	ret_value =  parse_mode( token_list );
    }
    if( identifier == "Offset" )
    {
	ret_value =  parse_image( token_list );
    }
    if( identifier == "Animation" )
    {
	ret_value =  parse_animation( token_list );
    }
    if( identifier == "Image" )
    {
	ret_value =  parse_image( token_list );
    }
    if( identifier == "MaxTime" )
    {
	ret_value =  parse_max_time( token_list );
    }
    if( identifier == "MaxState" )
    {
	ret_value =  parse_max_state( token_list );
    }
    if( identifier == "Children" )
    {
	ret_value =  parse_child( token_list );
    }
    return ret_value;
}
//------------------------------------------------------------------------
bool ndObject::parse_width( TokenList& token_list )
{
    u8 set_value;
    if( false == ParseValue( token_list , set_value ) )
    {
	return false;
    }
    if( false == check_width( set_value ) )
    {
	return false;
    }
    m_width = set_value;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_height( TokenList& token_list )
{
    u8 set_value;
    if( false == ParseValue( token_list , set_value ) )
    {
	return false;
    }
    if( false == check_height( set_value ) )
    {
	return false;
    }
    m_height = set_value;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_palette_number( TokenList& token_list )
{
    u8 set_value;
    if( false == ParseValue( token_list , set_value ) )
    {
	return false;
    }
    switch( m_bit_count )
    {
	case 4 :
	    if( set_value >= 16 )
	    {
		return false;
	    }
	    break;
	case 8 :
	    if( set_value != 0 )
	    {
		return false;
	    }
	    break;
	default :
	    break;
    }
    m_palette_number = set_value;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_bit_count( TokenList& token_list )
{
    u8 set_value;
    if( false == ParseValue( token_list , set_value ) )
    {
	return false;
    }
    if( false == check_bit_count( set_value ) )
    {
	return false;
    }
    m_bit_count = set_value;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_flip( TokenList& token_list )
{
    u8 set_value;
    if( false == ParseValue( token_list , set_value ) )
    {
	return false;
    }
    if( set_value >= 4 )
    {
	return false;
    }
    m_flip = set_value;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_offset( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_offset_x ) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_offset_y ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_mode( TokenList& token_list )
{
    u8 set_value;
    if( false == ParseValue( token_list , set_value ) )
    {
	return false;
    }
    if( set_value >= 3 )
    {
	return false;
    }
    m_mode = set_value;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_image( TokenList& token_list )
{
    if( NULL == m_image_child_ptr )
    {
	m_image_child_ptr = new NodeInfo( m_node_magic_ptr ,
					  m_node_manager_ptr );
    }
    if( NULL == m_image_child_ptr ) return false;
    return m_image_child_ptr->Parse( token_list );
}
//------------------------------------------------------------------------
bool ndObject::parse_animation( TokenList& token_list )
{
    if( NULL == m_anim_node_ptr )
    {
	m_anim_node_ptr = new NodeInfo( m_node_magic_ptr ,
					  m_node_manager_ptr );
    }
    if( NULL == m_anim_node_ptr ) return false;
    return m_anim_node_ptr->Parse( token_list );
}
//------------------------------------------------------------------------
bool ndObject::parse_max_time( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_max_time ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_max_state( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_max_state ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::parse_child( TokenList& token_list )
{
    u32 num_of_children = 0;
    NodeInfo* child_ptr;
    std::string error_message( m_name );
    error_message += " : ";
    do
    {
	child_ptr = new NodeInfo(m_node_magic_ptr , m_node_manager_ptr );
	if( NULL == child_ptr )
	{
	    std::cerr << "Memory Over Flow : NodeInfo Create Child ";
	    return false;
	}
	if( false == child_ptr->Parse( token_list ) )
	{
	    delete child_ptr;
	    break;
	}
	m_children_list.push_back( child_ptr );
	++num_of_children;
    } while( 1 );
    if( 0 == num_of_children )
    {
        error_message += "Children are specified, but there are no children.";
	OutputError( error_message.c_str() );
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::output_oam( std::ofstream& out )
{
    if( false == create_oam() ) return false;
    return ::OutputArray( out , m_oam , 3 );
}
//------------------------------------------------------------------------
bool ndObject::output_width( std::ofstream& out )
{
    return ::Output( out , m_width );
}
//------------------------------------------------------------------------
bool ndObject::output_height( std::ofstream& out )
{
    return ::Output( out , m_height );
}
//------------------------------------------------------------------------
bool ndObject::output_palette_number( std::ofstream& out )
{
    return ::Output( out , m_palette_number );
}
//------------------------------------------------------------------------
bool ndObject::output_flip( std::ofstream& out )
{
    return ::Output( out , (u8)(m_flip | ((m_mode & 3)<<2)) );
}
//------------------------------------------------------------------------
bool ndObject::output_offset( std::ofstream& out )
{
    s16 out_x,out_y;
    out_x = (s16)(float)(m_offset_x * 256.0f);
    out_y = (s16)(float)(m_offset_y * 256.0f);
    if( true == ::Output( out , out_x ) )
    {
	return ::Output( out, out_y );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndObject::output_max_time( std::ofstream& out )
{
    return ::Output( out , m_max_time );
}
//------------------------------------------------------------------------
bool ndObject::output_max_state( std::ofstream& out )
{
    return ::Output( out , m_max_state );
}
//------------------------------------------------------------------------
bool ndObject::output_image( std::ofstream& out )
{
    if( NULL == m_image_child_ptr ) return false;
    return m_image_child_ptr->Output( out );
}
//------------------------------------------------------------------------
bool ndObject::output_animation( std::ofstream& out )
{
    if( NULL == m_anim_node_ptr ) return false;
    return m_anim_node_ptr->Output( out );
}
//------------------------------------------------------------------------
bool ndObject::output_children( std::ofstream& out )
{
    if( false == ::Output( out , (u16)(m_children_list.size()) ) )
    {
	return false;
    }
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_children_list.begin() ;
	 child_it != m_children_list.end() ;
	 ++child_it )
    {
	if( NULL == *child_it )
	{
	    return false;
	}
	if( false == (*child_it)->Output( out ) )
	{
	    return false;
	}
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::outtxt_width( std::ofstream& out )
{
    return ::OuttxtValue( out , m_width );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_height( std::ofstream& out )
{
    return ::OuttxtValue( out , m_height );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_palette_number( std::ofstream& out )
{
    return ::OuttxtValue( out , m_palette_number );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_flip( std::ofstream& out )
{
    return ::OuttxtValue( out , m_flip );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_mode( std::ofstream& out )
{
    return ::OuttxtValue( out , m_mode );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_offset( std::ofstream& out )
{
    if( true == ::OuttxtValue( out , m_offset_x ) )
    {
	out << " ";
	return ::OuttxtValue( out, m_offset_y );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndObject::outtxt_max_time( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_time );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_max_state( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_state );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_image( std::ofstream& out )
{
    if( NULL == m_image_child_ptr ) return false;
    return m_image_child_ptr->Outtxt( out );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_animation( std::ofstream& out )
{
    if( NULL == m_anim_node_ptr ) return false;
    return m_anim_node_ptr->Outtxt( out );
}
//------------------------------------------------------------------------
bool ndObject::outtxt_children( std::ofstream& out )
{
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_children_list.begin() ;
	 child_it != m_children_list.end() ;
	 ++child_it )
    {
	if( NULL == *child_it )
	{
	    return false;
	}
	if( false == (*child_it)->Outtxt( out ) )
	{
	    return false;
	}
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_oam( std::ofstream& out )
{
    if( false == create_oam() ) return false;
    return ::OuttxtArray( out , m_oam , 3 );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_width( std::ofstream& out )
{
    return ::OuttxtValue( out , m_width );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_height( std::ofstream& out )
{
    return ::OuttxtValue( out , m_height );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_palette_number( std::ofstream& out )
{
    return ::OuttxtValue( out , m_palette_number );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_flip( std::ofstream& out )
{
    return ::OuttxtValue( out , (u8)(m_flip | ((m_mode & 3)<<2)) );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_offset( std::ofstream& out )
{
    s16 out_x,out_y;
    out_x = (s16)(float)(m_offset_x * 256.0f);
    out_y = (s16)(float)(m_offset_y * 256.0f);
    if( false == ::Outtxt( out , out_x ) )
    {
	return ::Outtxt( out, out_y );
    }
    out << ",";
    return ::Outtxt( out, out_y );
    return false;
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_max_time( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_time );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_max_state( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_state );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_image( std::ofstream& out )
{
    if( NULL == m_image_child_ptr )
    {
	return false;
    }
    return m_image_child_ptr->OutCSource( out );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_animation( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_anim_node_ptr )
    {
	out << "0xffffffff";
	return true;
    }
    return m_anim_node_ptr->OutCSource( out );
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_children( std::ofstream& out )
{
    if( false == ::OuttxtValue( out , (u16)(m_children_list.size()) ) )
    {
	return false;
    }
    out << "," << std::endl;
    out << "(u32*)";
    if( m_children_list.size() == 0 )
    {
	out << "(0)";
    }
    else
    {
	out << GetCChildName().c_str();
    }
    return true;
}
//------------------------------------------------------------------------
bool ndObject::out_c_source_children_objects( std::ofstream& out )
{
    if( m_children_list.size() == 0 ) return true;
    out << "const u32 " << GetCChildName().c_str();
    out << "[" << m_children_list.size() << "] = {" << std::endl;
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_children_list.begin() ;
	 child_it != m_children_list.end() ;
	 ++child_it )
    {
	if( NULL == *child_it )
	{
	    return false;
	}
	if( false == (*child_it)->OutCSource( out ) )
	{
	    return false;
	}
	out << "," << std::endl;
    }
    out << "};" << std::endl;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::create_oam( void )
{
    if( false == set_value_from_image() ) return false;
    m_oam[0] = 0;
    m_oam[1] = 0;
    m_oam[2] = 0;
    switch( m_height )
    {
	case 8 :
	    break;
	case 16 :
	    m_oam[0] |= 0x4000;
	    break;
	case 32 :
	    m_oam[0] |= 0x8000;
	    break;
	case 64 :
	    m_oam[0] |= 0xc000;
	    break;
	default :
	    return false;
    }
    switch( m_width )
    {
	case 8 :
	    break;
	case 16 :
	    m_oam[1] |= 0x4000;
	    break;
	case 32 :
	    m_oam[1] |= 0x8000;
	    break;
	case 64 :
	    m_oam[1] |= 0xc000;
	    break;
	default :
	    return false;
    }
    switch( m_bit_count )
    {
	case 4 :
	    m_oam[2] |= ((u16)(m_palette_number & 0xf)) << 12;
	    break;
	case 8 :
	    m_oam[0] |= 0x2000;
	    break;
	default :
	    return false;
    }
    m_oam[0] |= (m_mode & 0x3) << 10;
    m_oam[1] |= ((u16)(m_flip & 0x3)) << 12;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::set_value_from_image( void )
{
    if( NULL == m_node_manager_ptr )
    {
	return false;
    }
    if( NULL == m_image_child_ptr )
    {
	std::cerr << m_name.c_str() << " : ";
	std::cerr << "There is no default image." << std::endl;
	return false;
    }
    AGBNode* image_ptr;
    image_ptr = m_node_manager_ptr->GetNodePtr( m_image_child_ptr->GetID() );
    if( NULL == image_ptr )
    {
	return false;
    }
    u16 tmp_value;
    if( false == check_width(m_width) )
    {
	if( false==image_ptr->GetValue(&tmp_value,NDIMAGE_VALUE_ID_WIDTH,0,1) )
	{
	    return false;
	}
	if( false == check_width( tmp_value ) )
	{
	    return false;
	}
	m_width = (u8)tmp_value;
    }
    if( false == check_height(m_height) )
    {
	if(false==image_ptr->GetValue(&tmp_value,NDIMAGE_VALUE_ID_HEIGHT,0,1))
	{
	    return false;
	}
	if( false == check_height( tmp_value ) )
	{
	    return false;
	}
	m_height = (u8)tmp_value;
    }
    if( false == check_bit_count(m_bit_count) )
    {
	if( false==image_ptr->GetValue( &tmp_value,
					NDIMAGE_VALUE_ID_BIT_COUNT,0,1) )
	{
	    return false;
	}
	if( false == check_bit_count( tmp_value ) )
	{
	    return false;
	}
	m_bit_count = tmp_value;
    }
    return true;
}
//------------------------------------------------------------------------
ndObject::~ndObject()
{
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_children_list.begin() ;
	 child_it != m_children_list.end() ;
	 ++child_it )
    {
	delete *child_it;
    }
    delete m_image_child_ptr;
}
//------------------------------------------------------------------------
u32 ndObject::GetSize(void)
{
    return get_default_size() + get_children_size();
}
//------------------------------------------------------------------------
std::string ndObject::GetCStructName( void )
{
    std::string ret_name("nodeObject");
    return ret_name;
}
//------------------------------------------------------------------------
std::string ndObject::GetCChildName( void )
{
    std::string ret_name = GetCName();
    ret_name += "_child";
    return ret_name;
}
//------------------------------------------------------------------------
bool ndObject::Output( std::ofstream& out )
{
    if( false == output_node_head(out) ) return false;
    if( false == output_oam( out ) ) return false;
    if( false == output_width( out ) ) return false;
    if( false == output_height( out ) ) return false;
    if( false == output_palette_number( out ) ) return false;
    if( false == output_flip( out ) ) return false;
    if( false == output_offset( out ) ) return false;
    if( false == output_max_time( out ) ) return false;
    if( false == output_max_state( out ) ) return false;
    if( false == output_image( out ) ) return false;
    if( false == output_animation( out ) ) return false;
    if( false == output_children( out ) ) return false;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::Outtxt( std::ofstream& out )
{
    if( NULL == m_node_magic_ptr ) return false;

    out << std::endl;
    out << m_node_magic_ptr->GetMagicName(m_magic).c_str() << " ";
    out << "\"" << m_name.c_str() << "\"" << std::endl;
    out << "{" << std::endl;

    if( false == outtxt_width( out ) ) return false;
    out << std::endl;
    if( false == outtxt_height( out ) ) return false;
    out << std::endl;
    if( false == outtxt_palette_number( out ) ) return false;
    out << std::endl;
    if( false == outtxt_flip( out ) ) return false;
    out << std::endl;
    if( false == outtxt_mode( out ) ) return false;
    out << std::endl;
    if( false == outtxt_offset( out ) ) return false;
    out << std::endl;
    if( false == outtxt_max_time( out ) ) return false;
    out << std::endl;
    if( false == outtxt_max_state( out ) ) return false;
    out << std::endl;
    if( false == outtxt_image( out ) ) return false;
    out << std::endl;
    if( false == outtxt_animation( out ) ) return false;
    out << std::endl;
    if( false == outtxt_children( out ) ) return false;
    out << std::endl;
    out << "};" << std::endl;
    return true;
}
//------------------------------------------------------------------------
bool ndObject::OutCSource( std::ofstream& out )
{
    if( false == out_c_source_children_objects( out ) ) return false;

    if( false == set_value_from_image() ) return false;
    if( false == create_oam() ) return false;

    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == out_c_source_node_head( out ) ) return false;
    if( false == out_c_source_oam( out ) ) return false;
    out << std::endl;
    if( false == out_c_source_width( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_height( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_palette_number( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_flip( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_offset( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_max_time( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_max_state( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_image( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_animation( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_children( out ) ) return false;
    out << std::endl;
    out << "};" << std::endl;
    return true;
}
//------------------------------------------------------------------------
__MAGBX__END

//
//
