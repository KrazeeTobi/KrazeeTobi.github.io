//======================================================
//    util.h
//    Useful miscellaneous functions.
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_UTIL_
#define	_AGB_UTIL_

#include <iostream>
#include <fstream>
#include <string>
#include <agbtypes.h>
#include <color.h>

//
//  Output values in binary
//
//--------------------------------------------------------------
bool Output( std::ofstream &out , s8 data );
bool Output( std::ofstream &out , u8 data );
bool Output( std::ofstream &out , s16 data );
bool Output( std::ofstream &out , u16 data );
bool Output( std::ofstream &out , s32 data );
bool Output( std::ofstream &out , u32 data );
bool Input( std::ifstream &out , s8& data );
bool Input( std::ifstream &out , u8& data );
bool Input( std::ifstream &out , s16& data );
bool Input( std::ifstream &out , u16& data );
bool Input( std::ifstream &out , s32& data );
bool Input( std::ifstream &out , u32& data );
void _itoa_c_hex( char val , char *str );
//--------------------------------------------------------------
//  Output array of values in binary.
//
template<class _Ty>
bool OutputArray( std::ofstream &out ,
		  _Ty *data_array , int Count )
{
    if( !out.is_open() ) return false;
    if( NULL == data_array ) return false;
    if( Count < 0 ) return false;
    for( int i=0 ; i<Count ; ++i )
    {
	if( !Output( out , data_array[i] ) ) return false;
    }
    return true;
}
template<class _Ty>
bool InputArray( std::ifstream &out ,
		  _Ty *data_array , int Count )
{
    if( !out.is_open() ) return false;
    if( NULL == data_array ) return false;
    if( Count < 0 ) return false;
    for( int i=0 ; i<Count ; ++i )
    {
	if( !Input( out , data_array[i] ) ) return false;
    }
    return true;
}
//--------------------------------------------------------------
//  Output values as hexadecimal strings.
//
template<class _Ty>
bool Outtxt( std::ofstream &out , _Ty data )
{
    if( !out.is_open() ) return false;
    char buf[3];
    std::string ty_str( "0x" );
    std::string tmp_str("");
    std::string num_str("");
    _Ty tmp = data;

	//  Replace values with strings.

    for( int i=0 ; i<sizeof(_Ty) ; ++i )
    {
	_itoa_c_hex( (tmp & 0xff) , buf );
	tmp_str = num_str;
	num_str = buf;
	num_str += tmp_str;
	tmp >>= 8;
    }
    ty_str += num_str;

	//  Output

    out << ty_str.c_str();

    return !(!out);
}
//--------------------------------------------------------------
//  Output array of values as strings.
//
template<class _Ty>
bool OuttxtArray( std::ofstream &out ,
		  _Ty *data_array , int Count )
{
    if( !out.is_open() ) return false;
    if( NULL == data_array ) return false;
    if( Count < 0 ) return false;
    for( int i=0 ; i<Count ; ++i )
    {
	if( (i != 0) && ((i & 0x7) == 0) ) out << std::endl;
	if( false == Outtxt( out , data_array[i] ) ) return false;
	out << " ,";
	if( !out ) return false;
	    //  Start a new line every 8 numbers.
	if( !out ) return false;
    }
    return true;
}
//--------------------------------------------------------------
bool OuttxtString( std::ofstream& out , const std::string& _Str );
template<class _Ty>
bool OuttxtValue( std::ofstream& out , _Ty _P )
{
    if( false == out.is_open() ) return false;
    if( sizeof(_Ty) == 1 )
    {
	out << (s16)_P;
    }
    else
    {
	out << _P;
    }
}
//----------------------------------------------------------------------

template<class _Ty> inline
_Ty& Min( const _Ty& _L , const _Ty& _R )
{
    return (_L < _R )? _L : _R ;
}

template<class _Ty> inline
_Ty& Max( const _Ty& _L , const _Ty& _R )
{
    return (_L > _R )? _L : _R ;
}

//
//  Get a color from a string.
//
__MAGBX::Color GetColorFromString( const char* str );


#endif	//  _AGB_UTIL_

//
//
