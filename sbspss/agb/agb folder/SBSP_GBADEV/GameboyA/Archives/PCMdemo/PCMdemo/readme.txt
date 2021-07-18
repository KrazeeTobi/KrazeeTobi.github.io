AGB PCM playback sample program
April 18th, 2000
Nintendo of America Inc.
Developer support group

These files are sample program, which can playback wave(.wav) files
 by AGB PCM channels.  This program uses 2 PCM channels(A,B),
 2 DMA channels(1,2) and 1 Timer channel(0).

1. Description of files
    sound.c : Includes 4 functions to use PCM playback
        soundStart()  : Initialize and start PCM channels
        soundStop()   : Stop PCM channel immediately
        soundVblank() : This function must be called
                            at the end of V-blank routine every frame
        soundDmaIrq() : Interrupt routine for DMA2

    sound.h : This header file should be included
                 in source files(main.c) calling sound functions.

    main.h : Main source file of simple demo program
             Sound functions are called in this file

    pikachu.wav : Original wave file

    pikachu.bin : Raw binary wave data file made by wav2agb tool

    pikachu.h : Header file made by wav2agb tool
                This file is included in sound.c

    makefile : Makefile for this project
               This file can be used by Cygwin Pro tool

    simple.bin : ROM binary file for AGB target board

    wav2agb/wav2agb.exe : wav2agb tool workable under cygwin

    wav2agb/wav2agb.c : Source file of the tool

    Other files are same as ones in simple demo program

2. How to use this demo program
    Press A button to start sound and press B button to stop sound
    The sound stops automatically at the end

How to use these functions by yourselves
    1. Prepare your own wave file to playback.
    2. Use wav2agb tool(wav2agb.exe ****.wav).
       Then, bin file(****.bin) and header file(****.h) will be made.
    3. Modify sound.h to include the header file
           and change name of wave data array name.
    4. Include to call sound functions in your source file(s).
    5. Modify this makefile or your makefile to change sound object file(s)
    6. Make ROM data and execute it.

If you have some questions or requests, please let us know.
E-mail address : support@noa.com