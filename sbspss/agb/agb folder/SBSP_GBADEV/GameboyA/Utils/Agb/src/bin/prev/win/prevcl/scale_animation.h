//======================================================
//    scale_animation.h                                   
//    Scaling animation
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__SCALE_ANIMATION_H__
#define	__SCALE_ANIMATION_H__

//-----------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "agbanimnode.h"

__MAGBX__START

//-----------------------------------------------------------------
class ScaleAnimationKey : public KeyObject
{
protected :
    float m_scale_x;
    float m_scale_y;

    virtual bool outtxt_value( std::ofstream& out );
    virtual bool out_c_source_value( std::ofstream& out );
    virtual bool output_value( std::ofstream& out );

    virtual bool parse_value( TokenList& token_list );
public :
    ScaleAnimationKey() : m_scale_x(0),m_scale_y(0){}

    virtual u32 GetSize(void);
} ;
//-----------------------------------------------------------------
class ScaleAnimation : public AGBAnimNode
{
protected :

    virtual KeyObject* create_key_object(void);

public :
    ScaleAnimation( NodeMagic* node_magic_ptr ,
		    NodeManager* node_manager_ptr ) :
	AGBAnimNode( node_magic_ptr , node_manager_ptr ){}
    virtual std::string GetCStructName(void);

};
//-----------------------------------------------------------------

__MAGBX__END

#endif	//  __SCALE_ANIMATION_H__
//
//
