//======================================================
//    charset.h                                           
//    BG character set class CharSet.
//    Character set to be handled for BG 256-color scaling 
//    screen mode.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_CHARSET_
#define	_AGB_CHARSET_

#include <list>
#include <fstream>
#include <iostream>
#include <agbtypes.h>
#include <character.h>
#include <maptextunit.h>
#include <filename.h>
#include <picture.h>
#include <palette.h>

__MAGBX__START

class CharSet : public AGBObject
{
public :
    typedef std::list<Character*> ch_list;
    typedef Character _Ty;
    typedef MapTextUnit _Ut;

protected :
    ch_list m_char_list;
    Palette m_palette;

    virtual bool true_add( _Ut &_ut , const _Ty& _P );
    virtual bool true_add( const _Ty& _P );

public :
    typedef CharSet _Myt;

    CharSet( void ){}
    CharSet( const _Myt& _X ){Set(_X);}
    virtual ~CharSet(){Clear();}

    virtual void Set(const _Myt& _X );

    virtual bool Unit( _Ut& _ut , const _Ty& _P );
    virtual _Ty *CreateCharacter( void ){return new Character;}
    virtual bool Add( _Ut& _ut , const _Ty& _P );
    virtual bool Add( const _Ty& _P );
    virtual bool Add( const _Myt& _X );
    virtual bool AddNoCheck( const _Ty& _P );
    virtual void SetPalette( const Palette& _Pal ){m_palette = _Pal;}
    virtual Palette& Palette( void ){return m_palette;}
    virtual const ch_list& c_list(){return m_char_list;}
    virtual u32 Size(){return m_char_list.size();}
    virtual void Clear( void );
    virtual u32 GetNumOfCharacters( void ){return (u32)m_char_list.size();}

    virtual bool Output( std::ofstream &out );
    virtual bool Outtxt( std::ofstream &out );
    virtual bool OutCSource( std::ofstream &out );
    virtual bool SaveBmp( const FileName& fname );
};

__MAGBX__END

#endif	//  _AGB_CHARSET_

//
//
