//======================================================
//    ndmapimage.h                                   
//    Definition of mass data for BG(handled as image node)
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDMAPIMAGE_H__
#define	__NDMAPIMAGE_H__

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
class ndMapImage : public ndImage
{
protected :
    u8 m_palette_number;

    virtual bool load_file( const FileName& file_name );

    virtual bool parse_mode( TokenList& token_list );
    virtual bool parse_palette_number( TokenList& token_list );
    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    virtual bool parse_images( TokenList& token_list );

    virtual bool out_c_source_image( std::ofstream& out );
    virtual bool output_image( std::ofstream& out );

public :
    ndMapImage( NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr ) :
	ndImage( node_magic_ptr, node_manager_ptr ) ,
	m_palette_number(0)
	{
	    m_bit_count = 8;
	}

} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __NDMAPIMAGE_H__

//
//
