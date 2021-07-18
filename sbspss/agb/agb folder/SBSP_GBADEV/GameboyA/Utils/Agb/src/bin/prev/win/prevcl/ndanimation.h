//======================================================
//    ndanimation.h                                   
//    Definition of animation node
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__NDANIMATION_H__
#define	__NDANIMATION_H__

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
#define	AGBNODE_ANIME_TYPE_CONST    (0)
#define	AGBNODE_ANIME_TYPE_LINEAR   (1)
#define	AGBNODE_HEAD_SIZE	(12)
//------------------------------------------------------------------------
__MAGBX__START
//------------------------------------------------------------------------
class ndAnimation : public AGBNode
{
protected :
    std::list<NodeInfo*> m_children_list;

    NodeInfo* m_image_child_ptr;

    virtual u32 get_children_size(void);
    virtual u32 get_default_size(void);

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    bool parse_child( TokenList& token_list );
    bool output_children( std::ofstream& out );
    bool outtxt_children( std::ofstream& out );
    bool out_c_source_children( std::ofstream& out );
    bool out_c_source_children_objects( std::ofstream& out );

public :
    ndAnimation( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr )
	{}
    virtual ~ndAnimation();

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

#endif	//  __NDANIMATION_H__
