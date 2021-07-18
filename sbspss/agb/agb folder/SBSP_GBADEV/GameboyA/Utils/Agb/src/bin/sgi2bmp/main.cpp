//======================================================
//    main.cpp                                           
//    sgi2bmp main routine                           
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <Cstdlib>
#include <Cstdio>
#include <iostream>
#include <list>
#include <string>
#include <filename.h>
#include <color.h>
#include <util.h>
#include <hpicture.h>
#include "pic_create.h"

#define	SGI2BMP_VERSION_STRING	"1.000"

void usage()
{
    std::cout << "sgi2bmp ver " << SGI2BMP_VERSION_STRING << std::endl;
    std::cout << "[usage] sgi2bmp filename ..." << std::endl;
    std::cout << "   -t Set threshold of transparency alpha" << std::endl;
    std::cout << "   -c Specify the color to paint out the portion that is extracted by alpha." << std::endl;
    exit( 0 );
}

int main( int argc , char **argv )
{
    __USING__MAGBX;

    std::list<FileName> fname_list;
    FileName tmp;
    char trans_flag=0;
    short transp=0;
    Color color;
    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'h' :
		case 'H' :
		case '?' :
		    usage();
		    return 0;
		case 't' :
		    if( ++i >= argc ) usage();
		    transp = atoi( argv[i] );
		    trans_flag = 1;
		    break;
		case 'c' :
		    if( ++i >= argc ) usage();
		    color = GetColorFromString( argv[i] );
		    trans_flag = 1;
		    break;
		default :
		    usage();
		    return 0;
	    }
	    continue;
	}
	tmp.set(argv[i]);
	fname_list.push_back( tmp );
    }
    if( fname_list.size() == 0 )
    {
	std::cout << "Input file is not specified." << std::endl;
	usage();
    }
    std::list<FileName>::iterator fname_list_it;
    std::string tmp_base;
    std::string base_base;
    FileName tmp_fname;
    HPicture* pic_ptr;
    for(fname_list_it = fname_list.begin() ;
	fname_list_it != fname_list.end() ;
	++fname_list_it )
    {
	pic_ptr = sgiImageLoad( *fname_list_it , trans_flag , transp , color );
	if( NULL == pic_ptr )
	{
	    std::cout << "\"" << (*fname_list_it).c_str() << "\"";
	    std::cout << ":Failed to read file." << std::endl;
	    continue;
	}
	tmp_fname = *fname_list_it;
	tmp_fname.set_extension("bmp");
	if( false == pic_ptr->SaveBmp( tmp_fname ) )
	{
	    std::cout << "\"" << tmp_fname.c_str() << "\"";
	    std::cout << ":Failed to write in file." << std::endl; 
	}
	delete pic_ptr;
    }
    return 0;
}

//
//
//
