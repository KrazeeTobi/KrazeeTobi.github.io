//======================================================
//    offset_animation.cpp                                   
//    Animation to shift coordinates. Affected by scaling/rotation. 
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include "offset_animation.h"
#include "token_list.h"
#include "token_type.h"
#include "prev_util.h"

__MAGBX__START

//----------------------------------------------------------------
AGBNode* CreateOffset( NodeMagic* node_magic_ptr ,
			NodeManager* node_manager_ptr )
{
    return new OffsetAnimation( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------
bool OffsetAnimationKey::out_c_source_value( std::ofstream& out )
{
    s16 out_x,out_y;
    out_x = (s16)(f32)(m_x * 256.0f);
    out_y = (s16)(f32)(m_y * 256.0f);
    out << out_x << ", " << out_y;
    return true;
}
//----------------------------------------------------------------
bool OffsetAnimationKey::outtxt_value( std::ofstream& out )
{
    if( false == out.is_open() ) return false;
    out << m_x << ", " << m_y;
    return true;
}
//----------------------------------------------------------------
bool OffsetAnimationKey::output_value( std::ofstream& out )
{
    s16 out_x,out_y;
    out_x = (s16)(f32)(m_x * 256.0f);
    out_y = (s16)(f32)(m_y * 256.0f);
    if( false == ::Output( out , out_x ) ) return false;
    return ::Output( out , out_y );
}
//----------------------------------------------------------------
bool OffsetAnimationKey::parse_value( TokenList& token_list )
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
u32 OffsetAnimationKey::GetSize( void )
{
    return 6;
}
//----------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------
KeyObject* OffsetAnimation::create_key_object(void)
{
    return new OffsetAnimationKey;
}
//----------------------------------------------------------------
std::string OffsetAnimation::GetCStructName(void)
{
    std::string ret_name = "nodeOffsetAnim";
    return ret_name;
}
//----------------------------------------------------------------

__MAGBX__END

//
//
