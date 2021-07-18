//======================================================
//    palette.cpp
//    Class for AGB palette
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <color.h>
#include <image.h>
#include <palette.h>

__MAGBX__START

//----------------------------------------------------------------------
u16* Palette::create_out_buffer( void )
{
    u16 *ret_buffer = new u16[NumOfColors()];
    if( NULL == ret_buffer ) return NULL;
    for( int i=0 ; i<NumOfColors() ; ++i )
    {
	ret_buffer[i] = ((Color&)Get(i)).Get();
    }
    return ret_buffer;
}
//----------------------------------------------------------------------
void Palette::delete_out_buffer( u16* out_buffer )
{
    delete[] out_buffer;
}
//----------------------------------------------------------------------
void Palette::Trim( void )
{
    if( !Size() ) return;
    u32 i;
    i = Size()-1;
    Color clr = Get(i);
    while( i > 0 )
    {
	if( clr != Get(--i) ) break;
    }
    ++i;
    for( u32 j=0 ; j<i ; ++j )
    {
	if( clr == Get( j ) ) break;
    }
    if( j != i )
    {
	--i;
    }
    else
    {
	if( clr == Get(i) ) --i;
    }
    Resize( i );
}
//----------------------------------------------------------------------
const Color& Palette::Get( int _N )
{
    if( (_N < 0) || (_N>=NumOfColors()) ) return m_dummy;
    return m_image.Get( _N % 16 , _N / 16 );
}
//----------------------------------------------------------------------
const Color& Palette::operator[](int _N)
{
    return Get( _N );
}
//----------------------------------------------------------------------
void Palette::Set( const Color& _P , int _N )
{
    if( (_N < 0) || (((_N+15)>>4) > m_image.Height()) ) return;
    m_image.Set(_P , _N % 16 , _N / 16);
}
//----------------------------------------------------------------------
void Palette::Set(const Palette& _X , int _N)
{
    u32 num_tmp = (u32)_N + ((Palette&)_X).Size();
    if( num_tmp > Size() )
    {
	if( false == Resize( num_tmp ) ) return;
    }
    m_image.Set( ((Palette&)_X).GetImage() , _N % 16 , _N / 16);
}
//----------------------------------------------------------------------
Palette& Palette::operator=(const Palette& _X)
{
    if( this != &_X )
    {
	u32 num_of_colors = ((Palette&)_X).NumOfColors();
	if( NumOfColors() != num_of_colors )
	    Resize( num_of_colors );
	Set( _X );
    }
    return (*this);
}
//----------------------------------------------------------------------
int Palette::Add( const Color& _P )
{
    u32 num_of_colors = m_num_of_colors;
    if( false == Resize(num_of_colors+1) ) return -1;
    Set( _P ,num_of_colors );
    return (int)num_of_colors;
}

//----------------------------------------------------------------------
int Palette::Add( const Palette& _X )
{
    u32 num_of_colors = (Size()+0xf)&~0xf ;
    u32 add_num = ((Palette&)_X).NumOfColors();
    if( false == Resize( num_of_colors + add_num ) )
	return -1;
    Set( _X , num_of_colors );
    return num_of_colors;
}
//----------------------------------------------------------------------
bool Palette::Resize( int _N )
{
    m_num_of_colors = _N;
    if( ((_N+0xf)>>4) == m_image.Height() ) return true;
    return m_image.Resize( 16, (_N+0xf) >> 4 );
}
//----------------------------------------------------------------------
bool Palette::Output( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u16* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    bool ret_val = ::OutputArray( out, out_buffer, (int)NumOfColors() );
    delete_out_buffer( out_buffer );
    return ret_val;
}
//----------------------------------------------------------------------
bool Palette::Outtxt( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u16* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    bool ret_val = ::OuttxtArray( out, out_buffer, (int)Size() );
    delete_out_buffer( out_buffer );
    return ret_val;
}
//----------------------------------------------------------------------
bool Palette::OutCSource( std::ofstream &out )
{
    if( !out.is_open() ) return false;
    u16* out_buffer = create_out_buffer();
    if( NULL == out_buffer ) return false;
    out << "const u16 " << m_name.c_str() << "_Palette[";
    out << Size() << "] = {" << std::endl;
    bool ret_val = ::OuttxtArray( out, out_buffer, (int)Size() );
    if( ret_val == true )
    {
	out << std::endl << "};" << std::endl;
    }
    delete_out_buffer( out_buffer );
    return ret_val;
}
//----------------------------------------------------------------------
bool Palette::LoadACT( const FileName& file_name )
{
    std::fstream f_stream;
    unsigned char Buffer[256*3];
    f_stream.open( file_name.c_str() , std::ios::in|std::ios::binary );
    if( !f_stream.is_open() )
    {
	std::cerr << "\"" << file_name.c_str() << "\"";
	std::cerr << "  Unable to open file" << std::endl;
	return false;
    }
    if( !f_stream.read( (char*)Buffer , 256*3 ) )
    {
	f_stream.close();
	return false;
    }
    Color color;
    for( int i=0 ; i<Size() ; ++i )
    {
	color.Set( Buffer[i*3], Buffer[i*3+1], Buffer[i*3+2] );
	Set( color , i );
    }
    return true;
}
//----------------------------------------------------------------------
bool Palette::SaveACT( const FileName& file_name )
{
    std::fstream f_stream;
    unsigned char Buffer[256*3];

    for( int i=0 ; i<Size() ; ++i )
    {
	if( i >= 256 ) break;
	Buffer[i*3] = ((Color&)Get(i)).Red();
	Buffer[i*3+1] = ((Color&)Get(i)).Green();
	Buffer[i*3+2] = ((Color&)Get(i)).Blue();
    }

    for( ; i<256 ; ++i )
    {
	Buffer[i*3] = 0;
	Buffer[i*3+1] = 0;
	Buffer[i*3+2] = 0;
    }
    f_stream.open( file_name.c_str() , std::ios::out|std::ios::binary );
    if( !f_stream.is_open() )
    {
	std::cerr << "\"" << file_name.c_str() << "\"";
	std::cerr << "  Unable to open file" << std::endl;
	return false;
    }
    if( !f_stream.write( (char*)Buffer , 256*3 ) )
    {
	f_stream.close();
	return false;
    }
    return true;
}
//----------------------------------------------------------------------

__MAGBX__END

//
//
