//======================================================
//    palette_animation.cpp                                   
//    Animation to change palette.
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "agbanimnode.h"
#include "token_type.h"
#include "prev_util.h"
#include "nodemagic.h"
#include "nodemanager.h"
#include "token_list.h"
#include "palette_animation.h"
//----------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------
AGBNode* CreatePaletteAnimation( NodeMagic* node_magic_ptr ,
				 NodeManager* node_manager_ptr )
{
    return new PaletteAnimation( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------
bool PaletteAnimationKey::outtxt_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << m_index;
    return true;
}
//----------------------------------------------------------------
bool PaletteAnimationKey::output_value( std::ofstream& out )
{
    return ::Output( out , m_index );
}
//----------------------------------------------------------------
bool PaletteAnimationKey::parse_value( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_index ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
u32  PaletteAnimationKey::GetSize( void )
{
    return 4;
}
//----------------------------------------------------------------

//----------------------------------------------------------------
KeyObject* PaletteAnimation::create_key_object(void)
{
    return new PaletteAnimationKey;
}
//----------------------------------------------------------------
bool  PaletteAnimation::parse_member( TokenList& token_list ,
				     const std::string& identifier )
{
    bool ret_value = false;
    if( identifier == "MaxTime" )
    {
	ret_value = parse_max_time( token_list );
    }
    if( identifier == "Palette" )
    {
	ret_value = parse_palette( token_list );
    }
    if( identifier == "Keys" )
    {
	ret_value = parse_key( token_list );
    }
    return ret_value;
}
//----------------------------------------------------------------
bool PaletteAnimation::parse_type( TokenList& token_list )
{
    return false;
}
//----------------------------------------------------------------
bool PaletteAnimation::parse_palette( TokenList& token_list )
{
    if( false == ParseString( token_list , m_child_name ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
u32 PaletteAnimation::get_default_size(void)
{
    return AGBNODE_HEAD_SIZE + 8;
}
//----------------------------------------------------------------
bool PaletteAnimation::output_type( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool PaletteAnimation::output_palette( std::ofstream& out )
{
    if( NULL == m_node_manager_ptr ) return false;
    if( 0xffffffff == m_child_id )
    {
	m_child_id = m_node_manager_ptr->GetID( m_child_name );
    }
    if( 0xffffffff == m_child_id )
    {
	return false;
    }
    return ::Output( out , (u32)m_child_id );
}
//----------------------------------------------------------------
bool PaletteAnimation::outtxt_type( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool PaletteAnimation::outtxt_palette( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_node_manager_ptr ) return false;
    if( m_child_name == "" )
    {
	m_child_name = m_node_manager_ptr->GetNodeName( m_id );
    }
    if( m_child_name == "" )
    {
	return false;
    }
    out << "\"" << m_child_name.c_str() << "\"";
    return true;
}
//----------------------------------------------------------------
bool PaletteAnimation::out_c_source_type( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool PaletteAnimation::out_c_source_palette( std::ofstream& out )
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
std::string PaletteAnimation::GetCSourceStructName(void)
{
    std::string ret_name = "nodePaletteAnim";
    return ret_name;
}
//----------------------------------------------------------------
bool PaletteAnimation::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( NULL == m_node_magic_ptr ) return false;

    out << std::endl;
    out << m_node_magic_ptr->GetMagicName(m_magic).c_str() << " ";
    out << "\"" << m_name.c_str() << "\"" << std::endl;
    out << "{" << std::endl;

	//  Output in the order of palette, max_time, and key. 
    if( false == outtxt_palette( out ) ) return false;
    out << std::endl;
    if( false == outtxt_max_time( out ) ) return false;
    out << std::endl;
    if( false == outtxt_key( out ) ) return false;
    out << std::endl;

    out << "}" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool PaletteAnimation::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  Output key data first. 

    out << std::endl;
    out_c_source_key_array( out );

	//  Then, output node data. 

    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == out_c_source_node_head( out ) ) return false;
    out << std::endl;
    if( false == out_c_source_palette( out ) ) return false;
    out << std::endl;
    if( false == out_c_source_max_time( out ) ) return false;
    out << std::endl;
    if( false == out_c_source_key( out ) ) return false;
    out << std::endl;

    out << "} ;" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool PaletteAnimation::Output( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( NULL == m_node_magic_ptr ) return false;

    if( false == output_node_head( out ) ) return false;
    if( false == output_palette( out ) ) return false;
    if( false == output_max_time( out ) ) return false;
    return output_key( out );
}
//----------------------------------------------------------------
__MAGBX__END

//
//
