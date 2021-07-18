//======================================================
//    nodeinfo.cpp                                   
//    Class which obtains node information
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
#include "agbnode.h"
#include "nodemagic.h"
#include "nodemanager.h"
#include "nodeinfo.h"
#include "c_access.h"
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
void NodeInfo::set_true_value( void )
{
    if( NULL == m_node_manager_ptr ) return;
    if( m_node_name == "" )
    {
	if( m_id == 0xffffffff ) return;
	m_node_name = m_node_manager_ptr->GetNodeName( m_id );
    }
    else
    {
	if( m_id == 0xffffffff )
	{
	    m_id = m_node_manager_ptr->GetID( m_node_name );
	}
    }
}
//------------------------------------------------------------------------
void NodeInfo::SetID( u32 id )
{
    if( m_node_name == "" ) m_id = id;
    set_true_value();
}
//------------------------------------------------------------------------
u32 NodeInfo::GetID( void )
{
    set_true_value();
    return m_id;
}
//------------------------------------------------------------------------
void NodeInfo::SetNodeName( const std::string& node_name )
{
    if( m_id == 0xffffffff ) m_node_name = node_name;
    set_true_value();
}
//------------------------------------------------------------------------
std::string NodeInfo::GetNodeName( void )
{
    set_true_value();
    return m_node_name;
}
//------------------------------------------------------------------------
bool NodeInfo::Output( std::ofstream& out )
{
    set_true_value();
    return ::Output( out , m_id );
}
//------------------------------------------------------------------------
bool NodeInfo::Outtxt( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    set_true_value();
    out << "\"" << m_node_name << "\"";
    return true;
}
//------------------------------------------------------------------------
bool NodeInfo::OutCSource( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    set_true_value();
    out << m_id;
    return true;
}
//------------------------------------------------------------------------
bool NodeInfo::Parse( TokenList& token_list )
{
    bool ret_value;
    if( true == IsNextSemicolon( token_list ) ) return false;
    ret_value = ParseString( token_list , m_node_name );
//    if( false == ret_value )
//    {
//    }
    return ret_value;
}
//------------------------------------------------------------------------
__MAGBX__END

//
//
