//======================================================
//    numlist.h                                           
//    List for removing elements from an array.
//    The number of elements in array must be less
//    than 255.
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__NUMLIST_H__
#define	__NUMLIST_H__

#include <agb.h>

#define	_NL_INVALID_NUMBER	(0xff)

#define	_NUMLISTNAME( type )	type##_nlist;

#define	_NUMLIST( type )	\
struct	\
{	\
    u8  head;	\
    u8  tail;	\
    u8  count;	\
    u8  max;	\
    numListNode *node_ptr;	\
    type	*data_array;	\
}

typedef struct
{
    u8  data;
    u8  next;
} numListNode;
//----------------------------------------------------------------------
typedef u8 nl_iterator;
//----------------------------------------------------------------------
#define	_nlClear( nl_ptr )	\
{	\
    ((*(nl_ptr)).head)=((*(nl_ptr)).tail)=(_NL_INVALID_NUMBER);	\
    ((*(nl_ptr)).count) = 0;	\
}
#define	_nlBegin( nl_ptr ) ((*(nl_ptr)).head)
#define	_nlNext( nln_ptr ) ((*(nln_ptr)).next)
#define	_nlData( nln_ptr ) ((*(nln_ptr)).data)
#define	_nlEnd( nl_ptr ) (_NL_INVALID_NUMBER)
#define	_nlPush( nln_ptr, num )
//----------------------------------------------------------------------

#endif	//  __NUMLIST_H__

//
//
