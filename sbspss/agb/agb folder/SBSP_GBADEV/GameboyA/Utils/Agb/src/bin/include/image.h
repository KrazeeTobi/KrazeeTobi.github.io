//======================================================
//    image.h                                           
//    Handles images of fixed size. Images are an aggregate 
//    of certain values with width and height. 
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_IMAGE_
#define	_AGB_IMAGE_
//--------------------------------------------------------------
#define	IMCMP_NONE_FLIP	(0)
#define	IMCMP_H_FLIP	(1)
#define	IMCMP_V_FLIP	(2)
#define	IMCMP_HV_FLIP	(IMCMP_H_FLIP|IMCMP_V_FLIP)
//--------------------------------------------------------------
#include <agbtypes.h>
#include <util.h>
//--------------------------------------------------------------
__MAGBX__START

template<class _Ty>
class Image : public AGBObject
{
public :
    typedef Image<_Ty> _Myt;

protected :
    u32 m_width;
    u32 m_height;
    _Ty *m_heap;
    _Ty **m_data_array_array;
    _Ty m_dummy;

	//  Allocate memory.

    bool alloc( void )
	{
	    if( NULL != m_heap ) return false;
	    m_heap = new _Ty[m_width * m_height];
	    if( NULL == m_heap ) return false;
	    m_data_array_array = new _Ty*[m_height];
	    if( NULL == m_data_array_array )
	    {
		delete[] m_heap;
		m_heap = NULL;
		return false;
	    }
	    for( u32 h_loop = 0 ; h_loop <m_height ; ++h_loop )
	    {
		m_data_array_array[h_loop] =
		    &m_heap[h_loop * m_width];
	    }
	    return true;
	}

	//  Free memory. 

    void free( void )
	{
	    delete[] m_heap;
	    delete[] m_data_array_array;
	    m_heap = NULL;
	    m_data_array_array = NULL;
	}

    bool is_alloc(void)
	{
	    return (NULL != m_heap);
	}

	//  Comparison function

    bool m_compare( const _Myt& _X , int mode=IMCMP_NONE_FLIP )
	{
	    if( this == &_X ) return true;
	    u32 width = ((_Myt&)_X).Width();
	    u32 height= ((_Myt&)_X).Height();
	    if( (m_width != width) || (m_height != height) ) return false;
	    switch( mode )
	    {
		case IMCMP_NONE_FLIP :
		    return m_compare_none_flip( _X );
		case IMCMP_H_FLIP :
		    return m_compare_h_flip( _X );
		case IMCMP_V_FLIP :
		    return m_compare_v_flip( _X );
		case IMCMP_HV_FLIP :
		    return m_compare_hv_flip( _X );
		default :
		    return false;
	    }
	    return true;
	}
    bool m_compare_none_flip( const _Myt& _X )
	{
	    if( this == &_X ) return true;
	    u32 width = ((_Myt&)_X).Width();
	    u32 height= ((_Myt&)_X).Height();
	    if( (m_width != width) || (m_height != height) ) return false;
	    u32 h_loop , w_loop;
	    for( h_loop = 0 ; h_loop < height; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width ; ++w_loop )
		{
		    if( m_data_array_array[h_loop][w_loop] !=
			((_Myt&)_X).Get( w_loop , h_loop ) )
			return false;
		}
	    }
	    return true;
	}
    bool m_compare_h_flip( const _Myt& _X )
	{
	    if( this == &_X ) return true;
	    u32 width = ((_Myt&)_X).Width();
	    u32 height= ((_Myt&)_X).Height();
	    if( (m_width != width) || (m_height != height) ) return false;
	    u32 h_loop , w_loop;
	    for( h_loop = 0 ; h_loop < height; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width ; ++w_loop )
		{
		    if( m_data_array_array[h_loop][w_loop] !=
			((_Myt&)_X).Get( width-w_loop-1, h_loop ) )
			return false;
		}
	    }
	    return true;
	}
    bool m_compare_v_flip( const _Myt& _X )
	{
	    if( this == &_X ) return true;
	    u32 width = ((_Myt&)_X).Width();
	    u32 height= ((_Myt&)_X).Height();
	    if( (m_width != width) || (m_height != height) ) return false;
	    u32 h_loop , w_loop;
	    for( h_loop = 0 ; h_loop < height; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width ; ++w_loop )
		{
		    if( m_data_array_array[h_loop][w_loop] !=
			((_Myt&)_X).Get( w_loop, height-h_loop-1 ) )
			return false;
		}
	    }
	    return true;
	}
    bool m_compare_hv_flip( const _Myt& _X )
	{
	    if( this == &_X ) return true;
	    u32 width = ((_Myt&)_X).Width();
	    u32 height= ((_Myt&)_X).Height();
	    if( (m_width != width) || (m_height != height) ) return false;
	    u32 h_loop , w_loop;
	    for( h_loop = 0 ; h_loop < height; ++h_loop )
	    {
		for( w_loop = 0 ; w_loop < width ; ++w_loop )
		{
		    if( m_data_array_array[h_loop][w_loop] !=
			((_Myt&)_X).Get(width-w_loop-1,
					height-h_loop-1) )
			return false;
		}
	    }
	    return true;
	}

public :
    Image( u32 width=0 , u32 height=0 ) :
        m_width( width ) , m_height( height )
	{
	    m_heap = NULL;
	    m_data_array_array = NULL;
	    alloc();
	}
    Image( const _Myt& _X ) :
	m_width( ((_Myt&)_X).Width() ) , m_height( ((_Myt&)_X).Height() )
	{
	    m_heap = NULL;
	    m_data_array_array = NULL;
	    alloc();
	    Set( _X );
	}
    ~Image(){free();}

//
//
//	Function to access elements  
//
//

	//  Find width and height of image.    

    u32 Width(){return m_width;}
    u32 Height(){return m_height;}
    u32 Size(){return Width()*Height();}

	//  Write function

    void Set( const _Ty& _P , u32 _x , u32 _y)
	{
	    if( _x >= m_width || _y >= m_height ) return;
	    m_data_array_array[_y][_x] = _P;
	}
    void Set( const _Myt& _X , u32 _x , u32 _y ,
			u32 wd = 0 ,u32 ht = 0 )
	{
	    u32 width , height;
	    width = (wd != 0 ) ? wd : ((_Myt&)_X).Width();
	    height= (ht != 0 ) ? ht: ((_Myt&)_X).Height();
	    Rect rc(0 , height-1 , 0 , width-1);
	    Set( _X , _x , _y , rc );
	}
    void Set( const _Myt& _X , u32 _x , u32 _y , const Rect& rc )
	{
	    if( this == &_X ) return;
	    if( _x >= m_width || _y >= m_height ) return;
	    u32 width , height;
	    width = (u32)((Rect&)rc).Width();
	    height = (u32)((Rect&)rc).Height();
	    u32 w_loop_num = Min( (u32)( m_width - _x ) , width);
	    u32 h_loop_num = Min( (u32)( m_height- _y ) , height);
	    for( u32 h_loop = 0 ; h_loop < h_loop_num ; ++h_loop )
	    {
		for( u32 w_loop = 0 ; w_loop < w_loop_num ; ++w_loop )
		{
		    Set( ((_Myt&)_X).Get( (u32)(((Rect&)rc).left + w_loop) ,
			 (u32)(((Rect&)rc).top + h_loop) ) ,
			 _x + w_loop , _y + h_loop );
		}
	    }
	}
    void Set( const _Myt& _X )
	{
	    Set( _X , 0 , 0 );
	}
    _Myt& operator=(const _Myt& _X)
	{
	    Duplicate( _X );
	    return (*this);
	}

    bool Duplicate( const _Myt& _X)
	{
	    if( true == Resize( ((_Myt&)_X).Width(),
				((_Myt&)_X).Height() ) )
	    {
		Set( _X );
		return true;
	    }
	    return false;
	}

	//  Get elements. 

    const _Ty& Get( u32 _x , u32 _y )
	{
	    if( _x >= m_width || _y >= m_height ) return m_dummy;
	    if( NULL == m_heap ) return m_dummy;
	    return m_data_array_array[_y][_x];
	}

    const _Ty& operator()( u32 _x , u32 _y )
	{
	    return Get( _x , _y );
	}

	//  Comparison function 

    bool Compare( const _Myt& _X )
	{
	    return m_compare( _X , IMCMP_NONE_FLIP );
	}

	//  Find flip status.    

    int CompareFlip( const _Myt& _X )
	{
	    for( int i=0 ; i<4 ; ++i )
		if( true == m_compare( _X , i ) ) return i;
	    return -1;
	}

//
//  Function to change size.  Image will be aligned upper left.
//
    bool Resize( u32 width , u32 height )
	{
	    if( m_width == width && m_height == height ) return true;
	    _Ty* heap_tmp = m_heap;
	    _Ty** data_array_array_tmp = m_data_array_array;

		//  Maintain the status as before the transfer. 

	    u32 old_width = m_width;
	    u32 old_height = m_height;
	    m_width = width;
	    m_height = height;

	    m_heap = NULL;
	    m_data_array_array = NULL;

		//  Reserve a new area in memory. If failed, return to the original area.
	    if( false == alloc() )
	    {
		m_width = old_width;
		m_height = old_height;
		m_heap = heap_tmp;
		m_data_array_array = data_array_array_tmp;
		return false;
	    }

		//  Copy the elements of the image.  

	    u32 w_loop_size = Min(old_width , m_width);
	    u32 h_loop_size = Min(old_height , m_height);
	    for( u32 h_loop = 0 ; h_loop < h_loop_size ; ++h_loop )
	    {
		for( u32 w_loop = 0 ; w_loop < w_loop_size ; ++w_loop )
		{
		    m_data_array_array[h_loop][w_loop] =
			data_array_array_tmp[h_loop][w_loop];
		}
	    }

		//  Release the old area.   

	    delete[] heap_tmp;
	    delete[] data_array_array_tmp;
	    return true;
	}
};

template<class _Ty> inline
bool operator==( const Image<_Ty> &_L , const Image<_Ty> &_R )
{
    return ((Image<_Ty>&)_L).Compare( (Image<_Ty>&)_R );
}

template<class _Ty> inline
bool operator!=( const Image<_Ty> &_L , const Image<_Ty> &_R )
{
    return !(_L == _R);
}

__MAGBX__END

__USING__MAGBX

bool OutputImage4b( const Image<u8>& image , std::ofstream& out );
bool OutputImage8b( const Image<u8>& image , std::ofstream& out );
bool OutputImage16b( const Image<u16>& image , std::ofstream& out );
bool OutputImage32b( const Image<u32>& image , std::ofstream& out );
bool OuttxtImage4b( const Image<u8>& image , std::ofstream& out );
bool OuttxtImage8b( const Image<u8>& image , std::ofstream& out );
bool OuttxtImage16b( const Image<u16>& image , std::ofstream& out );
bool OuttxtImage32b( const Image<u32>& image , std::ofstream& out );


//--------------------------------------------------------------
#endif	//  _AGB_IMAGE_

//
//
