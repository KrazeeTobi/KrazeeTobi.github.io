This file contains bugs fixed with the GnuPro thumb compiler, assembler, etc.
If the current version is stable, you don't need to upgrade immediately.
These issues will be incorporated into the next AGB Dev Kit to be released 
soon in Japan.


(How to upgrade)
Please overwrite the files below.

thumb/cc1.exe               : Cygnus\thumbelf-000512\H-i686-cygwin32\lib\gcc-lib\thumb-elf\2.9-arm-000512
thumb/as.exe                : Cygnus\thumbelf-000512\H-i686-cygwin32\thumb-elf\bin
                            : Cygnus\thumbelf-000512\H-i686-cygwin32\bin
thumb/gasp.exe              : Cygnus\thumbelf-000512\H-i686-cygwin32\bin
thumb/objcopy.exe           : Cygnus\thumbelf-000512\H-i686-cygwin32\bin
thumb/thumb-elf-as.exe      : Cygnus\thumbelf-000512\H-i686-cygwin32\bin
thumb/thumb-elf-gasp.exe    : Cygnus\thumbelf-000512\H-i686-cygwin32\bin
thumb/thumb-elf-objcopy.exe : Cygnus\thumbelf-000512\H-i686-cygwin32\bin 


--Changes--

*Fixed bugs regarding comparison between unsigned short variables. 

[Example]
The following source code would generate incorrect binary code when compiled 
using -o2 option.

unsigned short b16 = 0xfff0;

sub()
{
    b16 += 0x0040;

    if (b16 + 0x20 >= 0x0100) {
        b16 = 0;
    }
}

[The result would be shown as follows using 'objdump']

00000000 <sub>:
    0:  4904 4904   ldr     r1, [pc, #16]   (14 <sub+0x14>)
    2:  8808 8808   ldrh    r0, [r1, #0]
    4:  3040 3040   add     r0, #64
    6:  8008 8008   strh    r0, [r1, #0]
    8:  3020 3020   add     r0, #32
    a:  28ff 28ff   cmp     r0, #255
    c:  dd01 dd01   ble     12 <sub+0x12>
    e:  2000 2000   mov     r0, #0
    10: 8008 8008   strh    r0, [r1, #0]
    12: 4770 4770   bx      lr
    14: 0000 0000   lsl     r0, r0, #0
    ...

When executing add instruction in address '8', carry-up moves to upper 16-bit.
Then, the next cmp instruction in address 'a' incorrectly compares with 
variable that has unneeded data in upper 16-bit.  It should compare with 
unsigned short variable.


*Fixed problem of a function giving an incorrect return value when it using 
automatic array defined by GCC extended format.

[Example source code causing problem]

static int Test(int Arg1, char *Message) {

    int  Size  = 4;
    char Table[Size];   // Using automatic array defined by GCC extended format
    int  Dummy = 0;

    return 1;

DUMMY_LABEL:
    sprintf( Message, "%X%X%X", Dummy, Dummy, Dummy );
    return 0;
}


*Fixed bug regarding address calculation with 'as'.

[Example (as_test.s)]

   .TEXT
   .ALIGN
TestStartAdr:
   .word  (TestEndAdr - TestStartAdr)
   .word  (TestStartAdr - TestEndAdr)
   .word  (TestEndAdr - TestStartAdr) << 8
   .word  (TestStartAdr - TestEndAdr) << 8
   .word  (TestEndAdr - TestStartAdr) / 2
   .word  (TestStartAdr - TestEndAdr) / 2
   .word  (TestEndAdr - TestStartAdr) * 2
   .word  (TestStartAdr - TestEndAdr) * 2
TestEndAdr:
   .END


[Correct output by GNUPro-98r2 (GNU assembler version 2.9-armelf-981216 (thumb-elf) using BFD version 2.9-armelf-981216)]
TestStartAdr:
   0x00000020
   0xffffffe0
   0x00002000
   0xffffe000
   0x00000010
   0xfffffff0
   0x00000040
   0xffffffc0
TestEndAdr:


[Wrong output by GNUPro-99r1p3 (GNU assembler version 2.9-arm-000512 (thumb-elf) using BFD version 2.9-arm-000512)]
TestStartAdr:
   0x00000020
   0x00000000
   0x00000000
   0x00000000
   0x00000000
   0x00000000
   0x00000000
   0x00000000
TestEndAdr:


*Changed so 'objcopy' won't output warning messages

[Warning message previously shown]
objcopy: Warning: Output file cannot represent architecture UNKNOWN!


