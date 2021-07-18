//======================================================
//    token_list.h                                   
//    Class to save token, and fetch node for evaluation 
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <list>
#include <agbtypes.h>
#include "token_list.h"

__MAGBX__START
//----------------------------------------------------------------------
void TokenList::Clear()
{
    m_token_list.resize(0);
    m_it = m_token_list.begin();
}
//----------------------------------------------------------------------
void TokenList::Add( int type , const char* value_str )
{
    std::string str(value_str);
    Token tk;
    tk.type = type;
    tk.str = str;
    m_token_list.push_back(tk);
}
//----------------------------------------------------------------------
bool TokenList::Get(Token** tk_pptr)
{
    if( NULL == tk_pptr ) return false;
    if( m_token_list.end() == m_it )
    {
	*tk_pptr = NULL;
	return false;
    }
    *tk_pptr = &(*m_it);
    ++m_it;
    return true;
}
//----------------------------------------------------------------------
void TokenList::Back(void)
{
    if( m_token_list.begin() != m_it ) --m_it;
}
//----------------------------------------------------------------------
void TokenList::SetStart(void)
{
    m_it = m_token_list.begin();
}
//----------------------------------------------------------------------
bool TokenList::IsEnd(void)
{
    return (m_it == m_token_list.end());
}
//----------------------------------------------------------------------
__MAGBX__END

//
//
