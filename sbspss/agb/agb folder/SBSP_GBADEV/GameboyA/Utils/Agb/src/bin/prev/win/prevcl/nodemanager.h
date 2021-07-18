//======================================================
//    nodemanager.h                                   
//    Definition of class which manages all nodes
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NODEMANAGER_H__
#define	__NODEMANAGER_H__

#include <agbtypes.h>
#include "ex_reference.h"
#include "nodemagic.h"
#include "agbnode.h"
#include "screenheader.h"

//----------------------------------------------------------------------
#define	INVALID_NODE_ID	(0xffffffff)
//----------------------------------------------------------------------
typedef struct
{
    std::string name;
    __MAGBX::AGBNode*	node_ptr;
    u32		id;
} NodeResource ;
//----------------------------------------------------------------------
__MAGBX__START

class NodeManager : public AGBObject
{
protected :
    NodeMagic* m_node_magic_ptr;
    u32 m_id;
    std::list<std::string> m_node_name_list;
    std::map<u32,NodeResource> m_node_map;
    std::map<std::string,u32> m_id_map;
    u32 m_name_index;
    ScreenHeader* m_header_ptr;

    u32 get_name_size(void);
    u32 get_offset_table_size(void);
    bool output_node_header( std::ofstream& out );
    bool output_offset_table( std::ofstream& out );
    bool output_name( std::ofstream& out );
    bool output_nodes( std::ofstream& out );
    bool out_c_source_offset_table( std::ofstream& out );
    bool out_c_source_extern_nodes( std::ofstream& out );
    bool out_c_source_nodes( std::ofstream& out );
    bool out_c_source_header_chunk( std::ofstream& out );

public :
    NodeManager( void ) :
	m_id(0), m_name_index(0) , m_header_ptr(NULL)
	{ m_node_magic_ptr = new NodeMagic; }
    ~NodeManager();

    AGBNode* CreateNode( const std::string& MagicName ,
			 const std::string& NodeName );
    AGBNode* GetNodePtr( const std::string& NodeName );
    AGBNode* GetNodePtr( u32 id );
    u32 GetID( const std::string& NodeName );
    virtual std::string GetNodeName( u32 id );

    virtual u32 GetSize( void );
    virtual bool Parse( TokenList& token_list );
    virtual bool LoadFile( const PathName& path_name );
    virtual void GetFileNameList( std::list<FileName>& fname_list );

    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
    virtual bool OutCSourceHeader( std::ofstream& out );
};

__MAGBX__END
//----------------------------------------------------------------------

#endif	//  __NODEMANAGER_H__

//
//
