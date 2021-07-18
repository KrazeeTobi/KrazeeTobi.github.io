//======================================================
//    ndmapcharacter.h                                   
//    Definition of character data for BG (it is treated as an image)
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDMAPCHARACTER_H__
#define	__NDMAPCHARACTER_H__

#include <iostream>
#include <fstream>
#include <list>
#include <agbtypes.h>
#include <filename.h>
#include <image.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "ndimage.h"

//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
class ndMapCharacter : public ndCharacter
{
protected :
    u8 m_mode;

    virtual bool check_width( u16 width );
    virtual bool check_height( u16 height );
    virtual bool check_bit_count( u16 bit_count );

    virtual bool load_file( const FileName& file_name );

    virtual bool parse_member( TokenList& token_list,
			const std::string& identifier);
    virtual bool out_c_source_image( std::ofstream& out );
    bool parse_mode( TokenList& token_list );
    virtual bool output_image( std::ofstream& out );

public :
    ndMapCharacter( NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr ) :
	ndCharacter( node_magic_ptr, node_manager_ptr ) , m_mode(0)
	{}

    virtual bool Outtxt( std::ofstream& out );
} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __NDMAPCHARACTER_H__
