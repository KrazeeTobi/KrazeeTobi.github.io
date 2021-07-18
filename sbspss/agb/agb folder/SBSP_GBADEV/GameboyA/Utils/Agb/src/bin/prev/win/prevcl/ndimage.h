//======================================================
//    ndimage.h                                   
//    Definition of image node
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NDIMAGE_H__
#define	__NDIMAGE_H__

#include <agbtypes.h>
#include <filename.h>
#include <image.h>
#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"

//----------------------------------------------------------------------
#define	NDIMAGE_VALUE_ID_WIDTH		(0)
#define	NDIMAGE_VALUE_ID_HEIGHT		(1)
#define	NDIMAGE_VALUE_ID_BIT_COUNT	(2)
//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
class ndImage : public AGBNode
{
protected :
    u16 m_width;
    u16 m_height;
    u16 m_bit_count;

    std::list<AGBObject*>	m_image_list;

    virtual bool is_member_ok(void);
    virtual bool check_width( u16 width );
    virtual bool check_height( u16 height );
    virtual bool check_bit_count( u16 bit_count );

    virtual bool load_file( const FileName& file_name );

    virtual bool parse_member( TokenList& token_list ,
				const std::string& identifier );
    virtual bool parse_width( TokenList& token_list );
    virtual bool parse_height( TokenList& token_list );
    virtual bool parse_bit_count( TokenList& token_list );
    virtual int parse_one_image_4b( TokenList& token_list );
    virtual int parse_one_image_8b( TokenList& token_list );
    virtual int parse_one_image_16b( TokenList& token_list );
    virtual bool parse_images( TokenList& token_list );
    virtual bool parse_files( TokenList& token_list );
    virtual u32  get_one_image_size( void );
    virtual u32  get_image_size( void );

    virtual bool out_c_source_image_4b( std::ofstream& out, Image<u8>& im);
    virtual bool out_c_source_image_8b( std::ofstream& out, Image<u8>& im);
    virtual bool out_c_source_image_16b( std::ofstream& out, Image<u16>& im);

    virtual bool out_c_source_param( std::ofstream& out );
    virtual bool out_c_source_image( std::ofstream& out );

    virtual bool output_image_4b( std::ofstream& out, Image<u8>& im);
    virtual bool output_image_8b( std::ofstream& out, Image<u8>& im);
    virtual bool output_image_16b( std::ofstream& out, Image<u16>& im);

    virtual bool output_param( std::ofstream& out );
    virtual bool output_image( std::ofstream& out );

    virtual std::string get_c_image_name(void);

public :
    ndImage( NodeMagic* node_magic_ptr , NodeManager* node_manager_ptr ) :
	AGBNode( node_magic_ptr , node_manager_ptr ) ,
	m_width(0), m_height(0), m_bit_count(0){}
    virtual ~ndImage();

    virtual u32  GetSize(void);
    virtual bool GetValue( void* dest, u32 value_id, u32 start, u32 num);
    virtual std::string GetCStructName( void );
    virtual bool Outtxt( std::ofstream& out );
    virtual bool OutCSource( std::ofstream& out );
    virtual bool Output( std::ofstream& out );
} ;
//----------------------------------------------------------------------

__MAGBX__END

#endif	//  __NDIMAGE_H__

//
//
