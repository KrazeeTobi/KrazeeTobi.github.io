//======================================================
//    token_list.cpp                                   
//    Process token. Process every line. 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include "token_list.h"
#include "global.h"
#include "token_type.h"
#include "file_stack.h"
#include "if_control.h"

#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------
void output_list( token_list* output_list_ptr , char clear_flag );
void define_mode( void );
void undef_mode( void );
void include_mode( void );
void if_mode( void );
void if_mode_if( void );
void if_mode_ifdef( void );
void if_mode_ifndef( void );
void if_mode_else( void );
void if_mode_endif( void );
void line_mode( void );
long get_number_from_word( std::string word , char clear_flag );
void if_mode_push( long state );
//------------------------------------------------------------
extern token_list*	compare_define(const char* str_ptr);
extern void clear_check(void);
extern int set_check(std::string);
//------------------------------------------------------------
static	token_list	local_list;
static	long		if_bool=IF_TRUE;
//------------------------------------------------------------

#ifdef	__cplusplus
extern	"C"	{
#endif

//------------------------------------------------------------
extern int yyerror( const char* );
extern void	add_define(const char* key,token_list& define_list);
extern void	erase_define(const char* key);
//------------------------------------------------------------
void clear_list( void )
{
    local_list.resize(0);
}
//------------------------------------------------------------
void add_list( const char* word , int type )
{
    token_source	tk_src;
    tk_src.type	= type;
    tk_src.word	= word;
    local_list.push_back( tk_src );
}
//------------------------------------------------------------
void analysis_list( void )
{
    token_iterator	token_it = local_list.begin();
    switch( (*token_it).type )
    {
	case DEFINE:
	    if( if_bool ) define_mode();
	    break;
	case UNDEF:
	    if( if_bool ) undef_mode();
	    break;
	case INCLUDE:
	    if( if_bool ) include_mode();
	    break;
	case IF:
	case IFDEF:
	case IFNDEF:
	case ELSE:
	case ENDIF:
	    if_mode();
	    break;
	case LINE:
	    if( if_bool ) line_mode();
	    break;
	default:
	    if( if_bool ) output_list( &local_list , 1 );
	    break;
    }
    clear_list();
}
//------------------------------------------------------------

#ifdef	__cplusplus
}
#endif

//------------------------------------------------------------
void output_list( token_list* output_list_ptr , char clear_flag )
{
    if( NULL == output_list_ptr ) return;
    token_iterator	output_it;
    token_list* def_list_ptr;

    if( clear_flag ) clear_check();

    for( output_it = output_list_ptr->begin() ;
	 output_it != output_list_ptr->end() ;
	 ++output_it )
    {
	if( IDENTIFIER == (*output_it).type )
	{
	    def_list_ptr = compare_define( (*output_it).word.c_str() );
	    if( NULL != def_list_ptr )
	    {
		if( set_check( (*output_it).word ) )
		{
		    output_list( def_list_ptr , 0 );
		    continue;
		}
	    }
	}
	fprintf( get_out_file_ptr() , (*output_it).word.c_str() ) ;
	clear_check();
    }
}
//------------------------------------------------------------
void define_mode( void )
{
    token_iterator	define_it,key_it;
    for( define_it = local_list.begin() ;
	 define_it != local_list.end() ;
	 ++define_it )
    {
	if( IDENTIFIER == (*define_it).type ) break;
    }
    if( local_list.end() == define_it )
    {
	yyerror( "define identifier not exist" );
    }
    key_it = define_it;
    ++define_it;
    for( ; define_it != local_list.end() ; ++define_it )
    {
	if( SPACE != (*define_it).type ) break;
    }
    token_list define_token_list;
    for( ; define_it != local_list.end() ; ++define_it )
    {
	define_token_list.push_back( *define_it );
    }
    add_define( (*key_it).word.c_str() , define_token_list );
}
//------------------------------------------------------------
void undef_mode( void )
{
    token_iterator	define_it;
    for( define_it = local_list.begin() ;
	 define_it != local_list.end() ;
	 ++define_it )
    {
	if( IDENTIFIER == (*define_it).type ) break;
    }
    if( local_list.end() == define_it )
    {
	yyerror( "undef identifier not exist" );
    }
    erase_define( (*define_it).word.c_str() );
}
//------------------------------------------------------------
void include_mode( void )
{
    FILE*	new_fp;
    token_iterator	include_it;
    for( include_it = local_list.begin() ;
	 include_it != local_list.end() ;
	 ++include_it )
    {
	if( STRING_LITERAL == (*include_it).type ) break;
    }
    if( local_list.end() == include_it )
    {
	yyerror( "include file not appointed" );
    }

    std::string	file_name;
    file_name = (*include_it).word;
    std::string::iterator	fname_it = file_name.begin();
    file_name.erase( fname_it );
    fname_it = file_name.end();
    file_name.erase( --fname_it );

    new_fp = push_file( file_name.c_str() );
    if( NULL == new_fp )
    {
	yyerror( "file cannot open.\n" );
    }
}
//------------------------------------------------------------
void if_mode( void )
{
    token_iterator	if_it = local_list.begin();
    switch( (*if_it).type )
    {
	case IF:
	    if_mode_if();
	    break;
	case IFDEF:
	    if_mode_ifdef();
	    break;
	case IFNDEF:
	    if_mode_ifndef();
	    break;
	case ELSE:
	    if_mode_else();
	    break;
	case ENDIF:
	    if_mode_endif();
	    break;
	default :
	    break;
    }
    if_bool = if_get_bool();
}
//------------------------------------------------------------
void if_mode_if( void )
{
    token_iterator	if_it = local_list.begin();
    ++if_it;
    for( ; if_it != local_list.end() ; ++if_it )
    {
	if( (*if_it).type != SPACE ) break;
    }
    if( local_list.end() == if_it )
    {
	yyerror( "#if has no param." );
	return;
    }
    if( CONSTANT == (*if_it).type )
    {
	if_mode_push( atoi( (*if_it).word.c_str() ) );
	return;
    }
    if( IDENTIFIER == (*if_it).type )
    {
	if_mode_push( get_number_from_word( (*if_it).word , 1 ) );
	return;
    }
    yyerror( "no number set." );
}
//------------------------------------------------------------
void if_mode_ifdef( void )
{
    token_iterator	ifdef_it = local_list.begin();
    ++ifdef_it;
    for( ; ifdef_it != local_list.end() ; ++ifdef_it )
    {
	if( IDENTIFIER == (*ifdef_it).type ) break;
    }
    if( local_list.end() == ifdef_it )
    {
	yyerror( "#ifdef has no identifier." );
	return;
    }
    if_mode_push( exist_define( (*ifdef_it).word.c_str() ) );
}
//------------------------------------------------------------
void if_mode_ifndef( void )
{
    token_iterator	ifdef_it = local_list.begin();
    ++ifdef_it;
    for( ; ifdef_it != local_list.end() ; ++ifdef_it )
    {
	if( IDENTIFIER == (*ifdef_it).type ) break;
    }
    if( local_list.end() == ifdef_it )
    {
	yyerror( "no identifier." );
	return;
    }
    if_mode_push( !exist_define( (*ifdef_it).word.c_str() ) );
}
//------------------------------------------------------------
void if_mode_else( void )
{
    if_set_else();
}
//------------------------------------------------------------
void if_mode_endif( void )
{
    if_pop();
}
//------------------------------------------------------------
void line_mode( void )
{
    token_iterator	list_it;
    for( list_it = local_list.begin() ;
	 list_it != local_list.end() ;
	 ++list_it )
    {
	if( CONSTANT == (*list_it).type ) break;
    }
    if( local_list.end() == list_it )
    {
	yyerror( "#line not exist number" );
    }
    long	l_line = (long)atoi((*list_it).word.c_str() );
    std::string	file_name;
    for( ; list_it != local_list.end() ; ++list_it )
    {
	if( STRING_LITERAL == (*list_it).type ) break;
    }
    if( local_list.end() == list_it )
    {
	yyerror( "#line not exist file name" );
    }
    file_name = (*list_it).word;
    std::string::iterator	fname_it( file_name.begin() );
    file_name.erase( fname_it );
    fname_it = file_name.end();
    file_name.erase( --fname_it );
    set_file_name( file_name.c_str() );
    set_line( l_line );
}
//------------------------------------------------------------
long get_number_from_word( std::string word , char clear_flag )
{
    if( clear_flag ) clear_check();
    token_list*	def_list_ptr = compare_define( word.c_str() );
    if( NULL == def_list_ptr ) return 0;
    token_iterator	token_it = def_list_ptr->begin();
    if( def_list_ptr->end() == token_it ) return 0;
    if( (*token_it).type == CONSTANT )
	    return (long)atoi( (*token_it).word.c_str() );
    if( (*token_it).type == IDENTIFIER )
    {
	if( set_check( (*token_it).word ) )
	    return get_number_from_word( (*token_it).word , 0 );
    }
    return 0;
}
//------------------------------------------------------------
void if_mode_push( long state )
{
    if( state ) if_push( IF_STATE_ON );
    else	if_push( IF_STATE_OFF );
}
//------------------------------------------------------------

