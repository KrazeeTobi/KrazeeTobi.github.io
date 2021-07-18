//======================================================
//    colorspace.cpp
//    Color Space Class.  Can create one palette from multiple images.
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <list>
#include <agbtypes.h>
#include <color.h>
#include <hpicture.h>
#include <palette.h>
#include "colorspace.h"

extern u32 GetNearestPalette( const Palette& _Pal, const Color& _C, u16 offset );

__MAGBX__START

//-------------------------------------------------------
u16 ColorSpace::get_array_number( u8 _r, u8 _g, u8 _b )
{
    return (u16)((_r & 0xf8) << 7)
		 | (u16)((_g & 0xf8) << 2)
		 | (u16)((_b & 0xf8) >> 3);
}
//-------------------------------------------------------
u32 ColorSpace::get_use_num( u8 _r, u8 _g, u8 _b )
{
    return m_use_buffer[get_array_number( _r,_g,_b)];
}
//-------------------------------------------------------
u32 ColorSpace::get_use_num( const ColorCut& _cc )
{
    u32 ret_num = 0;
    for( u8 red_loop = ((ColorCut&)_cc).min_r ;
	red_loop < ((ColorCut&)_cc).max_r ;
	++red_loop )
    {
	for( u8 green_loop = ((ColorCut&)_cc).min_g ;
	    green_loop < ((ColorCut&)_cc).max_g ;
	    ++green_loop )
	{
	    for( u8 blue_loop = ((ColorCut&)_cc).min_b ;
		blue_loop < ((ColorCut&)_cc).max_b ;
		++blue_loop )
	    {
		ret_num += get_use_num( red_loop<<3,green_loop<<3,blue_loop<<3 );
	    }
	}
    }
    return ret_num;
}
//-------------------------------------------------------
void ColorSpace::set_use_num( const ColorCut& _cc )
{
    ::memset( m_use_red,   0, 32*sizeof(u32) );
    ::memset( m_use_green, 0, 32*sizeof(u32) );
    ::memset( m_use_blue,  0, 32*sizeof(u32) );
    u32 tmp;
    for( u8 red_loop = ((ColorCut&)_cc).min_r ;
	red_loop < ((ColorCut&)_cc).max_r ;
	++red_loop )
    {
	for( u8 green_loop = ((ColorCut&)_cc).min_g ;
	    green_loop < ((ColorCut&)_cc).max_g ;
	    ++green_loop )
	{
	    for( u8 blue_loop = ((ColorCut&)_cc).min_b ;
		blue_loop < ((ColorCut&)_cc).max_b ;
		++blue_loop )
	    {
		tmp = get_use_num( red_loop<<3,green_loop<<3,blue_loop<<3 );
		m_use_red[red_loop] += tmp;
		m_use_green[green_loop] += tmp;
		m_use_blue[blue_loop] += tmp;
	    }
	}
    }
}
//-------------------------------------------------------
void ColorSpace::narrow_color_cut( ColorCut& _cc )
{
    while( 0 == m_use_red[_cc.min_r] ) ++_cc.min_r;
    while( 0 == m_use_red[_cc.max_r-1] ) --_cc.max_r;
    while( 0 == m_use_green[_cc.min_g] ) ++_cc.min_g;
    while( 0 == m_use_green[_cc.max_g-1] ) --_cc.max_g;
    while( 0 == m_use_blue[_cc.min_b] ) ++_cc.min_b;
    while( 0 == m_use_blue[_cc.max_b-1] ) --_cc.max_b;
}
//-------------------------------------------------------
Color ColorSpace::get_average( const ColorCut& _cc )
{
    u8 red,green,blue;
    if( ((ColorCut&)_cc).IsUnique() )
    {
	red = ((ColorCut&)_cc).min_r;
	green = ((ColorCut&)_cc).min_g;
	blue = ((ColorCut&)_cc).min_b;
    }
    else
    {
	u32 red_sum = 0;
	u32 green_sum = 0;
	u32 blue_sum = 0;
	u32 red_num = 0;
	u32 green_num = 0;
	u32 blue_num = 0;
	u32 tmp;
	for( u8 red_loop = ((ColorCut&)_cc).min_r ;
	    red_loop < ((ColorCut&)_cc).max_r ;
	    ++red_loop )
	{
	    for( u8 green_loop = ((ColorCut&)_cc).min_g ;
		green_loop < ((ColorCut&)_cc).max_g ;
		++green_loop )
	    {
		for( u8 blue_loop = ((ColorCut&)_cc).min_b ;
		    blue_loop < ((ColorCut&)_cc).max_b ;
		    ++blue_loop )
		{
		    tmp = get_use_num( red_loop<<3,green_loop<<3,blue_loop<<3 );
		    red_num += tmp;
		    green_num += tmp;
		    blue_num += tmp;
		    red_sum += tmp * red_loop;
		    green_sum += tmp * green_loop;
		    blue_sum += tmp * blue_loop;
		}
	    }
	}
	red   = (u8)(u32)(red_sum / red_num);
	green = (u8)(u32)(green_sum / green_num);
	blue  = (u8)(u32)(blue_sum / blue_num);
    }
    red = ((red & 0x1f) << 3) | ((red & 0x1c) >> 2);
    green = ((green & 0x1f) << 3) | ((green & 0x1c) >> 2 );
    blue = ((blue & 0x1f) << 3) | ((blue & 0x1c) >> 2 );

    Color ret_clr( red,green,blue );
    return ret_clr;
}
//-------------------------------------------------------
void ColorSpace::set_base_0( void )
{
    if( !m_use_base_flag ) return;
    u32 zero_number;

    zero_number = GetNearestPalette( m_pal, m_base, m_offset );

    Color clr;
    clr = m_pal[0];
    m_pal.Set( m_base, 0 );
    if( zero_number ) m_pal.Set( clr, zero_number );
}
//-------------------------------------------------------
void ColorSpace::Add( const Color& _C )
{
    ++m_use_buffer[get_array_number(
		((Color&)_C).Red(),((Color&)_C).Green(),
		((Color&)_C).Blue() )];
}
//-------------------------------------------------------
void ColorSpace::Add( const HPicture& _Hpic )
{
    for( u32 h_loop=0 ; h_loop<((HPicture&)_Hpic).Height() ; ++h_loop )
    {
	for( u32 w_loop=0 ; w_loop<((HPicture&)_Hpic).Width() ; ++w_loop )
	{
	    Add( ((HPicture&)_Hpic).Get( w_loop, h_loop ) );
	}
    }
}
//-------------------------------------------------------
Palette& ColorSpace::CreatePalette( u16 NumOfColors )
{
    if( NumOfColors+m_offset > 256 ) return m_pal;
    ColorCut clr_cut(0,32,0,32,0,32);
    std::list<ColorCut> cut_list;
    cut_list.push_back( clr_cut );
    ColorCut	cut_first;
    ColorCut	cut_next;
    u32 num_under,num_over;
    u32 min_count,max_count;
//	u16 always_create=0;
	m_pal.Resize(m_offset);

    while( 1 )
    {
	if( !cut_list.size() ) break;
	if( cut_list.size() + m_pal.Size() >= m_offset+NumOfColors ) break;

	clr_cut = *(cut_list.begin());
	cut_list.pop_front();

	set_use_num( clr_cut );
	narrow_color_cut( clr_cut );
	if( clr_cut.IsUnique() )
	{
	    if( m_offset )
	    {
		if( get_average( clr_cut ) == m_pal[0] ) continue;
	    }
	    m_pal.Add( get_average( clr_cut ) );
	    continue;
	}

	num_under = 0;
	num_over = 0;
	if( (clr_cut.RedRange() >= clr_cut.GreenRange())
	  &&(clr_cut.RedRange() >= clr_cut.BlueRange() ) )
	{
	    min_count = clr_cut.min_r;
	    max_count = clr_cut.max_r-1;
	    while( min_count < max_count )
	    {
		if( num_under <= num_over )
		{
		    num_under += m_use_red[min_count++];
		}
		else
		{
		    num_over += m_use_red[max_count--];
		}
	    }
	    cut_first = clr_cut;
	    cut_first.max_r = min_count;
	    cut_next = clr_cut;
	    cut_next.min_r = max_count;	// Same value as min_count
	    cut_list.push_back( cut_first );
	    cut_list.push_back( cut_next );
	    continue;
	}
	if( clr_cut.GreenRange() >= clr_cut.BlueRange() )
	{
	    min_count = clr_cut.min_g;
	    max_count = clr_cut.max_g-1;
	    while( min_count < max_count )
	    {
		if( num_under <= num_over )
		{
		    num_under += m_use_green[min_count++];
		}
		else
		{
		    num_over += m_use_green[max_count--];
		}
	    }
	    cut_first = clr_cut;
	    cut_first.max_g = min_count;
	    cut_next = clr_cut;
	    cut_next.min_g = max_count;	// Same value as min_count
	    cut_list.push_back( cut_first );
	    cut_list.push_back( cut_next );
	    continue;
	}
	min_count = clr_cut.min_b;
	max_count = clr_cut.max_b-1;
	while( min_count < max_count )
	{
	    if( num_under <= num_over )
	    {
		num_under += m_use_blue[min_count++];
	    }
	    else
	    {
		num_over += m_use_blue[max_count--];
	    }
	}
	cut_first = clr_cut;
	cut_first.max_b = min_count;
	cut_next = clr_cut;
	cut_next.min_b = max_count;	// Same value as min_count
	cut_list.push_back( cut_first );
	cut_list.push_back( cut_next );
	continue;
    }

    for( std::list<ColorCut>::iterator cut_it = cut_list.begin() ;
	cut_it != cut_list.end() ; ++cut_it )
    {
	if( m_pal[0] != get_average( *cut_it ) )
	    m_pal.Add( get_average( *cut_it ) );
    }
    m_pal.Resize(m_offset + NumOfColors);

    set_base_0();
    return m_pal;
}
//-------------------------------------------------------

__MAGBX__END


