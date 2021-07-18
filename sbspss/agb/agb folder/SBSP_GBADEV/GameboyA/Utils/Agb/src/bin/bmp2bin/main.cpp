//======================================================
//    main.c
//    Main function for bmp2bin
//    Splits bmp in character and saves it as a binary file.
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
#include <palette.h>
#include <hpicture.h>
#include <picture.h>
#include <character.h>

#define	BMP2BIN_VERSION_STRING	"1.100"

//
//  Usage
//
void usage()
{
    std::cout << "bmp2bin ver " << BMP2BIN_VERSION_STRING << std::endl;
    std::cout << "[usage] bmp2bin -o out_filename [-w/-h/-p/-b] filename" << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "  -o out_filename	Specify output file name" << std::endl;
    std::cout << "  -w width  		Set width of object" << std::endl;
    std::cout << "  -h height 		Set height of object" << std::endl;
    std::cout << "  -p 			Output only palette in binary" << std::endl;
    std::cout << "  -b 			Output for bitmap mode" << std::endl;
    exit( 0 );
}

//
//  main function
//
int main( int argc , char **argv )
{
    __USING__MAGBX;
    std::list<FileName> fname_list;
    FileName tmp;
    FileName out_fname("");
    u32 grid_width = 8;
    u32 grid_height = 8;
    u8 bmp_flag = 0;
    u8 palette_flag = 0;

	//  Option judgement

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'b' :
		    bmp_flag = 1;
		    break;
		case 'o' :
		    if( ++i >= argc ) usage();
		    out_fname = argv[i];
		    break;
		case 'w' :
		    if( ++i >= argc ) usage();
		    grid_width = atoi( argv[i] );
		    if( 0 >= grid_width ) usage();
		    if( grid_width & 7 ) usage();
		    break;
		case 'p' :
		    palette_flag = 1;
		    break;
		case 'h' :
		    if( ++i >= argc ) usage();
		    grid_height = atoi( argv[i] );
		    if( 0 >= grid_height ) usage();
		    if( grid_height & 7 ) usage();
		    break;
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

	//  Error if no input file

    if( fname_list.size() == 0 )
    {
	std::cout << "Input file is not specified" << std::endl;
	exit(1);
    }
    if( ( bmp_flag ) && (palette_flag) )
    {
	std::cout << "Bit Map Mode and Palette Output Mode" << std::endl;
	std::cout << "cannot be set at the same time" << std::endl;
	exit(1);
    }

	//  Processing

    Picture pic;
    HPicture hpic;
    std::ofstream out;
    std::ifstream in;
    Character *ch_ptr=NULL;
    Rect rc;
    int w_loop , h_loop;
    int w_in_loop , h_in_loop;
    u8 high_color_mode_flag;


	//  Use .imb as the extension of the output filename - unless
	//  a palette is output, in which case use the .plb extension.

    if( out_fname.base().length() == 0 )
    {
	out_fname.set_base( (*fname_list.begin()).base() );
    }
    if( out_fname.extension().length() == 0 )
    {
	if( palette_flag ) out_fname.set_extension( "plb" );
	else out_fname.set_extension( "imb" );
    }

#ifdef	WIN32
    out.open( out_fname.c_str() , std::ios::out | std::ios::binary );
#else
    out.open( out_fname.c_str() );
#endif
    if( !out.is_open() )
    {
	std::cout << "\"" << out_fname.c_str() << "\"";
	std::cout << ":File was not created" << std::endl;
	exit(1);
    }

	//  Able to process multiple filenames

    std::list<FileName>::iterator fname_list_it;
    for(fname_list_it = fname_list.begin() ;
	fname_list_it != fname_list.end() ;
	++fname_list_it )
    {
	high_color_mode_flag = 0;

	    //	Load bmp.  Load as a file with a palette, and if it fails,
	    //	load as a file without a palette.

	if(false == pic.LoadBmp( (*fname_list_it) ) )
	{
	    if( false == hpic.LoadBmp( (*fname_list_it) ) )
	    {
		std::cout << "\"" << (*fname_list_it).c_str() << "\"";
		std::cout << ":Unable to open file" << std::endl;
		continue;
	    }
	    high_color_mode_flag = 1;
	}

	    //  Process in 24 bit mode.

	if( high_color_mode_flag )
	{
	    std::cout << "\"" << (*fname_list_it).c_str() << "\"" << std::endl;
	    std::cout << "width     = " << hpic.Width() << std::endl;
	    std::cout << "height    = " << hpic.Height() << std::endl;
	    std::cout << "bit_count = 16" << std::endl;
	    hpic.Output( out );
	    continue;
	}

	if( palette_flag )
	{
	    std::cout << "\"" << (*fname_list_it).c_str() << "\"" << std::endl;
	    std::cout << "colors = " << (pic.GetPalette()).Size() << std::endl;
	}
	else
	{
	    std::cout << "\"" << (*fname_list_it).c_str() << "\"" << std::endl;
	    std::cout << "width     = " << pic.Width() << std::endl;
	    std::cout << "height    = " << pic.Height() << std::endl;
	    std::cout << "bit_count = " << (u32)pic.BitCount() << std::endl;
	}

	    //	With palette

	    //  In the case of bitmap mode
	if( (bmp_flag!=0) && (pic.BitCount()<=8) )
	{
	    pic.Output( out );
	}
	else
	{

		//  For palette output mode, process completed by outputting palette.

	    if( palette_flag )
	    {
		(pic.GetPalette()).Output( out );
		continue;
	    }

		//	Create Character class

	    ch_ptr = pic.CreateCharacter();
	    if( NULL == ch_ptr )
	    {
		std::cout << "Memory Over Flow" << std::endl;
		continue;
	    }
	    for( h_loop = 0 ; h_loop < pic.Height() ; h_loop += grid_height )
	    {
		for( w_loop = 0 ; w_loop < pic.Width() ; w_loop += grid_width )
		{
		    for( h_in_loop = 0 ; h_in_loop < grid_height ; h_in_loop += 8 )
		    {
			for( w_in_loop = 0 ; w_in_loop < grid_width ; w_in_loop += 8 )
			{
			    rc.top = h_loop + h_in_loop;
			    rc.bottom = rc.top + 7;
			    rc.left = w_loop + w_in_loop;
			    rc.right = rc.left + 7;
			    ch_ptr->Set( pic.GetImage() , 0 , 0 , rc );
			    ch_ptr->Output( out );
			}
		    }
		}
	    }
	    pic.DeleteCharacter( ch_ptr );
	}
    }
    out.close();
    return 0;
}

//
//
//
