Simple Program Description 

- "make" Process
  Carry out a "make data" followed by "make" in Directory sample_yoshi/.  Data 
  Archive (bmp/islebmp/libislebmp.a,  bmp/  menubmp/libmenubmp.a, 
  bmp/yosbmp/libyosbmp.a,  bmp/yosbgbmp/libyosbgbmp.a) is created by "make data" 
  and linked to program when doing "make."

- Program Flow  
  main () of yos_main.c is the main.
  From this main loop, it calls one of the following at every frame, depending on
  the value of gMain.proc_num:
    * proc_0()     Menu (Rotation of Island)
    * yos_game()   Yoshi's Game

- Process during V Blank
  Interrupt routine of V Blank is VBlankIntr() of yos_main.c.
  After going through VBlankIntr(), (*gMain.pVBlankFunc)() is called.
  The processing the child process performs during V Blank is called by entering 
  a pointer in (*gMain.pVBlankFunc). This is to avoid the influence the long 
  duration of interrupt routine process may have on other interrupts.

- Process during H Blank
  H Blank Interrupt is used in Ocean and Sky in the menu.
  H Blank processing involves the child process directly changing the value of 
  the address table that is called from the interrupt routine. 

- Work Memory
  By designating it in the linker script file, the program overlays the work   
  area of child processes, such as:
  * Menu
  * Main part of the game
  Local variables in files are not used since only the (COMMON) section is
  to be overlaid in the linker scripts of the Yoshi sample.
  * Variables that can be seen globally are placed in the (COMMON) section. 
    Variables that cannot be seen globally are in (bss).

- Measurement of Yoshi Game CPU Processing Time
  By defining SPEED_CHK at yos_game.h, an egg is displayed on the screen when 
  START is pressed. The X Coordinate, which lies in the center of the egg 
  (the left edge of the screen is zero), indicates the number of lines for the 
  raster position when game process is completed. 
  The maximum is about 100. This location can be altered by changing the insert 
  location for the row of p1_line_count = ... in game_main().

- BG of Menu (Island)
  BG Mode 2 is used.  One for ocean and sky, and one for the island.  Perspective
  is added by changing scaling parameters in H Blank.  The sky is scrolled by
  changing scaling parameters.

- BG in Game
  BG Mode 1 is used.
  Distant View: 16 colors                   Screen size 256x256
  Intermediate View: 256 colors             Screen size 256x256
  Near View: Scaling screen (256 colors)    Screen size 512x512

- BG of Castle
  BG  Mode 3 (65536 colors) is used.

- OBJ in Game
  All use 256 colors. Those enlarged are always double-angle of character mode.

- Animation of Yoshi, etc.
  Done by rewriting the image data on VRAM.  
  DMA transfer is conducted in the function called after V Blank.
  Some items such as Dash Smoke have all the patterns on VRAM.

- Display Priority of OBJ in Game
  10 OAM lists are created and objects to displayed are entered in the OAM list.	  
  After entering all the objects to be displayed to the list, it creates OAM data 
  from the OAM list in order of priority and transfers using DMA during V Blank.  
  Since the list is cleared at the beginning of every frame, objects do not display 
  unless they are included in the list each time.

- Link of Image Data
  BG in game is compiled after converting to C source with bmp2agb.exe.
  Other image data is converted to object file (.o) with objcopy after converting
  to binary with bmp2bin or bmp2map. Since there is a large number of image data,
  they were archived using ar and linked as a library at the time of program
  compilation.

