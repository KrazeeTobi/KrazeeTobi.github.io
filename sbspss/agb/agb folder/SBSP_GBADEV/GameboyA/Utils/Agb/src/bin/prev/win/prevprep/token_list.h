//======================================================
//    token_list.h                                   
//    Process token. Process every line.
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_TOKEN_LIST_H_
#define	_TOKEN_LIST_H_

#ifdef	__cplusplus
extern	"C" {
#endif

void clear_list( void );
void add_list( const char* word , int type );
void analysis_list( void );

#ifdef	__cplusplus
}
#endif

#endif	/* _TOKEN_LIST_H_ */
