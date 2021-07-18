// Experimental Raytracing for AGB
//
// 4 objects + shadows + reflections
//
// guano
//       guano_99@hotmail.com

#include <math.h>

typedef unsigned char byte;
typedef unsigned short hword;
typedef unsigned long word;

#define PI 3.141592654

void putpixel(byte px,byte py,word colr,word colg,word colb)
{
 hword col=(colb<<10)|(colg<<5)|colr;
 __asm {
         mov    r0, py
         mov    r1,#480
         mul    r2,r0,r1
         mov    r1,px
         add    r2,r2,r1
         add    r2,r2,r1
         mov    r0,#0x6000000
         add    r0,r0,r2
         mov    r1,col
         strh   r1,[r0],1
      }
}


#include "ray.c"


int C_entry(void)
{
 *(word*)0x4000000=3;
 *(word*)0x4000004=8;

 trace();
 while(1);

 return 0;
}

