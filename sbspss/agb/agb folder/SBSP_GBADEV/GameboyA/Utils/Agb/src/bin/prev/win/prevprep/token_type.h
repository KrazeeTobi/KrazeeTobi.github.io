//======================================================
//    token_type.h                                   
//    Structure to save token 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_TOKEN_TYPE_H_
#define	_TOKEN_TYPE_H_

#include <string>
#include <list>

//------------------------------------------------------------
typedef struct
{
    int		type;
    std::string	word;
} token_source;
//------------------------------------------------------------
typedef std::list<token_source> token_list;
typedef std::list<token_source>::iterator token_iterator;
//------------------------------------------------------------

#endif	/* _TOKEN_TYPE_H_ */
