%{
/*======================================================
//    pp.l                                   
//    Lexical analysis and main routine
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================*/

#undef	yywrap

#include <stdio.h>
#include <string.h>
#include "global.h"
#include "token_list.h"
#include "file_stack.h"

static	FILE*	out_file_ptr;
static	int	comment_nest_count = 0;
%}

%x	COMMENT_STYLE_C

%%

"/*"	{ ++comment_nest_count ; BEGIN COMMENT_STYLE_C ;/* Start C style comment. */ }
<COMMENT_STYLE_C>"/*"	{ ++comment_nest_count ; }
<COMMENT_STYLE_C>"*/"	{ --comment_nest_count ; if(!comment_nest_count) BEGIN 0 ; }
<COMMENT_STYLE_C>\n	{ fprintf( get_out_file_ptr() , "\n" ) ; add_line(1) ; }
<COMMENT_STYLE_C>.	;

"//".*	{/* Nothing is done to C++ style comment lines. */}

"."	{ add_list( yytext , PERIOD ) ; }
"\""	{ add_list( yytext , DOUBLE_QT ) ; }

"#"	|
"["	|
"]"	|
"{"	|
"}"	|
"("	|
")"	|
";"	|
":"	|
","	|
"="	|
"+"	|
"-"	|
"*"	|
"/"	|
"?"	|
"!"	|
"&"	|
"|"	|
"\'" |
"$"	|
"%"	|
"~"	|
"^"	|
"<"	|
">"	|
"\\"	{ add_list( yytext , MARK ) ; }

"#define"	{ add_list( yytext , DEFINE ) ; }
"#undef"	{ add_list( yytext , UNDEF ) ; }
"#include"	{ add_list( yytext , INCLUDE ) ; }
"#if"	{ add_list( yytext , IF ) ; }
"#ifdef"	{ add_list( yytext , IFDEF ) ; }
"#ifndef"	{ add_list( yytext , IFNDEF ) ; }
"#else"	{ add_list( yytext , ELSE ) ; }
"#endif"	{ add_list( yytext , ENDIF ) ; }
"#line"	{ add_list( yytext , LINE ) ; }

"unsigned" |
"uchar"	|
"ushort" |
"ulong"	|
"char"	|
"short"	|
"long"	|
"pluchar"	|
"plushort" |
"plulong"	|
"plchar"	|
"plshort"	|
"pllong"	|
"float"	|
"double" |
"plfloat"	|
"pldouble" |
"node" |
"plnode" |
"string" |
"nodenum" |
"symbols" |
"form" |
"header" |
"chunk"		{ add_list( yytext , KEYWORD ) ; }

\"[^ \t\n]*\"	{ add_list( yytext , STRING_LITERAL ); }
[ \t]+		{ add_list( yytext , SPACE ) ; }
[_a-zA-Z][_a-zA-Z0-9]*	{ add_list( yytext , IDENTIFIER ) ; }
[0-9]+		{ add_list( yytext , CONSTANT ) ; }
\n	{ add_line(1); analysis_list(); fprintf( get_out_file_ptr() , "\n") ; }
.	{ add_list( yytext , UNDEFINED ) ; }

%%


int main( int , char** );
int yywrap();
int yyerror( const char* error_msg );
void usage( void );

int main(int argc,char** argv)
{
    int i;
    FILE *fp = NULL;
    int	output_file_arg_index = -1;
    int input_file_arg_index = -1;
    char*	pch;
    for( i=1 ; i<argc ; ++i)
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'o':
		    if( ++i>=argc ) break;
		    output_file_arg_index = i;
		    break;
		case 'D':
		    if( ++i>=argc ){
			usage();
			break;
		    }
		    clear_list();
			/* Process as if #define existed.*/
		    add_list( "#define" , DEFINE );
		    add_list( " " , SPACE );
		    add_list( argv[i] , IDENTIFIER );
		    add_list( " " , SPACE );
		    add_list( "1" , CONSTANT );
		    analysis_list();
		    break;
		case '?':
		case 'h':
		case 'H':
		    usage();
		    break;
		default :
		    printf( "invalid option %s.\n", argv[i] );
		    usage();
		    break;
	    }
	}
	else
	{
	    if( input_file_arg_index != -1 )
	    {
		printf( "too many input files.\n" );
		usage();
	    }
	    input_file_arg_index = i;
	}
    }
    if( -1 == input_file_arg_index )
    {
	printf("not required input file.\n\n");
	usage();
    }
    
    if( -1 == output_file_arg_index )
    {
	if( NULL == set_out_file( "" ) )
	{
	    printf( "stdout cannot open" );
	    exit(1);
	}
    }
    else
    {
	if( NULL == set_out_file( argv[output_file_arg_index] ) )
	{
	    printf( "outputfile \"%s\" cannot open" , argv[output_file_arg_index] );
	    exit(1);
	}
    }

    fp = push_file( argv[input_file_arg_index] );
    if( NULL == fp )
    {
	printf( "inputfile \"%s\" cannot open" , argv[1] );
	exit(1);
    }
    fprintf( get_out_file_ptr() , "\n" ) ;

    yylex();
    fcloseall();
    return	0;
}

int yywrap()
{
    FILE	*fp;
    fp = pop_file();
    if( NULL == fp ) return 1;
    return	0;
}

int yyerror( const char* error_msg )
{
    fprintf( stderr , "%s\t:line %d\t:%s\n" ,
	     get_file_name() , get_line() , error_msg );
    return 0;
}

void output_file_line( void )
{
    fprintf( get_out_file_ptr() ,
	    "\n#line\t%d\t\"%s\"\n" ,
	    get_line() ,
	    get_file_name() );
}

void end_application_by_error( void )
{
    int	ret;
    fcloseall();
    if( 0 < strlen( get_out_file_name() ) ) remove( get_out_file_name() );
    exit( 1 );
}

void usage( void )
{
    printf(
    "agbprep : pre-processor for agb previewer format  ver 0.1\n\n"
    "[usage] agbprep -D define [-D define]... -o filename input_filename\n\n"
    "       -D add define content\n"
    "       -o output file name\n"
    );
    exit( 1 );
}

