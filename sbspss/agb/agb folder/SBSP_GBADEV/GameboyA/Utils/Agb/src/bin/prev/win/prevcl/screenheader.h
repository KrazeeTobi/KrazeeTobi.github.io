//======================================================
//    screenheader.h                                   
//    Definition of header chunk 
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__SCREENHEADER_H__
#define	__SCREENHEADER_H__

#include <iostream>
#include <fstream>
#include <list>
#include <agbtypes.h>
#include <color.h>

#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "nodeinfo.h"

//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
class ScreenHeader : public AGBNode
{
protected :
    u16 m_disp_cnt;
    u16 m_bg0_cnt;
    u16 m_bg1_cnt;
    u16 m_bg2_cnt;
    u16 m_bg3_cnt;
    u8  m_priority[4];
    u8  m_bg_mode;
    Color m_bg_color;

    NodeInfo m_object_palette;
    NodeInfo m_bg_palette;

    std::list<NodeInfo*> m_object_list;
    std::list<NodeInfo*> m_bg_list;

    NodeInfo* m_info_ptr[4];

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    bool parse_objects( TokenList& token_list );
    bool parse_object_palette( TokenList& token_list );
    bool parse_bgs( TokenList& token_list );
    bool parse_bg_palette( TokenList& token_list );
    bool parse_bg_color( TokenList& token_list );

    bool set_bg_cnt( u16& cnt, u8 bg_number );
    bool create_disp_header( void );
    bool attach_bg_number( void );

    bool output_disp_header( std::ofstream& out );
    bool output_objects( std::ofstream& out );
    bool output_bgs( std::ofstream& out );

    bool outtxt_objects( std::ofstream& out );
    bool outtxt_bgs( std::ofstream& out );

    bool out_c_source_disp_header( std::ofstream& out );
    bool out_c_source_objects( std::ofstream& out );
    bool out_c_source_bgs( std::ofstream& out );

public :
    ScreenHeader( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr ) ,
	m_disp_cnt(0), m_bg0_cnt(0), m_bg1_cnt(0), m_bg2_cnt(0), m_bg3_cnt(0) ,
	m_bg_mode(255),
	m_object_palette( node_magic_ptr,node_manager_ptr) ,
	m_bg_palette( node_magic_ptr,node_manager_ptr)
	{
	    m_info_ptr[0] = NULL;
	    m_info_ptr[1] = NULL;
	    m_info_ptr[2] = NULL;
	    m_info_ptr[3] = NULL;
	    m_priority[0] = 255;
	    m_priority[1] = 255;
	    m_priority[2] = 255;
	    m_priority[3] = 255;
	}
    virtual ~ScreenHeader();

    virtual std::string GetCStructName( void );
    virtual std::string GetCStructName_BG( void );
    virtual std::string GetDispHeaderName( void );
    virtual std::string GetDispHeaderStructName( void );
    virtual std::string GetCName(void);
    virtual std::string GetCName_BG(void);
    virtual u32 GetSize(void);
    u32 GetNumOfObjects(void);
    u32 GetNumOfBGs(void);
    u32 GetObjectsSize(void);
    u32 GetBGsSize(void);
    u32 GetDispHeaderSize(void);

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );

};
//----------------------------------------------------------------------
__MAGBX__END
//----------------------------------------------------------------------

#endif	//  __SCREENHEADER_H__
//
//
