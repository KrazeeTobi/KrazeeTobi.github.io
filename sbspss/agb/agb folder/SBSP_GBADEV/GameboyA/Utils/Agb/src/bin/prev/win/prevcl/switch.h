//======================================================
//    switch.h                                   
//    Definition of single switch node for animation.
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__SWITCH_H__
#define	__SWITCH_H__

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"

__MAGBX__START

//----------------------------------------------------------------------
class SwitchState : public AGBObject
{
protected :
    u32 m_state;
    std::string m_child_name;
    NodeMagic* m_node_magic_ptr;
    NodeManager* m_node_manager_ptr;
public :
    SwitchState( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	m_state(0) , m_child_name("") , m_node_magic_ptr(node_magic_ptr) ,
	m_node_manager_ptr( node_manager_ptr ){}
    virtual ~SwitchState(){}

    virtual bool Parse( TokenList& token_list );
    virtual bool OutCSource( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool Output( std::ofstream& out );
    virtual u32  GetSize( void );
    u32	GetState(void);
} ;
//----------------------------------------------------------------------
class Switch : public AGBNode
{
protected :
    std::map<u32,SwitchState*> m_switch_map;

    virtual bool is_member_ok(void);
    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    bool parse_state( TokenList& token_list );

public :
    Switch( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr ){}
    virtual ~Switch();

    virtual u32 GetSize(void);
    virtual std::string GetCStructName( void );
    virtual std::string GetCStateName( void );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
    virtual bool Output( std::ofstream& out );
} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __SWITCH_H__
