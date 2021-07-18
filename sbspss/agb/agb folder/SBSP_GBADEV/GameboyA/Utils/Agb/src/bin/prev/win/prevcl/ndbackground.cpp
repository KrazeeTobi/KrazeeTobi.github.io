//======================================================
//    ndbackground.cpp                                   
//    BG node
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
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
#include "ndbackground.h"
#include "ndimage.h"
#include "nodeinfo.h"
#include "c_access.h"
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
AGBNode* CreateNdBackground( NodeMagic* node_magic_ptr ,
			 NodeManager* node_manager_ptr )
{
    return new ndBackground( node_magic_ptr , node_manager_ptr );
}
//------------------------------------------------------------------------
u32 ndBackground::get_children_size(void)
{
    std::list<NodeInfo*>::iterator child_it;
    child_it = m_children_list.begin();
    if( child_it == m_children_list.end() ) return 0;
    return (u32)((*child_it)->GetSize() * m_children_list.size());
}
//------------------------------------------------------------------------
u32 ndBackground::get_default_size( void )
{
    return AGBNODE_HEAD_SIZE + 20;
}
//------------------------------------------------------------------------
bool ndBackground::parse_member( TokenList& token_list ,
			    const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "MapImage" )
    {
	ret_value =  parse_map_image( token_list );
    }
    if( identifier == "MapCharacter" )
    {
	ret_value =  parse_map_character( token_list );
    }
    if( identifier == "Start" )
    {
	ret_value =  parse_start( token_list );
    }
    if( identifier == "Loop" )
    {
	ret_value =  parse_loop( token_list );
    }
    if( identifier == "VramSize" )
    {
	ret_value =  parse_vram_size( token_list );
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
	ret_value =  parse_children( token_list );
    }
    return ret_value;
}
//------------------------------------------------------------------------
bool ndBackground::parse_map_image( TokenList& token_list )
{
    if( NULL == m_map_image_ptr )
    {
	m_map_image_ptr = new NodeInfo( m_node_magic_ptr ,
					  m_node_manager_ptr );
    }
    if( NULL == m_map_image_ptr ) return false;
    return m_map_image_ptr->Parse( token_list );
}
//------------------------------------------------------------------------
bool ndBackground::parse_map_character( TokenList& token_list )
{
    if( NULL == m_map_character_ptr )
    {
	m_map_character_ptr = new NodeInfo( m_node_magic_ptr ,
					  m_node_manager_ptr );
    }
    if( NULL == m_map_character_ptr ) return false;
    return m_map_character_ptr->Parse( token_list );
}
//------------------------------------------------------------------------
bool ndBackground::parse_start( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_start_x ) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_start_y ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::parse_loop( TokenList& token_list )
{
    std::string str;
	//  about X direction 
    if( false == ParseString( token_list , str ) )
    {
	return false;
    }
    if( str == "ON" || str == "0n" || str == "on" )
    {
	m_loop_x_flag = NDBG_LOOP;
    }
    if( str == "OFF" || str == "0ff" || str == "off" )
    {
	m_loop_x_flag = NDBG_NOLOOP;
    }
	//  about Y direction
    if( false == ParseString( token_list , str ) )
    {
	return false;
    }
    if( str == "ON" || str == "0n" || str == "on" )
    {
	m_loop_y_flag = NDBG_LOOP;
    }
    if( str == "OFF" || str == "0ff" || str == "off" )
    {
	m_loop_y_flag = NDBG_NOLOOP;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::parse_vram_size( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_width ) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_height ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::parse_max_time( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_max_time ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::parse_max_state( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_max_state ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::parse_children( TokenList& token_list )
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
bool ndBackground::output_map_image( std::ofstream& out )
{
    if( NULL == m_map_image_ptr ) return false;
    return m_map_image_ptr->Output( out );
}
//------------------------------------------------------------------------
bool ndBackground::output_map_character( std::ofstream& out )
{
    if( NULL == m_map_character_ptr ) return false;
    return m_map_character_ptr->Output( out );
}
//------------------------------------------------------------------------
bool ndBackground::output_start( std::ofstream& out )
{
    if( false != ::Output( out , m_start_x ) )
    {
	return ::Output( out , m_start_y );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndBackground::output_loop( std::ofstream& out )
{
    if( false != ::Output( out , m_loop_x_flag ) )
    {
	return ::Output( out , m_loop_y_flag );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndBackground::output_vram_size( std::ofstream& out )
{
    u8 out_vram_bit_x = 0;
    u8 out_vram_bit_y = 0;
    u16 width = m_width;
    u16 height = m_height;
    while( width > 1 )
    {
	++out_vram_bit_x;
	width >>= 1;
    }
    while( height > 1 )
    {
	++out_vram_bit_y;
	height >>= 1;
    }
    out_vram_bit_x -= 3;
    out_vram_bit_y -= 3;
    if( false != ::Output( out , out_vram_bit_x ) )
    {
	return ::Output( out , out_vram_bit_y );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndBackground::output_max_time( std::ofstream& out )
{
    return ::Output( out , m_max_time );
}
//------------------------------------------------------------------------
bool ndBackground::output_max_state( std::ofstream& out )
{
    return ::Output( out , m_max_state );
}
//------------------------------------------------------------------------
bool ndBackground::output_children( std::ofstream& out )
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
bool ndBackground::outtxt_map_image( std::ofstream& out )
{
    if( NULL == m_map_image_ptr ) return false;
    return m_map_image_ptr->Outtxt( out );
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_map_character( std::ofstream& out )
{
    if( NULL == m_map_character_ptr ) return false;
    return m_map_character_ptr->Outtxt( out );
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_start( std::ofstream& out )
{
    if( false != ::OuttxtValue( out , m_start_x ) )
    {
	return ::OuttxtValue( out , m_start_y );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_loop( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    switch( m_loop_x_flag )
    {
	case NDBG_LOOP :
	    out << "\"ON\"";
	    break;
	case NDBG_NOLOOP :
	    out << "\"OFF\"";
	    break;
	default :
	    return false;
    }
    out << " ";
    switch( m_loop_y_flag )
    {
	case NDBG_LOOP :
	    out << "\"ON\"";
	    break;
	case NDBG_NOLOOP :
	    out << "\"OFF\"";
	    break;
	default :
	    return false;
    }
    return false;
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_vram_size( std::ofstream& out )
{
    if( false != ::OuttxtValue( out , m_width ) )
    {
	return ::OuttxtValue( out , m_height );
    }
    return false;
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_max_time( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_time );
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_max_state( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_state );
}
//------------------------------------------------------------------------
bool ndBackground::outtxt_children( std::ofstream& out )
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
bool ndBackground::out_c_source_map_image( std::ofstream& out )
{
    if( NULL == m_map_image_ptr )
    {
	return false;
    }
    return m_map_image_ptr->OutCSource( out );
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_map_character( std::ofstream& out )
{
    if( NULL == m_map_character_ptr )
    {
	return false;
    }
    return m_map_character_ptr->OutCSource( out );
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_start( std::ofstream& out )
{
    if( false == ::OuttxtValue( out, m_start_x ) )
    {
	return false;
    }
    out << ",";
    if( false == ::OuttxtValue( out, m_start_y ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_loop( std::ofstream& out )
{
    if( false == ::OuttxtValue( out, m_loop_x_flag ) )
    {
	return false;
    }
    out << ",";
    if( false == ::OuttxtValue( out, m_loop_y_flag ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_vram_size( std::ofstream& out )
{
    u8 out_vram_bit_x = 0;
    u8 out_vram_bit_y = 0;
    u16 width = m_width;
    u16 height = m_height;
    while( width > 1 )
    {
	++out_vram_bit_x;
	width >>= 1;
    }
    while( height > 1 )
    {
	++out_vram_bit_y;
	height >>= 1;
    }
    out_vram_bit_x -= 3;
    out_vram_bit_y -= 3;
    if( false == ::OuttxtValue( out, out_vram_bit_x ) )
    {
	return false;
    }
    out << ",";
    if( false == ::OuttxtValue( out, out_vram_bit_y ) )
    {
	return false;
    }
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_max_time( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_time );
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_max_state( std::ofstream& out )
{
    return ::OuttxtValue( out , m_max_state );
}
//------------------------------------------------------------------------
bool ndBackground::out_c_source_children( std::ofstream& out )
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
bool ndBackground::out_c_source_children_nodes( std::ofstream& out )
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
ndBackground::~ndBackground()
{
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_children_list.begin() ;
	 child_it != m_children_list.end() ;
	 ++child_it )
    {
	delete *child_it;
    }
    delete m_map_character_ptr;
    delete m_map_image_ptr;
}
//------------------------------------------------------------------------
u32 ndBackground::GetSize(void)
{
    return get_default_size() + get_children_size();
}
//------------------------------------------------------------------------
bool ndBackground::GetValue( void* dest, u32 value_id, u32 start, u32 num )
{
    u32 count;
    switch( value_id )
    {
	case NDBG_VALUE_MAP_IMAGE :
	    *(NodeInfo**)dest = m_map_image_ptr;
	    return true;
	case NDBG_VALUE_MAP_CHARACTER :
	    *(NodeInfo**)dest = m_map_character_ptr;
	    return true;
	case NDBG_VALUE_START :
	    if( start == 0 )
	    {
		*(s16*)dest = m_start_x;
		if( num >= 2 )
		{
		    *(((s16*)dest)+1) = m_start_y;
		}
		return true;
	    }
	    if( start == 1 )
	    {
		*(s16*)dest = m_start_y;
	    }
	    return true;
	case NDBG_VALUE_LOOP :
	    if( start == 0 )
	    {
		*(u8*)dest = m_loop_x_flag;
		if( num >= 2 )
		{
		    *(((u8*)dest)+1) = m_loop_y_flag;
		}
		return true;
	    }
	    if( start == 1 )
	    {
		*(u8*)dest = m_loop_y_flag;
	    }
	    return true;
	case NDBG_VALUE_VRAM_SIZE :
	    if( start == 0 )
	    {
		*(u16*)dest = m_width;
		if( num >= 2 )
		{
		    *(((u8*)dest)+1) = m_height;
		}
		return true;
	    }
	    if( start == 1 )
	    {
		*(u16*)dest = m_height;
	    }
	    return true;
	case NDBG_VALUE_MAX_TIME :
	    *(u16*)dest = m_max_time;
	    return true;
	case NDBG_VALUE_MAX_STATE :
	    *(u16*)dest = m_max_state;
	    return true;
	case NDBG_VALUE_CHILDREN :
	    count = 0;
	    std::list<NodeInfo*>::iterator child_it;
	    for( child_it = m_children_list.begin() ;
		 child_it != m_children_list.end() ;
		 ++child_it )
	    {
		if( ++count >= start ) break;
	    }
	    if( child_it == m_children_list.end() ) break;
	    count = 0;
	    for( ; child_it != m_children_list.end() ; ++child_it )
	    {
		*((NodeInfo**)dest+count) = *child_it;
		if( ++count >= num ) break;
	    }
	    if( count < num ) break;
	    return true;
    }
    return false;
}
//------------------------------------------------------------------------
std::string ndBackground::GetCStructName( void )
{
    std::string ret_name("nodeBackground");
    return ret_name;
}
//------------------------------------------------------------------------
std::string ndBackground::GetCChildName( void )
{
    std::string ret_name = GetCName();
    ret_name += "_child";
    return ret_name;
}
//------------------------------------------------------------------------
bool ndBackground::Output( std::ofstream& out )
{
    if( false == output_node_head(out) ) return false;
    if( false == output_map_image( out ) ) return false;
    if( false == output_map_character( out ) ) return false;
    if( false == output_start( out ) ) return false;
    if( false == output_loop( out ) ) return false;
    if( false == output_vram_size( out ) ) return false;
    if( false == output_max_time( out ) ) return false;
    if( false == output_max_state( out ) ) return false;
    if( false == output_children( out ) ) return false;
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::Outtxt( std::ofstream& out )
{
    if( NULL == m_node_magic_ptr ) return false;

    out << std::endl;
    out << m_node_magic_ptr->GetMagicName(m_magic).c_str() << " ";
    out << "\"" << m_name.c_str() << "\"" << std::endl;
    out << "{" << std::endl;

    if( false == outtxt_map_image( out ) ) return false;
    out << std::endl;
    if( false == outtxt_map_character( out ) ) return false;
    out << std::endl;
    if( false == outtxt_start( out ) ) return false;
    out << std::endl;
    if( false == outtxt_loop( out ) ) return false;
    out << std::endl;
    if( false == outtxt_vram_size( out ) ) return false;
    out << std::endl;
    if( false == outtxt_max_time( out ) ) return false;
    out << std::endl;
    if( false == outtxt_max_state( out ) ) return false;
    out << std::endl;
    if( false == outtxt_children( out ) ) return false;
    out << std::endl;
    out << "};" << std::endl;
    return true;
}
//------------------------------------------------------------------------
bool ndBackground::OutCSource( std::ofstream& out )
{
    if( false == out_c_source_children_nodes( out ) ) return false;

    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == out_c_source_node_head( out ) ) return false;
    if( false == out_c_source_map_image( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_map_character( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_start( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_loop( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_vram_size( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_max_time( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_max_state( out ) ) return false;
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
