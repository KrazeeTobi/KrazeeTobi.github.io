//======================================================
//    char256set.h                                           
//    BG character set class Char256Set.
//    Character set to be handled for 256-color text mode.  
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_CHAR256SET_
#define	_AGB_CHAR256SET_

#include <list>
#include <fstream>
#include <iostream>
#include <agbtypes.h>
#include <character.h>
#include <maptextunit.h>
#include <charset.h>
#include <char16set.h>

__MAGBX__START

class Char256Set : public Char16Set
{
public :
    typedef MapTextUnit Unit;
    typedef std::list<Character*> ch_list;

    typedef Char256Set _Myt;
    typedef Character _Ty;

protected :

public :

    Char256Set( void ) : Char16Set(){}
    Char256Set( const _Myt& _X ){Set(_X);}

    virtual _Ty *CreateCharacter( void );
    virtual bool OutCSource( std::ofstream& out );

};

__MAGBX__END

#endif	//  _AGB_CHAR256SET_

//
//
