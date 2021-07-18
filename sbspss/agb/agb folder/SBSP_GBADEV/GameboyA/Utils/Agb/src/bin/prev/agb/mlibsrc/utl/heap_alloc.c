//======================================================
//    heap_alloc.c                                         
//    Heap allocator
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================


#include <agbtypes.h>
#include "heap_alloc.h"

//--------------------------------------------------------------
//
//
//
//--------------------------------------------------------------
#define	HEAP_NOT_OCCUPIED	(0)
#define	HEAP_OCCUPIED		(1)
#define	HEAP_CONTINUOUS		(0)
#define	HEAP_NO_CONTINUOUS	(1)
#define	HEAP_MEM_MAGIC		(0xabcd)
#define	HEAP_MEM_ORIGIN_MAGIC	(0x1234)
#define	HEAP_MEM_BROKEN_MAGIC	(0xedcb)
//--------------------------------------------------------------
typedef struct _heap_mem_info
{
    u16 magic;
    u8  occupied;
    u8  continuous;
    u32 size;
    struct _heap_mem_info *prev;
    struct _heap_mem_info *next;
} heap_mem_info;
//--------------------------------------------------------------
u32 heap_start;
//--------------------------------------------------------------
static void heap_trim_one( heap_mem_info* info_ptr );
static void* heap_alloc( int size );
//--------------------------------------------------------------
void heapInit( u32 start_address, u32 end_address )
{
    heap_mem_info *info_ptr;
    heap_mem_info *origin_info_ptr;

    heap_start = (start_address + 3) & -4;
    origin_info_ptr = (heap_mem_info *)heap_start;
    info_ptr = (heap_mem_info *)(heap_start + sizeof(heap_mem_info) );

    origin_info_ptr->magic = HEAP_MEM_ORIGIN_MAGIC;
    info_ptr->magic        = HEAP_MEM_MAGIC;
    info_ptr->continuous = origin_info_ptr->continuous = HEAP_NO_CONTINUOUS;
    info_ptr->occupied         = HEAP_NOT_OCCUPIED;
    origin_info_ptr->occupied  = HEAP_OCCUPIED;

    origin_info_ptr->size = end_address - heap_start;
    info_ptr->size = origin_info_ptr->size - 2*sizeof(heap_mem_info);
    origin_info_ptr->next = origin_info_ptr->prev = info_ptr;
    info_ptr->next = info_ptr->prev = origin_info_ptr;
}
//--------------------------------------------------------------
void  heapCascade( u32 start_address, u32 end_address )
{
    heap_mem_info *origin_info_ptr;
    heap_mem_info *new_info_ptr;

    origin_info_ptr = (heap_mem_info*)heap_start;
    if( origin_info_ptr->magic != HEAP_MEM_MAGIC ) return;

    new_info_ptr = (heap_mem_info *)(u32)((start_address + 3)&-4);
    new_info_ptr->magic      = HEAP_MEM_MAGIC;
    new_info_ptr->occupied   = HEAP_NOT_OCCUPIED;
    new_info_ptr->continuous = HEAP_NO_CONTINUOUS;
    new_info_ptr->size = end_address - (u32)(new_info_ptr)
			- sizeof(heap_mem_info);
    new_info_ptr->next = origin_info_ptr;
    new_info_ptr->prev = origin_info_ptr->prev;
    origin_info_ptr->prev = new_info_ptr;
}
//--------------------------------------------------------------
static void *heap_alloc( int size )
{
    heap_mem_info *origin_info_ptr;
    heap_mem_info *info_ptr;
    heap_mem_info *new_info_ptr;
    u32 last_size;
    u32 alloc_size;

    origin_info_ptr = (heap_mem_info*)heap_start;
    if( origin_info_ptr->magic != HEAP_MEM_MAGIC ) return NULL;

    alloc_size = (u32)((size + 3)&-4);
    if( 0 == alloc_size ) return NULL;

    for( info_ptr  = origin_info_ptr->next ;
	 info_ptr != origin_info_ptr ;
	 info_ptr  = info_ptr->next )
    {
	if( info_ptr->occupied == HEAP_OCCUPIED ) continue;
	if( info_ptr->size < size ) continue;
	info_ptr->occupied = HEAP_OCCUPIED;
	last_size = (u32)(info_ptr->size - alloc_size);
	info_ptr->size = size;
	if( last_size > sizeof(heap_mem_info) )
	{
	    new_info_ptr = (heap_mem_info*)(u32)
			   ((u32)info_ptr + sizeof(heap_mem_info) +
			   alloc_size );
	    new_info_ptr->magic = HEAP_MEM_MAGIC;
	    new_info_ptr->occupied = HEAP_NOT_OCCUPIED;
	    new_info_ptr->continuous = info_ptr->continuous;
	    new_info_ptr->size = last_size - sizeof( heap_mem_info );
	    new_info_ptr->next = info_ptr->next;
	    new_info_ptr->prev = info_ptr;
	    info_ptr->next->prev = new_info_ptr;
	    info_ptr->next = new_info_ptr;
	    info_ptr->continuous = HEAP_CONTINUOUS;
	}
	return (void*)((u32)info_ptr + sizeof(heap_mem_info));
    }
    return NULL;
}
//--------------------------------------------------------------
void* heapAlloc( int size )
{
    void* ret_ptr;
    ret_ptr = heap_alloc( size );
    if( NULL != ret_ptr ) return ret_ptr;
    heapTrim();
    return heap_alloc( size );
}
//--------------------------------------------------------------
void heapFree( void* address )
{
    heap_mem_info* info_ptr;

    info_ptr = (heap_mem_info*)(u32)((u32)address) - (sizeof(heap_mem_info)-4);
    if( info_ptr->magic != HEAP_MEM_MAGIC ) return;

    info_ptr->occupied = HEAP_NOT_OCCUPIED;
}
//--------------------------------------------------------------
void heapFreeWithTrim( void* address )
{
    heap_mem_info* info_ptr;

    info_ptr = (heap_mem_info*)(u32)((u32)address) - (sizeof(heap_mem_info)-4);
    if( info_ptr->magic != HEAP_MEM_MAGIC ) return;

    info_ptr->occupied = HEAP_NOT_OCCUPIED;

    heap_trim_one( info_ptr );
    heap_trim_one( info_ptr->prev );
}
//--------------------------------------------------------------
void heapTrim( void )
{
    heap_mem_info *origin_info_ptr;
    heap_mem_info *info_ptr;

    origin_info_ptr = (heap_mem_info*)heap_start;
    if( origin_info_ptr->magic != HEAP_MEM_MAGIC ) return;

    for( info_ptr  = origin_info_ptr->next ;
	 info_ptr != origin_info_ptr ;
	 info_ptr  = info_ptr->next )
    {
	if( info_ptr->occupied = HEAP_NOT_OCCUPIED )
	    heap_trim_one( info_ptr );
    }
}
//--------------------------------------------------------------
static void heap_trim_one( heap_mem_info* info_ptr )
{
    heap_mem_info* tmp_ptr;
    if( info_ptr->occupied == HEAP_OCCUPIED ) return;
    if( info_ptr->continuous == HEAP_CONTINUOUS )
    {
	tmp_ptr = info_ptr->next;
	if( tmp_ptr->occupied == HEAP_NOT_OCCUPIED )
	{
	    tmp_ptr->magic = HEAP_MEM_BROKEN_MAGIC;
	    info_ptr->size += tmp_ptr->size + sizeof( heap_mem_info );
	    info_ptr->continuous = tmp_ptr->continuous;
	    info_ptr->next = tmp_ptr->next;
	    tmp_ptr->next->prev = info_ptr;
	}
    }
}
//--------------------------------------------------------------
//
//
//
//--------------------------------------------------------------
#define	HEAPS_NOT_OCCUPIED	(0)
#define	HEAPS_OCCUPIED		(1)
#define	HEAPS_CONTINUOUS	(0)
#define	HEAPS_NO_CONTINUOUS	(2)
#define	HEAPS_MEM_MAGIC		(0xbc)
#define	HEAPS_MEM_BROKEN_MAGIC	(0xfe)
//--------------------------------------------------------------
typedef struct _heaps_mem_info
{
    u8  magic;		//  To confirm whether heaps are used or not
    u8  flag;		//  Condition of memory managed by this structure
    u16 qsize;		//  One quarter (1/4) of the usable memory
    struct _heaps_mem_info *next;	//  Pointer to the next structure
} heaps_mem_info;
//--------------------------------------------------------------
//  Starting coordinate of heaps
//
u32 heaps_start;
//--------------------------------------------------------------
static void* heaps_alloc( int size );
static void heaps_trim_one( heaps_mem_info* info_ptr );
//--------------------------------------------------------------
void heapsInit( u32 start_address, u32 end_address )
{
    heaps_mem_info *info_ptr;
    heaps_mem_info *tmp_ptr;

    heaps_start = (start_address + 3) & -4;
    info_ptr = (heaps_mem_info *)heaps_start;

    info_ptr->magic = HEAPS_MEM_MAGIC;
    info_ptr->flag  = HEAPS_NO_CONTINUOUS | HEAPS_NOT_OCCUPIED;
    info_ptr->qsize  = (u16)(u32)((end_address - heaps_start
				 - sizeof(heaps_mem_info))>>2);
    info_ptr->next = NULL;
}
//--------------------------------------------------------------
void  heapsCascade( u32 start_address, u32 end_address )
{
    heaps_mem_info *info_ptr;
    heaps_mem_info *new_info_ptr;
    u32 true_start;

    info_ptr = (heaps_mem_info*)heap_start;
    if( info_ptr->magic != HEAPS_MEM_MAGIC ) return;

    while( info_ptr->next != NULL ) info_ptr = info_ptr->next;

    new_info_ptr = (heaps_mem_info *)(u32)((start_address + 3)&-4);
    new_info_ptr->magic = HEAPS_MEM_MAGIC;
    new_info_ptr->flag  = HEAPS_NOT_OCCUPIED | HEAPS_NO_CONTINUOUS;
    new_info_ptr->qsize = (u16)(u32)((end_address - (u32)new_info_ptr
				 - sizeof(heaps_mem_info))>>2);
    new_info_ptr->next = NULL;
    info_ptr->next = new_info_ptr;
}
//--------------------------------------------------------------
static void* heaps_alloc( int size )
{
    heaps_mem_info *info_ptr;
    heaps_mem_info *new_info_ptr;
    u16 alloc_qsize;
    u16 last_qsize;

    info_ptr = (heaps_mem_info*)heaps_start;
    if( info_ptr->magic != HEAPS_MEM_MAGIC ) return NULL;
    alloc_qsize = (u16)(u32)((size + 3) >> 2);
    if( 0 == alloc_qsize ) return NULL;

    for( ; info_ptr != NULL ; info_ptr = info_ptr->next )
    {
	if( info_ptr->flag & HEAPS_OCCUPIED ) continue;
	if( info_ptr->qsize < alloc_qsize ) continue;
	last_qsize = info_ptr->qsize - alloc_qsize;
	if( last_qsize > (sizeof(heaps_mem_info)>>2) )
	{
	    new_info_ptr = (heaps_mem_info*)(u32)
			   ((u32)info_ptr + sizeof(heaps_mem_info) +
			   (u32)(alloc_qsize<<2) );
	    new_info_ptr->magic = HEAPS_MEM_MAGIC;
	    new_info_ptr->flag = HEAPS_NOT_OCCUPIED;
	    new_info_ptr->flag = info_ptr->flag;
	    info_ptr->flag &= ~HEAPS_NO_CONTINUOUS;
	    new_info_ptr->qsize = last_qsize - (sizeof(heaps_mem_info)>>2);
	    new_info_ptr->next = info_ptr->next;
	    info_ptr->next = new_info_ptr;
	}
	info_ptr->flag |= HEAPS_OCCUPIED;
	return (void*)(((u32)info_ptr)+sizeof(heaps_mem_info));
    }
    return NULL;
}
//--------------------------------------------------------------
void* heapsAlloc( int size )
{
    void* ret_ptr;

    ret_ptr = heaps_alloc( size );
    if( NULL != ret_ptr ) return ret_ptr;

    heapsTrim();
    return heaps_alloc( size );
}
//--------------------------------------------------------------
void heapsFree( void* address )
{
    heaps_mem_info* info_ptr;
    heaps_mem_info* tmp_ptr;

    info_ptr = (heaps_mem_info*)((u32)address) - (sizeof(heaps_mem_info)-4);
    if( info_ptr->magic != HEAPS_MEM_MAGIC ) return;

    info_ptr->flag &= ~HEAPS_OCCUPIED;
}
//--------------------------------------------------------------
void heapsFreeWithTrim( void* address )
{
    heaps_mem_info* info_ptr;
    heaps_mem_info* tmp_ptr;

    info_ptr = (heaps_mem_info*)((u32)address) - (sizeof(heaps_mem_info)-4);
    if( info_ptr->magic != HEAPS_MEM_MAGIC ) return;

    info_ptr->flag &= ~HEAPS_OCCUPIED;
    heaps_trim_one( info_ptr );
}
//--------------------------------------------------------------
void heapsTrim( void )
{
    heaps_mem_info *info_ptr;

    for( info_ptr = (heaps_mem_info*)heaps_start ;
	info_ptr != NULL ; info_ptr = info_ptr->next )
    {
	if( info_ptr->flag & HEAPS_NOT_OCCUPIED )
	    heaps_trim_one( info_ptr );
    }
}
//--------------------------------------------------------------
static void heaps_trim_one( heaps_mem_info* info_ptr )
{
    heaps_mem_info* tmp_ptr;
    if( info_ptr->flag & HEAPS_OCCUPIED ) return;
    if( info_ptr->flag & HEAPS_CONTINUOUS )
    {
	tmp_ptr = info_ptr->next;
	if( NULL == tmp_ptr ) return;
	if( tmp_ptr->flag & HEAPS_NOT_OCCUPIED )
	{
	    tmp_ptr->magic = HEAPS_MEM_BROKEN_MAGIC;
	    info_ptr->qsize += tmp_ptr->qsize + (sizeof(heaps_mem_info)>>2);
	    info_ptr->flag = tmp_ptr->flag;
	    info_ptr->next = tmp_ptr->next;
	}
    }
}
//--------------------------------------------------------------

//
//
//
//
