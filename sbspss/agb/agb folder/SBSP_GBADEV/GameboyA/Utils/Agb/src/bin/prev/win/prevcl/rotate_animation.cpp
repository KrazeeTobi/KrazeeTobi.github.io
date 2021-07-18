//======================================================
//    rotate_animation.cpp                                   
//    Rotate animation
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agbtypes.h>
#include "ex_reference.h"
#include "rotate_animation.h"
#include "token_list.h"
#include "nodemagic.h"

__MAGBX__START

//----------------------------------------------------------------
AGBNode* CreateRotation( NodeMagic* node_magic_ptr ,
			 NodeManager* node_manager_ptr )
{
    return new RotateAnimation( node_magic_ptr , node_manager_ptr );
}
//----------------------------------------------------------------
bool RotateAnimationKey::out_c_source_value( std::ofstream& out )
{
    if( !out.is_open() ) return false;

    float angle = (float)m_angle;
    angle *= 256.0f;
    angle /= 360.0f;
    out << (u16)angle;

    return true;
}
//----------------------------------------------------------------
bool RotateAnimationKey::outtxt_value( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    out << (u16)m_angle;
    return true;
}
//----------------------------------------------------------------
bool RotateAnimationKey::output_value( std::ofstream& out )
{
    if( !out.is_open() ) return false;
    float angle = (float)m_angle;
    angle *= 256.0f;
    angle /= 360.0f;
    if( false == ::Output( out , (u8)angle ) ) return false;
    return ::Output( out , (u8)0 );
}
//----------------------------------------------------------------
bool RotateAnimationKey::parse_value( TokenList& token_list )
{
    if( false == ParseValue( token_list , m_angle ) )
    {
	return false;
    }

    return true;
}
//----------------------------------------------------------------
u32 RotateAnimationKey::GetSize( void )
{
    return 4;
}
//----------------------------------------------------------------
//
//
//
//
//----------------------------------------------------------------
KeyObject* RotateAnimation::create_key_object(void)
{
    return new RotateAnimationKey;
}
//----------------------------------------------------------------
std::string RotateAnimation::GetCStructName(void)
{
    std::string ret_name = "nodeRotateAnim";
    return ret_name;
}
//----------------------------------------------------------------

__MAGBX__END

//
//
