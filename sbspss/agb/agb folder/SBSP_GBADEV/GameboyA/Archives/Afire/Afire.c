// Fullscreen fire effect for the GBA
// /Mic, 2000 | stabmaster_@hotmail.com | come.to/progzone
//
// How to compile this baby:
//
//  zarmcc -c -Wall -Otime -ansic -fpu none -Littleend -cpu ARM7TDMI -apcs /narrow/noswst afire.c -o afire.o
//  zarmlink -bin -map -ro-base 0x8000000 -rw-base 0x3000000 afire.o -o afire.bin
//
//
// This is my first ever GBA proggy. I haven't had the time to learn that much bout the
// machine, wich explains why the code is so crappy. I guess the GBA was made for tile &
// sprite operations, and not for per-pixel effects like this one..
//
// Need info about GBA coding?  These sites can be useful:
//
//  www.consoledev.com
//  www.zophar.net
//
// And finally some credits:
// 
//  * All the people who've released their GBA demos as open-source, leaving me with
//    at least a clue of what to do..
//  * And of course "the invisible man" for his GBA emu.
//

 


#include <stdlib.h>

#define DISPCNT	((unsigned short *)0x04000000)
#define PALETTE	((unsigned short *)0x5000000)
#define SCREEN	((unsigned char *)0x6000000)

// Define some types to save me some typing later on.
//
typedef unsigned char uchar;
typedef unsigned short ushort;


ushort random16[63] = 
 {
   25662,56977,36314,46707,
   56747,47936,28467,50155,
   54470,9126,19191,26274,
   27205,13469,6769,48786,
   43195,17969,58549,13097,
   9962,26613,60724,25428,
   44416,43884,31777,40699,
   4280,32767,31882,41912,
   19050,42386,38267,39411,
   11739,36780,10921,43911,
   7473,38901,28614,62047,
   25094,22064,16149,14666,
   46209,34643,30017,25842,
   64242,3527,34102,35358,
   2277,3678,16479,3431,
   36135,63741,11311,
 };
uchar seed1=29, seed2=63;




// The GBA background palette consists of 256 (?) color entries in a 555-format
// (B at the top, R at the bottom).
//
ushort makecolor(ushort r, ushort g, ushort b)
{
  return ((r>>3) | ((g & 0xF8)<<2) | ((b & 0xF8)<<7));
}


// I ripped this one from Eloist's wire-cube demo...
//
void vsync()
{
  __asm
   {
    mov 	r0, #0x4000006
    scanline_wait:
     ldrh	r1, [r0]
     cmp	r1, #160
    bne 	scanline_wait
   }
}




int main()
{
int i,x,y,roffs,woffs;
ushort *pal;
uchar *video;
ushort pixel;


// Set graphics mode. I have no idea how this works, I just ripped it from
// Jum Hig's stars demo.
//
  *DISPCNT = 0x0404;

// Set up the palette:
//  Black -> Red -> Yellow -> White
//
pal = PALETTE;
for (i=0; i<32; i++)
 {
   pal[i] = makecolor((i<<3),0,0);
   pal[i+32] = makecolor(255,(i<<3),0);
   pal[i+64] = makecolor(255,255,(i<<3));
   //pal++;
 }

 // Set the remaining colors to white.
 // 
 for (i=96; i<256; i++) pal[i] = 0x7FFF;



  video = SCREEN;

  // Keep burnin' forever..
  //
  while (1)
   {
     vsync();
     for (x=2; x<240; x+=2)
      {
        roffs = 478+x;
        woffs = x;
        for (y=2; y<=156; y+=2)
         {
           pixel = (uchar)(*(video+roffs));
           pixel += (uchar)(*(video+roffs+2));
           pixel += (uchar)(*(video+roffs+4));
           pixel += (uchar)(*(video+roffs+484));
           pixel = (pixel>>2);
           if (pixel>0) pixel--;
           pixel |= (pixel<<8);

           *(ushort *)(video+woffs) = pixel;
           *(ushort *)(video+woffs+240) = pixel;
           roffs += 480;
           woffs += 480;
         }

        // Generate a random number.
        //
        pixel = random16[seed1];
        pixel += random16[seed2];
        random16[seed2] = pixel;
        seed1 += 1; seed1 &= 63;
        seed2 += 1; seed2 &= 63;

        // Write a random pixel (0-191) at {x,158}.
        //
        *(video+37440+x) = (uchar)((pixel+10) & 191);
      }
   }
  return 0;
}

       





