//======================================================
//    main.cpp                                           
//    Main part of bin2h
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#include <Cstdlib>
#include <Cstdio>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <agbtypes.h>
#include <filename.h>

#define	BIN2H_VERSION_STRING	"1.000"

//
//  Usage
//
void usage()
{
    std::cout << "bin2h ver " << BIN2H_VERSION_STRING << std::endl;
    std::cout << "[usage] bin2h -o out_filename filename filename ..." << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "  -o out_filename    Set output file name" << std::endl;
    exit( 0 );
}

unsigned long get_file_size( const char* file_name )
{
    if( NULL == file_name ) return 0;
    std::ifstream in;
    in.open( file_name, std::ios::in | std::ios::binary );
    if( !in ) return 0;
    in.seekg( 0 , std::ios::end );
    unsigned long file_size;
    file_size = (unsigned long)in.tellg();
    in.close();
    return file_size;
}

//
//  Main function
//
int main( int argc , char **argv )
{
    std::list<FileName> fname_list;
    FileName out_fname;
    FileName tmp;

	//  Process command line arguments

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'o' :
		    if( ++i >= argc ) usage();
		    out_fname = argv[i];
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
	tmp = argv[i];
	fname_list.push_back( tmp );
    }

	//  Error if no input file.

    if( fname_list.size() == 0 )
    {
	std::cout << "Input file is not specified." << std::endl;
	exit(1);
    }

	//  Processing

    std::ofstream out;
    std::ifstream in;
    FileName tmp_fname;
    out_fname.set_extension( "h" );

    out.open( out_fname.c_str() );
    if( !out )
    {
	std::cout << "Could not open output file" << std::endl;
	exit(1);
    }

    out << "#ifndef ";
    out << "_" << out_fname.base().c_str() << "_";
    out << out_fname.extension().c_str() << std::endl;
    out << "#define ";
    out << "_" << out_fname.base().c_str() << "_";
    out << out_fname.extension().c_str() << std::endl;
    out << std::endl;
    std::list<FileName>::iterator fname_list_it;
    for(fname_list_it = fname_list.begin() ;
	fname_list_it != fname_list.end() ;
	++fname_list_it )
    {
	tmp_fname = *fname_list_it;
	out << "extern char ";
	out << "binary_" << tmp_fname.base().c_str();
	out << "_" << tmp_fname.extension().c_str() << "_start";
	out << "[" << get_file_size(tmp_fname.c_str()) << "];" << std::endl;

    }
    out << std::endl;
    out << "#endif /* ";
    out << "_" << out_fname.base().c_str() << "_";
    out << out_fname.extension().c_str() << " */" << std::endl;
    out.close();
    return 0;
}
