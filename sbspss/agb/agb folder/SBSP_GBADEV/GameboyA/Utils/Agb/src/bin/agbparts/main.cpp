//======================================================
//    main.cpp                                           
//    Divide bmp into parts.
//    Library executes decision of parts.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <agbtypes.h>
#include <filename.h>
#include <palette.h>
#include <picture.h>
#include <character.h>
#include <charset.h>
#include <char16set.h>
#include <char256set.h>

#define	AGBPARTS_VERSION_STRING	"1.000"

//
//	Usage
//
void usage()
{
    std::cout << "agbparts ver " << AGBPARTS_VERSION_STRING << std::endl;
    std::cout << "[usage] agbparts -o filename filename" << std::endl;
    exit( 0 );
}
//
//	Main function
//
int main( int argc , char **argv )
{
    __USING__MAGBX

    FileName inName , outName;
    u8 flip_flag = 0;

	//
	//  Process command line arguments
	//

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'o' :
		    if( ++i >= argc ) usage();
		    outName = argv[i];
		    break;
		case 'f' :
		    flip_flag = 1;
		    break;
		case 'h' :
		case 'H' :
		case '?' :
		    usage();
		    return 0;
		default :
		    usage();
		    return 0;
	    }
	    continue;
	}
	inName = argv[i];
    }

	//  An error if input/output filenames are not specified. 

    if( inName.c_string() == "" )
    {
	std::cout << "Input file is not specified." << std::endl;
	usage();
    }
    if( outName.c_string() == "" )
    {
	std::cout << "Output file is not specified." << std::endl;
	usage();
    }

	//
	//  Portion to be decided
	//

    Picture pic;
    std::ofstream out;
    std::ifstream in;
    Character *ch_ptr=NULL;
    CharSet *ch_set_ptr=NULL;
    Rect rc;
    int w_loop , h_loop;

	//  Read bmp into Picture class.   

    if(false == pic.LoadBmp( inName ) )
    {
	std::cout << "\"" << inName.c_str() << "\"";
	std::cout << ":File could not be opened." << std::endl;
	exit( 1 );
    }

	//  Acquire CharSet pointer.    

    if( pic.BitCount() == 4 )
    {
	ch_set_ptr = new Char16Set;
    }
    else
    {
	if( flip_flag )
	{
	    ch_set_ptr = new Char256Set;
	}
	else
	{
	    ch_set_ptr = new CharSet;
	}
    }
    if( NULL == ch_set_ptr )
    {
	std::cout << "Memory Over Flow" << std::endl;
	exit(1);
    }

	//  Create Character class from CharSet.   

    ch_ptr = ch_set_ptr->CreateCharacter();
    if( NULL == ch_ptr )
    {
	std::cout << "Memory Over Flow" << std::endl;
	exit( 1 );
    }

	//  Divide .bmp and register as characters.

    for( h_loop = 0 ; h_loop < pic.Height() ; h_loop += 8 )
    {
	for( w_loop = 0 ; w_loop < pic.Width() ; w_loop += 8 )
	{
	    rc.Set( h_loop , h_loop+7 , w_loop , w_loop+7 );
	    ch_ptr->Set( pic.GetImage() , 0 , 0 , rc );
	    if( false == ch_set_ptr->Add( *ch_ptr ) )
	    {
		std::cout << "Characters could not be added." << std::endl;
		exit( 1 );
	    }
	}
    }

	//  Use palette of input file. 

    ch_set_ptr->SetPalette( pic.GetPalette() );

	//  Save output filename.  

    if( false == ch_set_ptr->SaveBmp( outName ) )
    {
	std::cout << "\"" << outName.c_str() << "\"";
	std::cout << ":Could not be written to file." << std::endl;
	exit( 1 );
    }
    std::cout << "The number of characters used is " ;
    std::cout << ch_set_ptr->Size() << "." << std::endl;
    return 0;
}

