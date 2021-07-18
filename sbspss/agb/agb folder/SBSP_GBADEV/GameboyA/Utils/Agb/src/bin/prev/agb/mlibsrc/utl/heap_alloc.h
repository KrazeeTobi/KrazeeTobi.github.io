//======================================================
//    heap_alloc.h                                         
//    Heap allocator
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__HEAP_ALLOC_H__
#define	__HEAP_ALLOC_H__

#include <agbtypes.h>

#undef	NULL
#define	NULL	((void*)0)

//--------------------------------------------------------------
void  heapInit( u32 start_address, u32 end_address );
void  heapCascade( u32 start_address, u32 end_address );
void* heapAlloc( int size );
void  heapFree( void* address );
void  heapFreeWithTrim( void* address );
void  heapTrim( void );
//--------------------------------------------------------------
void  heapsInit( u32 start_address, u32 end_address );
void  heapsCascade( u32 start_address, u32 end_address );
void* heapsAlloc( int size );
void  heapsFree( void* address );
void  heapsFreeWithTrim( void* address );
void  heapsTrim( void );
//--------------------------------------------------------------

#endif	//  __HEAP_ALLOC_H__
//
//
//
//
