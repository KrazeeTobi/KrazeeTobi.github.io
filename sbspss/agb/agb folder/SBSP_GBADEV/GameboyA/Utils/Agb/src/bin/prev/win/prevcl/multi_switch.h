//======================================================
//    multi_switch.h                                   
//    Definition of multi-switch node for animation  
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__MULTI_SWITCH_H__
#define	__MULTI_SWITCH_H__

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "nodeinfo.h"

__MAGBX__START

//----------------------------------------------------------------------
class MultiSwitchState : public AGBObject
{
protected :
    u32 m_state;
    u16 m_index;
    std::list<NodeInfo*> m_child_list;
    NodeMagic* m_node_magic_ptr;
    NodeManager* m_node_manager_ptr;
    bool parse_children( TokenList& token_list );
public :
    MultiSwitchState( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr ) :
	m_state(0) , m_node_magic_ptr(node_magic_ptr) ,
	m_index(0) ,
	m_node_manager_ptr( node_manager_ptr ){}
    virtual ~MultiSwitchState();

    void SetIndex( u16 index ){m_index = index;}
    virtual bool Parse( TokenList& token_list );
    virtual bool OutCSource( std::ofstream& out );
    bool OutCSourceArray( std::ofstream& out );
    u32  GetNumOfChildren( void ){return (u32)m_child_list.size();}
    virtual bool Outtxt( std::ofstream& out );
    virtual bool Output( std::ofstream& out );
    bool OutputArray( std::ofstream& out );
    virtual u32  GetSize( void );
    u32	GetState(void);
} ;
//----------------------------------------------------------------------
class MultiSwitch : public AGBNode
{
protected :
    std::map<u32,MultiSwitchState*> m_switch_map;
    u16	m_index;

    virtual bool is_member_ok(void);
    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    bool parse_case( TokenList& token_list );

public :
    MultiSwitch( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr ) , m_index(0){}
    virtual ~MultiSwitch();

    virtual u32 GetSize(void);
    virtual std::string GetCStructName( void );
    virtual std::string GetCStateName( void );
    virtual std::string GetCArrayName( void );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
    virtual bool Output( std::ofstream& out );
} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __MULTI_SWITCH_H__

//
//
