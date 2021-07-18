//======================================================
//    main.cpp
//    Main of bmpgrid
//    Split and save bitmap.
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
#include <image.h>
#include <filename.h>
#include <palette.h>
#include <hpicture.h>
#include <picture.h>
#include <character.h>

#define	BMPGRID_VERSION_STRING	"1.000"

//
//  Usage
//
void usage()
{
    std::cout << "BmpGrid ver " << BMPGRID_VERSION_STRING << std::endl;
    std::cout << "[usage] bmpgrid [-w/-h] output_file" << std::endl;
    std::cout << "    -w width  For width, use the number that is divisible by 8" << std::endl;
    std::cout << "    -h height For height, use the number that is divisible by 8" << std::endl;
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

	//  Option judgement

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
		case 'w' :
		    if( ++i >= argc ) usage();
		    grid_width = atoi( argv[i] );
		    if( 0 >= grid_width || (grid_width & 7) )
		    {
			std::cerr << "Width is not divisible by 8" << std::endl;
			usage();
		    }
		    break;
		case 'h' :
		    if( ++i >= argc ) usage();
		    grid_height = atoi( argv[i] );
		    if( 0 >= grid_width || (grid_width & 7) )
		    {
			std::cerr << "Height is not divisible by 8" << std::endl;
			usage();
		    }
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
	std::cerr << "Input file is not specified" << std::endl;
	exit(1);
    }

	//  Processing

    Picture pic;
    HPicture hpic;
    Picture pic_tmp(grid_width,grid_height);
    HPicture hpic_tmp(grid_width,grid_height);
    std::string tmp_base;
    FileName tmp_fname;
    Character *ch_ptr=NULL;
    Rect rc;
    u32 Count;
    char Count_txt[8];
    int w_loop , h_loop;
    u8 high_color_mode_flag;

	//  Use .imb as the extension of the output filename


    if( out_fname.base().length() == 0 )
    {
	out_fname.set_base( (*fname_list.begin()).base() );
	if( out_fname.extension().length() == 0 )
	{
	    out_fname.set_extension( "bmp" );
	}
    }

	//  Able to process multiple filename

    tmp_fname.set_extension( out_fname.extension() );

    std::list<FileName>::iterator fname_list_it;
    for(fname_list_it = fname_list.begin() ;
	fname_list_it != fname_list.end() ;
	++fname_list_it )
    {
	high_color_mode_flag = 0;
	Count = 0;

	    //	Load bmp.  Load it as a file with a palette, and if it fails,
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

	if( high_color_mode_flag )
	{
	    for( h_loop = 0 ; h_loop < hpic.Height() ; h_loop += grid_height )
	    {
		for( w_loop = 0 ; w_loop < hpic.Width() ; w_loop += grid_width )
		{
		    rc.top = h_loop;
		    rc.bottom = rc.top + grid_height- 1;
		    rc.left = w_loop;
		    rc.right = rc.left + grid_width - 1;

		    sprintf( Count_txt , "%04x" , Count++ );
		    tmp_base = out_fname.base();
		    tmp_base += '_';
		    tmp_base += Count_txt;
		    tmp_fname.set_base( tmp_base.c_str() );

		    hpic_tmp.Set( hpic.GetImage() , 0 , 0 , rc );
		    hpic_tmp.SaveBmp( tmp_fname );
		}
	    }
	    continue;
	}
	else
	{
	    for( h_loop = 0 ; h_loop < pic.Height() ; h_loop += grid_height )
	    {
		for( w_loop = 0 ; w_loop < pic.Width() ; w_loop += grid_width )
		{
		    rc.top = h_loop;
		    rc.bottom = rc.top + grid_height- 1;
		    rc.left = w_loop;
		    rc.right = rc.left + grid_width - 1;

		    sprintf( Count_txt , "%04x" , Count++ );
		    tmp_base = out_fname.base();
		    tmp_base += '_';
		    tmp_base += Count_txt;
		    tmp_fname.set_base( tmp_base.c_str() );

		    pic_tmp.Set( pic.GetImage() , 0 , 0 , rc );
		    pic_tmp.SetPalette( pic.GetPalette() );
		    pic_tmp.SaveBmp( tmp_fname );
		}
	    }
	    continue;
	}
    }
    return 0;
}

//
//
