//======================================================
//    if_control.cpp                                   
//    Process #if #ifdef #ifndef #endif
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include	<string>
#include	"if_control.h"

typedef struct _IfStack
{
	unsigned long	state;
	_IfStack*	parent_if_stack_ptr;
} IfStack;

static	IfStack		null_if;
static	IfStack*	now_if_ptr = &null_if;

#ifdef	__cplusplus
extern	"C"	{
#endif

//-------------------------------------------------------------------
extern int yyerror( const char* );
extern void output_file_line( void );
void end_application_by_error( void );
//-------------------------------------------------------------------
void if_push( long state )
{
    IfStack*	if_stack_ptr = new IfStack;
    if( NULL == if_stack_ptr )
    {
	printf( "memory overflow.\n" );
	end_application_by_error();
    }
    if_stack_ptr->state = state;
    if_stack_ptr->parent_if_stack_ptr = now_if_ptr;
    now_if_ptr = if_stack_ptr;
}
//-------------------------------------------------------------------
long if_pop( void )
{
    if( now_if_ptr == &null_if ) return -1;
    long return_state = now_if_ptr->state;
    IfStack* old_if_ptr = now_if_ptr;
    now_if_ptr = now_if_ptr->parent_if_stack_ptr;
    delete	old_if_ptr;
    return	if_get_state();
}
//-------------------------------------------------------------------
long if_get_state( void )
{
    if( now_if_ptr == &null_if ) return IF_STATE_NONE;
    return now_if_ptr->state;
}
//-------------------------------------------------------------------
void if_set_state( long state )
{
    if( now_if_ptr != &null_if ) now_if_ptr->state = state;
}
//-------------------------------------------------------------------
long if_set_else( void )
{
    if( now_if_ptr == &null_if )
    {
	yyerror( "use #else without #if." );
	return IF_STATE_NONE;
    }
    switch( now_if_ptr->state )
    {
	case IF_STATE_OFF :
	    now_if_ptr->state = IF_STATE_OFF_ELSE;
	    break;
	case IF_STATE_ON :
	    now_if_ptr->state = IF_STATE_ON_ELSE;
	    break;
	default :
	    yyerror( "too many #else used." );
	    break;
    }
    return	now_if_ptr->state;
}
//-------------------------------------------------------------------
long if_get_bool( void )
{
    IfStack*	check_if_stack_ptr;
    int i=0;
    for( check_if_stack_ptr = now_if_ptr ;
	 check_if_stack_ptr != &null_if ;
	 check_if_stack_ptr = check_if_stack_ptr->parent_if_stack_ptr )
    {
	switch( check_if_stack_ptr->state )
	{
	    case IF_STATE_OFF:
	    case IF_STATE_ON_ELSE:
		return	IF_FALSE;
	    default :
		break;
	}
    }
    return	IF_TRUE;
}
//-------------------------------------------------------------------

#ifdef	__cplusplus
}
#endif

