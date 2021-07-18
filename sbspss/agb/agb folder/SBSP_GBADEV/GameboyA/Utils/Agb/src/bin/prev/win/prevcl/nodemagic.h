//======================================================
//    nodemagic.h                                   
//    Definition of node magic and class to classify node type names 
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NODEMAGIC_H__
#define	__NODEMAGIC_H__

//----------------------------------------------------------------------
#include <map>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
//----------------------------------------------------------------------
#define	INVALID_MAGIC	(0xffffffff)
//----------------------------------------------------------------------
enum Magic
{
    magic_object = 0,
    magic_background ,
    magic_image ,
    magic_animation ,
    magic_switch ,
    magic_multi_switch ,
    magic_flipbook ,
    magic_rotate_animation ,
    magic_palette_animation ,
    magic_scale_animation ,
    magic_offset_animation ,
    magic_move_animation ,

    magic_max_num ,

    magic_palette_image  = 0x100,
    magic_character_image ,
    magic_map_character ,
    magic_map_image

};
//----------------------------------------------------------------------
typedef struct
{
    u32   magic;
    const char* Magic_name;
} nodeMagicResource;
//----------------------------------------------------------------------
typedef __MAGBX::AGBNode*
    (*_CreateNodeFunction)(class __MAGBX::NodeMagic* node_magic_ptr,
			   class __MAGBX::NodeManager* node_manager_ptr);
typedef struct
{
    u32 magic;
    _CreateNodeFunction fnc;
} nodeMagicFunctionResource;
//----------------------------------------------------------------------
extern nodeMagicResource mr_agb_default[];
extern u32 mr_size;
extern nodeMagicFunctionResource mfr_agb_default[];
extern u32 mfr_size;
//----------------------------------------------------------------------
__MAGBX__START

class NodeMagic
{
protected :
    std::map<std::string,u32> m_magic_map;
    std::map<u32,std::string> m_name_map;
    std::map<u32,_CreateNodeFunction> m_fnc_map;
public :
    NodeMagic( void );
    ~NodeMagic(){};

    void InitMagic( nodeMagicResource* mr_ptr=mr_agb_default,
		    u32 mr_num=mr_size);
    void InitFunction( nodeMagicFunctionResource* mfr_ptr=mfr_agb_default,
		       u32 mfr_num=mfr_size );

    u32 GetMagic(const char* magic_name);
    u32 GetMagic(const std::string& magic_name);
    std::string GetMagicName( u32 magic );
    AGBNode* CreateNode( const std::string& magic_name ,
			 NodeManager* node_manager_ptr );
};

__MAGBX__END
//----------------------------------------------------------------------

#endif	//  __NODEMAGIC_H__

//
//
