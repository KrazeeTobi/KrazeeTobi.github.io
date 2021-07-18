//======================================================
//    buffer.h
//    Class for buffer
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <iostream>
#include <fstream>
#include <agbtypes.h>
#include <buffer.h>

__MAGBX__START
//-----------------------------------------------------------------
Buffer::Buffer( u32 size, u32 type ) :
m_size(size),m_type(type),m_buffer_ptr(NULL),m_end_ptr(NULL)
{
    if(m_size)
    {
	m_buffer_ptr = new u8[m_size];
	if( m_buffer_ptr ) m_end_ptr = m_buffer_ptr + m_size;
    }
}
//-----------------------------------------------------------------
Buffer::Buffer(const Buffer& _X) :
m_type(((Buffer&)_X).Type()), m_size(((Buffer&)_X).Size()),
m_buffer_ptr(NULL),m_end_ptr(NULL)
{
    u8 v;
    if(m_size)
    {
	m_buffer_ptr = new u8[m_size];
	if( m_buffer_ptr )
	{
	    m_end_ptr = m_buffer_ptr + m_size;
	    Buffer::Iterator _it( ((Buffer&)_X).Begin() );
	    Buffer::Iterator _my_it( Begin() );
	    while( !((Buffer&)_X).IsEnd(_it) )
	    {
		((Buffer&)_X).Get(v,_it);
		Put(v,_my_it);
	    }
	}
    }
}
//-----------------------------------------------------------------
bool Buffer::IsEnd(const Buffer::Iterator& _It)
{
    if( NULL == *((Iterator&)_It) ) return true;
    return (u32)(*((Iterator&)_It)) >= (u32)m_end_ptr;
}
//-----------------------------------------------------------------
bool Buffer::Input( std::ifstream& in )
{
    if( NULL == m_buffer_ptr ) return false;
    if( 0 == m_size ) return false;
    if( false == in.is_open() ) return false;
    return !(!in.read((char*)m_buffer_ptr,m_size));
}
//-----------------------------------------------------------------
bool Buffer::Output( std::ofstream& out )
{
    if( NULL == m_buffer_ptr ) return false;
    if( 0 == m_size ) return false;
    if( false == out.is_open() ) return false;
    return !(!out.write((char*)m_buffer_ptr,m_size));
}
//-----------------------------------------------------------------
bool Buffer::Get( u32& _V,Buffer::Iterator& _It )
{
    u16 f,s;
    switch( m_type )
    {
    case BUFFER_TYPE_LITTLE_ENDIAN :
	if( false == Get( s, _It ) ) return false;
	if( false == Get( f, _It ) ) return false;
	break;
    case BUFFER_TYPE_BIG_ENDIAN :
	if( false == Get( f, _It ) ) return false;
	if( false == Get( s, _It ) ) return false;
	break;
    default :
	return false;
    }
    _V = ((u32)f<<16) + (u32)s;
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Get( s32& _V,Buffer::Iterator& _It )
{
    u32 v;
    if( false == Get(v,_It) ) return false;
    _V = *(s32*)(&v);
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Get( u16& _V,Buffer::Iterator& _It )
{
    u8 f,s;
    switch( m_type )
    {
    case BUFFER_TYPE_LITTLE_ENDIAN :
	if( false == Get( s, _It ) ) return false;
	if( false == Get( f, _It ) ) return false;
	break;
    case BUFFER_TYPE_BIG_ENDIAN :
	if( false == Get( f, _It ) ) return false;
	if( false == Get( s, _It ) ) return false;
	break;
    default :
	return false;
    }
    _V = ((u16)f<<8) + (u16)s;
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Get( s16& _V,Buffer::Iterator& _It )
{
    u16 v;
    if( false == Get(v,_It) ) return false;
    _V = *(s16*)(&v);
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Get( u8& _V,Buffer::Iterator& _It )
{
    if( IsEnd(_It) ) return 0;
    u8 ret_val = *(u8*)(*_It);
    _It.add_8();
    _V = ret_val;
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Get( s8& _V,Buffer::Iterator& _It )
{
    u8 v;
    if( false == Get(v,_It) ) return false;
    _V = *(s8*)(&v);
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Put( u32 _V, Buffer::Iterator& _It )
{
    u16 f,s;
    switch( m_type )
    {
    case BUFFER_TYPE_LITTLE_ENDIAN :
	s = (u16)(((u32)_V & 0xffff0000) >> 16 );
	f = (u16)((u32)_V & 0xffff);
	break;
    case BUFFER_TYPE_BIG_ENDIAN :
	f = (u16)(((u32)_V & 0xffff0000) >> 16 );
	s = (u16)((u32)_V & 0xffff);
	break;
    default :
	return false;
    }
    if( false == Put( f, _It ) ) return false;
    if( false == Put( s, _It ) ) return false;
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Put( s32 _V, Buffer::Iterator& _It )
{
    s32 tmp_v;
    u32 v;
    tmp_v = _V;
    v = *(u32*)(&tmp_v);
    return Put( v, _It );
}
//-----------------------------------------------------------------
bool Buffer::Put( u16 _V, Buffer::Iterator& _It )
{
    u8 f,s;
    switch( m_type )
    {
    case BUFFER_TYPE_LITTLE_ENDIAN :
	s = (u8)(((u16)_V & 0xff00) >> 8 );
	f = (u8)((u16)_V & 0xff);
	break;
    case BUFFER_TYPE_BIG_ENDIAN :
	f = (u8)(((u16)_V & 0xff00) >> 8 );
	s = (u8)((u16)_V & 0xff);
	break;
    default :
	return false;
    }
    if( false == Put( f, _It ) ) return false;
    if( false == Put( s, _It ) ) return false;
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Put( s16 _V, Buffer::Iterator& _It )
{
    s16 tmp_v;
    u16 v;
    tmp_v = _V;
    v = *(u16*)(&tmp_v);
    return Put( v, _It );
}
//-----------------------------------------------------------------
bool Buffer::Put( u8  _V, Buffer::Iterator& _It )
{
    if( IsEnd( _It ) ) return false;
    *(*_It) = _V;
    _It.add_8();
    return true;
}
//-----------------------------------------------------------------
bool Buffer::Put( s8  _V, Buffer::Iterator& _It )
{
    s8 tmp_v;
    u8 v;
    tmp_v = _V;
    v = *(u8*)(&tmp_v);
    return Put( v, _It );
}
//-----------------------------------------------------------------
bool operator==(const Buffer::Iterator& _L,
		const Buffer::Iterator& _R)
{
    return *((Buffer::Iterator&)_L)==*((Buffer::Iterator&)_R);
}
//-----------------------------------------------------------------


__MAGBX__END

