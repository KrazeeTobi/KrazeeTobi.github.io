* Color Special Effect Test

- BG0      foremost ground   priority 1
- BG1      cloud             priority 2
- OBJ0     Yoshi(left)       priority 1
- OBJ1     Yoshi(middle)     priority 2
- OBJ2     Yoshi(right)      priority 3


How to operate buttons
  
  + key      : OBJ0 move
  + & A key  : OBJ1 move
  + & B key  : OBJ2 move 

   L : make the upper layer darker with alpha blending (EVA++, EVB--)
  R : make the lower layer darker with alpha blending (EVA--, EVB++)
  (The total of alpha blending is designed to be 1)
  
   (When B is pressed, EVY ,not EVA or EVB, changes)

  B + L :  EVY  +1
  B + R :  EVY  -1
  
   SELECT : OBJ semi-transparent ON/OFF switch

  START  : Select color special effect
     (alpha -> brightness UP -> brightness DOWN -> Nothing -> alpha -> ...)
  
