//======================================================
//    ndobject.h                                   
//    Definition of object node
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDOBJECT_H__
#define	__NDOBJECT_H__

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
#define	AGBNODE_HEAD_SIZE	(12)
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
class ndObject : public AGBNode
{
protected :
    u8 m_width;
    u8 m_height;
    u8 m_palette_number;
    u8 m_bit_count;
    u8 m_flip;		//  Vertical/horizontal flips
    u8 m_mode;		//  Semitransparent, window
    u16 m_max_time;
    u16 m_max_state;
    float m_offset_x;	//  x direction offset.Relative coordinate for parent node. 
    float m_offset_y;	//  y direction offset.Relative coordinate for parent node.
    std::list<NodeInfo*> m_children_list;
    u16 m_oam[3];

    NodeInfo* m_image_child_ptr;
    NodeInfo* m_anim_node_ptr;

    bool check_width( u8 width );
    bool check_height( u8 height );
    bool check_bit_count( u8 bit_count );

    virtual u32 get_children_size(void);
    virtual u32 get_default_size(void);

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    bool parse_width( TokenList& token_list );
    bool parse_height( TokenList& token_list );
    bool parse_palette_number( TokenList& token_list );
    bool parse_bit_count( TokenList& token_list );
    bool parse_flip( TokenList& token_list );
    bool parse_mode( TokenList& token_list );
    bool parse_max_time( TokenList& token_list );
    bool parse_max_state( TokenList& token_list );
    bool parse_offset( TokenList& token_list );
    bool parse_image( TokenList& token_list );
    bool parse_animation( TokenList& token_list );
    bool parse_child( TokenList& token_list );

    bool output_oam( std::ofstream& out );
    bool output_width( std::ofstream& out );
    bool output_height( std::ofstream& out );
    bool output_palette_number( std::ofstream& out );
    bool output_flip( std::ofstream& out );
    bool output_offset( std::ofstream& out );
    bool output_max_time( std::ofstream& out );
    bool output_max_state( std::ofstream& out );
    bool output_image( std::ofstream& out );
    bool output_animation( std::ofstream& out );
    bool output_children( std::ofstream& out );

    bool outtxt_width( std::ofstream& out );
    bool outtxt_height( std::ofstream& out );
    bool outtxt_palette_number( std::ofstream& out );
    bool outtxt_flip( std::ofstream& out );
    bool outtxt_mode( std::ofstream& out );
    bool outtxt_offset( std::ofstream& out );
    bool outtxt_max_time( std::ofstream& out );
    bool outtxt_max_state( std::ofstream& out );
    bool outtxt_image( std::ofstream& out );
    bool outtxt_animation( std::ofstream& out );
    bool outtxt_children( std::ofstream& out );

    bool out_c_source_oam( std::ofstream& out );
    bool out_c_source_width( std::ofstream& out );
    bool out_c_source_height( std::ofstream& out );
    bool out_c_source_palette_number( std::ofstream& out );
    bool out_c_source_flip( std::ofstream& out );
    bool out_c_source_offset( std::ofstream& out );
    bool out_c_source_max_time( std::ofstream& out );
    bool out_c_source_max_state( std::ofstream& out );
    bool out_c_source_image( std::ofstream& out );
    bool out_c_source_animation( std::ofstream& out );
    bool out_c_source_children( std::ofstream& out );
    bool out_c_source_children_objects( std::ofstream& out );

    bool create_oam( void );
    bool set_value_from_image( void );

public :
    ndObject( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr ) ,
	m_width(0) , m_height(0) , m_palette_number(0) , m_flip(0) ,
	m_offset_x(0), m_offset_y(0), m_mode(0)
	{
	    m_oam[0] = 0;
	    m_oam[1] = 0;
	    m_oam[2] = 0;
	    m_image_child_ptr = new NodeInfo( m_node_magic_ptr ,
					      m_node_manager_ptr );
	    m_anim_node_ptr = new NodeInfo( m_node_magic_ptr ,
					      m_node_manager_ptr );
	}
    virtual ~ndObject();

 //   virtual std::string GetCName(void);
    virtual u32 GetSize(void);

    virtual std::string GetCStructName( void );
    std::string GetCChildName( void );

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
};

__MAGBX__END
//------------------------------------------------------------------------

#endif	//  __NDOBJECT_H__

//
//
