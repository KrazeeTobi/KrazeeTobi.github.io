// 'Around the World' demo
// Mic, 2001
// stabmaster_@hotmail.com | come.to/progzone
//
// All key-input code was derived from Nokturn's key demo.
// The hand8x16 font is the work of David Cuny.
//



#include <stdlib.h>
#include <math.h>
#include "gbal.h"

#define KEYREG   *(u16 *)0x04000130


extern u8 miku_raw,miku_pal;
extern u8 bahamas,belgium,chile,denmark,finland,france,germany,greece,iceland,
          india,ireland,italy,kuwait,monaco,netherlands,norway,spain,sweden,
          switzerland,trinidad,usa;
extern u8 hand8x16,sys8x16;


long camX,camY,camZ;

POINT flag[264];
float points3d[792];

float sine[256];
u8 ang[2];


u8 base_col[8] = {7,39,71,103,135,167,199,230};
u8 basecol;

u8 *map, map_ij;
int country;
u8 text_xpos;
char *name;




// float[3] -> POINT
void Project(float *src, long *dest, int num_points)
{
int i,si,di;
float sx,sy,sz;

   si = 0;
   di = 0;
   for (i=0; i<num_points; i++)
   {
      sx = src[si]; 
      sy = src[si+1];
      sz = src[si+2];
    
      // !!! calculate the colour of each vertex. !!!
      dest[di+2] = (long)((sz+9.5f)*1.14f);
  
      si += 3;
      sz += (float)(camZ);
      if (sz!=0)
      {
         dest[di] = (long)((FOCAL*sx)/sz)+camX;
         dest[di+1] = (long)((FOCAL*sy)/sz)+camY;
      }else
      {
         dest[di] = camX;
         dest[di+1] = camY;
      }
      di += 5;
   }
}





void draw_section()
{
u32 y,col32;
long x1,x2;
u8 *dest,*last_dest;
long clipped;

  if (dsdata.y1 >= RContext.height) return;
  if (dsdata.y2 < 0) return;

  col32 = dsdata.c1 + basecol;
  col32 |= (col32<<8);
  col32 |= (col32<<16);

  if (dsdata.y1<0)  
  {
    clipped = 0-dsdata.y1;
    dsdata.x1 += (dsdata.dxdy1*clipped);
    dsdata.x2 += (dsdata.dxdy2*clipped);
    dsdata.y1 = 0;
  }
  if (dsdata.y2 >= RContext.height) dsdata.y2 = (RContext.height-1);
  dest = (RContext.buffer + (dsdata.y1*RContext.width));

  for (y=dsdata.y1; y<=dsdata.y2; y++)  
  {
    if (dsdata.x1 <= dsdata.x2)
    {
      x1 = dsdata.x1;
      x2 = dsdata.x2;
    }else
    {
      x1 = dsdata.x2;
      x2 = dsdata.x1;
    }
    x1 >>= 9;
    x2 >>= 9;
    if ((x1<RContext.width)&&(x2>=0))
    {
      last_dest = dest;
      dest += x1;
      __asm
      {
        mov r0,dest
        mov r1,x2
        mov r2,x1
        sub r1,r1,r2
        add r1,r1,#1
        mov r2,col32
         Draw:
           strb r2,[r0],#1
           subs r1,r1,#1
         bne Draw
      }
      dest = last_dest;
    } 
    if (y<dsdata.y2)
    {
      dest += RContext.width;
      dsdata.x1 += dsdata.dxdy1;
      dsdata.x2 += dsdata.dxdy2;
    }
  }
}



void blur()
{
u32 col32;
int i,j;
long offs=4840;

  for (i=0;i<120;i++)
  {
    for (j=0;j<160;j++)
    {
      col32 = *(u8 *)(FRONT+offs-1);
      col32 += *(u8 *)(FRONT+offs+1);
      col32 += *(u8 *)(FRONT+offs-240);
      col32 += *(u8 *)(FRONT+offs+240);
      *(u8 *)(FRONT+offs) = (u8)(col32>>2);
      offs++;
    }
    offs += 80;
  }
}



void CheckKeys()
{

  if (! (KEYREG & 16)) 
  {
    country++;
    if (country>20) { country = 0; }
    KEYREG |= 16;
  } else if (! (KEYREG & 32))
  {
    country--;
    if (country<0) { country = 20; }
    KEYREG |= 32;
  }  
  
  switch (country)
  {
    case 0:
      map = &bahamas;
      break;
    case 1:
      map = &belgium;
      break;
    case 2:
      map = &chile;
      break;
    case 3:
      map = &denmark;
      break;
    case 4:
      map = &finland;
      break;
    case 5:
      map = &france;
      break;
    case 6:
      map = &germany;
      break;
    case 7:
      map = &greece;
      break;
    case 8:
      map = &iceland;
      break;
    case 9:
      map = &india;
      break;
    case 10:
      map = &ireland;
      break;
    case 11:
      map = &italy;
      break;
    case 12:
      map = &kuwait;
      break;
    case 13:
      map = &monaco;
      break;
    case 14:
      map = &netherlands;
      break;
    case 15:
      map = &norway;
      break;
    case 16:
      map = &spain;
      break;
    case 17:
      map = &sweden;
      break;
    case 18:
      map = &switzerland;
      break;
    case 19:
      map = &trinidad;
      break;
    case 20:
      map = &usa;
      break;
    default:
      break;
  }
  name = (char *)(map+243);
  text_xpos = *(map+242);
}


 
void show_pic()
{
int i,j,si=0,di=9660;  

  for (i=0; i<80; i++)
  {
    for (j=0; j<30; j++)
    {
      *(u32 *)(BACK+di) = *(u32 *)(&miku_raw+si);
      si += 4;
      di += 4;
    }
  di += 120;
  }
}
   



int GBA_main()
{
float f;
u8 xan,yan,zan,xan2;
float xadd,yadd;
float sizeX,sizeY;
int i,j, iMul22,jMul66;


  for (f=0; f<256; f+=1)
  {
    sine[(int)f] = (float)sin(f*3.1415926f/128.0f);
  }

  camX = 20; camY = 14; camZ = 300;


  gbalSetMode(_240x160x1x256_);
  
  gbalSetPalette(BACKGROUND, (u16 *)&miku_pal, 256);
  show_pic();
  gbalSwapBuffers();

   // Delay..
    __asm
   {
    mov r0, #0x4000006
    mov r2,4500
    delay_loop:
      wait_once:
        ldrh r1, [r0]
        cmp	r1, #160
      bne wait_once
      subs r2,r2,#1
    bne delay_loop
   }

  // Now fade out slowly
  for (i=0; i<22; i++)
  {
    gbalVSync();
    blur();
  }

  gbalDisable(GBAL_DMA_CLEAR);
  gbalClearBuffer(0);
  gbalSetFont(&sys8x16);
  gbalTextOut(52,2, 34, "Around the World");
  gbalTextOut(76,18, 34, "Mic, 2001");
  gbalTextOut(4,48, 40, "Controls:");
  gbalTextOut(12,64, 40, "Left/Right - change flag");
  gbalTextOut(44,130, 43, "> Press B button <");
  gbalSwapBuffers();

  // Wait for B-button to be pressed. 
  // (the compiler tried to be smart so I had to use this ugly code)
  __asm
  {
   mov r0,#0x04000130
   wait_for_B:
     ldrh r1,[r0]
     and r1,r1,2
     cmp r1,#0
   bne wait_for_B
  } 
  KEYREG |= 2;

  gbalClearBuffer(0);
  gbalSetFont(&hand8x16);

  for (i=0; i<32; i++)
  {
   gbalSetColor(BACKGROUND, i, (i<<10) );
   gbalSetColor(BACKGROUND, i+32, i );
   gbalSetColor(BACKGROUND, i+64, (i<<10)|(i<<5)|i );
   gbalSetColor(BACKGROUND, i+96, ((i/3)<<10)|((i/3)<<5)|(i/3) );
   gbalSetColor(BACKGROUND, i+128, ((i>>1)+(i>>2)+(i>>3))<<5 );
   gbalSetColor(BACKGROUND, i+160, (i<<10)|(i<<5)|i );
   gbalSetColor(BACKGROUND, i+192, ((i&30)<<4)|i );
   gbalSetColor(BACKGROUND, i+224, (i<<5)|i );
  }
  

  DrawSection = draw_section;


  map = &sweden;
  name = (char *)(map+243);
  text_xpos = *(map+242);
  country = 17;


  ang[0] = 0; ang[1] = 0;

  while (1)
  {
    gbalClearBuffer(0);
    CheckKeys();

    sizeX = 0.0f;
    xan2 = ang[0];  yan = ang[1];

    for (i=0; i<22; i++)
    {
       yadd = 4.2f * sine[yan];
       xan = xan2;
 
       jMul66 = 0;
       sizeY = 0.0f;
       for (j=0; j<12; j++)
       {
          zan = xan+(xan>>1)+yan;
          xadd = 6.5f * sine[xan];

          points3d[jMul66 + (i<<1)+i] = 46.0f + sizeX + xadd;
          points3d[jMul66 + (i<<1)+i + 1] = 40.0f + sizeY + yadd;
          points3d[jMul66 + (i<<1)+i + 2] = 9.5f * sine[zan];

          xan += 12; 
          sizeY += 6.55f;
          jMul66 += 66;
       }
       yan += 13;
       sizeX += 7.0f;
    }

    Project(&points3d[0], &flag[0].x, 264);


    iMul22 = 0;
    for (i=0; i<11; i++)
    {
      for (j=0; j<21; j++)
      {
         map_ij = map[iMul22+j];
         if (map_ij)
         {
            basecol = base_col[map_ij-1];
            gbalTriangle(&flag[iMul22+j], &flag[iMul22+23+j], &flag[iMul22+22+j]);
            gbalTriangle(&flag[iMul22+j], &flag[iMul22+23+j], &flag[iMul22+1+j]);
         }
      }
      iMul22 += 22;
    }

    gbalTextOut(text_xpos,129, 250, name);

    gbalSwapBuffers();


    ang[0] += 1;
    ang[1] += 2;

  }


  return 0;
}

       





