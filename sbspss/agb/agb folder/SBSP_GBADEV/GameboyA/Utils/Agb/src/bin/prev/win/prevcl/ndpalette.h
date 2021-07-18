//======================================================
//    ndpalette.h                                   
//    Definition of palette for AGB color format (it is treated as image node)
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDPALETTE_H__
#define	__NDPALETTE_H__

#include <iostream>
#include <fstream>
#include <list>
#include <agbtypes.h>
#include <filename.h>
#include <image.h>
#include <palette.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "ndimage.h"

//----------------------------------------------------------------------

__MAGBX__START

//----------------------------------------------------------------------
class ndPalette : public ndImage
{

protected :
    u16 m_tmp_num;

    bool load_act( const FileName& file_name );
    bool load_bmp( const FileName& file_name );
    void set_palette( Palette& pal );

    virtual bool check_width( u16 width );
    virtual bool check_height( u16 height );
    virtual bool check_bit_count( u16 bit_count );

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    virtual bool load_file( const FileName& file_name );

    virtual bool out_c_source_image( std::ofstream& out );
    virtual bool output_image( std::ofstream& out );

public :
    ndPalette( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	ndImage( node_magic_ptr , node_manager_ptr ) , m_tmp_num(0)
	{
	    m_width = 16;
	    m_height= 1;
	    m_bit_count = 16;
	}

    virtual bool Outtxt( std::ofstream& out );
} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __NDPALETTE_H__

//
//
