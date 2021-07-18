/********************************************************
*	Just a quick mode 4 demo
*
*		  by devoto
*	(actualy most of the good stuff was taken
*     from eloist wire cube and Nokturn's KEY demos) 	*		
********************************************************/

// Gba.h has all the register definitions
#include "gba.h"//from Eloist Wire cube Demo
#include <math.h>

//Some direction defines 
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

//Key Definitions from Nokturn's key demo
#define KEY_A 1
#define KEY_B 2
#define KEY_SELECT 4
#define KEY_START 8
#define KEY_RIGHT 16
#define KEY_LEFT 32
#define KEY_UP 64
#define KEY_DOWN 128
#define KEY_R 256
#define KEY_L 512
int* KEYS = (int*)0x04000130;


//memory offset of the palette mem and video
u16 *palette_mem = (u16*)0x5000000;
u8* Video_Buffer8 = (u8*)0x600A000;

//maze data
const char maze[16][16]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,1,1,0,1,0,1,0,1,1,0,1},
	{1,0,1,0,1,0,0,0,1,1,1,0,1,1,0,1},
	{1,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1},
	{1,0,1,1,1,0,1,0,1,0,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
	{1,0,1,0,0,0,1,1,0,0,1,0,1,1,0,1},
	{1,0,1,0,1,0,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,1,0,1,1,1,1,0,1},
	{1,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//structure to hold a position

typedef struct xy {
	int x,y;
}xy;

//A couple of arrays that simplify the looking through the maze

struct xy increment[4]={{-1,0},{0,1},{1,0},{0,-1}};  //looks forward based on direction
struct xy left[4]={{0,-1},{-1,0},{0,1},{1,0}};       //  "    left     "    "    "
struct xy right[4]={{0,1},{1,0},{0,-1},{-1,0}};      //  "    right    "    "    "

//current position and such

struct xy pos={5,5};

int direction=0;   //
int visibility=4;

int mode = 0x04;  //current video mode.  Mode 4 apears to be a linear
                  //8 bit palette mode with a back buffer at 0x600A000.  You can
		  //Switch to back buffer by orring *(0x4000000) with
		  //0x10 

//Declerations
void WaitForVsync(void);
void line(int x1, int y1, int x2, int y2, int color);  //just good old bresham 
int sgn (int value);
int abs (int value);
void drawmaze(void);                                   	//draws maze
void Move(int Direction);			       	//moves fwd or back
int Get_Input(void);					//reads PAD and changes Direction
void Clear_Buffer(void);				//duh
void Wait(int time);					//waits
void Flip(void);					//flips back -> front / front->back

///////////////// C code entry (main())/////////////////////
int C_entry()
{
	//setup the display mode
	REG_DISPCNT = mode;   //set screen mode(REG_DISPCNT = *0x4000000)
	REG_DISPSTAT = 0x02;  //Not sure
	
	//Palette is 256 16 bit entries:  bbbbbgggggrrrrr-
 
	palette_mem[0] = 0x0;       //sets palette 0 to black
	palette_mem[15] = 0xF000;   //sets palette 15 to blue
	
	
/////////////////MAIN LOOP////////////////////	
	while (1)
	 {
	
	

	Clear_Buffer();
	Move(Get_Input());	//get_input returns direction if up or down was
						//pressed, 0 otherwise.				
	drawmaze();
	
	WaitForVsync();
	Flip();               	//swap front and back buffers
	Wait(300);		//wait a bit
	}
}
//////////////////////////////////////////////

///////WaitForVsync//////////////////////////
void WaitForVsync(void)
{
	__asm 
	{
		mov 	r0, #0x4000006   //0x4000006 is vertical trace counter when it hits 					 //160 the vblanc starts
		scanline_wait:
		ldrh	r1, [r0]
		cmp	r1, #160
		bne 	scanline_wait
	}			
}

///////Just a simple breshams line drawing rutine

void line(int x1,int y1,int x2,int y2,int color)
{
  int y_unit,x_unit; // Variables for amount of change
                     //  in x and y
  int i,xdiff,length,error_term;
  
  
  int offset=y1*240+x1+10; // Calculate offset into video RAM

  int ydiff=y2-y1;   // Calculate difference between
                     //  y coordinates
  
  
  x1+=10;  ///ofset to make up for screen size
  x2+=10;	//too lazy to change all the line drawing calls
			//so I just offset it here.  Delete these lines if you want
			//to use this code and the +10 in "int offset=y1*240+x1+10" above
  

  if (ydiff<0) {     // If the line moves in the negative
                     //  direction
    ydiff=-ydiff;    // ...get absolute value of difference
    y_unit=-240;     // ...and set negative unit in
                     //  y dimension
  }
  
  else y_unit=240;   // Else set positive unit in
                     //  y dimension

  xdiff=x2-x1;			// Calculate difference between
                        //  x coordinates
  if (xdiff<0) {				// If the line moves in the
                        //  negative direction
	  xdiff=-xdiff;				// ...get absolute value of
                        //  difference
	  x_unit=-1;					// ...and set negative unit
                        //  in x dimension
  }
  else x_unit=1;				// Else set positive unit in
                        //  y dimension

  error_term=0;			// Initialize error term
  if (xdiff>ydiff) {		// If difference is bigger in
                        //  x dimension
	  length=xdiff+1;	// ...prepare to count off in
                        //  x direction
    for (i=0; i<length; i++) {  // Loop through points
                                    //  in x direction
      if(mode == 0x04)
		  Video_Buffer8[offset] = color;	// Set the next pixel in the
     
      offset+=x_unit;				// Move offset to next pixel
                            //  in x direction
      error_term+=ydiff;		// Check to see if move
                            // required in y direction
      if (error_term>xdiff) {	// If so...
        error_term-=xdiff;		// ...reset error term
        offset+=y_unit;				// ...and move offset to next
                              //  pixel in y dir.
		  }
	  }
  }
  else {								// If difference is bigger in
                        //  y dimension
    length=ydiff+1;	// ...prepare to count off in
                        //  y direction
    for (i=0; i<length; i++) {	// Loop through points
                                    //  in y direction
      if(mode == 0x04)
		  Video_Buffer8[offset] = color;	// Set the next pixel in the
      

      offset+=y_unit;				// Move offset to next pixel
                            //  in y direction
      error_term+=xdiff;    // Check to see if move
                            //  required in x direction
      if (error_term>0) {		// If so...
        error_term-=ydiff;	// ...reset error term
        offset+=x_unit;			// ...and move offset to next
                            //  pixel in x dir.
      }
    }
  }
}


//////////////////sng and abs//////////////////
int sgn (int value)
{
	if (value<0)
		return -1;
	else
		return 1;
}
///////////////////////////////
int abs (int value)
{
	if (value<0)
		return (value-(2*value));	
	else
		return value;
}
////////////////////////////////////////////////

///////////////DRAWMAZE////////////////////////
void drawmaze(void)

// Draw the maze stored in array maze[] into video
// memory at address 0x6000000(or 0x600A000)
// Took this from my old VGA days.  
{
	struct xy block,lblock,rblock;
	int dist;

	// Draw the maze at each distance allowed by visibility

	for(dist=0; dist<visibility; dist++) {

		// Find current square of maze:

		block.x=pos.x+dist*increment[direction].x;
		block.y=pos.y+dist*increment[direction].y;

		// Find square to the left of current square:

		lblock.x=block.x+left[direction].x;
		lblock.y=block.y+left[direction].y;

		// Find square to the right of current square:

		rblock.x=block.x+right[direction].x;
		rblock.y=block.y+right[direction].y;

		// Draw image of squares according to distance:

		switch(dist) {
			case 0:  // Draw current square

				// Is wall open to the left?
				// If not, draw wall

				if (maze[lblock.x][lblock.y]) {
					line(0 ,19,53 ,44,15);
					line(53,44,53 ,93,15);
					line(53 ,93,0,118,15);
				}
				else { // Else draw opening
					line(0 ,44,53 ,44,15);
					line(53,44,53 ,93,15);
					line(53 ,93, 0,93,15);
				}

				// Is wall open to the right?
				// If not, draw wall

				if (maze[rblock.x][rblock.y]) {
					line(212,19,160,44,15);
					line(160,44,160,93,15);
					line(212,118,160,93,15);
				}
				else { // Else draw opening
					line(212,44,160,44,15);
					line(160,44,160,93,15);
					line(160,93,212,93,15);
				}
				break;
			case 1: // Repeat for next square

				// Can we see through the next square?
				// If not, draw wall

				if (maze[block.x][block.y]) {
					line(53,44,53,93,15);
					line(160,44,160,93,15);
					line(53,44,160,44,15);
					line(53,93,160,93,15);
				}
				else { // Else draw sides of next square
					if (maze[lblock.x][lblock.y]) {
						line(53,44,80,57,15);
						line(80,57,80,80,15);
						line(80,80,53,93,15);
					}
					else {
						line(53,57,80,57,15);
						line(80,57,80,80,15);
						line(80,80,53,80,15);
					}
					if (maze[rblock.x][rblock.y]) {
						line(160,44,133,57,15);
						line(133,57,133,80,15);
						line(133,80,160,93,15);
					}
					else {
						line(160,57,133,57,15);
						line(133,57,133,80,15);
						line(133,80,160,80,15);
					}
				}
				break;
			case 2: // Do it again
				if (maze[block.x][block.y]) {
					line(80,57,80,80,15);
					line(133,57,133,80,15);
					line(80,57,133,57,15);
					line(80,80,133,80,15);
				}
				else {
					if (maze[lblock.x][lblock.y]) {
						line(80,57,93,63,15);
						line(93,63,93,74,15);
						line(93,74,80,80,15);
					}
					else {
						line(80,63,93,63,15);
						line(93,63,93,74,15);
						line(93,74,80,74,15);
					}
					if (maze[rblock.x][rblock.y]) {
						line(133,57,120,63,15);
						line(120,63,120,74,15);
						line(120,74,133,80,15);
					}
					else {
						line(133,63,120,63,15);
						line(120,63,120,74,15);
						line(120,74,133,74,15);
					}
				}
				break;
			case 3: // And again
				if (maze[block.x][block.y]) {
					line(93,63,93,74,15);
					line(120,63,120,74,15);
					line(93,63,120,63,15);
					line(93,74,120,74,15);
				}
				else {
					if (maze[lblock.x][lblock.y]) {
						line(93,63,100,66,15);
						line(100,66,100,70,15);
						line(100,70,93,74,15);
					}
					else {
						line(93,66,100,66,15);//
						line(100,66,100,70,15);//
						line(100,70,93,70,15);//
					}
					if (maze[rblock.x][rblock.y]) {
						line(120,63,113,66,15);
						line(113,66,113,70,15);
						line(113,70,120,74,15);
					}
					else {
						line(120,66,113,66,15);
						line(113,66,113,70,15);
						line(113,70,120,70,15);
					}
				}
				break;
		}

		// If view is obscured by wall, stop drawing:

		if (maze[block.x][block.y]) break;
	}
}//End Draw Maze

////////////////////////////////////////////////////////

///////////////Get Input////////////////////////////////
int Get_Input(void)
{
	int d = 0; //keep track of delta

//key bits are reset when a key is pressed.  Apperantly they must be set back to 0;

	if(!((*KEYS) & KEY_UP))        //is UP bit 0?
	{
		d = UP;			//need to Move UP
		(*KEYS) |= KEY_UP;      //reset KEY_UP bit to 1
	}
	if(!((*KEYS) & KEY_DOWN))
	{
		d = DOWN;	
		(*KEYS) |= KEY_DOWN;
	}
	if(!((*KEYS) & KEY_LEFT))
	{
		direction -= 1;
		if(direction < 0)
			direction = 3;

		(*KEYS) |= KEY_LEFT;
	}
	if(!((*KEYS) & KEY_RIGHT))
	{
		direction += 1;
		if(direction > 3)
			direction = 0;

		(*KEYS) |= KEY_RIGHT;
	}
	if(!((*KEYS) & KEY_A))
	{
		//do A button stuff here
	}
	return d;
}

/////////////////////////////////////////////////////////

////////////////////MOVE/////////////////////////////////
void Move(int d)
{
	struct xy old;  //holds initial xy incase we try to move into a wall
	old.x = pos.x;
	old.y = pos.y;

	if(d == UP)
	{
		pos.x += increment[direction].x;     //move forward
		pos.y += increment[direction].y;		
	}
	if(d == DOWN)
	{
		pos.x -= increment[direction].x;     //Move back
		pos.y -= increment[direction].y;		
	}
	if(maze[pos.x][pos.y])     //inside a wall move back
	{
		pos.x = old.x;
		pos.y = old.y;
	}
}

void Clear_Buffer(void)
{
	int i;
	int* Video_Buffer32 = (int*)Video_Buffer8;  //make it a 32 bit pointer 

	if(mode == 0x4)
	{
		for(i = (240*160/4); i; i-=4)   //32 bit is faster
		{	
			Video_Buffer32[i] = 0;      //unroll it a little
			Video_Buffer32[i+1] = 0;
			Video_Buffer32[i+2] = 0;
			Video_Buffer32[i+3] = 0;
		}//end for
	}//end if
}// end Clear_Buffer

void Wait(int time)
{
	int i1,i2,temp;
	for(i1 = 0; i1 < time; i1++)
		for(i2 = 0; i2 < time; i2++)
			temp = i1*i2;
}//end Wait


void Flip(void)
{
	if(REG_DISPCNT == 0x04)
	{
		REG_DISPCNT |= 0x10;   //flip to back
		Video_Buffer8 = (u8*)0x6000000;  //draw to front
	}
	else
	{
		REG_DISPCNT = 0x04; //flip to front
		Video_Buffer8 = (u8*)0x600A000; //draw to back
	}//end ifelse
}//end flip