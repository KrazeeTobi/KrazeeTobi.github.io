//======================================================
//    main.c                                           
//    Main Part of bmp2map.
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
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
#include <map.h>
#include <map16.h>
#include <map256.h>

#define	BMP2MAP_VERSION_STRING	"1.000"

//
//  Usage
//

void usage()
{
    std::cout << "bmp2map ver " << BMP2MAP_VERSION_STRING << std::endl;
    std::cout << "[usage] bmp2map -o outfilename filename" << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "\t-f            Flip ON" << std::endl;
    std::cout << "\t-p palette    Use palette. Specify palette number" << std::endl;
    std::cout << "\t-c filename   Specify pattern character bitmap" << std::endl;
    std::cout << "\t-b            Output in binary" << std::endl;
    std::cout << "\t-B            Output parts image at binary output" << std::endl;
    std::cout << "\t-P            Output palette image at binary output" << std::endl;
    std::cout << "\t-M            Output map image at binary output" << std::endl;
    exit( 0 );
}

int main( int argc , char **argv )
{
    __USING__MAGBX;

    FileName inName , outName;
    FileName patName;
    u8 pattern_file_flag = 0;
    u8 flip_flag = 0;
    u8 binary_flag = 0;
    u8 palette_number = 0;
    u8 palette_out_flag = 0;
    u8 map_out_flag = 0;
    u8 bitmap_out_flag = 0;
    u32 num_of_characters = 0;
    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'b' :
		    binary_flag = 1;
		    break;
		case 'B' :
		    bitmap_out_flag = 1;
		    break;
		case 'P' :
		    palette_out_flag = 1;
		    break;
		case 'M' :
		    map_out_flag = 1;
		    break;
		case 'c' :
		    if( ++i >= argc ) usage();
		    patName = argv[i];
		    pattern_file_flag = 1;
		    break;
		case 'o' :
		    if( ++i >= argc ) usage();
		    outName = argv[i];
		    break;
		case 'f' :
		    flip_flag = 1;
		    break;
		case 'p' :
		    if( ++i >= argc ) usage();
		    palette_number = (u8)atoi(argv[i]);
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
    if( inName.c_string() == "" )
    {
	std::cerr << "Input file is not specified" << std::endl;
	usage();
    }
    Picture pic;
    std::ofstream out;
    std::ifstream in;
    Map *map_ptr=NULL;
    Character *ch_ptr=NULL;
    CharSet *chset_ptr=NULL;
    Rect rc;
    int w_loop , h_loop;

    if(false == pic.LoadBmp( inName ) )
    {
	std::cout << "\"" << inName.c_str() << "\"";
	std::cout << ":Unable to open file" << std::endl;
	exit( 1 );
    }
	//  Obtain map pointer
    if( pic.BitCount() == 4 )
    {
	chset_ptr = new Char16Set;
	map_ptr = new Map16(pic.Width()/8 , pic.Height()/8);
	if( NULL != map_ptr )
	    ((Map16*)map_ptr)->SetPaletteNumber(palette_number);
    }
    else
    {
	if( flip_flag )
	{
	    chset_ptr = new Char256Set;
	    map_ptr = new Map256(pic.Width()/8 , pic.Height()/8);
	}
	else
	{
	    chset_ptr = new CharSet;
	    map_ptr = new Map(pic.Width()/8 , pic.Height()/8);
	}
    }
    if( NULL == map_ptr || NULL == chset_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	exit(1);
    }
	//  Set map
    ch_ptr = map_ptr->CreateCharacter();
    if( NULL == ch_ptr )
    {
	std::cerr << "Memory Over Flow" << std::endl;
	exit( 1 );
    }
    if( pattern_file_flag )
    {
	Picture pat_pic;
	if( false == pat_pic.LoadBmp( patName ) )
	{
	    std::cerr << "Unble to read pattern file" << std::endl;
	    exit( 1 );
	}
	std::cout << "Pattern File \"" << patName.c_str();
	std::cout << "\" reading complete" << std::endl;
	for( h_loop = 0 ; h_loop < pat_pic.Height() ; h_loop += 8 )
	{
	    for( w_loop = 0 ; w_loop < pat_pic.Width() ; w_loop += 8 )
	    {
		rc.top = h_loop;
		rc.bottom = rc.top + 7;
		rc.left = w_loop;
		rc.right = rc.left + 7;

		ch_ptr->Set( pat_pic.GetImage() , 0 , 0 , rc );
		if( false == chset_ptr->AddNoCheck( *ch_ptr ) )
		{
		    std::cout << "Unable to add characters" << std::endl;
		    exit( 1 );
		}
	    }
	}
	map_ptr->SetCharSet( *chset_ptr );
	num_of_characters = map_ptr->GetNumOfCharacters();
    }
    delete chset_ptr;
    map_ptr->SetPalette( pic.GetPalette() );
    map_ptr->SetName( inName.base().c_str() );
    for( h_loop = 0 ; h_loop < pic.Height() ; h_loop += 8 )
    {
	for( w_loop = 0 ; w_loop < pic.Width() ; w_loop += 8 )
	{
	    rc.top = h_loop;
	    rc.bottom = rc.top + 7;
	    rc.left = w_loop;
	    rc.right = rc.left + 7;

	    ch_ptr->Set( pic.GetImage() , 0 , 0 , rc );
	    if( false == map_ptr->SetCharacter( w_loop/8 , h_loop/8 , *ch_ptr ) )
	    {
		std::cout << "Unable to add characters" << std::endl;
		exit( 1 );
	    }
	}
    }
    map_ptr->DeleteCharacter( ch_ptr );

    if( outName.base() == "" ) outName.set_base( inName.base() );
    if( binary_flag )
    {
	if( bitmap_out_flag == 0 && palette_out_flag == 0 )
	    map_out_flag = 1;
	if( map_out_flag )
	{
	    outName.set_extension( "mpb" );
	    if( NULL == map_ptr->GetMapImagePtr() )
	    {
		std::cout << "Unable to create map" << std::endl;
		exit( 1 );
	    }
	    if( false == ((AGBObject*)map_ptr->GetMapImagePtr())->Output( outName ) )
	    {
		std::cout << "\"" << outName.c_str() << "\"";
		std::cout << ":Unable to write in file" << std::endl;
		exit( 1 );
	    }
	}
	if( palette_out_flag )
	{
	    outName.set_extension( "plb" );
	    if( NULL == map_ptr->GetPalettePtr() )
	    {
		std::cout << "Unable to create palette" << std::endl;
		exit( 1 );
	    }
	    if( false == ((AGBObject*)map_ptr->GetPalettePtr())->Output( outName ) )
	    {
		std::cout << "\"" << outName.c_str() << "\"";
		std::cout << ":Unable to write in file" << std::endl;
		exit( 1 );
	    }
	}
	if( bitmap_out_flag )
	{
	    outName.set_extension( "imb" );
	    if( NULL == map_ptr->GetCharSetPtr() )
	    {
		std::cout << "Unable to create palette" << std::endl;
		exit( 1 );
	    }
	    if( false == ((AGBObject*)map_ptr->GetCharSetPtr())->Output( outName ) )
	    {
		std::cout << "\"" << outName.c_str() << "\"";
		std::cout << ":Unable to write in file" << std::endl;
		exit( 1 );
	    }
	}
    }
    else
    {
	if( outName.extension() == "" ) outName.set_extension( "c" );
	if( false == ((AGBObject*)map_ptr)->OutCSource( outName ) )
	{
	    std::cout << "\"" << outName.c_str() << "\"";
	    std::cout << ":Unable to write in file" << std::endl;
	    exit( 1 );
	}
    }
    if( pattern_file_flag )
    {
	if( num_of_characters < map_ptr->GetNumOfCharacters() )
	{
	    std::cout << "Pattern ";
	    std::cout << map_ptr->GetNumOfCharacters() - num_of_characters;
	    std::cout << " was added " << std::endl;
	}
    }
    std::cout << "Number of patterns is " << map_ptr->GetNumOfCharacters() << std::endl;
//   std::cout << " are ..." << std::endl;
    return 0;
}
