//======================================================
//    if_control.h                                   
//    Process #if #ifdef #ifndef #endif 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_IF_CONTROL_H_
#define	_IF_CONTROL_H_

#define	IF_STATE_NONE		(0)
#define	IF_STATE_OFF		(1)
#define	IF_STATE_ON		(2)
#define	IF_STATE_OFF_ELSE	(3)
#define	IF_STATE_ON_ELSE	(4)

#define	IF_FALSE		(0)
#define	IF_TRUE			(1)

#include <stdio.h>

#ifdef	__cplusplus
extern	"C" {
#endif

void if_push( long state );
long if_pop( void );
long if_get_state( void );
void if_set_state( long state );
long if_set_else( void );
long if_get_bool( void );

#ifdef	__cplusplus
}
#endif

#endif	/* _IF_CONTROL_H_ */
