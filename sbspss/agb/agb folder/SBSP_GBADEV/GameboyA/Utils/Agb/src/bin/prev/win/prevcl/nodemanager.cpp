//======================================================
//    nodemanager.cpp                                   
//    Class to manage all nodes
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <agbtypes.h>
#include "nodemanager.h"
#include "agbnode.h"
#include "screenheader.h"
#include "prev_util.h"
//-----------------------------------------------------------------
__MAGBX__START
//-----------------------------------------------------------------
u32 NodeManager::get_name_size( void )
{
    return (m_name_index + 3) & -4;
}
//-----------------------------------------------------------------
u32 NodeManager::get_offset_table_size( void )
{
    return m_id*4+4;
}
//-----------------------------------------------------------------
bool NodeManager::output_node_header( std::ofstream& out )
{
	//  Identifier of previewer should be included. 
    if( false == ::Output( out , (u32)0) ) return false;
    if( false == ::Output( out , (u32)0) ) return false;
    if( false == ::Output( out , (u32)0) ) return false;

    u32 offset = 28;

	//  nodeOffsetTable offset

    offset += get_name_size();
    if( false == ::Output( out , (u32)offset ) ) return false;

	//  dispHeader offset

    offset += get_offset_table_size();
    if( false == ::Output( out , (u32)offset ) ) return false;

	//  nodeOffsetTable offset

    offset += m_header_ptr->GetDispHeaderSize();
    if( false == ::Output( out , (u32)offset ) ) return false;

	//  nodeOffsetTable offset

    offset += m_header_ptr->GetObjectsSize();
    if( false == ::Output( out , (u32)offset ) ) return false;

    return true;
}
//-----------------------------------------------------------------
bool NodeManager::output_offset_table( std::ofstream& out )
{
    u32 offset = GetSize();
    if( false == ::Output( out , (u32)m_node_map.size() ) )
    {
	return false;
    }
    std::map<u32 , NodeResource>::iterator node_it;
    for( node_it = m_node_map.begin() ;
	node_it != m_node_map.end() ;
	++node_it )
    {
	std::cerr << "node\"" << ((*node_it).second).name.c_str();
	std::cerr << "\" Outputting" << std::endl;
	if( false == ::Output( out , offset ) )
	{
	    return false;
	}
	offset += (((*node_it).second).node_ptr)->GetSize();
    }
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::output_name( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    std::list<std::string>::iterator name_it;
    for( name_it = m_node_name_list.begin() ;
	name_it != m_node_name_list.end() ;
	++name_it )
    {
	out << (*name_it).c_str();
	out << '\0';
    }
	 //  Adjust the length to be multiple of 4. 

    int dummy_num = (4-(m_name_index & 3)) & 3;
    for( int i=0 ; i<dummy_num ; ++i )
    {
	out << '\0';
    }
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::output_nodes( std::ofstream& out )
{
    std::map<u32,NodeResource>::iterator node_it;
    AGBNode* node_ptr;
    for( node_it = m_node_map.begin() ;
	node_it != m_node_map.end() ;
	++node_it )
    {
	node_ptr = (*node_it).second.node_ptr;
	if( NULL == node_ptr )
	{
	    return false;
	}
	if( false == node_ptr->Output( out ) )
	{
	    std::cerr << "\"" << (*node_it).second.name.c_str() << "\"";
	    std::cerr << "An error occurred while outputting" << std::endl;
	    return false;
	}
    }
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::out_c_source_offset_table( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << std::endl;
    out << "const u32 node_table[" << m_node_map.size();
    out << "] = {" << std::endl;
    AGBNode* node_ptr;
    std::map<u32,NodeResource>::iterator node_it;
    for( node_it = m_node_map.begin() ;
	 node_it != m_node_map.end() ;
	 ++node_it )
    {
	node_ptr = ((*node_it).second).node_ptr;
	if( NULL == node_ptr ) return false;
	out << "(u32)(&" << node_ptr->GetCName().c_str();
	out << ")," << std::endl;
    }
    out << "};" << std::endl;
    out << std::endl;
    out << "const nodeOffsetTable node_offset_table = {" << std::endl;
    out << m_node_map.size() << "," << std::endl;
    out << "(u32*)node_table" << std::endl;
    out << "};" << std::endl;
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::out_c_source_header_chunk( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_header_ptr ) return false;
    out << "const nodeHeaderChunk prev_node_header = {" << std::endl;
    out << "{" << std::endl << "0," << std::endl << "0," << std::endl;
    out << "0" << std::endl << "}," << std::endl;

    out << "&node_offset_table," << std::endl;

    out << "&" << m_header_ptr->GetDispHeaderName().c_str();
    out << "," << std::endl;

    out << "&" << m_header_ptr->GetCName().c_str();
    out << "," << std::endl;

    out << "&" << m_header_ptr->GetCName_BG().c_str();
    out << std::endl;

    out << "};" << std::endl;
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::out_c_source_extern_nodes( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << std::endl;
    AGBNode* node_ptr;
    std::map<u32,NodeResource>::iterator node_it;
    for( node_it = m_node_map.begin() ;
	 node_it != m_node_map.end() ;
	 ++node_it )
    {
	node_ptr = ((*node_it).second).node_ptr;
	if( NULL == node_ptr ) return false;
	out << "extern const ";
	out << node_ptr->GetCStructName().c_str();
	out << " " << node_ptr->GetCName().c_str();
	out << ";" << std::endl;
    }
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::out_c_source_nodes( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << std::endl;
    AGBNode* node_ptr;
    std::map<u32,NodeResource>::iterator node_it;
    for( node_it = m_node_map.begin() ;
	 node_it != m_node_map.end() ;
	 ++node_it )
    {
	node_ptr = ((*node_it).second).node_ptr;
	if( NULL == node_ptr ) return false;
	if( false == node_ptr->OutCSource( out ) )
	{
	    std::cerr << "\"" << (*node_it).second.name.c_str() << "\"";
	    std::cerr << "An error occurred while outputting" << std::endl;
	    return false;
	}
	out << std::endl;
    }
    return true;
}
//-----------------------------------------------------------------
NodeManager::~NodeManager()
{
    std::map<u32,NodeResource>::iterator nr_map_it;
    for( nr_map_it = m_node_map.begin() ;
	nr_map_it != m_node_map.end() ;
	++nr_map_it )
    {
	delete (*nr_map_it).second.node_ptr;
    }
}
//-----------------------------------------------------------------
AGBNode* NodeManager::CreateNode( const std::string& MagicName ,
			 	  const std::string& NodeName )
{
    if( NULL == m_node_magic_ptr ) return NULL;
    u32 magic = m_node_magic_ptr->GetMagic( MagicName );
    if( INVALID_MAGIC == magic ) return NULL;
    AGBNode* node_ptr = m_node_magic_ptr->CreateNode( MagicName,this );
    if( NULL == node_ptr ) return NULL;
    NodeResource set_res;
    set_res.id = m_id;
    set_res.node_ptr = node_ptr;
    set_res.name = NodeName;

    std::map<u32,NodeResource>::value_type map_value(m_id,set_res);
    m_node_map.insert( map_value );

    std::map<std::string,u32>::value_type id_value(NodeName,m_id);
    m_id_map.insert( id_value );

    node_ptr->SetID( m_id );
    node_ptr->SetNameIndex( m_name_index );
    node_ptr->SetName( NodeName );
    if( node_ptr->GetMagic() == INVALID_MAGIC )
	node_ptr->SetMagic( magic );

    ++m_id;
    m_node_name_list.push_back( NodeName );
    m_name_index += NodeName.length() + 1;

    return node_ptr;
}
//-----------------------------------------------------------------
AGBNode* NodeManager::GetNodePtr( const std::string& NodeName )
{
    return GetNodePtr( GetID(NodeName) );
}
//-----------------------------------------------------------------
AGBNode* NodeManager::GetNodePtr( u32 id )
{
    std::map<u32,NodeResource>::iterator node_it;
    node_it = m_node_map.find( id );
    std::string ret_name("");
    if( node_it == m_node_map.end() ) return NULL;
    return (*node_it).second.node_ptr;
}
//-----------------------------------------------------------------
u32 NodeManager::GetID( const std::string& NodeName )
{
    std::map<std::string,u32>::iterator id_it;
    id_it = m_id_map.find( NodeName );
    if( id_it == m_id_map.end() ) return INVALID_NODE_ID;
    return (*id_it).second;
}
//-----------------------------------------------------------------
std::string NodeManager::GetNodeName( u32 id )
{
    std::map<u32,NodeResource>::iterator node_it;
    node_it = m_node_map.find( id );
    std::string ret_name("");
    if( node_it != m_node_map.end() )
    {
	ret_name = ((*node_it).second).name;
    }
    return ret_name;
}
//-----------------------------------------------------------------
u32 NodeManager::GetSize( void )
{
    u32 ret_value = 28;
    if( NULL == m_header_ptr ) return 0;
    ret_value += get_name_size();
    ret_value += get_offset_table_size();
    ret_value += m_header_ptr->GetSize();
    return ret_value;
}
//-----------------------------------------------------------------
bool NodeManager::Parse( TokenList& token_list )
{
    std::string magic_name;
    if( false == ParseIdentifier( token_list , magic_name ) )
    {
	std::cerr << "Identifier does not exist." << std::endl;
	return false;
    }
    if( magic_name == "Header" )
    {
	if( NULL != m_header_ptr ) return false;
	m_header_ptr = new ScreenHeader( m_node_magic_ptr , this );
	if( NULL == m_header_ptr ) return false;
	m_header_ptr->SetName( "header" );
	return m_header_ptr->Parse( token_list );
    }
    else
    {
	std::string node_name;
	if( false == ParseString( token_list , node_name ) ) return false;
	AGBNode* node_ptr = CreateNode( magic_name , node_name );
	if( NULL == node_ptr ) return false;
	return node_ptr->Parse( token_list );
	return true;
    }
	//  It will not be here in reality. 
	//  For the above program, true is returned when an error occurs in analysis.  
    return false;
}
//-----------------------------------------------------------------
bool NodeManager::LoadFile( const PathName& path_name )
{
    std::map<u32,NodeResource>::iterator node_it;
    AGBNode* node_ptr;
    for( node_it = m_node_map.begin() ;
	node_it != m_node_map.end() ;
	++node_it )
    {
	node_ptr = (*node_it).second.node_ptr;
	if( NULL == node_ptr )
	{
	    return false;
	}
	if( false == node_ptr->LoadFile( path_name ) )
	{
	    std::cerr << "\"" << (*node_it).second.name.c_str() << "\"";
	    std::cerr << "An error occurred during file load." << std::endl;
	    return false;
	}
    }
    return true;
}
//-----------------------------------------------------------------
void NodeManager::GetFileNameList( std::list<FileName>& fname_list )
{
    std::map<u32,NodeResource>::iterator node_it;
    AGBNode* node_ptr;
    for( node_it = m_node_map.begin() ;
	node_it != m_node_map.end() ;
	++node_it )
    {
	node_ptr = (*node_it).second.node_ptr;
	if( NULL == node_ptr )
	{
	    return;
	}
	node_ptr->GetFileNameList( fname_list );
    }
}
//-----------------------------------------------------------------
bool NodeManager::Output( std::ofstream& out )
{
    if( NULL == m_header_ptr ) return false;
    if( false == output_node_header( out ) ) return false;
    if( false == output_name( out ) ) return false;
    if( false == output_offset_table( out ) ) return false;
    if( false == m_header_ptr->Output( out ) ) return false;
    if( false == output_nodes( out ) ) return false;
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::Outtxt( std::ofstream& out )
{
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::OutCSource( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_header_ptr ) return false;
    out << "#include <agbtypes.h>" << std::endl;
    out << "#include \"prevdata.h\"" << std::endl;
    out << "#include <nodes.h>" << std::endl;
    out << std::endl;
    if( false == m_header_ptr->OutCSource(out) ) return false;
    if( false == out_c_source_offset_table(out) ) return false;
    if( false == out_c_source_header_chunk(out) ) return false;
    if( false == out_c_source_nodes(out) ) return false;
    return true;
}
//-----------------------------------------------------------------
bool NodeManager::OutCSourceHeader( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << "#ifndef __PREVDATA_H__" << std::endl;
    out << "#define __PREVDATA_H__" << std::endl;
    out << std::endl;
    out << "#include <agbtypes.h>" << std::endl;
    out << "#include <nodes.h>" << std::endl;
    out << std::endl;
    if( false == out_c_source_extern_nodes( out ) ) return false;
    out << "extern const nodeHeaderChunk prev_node_header;" << std::endl;
    out << std::endl;
    out << "#endif  //  __PREVDATA_H__" << std::endl;
    return true;
}
//-----------------------------------------------------------------

__MAGBX__END

//
//
