//======================================================
//    token_list.h                                   
//    Definition of class to save token and fetch node for evaluation 
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__TOKEN_LIST_H__
#define	__TOKEN_LIST_H__

#include <list>
#include <agbtypes.h>
//----------------------------------------------------------------------
typedef struct
{
    int type;
    std::string str;
} Token;
//----------------------------------------------------------------------
__MAGBX__START

class TokenList
{
protected :
    std::list<Token>	m_token_list;
    std::list<Token>::iterator m_it;
public :
    TokenList(void){Clear();}
    ~TokenList(){Clear();}

    void Clear(void);
    void Add( int type , const char* value_str );
    bool Get(Token** token_pptr);
    void Back(void);
    void SetStart(void);
    bool IsEnd(void);
};

__MAGBX__END
//----------------------------------------------------------------------

#endif	//  __TOKEN_LIST_H__

//
//
