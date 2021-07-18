//======================================================
//    map.h
//    Class to handle a map using AGB scaling BG. 
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_MAP_
#define	_AGB_MAP_

#include <agbtypes.h>
#include <character.h>
#include <maptextunit.h>
#include <filename.h>
#include <picture.h>
#include <palette.h>
#include <charset.h>
#include <maptextimage.h>
#include <mapsrimage.h>

__MAGBX__START

class Map : public AGBObject
{
public :
    typedef Character _Ch;
protected :
    CharSet *m_chset_ptr;
    Palette *m_palette_ptr;
    MapTextImage *m_mti_ptr;

    virtual bool is_alloc( void );
    virtual bool alloc(u32 width , u32 height);
    virtual void free(void);
    virtual bool is_character_over( void );
    virtual u32  get_bit_count(void);

    static const u32 m_scb_magic;

public :

    Map(u32 width=0 , u32 height=0) : m_chset_ptr(NULL) , m_palette_ptr(NULL) ,
	    m_mti_ptr(NULL)
	{
	    alloc(width , height);
	}

    virtual ~Map(){free();}

    virtual u32 Width(){return (NULL == m_mti_ptr)? 0 : m_mti_ptr->Width();}
    virtual u32 Height(){return (NULL == m_mti_ptr)? 0 : m_mti_ptr->Height();}
    virtual bool SetSize( u32 width , u32 height );
    virtual _Ch* CreateCharacter( void );
    virtual void DeleteCharacter( _Ch* char_ptr );
    virtual bool SetCharacter( u32 _x , u32 _y , const _Ch& _P );
    virtual bool SetCharacter( const _Ch& _P );
    virtual bool SetCharSet( const CharSet& _Chset );
    virtual bool SetUnit( u32 _x , u32 _y , const MapTextUnit& _P );
    virtual MapTextUnit GetUnit( u32 _x , u32 _y );
    virtual bool SetPalette( const Palette &_P );
    virtual void SetName( const char* name );
    virtual void SetName( const std::string& name );
    virtual u32 GetNumOfCharacters(void);
    virtual CharSet* GetCharSetPtr(void){return m_chset_ptr;}
    virtual Palette* GetPalettePtr(void){return m_palette_ptr;}
    virtual MapTextImage* GetMapImagePtr(void){return m_mti_ptr;}
    virtual bool OutCSource( std::ofstream& out );
    virtual bool OutputScb( std::ofstream& out );
    virtual u32 NumOfCharacters( void );
};

__MAGBX__END

#endif	//  _AGB_MAP_

//
//
