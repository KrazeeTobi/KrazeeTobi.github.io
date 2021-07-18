//////////////////////
//
// Header for Render.c
//
//////////////////////

#ifndef _SIM_RENDER_H
#define _SIM_RENDER_H

/////////////////////////////////////////////

#include <Agb.h>

typedef u8 ubyte;
typedef u32 ulong;

/////////////////////////////////////////////

#define NULL 0
#define BUCKET_SIZE 160

/////////////////////////////////////////////

struct screenRecord
{
	int		width;
	int		height;
	int		pitch;
	ubyte * p_pixels;
};

struct renderContext
{
	struct screenRecord * p_screen;
};

struct geomPoint
{
	int x;
	int y;
	int z;
};

struct geomTriang
{
	struct geomPoint verts[ 3 ];
};

struct geomAffine
{
	int matrix[ 3 ][ 3 ];
	struct geomPoint vector;
};

struct geomBucket
{
	int min_y;
	int max_y;
	int x[ BUCKET_SIZE ];
};

#define GEOM_MATRIX_SHIFT 12
#define GEOM_MATRIX_UNITY ( 1 << GEOM_MATRIX_SHIFT )
#define GEOM_MATRIX_BIAS ( 1 << ( GEOM_MATRIX_SHIFT - 1 ) )
#define GeomMatrixDownshift( value ) ( ( value + GEOM_MATRIX_BIAS ) >> GEOM_MATRIX_SHIFT )
#define GeomMatrixUpshift( value ) ( value << GEOM_MATRIX_SHIFT )

#define GEOM_COORD_SHIFT 4
#define GEOM_COORD_STEP ( 1 << GEOM_COORD_SHIFT )
#define GEOM_COORD_BIAS ( GEOM_COORD_STEP - 1 )
#define GeomCoordDownshift( value ) ( ( value + GEOM_COORD_BIAS ) >> GEOM_COORD_SHIFT )
#define GeomCoordUpshift( value ) ( value << GEOM_COORD_SHIFT )
#define GeomCoordGetFrac( value ) ( value & GEOM_COORD_BIAS )

/////////////////////////////////////////////

struct rendLod
{
	int			lod_log;
	int			old_u;
	int			old_v;
	int			old_dest_idx;
	int			split;
	int			end;
	u8 *		p_terrain_win;
	const u16 *	p_tile_to_char;
	const u8 *	p_char_to_slot;
};

/////////////////////////////////////////////

extern void BehaveInit( void );
extern void RenderInit( void );

extern void BehaveCycle( void );
extern void RenderCycle( void );

extern void RenderVBlank( void );
extern void RenderHBlank( void );

/////////////////////////////////////////////

extern u32 * p_rend_Mode7_FBuffer;

/////////////////////////////////////////////

#endif /* _SIM_RENDER_H */
