//======================================================
//    multi_switch.cpp                                   
//    Multi-switch node for animation 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agbtypes.h>
#include <util.h>
#include "prev_util.h"
#include "agbnode.h"
#include "token_type.h"
#include "token_list.h"
#include "multi_switch.h"
#include "ex_reference.h"
#include "nodemanager.h"

__MAGBX__START

//----------------------------------------------------------------------
AGBNode* CreateMultiSwitch( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr )
{
    return new MultiSwitch( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------------
bool MultiSwitchState::parse_children( TokenList& token_list )
{
    NodeInfo* node_ptr;
    u32 count = 0;
    while(1)
    {
	    //  End with ;. Error if there are no keys. 
	if( true == IsNextSemicolon( token_list ) )
	{
		//  If analysis ends even if there is no key.

	    if( !count )
	    {
		return false;
	    }
	    return true;
	}

	node_ptr = new NodeInfo( m_node_magic_ptr,m_node_manager_ptr);
	if( NULL == node_ptr ) return false;
	if( false == node_ptr->Parse( token_list ) )
	{
	    delete node_ptr;
	    return false;
	}
	m_child_list.push_back( node_ptr );
	++count;
    }
    return true;
}
//----------------------------------------------------------------------
MultiSwitchState::~MultiSwitchState()
{
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_child_list.begin() ;
	child_it != m_child_list.end() ;
	++child_it )
    {
	delete *child_it;
    }
}
//----------------------------------------------------------------------
bool MultiSwitchState::Parse( TokenList& token_list )
{
    if( true == IsNextSemicolon(token_list) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_state ) )
    {
	return false;
    }
    if( false == parse_children( token_list ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitchState::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << "{" << std::endl;
    out << "    " << m_state << "," << std::endl;
    out << "    " << m_child_list.size() << "," << std::endl;
    out << "    " << m_index << std::endl;
    out << "}," << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitchState::OutCSourceArray( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_child_list.begin() ;
	child_it != m_child_list.end() ;
	++child_it )
    {
	if( NULL == *child_it ) return false;
	if( false == (*child_it)->OutCSource( out ) ) return false;
	out << "," << std::endl;
    }
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitchState::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << "\t" << m_state << std::endl;
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_child_list.begin() ;
	child_it != m_child_list.end() ;
	++child_it )
    {
	if( NULL == *child_it ) return false;
	out << "\t";
	if( false == (*child_it)->Outtxt( out ) ) return false;
	out << std::endl;
    }
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitchState::Output( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( false == ::Output( out , (u32)m_state ) ) return false;
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_child_list.begin() ;
	child_it != m_child_list.end() ;
	++child_it )
    {
	if( NULL == *child_it ) return false;
	if( false == (*child_it)->Output( out ) ) return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitchState::OutputArray( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    std::list<NodeInfo*>::iterator child_it;
    for( child_it = m_child_list.begin() ;
	child_it != m_child_list.end() ;
	++child_it )
    {
	if( NULL == *child_it ) return false;
	if( false == (*child_it)->Output( out ) ) return false;
	out << "," << std::endl;
    }
    return true;
}
//----------------------------------------------------------------------
u32  MultiSwitchState::GetSize( void )
{
    return 4 + 4 * m_child_list.size();
}
//----------------------------------------------------------------------
u32  MultiSwitchState::GetState( void )
{
    return m_state;
}
//----------------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------------
bool MultiSwitch::is_member_ok( void )
{
    if( m_switch_map.size() == 0 )
    {
	    //  No distinction based on state.
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitch::parse_member( TokenList& token_list ,
			  const std::string& identifier )
{
    bool ret_value = false;
    if( identifier == "Case" )
    {
	ret_value = parse_case( token_list );
    }
    if( false == ret_value )
    {
	return false;
    }
    return ret_value;
}
//----------------------------------------------------------------------
bool MultiSwitch::parse_case( TokenList& token_list )
{
    MultiSwitchState* state_ptr;
    std::map<u32,MultiSwitchState*>::value_type* state_value_ptr;

    state_ptr = new MultiSwitchState(m_node_magic_ptr,m_node_manager_ptr);
    if( NULL == state_ptr ) return false;
    state_ptr->SetIndex( m_index );
    if( false == state_ptr->Parse( token_list ) )
    {
	delete state_ptr;
	return false;
    }
    m_index += (u16)state_ptr->GetNumOfChildren();
    state_value_ptr = new std::map<u32,MultiSwitchState*>::value_type(
				state_ptr->GetState(),state_ptr);
    if( NULL == state_value_ptr )
    {
	delete state_ptr;
	return false;
    }
    m_switch_map.insert( *state_value_ptr );
    delete state_value_ptr;

    return true;
}
//----------------------------------------------------------------------
MultiSwitch::~MultiSwitch()
{
    std::map<u32,MultiSwitchState*>::iterator switch_map_it;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	delete (*switch_map_it).second;
    }
}
//----------------------------------------------------------------------
u32 MultiSwitch::GetSize(void)
{
    u32 ret_size = AGBNODE_HEAD_SIZE + 4;
    std::map<u32,MultiSwitchState*>::iterator switch_map_it;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	ret_size += ((*switch_map_it).second)->GetSize();
    }
    return ret_size;
}
//----------------------------------------------------------------------
std::string MultiSwitch::GetCStructName( void )
{
    std::string ret_name("nodeMultiSwitch");
    return ret_name;
}
//----------------------------------------------------------------------
std::string MultiSwitch::GetCArrayName( void )
{
    std::string ret_name(GetCName());
    ret_name += "_Children";
    return ret_name;
}
//----------------------------------------------------------------------
std::string MultiSwitch::GetCStateName( void )
{
    std::string ret_name(GetCName());
    ret_name += "_State";
    return ret_name;
}
//----------------------------------------------------------------------
bool MultiSwitch::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitch::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  Output array of child node.

    out << std::endl;
    out << "const u32 " << GetCArrayName().c_str() << "[";
    out << m_index << "] = {" << std::endl;
    std::map<u32,MultiSwitchState*>::iterator switch_map_it;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	if( false == ((*switch_map_it).second)->OutCSourceArray(out) )
	    return false;
    }
    out << "};" << std::endl;

	//  Output array of state.  

    out << std::endl;
    out << "const " << GetCStructName().c_str() << "State";
    out << " " << GetCStateName().c_str() << "[";
    out << m_switch_map.size() << "] = {" << std::endl;
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	if( NULL != (*switch_map_it).second )
	{
	    ((*switch_map_it).second)->OutCSource( out );
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
    out << "," << std::endl;

    out << GetCArrayName().c_str();

    out << std::endl << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool MultiSwitch::Output( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  Output head of node. 
    if( false == output_node_head(out) ) return false;

	//  Output state number.  
    if( false == ::Output( out, (u32)m_switch_map.size() ) ) return false;

	//  Output each state data.  
    std::map<u32,MultiSwitchState*>::iterator switch_map_it;
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
    for( switch_map_it = m_switch_map.begin() ;
	 switch_map_it != m_switch_map.end() ;
	 ++switch_map_it )
    {
	if( NULL != (*switch_map_it).second )
	{
	    if( false == ((*switch_map_it).second)->OutputArray( out ) )
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
