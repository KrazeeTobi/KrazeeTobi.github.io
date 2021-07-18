//======================================================
//    agbanimnode.cpp                                   
//    Basic class of animation node
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbanimnode.h"
#include "token_list.h"
#include "token_type.h"
#include "prev_util.h"
#include "nodemagic.h"
//-----------------------------------------------------------------

__MAGBX__START

//----------------------------------------------------------------
bool KeyObject::out_c_source_value( std::ofstream& out )
{
    return outtxt_value(out);
}
//----------------------------------------------------------------
bool KeyObject::outtxt_value( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool KeyObject::output_value( std::ofstream& out )
{
    return true;
}
//----------------------------------------------------------------
bool KeyObject::parse_time( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_time ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
bool KeyObject::parse_value( TokenList& token_list )
{
    return false;
}
//----------------------------------------------------------------
bool KeyObject::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << "{ " << m_time << ", ";
    if( false == out_c_source_value(out) ) return false;
    out << "}";
    return true;
}
//----------------------------------------------------------------
bool KeyObject::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << m_time << ", ";
    return outtxt_value(out);
}
//----------------------------------------------------------------
bool KeyObject::Output( std::ofstream& out )
{
    if( false == ::Output( out , (u16)m_time ) )
    {
	return false;
    }
    return output_value( out );
}
//----------------------------------------------------------------
bool KeyObject::Parse( TokenList& token_list )
{
    if( false == parse_time( token_list ) )
    {
	return false;
    }
    return parse_value( token_list );
}
//----------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------
KeyObject* AGBAnimNode::create_key_object(void)
{
    return new KeyObject;
}
//----------------------------------------------------------------
bool AGBAnimNode::is_member_ok(void)
{
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::parse_member(TokenList& token_list ,
			       const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "MaxTime" )
    {
	ret_value = parse_max_time( token_list );
    }
    if( identifier == "Type" )
    {
	ret_value = parse_type( token_list );
    }
    if( identifier == "Keys" )
    {
	ret_value = parse_key( token_list );
    }
    return ret_value;
}
//----------------------------------------------------------------
bool AGBAnimNode::parse_type( TokenList& token_list )
{
    std::string type_name;
    if( false == ParseString( token_list , type_name ) )
    {
	return false;
    }
    if( type_name == "Const" ) m_type = 0;
    if( type_name == "Linear" ) m_type = 1;
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::parse_max_time( TokenList& token_list )
{
    u32 max_time;
    if( false == ParseValue( token_list , max_time ) )
    {
	return false;
    }

	//  Confirm if MaxTime does not exceed the max of key.
    std::map<u16,KeyObject*>::reverse_iterator map_rit;
    if( m_key_map.size() != 0 )
    {
	map_rit = m_key_map.rbegin();
	u32 now_max_time = (u32)((*map_rit).first);
	if( now_max_time > max_time )
	{
	    return false;
	}
    }
    m_max_time = (u16)max_time;
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::parse_key( TokenList& token_list )
{
    KeyObject* key_object_ptr;
    std::map<u16,KeyObject*>::value_type* key_value_ptr;
    u32 count = 0;
    while(1)
    {
	    //  End with;. An error if key is 0.  
	if( true == IsNextSemicolon( token_list ) )
	{
		//  If analysis is completed when there is no key.  
	    if( !count )
	    {
		return false;
	    }
	    return true;
	}

	key_object_ptr = create_key_object();
	if( NULL == key_object_ptr ) return false;
	if( false == key_object_ptr->Parse( token_list ) )
	{
	    delete key_object_ptr;
	    return false;
	}
	key_value_ptr = new std::map<u16,KeyObject*>::value_type(
				key_object_ptr->GetTime(),key_object_ptr);
	if( NULL == key_value_ptr )
	{
	    delete key_object_ptr;
	    return false;
	}
	m_key_map.insert( *key_value_ptr );
	delete key_value_ptr;
	++count;
    }
    return true;
}
//----------------------------------------------------------------
u32 AGBAnimNode::get_default_size(void)
{
    return AGBNODE_HEAD_SIZE + 6;
}
//----------------------------------------------------------------
u32 AGBAnimNode::get_key_size(void)
{
    u32 ret_size = 0;
    std::map<u16,KeyObject*>::iterator key_map_it;
    key_map_it = m_key_map.begin();
    if( key_map_it != m_key_map.end() )
    {
	ret_size = m_key_map.size() * (((*key_map_it).second)->GetSize());
    }
    return ret_size;
}
//----------------------------------------------------------------
bool AGBAnimNode::output_type( std::ofstream& out )
{
    return ::Output( out , (u16)m_type );
}
//----------------------------------------------------------------
bool AGBAnimNode::output_max_time( std::ofstream& out )
{
    return ::Output( out , (u16)m_max_time );
}
//----------------------------------------------------------------
bool AGBAnimNode::output_key( std::ofstream& out )
{
    if( false == ::Output( out , (u16)m_key_map.size() ) ) return false;
    std::map<u16,KeyObject*>::iterator key_it;
    for( key_it = m_key_map.begin() ;
	 key_it != m_key_map.end() ;
	 ++key_it )
    {
	if( false == ((*key_it).second)->Output( out ) )
	{
	    return false;
	}
    }
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::outtxt_type( std::ofstream& out )
{
    out << "    " << "Type ";
    if( m_type )
    {
	out << "\"Linear\"";
    }
    else
    {
	out << "\"Const\"";
    }
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::outtxt_max_time( std::ofstream& out )
{
    out << "    " << "MaxTime " << m_max_time;
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::outtxt_key( std::ofstream& out )
{
    out << "    " << "Keys " << std::endl;
    std::map<u16,KeyObject*>::iterator key_map_it;
    for( key_map_it = m_key_map.begin() ;
	 key_map_it != m_key_map.end() ;
	 ++key_map_it )
    {
	out << "\t";
	((*key_map_it).second)->Outtxt( out );
	out << "," << std::endl;
    }
    out << "\t;" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::out_c_source_type( std::ofstream& out )
{
    out << (u16)m_type << ",";
    if( m_type )
    {
	out << "\t//  Linear" << std::endl;
    }
    else
    {
	out << "\t//  Const" << std::endl;
    }
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::out_c_source_max_time( std::ofstream& out )
{
    out << m_max_time;
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::out_c_source_key( std::ofstream& out )
{
    out << GetNumOfKeys() << "," << std::endl;
    out << "(" << GetCStructName().c_str() << "Key*)" << GetCKeyName().c_str();
    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::out_c_source_key_array( std::ofstream& out )
{
    out << "const " << GetCStructName().c_str() << "Key ";
    out << GetCKeyName().c_str();
    out << "[" << GetNumOfKeys() << "] = {" << std::endl;

    std::map<u16,KeyObject*>::iterator key_map_it;
    for( key_map_it = m_key_map.begin() ;
	 key_map_it != m_key_map.end() ;
	 ++key_map_it )
    {
	if( false == ((*key_map_it).second)->OutCSource( out ) )
	{
	    return false;
	}
	out << " ," << std::endl;
    }

    out << "} ;" << std::endl << std::endl;

    return true;
}
//----------------------------------------------------------------
AGBAnimNode::~AGBAnimNode()
{
    std::map<u16,KeyObject*>::iterator key_map_it;
    for( key_map_it = m_key_map.begin() ;
	 key_map_it != m_key_map.end() ;
	 ++key_map_it )
    {
	delete (*key_map_it).second;
    }
}
//----------------------------------------------------------------
u32 AGBAnimNode::GetSize(void)
{
    return get_default_size() + get_key_size();
}
//----------------------------------------------------------------
std::string AGBAnimNode::GetCKeyName(void)
{
    std::string key_name = GetCName();
    key_name += "_Key";
    return key_name;
}
//----------------------------------------------------------------
std::string AGBAnimNode::GetCStructName(void)
{
    std::string ret_name = "nodeAnim";
    return ret_name;
}
//----------------------------------------------------------------
u32  AGBAnimNode::GetNumOfKeys(void)
{
    return (u32)m_key_map.size();
}
//----------------------------------------------------------------
bool AGBAnimNode::Outtxt( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    if( NULL == m_node_magic_ptr ) return false;

    out << std::endl;
    out << m_node_magic_ptr->GetMagicName(m_magic).c_str() << " ";
    out << "\"" << m_name.c_str() << "\"" << std::endl;
    out << "{" << std::endl;

	//  Output in the order of type, max_time, and key.   
    if( false == outtxt_type( out ) ) return false;
    out << ";" << std::endl;
    if( false == outtxt_max_time( out ) ) return false;
    out << ";" << std::endl;
    if( false == outtxt_key( out ) ) return false;
    out << ";" << std::endl;

    out << "}" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::OutCSource( std::ofstream& out )
{
    if( !out.is_open() ) return false;

	//  Output from key data first.  
    out << std::endl;
    out_c_source_key_array( out );

	//  Then, output node data.  

    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == out_c_source_node_head( out ) ) return false;
    if( false == out_c_source_max_time( out ) ) return false;
    out << "," << std::endl;
    if( false == out_c_source_type( out ) ) return false;
    if( false == out_c_source_key( out ) ) return false;
    out << std::endl;

    out << "} ;" << std::endl;

    return true;
}
//----------------------------------------------------------------
bool AGBAnimNode::Output( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    if( NULL == m_node_magic_ptr ) return false;

    if( false == output_node_head( out ) ) return false;
    if( false == output_type( out ) ) return false;
    if( false == output_max_time( out ) ) return false;
    return output_key( out );
}
//----------------------------------------------------------------

__MAGBX__END

//
//
