//======================================================
//    filename.cpp                                           
//    Class for using filenames.  Not exclusive to AGB.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <string>
#include <iostream>
#include <pathname.h>
#include <filename.h>

//----------------------------------------------------------------------
void FileName::set_name(void)
{
    m_file_name = m_path_name.c_string();
    m_file_name += m_base;
    if( m_extension.length() )
    {
	m_file_name += '.';
	m_file_name += m_extension;
    }
}
//----------------------------------------------------------------------
void FileName::set( const char* file_name )
{
    std::string tmp(file_name);
    set( tmp );
}
//----------------------------------------------------------------------
void FileName::set( const std::string &file_name )
{
    std::string tmp(file_name);
	//  First, confirm the location of "." to find extension.
    int period_pos = (int)tmp.rfind( '.' );
    if( period_pos < 0 ) period_pos = 0;

    int yenn_pos = (int)tmp.rfind( '\\' );
    int slash_pos = (int)tmp.rfind( '/' );
    int start_pos = (yenn_pos > slash_pos) ? yenn_pos : slash_pos;
    if( start_pos < 0 ) start_pos = 0;

    int length = ((std::string&)file_name).length();

	//
	//  Find extension
	//

    if( period_pos < start_pos ) period_pos = 0;

	//  Process file names starting with "." as in ".ini"
    if( start_pos > 0 && period_pos == start_pos+1 ) period_pos = 0;
    if( period_pos )
    {
	m_extension.resize(0);
	m_extension = &file_name[period_pos+1];
	std::string::reverse_iterator str_rit;

	    //  Exclude " if there is one after the extension
	str_rit = m_extension.rbegin();
	while( 1 )
	{
	    if( str_rit == m_extension.rend() ) break;
	    if( *str_rit != '\"' ) break;
	    m_extension.resize( m_extension.length()-1 );
	    str_rit = m_extension.rbegin();
	}
	tmp.resize( period_pos );
    }
    else
    {
	m_extension = "";
//	m_extension.resize( 0 );
    }

	//  Obtain base name

    m_base = &tmp[start_pos];

    std::string::iterator   str_it;
    str_it = m_base.begin();
    std::string	base_tmp(m_base);
    while( str_it != m_base.end() )
    {
	if( !((*str_it == '\"') || (*str_it == '\\') || (*str_it == '/')) )
	{
	    break;
	}
	m_base = &base_tmp[1];
	base_tmp = m_base;
	str_it = m_base.begin();
    }
    tmp.resize( start_pos );

	//  Obtain path name at the end

    m_path_name = tmp;

    set_name();
}
//----------------------------------------------------------------------
void FileName::set( const FileName &file_name )
{
    if( this != &file_name )
    {
	m_path_name = ((FileName&)file_name).path();
	m_base = ((FileName&)file_name).base();
	m_extension = ((FileName&)file_name).extension();
	set_name();
    }
}
//----------------------------------------------------------------------
void FileName::set( const PathName &path_name )
{
    m_path_name = path_name;
    m_base = "";
    m_extension = "";
    set_name();
}
//----------------------------------------------------------------------
FileName& FileName::operator=(const char* file_name)
{
    set(file_name);
    return (*this);
}
//----------------------------------------------------------------------
FileName& FileName::operator=(const std::string &file_name)
{
    set(file_name);
    return (*this);
}
//----------------------------------------------------------------------
FileName& FileName::operator=(const FileName &file_name)
{
    set(file_name);
    return (*this);
}
//----------------------------------------------------------------------
FileName& FileName::operator=(const PathName &path_name)
{
    set(path_name);
    return (*this);
}
//----------------------------------------------------------------------
void FileName::add( const char* file_name )
{
    FileName tmp( file_name );
    add( tmp );
}
//----------------------------------------------------------------------
void FileName::add( const std::string &file_name )
{
    FileName tmp( file_name );
    add( tmp );
}
//----------------------------------------------------------------------
void FileName::add( const PathName &path_name )
{
    m_path_name += path_name;
    set_name();
}
//----------------------------------------------------------------------
void FileName::add( const FileName &file_name )
{
    m_path_name += ((FileName&)file_name).path();
    if( ((FileName&)file_name).base().length() != 0 )
    {
	set_base( ((FileName&)file_name).base() );
	if( ((FileName&)file_name).extension().length() != 0 )
	{
	    set_extension( ((FileName&)file_name).extension() );
	}
    }
    set_name();
}
//----------------------------------------------------------------------
void FileName::set_base( const char* base )
{
    m_base = base;
    set_name();
}
//----------------------------------------------------------------------
void FileName::set_base( const std::string &base )
{
    m_base = base;
    set_name();
}
//----------------------------------------------------------------------
void FileName::set_extension( const char* ext )
{
    m_extension = ext;
    set_name();
}
//----------------------------------------------------------------------
void FileName::set_extension( const std::string &ext )
{
    m_extension = ext;
    set_name();
}
//----------------------------------------------------------------------
bool FileName::is_extension( const char* ext )
{
    std::string tmp( ext );
    return is_extension(tmp);
}
//----------------------------------------------------------------------
bool FileName::is_extension( const std::string &ext )
{
    std::string ext1(""),ext2("");
    std::string::iterator str_it;
    char add;
    for( str_it = m_extension.begin() ;
	str_it != m_extension.end() ;
	++str_it )
    {
	add = *str_it;
	if( add >= 'A' && add <= 'Z' )
	{
	    add -= 'A';
	    add += 'a';
	}
	ext1 += add;
    }
    for( str_it = ((std::string&)ext).begin() ;
	str_it != ((std::string&)ext).end() ;
	++str_it )
    {
	add = *str_it;
	if( add >= 'A' && add <= 'Z' )
	{
	    add -= 'A';
	    add += 'a';
	}
	ext2 += add;
    }
    return ext1 == ext2;
}
//----------------------------------------------------------------------
bool FileName::is_extension( const FileName &file )
{
    return is_extension( ((FileName&)file).extension() );
}
//----------------------------------------------------------------------
FileName operator+(const PathName& _L ,const FileName& _R)
{
    FileName fname(((PathName&)_L).c_str());
    fname += ((FileName&)_R).pathname();
    fname.set_base(((FileName&)_R).base());
    fname.set_extension(((FileName&)_R).extension());
    return fname;
}
//----------------------------------------------------------------------

//
//
