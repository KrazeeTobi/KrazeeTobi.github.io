This zip file contains two programs that will allow you to convert AVIs for playback on the Game Boy Advance (AGB).

---------------------------------AVI2BMP.zip------------------------------------

The program AVI2BMP.exe is a Windows tool that will convert an AVI to a series of BMPs. It produces a makefile, a data file, a C header file, a C source file and a WAV file. A brief explanation of each file follows:

 - The makefile contains the commands necessary to convert the bitmap files into a data library for your project. This library will contain compressed data depending on the compression you chose inside the program, AVI2BMP.exe. The compression techniques available are those supported by the AGB's built in system functions.

 - The data file is used by the above makefile and contains the names of the bitmaps the makefile will need to reference in order to compile the bitmap library.

 - The C header file contains define statements for the AVI Length (number of frames), the AVI Scale (micro-seconds per frame), Frame Wait (number of V-blank periods to wait before loading the next frame), BG State (BG display mode value), BG Center X and BG Center Y (starting center point for BG). This file also contains a lookup table for the individual bitmaps (frames), the combined palette data for all of the frames (if in 240x160 256 color mode) and the function headers for the C source file. 

 - The C source file contains the function used to load the first frame and palette data into VRAM (InitData), and the function used to load the compressed data into VRAM using the appropriate API function call for uncompressing data (FrameSwap).

 - The WAV file contains the audio data. If there isn't any audio data you will be notified via a message box when the conversion process takes place.

Notes concerning the AVI2BMP program: 

 - AVI2BMP will only convert AVIs which are correctly formatted for the BMP2AGB.exe command line tool found in the AGB Developer's Kit. These formats are:

	 - Color Depth: 24 bit or 8 bit
	 - Resolutions: 240x160 or 160x128

 - If you are converting an AVI that has a 240x160 resolution, you will need to make sure that the entire AVI uses a shared palette. The player only uses the palette from the first bitmap. This increases the performance of the player, as it doesn't have to swap a new palette in for each frame.

The source code for the AVI2BMP program is included in AVI2BMP.zip.

---------------------------------Player.zip-------------------------------------

The AGB AVI player, contained in Player.zip, uses the output files from AVI2BMP.exe and creates a simple AVI player for the AGB. All you need to do to compile the Player is copy the files into a sub-directory (named bitmap) and use the makefile found in the Player directory. (This project assumes you have used the default installation directories for the AGB Development Kit. If not, you will need to adjust the main makefile.)

Notes concerning the Player project: 

 - The Player project doesn't use any timer functions to control the playback rate. It uses a V-Blank counter to keep track of the number of screen refreshes that have occurred. When this counter is greater than or equal to the Frame Wait variable, then it calls the Frame Swap function.

 - Also, the compression API takes about three frames to uncompress a single frame. Therefore, any AVI that is faster than 20 frames per second will not play back properly.

 
Please feel free to adjust the program as you see fit. If you run into any further issues, or you would like to make a suggestion, please let me know (jamesve@noa.nintendo.com).
