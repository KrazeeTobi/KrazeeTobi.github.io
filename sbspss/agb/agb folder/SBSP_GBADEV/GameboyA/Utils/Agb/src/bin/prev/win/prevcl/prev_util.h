//======================================================
//    prev_util.h                                   
//    Definitions of useful functions to be used for previewer
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__PREV_UTIL_H__
#define	__PREV_UTIL_H__

#include <string>
#include "token_type.h"
#include "token_list.h"
//----------------------------------------------------------------------
std::string GetStringFromLiteral(const std::string& str);
double	    GetValueFromConstant(const std::string& str);
//----------------------------------------------------------------------
__USING__MAGBX
bool ParseString( TokenList& token_list ,
		  std::string& str );
bool ParseIdentifier( TokenList& token_list ,
		      std::string& str );
bool ParseSemicolon( TokenList& token_list );
bool IsNextSemicolon( TokenList& token_list );
bool FindSemicolon( TokenList& token_list );

template<class _Ty>
bool ParseValue( TokenList& token_list , _Ty& _Pt )
{
    Token* tk_ptr;
    if( false == token_list.Get( &tk_ptr ) ) return false;
    if( NULL == tk_ptr ) return false;
    if( tk_ptr->type != CONSTANT ) return false;
    _Pt = (_Ty)GetValueFromConstant( tk_ptr->str );
    return true;
}
//----------------------------------------------------------------------

#endif	//  __PREV_UTIL_H__

//
//
