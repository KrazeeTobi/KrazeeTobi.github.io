//======================================================
//    c_access.cpp                                       
//    Functions to access each class from C language. 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <list>
#include <agbtypes.h>
#include <filename.h>
#include "token_list.h"
#include "token_type.h"
#include "nodemanager.h"
#include "c_access.h"

//-------------------------------------------------------------
#define	PARSE_MODE_NODE	(0)
#define	PARSE_MODE_LINE	(1)
//-------------------------------------------------------------
static __MAGBX::TokenList* token_list_ptr;
static __MAGBX::NodeManager* node_manager_ptr;
static std::string error_file_name;
static u32 error_line;
static u32 parse_mode;
static u32 node_parenthesis_count;
static PathName pname;
static std::list<FileName> fname_list;
//-------------------------------------------------------------
#ifdef	__cplusplus
extern "C" {
#endif
//-------------------------------------------------------------
int InitApp( const char* input_file_name )
{
    node_manager_ptr = new __MAGBX::NodeManager;
    token_list_ptr = new __MAGBX::TokenList;
    if( NULL == node_manager_ptr || NULL == token_list_ptr )
    {
	std::cerr << "Not enough memory" << std::endl;
	return -1;
    }
    fname_list.resize( 0 );
    error_line = 0;
    parse_mode = PARSE_MODE_NODE;
    node_parenthesis_count = 0;
    SetInputPath( input_file_name );
    SetErrorFileName( input_file_name );
    return 0;
}
//-------------------------------------------------------------
void DeleteApp( void )
{
    delete node_manager_ptr;
    delete token_list_ptr;
}
//-------------------------------------------------------------
int AddToken( u32 token_id , const char* token_str )
{
    if( NULL == token_str ) return -1;
    if( NULL == token_list_ptr ) return -1;
    if( NULL == node_manager_ptr ) return -1;
    std::string tmp_str( token_str );
    int ret_state = 0;
    switch( parse_mode )
    {
	case PARSE_MODE_NODE :
	    if( token_id == PARENTHISIS_OPEN )
	    {
		++node_parenthesis_count;
		break;
	    }
	    if( token_id == PARENTHISIS_CLOSE )
	    {
		if( 0 == --node_parenthesis_count )
		{
		    token_list_ptr->SetStart();
		    if( false == node_manager_ptr->Parse( *token_list_ptr ) )
		    {
			std::cerr << "parse_error" << std::endl;
			ret_state = -1;
		    }
		    token_list_ptr->Clear();
		    break;
		}
		    //  More } than { . 
		if( 0 > node_parenthesis_count )
		{
		    return -1;
		}
	    }
	    if( token_id == LINE )
	    {
		parse_mode = PARSE_MODE_LINE;
		break;
	    }
	    token_list_ptr->Add(token_id,token_str );
	    break;

	case PARSE_MODE_LINE :
	    if( token_id == CONSTANT )
	    {
		SetErrorLine( (u32)GetValueFromConstant(tmp_str) );
		break;
	    }
	    if( token_id == STRING_LITERAL )
	    {
		SetErrorFileName( GetStringFromLiteral(tmp_str).c_str() );
		break;
	    }
	    parse_mode = PARSE_MODE_NODE;
	    AddToken( token_id , token_str );
	    break;
	default :
	    break;
    }
    return ret_state;
}
//-------------------------------------------------------------
void AddErrorLine( u32 add_value )
{
    error_line += add_value;
}
//-------------------------------------------------------------
void SetInputPath( const char* input_name )
{
    if( NULL == input_name )
    {
	pname = "";
    }
    else
    {
	FileName fname( input_name );
	pname = fname.path();
    }
}
//-------------------------------------------------------------
void SetErrorLine( u32 line )
{
    error_line = line;
}
//-------------------------------------------------------------
void SetErrorFileName( const char* file_name )
{
    if( NULL == file_name ) return;
    error_file_name = file_name;

	//  Register the specified file in file list. 

    FileName fname( file_name );
    std::list<FileName>::iterator fname_it;
    for( fname_it = fname_list.begin() ;
	fname_it != fname_list.end() ;
	++fname_it )
    {
	if( (*fname_it).c_string() == fname.c_string() )
	    break;
    }
    if( fname_it == fname_list.end() )
    {
	FileName set_name;
	set_name = pname;
	set_name += fname;
	fname_list.push_back( set_name );
    }
}
//-------------------------------------------------------------
void OutputError( const char* error_message )
{
    if( NULL == error_message ) return;
    std::cerr << error_file_name.c_str() << " ";
    std::cerr << error_line << " : ";
    std::cerr << error_message << std::endl;
}
//-------------------------------------------------------------
int OutDepend( const char* file_name )
{
    if( NULL == file_name ) return -1;
    if( NULL == node_manager_ptr ) return -1;
    FileName fname( file_name );

	//  Get node dependent file.
    node_manager_ptr->GetFileNameList(fname_list);
    std::cout << fname.c_str() << " :";
    std::list<FileName>::iterator fname_it;
    std::list<FileName>::iterator check_it = fname_list.end();
    --check_it;
    for( fname_it = fname_list.begin() ;
	fname_it != fname_list.end() ;
	++fname_it )
    {
	std::cout << " ";
	if( (*fname_it).c_string().length() == 0 ) continue;
	fname.set( pname );
	fname += *fname_it;
	std::cout << fname.c_str();
	if( fname_it != check_it ) std::cout << " \\";
	std::cout << std::endl;
    }
    return 0;
}
//-------------------------------------------------------------
int LoadFile( void )
{
    if( NULL == node_manager_ptr ) return -1;
    if( false == node_manager_ptr->LoadFile(pname) )
    {
	std::cerr << "Failed to read file." << std::endl;
	return -1;
    }
    return 0;
}
//-------------------------------------------------------------
int OutputNode( const char* file_name )
{
    if( NULL == file_name ) return -1;
    FileName out_name( file_name );
    if( (out_name.extension() == "c") || (out_name.extension() == "h") )
    {
	return OutputCSource(out_name.c_str());
    }
    else
    {
	return OutputBinary(out_name.c_str());
    }
}
//-------------------------------------------------------------
int OutputCSource( const char* file_name )
{
    if( NULL == file_name ) return -1;
    if( NULL == node_manager_ptr ) return -1;
    FileName out_name = file_name;
    std::ofstream out;
    out_name.set_extension( "h" );
    std::cerr << '\"' << out_name.c_str() << '\"';
    std::cerr << "Outputting " << std::endl;
    out.open( out_name.c_str() );
    if( false == node_manager_ptr->OutCSourceHeader( out ) )
    {
	std::cerr << "Failed to output header" << std::endl;
	return -1;
    }
    out.close();
    out_name.set_extension( "c" );
    std::cerr << '\"' << out_name.c_str() << '\"';
    std::cerr << "Outputting" << std::endl;
    out.open( out_name.c_str() );
    if( false == node_manager_ptr->OutCSource( out ) )
    {
	std::cerr << "Failed to output chunk of data." << std::endl;
	return -1;
    }
    return 0;
}
//-------------------------------------------------------------
int OutputBinary( const char* file_name )
{
    if( NULL == file_name ) return -1;
    if( NULL == node_manager_ptr ) return -1;
    FileName out_name = file_name;
    std::ofstream out;
    out.open( file_name , std::ios::out | std::ios::binary );
    if( false == node_manager_ptr->Output( out ) )
    {
	std::cerr << "Failed to output chunk of data." << std::endl;
	return -1;
    }
    return 0;
}
//-------------------------------------------------------------
#ifdef	__cplusplus
}
#endif

//
//
