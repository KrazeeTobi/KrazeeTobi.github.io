//======================================================
//    rotate_animation.h                                   
//    Rotate animation
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__ROTATE_ANIMATION_H__
#define	__ROTATE_ANIMATION_H__

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "agbanimnode.h"
#include "token_type.h"
#include "prev_util.h"

__MAGBX__START

//-----------------------------------------------------------------
class RotateAnimationKey : public KeyObject
{
protected :
    u16 m_angle;

    virtual bool outtxt_value( std::ofstream& out );
    virtual bool output_value( std::ofstream& out );
    virtual bool out_c_source_value( std::ofstream& out );

    virtual bool parse_value( TokenList& token_list );
public :
    RotateAnimationKey() : m_angle(0){}

    virtual u32 GetSize(void);
} ;
//-----------------------------------------------------------------
class RotateAnimation : public AGBAnimNode
{
protected :

    virtual KeyObject* create_key_object(void);

public :
    RotateAnimation( NodeMagic* node_magic_ptr ,
		     NodeManager* node_manager_ptr ) :
	AGBAnimNode( node_magic_ptr , node_manager_ptr ){}
    virtual std::string GetCStructName(void);

};
//-----------------------------------------------------------------

__MAGBX__END

#endif	//  __ROTATE_ANIMATION_H__

//
//
