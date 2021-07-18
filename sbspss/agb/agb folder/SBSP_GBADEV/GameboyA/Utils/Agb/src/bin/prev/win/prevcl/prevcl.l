%{
/*======================================================
//    prevcl.l                                   
//    Lexical analysis routine and main routine
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================*/
#undef	yywrap

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "token_type.h"
#include "c_access.h"

static	int	comment_nest_count = 0;
static	int	error_flag = 0;
%}

%x	COMMENT_STYLE_C

%%

"/*"	{ ++comment_nest_count ; BEGIN COMMENT_STYLE_C ; /* comment */ }
<COMMENT_STYLE_C>"/*"	{ ++comment_nest_count; }
<COMMENT_STYLE_C>"*/"	{ if( !(--comment_nest_count) ) BEGIN 0;}
<COMMENT_STYLE_C>\n	{ AddErrorLine(1); }
<COMMENT_STYLE_C>.	;

"//".*	{/* Nothing is done to C++ style comment lines.*/}

"{"	{ error_flag = AddToken( PARENTHISIS_OPEN , yytext ) ; }
"}"	{ error_flag = AddToken( PARENTHISIS_CLOSE, yytext ) ; }

";"	{ error_flag = AddToken( SEMI_COLON, yytext ) ; }

"#line"	{ error_flag = AddToken( LINE, yytext ) ; }

\"[^ \t\n]*\"	{ error_flag = AddToken( STRING_LITERAL, yytext ); }
[ \t]+		{ /* space and tab */ }
[_a-zA-Z][_a-zA-Z0-9]*	{ error_flag = AddToken( IDENTIFIER, yytext ) ; }
-?(([0-9]+)|([0-9]*\.[0-9]+))	{ error_flag = AddToken( CONSTANT, yytext ) ; }
\n	{ AddErrorLine(1); }
.	{ /* AddToken( UNDEFINED, lexer_ptr->YYText() ) ;*/ }

%%


//----------------------------------------------------------------------
int main( int , char** );
int yywrap();
void usage( void );
//----------------------------------------------------------------------
int main(int argc,char** argv)
{
    int i;
    int	output_file_arg_index = -1;
    int input_file_arg_index = -1;
    char depend_flag = 0;
    int ret_status;
    FILE *fp;
    struct yy_buffer_state *pp_new_buffer;
    for( i=1 ; i<argc ; ++i)
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'd' :
		    depend_flag = 1;
		    break;
		case 'o':
		    if( ++i>=argc ) break;
		    output_file_arg_index = i;
		    break;
		case 'D':
		    break;
		case '?':
		case 'h':
		case 'H':
		    usage();
		    break;
		default :
		    printf( "invalid option %s\n", argv[i] );
		    usage();
		    break;
	    }
	}
	else
	{
	    if( input_file_arg_index != -1 )
	    {
		fprintf( stderr, "too many input files.\n" );
		usage();
	    }
	    input_file_arg_index = i;
	}
    }

    if( -1 == output_file_arg_index )
    {
	fprintf( stderr, "not required output file.\n\n" );
	usage();
    }
    if( -1 == input_file_arg_index )
    {
	fp = stdin;
	if( 0 != InitApp( NULL ) )
	{
	    exit( 1 );
	}
    }
    else
    {
	fp = fopen( argv[input_file_arg_index] , "r" );
	if( 0 != InitApp( argv[input_file_arg_index] ) )
	{
	    exit( 1 );
	}
    }
    if( NULL == fp )
    {
	fprintf( stderr,"\"%d\"%s\"\n"
		"File could not be opened.\n" ,
		argv[input_file_arg_index] );
	exit(1);
    }

    pp_new_buffer = yy_create_buffer( fp , 16384 );
    if( NULL == pp_new_buffer )
    {
	fprintf( stderr,"Not enough memory\n");
	exit( 1 );
    }
    yy_switch_to_buffer( pp_new_buffer );
    yylex();
    if( error_flag )
    {
	fprintf( stderr,"An error occurred during script analysis.\n");
	exit( 1 );
    }

	//  Output

    if( depend_flag )
    {
	ret_status = OutDepend( argv[output_file_arg_index] );
    }
    else
    {
	ret_status = LoadFile();
	if( 0 == ret_status )
	{
	    ret_status = OutputNode(argv[output_file_arg_index] );
	}
    }
    DeleteApp();
    if( ret_status != 0 ) exit( 1 );
    return 0;
}
//----------------------------------------------------------------------
int yywrap()
{
    return 1;
}
//----------------------------------------------------------------------
void usage( void )
{
    printf("prevcl : AGB Previewer compiler ver 0.1\n\n"
           "[usage] prevcl -o filename input_filename\n\n"
            "       -o output file name\n" );
    exit( 1 );
}
//----------------------------------------------------------------------

