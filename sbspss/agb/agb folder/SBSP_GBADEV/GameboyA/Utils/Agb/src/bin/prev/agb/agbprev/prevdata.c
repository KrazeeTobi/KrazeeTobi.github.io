#include <agbtypes.h>
#include "prevdata.h"
#include <nodes.h>

const nodeDispHeader DefaultDispHeader = {
0x1040,	// DISPCNT
0x0000,	// BG0CNT
0x0000,	// BG1CNT
0x0000,	// BG2CNT
0x0000,	// BG3CNT
};

const u32 RootObjects_Table[1] = {
0,
};

const nodeRootObjects RootObjects = {
1,
1,
(u32*)RootObjects_Table
};

const nodeRootBGs RootBGs = {
0xffffffff,
0,
0xffff,
0x0000,
{
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
}
};

const u32 node_table[14] = {
(u32)(&obj1Object),
(u32)(&pal1Image),
(u32)(&anim1Animation),
(u32)(&ballImage),
(u32)(&sw1Switch),
(u32)(&sw2Switch),
(u32)(&sw3Switch),
(u32)(&sw4Switch),
(u32)(&sw5Switch),
(u32)(&fb1FlipBook),
(u32)(&rot1Rotation),
(u32)(&scl1Scale),
(u32)(&ofs1Offset),
(u32)(&mv1Move),
};

const nodeOffsetTable node_offset_table = {
14,
(u32*)node_table
};
const nodeHeaderChunk prev_node_header = {
{
0,
0,
0
},
&node_offset_table,
&DefaultDispHeader,
&RootObjects,
&RootBGs
};

const nodeObject obj1Object = {
{
    0,
    32,
    0
} ,
0x4000 ,0x4000 ,0x0000 ,
16,
16,
0,
0,
0x0000,0x0000,
60,
6,
3,
2,
0,
(u32*)(0)
};


const u16 pal1Image_data[256] = {
0x0000 ,0x0842 ,0xdb3a ,0x2129 ,0xefff ,0xced6 ,0xe7bd ,0xcab5 ,
0xe39c ,0xdf7b ,0xc273 ,0xba31 ,0x2dce ,0x258c ,0x14e7 ,0xffff ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,
};

const nodeImage pal1Image= {
{
    2,
    532,
    5
} ,
256,
1,
16,
1,
(u8*)pal1Image_data
};

const u32 anim1Animation_child[5] = {
4,
5,
6,
7,
8,
};
const nodeAnimation anim1Animation = {
{
    3,
    36,
    10
} ,
5,
(u32*)anim1Animation_child
};


const u8 ballImage_data[512] = {
//	<0>
//  (0,0)
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x10 ,0x51 ,0x55 ,0x10 ,0x2c ,0x28 ,0x89 ,

//  (1,0)
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x55 ,0x12 ,0x01 ,0x00 ,0x66 ,0x66 ,0xbf ,0x01 ,

//  (0,1)
0x50 ,0x29 ,0x82 ,0x99 ,0x5b ,0x22 ,0x22 ,0x99 ,
0x52 ,0x25 ,0x25 ,0x22 ,0x55 ,0x55 ,0x22 ,0x22 ,
0xac ,0x55 ,0x55 ,0x52 ,0xb0 ,0xbb ,0xaa ,0xaa ,
0x00 ,0xce ,0xcc ,0xcc ,0x00 ,0x10 ,0xd1 ,0xdd ,

//  (1,1)
0x88 ,0x66 ,0x66 ,0x09 ,0x88 ,0x88 ,0x86 ,0xb9 ,
0x92 ,0x99 ,0x99 ,0xb5 ,0x22 ,0x92 ,0x55 ,0xcb ,
0x52 ,0x52 ,0xcb ,0xdc ,0xba ,0xcb ,0xcc ,0x0c ,
0xcc ,0xcc ,0xeb ,0x00 ,0xdd ,0x1d ,0x01 ,0x00 ,

//	<1>
//  (0,0)
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0xb0 ,0x2b ,0x89 ,0x00 ,0x9a ,0x99 ,0x89 ,
0x50 ,0x22 ,0x92 ,0x99 ,0x2e ,0x52 ,0x22 ,0x99 ,

//  (1,0)
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x68 ,0xb6 ,0x0a ,0x00 ,0x68 ,0xf6 ,0x26 ,0x00 ,
0x88 ,0x66 ,0x66 ,0x08 ,0x88 ,0x68 ,0x86 ,0xe8 ,

//  (0,1)
0x52 ,0x95 ,0x22 ,0x92 ,0x55 ,0x52 ,0x22 ,0x92 ,
0x55 ,0x55 ,0x52 ,0x22 ,0xa5 ,0x55 ,0x25 ,0x52 ,
0xae ,0x5a ,0x55 ,0x55 ,0xb0 ,0xbb ,0xab ,0xaa ,
0x00 ,0xcd ,0xcb ,0xcc ,0x00 ,0xd0 ,0xce ,0xcc ,

//  (1,1)
0x89 ,0x88 ,0x98 ,0x52 ,0x92 ,0x99 ,0x29 ,0xc5 ,
0x22 ,0x22 ,0x52 ,0xcb ,0x22 ,0x52 ,0xb5 ,0xbc ,
0x55 ,0xb5 ,0xcc ,0x1c ,0xbb ,0xcc ,0xcc ,0x0c ,
0xcc ,0xcc ,0xdb ,0x00 ,0xcc ,0xdc ,0x0e ,0x00 ,

//	<2>
//  (0,0)
0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x10 ,0x73 ,0x86 ,
0x00 ,0xa1 ,0x96 ,0x89 ,0x10 ,0x9a ,0x22 ,0x99 ,
0xe0 ,0x28 ,0x22 ,0x89 ,0xa0 ,0x25 ,0x22 ,0x99 ,
0x50 ,0x55 ,0x22 ,0x92 ,0x50 ,0x25 ,0x25 ,0x22 ,

//  (1,0)
0x00 ,0x00 ,0x00 ,0x00 ,0x46 ,0x35 ,0x01 ,0x00 ,
0x68 ,0x44 ,0x15 ,0x00 ,0x68 ,0x66 ,0x54 ,0x01 ,
0x68 ,0x68 ,0x46 ,0x03 ,0x88 ,0x68 ,0x88 ,0x0a ,
0x89 ,0x89 ,0x98 ,0x07 ,0x92 ,0x99 ,0x59 ,0x0b ,

//  (0,1)
0x50 ,0x55 ,0x22 ,0x22 ,0x70 ,0x55 ,0x25 ,0x25 ,
0xc0 ,0x5a ,0x57 ,0x25 ,0xe0 ,0xaa ,0x7a ,0x77 ,
0x10 ,0xbd ,0xbc ,0xbc ,0x00 ,0xd0 ,0xcc ,0xcc ,
0x00 ,0x00 ,0xde ,0xcc ,0x00 ,0x00 ,0x00 ,0x00 ,

//  (1,1)
0x92 ,0x22 ,0xa2 ,0x0c ,0x22 ,0x52 ,0xca ,0x0c ,
0x55 ,0xa5 ,0xcb ,0x0d ,0xa7 ,0xcb ,0xbd ,0x01 ,
0xcc ,0xcc ,0x3b ,0x01 ,0xcc ,0xbc ,0x13 ,0x00 ,
0xcc ,0xe3 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,

//	<3>
//  (0,0)
0x00 ,0x00 ,0xd0 ,0x86 ,0x00 ,0x00 ,0x22 ,0x89 ,
0x00 ,0xa0 ,0x22 ,0x89 ,0x00 ,0x2c ,0x22 ,0x99 ,
0x00 ,0x9c ,0x22 ,0x89 ,0x00 ,0x25 ,0x25 ,0x92 ,
0x00 ,0x55 ,0x22 ,0x92 ,0x00 ,0x25 ,0x22 ,0x22 ,

//  (1,0)
0xf6 ,0x0d ,0x00 ,0x00 ,0x68 ,0x66 ,0x00 ,0x00 ,
0x68 ,0x66 ,0x05 ,0x00 ,0x68 ,0x66 ,0xbf ,0x00 ,
0x88 ,0x66 ,0xb6 ,0x00 ,0x89 ,0x88 ,0x58 ,0x00 ,
0x99 ,0x88 ,0x58 ,0x00 ,0x99 ,0x99 ,0xa2 ,0x00 ,

//  (0,1)
0x00 ,0x55 ,0x25 ,0x22 ,0x00 ,0x55 ,0x55 ,0x22 ,
0x00 ,0xaa ,0x55 ,0x55 ,0x00 ,0xad ,0x5a ,0x55 ,
0x00 ,0xbe ,0xba ,0xba ,0x00 ,0xd0 ,0xcc ,0xcc ,
0x00 ,0x00 ,0xcc ,0xcc ,0x00 ,0x00 ,0x10 ,0xcb ,

//  (1,1)
0x22 ,0x22 ,0xb5 ,0x00 ,0x22 ,0x52 ,0xcb ,0x00 ,
0x52 ,0xa5 ,0xcc ,0x00 ,0xa5 ,0xcb ,0xeb ,0x00 ,
0xbb ,0xcc ,0xdc ,0x00 ,0xcc ,0xcc ,0x0d ,0x00 ,
0xcc ,0xcc ,0x00 ,0x00 ,0xbc ,0x0e ,0x00 ,0x00 ,

};

const nodeImage ballImage= {
{
    2,
    532,
    16
} ,
16,
16,
4,
4,
(u8*)ballImage_data
};


const nodeSwitchState sw1Switch_State[2] = {
{   0 , 9 },
{   5 , 9 },
};

const nodeSwitch sw1Switch = {
{
    4,
    32,
    21
} ,
2 ,
(nodeSwitchState*)sw1Switch_State
};


const nodeSwitchState sw2Switch_State[2] = {
{   1 , 10 },
{   5 , 10 },
};

const nodeSwitch sw2Switch = {
{
    4,
    32,
    25
} ,
2 ,
(nodeSwitchState*)sw2Switch_State
};


const nodeSwitchState sw3Switch_State[2] = {
{   2 , 11 },
{   5 , 11 },
};

const nodeSwitch sw3Switch = {
{
    4,
    32,
    29
} ,
2 ,
(nodeSwitchState*)sw3Switch_State
};


const nodeSwitchState sw4Switch_State[2] = {
{   3 , 12 },
{   5 , 12 },
};

const nodeSwitch sw4Switch = {
{
    4,
    32,
    33
} ,
2 ,
(nodeSwitchState*)sw4Switch_State
};


const nodeSwitchState sw5Switch_State[2] = {
{   4 , 13 },
{   5 , 13 },
};

const nodeSwitch sw5Switch = {
{
    4,
    32,
    37
} ,
2 ,
(nodeSwitchState*)sw5Switch_State
};


const nodeFlipBookKey fb1FlipBook_Key[7] = {
{ 0, 0, 0, 0} ,
{ 5, 1, 0, 0} ,
{ 10, 2, 0, 0} ,
{ 15, 3, 0, 0} ,
{ 20, 2, 0, 0} ,
{ 25, 1, 0, 0} ,
{ 30, 0, 0, 0} ,
} ;

const nodeFlipBook fb1FlipBook = {
{
    6,
    62,
    41
} ,
3,
30,
7,
(nodeFlipBookKey*)fb1FlipBook_Key
} ;


const nodeRotateAnimKey rot1Rotation_Key[3] = {
{ 0, 0} ,
{ 30, 128} ,
{ 60, 255} ,
} ;

const nodeRotateAnim rot1Rotation = {
{
    7,
    30,
    45
} ,
60,
1,	//  Linear
3,
(nodeRotateAnimKey*)rot1Rotation_Key
} ;


const nodeScaleAnimKey scl1Scale_Key[5] = {
{ 0, 256, 256} ,
{ 15, 128, 512} ,
{ 30, 256, 256} ,
{ 45, 512, 128} ,
{ 60, 256, 256} ,
} ;

const nodeScaleAnim scl1Scale = {
{
    9,
    48,
    50
} ,
60,
1,	//  Linear
5,
(nodeScaleAnimKey*)scl1Scale_Key
} ;


const nodeOffsetAnimKey ofs1Offset_Key[5] = {
{ 0, 0, 0} ,
{ 15, 0, 3840} ,
{ 30, 3840, 0} ,
{ 45, 0, -3840} ,
{ 60, 0, 0} ,
} ;

const nodeOffsetAnim ofs1Offset = {
{
    10,
    48,
    55
} ,
60,
1,	//  Linear
5,
(nodeOffsetAnimKey*)ofs1Offset_Key
} ;


const nodeMoveAnimKey mv1Move_Key[5] = {
{ 0, 512, 0} ,
{ 15, 0, 512} ,
{ 30, -512, 0} ,
{ 45, 0, -512} ,
{ 60, 0, 0} ,
} ;

const nodeMoveAnim mv1Move = {
{
    11,
    48,
    60
} ,
60,
0,	//  Const
5,
(nodeMoveAnimKey*)mv1Move_Key
} ;

