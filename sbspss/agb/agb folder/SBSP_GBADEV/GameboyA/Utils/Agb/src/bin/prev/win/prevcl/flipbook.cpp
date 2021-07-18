//======================================================
//    flipbook.cpp                                   
//    Flip book animation node
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbanimnode.h"
#include "token_list.h"
#include "token_type.h"
#include "flipbook.h"
#include "prev_util.h"
#include "nodemanager.h"
//----------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------
AGBNode* CreateFlipBook( NodeMagic* node_magic_ptr ,
			 NodeManager* node_manager_ptr )
{
    return new FlipBook( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------
bool FlipBookKey::out_c_source_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << m_frame << ", " << (u16)m_flip << ", " << (u16)0;
    return true;
}
//----------------------------------------------------------------
bool FlipBookKey::outtxt_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << m_frame << ", " << (u16)m_flip;
    return true;
}
//----------------------------------------------------------------
bool FlipBookKey::output_value( std::ofstream& out )
{
    if( false == ::Output( out , (u16)m_frame ) ) return false;
    if( false == ::Output( out , (u8)m_flip ) ) return false;
    return ::Output( out , (u8)0 );
}
//----------------------------------------------------------------
bool FlipBookKey::parse_value( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_frame ) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_flip ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
u32 FlipBookKey::GetSize( void )
{
    return (u32)6;
}
//----------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------
KeyObject* FlipBook::create_key_object(void)
{
    return new FlipBookKey;
}
//----------------------------------------------------------------
bool  FlipBook::parse_member( TokenList& token_list ,
			      const std::string& identifier )
{
    bool ret_value = false;
    if( identifier == "MaxTime" )
    {
	ret_value = parse_max_time( token_list );
    }
    if( identifier == "Image" )
    {
	ret_value = parse_image( token_list );
    }
    if( identifier == "Keys" )
    {
	ret_value = parse_key( token_list );
    }
    return ret_value;
}
//----------------------------------------------------------------
bool FlipBook::parse_type( TokenList& token_list )
{
    return false;
}
//----------------------------------------------------------------
bool FlipBook::parse_image( TokenList& token_list )
{
    if( false == ParseString( token_list , m_child_name ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
u32 FlipBook::get_default_size(void)
{
    return AGBNODE_HEAD_SIZE + 8;
}
//----------------------------------------------------------------
bool FlipBook::output_type( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool FlipBook::output_image( std::ofstream& out )
{
    if( NULL == m_node_manager_ptr ) return false;
    if( 0xffffffff == m_child_id )
    {
	m_child_id = m_node_manager_ptr->GetID( m_child_name );
	if( 0xffffffff == m_child_id )
	{
	    return false;
	}
    }
    return ::Output( out , (u32)m_child_id );
}
//----------------------------------------------------------------
bool FlipBook::outtxt_type( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool FlipBook::outtxt_image( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_node_manager_ptr ) return false;
    if( m_child_name == "" )
    {
	m_child_name = m_node_manager_ptr->GetNodeName( m_id );
	if( m_child_name == "" )
	{
	    return false;
	}
    }
    out << "\"" << m_child_name.c_str() << "\"";
    return true;
}
//----------------------------------------------------------------
bool FlipBook::out_c_source_type( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool FlipBook::out_c_source_image( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_node_manager_ptr ) return false;
    if( 0xffffffff == m_child_id )
    {
	m_child_id = m_node_manager_ptr->GetID( m_child_name );
	if( 0xffffffff == m_child_id )
	{
	    return false;
	}
    }
    out << m_child_id;
    return true;
}
//----------------------------------------------------------------
std::string FlipBook::GetCStructName(void)
{
    std::string ret_name = "nodeFlipBook";
    return ret_name;
}
//----------------------------------------------------------------
bool FlipBook::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( NULL == m_node_magic_ptr ) return false;

    out << std::endl;
    out << m_node_magic_ptr->GetMagicName(m_magic).c_str() << " ";
    out << "\"" << m_name.c_str() << "\"" << std::endl;
    out << "{" << std::endl;

	//  Output image, max_time, and key - in that order.
    if( false == outtxt_image( out ) ) return false;
    out << ";" << std::endl;
    if( false == outtxt_max_time( out ) ) return false;
    out << ";" << std::endl;
    if( false == outtxt_key( out ) ) return false;
    out << std::endl;

    out << "}" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool FlipBook::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  First, output from key data

    out << std::endl;
    out_c_source_key_array( out );

	//  then, output from node data

    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == out_c_source_node_head( out ) ) return false;
    if( false == out_c_source_image( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_max_time( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_key( out ) ) return false;
    out << std::endl;

    out << "} ;" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool FlipBook::Output( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( NULL == m_node_magic_ptr ) return false;

    if( false == output_node_head( out ) ) return false;
    if( false == output_image( out ) ) return false;
    if( false == output_max_time( out ) ) return false;
    return output_key( out );
}
//----------------------------------------------------------------
__MAGBX__END

//
//
