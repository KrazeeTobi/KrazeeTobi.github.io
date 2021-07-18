//======================================================
//    util.h                                         
//    Useful macros and functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__UTIL_H__
#define	__UTIL_H__

#undef	NULL
#define	NULL	((void*)0)
//----------------------------------------------------------------------
//	Linear interpolation macro
//
//	Find _value during _key for the primary function, which takes _value 0 
//  when _key0 and _value1 when _key1
//
#define	_Linear( _key,_key0,_value0,_key1,_value1 )	\
    (((_key-_key0)*_value1+(_key1-_key)*_value0)/(_key1-_key0))
//----------------------------------------------------------------------
//	Helper function for AGBPrint. Numerical value is displayed.  For debugging.
//
void PrintNum( u32 num );
void PrintNumHex( u32 num );
//----------------------------------------------------------------------
extern const short rcos[256];
extern const short rsin[256];

//
//	Sin and Cos
//	The following argument, angle, needs to be
//	between 0~255.
//	angle is calculated by (degrees * (256 / 360)).
//	angle =  0 ...  0  degrees
//	angle = 64 ...  90 degrees
//	angle =128 ... 180 degrees
//	angle =192 ... 270 degrees
//
#define	Sin( angle ) \
	(rsin[angle])
#define Cos( angle ) \
	(rcos[angle])
//----------------------------------------------------------------------
//	Expansion/Reduction Rotation Structure 
//
typedef struct
{
    s16 dx;
    s16 dmx;
    s16 dy;
    s16 dmy;
} SRMatrix;
//----------------------------------------------------------------------
//
//	Argument
//	RScaleX  Reciprocal of expansion rate in the X direction
//	RScaleY  Reciprocal of expansion rate in the Y direction
//
void SRMatrixSet( SRMatrix* mtx_ptr, s16 RScaleX, s16 RScaleY, u8 Angle );
void SRMatrixSetIdent( SRMatrix* mtx_ptr );
#define	_SRMatrixIdent( dest_ptr )	\
{	\
    ((*(dest_ptr)).dx) = 0x100;	\
    ((*(dest_ptr)).dy) = 0;	\
    ((*(dest_ptr)).dmx)= 0;	\
    ((*(dest_ptr)).dmy)= 0x100;	\
}
#define	_SRMatrixCopy( dest_ptr , src_ptr )	\
{	\
    ((*(dest_ptr)).dx) = ((*(src_ptr)).dx);	\
    ((*(dest_ptr)).dy) = ((*(src_ptr)).dy);	\
    ((*(dest_ptr)).dmx)= ((*(src_ptr)).dmx);	\
    ((*(dest_ptr)).dmy)= ((*(src_ptr)).dmy);	\
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
typedef struct
{
    s16 x_l;
    s16 x_h;
    s16 y_l;
    s16 y_h;
} RefStartCoord;
//----------------------------------------------------------------------
//
//	Argument
//	x  Center of screen  X coordinate
//	y  Center of screen  Y coordinate
//
void RefStartCoordSet(RefStartCoord* rsc_ptr, SRMatrix* mtx_ptr, s16 x, s16 y);
void RefStartCoordSetIdent(RefStartCoord* rsc_ptr, s16 x, s16 y);
#define _RefStartCoordCopy( dest_ptr , src_ptr )	\
{	\
    ((*(dest_ptr)).x_l) = ((*(src_ptr)).x_l);	\
    ((*(dest_ptr)).x_h) = ((*(src_ptr)).x_h);	\
    ((*(dest_ptr)).y_l) = ((*(src_ptr)).y_l);	\
    ((*(dest_ptr)).y_h) = ((*(src_ptr)).y_h);	\
}
//----------------------------------------------------------------------
extern const u16 bit_value_table[16];
extern const u16 bit_and_table[16];
#define	_BitValue( bit ) \
    (bit_value_table[bit])
#define	_BitAnd( bit ) \
    (bit_and_table[bit])
/*----------------------------------------------------------------------*/
#define	_wrapUpperLimit( _val,_lower,_upper )	\
    {	\
	while( (_val) >= (_upper) ) (_val) -= (_upper-_lower);	\
    }
#define	_wrapLowerLimit( _val,_lower,_upper )	\
    {	\
	while( (_val) < (_lower) ) (_val) += (_upper-_lower);	\
    }
#define	_wrapLimit( _val,_lower,_upper )	\
    {	\
	_wrapLowerLimit( _val,_lower,_upper );	\
	_wrapUpperLimit( _val,_lower,_upper );	\
    }
/*----------------------------------------------------------------------*/
#define	_Min( a,b ) (((a)<(b)) ? (a):(b) );
#define	_Max( a,b ) (((a)>(b)) ? (a):(b) );
#define	_Abs( a ) (((a)<0) ? -(a) : (a) )
#define	_Sgn( a ) (((a)==0) ? 0 : (((a)<0) ? -1 : 1) )
/*----------------------------------------------------------------------*/

#endif	//  __UTIL_H__
//
//
