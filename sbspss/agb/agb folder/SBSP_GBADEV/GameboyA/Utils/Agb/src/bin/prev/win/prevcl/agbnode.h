//======================================================
//    agbnode.h                                       
//    Basic class definition for all nodes 
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__AGBNODE_H__
#define	__AGBNODE_H__

//------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <agbtypes.h>
#include <util.h>
#include "token_list.h"
#include "ex_reference.h"
//------------------------------------------------------------------------
#define	AGBNODE_ANIME_TYPE_CONST    (0)
#define	AGBNODE_ANIME_TYPE_LINEAR   (1)
#define	AGBNODE_HEAD_SIZE	(12)
//------------------------------------------------------------------------
__MAGBX__START

class AGBNode : public AGBObject
{
protected :
    u32 m_id;
    u32 m_name_index;
    u32 m_magic;
    NodeMagic* m_node_magic_ptr;
    NodeManager* m_node_manager_ptr;
    std::list<FileName> m_fname_list;

    virtual bool is_member_ok( void )
	{return false;}
    virtual bool parse_member( TokenList& token_list,
			       const std::string& identifier )
	{return false;}

    virtual bool load_file( const FileName& file_name ){return true;}
    virtual bool out_c_source_node_head( std::ofstream& out );
    virtual bool output_node_head( std::ofstream& out );

public :
    AGBNode( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
		m_id(0xffffffff) , m_name_index(0xffffffff) ,
		m_magic(0xffffffff) , m_node_magic_ptr(node_magic_ptr) ,
		m_node_manager_ptr( node_manager_ptr ){}
    virtual ~AGBNode(){}

    virtual std::string GetCStructName( void );

    virtual std::string GetCName(void);
    virtual u32 GetSize(void){ return AGBNODE_HEAD_SIZE; }
    virtual void GetFileNameList( std::list<FileName>& fname_list );
    virtual bool LoadFile( const PathName& path_name );

    virtual bool GetValue( void* dest, u32 value_id, u32 start, u32 num );

    virtual bool Parse( TokenList& token_list );

    void SetID( u32 id ){m_id = id;}
    u32 GetID(void){return m_id;}
    void SetNameIndex( u32 name_index ){m_name_index = name_index;}
    u32 GetNameIndex(void){return m_name_index;}
    void SetMagic( u32 magic ){m_magic = magic;}
    u32 GetMagic( void ){ return m_magic; }

    void ErrorMessage( const char* message );
    void ErrorMessage( const std::string& message );
};

__MAGBX__END
//------------------------------------------------------------------------

#endif	//  __AGBNODE_H__

//
//
