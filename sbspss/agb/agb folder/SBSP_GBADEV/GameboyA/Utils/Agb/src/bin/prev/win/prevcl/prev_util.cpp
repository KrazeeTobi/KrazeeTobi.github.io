//======================================================
//    prev_util.cpp                                   
//    Useful functions to be used for previewer
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <string>
#include <Cstdlib>
#include <agbtypes.h>
#include "token_list.h"
#include "token_type.h"
#include "prev_util.h"
//----------------------------------------------------------------------
std::string GetStringFromLiteral(const std::string& str)
{
    std::string ret_str(str);
    std::string::iterator str_it;

    str_it = ret_str.begin();
    if( (*str_it == '\"') || (*str_it == '\'') )
    {
	ret_str.erase(str_it);
    }
    str_it = ret_str.end();
    --str_it;
    if( (*str_it == '\"') || (*str_it == '\'') )
    {
	ret_str.erase(str_it);
    }
    return ret_str;
}
//----------------------------------------------------------------------
double GetValueFromConstant(const std::string& str)
{
    return atof(str.c_str());
}
//----------------------------------------------------------------------
bool ParseString( __MAGBX::TokenList& token_list,
		  std::string& _Str )
{
    Token* tk_ptr;
    if( false == token_list.Get( &tk_ptr ) ) return false;
    if( NULL == tk_ptr ) return false;
    if(tk_ptr->type!=STRING_LITERAL) return false;
    _Str = GetStringFromLiteral( tk_ptr->str );
    return true;
}
//----------------------------------------------------------------------
bool ParseIdentifier( __MAGBX::TokenList& token_list,
		      std::string& _Str )
{
    Token* tk_ptr;
    if( false == token_list.Get( &tk_ptr ) ) return false;
    if( NULL == tk_ptr ) return false;
    if(tk_ptr->type!=IDENTIFIER) return false;
    _Str = tk_ptr->str;
    return true;
}
//----------------------------------------------------------------------
bool ParseSemicolon( __MAGBX::TokenList& token_list)
{
    Token* tk_ptr;
    if( false == token_list.Get( &tk_ptr ) ) return false;
    if( NULL == tk_ptr ) return false;
    if( tk_ptr->type != SEMI_COLON )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool IsNextSemicolon( __MAGBX::TokenList& token_list)
{
    bool ret_value = ParseSemicolon( token_list );
    token_list.Back();
    return ret_value;
}
//----------------------------------------------------------------------
bool FindSemicolon( __MAGBX::TokenList& token_list)
{
    Token* tk_ptr;
    do
    {
	if( false == token_list.Get( &tk_ptr ) )
	{
	    return false;
	}
	if( NULL == tk_ptr )
	{
	    return false;
	}
    } while( tk_ptr->type != SEMI_COLON );
    return true;
    return false;
}
//----------------------------------------------------------------------

//
//
