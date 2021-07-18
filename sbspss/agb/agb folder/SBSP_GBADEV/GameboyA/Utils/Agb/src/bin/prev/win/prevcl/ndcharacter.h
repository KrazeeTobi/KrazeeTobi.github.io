//======================================================
//    ndcharacter.h                                   
//    Definition of character node(handled as image node)
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDCHARACTER_H__
#define	__NDCHARACTER_H__

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
class ndCharacter : public ndImage
{
protected :

    virtual bool check_width( u16 width );
    virtual bool check_height( u16 height );
    virtual bool check_bit_count( u16 bit_count );

    virtual bool load_file( const FileName& file_name );

    virtual bool parse_images( TokenList& token_list );

    virtual bool out_c_source_image_4b( std::ofstream& out, Image<u8>& im);
    virtual bool out_c_source_image_8b( std::ofstream& out, Image<u8>& im);
    virtual bool out_c_source_image_16b( std::ofstream& out, Image<u16>& im);
    virtual bool output_image_4b( std::ofstream& out, Image<u8>& im);
    virtual bool output_image_8b( std::ofstream& out, Image<u8>& im);
    virtual bool output_image_16b( std::ofstream& out, Image<u16>& im);

public :
    ndCharacter( NodeMagic* node_magic_ptr, NodeManager* node_manager_ptr ) :
	ndImage( node_magic_ptr, node_manager_ptr ){m_width = 8;m_height = 8;}

    virtual bool Outtxt( std::ofstream& out );
} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __NDCHARACTER_H__
