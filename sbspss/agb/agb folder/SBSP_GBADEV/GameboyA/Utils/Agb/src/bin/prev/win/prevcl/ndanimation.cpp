//======================================================
//    ndanimation.cpp                                   
//    Animation node
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
#include "ndanimation.h"
#include "nodeinfo.h"
#include "c_access.h"
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
AGBNode* CreateNdAnimation( NodeMagic* node_magic_ptr ,
			 NodeManager* node_manager_ptr )
{
    return new ndAnimation( node_magic_ptr , node_manager_ptr );
}
//------------------------------------------------------------------------
u32 ndAnimation::get_children_size(void)
{
    std::list<NodeInfo*>::iterator child_it;
    child_it = m_children_list.begin();
    if( child_it == m_children_list.end() ) return 0;
    return (u32)((*child_it)->GetSize() * m_children_list.size());
}
//------------------------------------------------------------------------
u32 ndAnimation::get_default_size( void )
{
    return AGBNODE_HEAD_SIZE + 4;
}
//------------------------------------------------------------------------
bool ndAnimation::parse_member( TokenList& token_list ,
			    const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "Children" )
    {
	ret_value =  parse_child( token_list );
    }
    return ret_value;
}
//------------------------------------------------------------------------
bool ndAnimation::parse_child( TokenList& token_list )
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
bool ndAnimation::output_children( std::ofstream& out )
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
bool ndAnimation::outtxt_children( std::ofstream& out )
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
bool ndAnimation::out_c_source_children( std::ofstream& out )
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
bool ndAnimation::out_c_source_children_objects( std::ofstream& out )
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
ndAnimation::~ndAnimation()
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
u32 ndAnimation::GetSize(void)
{
    return get_default_size() + get_children_size();
}
//------------------------------------------------------------------------
std::string ndAnimation::GetCStructName( void )
{
    std::string ret_name("nodeAnimation");
    return ret_name;
}
//------------------------------------------------------------------------
std::string ndAnimation::GetCChildName( void )
{
    std::string ret_name = GetCName();
    ret_name += "_child";
    return ret_name;
}
//------------------------------------------------------------------------
bool ndAnimation::Output( std::ofstream& out )
{
    if( false == output_node_head(out) ) return false;
    if( false == output_children( out ) ) return false;
    return true;
}
//------------------------------------------------------------------------
bool ndAnimation::Outtxt( std::ofstream& out )
{
    if( NULL == m_node_magic_ptr ) return false;

    out << std::endl;
    out << m_node_magic_ptr->GetMagicName(m_magic).c_str() << " ";
    out << "\"" << m_name.c_str() << "\"" << std::endl;
    out << "{" << std::endl;

    if( false == outtxt_children( out ) ) return false;
    out << std::endl;
    out << "};" << std::endl;
    return true;
}
//------------------------------------------------------------------------
bool ndAnimation::OutCSource( std::ofstream& out )
{
    if( false == out_c_source_children_objects( out ) ) return false;

    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == out_c_source_node_head( out ) ) return false;
    if( false == out_c_source_children( out ) ) return false;
    out << std::endl;
    out << "};" << std::endl;
    return true;
}
//------------------------------------------------------------------------
__MAGBX__END

