AGB Sample Game Explanation 


 - Operation Instructions
   If the B button is pressed when the dolphin is near the surface of the sea, it 
   jumps.  
   The dolphin moves up and down, and right and left by the +Control Pad.   
   If the dolphin bumps against the nautilus who is floating under water, the 
   dolphin knocks over it.  


 - Characters

   Dolphin
     A character controlled by a player.
   Nautiluses
     They are floating under water. 
     They occasionally blow a dart from a blowgun. 
     However, the darts do not hit the dolphin.  
   Rings
     They are floating under water.
     If the dolphin passes through the center of a ring, it moves up and down.  


 - Source File Configuration

   Background control  bg.c
   Enemy control       enemy.c
   Enemy data          enemy_dat.c
   General data        game_dat.c
   Collision detection hitcheck.c
   Main                main.c
   Player control      player.c
   Player data         player_dat.c
   Ring control        ring.c



 - Program Description

   Light Reflection Processing for the Dolphin
    The OBJ window is used for a cutout. The images are expressed with 
    semi-transparent processing using the ordinary OBJ underneath the layer and 
    the light BG.  
  

   Processing During H-Blank  
    The raster scroll is used for BG during H-blank, in order to give the 
    impression that the user is underwater.  

   BG Planes
    BG mode 0 is used.  

    Sky		BG1	256 colors	screen size  256 x 256
    Ocean A	BG2	256 colors	screen size  256 x 256
    Ocean B	BG2	256 colors	screen size  256 x 256
    Coral 	BG1	256 colors	screen size  256 x 256
    Light	BG0	256 colors	screen size  256 x 256

   Character Animation 
    Character animation is performed by DMA transferring image data into VRAM.
