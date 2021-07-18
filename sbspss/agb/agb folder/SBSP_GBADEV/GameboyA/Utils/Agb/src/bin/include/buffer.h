//======================================================
//    buffer.h
//    Class for buffer
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	__BUFFER_H__
#define	__BUFFER_H__

#include <iostream>
#include <fstream>
#include <agbtypes.h>

#define	BUFFER_TYPE_LITTLE_ENDIAN	(0)
#define	BUFFER_TYPE_BIG_ENDIAN		(1)

__MAGBX__START

class Buffer
{
protected :
    u32 m_type;
    u32 m_size;
    u8* m_buffer_ptr;
    u8* m_end_ptr;
public :

    class Iterator
    {
    protected :
	u8* m_ptr;
    public :
	Iterator( u8* ptr=NULL ) : m_ptr(ptr){}
	Iterator( const Iterator& _X ) : m_ptr( *_X ){}
	~Iterator(){}

	u8* operator*() const{return m_ptr;}
	void add_32(void){if(m_ptr)m_ptr+=4;}
	void add_16(void){if(m_ptr)m_ptr+=2;}
	void add_8(void){if(m_ptr)++m_ptr;}
    };

#ifdef	WIN32
    Buffer( u32 size=0, u32 type=BUFFER_TYPE_LITTLE_ENDIAN );
#else
    Buffer( u32 size=0, u32 type=BUFFER_TYPE_BIG_ENDIAN );
#endif
    Buffer(const Buffer& _X);
    virtual ~Buffer(){delete[] m_buffer_ptr;}

    u32 Type(void){return m_type;}
    u32 Size(void){return m_size;}
    Iterator Begin(void){return Iterator(m_buffer_ptr);}
    Iterator End(void){return Iterator(m_buffer_ptr+m_size);}

    bool IsEnd(const Iterator& _It);
    virtual bool Input( std::ifstream& in );
    virtual bool Output( std::ofstream& out );
    bool Get( u32& _V,Iterator& _It );
    bool Get( s32& _V,Iterator& _It );
    bool Get( u16& _V,Iterator& _It );
    bool Get( s16& _V,Iterator& _It );
    bool Get( u8&  _V,Iterator& _It );
    bool Get( s8&  _V,Iterator& _It );
    bool Put( u32 _V, Iterator& _It );
    bool Put( s32 _V, Iterator& _It );
    bool Put( u16 _V, Iterator& _It );
    bool Put( s16 _V, Iterator& _It );
    bool Put( u8  _V, Iterator& _It );
    bool Put( s8  _V, Iterator& _It );

};

bool operator==(const Buffer::Iterator& _L,
		const Buffer::Iterator& _R);

__MAGBX__END

#endif	//  __BUFFER_H__
