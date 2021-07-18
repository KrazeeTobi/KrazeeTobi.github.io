//======================================================
//    nodeinfo.h                                   
//    Definition of class which obtains node information
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NODEINFO_H__
#define	__NODEINFO_H__

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include <util.h>
#include "ex_reference.h"
#include "token_list.h"
#include "prev_util.h"
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
class NodeInfo : public AGBObject
{
public :
    typedef NodeInfo _Myt;
protected :
    u32 m_id;
    std::string m_node_name;
    NodeMagic* m_node_magic_ptr;
    NodeManager* m_node_manager_ptr;

    void set_true_value( void );
public :
    NodeInfo( NodeMagic* node_magic_ptr ,NodeManager* node_manager_ptr ) :
	m_node_magic_ptr(node_magic_ptr), m_node_manager_ptr(node_manager_ptr),
	m_id( 0xffffffff), m_node_name(""){}
    NodeInfo( const _Myt& _X ){*this = _X;}
    ~NodeInfo(){}

    _Myt& operator=(const _Myt& _X )
	{
	    if( &_X != this )
	    {
		SetID( ((_Myt&)_X).GetID() );
		SetNodeName( ((_Myt&)_X).GetNodeName() );
		m_node_magic_ptr = GetNodeMagicPtr();
		m_node_manager_ptr = GetNodeManagerPtr();
	    }
	}

    void SetID( u32 id );
    u32 GetID( void );

    void SetNodeName( const std::string& node_name );
    std::string GetNodeName( void );

    NodeMagic*	 GetNodeMagicPtr(void){return m_node_magic_ptr;}
    NodeManager* GetNodeManagerPtr(void){return m_node_manager_ptr;}

    virtual u32 GetSize(void){return 4;}

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );

    virtual bool Parse( TokenList& token_list );
};
//------------------------------------------------------------------------
__MAGBX__END
//------------------------------------------------------------------------

#endif	//  __NODEINFO_H__

//
//
