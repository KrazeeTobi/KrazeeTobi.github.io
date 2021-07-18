//======================================================
//    pathname.cpp                                           
//    Class to handle pathname.  Not exclusive to AGB.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <string>
#include <list>
#include <pathname.h>

//--------------------------------------------------------------
void PathName::set_name(void)
{
    m_path = "";
    std::list<std::string>::iterator str_list_it;
    for( str_list_it = m_path_list.begin() ;
	 str_list_it != m_path_list_it ;
	 ++str_list_it )
    {
	m_path += *str_list_it;
	m_path += m_sep;
    }
}
//--------------------------------------------------------------
void PathName::set( const char *path_name )
{
    std::string tmp( path_name );
    set(tmp);
}
//--------------------------------------------------------------
void PathName::set( const std::string &path_name )
{
    std::string::const_iterator str_cit;
    std::string tmp("");
    m_path_list.resize(0);
    for( str_cit = path_name.begin() ;
	 str_cit != path_name.end() ;
	 ++str_cit )
    {
	    //	Ignore "
	if( *str_cit == '\"' ) continue;

	    //	If "\" is found, evaluate the character array up to that point
	    //	as the folder name and register to the list.
	if( *str_cit == '/' || *str_cit == '\\' )
	{
	    m_path_list.push_back( tmp );
	    tmp.resize( 0 );
	    continue;
	}
	tmp += *str_cit;
    }
	//  Even if the final character array is not ""
    //  regard it as folder name
    if( tmp != "" ) m_path_list.push_back( tmp );
    m_path_list_it = m_path_list.end();
    set_name();
}
//--------------------------------------------------------------
void PathName::set( const PathName& path_name )
{
    std::list<std::string>::const_iterator str_list_cit;
    m_path_list.resize(0);
    if( &path_name != this )
    {
	    //	Copy folder names one by one
	for( str_list_cit = ((PathName&)path_name).c_list().begin() ;
	     str_list_cit != ((PathName&)path_name).c_list().end() ;
	     ++str_list_cit )
	{
	    m_path_list.push_back( *str_list_cit );
	}
    }
    m_path_list_it = m_path_list.end();
}
//--------------------------------------------------------------
PathName& PathName::operator=( const char *path_name )
{
    set(path_name);
    return *this;
}
//--------------------------------------------------------------
PathName& PathName::operator=( const std::string &path_name )
{
    set(path_name);
    return *this;
}
//--------------------------------------------------------------
PathName& PathName::operator=( const PathName &path_name )
{
    set(path_name);
    return *this;
}
//--------------------------------------------------------------
void PathName::add( const char *path_name )
{
    std::string tmp( path_name );
    add(tmp);
}
//--------------------------------------------------------------
void PathName::add( const std::string &path_name )
{
    PathName    tmp_path( path_name );
    add( tmp_path );
}
//--------------------------------------------------------------
void PathName::add( const PathName &path_name )
{
    if( &path_name != this )
    {
	    //	Planning to expand to method that recognizes m_path_list            
	std::list<std::string>::const_iterator str_list_cit;

	for( str_list_cit = ((PathName&)path_name).c_list().begin() ;
	     str_list_cit != ((PathName&)path_name).c_list().end() ;
	     ++str_list_cit )
	{
		 //  If the character array was "..", move it to the folder one 
         // above
	    if( (*str_list_cit) == ".." )
	    {
		if( m_path_list.size() )
		{
		    m_path_list.pop_back();
		    continue;
		}
		m_path_list.push_back( *str_list_cit );
		continue;
	    }
	    m_path_list.push_back( *str_list_cit );
	    continue;
	}
	m_path_list_it = m_path_list.end();
	set_name();
    }
}
//--------------------------------------------------------------

//
//
