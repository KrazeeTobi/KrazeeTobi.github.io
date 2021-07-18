//======================================================
//    agbnode.cpp                                       
//    Basic class for all nodes
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

//------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <agbtypes.h>
#include <util.h>
#include "token_list.h"
#include "ex_reference.h"
#include "nodemagic.h"
#include "nodemanager.h"
#include "agbnode.h"
#include "prev_util.h"
#include "c_access.h"
//------------------------------------------------------------------------
#define	AGBNODE_ANIME_TYPE_CONST    (0)
#define	AGBNODE_ANIME_TYPE_LINEAR   (1)
#define	AGBNODE_HEAD_SIZE	(12)
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
bool AGBNode::out_c_source_node_head( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << "{" << std::endl;
    out << "    " << m_magic << "," << std::endl;
    out << "    " << GetSize() << "," << std::endl;
    out << "    " << m_name_index << std::endl;
    out << "} ," << std::endl;
    return true;
}
//------------------------------------------------------------------------
bool AGBNode::output_node_head( std::ofstream& out )
{
    if( false == ::Output( out , m_magic ) ) return false;
    if( false == ::Output( out , GetSize() ) ) return false;
    return ::Output( out , m_name_index );
}
//------------------------------------------------------------------------
std::string AGBNode::GetCStructName( void )
{
    std::string tmp = m_name;
    return tmp;
}
//------------------------------------------------------------------------
std::string AGBNode::GetCName(void)
{
    std::string cname = m_name;
    if( NULL != m_node_magic_ptr )
    {
	cname += m_node_magic_ptr->GetMagicName( m_magic );
    }
    return cname;
}
//------------------------------------------------------------------------
void AGBNode::GetFileNameList( std::list<FileName>& fname_list )
{
    std::list<FileName>::iterator my_it,dest_it;
    for( my_it = m_fname_list.begin() ;
	my_it != m_fname_list.end() ;
	++my_it )
    {
	for( dest_it = fname_list.begin() ;
	    dest_it != fname_list.end() ;
	    ++dest_it )
	{
	    if( (*dest_it).c_string() == (*my_it).c_string() ) break;
	}
	if( fname_list.end() == dest_it )
	{
	    fname_list.push_back( *my_it );
	}
    }
}
//------------------------------------------------------------------------
bool AGBNode::LoadFile( const PathName& path_name )
{
    FileName load_name;
    std::list<FileName>::iterator my_it;
    for( my_it = m_fname_list.begin() ;
	my_it != m_fname_list.end() ;
	++my_it )
    {
	load_name = path_name;
	load_name += *my_it;
	if( false == load_file( load_name ) )
	{
	    std::cerr << "\"" << load_name.c_str() << "\"";
	    std::cerr << "cannot read" << std::endl;
	    return false;
	}
    }
    return true;
}
//------------------------------------------------------------------------
bool AGBNode::GetValue(  void* dest, u32 value_id, u32 start, u32 num )
{
    return false;
}
//------------------------------------------------------------------------
bool AGBNode::Parse( TokenList& token_list )
{
    std::string identifier;
    std::string error_message;
    std::cerr << m_name.c_str() << "Analyzing" << std::endl;
    while( 1 )
    {
	if( true == token_list.IsEnd() ) break;
	if( false == ParseIdentifier(token_list,identifier) )
	{
	    token_list.Back();
	    if( true == FindSemicolon(token_list) )
	    {
		continue;
	    }
	    break;
	}
	if( true == parse_member( token_list , identifier ) )
	{
	    if( false == ParseSemicolon(token_list) )
	    {
		std::string error_message;
		error_message = "\"; cannot fine \"";
		ErrorMessage( error_message );
		token_list.Back();
	    }
	    continue;
	}
	error_message = "Variable \"";
	error_message += identifier;
	error_message += "An error is happened in \".";
	ErrorMessage( error_message );
    }
    return true;
}
//------------------------------------------------------------------------
void AGBNode::ErrorMessage( const char* message )
{
    std::string message_str( message );
    ErrorMessage( message_str );
}
//------------------------------------------------------------------------
void AGBNode::ErrorMessage( const std::string& message )
{
    std::string message_str( m_name );
    message_str += " : ";
    message_str += message;
    ::OutputError( message_str.c_str() );
}
//------------------------------------------------------------------------
__MAGBX__END
//------------------------------------------------------------------------

//
//
