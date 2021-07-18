;guano_99@hotmail.com

 AREA cdintro, CODE, READONLY

 ENTRY
 b start
 DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

start
 adrl r8,text
 ldr r3,const
 mov r0,#0x6000000
 adr r1,picture
 mov r2,#0x4000000
 add r2,r2,#0xd4
 str r1,[r2],#4
 str r0,[r2],#4
 str r3,[r2]
 ldr r3,const2
 mov r0,#0x5000000
 adr r1,colours
 mov r2,#0x4000000
 add r2,r2,#0xd4
 str r1,[r2],#4
 str r0,[r2],#4
 str r3,[r2]
 mov r6,#0

mainloop

 add r6,r6,#1
 and r6,r6,#15

 mov r0,#0x04
 add r0,r0,#0x400
 mov r1,#0x4000000
 str r0,[r1]
 mov r2,#20
 mov r3,#161
 mov r4,#20
 add r1,r1,#6

loop

 ldr r0,[r1]
 and r0,r0,#0xff
 cmp r0,r2
 bne loop

loop2

 ldr r0,[r1]
 and r0,r0,#0xff
 cmp r0,r3
 bne loop2

 sub r4,r4,#1
 bne loop

 ldr r3,const3
 mov r0,#0x6000000
 mov r1,r0
 add r1,r1,#0xe100
 mov r2,#0x4000000
 add r2,r2,#0xd4
 str r0,[r2],#4
 str r1,[r2],#4
 str r3,[r2]
 mov r0,#0x6000000
 mov r1,r0
 add r0,r0,#0x9600
 mov r2,#0x4000000
 add r2,r2,#0xd4
 str r0,[r2],#4
 str r1,[r2],#4
 str r3,[r2]
 mov r1,r0
 mov r0,#0x6000000
 add r0,r0,#0xe100
 mov r2,#0x4000000
 add r2,r2,#0xd4
 str r0,[r2],#4
 str r1,[r2],#4
 str r3,[r2]
 ldr r0,[r8]
 and r0,r0,#0xff
 cmp r6,#0
 bne notzero
 add r8,r8,#2
 ldr r1,[r8]
 and r1,r1,#0xff
 cmp r1,#0
 bne notzero

 adrl r8,text

notzero

 adrl r1,fonts
 mov r2,r0
 add r1,r1,r6
 add r1,r1,r6
 sub r0,r0,#32
 mov r2,#32
 mul r0,r2,r0
 add r1,r1,r0
 mov r0,#0x6000000
 add r0,r0,#0x7800
 add r0,r0,#0x4b0
 add r0,r0,#238
 mov r2,#32

loop3

 ldrh r4,[r1]
 strh r4,[r0]
 add r0,r0,#240
 add r1,r1,#2048
 subs r2,r2,#1
 bne loop3

 ldr r3,const4
 mov r0,#0x6000000
 add r0,r0,#0x7800
 add r0,r0,#0x4b0
 mov r1,r0
 sub r1,r1,#2
 mov r2,#0x4000000
 add r2,r2,#0xd4
 str r0,[r2],#4
 str r1,[r2],#4
 str r3,[r2]
 b mainloop

colours
        INCBIN 555.pal
const
        DCD 0x84007080
const2
        DCD 0x84000100
const3
        DCD 0x840012c0
const4
        DCD 0x80000b40

picture
        INCBIN pic.raw
        INCBIN pic1.raw
fonts
        INCBIN fonts.raw
text
        DCB "          W W W . C O N S O L E D E V . C O M   -     T H E "
        DCB "  O N L Y   C O N S O L E   D E V E L O P M E N T   W E B S "
        DCB "I T E   Y O U   N E E D           C O D E     B Y     G U A "
        DCB "N O _ 9 9 @ H O T M A I L . C O M             "
        DCD 0
 END

