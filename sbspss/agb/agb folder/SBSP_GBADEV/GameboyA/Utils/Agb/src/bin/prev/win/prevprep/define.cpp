//======================================================
//    define.cpp                                   
//    Process #define
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include	<map>
#include	<string>
#include	"global.h"
#include	"token_list.h"
#include	"token_type.h"

typedef struct{
    token_list	value;
    char	check_flag;
} define_value ;

#define	_MAP_TYPE	std::map<std::string,define_value>

static	_MAP_TYPE	define_map;

#ifdef	__cplusplus
extern	"C" {
#endif

//-----------------------------------------------------------------------
void	add_define( const char* key , token_list& value )
{
    _MAP_TYPE::iterator	map_it;
    std::string	key_string(key);
    map_it = define_map.find(key_string);
    define_value	add_value;
    add_value.value = value;
	//	Add key if no key exists.
    if( map_it == define_map.end() )
    {
	_MAP_TYPE::value_type	define_pair(key_string,add_value);
	define_map.insert(define_pair);
    }
    else
	//	Switch key if there is a key
    {
	(*map_it).second = add_value;
    }
}
//-----------------------------------------------------------------------
int	exist_define( const char* str_ptr )
{
    if( NULL == str_ptr ) return (int)false ;
    std::string find_key( str_ptr );
    _MAP_TYPE::iterator map_it = define_map.find(find_key);
    return	(int)( map_it != define_map.end() );
}
//-----------------------------------------------------------------------
void	erase_define( const char* key )
{
    if( NULL == key ) return;
    std::string find_key( key );
    _MAP_TYPE::iterator map_it = define_map.find(find_key);
    if( map_it != define_map.end() ) define_map.erase( map_it );
}
//-----------------------------------------------------------------------

#ifdef	__cplusplus
}
#endif

//-----------------------------------------------------------------------
token_list* compare_define( const char* str_ptr )
{
    std::string	find_key(str_ptr);
    _MAP_TYPE::iterator	map_it = define_map.find(find_key);
    if( map_it == define_map.end() ) return NULL;
    else return &((*map_it).second.value);
}
//-----------------------------------------------------------------------
void	clear_check( void )
{
    for( _MAP_TYPE::iterator map_it = define_map.begin() ;
	 map_it != define_map.end() ; ++map_it )
	(*map_it).second.check_flag = 0;
}
//-----------------------------------------------------------------------
int	set_check( std::string key )
{
    _MAP_TYPE::iterator map_it = define_map.find( key );
    if( define_map.end() == map_it ) return 0;
    if( (*map_it).second.check_flag ) return 0;
    (*map_it).second.check_flag = 1;
    return 1;
}
//-----------------------------------------------------------------------
