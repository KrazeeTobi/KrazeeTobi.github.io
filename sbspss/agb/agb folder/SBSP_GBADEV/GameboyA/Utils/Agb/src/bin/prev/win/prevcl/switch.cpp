//======================================================
//    switch.cpp                                   
//    Single switch node for animation
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================


#include <agbtypes.h>
#include <util.h>
#include "prev_util.h"
#include "agbnode.h"
#include "token_type.h"
#include "token_list.h"
#include "switch.h"
#include "ex_reference.h"
#include "nodemanager.h"

__MAGBX__START

//----------------------------------------------------------------------
AGBNode* CreateSwitch( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr )
{
    return new Switch( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------------
bool SwitchState::Parse( TokenList& token_list )
{
    if( true == IsNextSemicolon(token_list) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_state ) )
    {
	return false;
    }
    if( false == ParseString( token_list , m_child_name ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool SwitchState::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << "{   " << m_state << " , ";
    out << m_node_manager_ptr->GetID(m_child_name) << " }";
    return true;
}
//----------------------------------------------------------------------
bool SwitchState::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << m_state << " , \"" << m_child_name.c_str() <<"\"";
    return true;
}
//----------------------------------------------------------------------
bool SwitchState::Output( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( false == ::Output( out , (u32)m_state ) ) return false;
    if( false == ::Output( out ,
	(u32)(m_node_manager_ptr->GetID( m_child_name )) ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
u32  SwitchState::GetSize( void )
{
    return 8;
}
//----------------------------------------------------------------------
u32  SwitchState::GetState( void )
{
    return m_state;
}
//----------------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------------
bool Switch::is_member_ok( void )
{
    if( m_switch_map.size() == 0 )
    {
	    //  No distinction based on state.
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool Switch::parse_member( TokenList& token_list ,
			  const std::string& identifier )
{
    bool ret_value = false;
    if( identifier == "States" )
    {
	ret_value = parse_state( token_list );
    }
    if( false == ret_value )
    {
	return false;
    }
    return ret_value;
}
//----------------------------------------------------------------------
bool Switch::parse_state( TokenList& token_list )
{
    SwitchState* state_ptr;
    std::map<u32,SwitchState*>::value_type* state_value_ptr;
    while( 1 )
    {
	state_ptr = new SwitchState(m_node_magic_ptr,m_node_manager_ptr);
	if( NULL == state_ptr ) return false;
	if( false == state_ptr->Parse( token_list ) )
	{
	    delete state_ptr;
	    return true;
	}
	state_value_ptr = new std::map<u32,SwitchState*>::value_type(
				state_ptr->GetState(),state_ptr);
	if( NULL == state_value_ptr )
	{
	    delete state_ptr;
	    return false;
	}
	m_switch_map.insert( *state_value_ptr );
	delete state_value_ptr;
    }
    return true;
}
//----------------------------------------------------------------------
Switch::~Switch()
{
    std::map<u32,SwitchState*>::iterator switch_map_it;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	delete (*switch_map_it).second;
    }
}
//----------------------------------------------------------------------
u32 Switch::GetSize(void)
{
    return AGBNODE_HEAD_SIZE + 4 + m_switch_map.size()*8;
}
//----------------------------------------------------------------------
std::string Switch::GetCStructName( void )
{
    std::string ret_name("nodeSwitch");
    return ret_name;
}
//----------------------------------------------------------------------
std::string Switch::GetCStateName( void )
{
    std::string ret_name(GetCName());
    ret_name += "_State";
    return ret_name;
}
//----------------------------------------------------------------------
bool Switch::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    return true;
}
//----------------------------------------------------------------------
bool Switch::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  Output array of state first. 

    out << std::endl;
    out << "const " << GetCStructName().c_str() << "State";
    out << " " << GetCStateName().c_str() << "[";
    out << m_switch_map.size() << "] = {" << std::endl;
    std::map<u32,SwitchState*>::iterator switch_map_it;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	if( NULL != (*switch_map_it).second )
	{
	    ((*switch_map_it).second)->OutCSource( out );
	    out << "," << std::endl;
	}
    }
    out << "};" << std::endl;

    out << std::endl;
    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    out_c_source_node_head( out );

    out << m_switch_map.size() << " ," << std::endl;
    out << "(" << GetCStructName().c_str() << "State*)";
    out << GetCStateName().c_str();

    out << std::endl << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool Switch::Output( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  Output head of node.
    if( false == output_node_head(out) ) return false;

	//  Output state number.   
    if( false == ::Output( out, (u32)m_switch_map.size() ) ) return false;

	//  Output each state data.  
    std::map<u32,SwitchState*>::iterator switch_map_it;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	if( NULL != (*switch_map_it).second )
	{
	    if( false == ((*switch_map_it).second)->Output( out ) )
	    {
		return false;
	    }
	}
    }

    return true;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
