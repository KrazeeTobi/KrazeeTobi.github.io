//======================================================
//    filestack.cpp                                   
//    Process files and lines that are being processed.
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include	<string>
#include	"file_stack.h"

#define	DEFAULT_MAX_OPENED_FILE_NUM	16

struct	yy_buffer_state;

typedef struct _FileStack
{
    std::string	file_name;
    FILE*	file_ptr;
    yy_buffer_state*	yy_buffer_ptr;
    long	line;
    _FileStack*	parent_file_stack_ptr;
} FileStack;

static	std::string	now_file_name;
static	long	now_line;

static	FileStack	null_file;
static	FileStack*	now_file_ptr = &null_file;

static	int	max_opened_file_num = DEFAULT_MAX_OPENED_FILE_NUM;
static	int	opened_file_num = 0;

#ifdef	__cplusplus
extern	"C"	{
#endif

yy_buffer_state* pp_create_buffer_state( FILE* fp );

//-------------------------------------------------------------------
extern int yyerror( const char* );
extern void output_file_line( void );
extern void yy_switch_to_buffer( yy_buffer_state* );
extern yy_buffer_state* yy_create_buffer(FILE*,int);
extern void yy_delete_buffer( yy_buffer_state* );
void end_application_by_error( void );
//-------------------------------------------------------------------
FILE*	push_file( const char* file_name )
{
    yy_buffer_state*	yy_buffer_ptr;
    FileStack*	file_stack_ptr = new FileStack;
    if( NULL == file_stack_ptr )
    {
	printf( "memory overflow.\n" );
	end_application_by_error();
    }
    file_stack_ptr->file_ptr = fopen( file_name , "r" );
    if( NULL == file_stack_ptr->file_ptr )
    {
	delete	file_stack_ptr;
	yyerror( "file cannot open." );
	end_application_by_error();
    }
    if( ++opened_file_num > max_opened_file_num )
    {
	yyerror( "too many include files." );
	end_application_by_error();
    }
    file_stack_ptr->file_name = file_name;
    file_stack_ptr->line = 0;
    yy_buffer_ptr = pp_create_buffer_state(file_stack_ptr->file_ptr);
    if( NULL == yy_buffer_ptr )
    {
	delete	file_stack_ptr;
	yyerror( "memory overflow." );
	end_application_by_error();
	exit(1);
    }
    file_stack_ptr->yy_buffer_ptr = yy_buffer_ptr;
    file_stack_ptr->parent_file_stack_ptr = now_file_ptr;
    now_file_ptr = file_stack_ptr;
    set_file_name( file_name );
    set_line( 0 );
    output_file_line();
    return get_file_ptr();
}
//-------------------------------------------------------------------
yy_buffer_state* pp_create_buffer_state( FILE* fp )
{
    yy_buffer_state*	pp_new_buffer = yy_create_buffer( fp , 16384 );
    yy_switch_to_buffer( pp_new_buffer );
    return pp_new_buffer;
}
//-------------------------------------------------------------------
FILE*	get_file_ptr()
{
    return	(now_file_ptr == &null_file) ?
	    NULL : now_file_ptr->file_ptr ;
}
//-------------------------------------------------------------------
const char* get_file_name()
{
    return	(now_file_ptr == &null_file) ?
	    NULL : now_file_name.c_str() ;
}
//-------------------------------------------------------------------
long	get_line()
{
    return	(now_file_ptr == &null_file) ?
	    -1 : now_line ;
}
//-------------------------------------------------------------------
long	add_line( long add_value )
{
    now_file_ptr->line += add_value;
    now_line += add_value;
    return	get_line();
}
//-------------------------------------------------------------------
void	set_file_name(const char* new_file_name)
{
    now_file_name = new_file_name;
}
//-------------------------------------------------------------------
void	set_line( long new_line )
{
    now_line = new_line;
}
//-------------------------------------------------------------------
FILE*	pop_file()
{
    if( now_file_ptr == &null_file ) return NULL;
    fclose( now_file_ptr->file_ptr );
    FileStack*	old_file_ptr = now_file_ptr;
    now_file_ptr = now_file_ptr->parent_file_stack_ptr;
    yy_delete_buffer( old_file_ptr->yy_buffer_ptr );
    delete	old_file_ptr;
    FILE*	ret_fp = get_file_ptr();
    if( NULL != ret_fp )
    {
	set_file_name( now_file_ptr->file_name.c_str() );
	set_line( now_file_ptr->line );
	output_file_line();
	yy_switch_to_buffer( now_file_ptr->yy_buffer_ptr );
    }
    --opened_file_num;
    return ret_fp;
}
//-------------------------------------------------------------------
void	set_max_file_num( int num )
{
    if( num <= 1 || num >= 32 ) return;
    max_opened_file_num = num;
}
//-------------------------------------------------------------------
//		Output file related
//-------------------------------------------------------------------
static	std::string	out_file_name;
static	FILE*	out_file_ptr = NULL;
//-------------------------------------------------------------------
FILE*	set_out_file( const char* file_name )
{
    if( out_file_ptr ) close_out_file();
    if( 0 < strlen( file_name ) ) out_file_ptr = fopen( file_name , "w" );
    else	out_file_ptr = stdout;
    out_file_name = file_name;
    return	out_file_ptr;
}
//-------------------------------------------------------------------
FILE*	get_out_file_ptr( void )
{
    return	out_file_ptr ;
}
//-------------------------------------------------------------------
void	close_out_file( void )
{
    if( NULL != out_file_ptr ) fclose( out_file_ptr );
    out_file_ptr = NULL;
}
//-------------------------------------------------------------------
const char*	get_out_file_name( void )
{
    return	out_file_name.c_str();
}
//-------------------------------------------------------------------

#ifdef	__cplusplus
}
#endif

