//======================================================
//    c_access.h                                       
//    Functions to access each class from C language
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__C_ACCESS_H__
#define	__C_ACCESS_H__

#include "token_type.h"

#ifdef	__cplusplus
extern "C" {
#endif
//-------------------------------------------------------------
int  InitApp( const char* input_file_name );
void DeleteApp( void );
int  AddToken( unsigned long token_id , const char* token_str );
void AddErrorLine( unsigned long );
void SetInputPath( const char* input_name );
void SetErrorLine( unsigned long line );
void SetErrorFileName( const char* file_name );
void OutputError( const char* error_message );
int  OutDepend( const char* file_name );
int  LoadFile( void );
int  OutputNode( const char* file_name );
int  OutputCSource( const char* file_name );
int  OutputBinary( const char* file_name );
//-------------------------------------------------------------
#ifdef	__cplusplus
}
#endif

#endif	//  __C_ACCESS_H__

//
//
