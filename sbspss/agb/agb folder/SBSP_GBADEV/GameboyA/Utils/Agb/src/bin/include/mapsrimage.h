//======================================================
//    mapsrimage.h                                           
//    Class to handle images of AGB scaling BG. 
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_MAPSRIMAGE_
#define	_AGB_MAPSRIMAGE_

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <maptextimage.h>

__MAGBX__START

class MapSRImage : public MapTextImage
{
private :
    u8* create_out_buffer( void );
    void delete_out_buffer( u8* buffer_ptr );
protected :
public :
    typedef MapSRImage _Myt;

    MapSRImage( u32 width=0 , u32 height=0 ) :
       MapTextImage(width , height){}
    MapSRImage( const _Myt& _X ) :
       MapTextImage( _X ){}

    virtual bool Output( std::ofstream &out );
    virtual bool Outtxt( std::ofstream &out );
    virtual bool OutCSource( std::ofstream &out );

};

__MAGBX__END

#endif	//  _AGB_MAPSRIMAGE_

//
//
