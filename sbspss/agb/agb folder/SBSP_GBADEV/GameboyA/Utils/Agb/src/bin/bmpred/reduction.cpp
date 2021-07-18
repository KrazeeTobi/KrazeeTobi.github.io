//======================================================
//    reduction.cpp
//    Reduce Colors of HPicture to Picture
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <list>
#include <agbtypes.h>
#include <palette.h>
#include <hpicture.h>
#include <picture.h>
#include <color.h>

__USING__MAGBX

u32 GetNearestPalette( const Palette& _Pal, const Color& _C, u16 offset )
{
    u32 minimum_distance = 0xffffffff;
    u32 minimum_number = 0;
    u32 tmp_distance;
    tmp_distance = ((Color&)_C).SquareDistance(((Palette&)_Pal)[0]);
    for( u32 loop=offset ; loop<((Palette&)_Pal).Size() ; ++loop )
    {
	tmp_distance = ((Color&)_C).SquareDistance(
	    ((Palette&)_Pal).Get(loop) );
	if( minimum_distance > tmp_distance )
	{
	    minimum_distance = tmp_distance;
	    minimum_number = loop;
	}
	if( 0 == minimum_distance ) break;
    }
    return minimum_number;
}

//
//
//
Picture* CreateReductionPicture( const HPicture& _Hpic, const Palette& _Pal, u16 offset )
{
    Picture* ret_pic;
    u32 width,height;
    u32 h_percent_check;
    u32 h_percent_unit;
    u16 h_percent;

    width = ((HPicture&)_Hpic).Width();
    height = ((HPicture&)_Hpic).Height();

    h_percent_unit = (height+3) / 4;
    h_percent_check = h_percent_unit;
    h_percent = 0;

    ret_pic = new Picture( width , height );
    if( NULL == ret_pic ) return NULL;

    for( u32 h_loop=0 ; h_loop<height ; ++h_loop )
    {
	for( u32 w_loop=0 ; w_loop<width ; ++w_loop )
	{
	    ret_pic->Set( (u8)GetNearestPalette( _Pal,
			    ((HPicture&)_Hpic).Get( w_loop,h_loop ), offset) ,
			    w_loop, h_loop
			    );
	}
	if( h_loop >= h_percent_check )
	{
	    h_percent += 25;
	    h_percent_check += h_percent_unit;
	    std::cout << "..." << h_percent << "%";
	}
    }
    ret_pic->SetPalette( _Pal );

    if( h_percent < 100 )
    {
	std::cout << "...100%";
    }
    std::cout << "(End)" << std::endl;
    return ret_pic;
}

//
//
