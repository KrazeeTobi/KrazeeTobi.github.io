// GBALib
// v. 00.12.16 wip
// /Mic, 2000
//

#include <string.h>



// [graphics modes]
#define _240x160x1x256_		0x04
#define _240x160x0x32k_		0x03
#define _160x128x0x32k_		0x05



// [palettes]
#define BACKGROUND	0x05000000
#define OBJECT		0x05000200

#define VRAM 		0x06000000

#define FOCAL 256.0f

// [shade models]
#define GBAL_FLAT 0
#define GBAL_SMOOTH 1

// [polygon modes]
#define GBAL_POINT  0
#define GBAL_LINE   1
#define GBAL_FILL   2


#define GBAL_TEXTURE_2D     1
#define GBAL_DMA_CLEAR      2



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;



typedef struct POINT
{
  long x, y;
  long c;
  long u,v;
}POINT;


struct RContext
{
 u8 *buffer;
 u32 width;
 u32 height;
 u8 bitspp;
}RContext;

struct gbal_texture
{
 void *texture;
 u32 width;
 u32 height;
}gbal_texture;

struct gbal_font
{
 u8 *font;
 u8 w;
 u8 width;
 u8 height;
 u32 char_size;
 u16 first;
 u16 last;
 u16 numchars;
 u32 header_size;
}gbal_font;



// data for Draw?Section?()
struct dsdata
{
 long x1,x2;
 long y1,y2;
 long c1,c2;
 long red1,red2, green1,green2, blue1,blue2;
 long u1,u2, v1,v2;
 long dxdy1,dxdy2;
 long dcdy1,dcdy2;
 long drdy1,drdy2,dgdy1,dgdy2,dbdy1,dbdy2;
 long dudy1,dudy2,dvdy1,dvdy2;
}dsdata;


u32 _clear_col = 0;
u32 *_clear_col_ptr = &_clear_col;


u8 *FRONT=(u8 *)VRAM, *BACK=(u8 *)VRAM;
u8 *VIDEO = (u8 *)VRAM;
u8 _polygon_mode = GBAL_FILL;
u8 _current_mode = 0;
u16 _dma_word_count = 1;


typedef void (*tri_func)(POINT *pp1, POINT *pp2, POINT *pp3);

tri_func GouraudTriangle;
tri_func TextureTriangle;
tri_func gbalTriangle, last_gbalTriangle;

void (*DrawSection)(void);
void (*gbalClearBuffer)(u16 col);
void (*gbalBlit)(long x,long y,long xdim,long ydim,void *src,u16 rastop);


#define putpixel8(x,y,c)    if ((y>=0)&&(y<RContext.height)) {\
                            if ((x>=0)&&(y<RContext.width)) {\
                            *(BACK+(y*RContext.width)+x) = c; }}

#define putpixel15(x,y,c)    if ((y>=0)&&(y<RContext.height)) {\
                            if ((x>=0)&&(y<RContext.width)) {\
                            *(u16 *)(BACK+((y+y)*RContext.width)+x+x) = c; }}


#define gbalMakeColor(r,g,b) (u16)(((r&248)>>3)|((g&248)<<2)|((b&248)<<7));




void gbalSwapBuffers()
{
  if (_current_mode!=3)
  {
    __asm
    {
       mov      r2, #0x4000000 
       ldrh     r0, [r2]
       and 	    r1, r0, #0xFFFFFFEF
       tst 	    r0, #0x10
       orreq    r1, r1, #0x10
       strh     r1, [r2]
       mov 	    r0, #0x6000000
       mov      r2,r0
       ldrh     r1, [0x4000000]
       tst 	    r1, #0x10
       addeq    r0, r0, #0x0A000
       addne    r2,r2,#0x0A000
       mov      BACK,r0
       mov      FRONT,r2	
    }
    RContext.buffer = BACK;
  }
}



// This doesn't work correctly with the current version of the gba emu.
void clearBufferDMA(u16 col)
{
u8 *RCBuf = RContext.buffer;

  _clear_col = col;
  if (_current_mode==4)
  {
    _clear_col = (_clear_col<<8)|_clear_col;
  }
  _clear_col = (_clear_col<<16)|_clear_col;
  __asm
  {

    mov     r1,_clear_col_ptr
    mov     r2,RCBuf
    mov	r3, _dma_word_count	
    mov	r4, #0x8500 
    mov	r0, #0x40000D4
    str	r1, [r0], #0x4
    str	r2, [r0], #0x4
    strh	r3, [r0], #0x2
    strh	r4, [r0]
  }
}


// This works just fine, but it's slow.
void clearBufferCPU(u16 col)
{
u8 *RCBuf = RContext.buffer;

  _clear_col = col;
  if (_current_mode==4)
  {
    _clear_col = (_clear_col<<8)|_clear_col;
  }
  _clear_col = (_clear_col<<16)|_clear_col;
  __asm
  {

    mov     r1, _clear_col
    mov     r2, RCBuf
    mov	r3, _dma_word_count	
    clear_loop:
      str	r1, [r2], #4
      subs  r3, r3, #1
    bne clear_loop
  }
}




void gbalSetFont(u8 *the_font)
{
   gbal_font.font = the_font;
   gbal_font.first = *(u8 *)(the_font);
   gbal_font.last = *(u8 *)(the_font+1);
   gbal_font.numchars = (gbal_font.last-gbal_font.first)+1;
   gbal_font.header_size = (gbal_font.numchars+6);
   gbal_font.w = *(u8 *)(the_font+2);
   gbal_font.width = gbal_font.w<<3;
   gbal_font.height = *(u8 *)(the_font+3);
   gbal_font.char_size = (gbal_font.w*gbal_font.height);
}



void gbalCharOut(int x, int y, u8 col, u8 tecken)
{
u8 *src,*dest;
int xdim,ydim;

  if ((tecken<gbal_font.first)||(tecken>gbal_font.last)) { return; }
  tecken -= gbal_font.first;

  src = (gbal_font.font+(gbal_font.char_size*tecken))+gbal_font.header_size;
  xdim = *(u8 *)(gbal_font.font + tecken + 6);
  ydim = gbal_font.height;

  if ((x>=RContext.width)||((x+xdim-1)<0)) { return; }
  if ((y>=RContext.height)||((y+ydim-1)<0)) { return; }

  if (y<0) { src -= (y*xdim); ydim += y; y=0; }
  if ((y+ydim)>RContext.height) { ydim -= (int)((y+ydim)-RContext.height); }

  if (x<0) { src -= x; xdim += x; x=0; }
  if ((x+xdim)>RContext.width) { xdim -= (int)((x+xdim)-RContext.width); }

  dest = (u8 *)(BACK+(y*240)+x);
 
  __asm 
  {
    mov r0,src
    mov r1,dest
    mov r2,ydim
    mov r3,gbal_font.width
    mov r6,xdim
    sub r3,r3,r6
    mov r3,r3,lsr #3
    mov r5,r6,lsr #3
    ands r6,r6,#7
    addne r5,r5,#1
    mov xdim,r5
    mov r7,r5,lsl #3
    mov r4,RContext.width
    sub r4,r4,r7

    mov r7,col
    coYloop:
      stmfd sp!,{r3-r4}
      mov r5,xdim
      coXloop:
        ldrb r6,[r0]
        mov r3,#128
        coBitsLoop:
          ands r4,r6,r3
          beq invisible
            strb r7,[r1]
          invisible:
          add r1,r1,#1
          movs r3,r3,lsr #1
        bne coBitsLoop
        add r0,r0,#1
        subs r5,r5,#1
      bne coXloop
      ldmfd sp!,{r3-r4}
      add r1,r1,r4
      add r0,r0,r3  
      subs r2,r2,#1
    bne coYloop
  }
}


void gbalTextOut(int x, int y, u8 col, char *straeng)
{
u8 *src,*dest;
int i,xpos,xdim,ydim;
int yclip1=0,yclip2=0, YxWidth;
u8 tecken;


  ydim = gbal_font.height;
  if ((y>=RContext.height)||((y+ydim-1)<0)) { return; }
  if (y<0) { yclip1 = -y; ydim += y; y=0; }
  if ((y+ydim)>RContext.height) { yclip2 = (int)((y+ydim)-RContext.height); ydim-=yclip2; }
  YxWidth = y*(int)RContext.width;

  for (i=0; i<strlen((char *)straeng); i++)
  {
    tecken = straeng[i];
    if ((tecken<gbal_font.first)||(tecken>gbal_font.last)) { continue; }
    tecken -= gbal_font.first;

    xpos = x;
    src = (gbal_font.font+(gbal_font.char_size*tecken))+gbal_font.header_size;
    xdim = *(u8 *)(gbal_font.font + tecken + 6);
    src += (yclip1*xdim);

    x = xpos+xdim+1;
    if ((xpos>=RContext.width)||((xpos+xdim-1)<0)) { continue; }

    if (xpos<0) { src -= xpos; xdim += xpos; xpos=0; }
    if ((xpos+xdim)>RContext.width) { xdim -= (int)((xpos+xdim)-RContext.width); }

    dest = (u8 *)(BACK+YxWidth+xpos);
 
    __asm 
    {
      mov r0,src
      mov r1,dest
      mov r2,ydim
      mov r3,gbal_font.width
      mov r6,xdim
      sub r3,r3,r6
      mov r3,r3,lsr #3
      mov r5,r6,lsr #3
      ands r6,r6,#7
      addne r5,r5,#1
      mov xdim,r5
      mov r7,r5,lsl #3
      mov r4,RContext.width
      sub r4,r4,r7

      mov r7,col
      toYloop:
        // push r3; push r4
        stmfd sp!,{r3-r4}
        mov r5,xdim
        toXloop:
          ldrb r6,[r0]
          mov r3,#128
          toBitsLoop:
            ands r4,r6,r3
            beq invisible
              strb r7,[r1]
            invisible:
            add r1,r1,#1
            movs r3,r3,lsr #1
          bne toBitsLoop
          add r0,r0,#1
          subs r5,r5,#1
        bne toXloop
        // pop r4; pop r3
        ldmfd sp!,{r3-r4}
        add r1,r1,r4
        add r0,r0,r3  
        subs r2,r2,#1
      bne toYloop
    }
  }
}



void line8(long x1, long y1, long x2, long y2, u8 col)
{
int dx,dy,numpixels;
int d,dinc1,dinc2;
int xinc1,xinc2, yinc1,yinc2;
int x,y;
//u8 *dest = BACK;

  dx = (int)(x2-x1);
  dy = (int)(y2-y1);
  if (dx<0) { dx = -dx; }
  if (dy<0) { dy = -dy; }
  if (dx>dy)
  {
    numpixels = dx+1;
    d = (dy<<1)-dx;
    dinc1 = (dy<<1);
    dinc2 = (dy-dx)<<1;
    xinc1 = 1;
    xinc2 = 1;
    yinc1 = 0;
    yinc2 = 1;
  }else
  {
    numpixels = dy+1;
    d = (dx<<1)-dx;
    dinc1 = (dx<<1);
    dinc2 = (dx-dy)<<1;
    xinc1 = 0;
    xinc2 = 1;
    yinc1 = 1;
    yinc2 = 1; 
  }
  if (x1>x2) { xinc1 = -xinc1; xinc2 = -xinc2; }
  if (y1>y2) { yinc1 = -yinc1; yinc2 = -yinc2; }
  x = (int)x1;
  y = (int)y1;
  for (; numpixels; numpixels--)
  {
    putpixel8(x,y,col);
    if (d<0)
    {
      d += dinc1;
      x += xinc1;
      y += yinc1;
    }else  
    {
      d += dinc2;
      x += xinc2;
      y += yinc2;
    }
  }
}


void gline8(long x1, long y1, long x2, long y2, u8 col1, u8 col2)
{
int dx,dy,numpixels;
int d,dinc1,dinc2;
int xinc1,xinc2, yinc1,yinc2;
int x,y;
int col,dc,cinc;
//u8 *dest = BACK;

  dc = ((int)col2-(int)col1)+1;
  col = (int)col1<<16;

  dx = (int)(x2-x1);
  dy = (int)(y2-y1);
  if (dx<0) { dx = -dx; }
  if (dy<0) { dy = -dy; }
  if (dx>dy)
  {
    numpixels = dx+1;
    d = (dy<<1)-dx;
    dinc1 = (dy<<1);
    dinc2 = (dy-dx)<<1;
    xinc1 = 1;
    xinc2 = 1;
    yinc1 = 0;
    yinc2 = 1;
  }else
  {
    numpixels = dy+1;
    d = (dx<<1)-dx;
    dinc1 = (dx<<1);
    dinc2 = (dx-dy)<<1;
    xinc1 = 0;
    xinc2 = 1;
    yinc1 = 1;
    yinc2 = 1; 
  }
  if (x1>x2) { xinc1 = -xinc1; xinc2 = -xinc2; }
  if (y1>y2) { yinc1 = -yinc1; yinc2 = -yinc2; }
  x = (int)x1;
  y = (int)y1;
  cinc = (dc<<16)/numpixels;
  //cfrac = 0;
  //cinc2 = 1;
  //if (col>col2) { cinc2 = -cinc2; }

  for (; numpixels; numpixels--)
  {
    putpixel8(x, y, col>>16);
    if (d<0)
    {
      d += dinc1;
      x += xinc1;
      y += yinc1;
    }else  
    {
      d += dinc2;
      x += xinc2;
      y += yinc2;
    }
    col += cinc;
  }
}




void srccopy8(long x, long y, long xdim, long ydim, u8 *src)
{
u8 *RCbuf = RContext.buffer;
long RCw = RContext.width;

/*
  if ((x>=RContext.width)||((x+xdim-1)<0)) { return; }
  if ((y>=RContext.height)||((y+ydim-1)<0)) { return; }

  if (y<0) { src -= (y*xdim); ydim += y; y=0; }
  if ((y+ydim)>RContext.height) { ydim -= ((y+ydim)-RContext.height); }

  if (x<0) { src -= x; xdim += x; x=0; }
  if ((x+xdim)>RContext.width) { xdim -= ((x+xdim)-RContext.width); }
*/

  __asm
  {
   mov r0,RCw
   mov r1,y
   mul r1,r0,r1
   mov r0,x
   add r1,r1,r0
   mov r0,RCbuf  
   add r0,r0,r1

   // r3 = RContext.width - x
   mov r2,src
   mov r3,RCw
   mov r4,xdim
   sub r3,r3,r4

   mov r4,ydim
   Yloop8:
    mov r5,xdim
    mov r6,r5,lsr #2
    and r5,r5,#3
    Xloop8:
     ldr r1,[r2],#4
     str r1,[r0],#4
     // The 's'-suffix is neccecary to update the flags, or you'd get an
     // eternal loop..
     subs r6,r6,#1
    bne Xloop8
    cmp r5,#0
    beq noRest
    drawRest:
      ldrb r1,[r2],#1
      strb r1,[r0],#1
      subs r5,r5,#1
    bne drawRest
    noRest:
    add r0,r0,r3
    subs r4,r4,#1
   bne Yloop8
  }
}


void notnullcopy8(long x, long y, long xdim, long ydim, u8 *src)
{
u8 *RCbuf = RContext.buffer;
long RCw = RContext.width;
/*
  if ((x>=RContext.width)||((x+xdim-1)<0)) { return; }
  if ((y>=RContext.height)||((y+ydim-1)<0)) { return; }

  if (y<0) { src -= (y*xdim); ydim += y; y=0; }
  if ((y+ydim)>RContext.height) { ydim -= ((y+ydim)-RContext.height); }

  if (x<0) { src -= x; xdim += x; x=0; }
  if ((x+xdim)>RContext.width) { xdim -= ((x+xdim)-RContext.width); }
*/
  __asm
  {
   mov r0,RCw
   mov r1,y
   mul r1,r0,r1
   mov r0,x
   add r1,r1,r0
   mov r0,RCbuf 
   add r0,r0,r1

   // r3 = RContext.width - x
   mov r2,src
   mov r3,RCw
   mov r4,xdim
   sub r3,r3,r4

   mov r4,ydim
   Yloop8:
     mov r5,xdim
     Xloop8:
       ldrb r1,[r2],#1
       orrs r1,r1,r1
       beq invisible
         strb r1,[r0]
       invisible: 
       add r0,r0,#1
       subs r5,r5,#1
     bne Xloop8
     add r0,r0,r3
     subs r4,r4,#1
   bne Yloop8
  }
}


void srccopy15(long x, long y, long xdim, long ydim, u16 *src)
{
long xdim2 = xdim;

  __asm
  {
   mov r0,RContext.width,lsl #1
   mov r1,y
   mul r1,r0,r1
   mov r0,x
   add r1,r1,r0
   add r1,r1,r0
   mov r0,BACK
   add r0,r0,r1

   // r3 = (RC.width*2) - (xdim*2)
   mov r2,src
   mov r3,RContext.width,lsl #1
   mov r4,xdim2
   sub r3,r3,r4
   sub r3,r3,r4

   mov r4,ydim
   Yloop15:
     mov r5,xdim
     mov r6,r5,lsr #1
     Xloop15:
       ldr r1,[r2],#4
       str r1,[r0],#4

       // The 's'-suffix is neccecary to update the flags, or you'd get an
       // eternal loop..
       subs r6,r6,#1
     bne Xloop15
     tst r5,#1
     beq noOdd15
       ldrh r1,[r2],#2
       strh r1,[r0],#2
     noOdd15:
     add r0,r0,r3
     subs r4,r4,#1
   bne Yloop15 
  }
}


void notnullcopy15(long x, long y, long xdim, long ydim, u16 *src)
{

  __asm
  {
   mov r0,RContext.width,lsl #1
   mov r1,y
   mul r1,r0,r1
   mov r0,x
   add r1,r1,r0
   add r1,r1,r0
   mov r0,BACK 
   add r0,r0,r1

   // r3 = RContext.width - x
   mov r2,src
   mov r3,RContext.width,lsl #1
   mov r4,xdim
   sub r3,r3,r4
   sub r3,r3,r4

   mov r4,ydim
   Yloop15:
     mov r5,xdim
     Xloop15:
       ldrh r1,[r2],#2
       orrs r1,r1,r1
       beq invisible
         strh r1,[r0]
       invisible: 
       add r0,r0,#2
       subs r5,r5,#1
     bne Xloop15
     add r0,r0,r3
     subs r4,r4,#1
   bne Yloop15
  }
}



// Internal function, don't call this one.
void DrawSection8()
{
u32 y;
long x1,x2;
u8 *dest,*last_dest, col;
long clipped;
  if (dsdata.y1 >= RContext.height) return;
  if (dsdata.y2 < 0) return;

  col = (u8)(dsdata.c1);
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
        mov r2,col
        Store8:
          strb r2,[r0],#1
          subs r1,r1,#1
        bne Store8
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


// Internal function, don't call this one.
void DrawSection15()
{
u32 y;
long x1,x2;
u16 *dest,*last_dest, col;
long clipped;
  if (dsdata.y1 >= RContext.height) return;
  if (dsdata.y2 < 0) return;

  col = (u16)(dsdata.c1);
  if (dsdata.y1<0)  
  {
    clipped = 0-dsdata.y1;
    dsdata.x1 += (dsdata.dxdy1*clipped);
    dsdata.x2 += (dsdata.dxdy2*clipped);
    dsdata.y1 = 0;
  }
  if (dsdata.y2 >= RContext.height) dsdata.y2 = (RContext.height-1);
  dest = ((u16 *)(RContext.buffer) + (dsdata.y1*RContext.width));

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
        mov r2,col
        Store16:
          strh r2,[r0]
          add r0,r0,#2
          subs r1,r1,#1
        bne Store16
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




// Draw a single-coloured triangle.
void Triangle(POINT *pp1, POINT *pp2, POINT *pp3)
{
POINT *pp4;
long dx1,dx2,dx3;
long dy1,dy2,dy3;
long dxdy1,dxdy2,dxdy3;

  if (_polygon_mode==GBAL_POINT)
  {
    putpixel8(pp1->x, pp1->y, (u8)pp1->c);
    putpixel8(pp2->x, pp2->y, (u8)pp1->c);
    putpixel8(pp3->x, pp3->y, (u8)pp1->c);
  }else if (_polygon_mode==GBAL_LINE)
  {
    line8(pp1->x,pp1->y, pp2->x,pp2->y, (u8)pp1->c);
    line8(pp2->x,pp2->y, pp3->x,pp3->y, (u8)pp1->c);
    line8(pp1->x,pp1->y, pp3->x,pp3->y, (u8)pp1->c);
  }else
  {

    if (pp2->y < pp1->y) { pp4=pp1; pp1=pp2; pp2=pp4; }
    if (pp3->y < pp1->y) { pp4=pp1; pp1=pp3; pp3=pp4; }
    if (pp3->y < pp2->y) { pp4=pp2; pp2=pp3; pp3=pp4; }

    dx1 = (pp2->x - pp1->x);
    dx2 = (pp3->x - pp2->x);
    dx3 = (pp3->x - pp1->x);

    dy1 = (pp2->y - pp1->y);
    dy2 = (pp3->y - pp2->y);
    dy3 = (pp3->y - pp1->y);
    if (dy1==0) dy1++;
    if (dy2==0) dy2++;
    if (dy3==0) dy3++;

    dxdy1 = ((dx1<<9)/dy1);
    dxdy2 = ((dx2<<9)/dy2);
    dxdy3 = ((dx3<<9)/dy3);

    dsdata.c1 = pp1->c;

    dsdata.x1 = (pp1->x<<9);
    dsdata.x2 = dsdata.x1;
    dsdata.y1 = pp1->y;
    dsdata.y2 = pp2->y;
    dsdata.dxdy1 = dxdy1;
    dsdata.dxdy2 = dxdy3;

    DrawSection();
    dsdata.y1 = pp2->y;
    dsdata.y2 = pp3->y;
    dsdata.x1 = (pp2->x<<9);
    dsdata.dxdy1 = dxdy2;
    dsdata.dxdy2 = dxdy3;
    DrawSection();
  }
}


// Internal function, don't call this one.
void DrawGSection8()
{
u32 y;
long x1,x2, tmp, dcdx;
long c1,c2;
u8 *dest,*last_dest;
long clipped;
  if (dsdata.y1>=RContext.height) return;
  if (dsdata.y2<0) return;

  if (dsdata.y1<0)  
  {
    clipped = 0-dsdata.y1;
    dsdata.x1 += (dsdata.dxdy1*clipped);
    dsdata.x2 += (dsdata.dxdy2*clipped);
    dsdata.c1 += (dsdata.dcdy1*clipped);
    dsdata.c2 += (dsdata.dcdy2*clipped);
    dsdata.y1 = 0;
  }
  if (dsdata.y2>=RContext.height) dsdata.y2 = (RContext.height-1);
  dest = (RContext.buffer + (dsdata.y1*RContext.width));

  for (y=dsdata.y1; y<=dsdata.y2; y++)  
  {
    if (dsdata.x1 <= dsdata.x2)
    {
      x1 = dsdata.x1;
      x2 = dsdata.x2;
      c1 = dsdata.c1;
      c2 = dsdata.c2;
    }else
    {
      x1 = dsdata.x2;
      x2 = dsdata.x1;
      c1 = dsdata.c2;
      c2 = dsdata.c1;
    }
    x1 >>= 9;
    x2 >>= 9;
    if ((x1<RContext.width)&&(x2>=0))
    {
      last_dest = dest;
      tmp = (x2-x1);
      if (tmp==0) tmp++;
      dcdx = ((c2-c1)/tmp);
      dest += x1;
      __asm
      {
        mov r0,dest
        mov r1,x2
        mov r2,x1
        sub r1,r1,r2
        add r1,r1,#1
        mov r2,c1
        mov r3,dcdx
        Inner:
          mov r4,r2,lsr #16     // r4 = SHR(r2,16)
          strb r4,[r0],#1
          subs r1,r1,#1
          add r2,r2,r3
        bne Inner
      }
      dest = last_dest;
    } 
    if (y<dsdata.y2)
    {
      dest += RContext.width;
      dsdata.x1 += dsdata.dxdy1;
      dsdata.x2 += dsdata.dxdy2;
      dsdata.c1 += dsdata.dcdy1;
      dsdata.c2 += dsdata.dcdy2;
    }
  }
}


// Internal function, don't call this one.
void DrawGSection15()
{
u32 y;
long x1,x2, tmp, drdx,dgdx,dbdx;
long red1,red2, green1,green2, blue1,blue2;
u16 *dest,*last_dest;
long clipped;
  if (dsdata.y1>=RContext.height) return;
  if (dsdata.y2<0) return;

  if (dsdata.y1<0)  
  {
    clipped = 0-dsdata.y1;
    dsdata.x1 += (dsdata.dxdy1*clipped);
    dsdata.x2 += (dsdata.dxdy2*clipped);
    dsdata.red1 += (dsdata.drdy1*clipped);
    dsdata.red2 += (dsdata.drdy2*clipped);
    dsdata.green1 += (dsdata.dgdy1*clipped);
    dsdata.green2 += (dsdata.dgdy2*clipped);
    dsdata.blue1 += (dsdata.dbdy1*clipped);
    dsdata.blue2 += (dsdata.dbdy2*clipped);
    dsdata.y1 = 0;
  }
  if (dsdata.y2>=RContext.height) dsdata.y2 = (RContext.height-1);
  dest = ((u16 *)(RContext.buffer) + (dsdata.y1*RContext.width));

  for (y=dsdata.y1; y<=dsdata.y2; y++)  
  {
    if (dsdata.x1 <= dsdata.x2)
    {
      x1 = dsdata.x1;
      x2 = dsdata.x2;
      red1 = dsdata.red1;
      red2 = dsdata.red2;
      green1 = dsdata.green1;
      green2 = dsdata.green2;
      blue1 = dsdata.blue1;
      blue2 = dsdata.blue2;
    }else
    {
      x1 = dsdata.x2;
      x2 = dsdata.x1;
      red1 = dsdata.red2;
      red2 = dsdata.red1;
      green1 = dsdata.green2;
      green2 = dsdata.green1;
      blue1 = dsdata.blue2;
      blue2 = dsdata.blue1;
    }
    x1 >>= 9;
    x2 >>= 9;
    if ((x1<RContext.width)&&(x2>=0))
    {
      last_dest = dest;
      tmp = (x2-x1);
      if (tmp==0) tmp++;
      drdx = ((red2-red1)/tmp);
      dgdx = ((green2-green1)/tmp);
      dbdx = ((blue2-blue1)/tmp);
      dest += x1;
      __asm
      {
        mov r0,dest
        mov r1,x2
        mov r2,x1
        sub r1,r1,r2
        add r1,r1,#1
        mov r2,red1
        mov r3,drdx
        mov r4,green1
        mov r5,blue1
 
        Inner15:
          mov r6,r2,lsr #16     // r6 = SHR(r2,16)
          mov r7,r4,lsr #11
          and r7,r7,#992
          add r6,r6,r7
          mov r7,r5,lsr #6
          and r7,r7,#31744
          add r6,r6,r7
          strh r6,[r0]
          add r0,r0,#2 
          add r2,r2,r3
          mov r6,dgdx
          mov r7,dbdx
          add r4,r4,r6
          add r5,r5,r7
          subs r1,r1,#1
        bne Inner15
      }
      dest = last_dest;
    } 
    if (y<dsdata.y2)
    {
      dest += RContext.width;
      dsdata.x1 += dsdata.dxdy1;
      dsdata.x2 += dsdata.dxdy2;
      dsdata.red1 += dsdata.drdy1;
      dsdata.red2 += dsdata.drdy2;
      dsdata.green1 += dsdata.dgdy1;
      dsdata.green2 += dsdata.dgdy2;
      dsdata.blue1 += dsdata.dbdy1;
      dsdata.blue2 += dsdata.dbdy2;
    }
  }
}


// Draw a gouraudshaded triangle. 
void GouraudTriangle8(POINT *pp1, POINT *pp2, POINT *pp3)
{
POINT *pp4;
long dx1,dx2,dx3;
long dy1,dy2,dy3;
long dc1,dc2,dc3;
long dxdy1,dxdy2,dxdy3;
long dcdy1,dcdy2,dcdy3;

  if (_polygon_mode==GBAL_POINT)
  {
    putpixel8(pp1->x, pp1->y, (u8)pp1->c);
    putpixel8(pp2->x, pp2->y, (u8)pp2->c);
    putpixel8(pp3->x, pp3->y, (u8)pp3->c);
  }else if (_polygon_mode==GBAL_LINE)
  {
    gline8(pp1->x,pp1->y, pp2->x,pp2->y, (u8)pp1->c,(u8)pp2->c);
    gline8(pp2->x,pp2->y, pp3->x,pp3->y, (u8)pp2->c,(u8)pp3->c);
    gline8(pp1->x,pp1->y, pp3->x,pp3->y, (u8)pp1->c,(u8)pp3->c);
  }else
  {
    if (pp2->y < pp1->y) { pp4=pp1; pp1=pp2; pp2=pp4; }
    if (pp3->y < pp1->y) { pp4=pp1; pp1=pp3; pp3=pp4; }
    if (pp3->y < pp2->y) { pp4=pp2; pp2=pp3; pp3=pp4; }

    dx1 = (pp2->x - pp1->x);
    dx2 = (pp3->x - pp2->x);
    dx3 = (pp3->x - pp1->x);

    dy1 = (pp2->y - pp1->y);
    dy2 = (pp3->y - pp2->y);
    dy3 = (pp3->y - pp1->y);
    if (dy1==0) dy1++;
    if (dy2==0) dy2++;
    if (dy3==0) dy3++;

    dc1 = (pp2->c - pp1->c);
    dc2 = (pp3->c - pp2->c);
    dc3 = (pp3->c - pp1->c);

    dxdy1 = ((dx1<<9)/dy1);
    dxdy2 = ((dx2<<9)/dy2);
    dxdy3 = ((dx3<<9)/dy3);

    dcdy1 = ((dc1<<16)/dy1);
    dcdy2 = ((dc2<<16)/dy2);
    dcdy3 = ((dc3<<16)/dy3);

    dsdata.x1 = (pp1->x<<9);
    dsdata.x2 = dsdata.x1;
    dsdata.c1 = (pp1->c<<16);
    dsdata.c2 = dsdata.c1;
    dsdata.y1 = pp1->y;
    dsdata.y2 = pp2->y;
    dsdata.dxdy1 = dxdy1;
    dsdata.dxdy2 = dxdy3;
    dsdata.dcdy1 = dcdy1;
    dsdata.dcdy2 = dcdy3;

    DrawGSection8();
    dsdata.y1 = pp2->y;
    dsdata.y2 = pp3->y;
    dsdata.x1 = (pp2->x<<9);
    dsdata.c1 = (pp2->c<<16);
    dsdata.dxdy1 = dxdy2;
    dsdata.dxdy2 = dxdy3;
    dsdata.dcdy1 = dcdy2;
    dsdata.dcdy2 = dcdy3;
    DrawGSection8();
  } 
}



void GouraudTriangle15(POINT *pp1, POINT *pp2, POINT *pp3)
{
POINT *pp4;
long dx1,dx2,dx3;
long dy1,dy2,dy3;
long dr1,dr2,dr3;
long dg1,dg2,dg3;
long db1,db2,db3;
long dxdy1,dxdy2,dxdy3;
long drdy1,drdy2,drdy3;
long dgdy1,dgdy2,dgdy3;
long dbdy1,dbdy2,dbdy3;
long red1,red2,red3;
long green1,green2,green3;
long blue1,blue2,blue3;

  if (pp2->y < pp1->y) { pp4=pp1; pp1=pp2; pp2=pp4; }
  if (pp3->y < pp1->y) { pp4=pp1; pp1=pp3; pp3=pp4; }
  if (pp3->y < pp2->y) { pp4=pp2; pp2=pp3; pp3=pp4; }

  dx1 = (pp2->x - pp1->x);
  dx2 = (pp3->x - pp2->x);
  dx3 = (pp3->x - pp1->x);

  dy1 = (pp2->y - pp1->y);
  dy2 = (pp3->y - pp2->y);
  dy3 = (pp3->y - pp1->y);
  if (dy1==0) dy1++;
  if (dy2==0) dy2++;
  if (dy3==0) dy3++;

  red1 = (pp1->c&31);
  red2 = (pp2->c&31);
  red3 = (pp3->c&31);
  green1 = ((pp1->c>>5)&31);
  green2 = ((pp2->c>>5)&31);
  green3 = ((pp3->c>>5)&31);
  blue1 = ((pp1->c>>10)&31);
  blue2 = ((pp2->c>>10)&31);
  blue3 = ((pp3->c>>10)&31);

  dr1 = (red2-red1);
  dr2 = (red3-red2);
  dr3 = (red3-red1);
  dg1 = (green2-green1);
  dg2 = (green3-green2);
  dg3 = (green3-green1);
  db1 = (blue2-blue1);
  db2 = (blue3-blue2);
  db3 = (blue3-blue1);

  dxdy1 = ((dx1<<9)/dy1);
  dxdy2 = ((dx2<<9)/dy2);
  dxdy3 = ((dx3<<9)/dy3);

  drdy1 = ((dr1<<16)/dy1);
  drdy2 = ((dr2<<16)/dy2);
  drdy3 = ((dr3<<16)/dy3);
  dgdy1 = ((dg1<<16)/dy1);
  dgdy2 = ((dg2<<16)/dy2);
  dgdy3 = ((dg3<<16)/dy3);
  dbdy1 = ((db1<<16)/dy1);
  dbdy2 = ((db2<<16)/dy2);
  dbdy3 = ((db3<<16)/dy3);

  dsdata.x1 = (pp1->x<<9);
  dsdata.x2 = dsdata.x1;
  dsdata.red1 = (red1<<16);
  dsdata.red2 = dsdata.red1;
  dsdata.green1 = (green1<<16);
  dsdata.green2 = dsdata.green1;
  dsdata.blue1 = (blue1<<16);
  dsdata.blue2 = dsdata.blue1;
  dsdata.y1 = pp1->y;
  dsdata.y2 = pp2->y;
  dsdata.dxdy1 = dxdy1;
  dsdata.dxdy2 = dxdy3;
  dsdata.drdy1 = drdy1;
  dsdata.drdy2 = drdy3;
  dsdata.dgdy1 = dgdy1;
  dsdata.dgdy2 = dgdy3;
  dsdata.dbdy1 = dbdy1;
  dsdata.dbdy2 = dbdy3;

  DrawGSection15();
  dsdata.y1 = pp2->y;
  dsdata.y2 = pp3->y;
  dsdata.x1 = (pp2->x<<9);
  dsdata.red1 = (red2<<16);
  dsdata.green1 = (green2<<16);
  dsdata.blue1 = (blue2<<16);
  dsdata.dxdy1 = dxdy2;
  dsdata.dxdy2 = dxdy3;
  dsdata.drdy1 = drdy2;
  dsdata.drdy2 = drdy3;
  dsdata.dgdy1 = dgdy2;
  dsdata.dgdy2 = dgdy3;
  dsdata.dbdy1 = dbdy2;
  dsdata.dbdy2 = dbdy3;
  DrawGSection15();
}



// Internal function, don't call this one.
void DrawTSection8()
{
u32 y;
long x1,x2, tmp, dudx,dvdx;
long u1,u2, v1,v2;
u16 *dest,*last_dest;
long clipped;
  if (dsdata.y1>=RContext.height) return;
  if (dsdata.y2<0) return;

  if (dsdata.y1<0)  
  {
    clipped = 0-dsdata.y1;
    dsdata.x1 += (dsdata.dxdy1*clipped);
    dsdata.x2 += (dsdata.dxdy2*clipped);
    dsdata.u1 += (dsdata.dudy1*clipped);
    dsdata.u2 += (dsdata.dudy2*clipped);
    dsdata.v1 += (dsdata.dvdy1*clipped);
    dsdata.v2 += (dsdata.dvdy2*clipped);
    dsdata.y1 = 0;
  }
  if (dsdata.y2>=RContext.height) dsdata.y2 = (RContext.height-1);
  dest = ((u16 *)(RContext.buffer) + (dsdata.y1*RContext.width));

  for (y=dsdata.y1; y<=dsdata.y2; y++)  
  {
    if (dsdata.x1 <= dsdata.x2)
    {
      x1 = dsdata.x1;
      x2 = dsdata.x2;
      u1 = dsdata.u1;
      u2 = dsdata.u2;
      v1 = dsdata.v1;
      v2 = dsdata.v2;
    }else
    {
      x1 = dsdata.x2;
      x2 = dsdata.x1;
      u1 = dsdata.u2;
      u2 = dsdata.u1;
      v1 = dsdata.v2;
      v2 = dsdata.v1;
    }
    x1 >>= 9;
    x2 >>= 9;
    if ((x1<RContext.width)&&(x2>=0))
    {
      last_dest = dest;
      tmp = (x2-x1);
      if (tmp==0) tmp++;
      dudx = ((u2-u1)/tmp);
      dvdx = ((v2-v1)/tmp);
      dest += x1;
      __asm
      {
        mov r0,dest
        // to be written
      }
      dest = last_dest;
    } 
    if (y<dsdata.y2)
    {
      dest += RContext.width;
      dsdata.x1 += dsdata.dxdy1;
      dsdata.x2 += dsdata.dxdy2;
      dsdata.u1 += dsdata.dudy1;
      dsdata.u2 += dsdata.dudy2;
      dsdata.v1 += dsdata.dvdy1;
      dsdata.v2 += dsdata.dvdy2;
    }
  }
}

void TextureTriangle8(POINT *pp1, POINT *pp2, POINT *pp3)
{
}







// Set the rendering context.
void gbalRContext(void *buffer, u32 width, u32 height, u8 bitspp)
{
  RContext.buffer = (u8 *)(buffer);
  RContext.width = width;
  RContext.height = height;
  RContext.bitspp = bitspp;
  if (bitspp==15)
  {
    DrawSection = DrawSection15;
    GouraudTriangle = GouraudTriangle15;
  }else
  {
    GouraudTriangle = GouraudTriangle8;
    TextureTriangle = TextureTriangle8;
    DrawSection = DrawSection8;
  }
  gbalTriangle = Triangle;
}


void gbalShadeModel(u8 m)
{
  if (m==GBAL_FLAT)
  {
    gbalTriangle = Triangle;
  }else
  {
    gbalTriangle = GouraudTriangle;  
  }
}


void gbalPolygonMode(u8 m)
{
  if (m<=2)
  {
    _polygon_mode = m;
  }
}


void gbalSetMode(u8 wich)
{
  if (wich<=5) 
  {
    *(u32 *)(0x04000000) = wich;
    if (wich==3)
    {
        FRONT = BACK = (u8 *)VRAM;
        gbalRContext(BACK,240,160,15);

    }else
    {
        FRONT = (u8 *)VRAM;
        BACK = FRONT+0x0A000;
        if (wich==4)
        {
            gbalRContext(BACK,240,160,8);
        }else
        {
            gbalRContext(BACK,160,128,15);
        }
    }
  
    //*(u16 *)(0x04000004) = 8;
  }
  _current_mode = wich;
  _dma_word_count = (u16)(((RContext.bitspp+1)>>3)*RContext.width*RContext.height)>>2;
  gbalClearBuffer = clearBufferDMA;
}



// I ripped this one from Eloist's wire-cube demo...
//
void gbalVSync()
{
/*
  __asm
   {
    mov 	r0, #0x4000006
    scanline_wait:
     ldrh	r1, [r0]
     cmp	r1, #160
    bne 	scanline_wait
   }
*/
    __asm
    {
     mov r0,#0x04000004
     wait_retrace:
       ldrh r1,[r0]
       tst r1,#1
     bne wait_retrace
    }
}


void gbalSetPalette(long wich, u16 *pal, int num_colors)
{
int i;
  if ((wich==BACKGROUND)||(wich==OBJECT))
  {
    for (i=0; i<num_colors; i++)
    {
      *(u16 *)(wich+i+i) = *(pal+i);
    }
  }
}


void gbalSetColor(long wich, long col_num, u16 col)
{
  if ((wich==BACKGROUND)||(wich==OBJECT))
  {
    col_num &= 255;
    *(u16 *)(wich+col_num+col_num) = col;
  }
}


void gbalTexImage2D(void *tex_addr, u32 tex_width, u32 tex_height)
{
  gbal_texture.texture = tex_addr;
  gbal_texture.width = tex_width;
  gbal_texture.height = tex_height;
}


void gbalEnable(u16 what)
{
  switch (what)
  {
    case GBAL_TEXTURE_2D:
      last_gbalTriangle = gbalTriangle;
      gbalTriangle = TextureTriangle;
      break;
    case GBAL_DMA_CLEAR:
      gbalClearBuffer = clearBufferDMA;
      break;
    default:
      break;
  }
}


void gbalDisable(u16 what)
{
  switch (what)
  {
    case GBAL_TEXTURE_2D:
      gbalTriangle = last_gbalTriangle;
      break;
    case GBAL_DMA_CLEAR:
      gbalClearBuffer = clearBufferCPU;
      break;
    default:
      break;
  }
}


 