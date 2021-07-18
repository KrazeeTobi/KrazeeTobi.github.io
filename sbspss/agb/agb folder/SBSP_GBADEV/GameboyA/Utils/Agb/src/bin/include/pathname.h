//======================================================
//    pathname.h                                           
//    Class to handle pathnames. Not exclusively for AGB.  
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_PATHNAME_
#define	_PATHNAME_

#include <string>
#include <list>

class	PathName
{
protected :
    std::string m_path;
    std::list<std::string> m_path_list;
    std::list<std::string>::iterator m_path_list_it;
    char m_sep;

    void    set_name(void);
public :
    typedef PathName _Myt;

    PathName( char sep='/' ) : m_sep(sep)
	{m_path_list_it = m_path_list.end();}
    PathName( const char *path_name , char sep='/' ) : m_sep(sep)
	{set(path_name);}
    PathName( const std::string &path_name , char sep='/' ) : m_sep(sep)
	{set(path_name);}
    PathName( const _Myt &path_name , char sep='/' ) : m_sep(sep)
	{set(path_name);}
    ~PathName(){};

	//  set function - Function to register folder name
    void set( const char *path_name );
    void set( const std::string &path_name );
    void set( const _Myt& path_name );

    _Myt& operator=( const char *path_name );
    _Myt& operator=( const std::string &path_name );
    _Myt& operator=( const _Myt &path_name );

	//  add function - Function to add folder

    void add( const char *path_name );
    void add( const std::string &path_name );
    void add( const _Myt &path_name );

    void operator+=( const char *path_name ){add(path_name);}
    void operator+=( const std::string &path_name ){add(path_name);}
    void operator+=( const _Myt &path_name ){add(path_name);}

	//  For changing types. 
    const std::string &c_string( void ){return m_path;}
    const std::list<std::string> &c_list( void ){return m_path_list;}
    const char *c_str( void ) const{return m_path.c_str();}

    char separator(void){return m_sep;}
};

template<class _lTy , class _rTy>
PathName operator+(_lTy &lhs , _rTy &rhs)
{
    PathName ret_path(lhs);
    ret_path += rhs;
    return ret_path;
}

#endif	//  _PATHNAME_

//
//
