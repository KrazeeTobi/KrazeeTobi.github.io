//======================================================
//    filename.h                                           
//    Class to handle filenames. Not exclusively for AGB.
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_FILENAME_
#define	_FILENAME_

#include <string>
#include <iostream>
#include <pathname.h>

class	FileName
{
protected :
    PathName	m_path_name;
    std::string	m_file_name;
    std::string	m_base;
    std::string	m_extension;

    void    set_name(void);

public :
    typedef FileName	_Myt;

    FileName( void ) :
	m_path_name('/') ,
	m_file_name("") , m_base( "" ) , m_extension("")
    {}
    FileName( char sep ) :
	m_path_name(sep) ,
	m_file_name("") , m_base( "" ) , m_extension("")
    {}
    FileName( const char* file_name , char sep='/' ) :
	m_path_name(sep) ,
	m_file_name("") , m_base( "" ) , m_extension("")
	{set(file_name);}
    FileName( const std::string &file_name , char sep='/' ) :
	m_path_name(sep),
	m_file_name("") , m_base( "" ) , m_extension("")
	{set(file_name);}
    FileName( const _Myt &file_name ) :
	m_path_name( ((PathName&)((_Myt&)file_name).base()).separator() ) ,
	m_file_name("") , m_base( "" ) , m_extension("")
	{set(file_name);}
    FileName( const PathName &path_name ) :
	m_path_name(((PathName&)path_name).separator()),
	m_file_name("") , m_base( "" ) , m_extension("")
	{set(path_name);}
    ~FileName(){}

	//  set function - Set filename.  

    void    set( const char* file_name );
    void    set( const std::string &file_name );
    void    set( const _Myt &file_name );
    void    set( const PathName &path_name );
    _Myt&   operator=(const char* file_name);
    _Myt&   operator=(const std::string &file_name);
    _Myt&   operator=(const _Myt &file_name);
    _Myt&   operator=(const PathName &path_name);

    void    add( const char* file_name );
    void    add( const std::string &file_name );
    void    add( const PathName &path_name );
    void    add( const FileName &file_name );
    void    operator+=(const char* file_name){add(file_name);}
    void    operator+=(const std::string &file_name){add(file_name);}
    void    operator+=(const PathName &path_name){add(path_name);}
    void    operator+=(const FileName &file_name){add(file_name);}

    void    set_base( const char* base );
    void    set_base( const std::string &base );

    void    set_extension( const char* ext );
    void    set_extension( const std::string &ext );
    bool    is_extension( const char* ext );
    bool    is_extension( const std::string& ext );
    bool    is_extension( const _Myt& _X );

    const std::string &base(){return m_base;}
    const std::string &extension(){return m_extension;}
    const PathName &path(){return m_path_name;}
    const PathName &pathname(){return m_path_name;}

    const std::string &c_string( void ){return m_file_name;}
    const char* c_str() const {return m_file_name.c_str();}
};

FileName operator+(const PathName& _L ,const FileName& _R);

#endif	//  _FILENAME_

//
//
