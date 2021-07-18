//======================================================
//    nodemagic.h                                   
//    Node magic and class to classify node type names  
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <map>
#include <agbtypes.h>
//----------------------------------------------------------------------
class NodeManager;
//----------------------------------------------------------------------
#include "nodemagic.h"
//----------------------------------------------------------------------
__MAGBX__START
extern AGBNode* CreateSwitch(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateMultiSwitch(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateNdObject(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateNdAnimation(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateFlipBook(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreatePaletteAnimation(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateScale(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateRotation(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateOffset(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateMove(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateNdImage(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreatePalette(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateCharacter(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateMapCharacter(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateMapImage(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
extern AGBNode* CreateNdBackground(
	NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr );
__MAGBX__END
//----------------------------------------------------------------------
nodeMagicResource mr_agb_default[] =
{
    {magic_object , "Object"} ,
    {magic_image , "Image"} ,
    {magic_switch , "Switch"} ,
    {magic_multi_switch , "MultiSwitch"} ,
    {magic_flipbook , "FlipBook"} ,
    {magic_animation , "Animation"} ,
    {magic_rotate_animation , "Rotation"} ,
    {magic_scale_animation , "Scale"} ,
    {magic_offset_animation , "Offset"} ,
    {magic_move_animation , "Move"} ,
    {magic_palette_animation , "PaletteAnimation"} ,
    {magic_palette_image , "Palette"} ,
    {magic_character_image , "Character"} ,
    {magic_map_character , "MapCharacter"} ,
    {magic_map_image , "MapImage"} ,
    {magic_background , "Background"} ,
};
u32 mr_size = sizeof(mr_agb_default)/sizeof(nodeMagicResource);
nodeMagicFunctionResource mfr_agb_default[] =
{
    {magic_object , __MAGBX::CreateNdObject } ,
    {magic_image , __MAGBX::CreateNdImage } ,
    {magic_animation , __MAGBX::CreateNdAnimation } ,
    {magic_switch , __MAGBX::CreateSwitch } ,
    {magic_multi_switch , __MAGBX::CreateMultiSwitch } ,
    {magic_flipbook , __MAGBX::CreateFlipBook } ,
    {magic_rotate_animation , __MAGBX::CreateRotation } ,
    {magic_scale_animation , __MAGBX::CreateScale } ,
    {magic_offset_animation , __MAGBX::CreateOffset } ,
    {magic_move_animation , __MAGBX::CreateMove } ,
    {magic_palette_animation , __MAGBX::CreatePaletteAnimation } ,
    {magic_palette_image , __MAGBX::CreatePalette } ,
    {magic_character_image , __MAGBX::CreateCharacter } ,
    {magic_map_character , __MAGBX::CreateMapCharacter } ,
    {magic_map_image , __MAGBX::CreateMapImage } ,
    {magic_background , __MAGBX::CreateNdBackground } ,
};
u32 mfr_size = sizeof(mfr_agb_default)/sizeof(nodeMagicFunctionResource);
//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
NodeMagic::NodeMagic( void )
{
    InitMagic();
    InitFunction();
}
//----------------------------------------------------------------------
void NodeMagic::InitMagic( nodeMagicResource* mr_ptr/*=mr_agb_default*/,
			   u32 mr_num/*=mr_size*/ )
{
    std::map<std::string,u32>::value_type *magic_value_ptr;
    std::map<u32,std::string>::value_type *name_value_ptr;

//    m_magic_map.resize(0);
//    m_name_map.resize(0);

    if( NULL == mr_ptr ) return;
    if( 0 == mr_num ) return;

    std::string magic_name;
    for( u32 loop=0 ; loop<mr_num ; ++loop )
    {
	magic_name = mr_ptr[loop].Magic_name;

	magic_value_ptr = new std::map<std::string,u32>::value_type(
	    magic_name ,mr_ptr[loop].magic );
	if( NULL == magic_value_ptr ) break;
	m_magic_map.insert( *magic_value_ptr );
	delete magic_value_ptr;

	name_value_ptr = new std::map<u32,std::string>::value_type(
	    mr_ptr[loop].magic, magic_name );
	if( NULL == name_value_ptr ) break;
	m_name_map.insert( *name_value_ptr );
	delete name_value_ptr;
    }
}
//----------------------------------------------------------------------
void NodeMagic::InitFunction( nodeMagicFunctionResource* mfr_ptr
					/*=mfr_agb_default*/,
			      u32 mfr_num/*=mfr_size*/ )
{
    std::map<u32,_CreateNodeFunction>::value_type *fnc_value_ptr;

//    m_fnc_map.resize(0);

    if( NULL == mfr_ptr ) return;
    if( 0 == mfr_num ) return;

    for( u32 loop=0 ; loop<mfr_num ; ++loop )
    {
	fnc_value_ptr = new std::map<u32,_CreateNodeFunction>::value_type(
	    mfr_ptr[loop].magic , mfr_ptr[loop].fnc );
	if( NULL == fnc_value_ptr ) break;
	m_fnc_map.insert( *fnc_value_ptr );
	delete fnc_value_ptr;
    }
}
//----------------------------------------------------------------------
u32 NodeMagic::GetMagic(const char* magic_name)
{
    std::string magic_str(magic_name);
    return GetMagic(magic_str);
}
//----------------------------------------------------------------------
u32 NodeMagic::GetMagic(const std::string& magic_name)
{
    std::map<std::string,u32>::iterator mp_it;
    mp_it = m_magic_map.find(magic_name);
    if( mp_it == m_magic_map.end() ) return INVALID_MAGIC;
    return (*mp_it).second;
}
//----------------------------------------------------------------------
std::string NodeMagic::GetMagicName( u32 magic )
{
    std::map<u32,std::string>::iterator name_it;
    name_it = m_name_map.find(magic);
    std::string invalid_name("");
    if( name_it == m_name_map.end() ) return invalid_name;
    return (*name_it).second;
}
//----------------------------------------------------------------------
AGBNode* NodeMagic::CreateNode( const std::string& magic_name ,
		 		NodeManager* node_manager_ptr )
{
    u32 node_magic = GetMagic( magic_name );
    if( INVALID_MAGIC == node_magic ) return NULL;
    std::map<u32,_CreateNodeFunction>::iterator fnc_map_it;
    fnc_map_it = m_fnc_map.find( node_magic );
    if( m_fnc_map.end() == fnc_map_it ) return NULL;
    return (*((*fnc_map_it).second))( this , node_manager_ptr );
}
//----------------------------------------------------------------------
__MAGBX__END
//----------------------------------------------------------------------

//
//
