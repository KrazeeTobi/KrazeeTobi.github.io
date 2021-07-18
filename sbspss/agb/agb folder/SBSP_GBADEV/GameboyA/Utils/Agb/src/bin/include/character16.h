//======================================================
//    character16.h                                           
//    Handles BG 16-color character class Character16.   
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_CHARACTER16_
#define	_AGB_CHARACTER16_

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <util.h>
#include <character.h>

__MAGBX__START

class Character16 : public Character
{

protected :

    virtual u8* create_out_buffer( void );

public :

    virtual u32 Size(){return 32;}
    virtual bool Output( std::ofstream &out );
    virtual bool Outtxt( std::ofstream &out );

};

__MAGBX__END

#endif	//  _AGB_CHARACTER16_

//
//
