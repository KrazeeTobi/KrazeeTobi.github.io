//======================================================
//    main.cpp                                           
//    bmp2prev Main routine                          
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <Cstdlib>
#include <Cstdio>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <agbtypes.h>
#include <filename.h>
#include <picture.h>
#include <color.h>
#include <util.h>

#define	BMP2PREV_VERSION_STRING	"1.000"

const char* object_node_name="obj";
const char* palette_node_name="pal";
const char* character_node_name="chr";

//
//  Usage
//
void usage()
{
    std::cout << "bmp2bin prev " << BMP2PREV_VERSION_STRING << std::endl;
    std::cout << "[usage] bmp2prev (-o outfilename) filename" << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "-o outfilename  Specify output file name" << std::endl;
    std::cout << "-c bg_color  Specify background color " << std::endl;
    exit( 0 );
}

//
//  main function
//
int main( int argc , char **argv )
{
    __USING__MAGBX;

    std::string inname;
    std::list<std::string> str_list;
    std::string outname;
    Color color;

	//  Option decision

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'o' :
		    if( ++i >= argc )
		    {
			std::cout << "there is no file name after -o" << std::endl;
			usage();
		    }
		    outname = argv[i]; 
		    break;
		case 'c' :
		    if( ++i >= argc )
		    {
			std::cout << "Color is not specified after -c." << std::endl;
			usage();
		    }
		    color = GetColorFromString( argv[i] );
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
	inname = argv[i];
	str_list.push_back( inname );
    }

	//  An error in case there is no input file.

    if( str_list.size() == 0 )
    {
	std::cout << "Input file is not specified." << std::endl;
	exit(1);
    }
    std::ostream* out_ptr;
    std::ofstream out_file;
    if( outname.length() == 0 )
    {
	out_ptr = &std::cout;
    }
    else
    {
	out_file.open( outname.c_str() );
	if( false == out_file.is_open() )
	{
	    std::cout << "Cannot open output file." << std::endl;
	    exit(1);
	}
	out_ptr = &out_file;
    }

    int count = 0;
    unsigned short* width_ptr = new unsigned short[str_list.size()];
    unsigned short* height_ptr = new unsigned short[str_list.size()];
    std::string* fname_ptr = new std::string[str_list.size()];
    unsigned short bit_count;
    if( NULL ==width_ptr || NULL == height_ptr || NULL == fname_ptr )
    {
	std::cout << "Memory shortage" << std::endl;
	exit(1);
    }
    Picture pic;
    std::list<std::string>::iterator str_list_it;
    for( str_list_it = str_list.begin() ;
	str_list_it != str_list.end() ;
	++str_list_it )
    {
	if( false == pic.LoadBmp( (*str_list_it) ) )
	{
	    std::cout << "\"" << (*str_list_it).c_str() << "\" cannot be read in" << std::endl;
	    continue;
	}
	if( 0 == count )
	{
	    bit_count = pic.BitCount();
	}
	width_ptr[count] = pic.Width();
	height_ptr[count] = pic.Height();
	fname_ptr[count] = (*str_list_it);
	++count;
    }

    if( 0 == count )
    {
	std::cout << "Cannot read input file." << std::endl;
	delete[] width_ptr;
	delete[] height_ptr;
	delete[] fname_ptr;
	exit(1);
    }

	//	Processing part

    (*out_ptr) << "Header" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    Objects" << std::endl;
    for( i=0 ; i<count ; ++i )
    {
	(*out_ptr) << "\t\"" << object_node_name << i << "\"" << std::endl;
    }
    (*out_ptr) << "\t;" << std::endl;
    (*out_ptr) << "    ObjectPalette" << std::endl;
    (*out_ptr) << "\t\"" << palette_node_name << "\";" << std::endl;
    (*out_ptr) << "    BGColor ";
    (*out_ptr) << (u16)color.Red() << " " << (u16)color.Green() << " ";
    (*out_ptr) << (u16)color.Blue() << ";" << std::endl;
    (*out_ptr) << "}" << std::endl;
    (*out_ptr) << std::endl;
    for( i=0 ; i<count ; ++i )
    {
	(*out_ptr) << "Object \"" << object_node_name << i << "\"" << std::endl;
	(*out_ptr) << "{" << std::endl;
	(*out_ptr) << "    MaxTime 0;" << std::endl;
	(*out_ptr) << "    MaxState 0;" << std::endl;
	(*out_ptr) << "    Image \"" << character_node_name << i << "\";" << std::endl;
	(*out_ptr) << "}" << std::endl;
	(*out_ptr) << std::endl;
	(*out_ptr) << "Character \"" << character_node_name << i << "\"" << std::endl;
	(*out_ptr) << "{" << std::endl;
	(*out_ptr) << "    Width " << width_ptr[i] << ";" << std::endl;
	(*out_ptr) << "    Height " << height_ptr[i] << ";" << std::endl;
	(*out_ptr) << "    Files \"" << fname_ptr[i].c_str() << "\";" << std::endl;
	(*out_ptr) << "}" << std::endl;
	(*out_ptr) << std::endl;
    }
    (*out_ptr) << "Palette \"" << palette_node_name << "\"" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    NumOfColors " << (short)(1<<bit_count) << ";" << std::endl;
    (*out_ptr) << "    Files \"" << fname_ptr[0].c_str() << "\";" << std::endl;
    (*out_ptr) << "}" << std::endl;

    delete[] width_ptr;
    delete[] height_ptr;
    delete[] fname_ptr;

    return 0;
}



//
//
//
