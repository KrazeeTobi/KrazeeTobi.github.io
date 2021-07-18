//======================================================
//    global.h                                   
//    Function to confirm the token type and the 
//    existence of define 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_GLOBAL_H_
#define	_GLOBAL_H_

enum token_number{

    UNDEFINED = 257,
    PERIOD,
    MARK,
    DOUBLE_QT,
    LINE,
    DEFINE,
    UNDEF,
    INCLUDE,
    IF,
    IFDEF,
    IFNDEF,
    ELSE,
    ENDIF,
    KEYWORD,
    SPACE,
    IDENTIFIER,
    CONSTANT,
    STRING_LITERAL,
    END_OF_LINE,
};

#ifdef	__cplusplus
extern	"C" {
#endif

int	exist_define(const char*);

#ifdef	__cplusplus
}
#endif

#endif	/*	_GLOBAL_H_	*/
