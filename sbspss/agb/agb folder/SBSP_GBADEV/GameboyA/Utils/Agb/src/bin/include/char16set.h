//======================================================
//    char16set.h                                           
//    BG character set class Char16Set.
//    Character set to be handled for 16-color text mode. 
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_CHAR16SET_
#define	_AGB_CHAR16SET_

#include <list>
#include <fstream>
#include <iostream>
#include <agbtypes.h>
#include <character16.h>
#include <maptextunit.h>
#include <charset.h>
#include <picture.h>
#include <palette.h>

__MAGBX__START

class Char16Set : public CharSet
{
public :
    typedef Character _Ty;
    typedef MapTextUnit _Ut;
    typedef Char16Set _Myt;

protected :

public :

    Char16Set( void ) : CharSet(){}
    Char16Set( const _Myt& _X ){Set(_X);}
    virtual _Ty *CreateCharacter( void );
    virtual bool Unit( _Ut& _ut , const _Ty& _P );
    virtual bool OutCSource( std::ofstream &out );

};

__MAGBX__END

#endif	//  _AGB_CHAR16SET_

//
//
