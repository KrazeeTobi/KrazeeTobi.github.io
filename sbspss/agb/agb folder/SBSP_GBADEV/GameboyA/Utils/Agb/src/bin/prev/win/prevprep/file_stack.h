//======================================================
//    filestack.h                                   
//    Process files and lines that are being processed.
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_FILESTACK_H_
#define	_FILESTACK_H_

#include <stdio.h>

#ifdef	__cplusplus
extern	"C"	{
#endif

FILE*	push_file( const char* );
FILE*	get_file_ptr( void );
const char*	get_file_name( void );
long	get_line( void );
void	set_file_name( const char* );
void	set_line( long );
long	add_line(long add_value);
FILE*	pop_file( void );
void	set_max_file_num( int );

FILE*	set_out_file( const char* );
FILE*	get_out_file_ptr( void );
void	close_out_file( void );
const char* get_out_file_name( void );

#ifdef	__cplusplus
}
#endif

#endif	/* _FILESTACK_H_ */
