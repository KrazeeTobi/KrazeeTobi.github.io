//======================================================
//    token_type.h                                   
//    Definition of token types
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__TOKEN_TYPE_H__
#define	__TOKEN_TYPE_H__

enum token_type
{

    UNDEFINED = 257,
//    PERIOD,
//    MARK,
//    DOUBLE_QT,
    LINE,
//    KEYWORD,
    PARENTHISIS_OPEN,
    PARENTHISIS_CLOSE,
    SPACE,
    IDENTIFIER,
    CONSTANT,
    SEMI_COLON,
    STRING_LITERAL,
    END_OF_LINE,
};

#endif	//  __TOKEN_TYPE_H__

//
//
