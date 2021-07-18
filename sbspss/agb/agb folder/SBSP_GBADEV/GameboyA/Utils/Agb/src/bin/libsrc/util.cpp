//======================================================
//    util.cpp
//    Group of useful miscellaneous functions.
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <Cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <util.h>
#include <agbtypes.h>

//
//  Output numerical value using binary
//
//----------------------------------------------------------------------
bool Output( std::ofstream &out , s8 data )
{
    if( false == out.is_open() ) return false;
    return !(!out.put( data ));
}
//----------------------------------------------------------------------
bool Output( std::ofstream &out , u8 data )
{
    return Output( out , (s8)data );
}
//----------------------------------------------------------------------
bool Output( std::ofstream &out , s16 data )
{
    if( true == Output( out , (s8)(s16)(data & 0x00ff) ) )
    {
	return Output( out ,(s8)(s16)((data & 0xff00)>>8) );
    }
    return false;
}
//----------------------------------------------------------------------
bool Output( std::ofstream &out , u16 data )
{
    return Output( out , (s16)data );
}
//----------------------------------------------------------------------
bool Output( std::ofstream &out , s32 data )
{
    if( true == Output( out , (s16)(s32)(data & 0x0000ffff) ) )
    {
	return Output( out , (s16)(s32)((data & 0xffff0000)>>16) );
    }
    return false;
}
//----------------------------------------------------------------------
bool Output( std::ofstream &out , u32 data )
{
    return Output( out,  (s32)data );
}
//
//  Input numerical value using binary
//
//----------------------------------------------------------------------
bool Input( std::ifstream &in , s8& data )
{
    if( false == in.is_open() ) return false;
    return !(!in.get( data ));
}
//----------------------------------------------------------------------
bool Input( std::ifstream &in , u8& data )
{
    return Input( in , (s8&)data );
}
//----------------------------------------------------------------------
bool Input( std::ifstream &in , s16& data )
{
    s8 input_data;
    if( true == Input( in , input_data ) )
    {
	data = (s16)input_data;
	if( false == Input( in, input_data ) ) return false;
	data |= (s16)input_data << 8;
    }
    return false;
}
//----------------------------------------------------------------------
bool Input( std::ifstream &in , u16& data )
{
    return Input( in , (s16&)data );
}
//----------------------------------------------------------------------
bool Input( std::ifstream &in , s32& data )
{
    s16 input_data;
    if( true == Input( in , input_data) )
    {
	data = (s32)input_data;
	if( false == Input( in , input_data ) ) return false;
	data |= (s32)input_data << 16;
    }
    return false;
}
//----------------------------------------------------------------------
bool Input( std::ifstream &in , u32& data )
{
    return Input( in, (s32&)data );
}
//----------------------------------------------------------------------
bool OuttxtString( std::ofstream& out , const std::string& _Str )
{
    if( false == out.is_open() ) return false;
    out << "\"" << ((std::string&)_Str).c_str() << "\"";
    return true;
}
//----------------------------------------------------------------------
void _itoa_c_hex( char val , char *str )
{
    if( NULL == str ) return;
    char tmp;
    tmp = (val & 0xf0) >> 4;
    str[0] = (tmp<10)? ('0'+tmp):('a'+tmp-10);
    tmp = (val & 0x0f);
    str[1] = (tmp<10)? ('0'+tmp):('a'+tmp-10);
    str[2] = '\0';
}
//----------------------------------------------------------------------
//
//  Obtain color from character string
//
__MAGBX::Color GetColorFromString( const char* str )
{
    __MAGBX::Color color(0,0,0);
    if( NULL == str ) return color;
    if( str[0] == '0' && str[1] == 'x' )
    {
	u32 tmp;
	tmp = (u32)strtol( &str[2], NULL , 16 );
	color.Set( (u8)(u32)((tmp & 0xff0000)>>16) ,
		    (u8)(u32)((tmp & 0xff00)>>8) ,
		    (u8)(u32)((tmp & 0xff)) );
	return color;
    }
    std::string clr_str(str);
    if( (str[0] >= '0' && str[0] <= '9') || str[0] == ',' )
    {
	s32 tmp_c[3];
	std::string tmp_c_str;
	std::string::iterator str_it = clr_str.begin();
	for( int i=0 ; i<3 ; ++i )
	{
	    tmp_c_str = "";
	    for( ; str_it != clr_str.end() ; ++str_it )
	    {
		if( *str_it == ',' )
		{
		    ++str_it;
		    break;
		}
		tmp_c_str += *str_it;
	    }
	    tmp_c[i] = atoi( tmp_c_str.c_str() );
	}
	color.Set( (u8)tmp_c[0], (u8)tmp_c[1], (u8)tmp_c[2] );
    }
    if( clr_str == "black" )
    {
	color.Set( 0,0,0 );
	return color;
    }
    if( clr_str == "white" )
    {
	color.Set( 255,255,255 );
	return color;
    }
    if( clr_str == "red" )
    {
	color.Set( 255,0,0 );
	return color;
    }
    if( clr_str == "green" )
    {
	color.Set( 0,255,0 );
	return color;
    }
    if( clr_str == "blue" )
    {
	color.Set( 0,0,255 );
	return color;
    }
    if( clr_str == "yellow" )
    {
	color.Set( 255,255,0 );
	return color;
    }
    if( clr_str == "purple" )
    {
	color.Set( 255,0,255 );
	return color;
    }
    if( clr_str == "cyan" )
    {
	color.Set( 0,255,255 );
	return color;
    }
    return color;
}
//----------------------------------------------------------------------

//
//
