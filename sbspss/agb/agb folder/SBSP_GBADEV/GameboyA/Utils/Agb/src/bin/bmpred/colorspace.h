//
//
//
//
//

#ifndef	__COLOR_SPACE_H__
#define	__COLOR_SPACE_H__

#include <agbtypes.h>
#include <palette.h>
#include <hpicture.h>
#include <color.h>
#include <Cstring>

__MAGBX__START

class ColorCut
{
public :
    u8	min_r;
    u8	max_r;
    u8	min_g;
    u8	max_g;
    u8	min_b;
    u8	max_b;
    ColorCut( u8 n_r=0,u8 x_r=1,u8 n_g=0,u8 x_g=1,u8 n_b=0,u8 x_b=1 )
    {
	Set( n_r, x_r, n_g, x_g, n_b, x_b );
    }
    ~ColorCut(){}
    void Set( u8 n_r,u8 x_r,u8 n_g,u8 x_g,u8 n_b,u8 x_b )
    {
	min_r = n_r;
	max_r = x_r;
	min_g = n_g;
	max_g = x_g;
	min_b = n_b;
	max_b = x_b;
    }
    u8 RedRange(void){return (max_r > min_r) ? ((max_r-min_r-1)) : 0;}
    u8 GreenRange(void){return (max_g > min_g) ? ((max_g-min_g-1)) : 0;}
    u8 BlueRange(void){return (max_b > min_b) ? ((max_b-min_b-1)) : 0;}
    bool IsUnique( void )
    {
	return ( RedRange()==0 && GreenRange()==0 && BlueRange()==0 );
    }
};

class ColorSpace
{
protected :
    u32 m_use_buffer[32768];
    u32 m_use_red[32];
    u32 m_use_green[32];
    u32 m_use_blue[32];
    Palette m_pal;
    Color m_base;
    u8  m_use_base_flag;
    u16 m_offset;

    u16 get_array_number( u8 _r, u8 _g, u8 _b );

    u32 get_use_num( u8 _r, u8 _g, u8 _b );
    u32 get_use_num( const ColorCut& _cc );
    void set_use_num( const ColorCut& _cc );
    void narrow_color_cut( ColorCut& _cc );
    Color get_average( const ColorCut& _cc );
    void set_base_0( void );
public :
    ColorSpace(void) : m_pal(0), m_use_base_flag(0), m_offset(0)
	{::memset( m_use_buffer,0,sizeof(m_use_buffer) );}
    ~ColorSpace(){}

    void Add( u8 _r, u8 _g, u8 _b);
    void Add( const Color& _C );
    void Add( const HPicture& _Hpic );
	void SetOffset( u16 _offset ){m_offset = _offset;}
    Palette& CreatePalette( u16 NumOfColors );
    Palette& GetPalette( void ){return m_pal;}

    void SetBase( const Color& _C ){m_base = _C;m_use_base_flag=1;}

};

__MAGBX__END

#endif	//  __COLOR_SPACE_H__

//
//
