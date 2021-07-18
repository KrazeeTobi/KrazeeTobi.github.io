//======================================================
//    main.cpp                                         
//    Main routine for act2agb. Library processes load 
//    and output.
//                                                     
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <string>
#include <iostream>
#include <Cmath>
#include <Cstdio>
#include <agbtypes.h>
#include <palette.h>
#include <filename.h>

#define	ACT2AGB_VERSION_NUMBER	"1.000"

void usage( void )
{
    std::cout << "act2agb.exe ver " << ACT2AGB_VERSION_NUMBER << std::endl;
    std::cout << "[usage] act2agb [-c] (infilename)" << std::endl;
    std::cout << "-c num_of_colors Specify the number of colors.(1-256)" << std::endl;
    exit(0);
}

int main( int argc , char **argv )
{
    __USING__MAGBX;

    FileName input_filename;
    FileName output_filename;
    short num_of_colors = 256;
    if( argc <= 1 ) usage();
    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'c' :
		    ++i;
		    if( i >= argc )
		    {
			usage();
			return 0;
		    }
		    num_of_colors = (short)atoi( argv[i] );
		    if( num_of_colors <= 0 || num_of_colors > 256 )
			usage();
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
	input_filename = argv[i];
    }

	//  Read data. 

    Palette pal(num_of_colors);
    pal.LoadACT( input_filename );

	//  Create output filename.  

    output_filename = input_filename;
    output_filename.set_extension("c");

	//  Write data.  

    pal.SetName( output_filename.base() );
    std::ofstream out;
    out.open( output_filename.c_str() , std::ios::out | std::ios::binary );
    pal.OutCSource( out );

    return 0;
}

