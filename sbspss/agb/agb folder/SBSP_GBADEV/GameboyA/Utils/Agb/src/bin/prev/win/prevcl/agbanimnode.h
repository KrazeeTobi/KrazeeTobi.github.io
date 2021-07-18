//======================================================
//    agbanimnode.h                                   
//    Basic class definition of animation node
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__AGB_ANIM_NODE_H__
#define	__AGB_ANIM_NODE_H__

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"

//-----------------------------------------------------------------
#define	AGBNODE_ANIME_TYPE_CONST    (0)
#define	AGBNODE_ANIME_TYPE_LINEAR   (1)
//-----------------------------------------------------------------

__MAGBX__START

//-----------------------------------------------------------------
class KeyObject : public AGBObject
{
protected :
    u16 m_time;

    virtual bool out_c_source_value( std::ofstream& out );
    virtual bool outtxt_value( std::ofstream& out );
    virtual bool output_value( std::ofstream& out );

    virtual bool parse_time( TokenList& token_list );
    virtual bool parse_value( TokenList& token_list );
public :
    KeyObject(){}
    virtual ~KeyObject(){}
    virtual u32 GetSize(void){return 2;}
    virtual u16 GetTime(void){return m_time;}
    virtual void SetTime(u16 time){m_time = time;}

    virtual bool OutCSource( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool Output( std::ofstream& out );
    virtual bool Parse( TokenList& token_list );
};
//-----------------------------------------------------------------
class AGBAnimNode : public AGBNode
{
protected :
    u8  m_type;
    u16 m_max_time;
    std::map<u16,KeyObject*> m_key_map;

	//   Create key object

    virtual KeyObject* create_key_object(void);

	//   Analyze each element 

    virtual bool is_member_ok( void );
    virtual bool parse_member(TokenList& token_list ,
			      const std::string& identifier );
    virtual bool parse_type( TokenList& token_list );
    virtual bool parse_max_time( TokenList& token_list );
    virtual bool parse_key( TokenList& token_list );
    virtual u32 get_default_size(void);
    virtual u32 get_key_size(void);

	//  Output function

    virtual bool output_type( std::ofstream& out );
    virtual bool output_max_time( std::ofstream& out );
    virtual bool output_key( std::ofstream& out );

    virtual bool outtxt_type( std::ofstream& out );
    virtual bool outtxt_max_time( std::ofstream& out );
    virtual bool outtxt_key( std::ofstream& out );

    virtual bool out_c_source_type( std::ofstream& out );
    virtual bool out_c_source_max_time( std::ofstream& out );
    virtual bool out_c_source_key( std::ofstream& out );
    virtual bool out_c_source_key_array( std::ofstream& out );

public :
    AGBAnimNode( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr, node_manager_ptr ), m_type(0), m_max_time(0){}
    virtual ~AGBAnimNode();

    virtual u32 GetSize(void);
    virtual u32  GetNumOfKeys(void);
    virtual std::string GetCKeyName( void );
    virtual std::string GetCStructName(void);
    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
};
//-----------------------------------------------------------------

__MAGBX__END

#endif	//  __AGB_ANIM_NODE_H__

//
//
