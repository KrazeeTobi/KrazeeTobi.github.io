//======================================================
//    move_animation.h                                   
//    Move animation: node definition that moves object 
//    or BG
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__MOVE_ANIMATION_H__
#define	__MOVE_ANIMATION_H__

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
class MoveAnimationKey : public KeyObject
{
protected :
    f32 m_x;
    f32 m_y;

    virtual bool out_c_source_value( std::ofstream& out );
    virtual bool outtxt_value( std::ofstream& out );
    virtual bool output_value( std::ofstream& out );

    virtual bool parse_value( TokenList& token_list );
public :
    MoveAnimationKey() : m_x(0),m_y(0){}

    virtual u32 GetSize(void);
} ;
//-----------------------------------------------------------------
class MoveAnimation : public AGBAnimNode
{
protected :

    virtual KeyObject* create_key_object(void);

public :
    MoveAnimation( NodeMagic* node_magic_ptr ,
		     NodeManager* node_manager_ptr ) :
	AGBAnimNode( node_magic_ptr , node_manager_ptr ){}
    virtual std::string GetCStructName(void);

};
//-----------------------------------------------------------------

__MAGBX__END

#endif	//  __MOVE_ANIMATION_H__

//
//
