//======================================================
//    ndbackground.h                                   
//    Definition of BG node
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDBACKGROUND_H__
#define	__NDBACKGROUND_H__

//------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <agbtypes.h>
#include <util.h>
#include "ex_reference.h"
#include "token_list.h"
#include "nodeinfo.h"
//------------------------------------------------------------------------
#define	NDBG_LOOP	(0)
#define	NDBG_NOLOOP	(1)

#define	NDBG_VALUE_MAP_IMAGE		(0)
#define	NDBG_VALUE_MAP_CHARACTER	(1)
#define	NDBG_VALUE_START		(2)
#define	NDBG_VALUE_LOOP			(3)
#define	NDBG_VALUE_VRAM_SIZE		(4)
#define	NDBG_VALUE_MAX_TIME		(5)
#define	NDBG_VALUE_MAX_STATE		(6)
#define	NDBG_VALUE_CHILDREN		(7)

//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
class ndBackground : public AGBNode
{
protected :
    u16 m_width;
    u16 m_height;
    s16 m_start_x;
    s16 m_start_y;
    u16 m_max_time;
    u16 m_max_state;
    u8  m_loop_x_flag;
    u8  m_loop_y_flag;
    NodeInfo* m_map_image_ptr;
    NodeInfo* m_map_character_ptr;

    std::list<NodeInfo*> m_children_list;

//    virtual bool out_c_source_node_head( std::ofstream& out );
//    virtual bool output_node_head( std::ofstream& out );

    virtual u32 get_children_size(void);
    virtual u32 get_default_size(void);

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    bool parse_map_image( TokenList& token_list );
    bool parse_map_character( TokenList& token_list );
    bool parse_start( TokenList& token_list );
    bool parse_loop( TokenList& token_list );
    bool parse_vram_size( TokenList& token_list );
    bool parse_max_time( TokenList& token_list );
    bool parse_max_state( TokenList& token_list );
    bool parse_children( TokenList& token_list );

    bool output_map_image( std::ofstream& out );
    bool output_map_character( std::ofstream& out );
    bool output_start( std::ofstream& out );
    bool output_loop( std::ofstream& out );
    bool output_vram_size( std::ofstream& out );
    bool output_max_time( std::ofstream& out );
    bool output_max_state( std::ofstream& out );
    bool output_children( std::ofstream& out );

    bool outtxt_map_image( std::ofstream& out );
    bool outtxt_map_character( std::ofstream& out );
    bool outtxt_start( std::ofstream& out );
    bool outtxt_loop( std::ofstream& out );
    bool outtxt_vram_size( std::ofstream& out );
    bool outtxt_max_time( std::ofstream& out );
    bool outtxt_max_state( std::ofstream& out );
    bool outtxt_children( std::ofstream& out );

    bool out_c_source_map_image( std::ofstream& out );
    bool out_c_source_map_character( std::ofstream& out );
    bool out_c_source_start( std::ofstream& out );
    bool out_c_source_loop( std::ofstream& out );
    bool out_c_source_vram_size( std::ofstream& out );
    bool out_c_source_max_time( std::ofstream& out );
    bool out_c_source_max_state( std::ofstream& out );
    bool out_c_source_children( std::ofstream& out );
    bool out_c_source_children_nodes( std::ofstream& out );

    bool set_value_from_image( void );

public :
    ndBackground( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr ) ,
	m_width(256) , m_height(256) , m_start_x(0), m_start_y(0),
	m_loop_x_flag(NDBG_LOOP),m_loop_y_flag(NDBG_LOOP),
	m_max_time(0), m_max_state(0)
	{
	    m_map_image_ptr = new NodeInfo( m_node_magic_ptr ,
					    m_node_manager_ptr );
	    m_map_character_ptr = new NodeInfo( m_node_magic_ptr ,
						m_node_manager_ptr );
	}
    virtual ~ndBackground();

 //   virtual std::string GetCName(void);
    virtual u32 GetSize(void);

    virtual bool GetValue( void* dest, u32 value_id,
			   u32 start, u32 num );

    virtual std::string GetCStructName( void );
    std::string GetCChildName( void );

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
};

__MAGBX__END
//------------------------------------------------------------------------

#endif	//  __NDBACKGROUND_H__

//
//
