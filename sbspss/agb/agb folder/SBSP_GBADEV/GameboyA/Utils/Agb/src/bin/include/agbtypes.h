//======================================================
//    agbtypes.h                                           
//    Basic class for handling AGB data and the definitions 
//    of basic functions.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGBTYPES_
#define	_AGBTYPES_
//-------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <filename.h>
//-------------------------------------------------------------
//	export library namespace defines
//
#define	__MAGBX		magbx
#define	__MAGBX__START namespace __MAGBX {
#define	__MAGBX__END    };
#define	__USING__MAGBX	using namespace __MAGBX;
//-------------------------------------------------------------
//	types
//
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef long s32;
typedef unsigned long u32;
typedef float f32;
typedef double f64;

//-------------------------------------------------------------
//	Rect class
//
class Rect
{
public :
    s32 top;
    s32 bottom;
    s32 left;
    s32 right;

    Rect( s32 _t=0 , s32 _b=0 , s32 _l=0 , s32 _r=0 ) :
	top( _t ) , bottom( _b ) , left( _l ) , right( _r ){}
    ~Rect(){}
    void Set( s32 _t , s32 _b , s32 _l , s32 _r )
    {
	top = _t;
	bottom = _b;
	left = _l;
	right = _r;
    }
    s32 Width(){return (right-left+1);}
    s32 Height(){return (bottom-top+1);}
};
//-------------------------------------------------------------
//	Basic object
//
__MAGBX__START

class AGBObject
{
protected :
    std::string m_name;
public :
    AGBObject(){}
    AGBObject( const std::string& name ) : m_name(name){}
    AGBObject( const char* name ) : m_name(name){}
    virtual ~AGBObject(){}

//
//
//  --------Input/output functions 
//
//
    virtual bool Output( std::ofstream& out ){return true;}
    virtual bool Output( const FileName& fname )
	{
	    std::ofstream out( ((FileName&)fname).c_str() ,
		    std::ios::out | std::ios::binary );
	    if( !out.is_open() ) return false;
	    bool ret_val = Output( out );
	    out.close();
	    return ret_val;
	}
    virtual bool Output( const std::string& fname )
	{
	    FileName fn( fname );
	    return Output( fn );
	}
    virtual bool Output( const char* fname )
	{
	    FileName fn( fname );
	    return Output( fn );
	}

    virtual bool Outtxt( std::ofstream& out ){return true;}
    virtual bool Outtxt( const FileName& fname )
	{
	    std::ofstream out( ((FileName&)fname).c_str() );
	    if( !out.is_open() ) return false;
	    bool ret_val = Outtxt( out );
	    out.close();
	    return ret_val;
	}
    virtual bool Outtxt( const std::string& fname )
	{
	    FileName fn( fname );
	    return Outtxt( fn );
	}
    virtual bool Outtxt( const char* fname )
	{
	    FileName fn( fname );
	    return Outtxt( fn );
	}

    virtual bool OutCSource( std::ofstream& out ){return true;}
    virtual bool OutCSource( const FileName& fname )
	{
	    std::ofstream out( ((FileName&)fname).c_str() );
	    if( !out.is_open() ) return false;
	    bool ret_val = OutCSource( out );
	    out.close();
	    return ret_val;
	}
    virtual bool OutCSource( const std::string& fname )
	{
	    FileName fn( fname );
	    return OutCSource( fn );
	}
    virtual bool OutCSource( const char* fname )
	{
	    FileName fn( fname );
	    return OutCSource( fn );
	}
    virtual bool Input( std::ifstream& in ){return true;}
    virtual bool Intxt( std::ifstream& in ){return true;}

    virtual void SetName( const std::string& name ){m_name = name;}
    virtual void SetName( const char* name ){m_name = name;}
    virtual const std::string& Name( void ){return m_name;}
    virtual void AddName( const std::string& name ){m_name += name;}
    virtual void AddName( const char* name ){m_name += name;}
};

__MAGBX__END
//-------------------------------------------------------------
#endif	//  _AGBTYPES_


