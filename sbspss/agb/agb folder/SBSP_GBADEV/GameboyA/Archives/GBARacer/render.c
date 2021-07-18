//////////////////////////////////////////////////////////////////////////////
//
// Render.c
//
//////////////////////////////////////////////////////////////////////////////

#include "data.h"
#include "data_math_table.h"
#include "data_tile_proc.h"
#include "render.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define false 0
#define true -1

//#define BHV_CURVE_SEGMENTS 4
#define BHV_CURVE_SEGMENTS 15

#define REND_KEEP_3D false
#define REND_CHECK_TW false
#define REND_USE_LOD_1 true

#define REND_USE_DIVISION false

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

u32		rendCodeBuf[ 0x100 ];	         // Buffer for fill routine

#if REND_KEEP_3D
u32		rend_Back_Screen[ 20 * 30 * 8 ];
#else
u32		rend_Back_Screen[ 1 ];
#endif

u8		BgBak[ 0x0800 ];			     // BG backup

#if REND_CHECK_TW
u8		rend_TW_Check_Buff[ 0x0400 ];
#endif

u32		rend_Mode7_Buffer_0[ 640 ];
u32		rend_Mode7_Buffer_1[ 640 ];
u32	*	p_rend_Mode7_BBuffer;
u32	*	p_rend_Mode7_FBuffer;
vu8		dump_Screen_Flg;
vu32	frame_Rate;
vu32	frame_Count;
u32		s_fill_colour_long;

u16		bg_cos_val;
u16		bg_sin_val;
u16		bg_angle;

u32		camera_pos_x;
u32		camera_pos_y;

u16		rend_Slot_Id_Xref[ 0x0100 ];

int		sy;

int		rend_DPE_dsy;
int *	rend_DPE_p_sx;
int		rend_DPE_ival;
int		rend_DPE_istep;
int		rend_DPE_fval;
int		rend_DPE_fstep;
int		rend_DPE_ifstep;
int		rend_DPE_delta_y;

int		bhv_On_Curve_Controls[ BHV_CURVE_SEGMENTS * 2 ];
int		bhv_Current_S_Value;
int		bhv_Current_Segment;

struct renderContext * sp_render_context = NULL;

//static int test_x = 64;
//static int test_y = 128;

int	sys_Time_Begin;
int	sys_Time_Result;
int sys_Time_HWM;
int sys_Time_IHWM;

/*
#if REND_USE_LOD_1
static int lod_log = 0;
#else
static int lod_log = 1;
#endif

int		s_old_u;
int		s_old_v;
int		s_old_dest_idx;
static const u16 * p_tile_to_char;
static const u8 * p_char_to_slot;
*/
	
struct rendLod rend_Lod_1;
struct rendLod rend_Lod_2;
//struct rendLod rend_Lod_4;
static struct geomTriang test_triang;

struct geomBucket s_left_bucket;
struct geomBucket s_right_bucket;

extern void rend_fill_from_bux( void );
extern void rend_edge_to_bux( void );
extern void rend_clear_screen( void );

typedef void (* fillFuncPtr )(void);
typedef int bool;

//static void * sp_soft_screen = NULL;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

const u16 Rend_BG_Palettes[16][16]  = 
{
	{0x7fff, 0x0000, 0x001e, 0x0380, 0x7c00,},
};

const u32 Rend_Head_Masks[ 8 ] = 
{
    0xffffffff,
    0xfffffff0,
    0xffffff00,
    0xfffff000,
    0xffff0000,
    0xfff00000,
    0xff000000,
    0xf0000000
};

const u32 Rend_Tail_Masks[ 8 ] = 
{
    0x00000000,
    0x0000000f,
    0x000000ff,
    0x00000fff,
    0x0000ffff,
    0x000fffff,
    0x00ffffff,
    0x0fffffff,
};

const u8 Rend_Test_Card[ 2 ][ 64 ] = 
{
	{
		0, 0, 0, 0, 1, 1, 1, 1, 
		0, 0, 0, 0, 1, 1, 1, 1, 
		0, 0, 0, 0, 1, 1, 1, 1, 
		0, 0, 0, 0, 1, 1, 1, 1, 
		1, 1, 1, 1, 0, 0, 0, 0, 
		1, 1, 1, 1, 0, 0, 0, 0, 
		1, 1, 1, 1, 0, 0, 0, 0, 
		1, 1, 1, 1, 0, 0, 0, 0, 
	},
	{
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
	}
};
/*
const int bhv_Off_Curve_Controls[ BHV_CURVE_SEGMENTS * 2 ] =
{
		2048, 1024,
		3072, 2048,
		2048, 3072,
		1024, 2048,
};
*/
const int bhv_Off_Curve_Controls[ BHV_CURVE_SEGMENTS * 2 ] =
	{
		3484,  774,
		3636,  772,
		3628,  884,
		3518,  992,
		3320, 1190,
		3098, 1414,
		2984, 1518,
		2904, 1534,
		2866, 1478,
		2856, 1358,
		2908, 1296,
		2998, 1256,
		3116, 1142,
		3292,  958,
		3424,  822,
	};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int geom_Vector_To_Angle( int x_comp, int y_comp );

static void bhv_Init_Control_Points( void );
static void bhv_Update_Position( int speed );
static void bhv_Interpolate_Position( void );

static void rend_Prep_Mode7_Buffer( void );
void rend_Behave_Camera( struct rendLod * p_lod );
static void rend_Swap_Mode7_Buffers( void );

static void rend_Smart_Load_Terrain( int u, int v, struct rendLod * p_lod );
static bool rend_Terrain_Ok_In_U( int u, struct rendLod * p_lod );
static bool rend_Terrain_Ok_In_V( int v, struct rendLod * p_lod );
static void rend_Load_Terrain( int u, int v, struct rendLod * p_lod );
static void rend_LTW_Check( void );
static void rend_Load_Terrain_Window( int u, int v, int dest_idx, int width, int height, struct rendLod * p_lod );
static void rend_Load_Terrain_Window_Sub( int u, int v, u8 * p_char_map_start, int width, int height, struct rendLod * p_lod );
void rend_Init_Lods( void );

void rend_Init_Slot_Array( void );
void rend_Dump_Tiles( void );
void rend_Dump_Terrain( struct rendLod * p_lod );
static void rend_Clear_Screen( u8 index );
static int * GeomInitTriang( int * p_params, struct geomTriang * p_triang );
static int * GeomInitPoint( int * p_params, struct geomPoint * p_point );
static void rend_Init_Bucket( struct geomBucket * p_bucket );
static void rend_Draw_Triang( struct geomTriang * p_triang );
static void rend_Fill_From_Buckets( ubyte fill_colour );
static void rend_Draw_Poly_Edge( struct geomPoint * p_vert_0, struct geomPoint * p_vert_1 );

static void geom_Get_Trig_Ratios( int angle, int * p_cos, int * p_sin );

static void Plot_Pixel( u32 x, u32 y, ubyte fill_colour );
static void Draw_Number( int num );
static void Draw_Char( int x, int y, int char_val );

//////////////////////////////////////////////////////////////////////////////

void sys_Timer_Init( void );
void sys_Timer_Start( void );
void sys_Timer_Mark( void );
void sys_Timer_Stop( void );
static int sys_Get_Time( void );

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void BehaveInit( void )
{
	int triang_init_0[] = { 100, 60, 0,	80, 140, 0,		180, 110, 0 };
	
	( void )GeomInitTriang( &triang_init_0[ 0 ], &test_triang );

	bg_angle = 0x0200;
	frame_Count = 0;

	bhv_Init_Control_Points();

	bhv_Current_Segment = 0;
	bhv_Current_S_Value = 0;
	bhv_Update_Position( 64 );
}

//////////////////////////////////////////////////////////////////////////////

void BehaveCycle( void )
{
	struct geomPoint * p_vert = &test_triang.verts[ 0 ];
	p_vert->x += GEOM_COORD_STEP;
	if ( p_vert->x >= ( GEOM_COORD_STEP * 192 ) )
	{
		p_vert->x = GEOM_COORD_STEP * 64;
	}

	bhv_Update_Position( 64 );

	/*
	camera_pos_x -= 0x23;
	camera_pos_x &= 0x000fffff;

	camera_pos_y -= 0xc0;
	camera_pos_y &= 0x000fffff;
	*/

//	bg_angle++;
	bg_angle &= 0x03ff;
}

//////////////////////////////////////////////////////////////////////////////

void bhv_Init_Control_Points( void )
{
	int p;
	int next_p;
	int x;
	int y;
	int next_x;
	int next_y;
	int mean_x;
	int mean_y;

	for ( p = 0 ; p < BHV_CURVE_SEGMENTS * 2 ; p += 2 )
	{
		next_p = ( p + 2 ) < ( BHV_CURVE_SEGMENTS * 2 ) ? p + 2 : 0;
			
		x = bhv_Off_Curve_Controls[ p ];
		y = bhv_Off_Curve_Controls[ p + 1 ];

		next_x = bhv_Off_Curve_Controls[ next_p ];
		next_y = bhv_Off_Curve_Controls[ next_p + 1 ];

		mean_x = ( x + next_x ) >> 1;
		mean_y = ( y + next_y ) >> 1;

		bhv_On_Curve_Controls[ next_p ]		= mean_x;
		bhv_On_Curve_Controls[ next_p + 1 ]	= mean_y;
	}
}

//////////////////////////////////////////////////////////////////////////////

void bhv_Update_Position( int desired )
{
	int speed;

	speed = desired;
//	speed = ( desired << 12 )/ bhv_Actual_Speed;

	bhv_Current_S_Value += speed;
	while ( bhv_Current_S_Value >= 4096 )
	{
		bhv_Current_S_Value -= 4096;
		bhv_Current_Segment++;
		if ( bhv_Current_Segment >= BHV_CURVE_SEGMENTS )
		{
			bhv_Current_Segment = 0;
		}
	}

	bhv_Interpolate_Position();
}

//////////////////////////////////////////////////////////////////////////////

void bhv_Interpolate_Position( void )
{
	int p;
	int next_p;
	int x0;
	int x1;
	int x2;
	int x;
	int y0;
	int y1;
	int y2;
	int y;
	int s;
	int s_squared;
	int s_squared_hi;
	int s_squared_lo;
	int x_square_coeff;
	int x_square_term;
	int y_square_coeff;
	int y_square_term;
	int vx;
	int vy;

	p = bhv_Current_Segment * 2;
	next_p = ( p + 2 ) < ( BHV_CURVE_SEGMENTS * 2 ) ? p + 2 : 0;
	
	x0 = bhv_On_Curve_Controls[ p ];
	y0 = bhv_On_Curve_Controls[ p + 1 ];

	x1 = bhv_Off_Curve_Controls[ p ];
	y1 = bhv_Off_Curve_Controls[ p + 1 ];

	x2 = bhv_On_Curve_Controls[ next_p ];
	y2 = bhv_On_Curve_Controls[ next_p + 1 ];

	s = bhv_Current_S_Value;

	s_squared = s * s;
	s_squared_hi = s_squared >> 12;
	s_squared_lo = s_squared & 0x0fff;

	x_square_coeff = ( x0 + x2 - ( 2 * x1 ) );
	x_square_term = x_square_coeff * s_squared_hi + ( ( x_square_coeff * s_squared_lo ) >> 12 );

	y_square_coeff = ( y0 + y2 - ( 2 * y1 ) );
	y_square_term = y_square_coeff * s_squared_hi + ( ( y_square_coeff * s_squared_lo ) >> 12 );

	x = ( x_square_term + 2 * s * ( x1 - x0 ) + ( x0 << 12 ) ) >> 4;
	y = ( y_square_term + 2 * s * ( y1 - y0 ) + ( y0 << 12 ) ) >> 4;

	camera_pos_x = x;
	camera_pos_y = y;

	vx = ( 2 * s * x_square_coeff + 2 * ( ( x1 - x0 ) << 12 ) ) >> 8;
	vy = ( 2 * s * y_square_coeff + 2 * ( ( y1 - y0 ) << 12 ) ) >> 8;

	bg_angle = geom_Vector_To_Angle( vx, vy );
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int geom_Vector_To_Angle( int x_comp, int y_comp )
{
	int x_mag;
	int y_mag;
	int ratio;
	int raw_angle;
	int angle = 0;

#if REND_USE_DIVISION

	x_mag = x_comp > 0 ? x_comp : -x_comp;
	y_mag = y_comp > 0 ? y_comp : -y_comp;

	if ( x_mag > y_mag )
	{
		ratio = ( y_mag << 8 ) / x_mag;
	}
	else
	{
		ratio = ( x_mag << 8 ) / y_mag;
	}

	raw_angle = Dmt_Atan_Table[ ratio ];

	if ( x_comp > 0 )
	{
		if ( y_comp > 0 )
		{
			if ( x_mag > y_mag )
			{
				angle = 0x0300 - raw_angle;
			}
			else
			{
				angle = 0x0200 + raw_angle;
			}
		}
		else
		{
			if ( x_mag > y_mag )
			{
				angle = 0x0300 + raw_angle;
			}
			else
			{
				angle = ( 0x0400 - raw_angle ) & 0x03ff;
			}
		}
	}
	else
	{
		if ( y_comp > 0 )
		{
			if ( x_mag > y_mag )
			{
				angle = 0x0100 + raw_angle;
			}
			else
			{
				angle = 0x0200 - raw_angle;
			}
		}
		else
		{
			if ( x_mag > y_mag )
			{
				angle = 0x0100 - raw_angle;
			}
			else
			{
				angle = raw_angle;
			}
		}
	}

#endif

	return angle;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RenderInit( void )
{
	int x;
	int y;
	u16 index;
	u16 * screen_ptr;


	rend_Init_Lods();

//    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 16);  // Set BG character


    DmaCopy(3, rend_fill_from_bux, rendCodeBuf, sizeof(rendCodeBuf), 16);// Interrupt main routine set

	// Set BG palette:
//	DmaArrayCopy(3, Rend_BG_Palettes, BG_PLTT, 16);  
	DmaCopy( 3, Rdt_Palette_Entries, BG_PLTT, Rdt_Palette_Count * 2, 16);  

	// Build screen index table (BG #0, used for 3D):
	screen_ptr = ( u16 * )&BgBak[ 0 ];

	for ( y = 0 ; y < 20 ; y++ )
	{
		index = y;
		for ( x = 0 ; x < 30 ; x++ )
		{
			*screen_ptr = index;
			index += 20;
			screen_ptr++;
		}
		screen_ptr += 2;
	}

	rend_Clear_Screen( 0 );
	dump_Screen_Flg = 1;

    DmaCopy( 3, BgBak, BG_VRAM, 0x0800, 16 );


	// Build screen index table (BG #2, used for Mode 7):

	/*
	for ( x = 0 ; x < 0x0400 ; x++ )
	{
		if ( ( x & 0x0210 ) == 0 )
		{
			BgBak[ x ] = 0x00;
		}
		else
		{
			BgBak[ x ] = 0x01;
		}
	}

	// Send down char map:
    DmaCopy( 3, BgBak, BG_VRAM + 0x0800, 0x0400, 16 );
	*/
	p_rend_Mode7_BBuffer = &rend_Mode7_Buffer_0[ 0 ];
	p_rend_Mode7_FBuffer = &rend_Mode7_Buffer_1[ 0 ];

	rend_Prep_Mode7_Buffer();
	rend_Swap_Mode7_Buffers();
	rend_Prep_Mode7_Buffer();
	rend_Swap_Mode7_Buffers();

	rend_Init_Slot_Array();

//	rend_Load_Terrain( 0x0200, 0x0180 );

//	camera_pos_x = 0x00028000;
//	camera_pos_y = 0x00020000;

#if REND_USE_LOD_1
	rend_Behave_Camera( &rend_Lod_1 );
	rend_Dump_Tiles();
	rend_Dump_Terrain( &rend_Lod_1 );
#else
	rend_Behave_Camera( &rend_Lod_2 );
	rend_Dump_Tiles();
	rend_Dump_Terrain( &rend_Lod_2 );
#endif

	sys_Timer_Init();

	// Send down char data:
//	DmaCopy( 3, &Rdt_Char_Data[0], BG_VRAM + 0x4000, 0x0040 * 208, 16 );


    *(vu16 *)REG_BG0CNT =                             // Set BG control
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_BG2CNT =                             // Set BG control
            BG_COLOR_256 | BG_SCREEN_SIZE_1 | BG_PRIORITY_1 | BG_LOOP_ON
            | 1 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT ;

//    *(vu16 *)REG_IE    = IME_FLAG;                    // Set IME 
    *(vu16 *)REG_IME   = 1;                           // Set IME  

    *(vu16 *)REG_IE   |= V_BLANK_INTR_FLAG | H_BLANK_INTR_FLAG;           // V Blank interrupt permission
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE | STAT_H_BLANK_IF_ENABLE;

	*(vu16 *)REG_BG2PA	= 0x0000;
	*(vu16 *)REG_BG2PB	= 0x0000;
	*(vu16 *)REG_BG2PC	= 0x0000;
	*(vu16 *)REG_BG2PD	= 0x0000;

	*(vu16 *)REG_BG2X_L	= 0x0080;
	*(vu16 *)REG_BG2Y_L	= 0x0080;

    *(vu16 *)REG_DISPCNT = DISP_MODE_1 | DISP_BG0_ON | DISP_BG2_ON; // LCDC ON
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RenderCycle( void )
{
	int f;
	int h;
	int cos_val;
	int sin_val;

	rend_Clear_Screen( 0 );
//	rend_Draw_Triang( &test_triang );
//	Draw_Char( 0, 0, 'A' );
//	Draw_Char( 1, 0, '4' );

	geom_Get_Trig_Ratios( bg_angle, &cos_val, &sin_val );
	bg_cos_val = (u16)cos_val;
	bg_sin_val = (u16)sin_val;

#if REND_USE_LOD_1
	rend_Behave_Camera( &rend_Lod_1 );
#else
	rend_Behave_Camera( &rend_Lod_2 );
#endif

//	Draw_Number( frame_Count );

	sys_Timer_Stop();
	
	Draw_Number( sys_Time_HWM );

	if ( ( frame_Count & 0x00000ff ) == 0 )
	{
		sys_Timer_Mark();
	}

	dump_Screen_Flg = 1;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void sys_Timer_Init( void )
{
	sys_Time_Result = 0;
	sys_Time_IHWM = 0;
	sys_Time_HWM = 0;
}

//////////////////////////////////////////////////////////////////////////////

void sys_Timer_Start( void )
{
	sys_Time_Begin = sys_Get_Time();
}

//////////////////////////////////////////////////////////////////////////////

void sys_Timer_Mark( void )
{
	sys_Time_HWM = sys_Time_IHWM;
	sys_Time_IHWM = 0;
}

//////////////////////////////////////////////////////////////////////////////

void sys_Timer_Stop( void )
{
	sys_Time_Result = sys_Get_Time() - sys_Time_Begin;
	sys_Time_IHWM = sys_Time_Result > sys_Time_IHWM ? sys_Time_Result : sys_Time_IHWM;
}

//////////////////////////////////////////////////////////////////////////////

int sys_Get_Time( void )
{
	int v;
	v = 0x00ff & *( vu16 * )REG_VCOUNT;

	if ( v < 160 )
	{
		v += 68;
	}
	else
	{
		v -= 160;
	}
	
	return ( frame_Rate * 228 ) + v;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void RenderVBlank( void )
{
	frame_Count++;
	frame_Rate++;
	if ( dump_Screen_Flg )
	{
		frame_Rate = 0;
		sys_Timer_Start();

		rend_Dump_Tiles();

#if REND_USE_LOD_1
		rend_Dump_Terrain( &rend_Lod_1 );
#else
		rend_Dump_Terrain( &rend_Lod_2 );
#endif

		rend_Swap_Mode7_Buffers();
		
#if REND_KEEP_3D
		DmaArrayCopy(3, rend_Back_Screen, BG_VRAM+0x8000, 16);  // Set BG character
#endif

//		*(vu16 *)REG_BG2PA	=  bg_cos_val;
//		*(vu16 *)REG_BG2PB	=  bg_sin_val;
//		*(vu16 *)REG_BG2PC	= -bg_sin_val;
//		*(vu16 *)REG_BG2PD	=  bg_cos_val;

		dump_Screen_Flg = 0;
	}
//    DmaArrayCopy(3, BgBak,  BG_VRAM, 16);           // Set BG screen
}

//////////////////////////////////////////////////////////////////////////////

void RenderHBlank( void )
{
	sy = *(vu16 *)REG_VCOUNT;
	sy &= 0x00ff;

	if ( sy < 160 )
	{
		*(vu32 *)REG_BG2X_L = 0x00008000 + Dmt_U_Table[ sy ];
		*(vu32 *)REG_BG2Y_L = 0x00008000 - Dmt_V_Table[ sy ];
		*(vu16 *)REG_BG2PA	= Dmt_DU_Table[ sy ];
		*(vu16 *)REG_BG2PC	= Dmt_DV_Table[ sy ];
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void geom_Get_Trig_Ratios( int angle, int * p_cos, int * p_sin )
{
	int raw_cos;
	int raw_sin;

	int raw_index;
	int quadrant;

	raw_index = angle & 0x00ff;

	raw_cos = Dmt_Cos_Table[ raw_index ];
	raw_sin = Dmt_Cos_Table[ 0x0100 - raw_index ];

	quadrant = ( angle >> 8 ) & 0x03;

	if ( quadrant == 0 )
	{
		*p_cos = raw_cos;
		*p_sin = raw_sin;
	}
	else if ( quadrant == 1 )
	{
		*p_cos = -raw_sin;
//		*p_cos = raw_sin | 0x8000;
		*p_sin = raw_cos;
	}
	else if ( quadrant == 2 )
	{
		*p_cos = -raw_cos;
		*p_sin = -raw_sin;
//		*p_cos = -raw_sin;
//		*p_sin = -raw_cos;
	}
	else
	{
		*p_cos =  raw_sin;
		*p_sin = -raw_cos;
//		*p_sin = -raw_sin;
	}
}

//////////////////////////////////////////////////////////////////////////////

void rend_Clear_Screen( u8 index )
{
#if REND_KEEP_3D
//	u32 *	pixel_ptr;
	u32		fill_value;
	u32		p;
//	u32		i;
	fillFuncPtr p_fill_func;

//	pixel_ptr = &rend_Back_Screen[ 0 ];
	p = index & 0x000f;
	s_fill_colour_long =  ( p << 28 ) 
						| ( p << 24 )
						| ( p << 20 )
						| ( p << 16 )
						| ( p << 12 )
						| ( p <<  8 )
						| ( p <<  4 )
						|   p;

	p_fill_func = ( fillFuncPtr )( (u8 *)&rendCodeBuf[0] ) + ( rend_clear_screen - rend_fill_from_bux );
	p_fill_func();

//	for ( i = 4800 ; i != 0 ; i-- )
//	{
//		*pixel_ptr++ = fill_value;
//	}
#endif
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int * GeomInitTriang( int * p_params, struct geomTriang * p_triang )
{
	u8 v;
	for ( v = 0 ; v < 3 ; v++ )
	{
		p_params = GeomInitPoint( p_params, &p_triang->verts[ v ] );
	}

	return p_params;
}

//////////////////////////////////////////////////////////////////////////////

int * GeomInitPoint( int * p_params, struct geomPoint * p_point )
{
	p_point->x = *p_params++;
	p_point->y = *p_params++;
	p_point->z = *p_params++;

	p_point->x *= GEOM_COORD_STEP;
	p_point->y *= GEOM_COORD_STEP;
	p_point->z *= GEOM_COORD_STEP;

	return p_params;
}

//////////////////////////////////////////////////////////////////////////////

void rend_Init_Bucket( struct geomBucket * p_bucket )
{
	p_bucket->max_y = 0;
	p_bucket->min_y = BUCKET_SIZE - 1;
}

//////////////////////////////////////////////////////////////////////////////

void rend_Draw_Triang( struct geomTriang * p_triang )
{
	u8 v;
	int i;

	struct geomPoint * p_vert_0;
	struct geomPoint * p_vert_1;

	rend_Init_Bucket( &s_left_bucket );
	rend_Init_Bucket( &s_right_bucket );

	p_vert_1 = &p_triang->verts[ 2 ];

	for ( v = 0 ; v < 3 ; v++ )
	{
		p_vert_0 = p_vert_1;
		p_vert_1 = &p_triang->verts[ v ];

//		for ( i = 0 ; i < 1000 ; i++ )
//		{
		rend_Draw_Poly_Edge( p_vert_0, p_vert_1 );
//		}
	}

	rend_Fill_From_Buckets( 3 );
}

//////////////////////////////////////////////////////////////////////////////

void rend_Fill_From_Buckets( ubyte fill_colour )
{
#if REND_KEEP_3D
	/*
	u32 sy;
	u32 sx;

	for ( sy = s_left_bucket.min_y ; sy < s_left_bucket.max_y ; sy++ )
	{
		for ( sx = s_left_bucket.x[ sy ] ; sx < s_right_bucket.x[ sy ] ; sx++ )
		{
			Plot_Pixel( sx, sy, fill_colour );
		}
	}
	*/


	u32 fill_colour_long;
	int sy_min;
	int * p_sx_min;
	int * p_sx_max;
	u32 * p_pixel_line;
	int dsy;
	int sx_min;
	int sx_max;
	int ax;
	int ax_min;
	int ax_max;
	u32 head_mask;
	u32 tail_mask;
	u32 action_mask;
	u32 scratch_pixel;
	u32 * p_pixel;
	int dsx;
	int dsx_head;
	int dsx_body;
	fillFuncPtr p_fill_func;

	/*
	assert	(
				( s_left_bucket.max_y == s_right_bucket.max_y )
			&&	( s_left_bucket.min_y == s_right_bucket.min_y )
			);

	*/

	fill_colour_long =	  ( fill_colour << 28 ) 
						| ( fill_colour << 24 )
						| ( fill_colour << 20 )
						| ( fill_colour << 16 )
						| ( fill_colour << 12 )
						| ( fill_colour <<  8 )
						| ( fill_colour <<  4 )
						|   fill_colour;

	s_fill_colour_long = fill_colour_long;

//	rend_fill_from_bux();

//	p_fill_func = rend_fill_from_bux;
	p_fill_func = ( fillFuncPtr )&rendCodeBuf[0];
	p_fill_func();

	/*
	sy_min = s_left_bucket.min_y;

	p_sx_min = &s_left_bucket.x[ sy_min ];
	p_sx_max = &s_right_bucket.x[ sy_min ];

	p_pixel_line = &rend_Back_Screen[ sy_min ];


	for ( dsy = s_left_bucket.max_y - sy_min ; dsy > 0 ; dsy-- )
	{
		sx_min = *p_sx_min;
		sx_max = *p_sx_max;

		if ( sx_max != sx_min )
		{
			ax_min = sx_min >> 3;
			ax_max = sx_max >> 3;

			p_pixel = p_pixel_line + ( 160 * ax_min );

			head_mask = Rend_Head_Masks[ sx_min & 0x07 ];
			tail_mask = Rend_Tail_Masks[ sx_max & 0x07 ];

			if ( ax_min == ax_max )
			{
				action_mask = head_mask & tail_mask;
				scratch_pixel = ( ~action_mask ) & *p_pixel;
				*p_pixel = scratch_pixel | ( action_mask & fill_colour_long );
			}
			else
			{
				action_mask = head_mask;
				scratch_pixel = ( ~action_mask ) & *p_pixel;
				*p_pixel = scratch_pixel | ( action_mask & fill_colour_long );
				p_pixel += 160;

				for ( ax = ax_min + 1 ; ax < ax_max ; ax++ )
				{
					*p_pixel = fill_colour_long;
					p_pixel += 160;
				}

				action_mask = tail_mask;
				scratch_pixel = ( ~action_mask ) & *p_pixel;
				*p_pixel = scratch_pixel | ( action_mask & fill_colour_long );
			}
		}

		p_sx_min++;
		p_sx_max++;

		p_pixel_line++;
	}
	*/
#endif
}

//////////////////////////////////////////////////////////////////////////////

void rend_Draw_Poly_Edge( struct geomPoint * p_vert_0, struct geomPoint * p_vert_1 )
{
#if REND_KEEP_3D
	struct geomBucket * p_bucket;
	struct geomPoint * p_vert_temp;

	int y_0;
	int y_1;

	int sy_0;
	int sy_1;

	int x_0 = p_vert_0->x;
	int x_1 = p_vert_1->x;

	int delta_x;
	int up_delta_x;

	int k_minus_y_0;
	int init_val_dy;
	
	int ival_0;
	int fval_0;
	int istep_0;
	int fstep_0;
	
	int sy;
	int sx;
	int i;
	fillFuncPtr p_fill_func;

	if ( p_vert_0->y > p_vert_1->y )
	{
		p_vert_temp = p_vert_0;
		p_vert_0 = p_vert_1;
		p_vert_1 = p_vert_temp;
		p_bucket = &s_right_bucket;
	}
	else
	{
		p_bucket = &s_left_bucket;
	}

	y_0 = p_vert_0->y;
	y_1 = p_vert_1->y;

	sy_0 = GeomCoordDownshift( y_0 );
	sy_1 = GeomCoordDownshift( y_1 );

	if ( ( sy_1 - sy_0 ) < 1 )
	{
		// No pixels to draw, so forget it!
		return;
	}

	if ( sy_1 > p_bucket->max_y )
	{
//		assert ( sy_1 < BUCKET_SIZE );
		p_bucket->max_y = sy_1;
	}

	if ( sy_0 < p_bucket->min_y )
	{
//		assert ( sy_0 >= 0 );
		p_bucket->min_y = sy_0;
	}

	x_0 = p_vert_0->x;
	x_1 = p_vert_1->x;

	delta_x = x_1 - x_0;
	up_delta_x = GeomCoordUpshift( delta_x );
	rend_DPE_delta_y = y_1 - y_0;

	k_minus_y_0 = GeomCoordGetFrac( GEOM_COORD_STEP - GeomCoordGetFrac( y_0 ) );
	init_val_dy = k_minus_y_0 * delta_x;

	ival_0 = x_0 + (init_val_dy / rend_DPE_delta_y) + GEOM_COORD_BIAS;
	fval_0 = init_val_dy % rend_DPE_delta_y;

	istep_0 = up_delta_x / rend_DPE_delta_y;
	fstep_0 = up_delta_x % rend_DPE_delta_y;

	rend_DPE_dsy = sy_1 - sy_0;
	rend_DPE_ival = ival_0;
	rend_DPE_fval = fval_0;

	rend_DPE_istep = istep_0;
	rend_DPE_fstep = fstep_0;

	rend_DPE_p_sx = &p_bucket->x[ sy_0 ];

	if ( rend_DPE_fstep < 0 )
	{
		rend_DPE_fstep = -rend_DPE_fstep;
		rend_DPE_fval = -rend_DPE_fval;
		rend_DPE_ifstep = -1;
	}
	else
	{
		rend_DPE_fval -= rend_DPE_delta_y;
		rend_DPE_ifstep = 1;
	}

	p_fill_func = ( fillFuncPtr )( (u8 *)&rendCodeBuf[0] ) + ( rend_edge_to_bux - rend_fill_from_bux );
	p_fill_func();

/*		
		for ( sy = rend_DPE_dsy ; sy > 0 ; sy-- )
		{
//			sx = ival >> GEOM_COORD_SHIFT;
////		sx = GeomCoordDownshift( ival );
//			*p_sx++ = sx;
			*rend_DPE_p_sx++ = rend_DPE_ival;

			rend_DPE_ival += rend_DPE_istep;
			rend_DPE_fval += rend_DPE_fstep;

			if ( rend_DPE_fval > 0 )
			{
				rend_DPE_ival += rend_DPE_ifstep;
//				ival++;
				rend_DPE_fval -= rend_DPE_delta_y;
			}
//			else if ( fval < 0 )
//			{
//				ival--;
//				fval += delta_y;
//			}
		}
*/
#endif
}

//////////////////////////////////////////////////////////////////////////////

void Plot_Pixel( u32 x, u32 y, ubyte fill_colour )
{
#if REND_KEEP_3D
	int pixel_index;
	int pixel_shift;
	u32 pixel_mask;
	u32 pixel_value;
	u32 * p_pixel_block;

	pixel_index = y + ( ( x >> 3 ) * 160 );
	pixel_shift = ( x & 0x0007 ) << 2;
	pixel_mask = ~( 0x000f << pixel_shift );
	pixel_value = fill_colour << pixel_shift;

	p_pixel_block = &rend_Back_Screen[ pixel_index ];
	*p_pixel_block = ( *p_pixel_block & pixel_mask ) | pixel_value;
#endif
}

//////////////////////////////////////////////////////////////////////////////

void Draw_Number( int num )
{
#if REND_USE_DIVISION
	int digits[ 20 ];
	int i;
	int r;
	int d;
	int x;

	i = 0;
	r = num;

	if ( num == 0 )
	{
		digits[ 0 ] = '0';
	}
	else if ( num < 0 )
	{
		digits[ 0 ] = 'M';
	}
	else
	{

		while ( r > 0 )
		{
			d = r % 10;
			r = r / 10;
			digits[ i ] = d + '0';
			i++;
			digits[ i ] = 0;
		}
	}

	x = 0;
	while ( i >= 0 )
	{
		Draw_Char( x, 0, digits[ i ] );
		i--;
		x++;
	}
#endif
}

//////////////////////////////////////////////////////////////////////////////

void Draw_Char( int x, int y, int char_val )
{
#if REND_KEEP_3D
	int i;
	u32 * p_src;
	u32 * p_dest;

	p_src = &CharData_Sample[ char_val << 3 ];
	p_dest = &rend_Back_Screen[ ( y * 8 ) + ( x * 160 ) ];

	for ( i = 0 ; i < 8 ; i++ )
	{
		*p_dest++ = *p_src++;
	}
#endif
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void rend_Prep_Mode7_Buffer( void )
{
	int y;
	u32 * d_ptr;

	d_ptr = p_rend_Mode7_BBuffer;

	for ( y = 0 ; y < 160 ; y++ )
	{
		*d_ptr++ = 0x00000000;
		*d_ptr++ = 0x00000000;
		*d_ptr++ = 0x00000000;
		*d_ptr++ = 0x00000000;
	}
}

//////////////////////////////////////////////////////////////////////////////

void rend_Behave_Camera( struct rendLod * p_lod )
{
	int y;
//	int split;
//	int end;

	u32 * d_ptr;
	const u32 * u_ptr;
	const u32 * v_ptr;
	const u16 * du_ptr;
//	const u16 * dv_ptr;

	int cos_val;
	int sin_val;

	int cos_disp;
	int sin_disp;

	int ucu;
	int u1;
	int u2;
	int ucw;
	int u_min;
	int uc;
	int u;

	int vcu;
	int v1;
	int v2;
	int vcw;
	int v_min;
	int vc;
	int v;

	int du;

/*
#if REND_USE_LOD_1
	split = 80;
	end = 160
#else
	split = 60;
	end = 80;
#endif
*/
	// Determine camera FOV (just MML #0 for now)
	geom_Get_Trig_Ratios( bg_angle, &cos_val, &sin_val );

	cos_disp = ( cos_val * 120 ) << p_lod->lod_log;
	sin_disp = ( sin_val * 120 ) << p_lod->lod_log;

	ucu = camera_pos_x;
	vcu = camera_pos_y;

	uc = ucu >> 8;
	vc = vcu >> 8;

	u1 = ( ucu - cos_disp - sin_disp ) >> 8;
	v1 = ( vcu + sin_disp - cos_disp ) >> 8;
		      
	u2 = ( ucu + cos_disp - sin_disp ) >> 8;
	v2 = ( vcu - sin_disp - cos_disp ) >> 8;

	u_min = ( uc < u1 ) ? uc : u1;
	if ( u_min > u2 )
	{
		u_min = u2;
	}
	u_min &= ( 0xfffffff0 << p_lod->lod_log );

	v_min = ( vc < v1 ) ? vc : v1;
	if ( v_min > v2 )
	{
		v_min = v2;
	}
	v_min &= ( 0xfffffff8 << p_lod->lod_log );


//	sys_Timer_Start();
	rend_Smart_Load_Terrain( u_min, v_min, p_lod );
//	sys_Timer_Stop();

	ucw = ( ucu - ( u_min << 8 ) ) << ( 8 - p_lod->lod_log );
	vcw = ( vcu - ( v_min << 8 ) ) << ( 8 - p_lod->lod_log );

	u_ptr	= &Dmt_U_Table[ p_lod->split ];
	v_ptr	= &Dmt_V_Table[ p_lod->split ];
	du_ptr	= &Dmt_DU_Table[ p_lod->split ];
//	dv_ptr	= &Dmt_DV_Table[ split ];

	d_ptr = &p_rend_Mode7_BBuffer[ p_lod->split * 4 ];


	for ( y = p_lod->split ; y < p_lod->end ; y++ )
	{
		u = *u_ptr++;
		v = *v_ptr++;
		du = *du_ptr++;

		*d_ptr++ = ( ( u * cos_val ) - ( v * sin_val ) + ucw ) >> 8;
		*d_ptr++ = ( -( u * sin_val ) - ( v * cos_val ) + vcw ) >> 8;
		*d_ptr++ = ( du * cos_val ) >> 8;
		*d_ptr++ = ( du * -sin_val ) >> 8;
	}

}


//////////////////////////////////////////////////////////////////////////////

void rend_Swap_Mode7_Buffers( void )
{
	u32 * p_temp;

	p_temp					= p_rend_Mode7_BBuffer;
	p_rend_Mode7_BBuffer	= p_rend_Mode7_FBuffer;
	p_rend_Mode7_FBuffer	= p_temp;
}

//////////////////////////////////////////////////////////////////////////////

void rend_Smart_Load_Terrain( int u, int v, struct rendLod * p_lod )
{
	bool okay_in_u_and_v;
	
	okay_in_u_and_v = rend_Terrain_Ok_In_U( u, p_lod ) && rend_Terrain_Ok_In_V( v, p_lod );

	if ( !okay_in_u_and_v )
	{
		// Too much movement along one or both axes, so
		// we'll have to refresh the whole buffer:
		rend_Load_Terrain( u, v, p_lod );
	}

#if REND_CHECK_TW
	rend_LTW_Check();
#endif
}


//////////////////////////////////////////////////////////////////////////////

bool rend_Terrain_Ok_In_U( int u, struct rendLod * p_lod )
{
	int du;
	int win_dest_idx;
	int win_u;
	int win_0_h;
	int win_1_h;
	int win_1_v;

	du = ( u & 0xfffffff0 ) - p_lod->old_u;

	if ( du == 0 )
	{
		return true;
	}
	else if ( du ==  ( 16 << p_lod->lod_log ) )
	{
		// Moved 2 columns to the right, so scroll and fetch:
		win_dest_idx = ( p_lod->old_dest_idx + 32 ) & 0x000003ff;

		win_u = ( u + ( 30 << ( 3 + p_lod->lod_log ) ) ) & 0x0fff;

		win_0_h = ( 0x041f - win_dest_idx ) >> 5;

		rend_Load_Terrain_Window( win_u, p_lod->old_v, win_dest_idx, 2, win_0_h, p_lod );

		if ( win_0_h < 32 )
		{
			win_1_v = ( p_lod->old_v + ( win_0_h << ( 3 + p_lod->lod_log ) ) ) & 0x0fff;
			win_1_h = 32 - win_0_h;

			rend_Load_Terrain_Window( win_u, win_1_v, win_dest_idx & 0x001f, 2, win_1_h, p_lod );
		}

		p_lod->old_u = u;
		p_lod->old_dest_idx = ( p_lod->old_dest_idx + 2 ) & 0x000003ff;

		return true;
	}
	else if ( du == ( -16 << p_lod->lod_log ) )
	{
		// Moved 2 columns to the left, so scroll and fetch:
		win_dest_idx = ( p_lod->old_dest_idx - 2 ) & 0x000003ff;

		win_u = u;

		win_0_h = ( 0x041f - win_dest_idx ) >> 5;

		rend_Load_Terrain_Window( win_u, p_lod->old_v, win_dest_idx, 2, win_0_h, p_lod );

		if ( win_0_h < 32 )
		{
			win_1_v = ( p_lod->old_v + ( win_0_h << ( 3 + p_lod->lod_log ) ) ) & 0x0fff;
			win_1_h = 32 - win_0_h;

			rend_Load_Terrain_Window( win_u, win_1_v, win_dest_idx & 0x001f, 2, win_1_h, p_lod );
		}

		p_lod->old_u = u;
		p_lod->old_dest_idx = win_dest_idx;

		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////

bool rend_Terrain_Ok_In_V( int v, struct rendLod * p_lod )
{
	int dv;
	int win_dest_idx;
	int win_v;
	int win_0_w;
	int win_1_w;
	int win_1_u;
	int bytes_left;

	dv = ( v & 0xfffffff8 ) - p_lod->old_v;

	if ( dv == 0 )
	{
		return true;
	}
	else if ( dv == ( 8 << p_lod->lod_log ) )
	{
		// Moved 1 line down, so scroll and fetch:
		win_dest_idx = p_lod->old_dest_idx;

		win_v = ( v + ( 31 << ( 3 + p_lod->lod_log ) ) ) & 0x0fff;

		bytes_left = 0x0400 - win_dest_idx;
		win_0_w = bytes_left < 32 ? bytes_left : 32;

		rend_Load_Terrain_Window( p_lod->old_u, win_v, win_dest_idx, win_0_w, 1, p_lod );

		if ( win_0_w < 32 )
		{
			win_1_u = ( p_lod->old_u + ( win_0_w << ( 3 + p_lod->lod_log ) ) ) & 0x0fff;
			win_1_w = 32 - win_0_w;

			rend_Load_Terrain_Window( win_1_u, win_v, 0, win_1_w, 1, p_lod );
		}

		p_lod->old_v = v;
		p_lod->old_dest_idx = ( p_lod->old_dest_idx + 32 ) & 0x000003ff;

		return true;
	}
	else if ( dv == ( -8 << p_lod->lod_log ) )
	{
		// Moved 1 line up, so scroll and fetch:
		win_dest_idx = ( p_lod->old_dest_idx - 32 ) & 0x000003ff;

		win_v = v;

		bytes_left = 0x0400 - win_dest_idx;
		win_0_w = bytes_left < 32 ? bytes_left : 32;

		rend_Load_Terrain_Window( p_lod->old_u, win_v, win_dest_idx, win_0_w, 1, p_lod );

		if ( win_0_w < 32 )
		{
			win_1_u = ( p_lod->old_u + ( win_0_w << ( 3 + p_lod->lod_log ) ) ) & 0x0fff;
			win_1_w = 32 - win_0_w;

			rend_Load_Terrain_Window( win_1_u, win_v, 0, win_1_w, 1, p_lod );
		}

		p_lod->old_v = v;
		p_lod->old_dest_idx = win_dest_idx;

		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////

void rend_Load_Terrain( int u, int v, struct rendLod * p_lod )
{
	p_lod->old_u = u & ( 0xfffffff0 << p_lod->lod_log );
	p_lod->old_v = v & ( 0xfffffff8 << p_lod->lod_log );
	p_lod->old_dest_idx = 0;

	rend_Load_Terrain_Window( u, v, 0, 32, 32, p_lod );
}

//////////////////////////////////////////////////////////////////////////////

void rend_Load_Terrain_Window( int u, int v, int dest_idx, int width, int height, struct rendLod * p_lod )
{
	u8 * p_char_map_start;

	p_char_map_start = &p_lod->p_terrain_win[ dest_idx ];
	rend_Load_Terrain_Window_Sub( u, v, p_char_map_start, width, height, p_lod );
}

//////////////////////////////////////////////////////////////////////////////

void rend_LTW_Check( void )
{
#if REND_CHECK_TW
	int i;
	u8 * p_char_map;

	rend_Load_Terrain_Window_Sub( s_old_u, s_old_v, &rend_TW_Check_Buff[ 0 ], 32, 32 );

	for ( i = 0 ; i < 0x0400 ; i++ )
	{
		while( rend_TW_Check_Buff[ i ] != BgBak[ ( i + s_old_dest_idx ) & 0x03ff ] )
		{
			p_char_map = "Terrain window scroll error!";
		}
	}
#endif
}

//////////////////////////////////////////////////////////////////////////////

void rend_Load_Terrain_Window_Sub( int u, int v, u8 * p_char_map_start, int width, int height, struct rendLod * p_lod )
{
	int bx;
	int by;
	int cx;
	int cy;
	int tx;
	int ty;
	int ci;
	int ti;
	int rx;
	int ry;
	int c_slot;
	u8 * p_char_map;
	u8 * p_char_map_row;

	const u16 * p_ci;
	const u8 * p_ti;
	int count;
	int cols_left;

//	int lod_log = 0;
	int c_mask = 0x07 >> p_lod->lod_log;
	int t_shift = 3 - p_lod->lod_log;

/*
#if REND_USE_LOD_1
	p_tile_to_char = &Rdt_Lod1_Tile_To_Char[ 0 ];
	p_char_to_slot = &Rdt_Lod1_Char_To_Slot[ 0 ];
#else
	p_tile_to_char = &Rdt_Lod2_Tile_To_Char_Ary[ 0 ];
	p_char_to_slot = &Rdt_Lod2_Char_To_Slot_Ary[ 0 ];
#endif
*/


	bx = u >> ( 3 + p_lod->lod_log );
	by = v >> ( 3 + p_lod->lod_log );

	while ( u & 0x01 )
	{
		p_char_map = "Bad value - u is odd!";
	}

	// Get ptr to BG char map buffer:
//	p_char_map_row = &BgBak[ dest_idx ];
	p_char_map_row = p_char_map_start;

	for ( ry = by ; ry < by + height ; ry++ )
	{
		cy = ( ry & c_mask ) << t_shift;
		ty = ( ( ry >> t_shift ) & 0x3f ) << 6;

		p_char_map = p_char_map_row;
		p_char_map_row += 32;

		for ( rx = bx ; rx < bx + width ; rx += 2 )
		{
			cx = rx & c_mask;
			tx = ( rx >> t_shift ) & 0x3f;

			ti = Rdt_Tile_Map_Ary[ tx + ty ];
			
			p_ci = &p_lod->p_tile_to_char[ ( ti << ( 6 - ( p_lod->lod_log << 1 ) ) ) + cx + cy ];

			//////////////

			ci = *p_ci++;

			c_slot = p_lod->p_char_to_slot[ ci ];

			if ( ( rend_Slot_Id_Xref[ c_slot ] & 0x3fff ) != ci )
			{
				while ( rend_Slot_Id_Xref[ c_slot ] & 0x4000 )
				{
				}

				rend_Slot_Id_Xref[ c_slot ] = ci | 0x4000;
			}

			*p_char_map = c_slot;
			p_char_map++;

			//////////////

			ci = *p_ci++;

			c_slot = p_lod->p_char_to_slot[ ci ];

			if ( ( rend_Slot_Id_Xref[ c_slot ] & 0x3fff ) != ci )
			{
				while ( rend_Slot_Id_Xref[ c_slot ] & 0x4000 )
				{
				}

				rend_Slot_Id_Xref[ c_slot ] = ci | 0x4000;
			}

			*p_char_map = c_slot;
			p_char_map++;

			//////////////

		}
	}
}

//////////////////////////////////////////////////////////////////////////////

void rend_Init_Slot_Array( void )
{
	int i;

	for ( i = 0 ; i < 256 ; i++ )
	{
		rend_Slot_Id_Xref[ i ] = 0x3fff;
	}
}

//////////////////////////////////////////////////////////////////////////////

void rend_Dump_Tiles( void )
{
	int i;
	int s_idx;
	int d_idx;

	const u8 * p_char_data;

/*
#if REND_USE_LOD_1
	const u8 * p_char_data = &Rdt_Lod1_Char_Data[ 0 ];
#else
	const u8 * p_char_data = &Rdt_Lod2_Char_Data[ 0 ];
#endif
*/

	p_char_data = &Rdt_Lod1_Char_Data[ 0 ];

	for ( i = 0 ; i < Rdt_Lod1_Slot_Count ; i++ )
	{
		if ( rend_Slot_Id_Xref[ i ] > 0x3fff )
		{
			s_idx = rend_Slot_Id_Xref[ i ] & 0x3fff;
			rend_Slot_Id_Xref[ i ] = s_idx;

			s_idx <<= 6;
			d_idx =	i << 6;
		    DmaCopy( 3, p_char_data + s_idx, BG_VRAM + 0x4000 + d_idx, 0x0040, 16 );
			DmaWait( 3 );
		}
	}

	p_char_data = &Rdt_Lod2_Char_Data[ 0 ];

	for ( i = Rdt_Lod1_Slot_Count ; i < Rdt_Lod2_Slot_Count ; i++ )
	{
		if ( rend_Slot_Id_Xref[ i ] > 0x3fff )
		{
			s_idx = rend_Slot_Id_Xref[ i ] & 0x3fff;
			rend_Slot_Id_Xref[ i ] = s_idx;


			s_idx <<= 6;
			d_idx =	i << 6;
		    DmaCopy( 3, p_char_data + s_idx, BG_VRAM + 0x4000 + d_idx, 0x0040, 16 );
			DmaWait( 3 );
		}
	}

	p_char_data = &Rdt_Lod4_Char_Data[ 0 ];

	for ( i = Rdt_Lod2_Slot_Count ; i < 256 ; i++ )
	{
		if ( rend_Slot_Id_Xref[ i ] > 0x3fff )
		{
			s_idx = rend_Slot_Id_Xref[ i ] & 0x3fff;
			rend_Slot_Id_Xref[ i ] = s_idx;


			s_idx <<= 6;
			d_idx =	i << 6;
		    DmaCopy( 3, p_char_data + s_idx, BG_VRAM + 0x4000 + d_idx, 0x0040, 16 );
			DmaWait( 3 );
		}
	}

//    DmaCopy( 3, &Rdt_Char_Data[0], BG_VRAM + 0x4000, 0x0040 * 208, 16 );
}

//////////////////////////////////////////////////////////////////////////////

void rend_Dump_Terrain( struct rendLod * p_lod )
{
	int i;
	int src_idx;
	int bytes_left;

	for ( i = 0x0000 ; i < 0x0400 ; i += 0x0020 )
	{
		src_idx = ( p_lod->old_dest_idx + i ) & 0x000003ff;
		bytes_left = 0x0400 - src_idx;

		if ( bytes_left < 0x0020 )
		{
			DmaCopy( 3, p_lod->p_terrain_win + src_idx, BG_VRAM + 0x0800 + i, bytes_left, 16 );
			DmaWait( 3 );

			DmaCopy( 3, p_lod->p_terrain_win, BG_VRAM + 0x0800 + i + bytes_left, 0x0020 - bytes_left, 16 );
			DmaWait( 3 );
		}
		else
		{
			DmaCopy( 3, p_lod->p_terrain_win + src_idx, BG_VRAM + 0x0800 + i, 0x0020, 16 );
			DmaWait( 3 );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////

void rend_Init_Lods( void )
{
	rend_Lod_1.lod_log			= 0;
	rend_Lod_1.old_u			= 0;
	rend_Lod_1.old_v			= 0;
	rend_Lod_1.old_dest_idx		= 0;
	rend_Lod_1.split			= 80;
	rend_Lod_1.end				= 160;
	rend_Lod_1.p_terrain_win	= &BgBak[ 0 ];
	rend_Lod_1.p_tile_to_char	= &Rdt_Lod1_Tile_To_Char_Ary[ 0 ];
	rend_Lod_1.p_char_to_slot	= &Rdt_Lod1_Char_To_Slot_Ary[ 0 ];

	rend_Lod_2.lod_log			= 1;
	rend_Lod_2.old_u			= 0;
	rend_Lod_2.old_v			= 0;
	rend_Lod_2.old_dest_idx		= 0;
	rend_Lod_2.split			= 60;
	rend_Lod_2.end				= 80;
	rend_Lod_2.p_terrain_win	= &BgBak[ 0x0400 ];
	rend_Lod_2.p_tile_to_char	= &Rdt_Lod2_Tile_To_Char_Ary[ 0 ];
	rend_Lod_2.p_char_to_slot	= &Rdt_Lod2_Char_To_Slot_Ary[ 0 ];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


