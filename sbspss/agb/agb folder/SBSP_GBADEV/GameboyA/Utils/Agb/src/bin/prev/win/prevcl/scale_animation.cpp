//======================================================
//    scale_animation.cpp                                   
//    Scaling animation
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include "ex_reference.h"
#include "scale_animation.h"
#include "token_list.h"
#include "nodemagic.h"
#include "token_type.h"
#include "prev_util.h"

__MAGBX__START

//----------------------------------------------------------------
AGBNode* CreateScale(NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr )
{
    return new ScaleAnimation( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------
bool ScaleAnimationKey::outtxt_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << m_scale_x << ", " << m_scale_y;
    return true;
}
//----------------------------------------------------------------
bool ScaleAnimationKey::out_c_source_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    s16 out_x = (s16)(float)(256.0f / m_scale_x);
    s16 out_y = (s16)(float)(256.0f / m_scale_y);
    out << out_x << ", " << out_y;
    return true;
}
//----------------------------------------------------------------
bool ScaleAnimationKey::output_value( std::ofstream& out )
{
    s16 out_x = (s16)(float)(256.0f / m_scale_x);
    s16 out_y = (s16)(float)(256.0f / m_scale_y);
    if( false == ::Output( out , out_x ) ) return false;
    return ::Output( out , out_y );
}
//----------------------------------------------------------------
bool ScaleAnimationKey::parse_value( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_scale_x ) )
    {
	return false;
    }
    if( false == ParseValue( token_list , m_scale_y ) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------
u32 ScaleAnimationKey::GetSize( void )
{
    return 6;
}
//----------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------
KeyObject* ScaleAnimation::create_key_object(void)
{
    return new ScaleAnimationKey;
}
//----------------------------------------------------------------
std::string ScaleAnimation::GetCStructName(void)
{
    std::string ret_name = "nodeScaleAnim";
    return ret_name;
}
//----------------------------------------------------------------

__MAGBX__END

//
//
