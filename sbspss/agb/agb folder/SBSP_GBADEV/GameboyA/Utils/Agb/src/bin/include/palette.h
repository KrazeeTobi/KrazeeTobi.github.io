//======================================================
//    palette.h
//    Class to handle AGB palette.  
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_PALETTE_
#define	_AGB_PALETTE_

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <image.h>
#include <color.h>
#include <filename.h>

__MAGBX__START

class Palette : public AGBObject
{
public :
    typedef Palette _Myt;
    typedef Color _Ty;

    typedef Image<Color>    _Im;

protected :
    virtual u16* create_out_buffer( void );
    virtual void delete_out_buffer( u16* out_buffer );
protected :
    u32 m_num_of_colors;
    _Ty	m_dummy;
    _Im	m_image;
public :
    typedef Palette _Myt;
    typedef Color _Ty;

	//  Constructor.  Default is 256 colors.

    Palette( u32 num_of_colors = 256 )
	: m_image( 16 , (num_of_colors+15) / 16 ) ,
	m_num_of_colors( num_of_colors )
	{}

	//  Copy constructor.

    Palette( const _Myt& _X ) :
    m_image( ((_Myt&)_X).GetImage()), m_num_of_colors(((_Myt&)_X).Size()){}

	//  Get parameter.

    u32 NumOfColors(void){return m_num_of_colors;}
    u32 Size(){return NumOfColors();}

	//   Find the Nth color.

    void Trim( void );

	//   Find the Nth color.

    virtual const _Ty& Get( int _N );
    virtual const _Ty& operator[](int _N);

	//  Set the color.

    virtual void Set( const _Ty& _P , int _N=0 );
    virtual void Set( const _Myt& _X , int _N=0);
    virtual _Myt& operator=(const _Myt& _X);

	//  Set the color.

    virtual int Add( const _Ty& _P );
    virtual int Add( const _Myt& _X );

	//  Reserve area again.

    virtual bool Resize( int _N );

	//  Save

    virtual bool Output( std::ofstream &out );
    virtual bool Outtxt( std::ofstream &out );
    virtual bool OutCSource( std::ofstream &out );

	//  Read .act file.

    virtual bool LoadACT( const FileName& file_name );
    virtual bool SaveACT( const FileName& file_name );

    _Im& GetImage( void ){return m_image;}
};

__MAGBX__END

#endif	//  _AGB_PALETTE_

//
//
