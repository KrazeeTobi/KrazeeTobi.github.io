//======================================================
//    move_animation.cpp                                   
//    Move animation, a node that moves an object or BG
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include "move_animation.h"
#include "token_list.h"
#include "token_type.h"
#include "prev_util.h"

__MAGBX__START

//----------------------------------------------------------------
AGBNode* CreateMove( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr )
{
    return new MoveAnimation( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------
bool MoveAnimationKey::out_c_source_value( std::ofstream& out )
{
    s16 out_x,out_y;
    out_x = (s16)(f32)(m_x * 256.0f);
    out_y = (s16)(f32)(m_y * 256.0f);
    out << out_x << ", " << out_y;
    return true;
}
//----------------------------------------------------------------
bool MoveAnimationKey::outtxt_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << m_x << ", " << m_y;
    return true;
}
//----------------------------------------------------------------
bool MoveAnimationKey::output_value( std::ofstream& out )
{
    s16 out_x,out_y;
    out_x = (s16)(f32)(m_x * 256.0f);
    out_y = (s16)(f32)(m_y * 256.0f);
    if( false == ::Output( out , out_x ) ) return false;
    return ::Output( out , out_y );
}
//----------------------------------------------------------------
bool MoveAnimationKey::parse_value( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_x ) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_y ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
u32 MoveAnimationKey::GetSize( void )
{
    return 6;
}
//----------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------
KeyObject* MoveAnimation::create_key_object(void)
{
    return new MoveAnimationKey;
}
//----------------------------------------------------------------
std::string MoveAnimation::GetCStructName(void)
{
    std::string ret_name = "nodeMoveAnim";
    return ret_name;
}
//----------------------------------------------------------------

__MAGBX__END

//
//
