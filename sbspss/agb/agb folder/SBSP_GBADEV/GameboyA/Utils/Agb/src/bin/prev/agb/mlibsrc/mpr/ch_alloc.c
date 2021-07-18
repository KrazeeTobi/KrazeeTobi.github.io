//======================================================
//    ch_alloc.c                                      
//    Character number management functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agbtypes.h>
#include <util.h>

//--------------------------------------------------------------
#define	CHAL_MAGIC		(0xecdb)
#define	CHAL_NOT_OCCUPIED	(0)
#define	CHAL_OCCUPIED		(1)
//--------------------------------------------------------------
typedef struct _chal_use_info
{
    u16 magic;
    u8  occupied;
    u8  dummy;
    u16 number;
    u16 size;
    struct _chal_use_info* prev;
    struct _chal_use_info* next;
} chal_use_info;
//--------------------------------------------------------------
u16 chal_start_number;
u16 chal_end_number;
chal_use_info* chal_origin_ptr;
//--------------------------------------------------------------
static void chal_list_init( void );
static chal_use_info* chal_list_node_alloc( void );
static void chal_list_node_free( chal_use_info* node_ptr );
//--------------------------------------------------------------
void chalInit(u16 start_number,u16 end_number)
{
    chal_use_info* start_ptr;
    chal_list_init();
    chal_origin_ptr = chal_list_node_alloc();
    start_ptr = chal_list_node_alloc();

	//  Set origin node
    chal_origin_ptr->occupied = CHAL_OCCUPIED;
    chal_origin_ptr->number = 0;
    chal_origin_ptr->size = 0;
    chal_origin_ptr->next = start_ptr;
    chal_origin_ptr->prev = start_ptr;

	//  Set head Node
    start_ptr->occupied = CHAL_NOT_OCCUPIED;
    start_ptr->number = start_number;
    start_ptr->size = end_number - start_number - 1;
    start_ptr->next = chal_origin_ptr;
    start_ptr->prev = chal_origin_ptr;
}
//--------------------------------------------------------------
u16 chalAlloc(u16 size,u8 boundary_bit)
{
    chal_use_info* node_ptr;
    chal_use_info* new_node_ptr;
    u16 boundary_dust;
    u16 and_value;

    and_value = _BitAnd( boundary_bit );
    for( node_ptr = chal_origin_ptr->next ;
	node_ptr != chal_origin_ptr ;
	node_ptr = node_ptr->next )
    {
	if( node_ptr->occupied ) continue;
	boundary_dust = node_ptr->number & and_value;
	if( boundary_dust )
	    boundary_dust = and_value + 1 - boundary_dust;
	if( node_ptr->size < size + boundary_dust ) continue;

	    //  Set aside since the place to take area was found

	    //  Register the leftover section of area's boundary as usable area

	if( boundary_dust )
	{
	    new_node_ptr = chal_list_node_alloc();
	    new_node_ptr->occupied = CHAL_NOT_OCCUPIED;
	    new_node_ptr->number = node_ptr->number;
	    new_node_ptr->size = boundary_dust;
	    new_node_ptr->prev = node_ptr->prev;
	    new_node_ptr->next = node_ptr;
	    node_ptr->number += boundary_dust;
	    node_ptr->size -= boundary_dust;
	    node_ptr->prev = new_node_ptr;
	}

	    //  Enter the garbage left in back in the usable area.

	    //  Actually keep the area

	if( node_ptr->size > size )
	{
	    new_node_ptr = chal_list_node_alloc();
	    new_node_ptr->occupied = CHAL_NOT_OCCUPIED;
	    new_node_ptr->number = node_ptr->number + size;
	    new_node_ptr->size = size - node_ptr->size;
	    new_node_ptr->next = node_ptr->next;
	    new_node_ptr->prev = node_ptr;
	    node_ptr->size = size;
	    node_ptr->next = new_node_ptr;
	}

	node_ptr->occupied = CHAL_OCCUPIED;
	return node_ptr->number;
    }
    return 0xffff;
}
//--------------------------------------------------------------
static void chal_trim_one( chal_use_info* node_ptr )
{
    chal_use_info* tmp_ptr;

    if( node_ptr->occupied == CHAL_OCCUPIED ) return;
    tmp_ptr = node_ptr->next;
    if( tmp_ptr->occupied == CHAL_OCCUPIED ) return;
    node_ptr->size += tmp_ptr->size;
    node_ptr->next = tmp_ptr->next;
    chal_list_node_free( tmp_ptr );
}
//--------------------------------------------------------------
void chalFree(u16 number)
{
    chal_use_info* node_ptr;

    for( node_ptr = chal_origin_ptr->next ;
	node_ptr != chal_origin_ptr ;
	node_ptr = node_ptr->next )
    {
	if( node_ptr->number == number ) break;
    }
    if( node_ptr == chal_origin_ptr ) return;
    node_ptr->occupied = CHAL_NOT_OCCUPIED;
    chal_trim_one( node_ptr );
    chal_trim_one( node_ptr->prev );
}
//--------------------------------------------------------------

//--------------------------------------------------------------
//	Allocation of List Node, etc.
//--------------------------------------------------------------
#define	CHAL_LIST_NODE_MAX_NUM	(128)
//--------------------------------------------------------------
u16 chal_node_count;
chal_use_info* chal_nouse_ptr;
chal_use_info chal_node_buffer[CHAL_LIST_NODE_MAX_NUM];
//--------------------------------------------------------------
static void chal_list_init( void )
{
    chal_node_count = 0;
    chal_nouse_ptr = NULL;
}
//--------------------------------------------------------------
static chal_use_info* chal_list_node_alloc( void )
{
    chal_use_info* ret_ptr;

    if( NULL != chal_nouse_ptr )
    {
	ret_ptr = chal_nouse_ptr;
	chal_nouse_ptr = chal_nouse_ptr->next;
	return ret_ptr;
    }
    if( chal_node_count >= CHAL_LIST_NODE_MAX_NUM ) return NULL;
    ret_ptr = &chal_node_buffer[chal_node_count++];
    ret_ptr->magic = CHAL_MAGIC;
    return ret_ptr;
}
//--------------------------------------------------------------
static void chal_list_node_free( chal_use_info* node_ptr )
{
    if( NULL == node_ptr ) return;
    if( node_ptr->magic != CHAL_MAGIC ) return;

    node_ptr->next = chal_nouse_ptr;
    chal_nouse_ptr = node_ptr;
}
//--------------------------------------------------------------

//
//
//
