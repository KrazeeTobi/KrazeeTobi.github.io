//======================================================
//    main.cpp
//    Main of bmpred 
//    Reduce Colors of bitmap
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

//----------------------------------------------------------------------

#include <string>
#include <list>
#include <agbtypes.h>
#include <hpicture.h>
#include <picture.h>
#include <color.h>
#include <util.h>
#include <palette.h>
#include <filename.h>
#include "colorspace.h"

#define	BMPRED_VERSION_STRING	"1.000"

extern Picture* CreateReductionPicture( const HPicture& _Hpic, const Palette& _Pal, u16 offset );

typedef struct
{
    HPicture*	hpic_ptr;
    FileName	fname;
} hpic_pair;

typedef struct
{
    Picture*	pic_ptr;
    FileName	fname;
} pic_pair;

void DeleteHPicPairList( std::list<hpic_pair>& hp_list )
{
    std::list<hpic_pair>::iterator hp_it;
    for( hp_it = hp_list.begin() ;
	hp_it != hp_list.end() ;
	++hp_it )
    {
	delete (*hp_it).hpic_ptr;
	(*hp_it).hpic_ptr = NULL;
    }
    hp_list.resize(0);
}

void DeletePicPairList( std::list<pic_pair>& pp_list )
{
    std::list<pic_pair>::iterator pp_it;
    for( pp_it = pp_list.begin() ;
	pp_it != pp_list.end() ;
	++pp_it )
    {
	delete (*pp_it).pic_ptr;
	(*pp_it).pic_ptr = NULL;
    }
    pp_list.resize(0);
}

void RedHPicToPic( std::list<pic_pair>& pp_list,
		   std::list<hpic_pair>& hp_list,
		   Palette& pal, u16 offset )
{
    pic_pair pp;
    std::string base_name;
    std::list<hpic_pair>::iterator hp_it;
    for( hp_it = hp_list.begin() ;
	hp_it != hp_list.end() ;
	++hp_it )
    {
	std::cout << (*hp_it).fname.c_str();
	std::cout << " Reducing Colors " << std::endl;
	pp.pic_ptr = CreateReductionPicture( *(*hp_it).hpic_ptr, pal, offset );
	if( NULL == pp.pic_ptr )
	{
	    std::cerr << "\"" << (*hp_it).fname.c_str() << "\"";
	    std::cerr << "Could not Reduce Colors." << std::endl;
	    continue;
	}
	pp.fname = (*hp_it).fname;
	base_name = pp.fname.base();
	base_name += "_rd";
	pp.fname.set_base( base_name );

	pp_list.push_back( pp );
    }
}

void PicListSave( std::list<pic_pair>& pp_list )
{
    pic_pair pp;
    std::string base_name;
    std::list<pic_pair>::iterator pp_it;
    for( pp_it = pp_list.begin() ;
	pp_it != pp_list.end() ;
	++pp_it )
    {
	if( NULL != (*pp_it).pic_ptr )
	{
	    if( false == (*pp_it).pic_ptr->SaveBmp( (*pp_it).fname ) )
	    {
		std::cerr << "\"" << (*pp_it).fname.c_str() << "\"";
		std::cerr << "Could not write." << std::endl;
	    }
	}
    }
}

bool AddHPic( std::list<hpic_pair>& hp_list, FileName& fname )
{
    HPicture* hpic_ptr = NULL;
    hpic_ptr = new HPicture;
    if( NULL == hpic_ptr ) return false;
    if( false == hpic_ptr->LoadBmp( fname ) )
    {
	delete hpic_ptr;
	return false;
    }
    hpic_pair hp;
    hp.hpic_ptr = hpic_ptr;
    hp.fname = fname;
    hp_list.push_back( hp );
    return true;
}

bool CreatePaletteFromHPicList( Palette& pal, u16 num_of_colors,
			        std::list<hpic_pair>& hp_list,
			        Color& base, u16 offset, u8 use_base_flag)
{
    ColorSpace	color_space;
    std::list<hpic_pair>::iterator hp_it;
    for( hp_it = hp_list.begin() ;
	hp_it != hp_list.end() ;
	++hp_it )
    {
	color_space.Add( *(*hp_it).hpic_ptr );
    }
    color_space.SetOffset(offset);
    if( use_base_flag )
    {
	color_space.SetBase( base );
    }
    pal = color_space.CreatePalette( num_of_colors );
    return true;
}

//
//  How to Use
//
void usage()
{
    std::cout << "bmpred ver " << BMPRED_VERSION_STRING << std::endl;
    std::cout << "[usage] bmpred [-c/-n/-p/-P] -o output_file input_file" << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "    -c color   Set Background Colors." << std::endl;
    std::cout << "    -n num     Specify the number of colors to reduce (Default256)." << std::endl;
    std::cout << "    -s start   Start Color Numbers (Default 0)." << std::endl;
    std::cout << "    -p palette Specify Palette (bmp/.act)." << std::endl;
    std::cout << "    -P Output Palette." << std::endl;
    exit( 0 );
}

//
//
//
__USING__MAGBX;

int main( int argc, char** argv )
{

    std::list<FileName> fname_list;
    Color base;
    u8 use_base_flag = 0;
    u8 use_palette_flag = 0;
    u8 out_palette_flag = 0;
    u16 color_start = 0;
    u16 num_of_colors = 256;
    FileName tmp;
    FileName pal_fname;
    FileName out_fname("");

	//  Option Determination

    for( int i=1 ; i<argc ; ++i )
    {
	if( argv[i][0] == '/' || argv[i][0] == '-' )
	{
	    switch( argv[i][1] )
	    {
	    case 's' :
		if( ++i >= argc )
		{
		    std::cerr << "-s : Offset Colors" << std::endl;
		    exit(1);
		}
		color_start = atoi( argv[i] );
		break;
	    case 'c' :
		if( ++i >= argc )
		{
		    std::cerr << "-c : Colors not specified." << std::endl;
		    exit(1);
		}
		base = GetColorFromString( argv[i] );
		use_base_flag = 1;
		break;
	    case 'n' :
		if( ++i >= argc ) usage();
		num_of_colors = atoi( argv[i] );
		break;
	    case 'P' :
		out_palette_flag = 1;
		break;
	    case 'o' :
		if( ++i >= argc ) usage();
		out_fname = argv[i];
		break;
	    case 'p' :
		if( ++i >= argc ) usage();
		pal_fname = argv[i];
		use_palette_flag = 1;
		break;
	    default :
		usage();
		return 0;
	    }
	    continue;
	}
	tmp = argv[i];
	fname_list.push_back( tmp );
    }

    if( (num_of_colors) == 0 )
    {
	std::cerr << "Number of color is 0." << std::endl;
	exit(1);
    }
    if( (num_of_colors+color_start) > 256 )
    {
	std::cerr << "Color Number is more than 256." << std::endl;
	exit(1);
    }

	//  Error if there is no intput file

    if( fname_list.size() == 0 )
    {
	std::cerr << "Input File not specified." << std::endl;
	exit(1);
    }

    Picture* pic_ptr = NULL;

    std::list<hpic_pair> hp_list;
    std::list<FileName>::iterator fname_list_it;
    for( fname_list_it = fname_list.begin() ;
	fname_list_it != fname_list.end() ;
	++fname_list_it )
    {
	if( false == AddHPic( hp_list, *fname_list_it ) )
	{
	    std::cerr << "\"" << (*fname_list_it).c_str() << "\"";
	    std::cerr << "Could not read" << std::endl;
	}
    }
    if( hp_list.size() == 0 )
    {
	std::cerr << "Could not read even one image\n" << std::endl;
	return 1;
    }
    Palette pal(num_of_colors);

    if( use_palette_flag )
    {
	if( out_palette_flag )
	{
	    std::cerr << "Inputting palette to output palette." << std::endl;
	    exit(1);
	}
	char ext[8];
	for( i=0 ; i<8 ; ++i )
	{
	    ext[i] = '\0';
	}
	std::string::iterator str_it;
	std::string ext_str;
	ext_str = pal_fname.extension();
	i=0;
	for( str_it = ext_str.begin();
	    str_it != ext_str.end();
	    ++str_it )
	{
	    if( i>6 ) break;
	    ext[i] = *str_it;
	    if( ext[i] >= 'A' && ext[i] <= 'Z' ) ext[i] -= ('A'-'a');
	    ++i;
	}
	ext_str = ext;
	if( ext_str == "act" )
	{
	    if( false == pal.LoadACT( pal_fname ) )
	    {
		std::cerr << "\"" << pal_fname.c_str();
		std::cerr << "\" Could not read" << std::endl;
		DeleteHPicPairList( hp_list );
		exit(1);
	    }
	}
	else
	{
	    pic_ptr = new Picture;
	    if( NULL == pic_ptr )
	    {
		std::cerr << "Lacking memory" << std::endl;
		DeleteHPicPairList( hp_list );
		exit(1);
	    }
	    if( false == pic_ptr->LoadBmp( pal_fname ) )
	    {
		std::cerr << "\"" << pal_fname.c_str();
		std::cerr << "\" Could not read" << std::endl;
		delete pic_ptr;
		exit(1);
	    }
	    pal = pic_ptr->GetPalette();
	    delete pic_ptr;
	    pic_ptr = NULL;
	}
    }
    else
    {
		//  Create Palette
	if( false == CreatePaletteFromHPicList( pal, num_of_colors,
	    hp_list, base, color_start , use_base_flag) )
	{
	    std::cerr << "Could not create Palette." << std::endl;
	    DeleteHPicPairList( hp_list );
	}
	std::cout << "Created Palette" << std::endl;
    }

    if( out_palette_flag )
    {
	if( out_fname.base().length() == 0 )
	{
	    out_fname.set_base( (*fname_list.begin()).base() );
	    if( out_fname.extension().length() == 0 )
	    {
		out_fname.set_extension( "act" );
	    }
	}

	if( false == pal.SaveACT( out_fname ) )
	{
	    std::cerr << "\"" << out_fname.c_str() << "\"";
	    std::cerr << "Failed to output" << std::endl;
	    DeleteHPicPairList( hp_list );
	    exit( 1 );
	}
	return 0;
    }

    std::list<pic_pair> pp_list;

    RedHPicToPic( pp_list, hp_list, pal , color_start );

    DeleteHPicPairList( hp_list );

    Picture* tmp_pic_ptr;

    if( (pp_list.size() == 1) && (out_fname.c_string().size()!=0) )
    {
	tmp_pic_ptr = (*(pp_list.begin())).pic_ptr;
	if( false == (*(pp_list.begin())).pic_ptr->SaveBmp( out_fname ) )
	{
	    DeletePicPairList( pp_list );
	    std::cerr << "Could not output" << std::endl;
	    exit(1);
	}
    }
    else
    {
	PicListSave( pp_list );
    }

    DeletePicPairList( pp_list );

    return 0;
}

//
//
