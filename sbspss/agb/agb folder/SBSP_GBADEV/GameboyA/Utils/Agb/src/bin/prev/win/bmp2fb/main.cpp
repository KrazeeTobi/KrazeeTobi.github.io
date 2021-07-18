//======================================================
//    main.cpp                                           
//    bmp2fb main routine                           
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

#define	BMP2FB_VERSION_STRING	"1.000"

const char* object_node_name="obj";
const char* palette_node_name="pal";
const char* character_node_name="chr";
const char* flipbook_node_name="fb";

//
//  Usage
//
void usage()
{
    std::cout << "bmp2fb.sh " << BMP2FB_VERSION_STRING << std::endl;
    std::cout << "[usage] bmp2fb (-whtr) (-o outfilename) filename" << std::endl;
    std::cout << "options" << std::endl;
    std::cout << "-w width    Width of one image" << std::endl;
    std::cout << "-h height   Height of one image" << std::endl;
    std::cout << "-t time     Frame count to next image" << std::endl;
    std::cout << "-r          Animate back and force" << std::endl;
    std::cout << "-c color    Set background color" << std::endl;
    exit( 0 );
}

//
//  Main function
//
int main( int argc , char **argv )
{
    __USING__MAGBX;

    std::string inname;
    std::list<std::string> str_list;
    std::string outname;
    u16 width = 0;
    u16 height = 0;
    u16 time = 1;
    u8  round_flag = 0;
    Color color;

	//  Process command line arguments

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'o' :
		    if( ++i >= argc )
		    {
			std::cout << "There is no file name after -o" << std::endl;
			usage();
		    }
		    outname = argv[i]; 
		    break;
		case 'r' :
		    round_flag = 1;
		    break;
		case 't' :
		    if( ++i >= argc )
		    {
			std::cout << "time is not specified with -t." << std::endl;
			usage();
		    }
		    time = atoi( argv[i] );
		    break;
		case 'c' :
		    if( ++i >= argc )
		    {
			std::cout << "Color is not specified after -b" << std::endl;
			usage();
		    }
		    color = GetColorFromString( argv[i] );
		    break;
		case 'w' :
		case 'W' :
		    if( ++i >= argc )
		    {
			std::cout << "-w Width is not specified with -W." << std::endl;
			usage();
		    }
		    width = atoi( argv[i] );
		    break;
		case 'h' :
		case 'H' :
		    if( ++i >= argc )
		    {
			usage();
		    }
		    height = atoi( argv[i] );
		    break;
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

	//  Error if no input file

    if( str_list.size() == 0 )
    {
	std::cout << "Input file is not specified." << std::endl;
	usage();
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
	    std::cout << "Cannot open output file" << std::endl;
	    exit(1);
	}
	out_ptr = &out_file;
    }
    u16 num_of_frame = 0;
    u16 max_time = 0;

    int count = 0;
    unsigned short bit_count;
    __MAGBX::Picture pic;
    std::list<std::string>::iterator str_list_it;
    for( str_list_it = str_list.begin() ;
	str_list_it != str_list.end() ;
	++str_list_it )
    {
	if( false == pic.LoadBmp( (*str_list_it) ) )
	{
	    std::cout << "\"" << (*str_list_it).c_str() << "\" cannot be read" << std::endl;
	    continue;
	}
	if( 0 == num_of_frame )
	{
	    bit_count = pic.BitCount();
	    if( width == 0 ) width = pic.Width();
	    if( height == 0 ) height = pic.Height();
	}
	++count;
	num_of_frame += (pic.Width() / width) * (pic.Height() / height );
    }

    if( 0 == count )
    {
	std::cout << "Cannot read input file." << std::endl;
	exit(1);
    }
    max_time = num_of_frame * time;
    if( round_flag )
    {
	if( num_of_frame > 2 )
	{
	    max_time += (num_of_frame - 2) * time;
	}
    }

	//	Processing 

    (*out_ptr) << "Header" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    Objects" << std::endl;
    (*out_ptr) << "\t\"" << object_node_name << "\"" << std::endl;
    (*out_ptr) << "\t;" << std::endl;
    (*out_ptr) << "    ObjectPalette" << std::endl;
    (*out_ptr) << "\t\"" << palette_node_name << "\";" << std::endl;
    (*out_ptr) << "    BGColor ";
    (*out_ptr) << (u16)color.Red() << " " << (u16)color.Green() << " ";
    (*out_ptr) << (u16)color.Blue() << ";" << std::endl;
    (*out_ptr) << "}" << std::endl;
    (*out_ptr) << std::endl;

    (*out_ptr) << "Object \"" << object_node_name <<"\"" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    MaxTime " << max_time << ";" << std::endl;
    (*out_ptr) << "    MaxState 1;" << std::endl;
    (*out_ptr) << "    Image \"" << character_node_name << "\";" << std::endl;
    (*out_ptr) << "    Children \"" << flipbook_node_name << "\";" << std::endl;
    (*out_ptr) << "}" << std::endl;
    (*out_ptr) << std::endl;

    (*out_ptr) << "Character \"" << character_node_name << "\"" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    Width " << width << ";" << std::endl;
    (*out_ptr) << "    Height " << height << ";" << std::endl;
    (*out_ptr) << "    Files";
    for( str_list_it = str_list.begin() ;
	str_list_it != str_list.end() ;
	++str_list_it )
    {
	(*out_ptr) << std::endl;
	(*out_ptr) << "\t\"" << *str_list_it << "\"";
    }
    (*out_ptr) << ";" << std::endl;
    (*out_ptr) << "}" << std::endl;
    (*out_ptr) << std::endl;

    (*out_ptr) << "Palette \"" << palette_node_name << "\"" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    NumOfColors " << (short)(1<<bit_count) << ";" << std::endl;
    (*out_ptr) << "    Files \"" << (*(str_list.begin())).c_str() << "\";" << std::endl;
    (*out_ptr) << "}" << std::endl;
    (*out_ptr) << std::endl;

    (*out_ptr) << "FlipBook \"" << flipbook_node_name << "\"" << std::endl;
    (*out_ptr) << "{" << std::endl;
    (*out_ptr) << "    Image \"" << character_node_name << "\";" << std::endl;
    (*out_ptr) << "    MaxTime " << max_time << ";" << std::endl;
    (*out_ptr) << "    Keys";
    u16 out_time = 0;
    for( i=0 ; i<(int)num_of_frame ; ++i )
    {
	(*out_ptr) << "\n\t" << out_time << " " << i << " 0";
	out_time += time;
    }
    if( round_flag )
    {
	for( i=(int)num_of_frame - 2 ; i>0 ; --i )
	{
	    (*out_ptr) << "\n\t" << out_time << " " << i << " 0";
	    out_time += time;
	}
    }
    (*out_ptr) << ";" << std::endl;
    (*out_ptr) << "}" << std::endl;

    return 0;
}



//
//
//
