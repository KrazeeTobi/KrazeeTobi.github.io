//======================================================
//    palette_animation.h                                   
//    Animation to change palette
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__PALETTE_ANIMATION_H__
#define	__PALETTE_ANIMATION_H__

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"

__MAGBX__START

//-----------------------------------------------------------------
class PaletteAnimationKey : public KeyObject
{
protected :
    u16 m_index;

    virtual bool outtxt_value( std::ofstream& out );
    virtual bool output_value( std::ofstream& out );

    virtual bool parse_value( TokenList& token_list );
public :
    PaletteAnimationKey() : KeyObject() , m_index(0){}
    virtual u32 GetSize(void);
};
//-----------------------------------------------------------------
class PaletteAnimation : public AGBAnimNode
{
protected :
    std::string m_child_name;
    u32 m_child_id;

	//  Create key object

    virtual KeyObject* create_key_object(void);

	//  Analyze each element 

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    virtual bool parse_type( TokenList& token_list );
    bool parse_palette( TokenList& token_list );
    virtual u32 get_default_size(void);

	//  Output function

    virtual bool output_type( std::ofstream& out );
    bool output_palette( std::ofstream& out );

    virtual bool outtxt_type( std::ofstream& out );
    bool outtxt_palette( std::ofstream& out );

    virtual bool out_c_source_type( std::ofstream& out );
    bool out_c_source_palette( std::ofstream& out );

public :
    PaletteAnimation( NodeMagic* node_magic_ptr ,
		      NodeManager* node_manager_ptr ) :
	AGBAnimNode( node_magic_ptr, node_manager_ptr ) ,
	m_child_name("") , m_child_id( 0xffffffff ){}

    virtual std::string GetCSourceStructName(void);
    virtual bool Output( std::ofstream& out );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
};
//-----------------------------------------------------------------

__MAGBX__END

#endif	//  __PALETTE_ANIMATION_H__

//
//
