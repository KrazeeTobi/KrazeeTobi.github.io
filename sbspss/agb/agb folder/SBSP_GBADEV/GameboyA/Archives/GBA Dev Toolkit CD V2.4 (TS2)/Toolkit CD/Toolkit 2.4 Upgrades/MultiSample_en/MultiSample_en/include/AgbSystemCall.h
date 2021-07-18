/********************************************************************/
/*          AgbSystemCall.h                                         */
/*            AGB System Call                                       */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _AGB_SYSTEM_CALL_H
#define _AGB_SYSTEM_CALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <AgbTypes.h>
#include <AgbSound.h>
#include <AgbMultiBoot.h>


#ifdef  __GNUC__
#ifndef CODE32
#define SystemCall(No)   asm ("SWI    "#No)
#else
#define SystemCall(No)   asm ("SWI    "#No" << 16")
#endif
#else
#ifndef CODE32
#define SystemCall(No) __asm { SWI    No}
#else
#define SystemCall(No) __asm { SWI    No << 16}
#endif
#endif


/*------------------------------------------------------------------*/
/*                   System Call No.                             */
/*------------------------------------------------------------------*/

#define SWI_NO_RESTART                  0       // SoftReset()
#define SWI_NO_REGISTER_RAM_RESET       1       // SoftReset()/RegisterRamReset()
#define SWI_NO_HALT                     2       // Halt()
#define SWI_NO_STOP                     3       // Stop()

#define SWI_NO_INTR_WAIT                4       // IntrWait()
#define SWI_NO_VBLANK_INTR_WAIT         5       // VBlankIntrWait()

#define SWI_NO_DIV                      6       // Div()/DivRem()
#define SWI_NO_DIV_ARM                  7       // DivArm()/DivRemArm()
#define SWI_NO_SQRT                     8       // Sqrt()
#define SWI_NO_ARCTAN                   9       // ArcTan()
#define SWI_NO_ARCTAN2                  10      // ArcTan2()

#define SWI_NO_CPU_SET                  11      // CpuSet()
#define SWI_NO_CPU_FAST_SET             12      // CpuFastSet()
#define SWI_NO_BG_AFFINE_SET            14      // BgAffineSet()
#define SWI_NO_OBJ_AFFINE_SET           15      // ObjAffineSet()
#define SWI_NO_BIT_UNPACK               16      // BitUnPack()
#define SWI_NO_LZ77_UNCOMP_WRAM         17      // LZ77UnCompWram()
#define SWI_NO_LZ77_UNCOMP_VRAM         18      // LZ77UnCompVram()
#define SWI_NO_HUFF_UNCOMP              19      // HuffUnComp()
#define SWI_NO_RL_UNCOMP_WRAM           20      // RLUnCompWram()
#define SWI_NO_RL_UNCOMP_VRAM           21      // RLUnCompVram()
#define SWI_NO_DIFF_8BIT_UNFILTER_WRAM  22      // Diff8bitUnFilterWram()
#define SWI_NO_DIFF_8BIT_UNFILTER_VRAM  23      // Diff8bitUnFilterVram()
#define SWI_NO_DIFF_16BIT_UNFILTER      24      // Diff16bitUnFilter()

#define SWI_NO_SOUND_BIAS_CHANGE        25      // SoundBiasSet()/SoundBiasReset()
#define SWI_NO_SOUND_DRIVER_INIT        26      // SoundDriverInit()
#define SWI_NO_SOUND_DRIVER_MODE        27      // SoundDriverMode()
#define SWI_NO_SOUND_DRIVER_MAIN        28      // SoundDriverMain()
#define SWI_NO_SOUND_DRIVER_VSYNC       29      // SoundDriverVSync()
#define SWI_NO_SOUND_DRIVER_VSYNC_OFF   40      // SoundDriverVSyncOff()
#define SWI_NO_SOUND_DRIVER_VSYNC_ON    41      // SoundDriverVSyncOn()
#define SWI_NO_SOUND_CHANNEL_CLEAR      30      // SoundChannelClear()
#define SWI_NO_MIDI_KEY_2_FREQ          31      // MidiKey2Freq()
#define SWI_NO_MUSIC_PLAYER_OPEN        32      // MusicPlayerOpen()
#define SWI_NO_MUSIC_PLAYER_START       33      // MusicPlayerStart()
#define SWI_NO_MUSIC_PLAYER_STOP        34      // MusicPlayerStop()
#define SWI_NO_MUSIC_PLAYER_CONTINUE    35      // MusicPlayerContinue()
#define SWI_NO_MUSIC_PLAYER_FADEOUT     36      // MusicPlayerFadeOut()

#define SWI_NO_MULTI_BOOT               37      // MultiBoot()


/*------------------------------------------------------------------*/
/*                   Software Reset                                 */
/*------------------------------------------------------------------*/

extern void SoftReset(u32 ResetFlags);

// Reset the register and RAM specified in ResetFlags and return to address 
// 0x8000000.
// CPU core register and the area 0x3007e00~0x3007fff of CPU internal RAM are 
// forced to clear.
//
// Arguments:
//    u32 ResetFlags      Specify register and RAM that are to be reset 
//                        (Refer to AgbDefine.h).

/*------------------------------------------------------------------*/
/*               Register & RAM Reset                               */
/*------------------------------------------------------------------*/

extern void RegisterRamReset(u32 ResetFlags);

// Reset the register and RAM that are specified in ResetFlags.
// However, do not clear the area 0x3007e00~0x3007fff of CPU internal RAM.
//
// Arguments:
//    u32 ResetFlags      Specify register and RAM that are to be reset 
//                        (Refer to AgbDefine.h).

/*------------------------------------------------------------------*/
/*                       HALT                                       */
/*------------------------------------------------------------------*/

#define Halt()                   SystemCall(2)

// Stop CPU only.
// Return with interrupt request (IF set) where valid interrupt is enable 
// (Set to IE).

/*------------------------------------------------------------------*/
/*                       STOP                                       */
/*------------------------------------------------------------------*/

extern void SoundBiasSet(void);
extern void SoundBiasReset(void);

#define Stop()                                               \
{                                                            \
    SoundBiasReset();                                        \
    SystemCall(3);                                           \
    SoundBiasSet();                                          \
}

// Stop Source Oscillation.
// When corresponding interrupt is enabled (set to IE), return with the 
// generation of the conditions for an interrupt request from a key, a Game Pak or
// SIO.
// IF flag will not be set since source oscillation is stopped.
// LCDC must be OFF when executed.

/*------------------------------------------------------------------*/
/*                 Interrupt Wait                                   */
/*------------------------------------------------------------------*/

extern void IntrWait(u8 InitCheckClear, u16 IntrFlags);

// Continue to wait in Halt status until interrupt specified in IntrFlags is 
// generated.
// Set the flag that corresponds to INTR_CHECK_BUF(0x3007ff8) using an interrupt 
// process.
// Overhead to call for system call can be reduced by using multiple interrupts at
// the same time when compared with the case where Halt() is called back 
// repeatedly.
//
// Arguments:
//    u8  InitCheckClear  Specify whether or not to clear when applicable flag has
//                        already been set.
//    u16 IntrFlags       Specify wait interrupt (refer to AgbDefine.h)

/*------------------------------------------------------------------*/
/*                    V Blank Interrupt Wait                        */
/*------------------------------------------------------------------*/

extern void VBlankIntrWait(void);

// Continue to wait in Halt status until V blank interrupt occurs.
// Set flag that corresonds to INTR_CHECK_BUF(0x3007ff8) in interrupt process.
// Overhead to call for system call can be reduced by using multiple interrupts at
// the same time when compared to the case where Halt() is called back repeatedly.
// It is equivalent to IntrWait(1, V_BLANK_INTR_FLAG).

/*------------------------------------------------------------------*/
/*                   Division with codes  (Quotient)                */
/*------------------------------------------------------------------*/

extern s32 Div(s32 Number, s32 Denom);      // Compaible with the library from RedHat (Formerly Cygnus)
extern s32 DivArm(s32 Denom, s32 Number);   // Compatible with the library from ARM

// Calculate Number/Denom.
// Register value is returned as r0=Number/Denom, r1=Number%Denom, 
// r3=|Number/Denom|.
//
// Arguments:
//    s32 Number           Numerator
//    s32 Denom           Denominator

/*------------------------------------------------------------------*/
/*                   Devision with codes (Remainder)                */
/*------------------------------------------------------------------*/

extern s32 DivRem(s32 Number, s32 Denom);   // Compatible with the library from RedHat (Formerly Cygnus)
extern s32 DivRemArm(s32 Denom, s32 Number); // Compatible with the library from ARM

// Calculate Number%Denom.
// Register value is returned as r0=Number%Denom, r1=Number%Denom, 
// r3=|Number/Denom|.
//
// Arguments:
//    s32 Number          Numerator
//    s32 Denom           Denominator

/*------------------------------------------------------------------*/
/*                   Square Root                                    */
/*------------------------------------------------------------------*/

extern u16 Sqrt(u32 X);

// Calculate square root.
// In order to make it accurate, shift argumentX by the multiple of 2 to the left,
// and shift return value to the right by the multiplied number used to match 
// digit.

/*------------------------------------------------------------------*/
/*                   Arc Tangent                                    */
/*------------------------------------------------------------------*/

extern s16 ArcTan(s16 Tan);

// Calculate arc tangent value.
// For return value, return -pi/2<theta<pi/2 in the range of 0xc000~0x4000.
// However, the range theta<-pi/4,pi/4<theta has a problem with accuracy.
//
// Arguments:
//    s16 Tan
//        Code:1
//        Integer part:1
//        Decimal part:14

/*------------------------------------------------------------------*/
/*                   Arc Tangent 2                                  */
/*------------------------------------------------------------------*/

extern u16 ArcTan2(s16 X, s16 Y);

// Calculate the arc tangent value after correction process.
// Use this for regular purpose.
// For return value, return 0<=theta<2pi in the range of 0~0xffff.
//
// Arguments:
//    s16 X, Y
//        Code:1
//        Integer part:1
//        Decimal part:14

/*------------------------------------------------------------------*/
/*                        Set CPU                                   */
/*------------------------------------------------------------------*/

extern void CpuSet(void *Srcp, void *Destp, u32 DmaCntData);

// Clear or copy RAM with a parameter which is compatible with DmaSet macro.
//* At 32-bit transfer, RAM is accessed forcefully by 4 byte boundary, and at 16-bit transfer,
// arguments need to be set by 2 byte boundary to access RAM. 
//
// Arguments:
//    void *Srcp          Source Address
//    void *Destp         Destination Address
//    u32 DmaCntData      Only DMA_SRC_FIX/DMA_32BIT_BUS/DMA_COUNT_MASK is valid
//          DMA_SRC_FIX(  0, 1) = (Source Address Increment, Source Address Fixed)
//          DMA_32BIT_BUS(0, 1) = (16bit Transfer, 32bit Transfer)
//          DMA_COUNT_MASK & DmaCntData = Transfer Count
//
// Upper Macro:
//  CpuClear, CpuArrayClear, CpuCopy, CpuArrayCopy

/*------------------------------------------------------------------*/
/*                   High Speed Set CPU                             */
/*------------------------------------------------------------------*/

extern void CpuFastSet(void *Srcp, void *Destp, u32 DmaCntData);

// Clear or copy RAM in high speed with a parameter which is compatible with 
// the DmaSet macro.
//* However, it is a 32-bit transfer by 32 bytes (8 words).
//* Even if arguments other than 4 byte boundary are given, RAM is accessed by 4 byte boundary forcefully.
//
// Arguments:
//    void *Srcp          Source Address
//    void *Destp         Destination Address
//    u32 DmaCntData      Only DMA_SRC_FIX/DMA_COUNT_MASK is valid
//          DMA_SRC_FIX(0, 1) = (Source Address Increment, Source Address Fixed)
//          DMA_COUNT_MASK & DmaCntData = Transfer Count
//
// Upper Macro:
//  CpuFastClear, CpuFastArrayClear, CpuFastCopy, CpuFastArrayCopy

/*------------------------------------------------------------------*/
/*                   Set BG Affine Transformation                   */
/*------------------------------------------------------------------*/

extern void BgAffineSet(BgAffineSrcData *Srcp, BgAffineDestData *Destp, s32 Num);

// Calculate and set the BG affine parameter.
//
// Arguments:
//  BgAffineSrcData  *Srcp      Source Address
//  BgAffineDestData *Destp     Destination Address
//              s32   Num       Number of times calculated
//
// BgAffineSrcData Structure
//    s32 SrcCenterX            Source Data Center Coordinate (8bits after decimal
//                               point)
//    s32 SrcCenterY
//    s16 DispCenterX           Display Center Coordinate
//    s16 DispCenterY
//    s16 RatioX                Scaling Ratio (8 bits after decimal point)
//    s16 RatioY
//    u16 Theta                 Rotation Angle (8bits after decimal point)
//                                  Valid Range    0 - 0xffff
// BgAffineDestData Structure
//    s16 H_DiffX               Line Direction X Coordinate Difference
//    s16 V_DiffX                 Vertical Direction X Coordinate Difference
//    s16 H_DiffY               Line Direction Y Coordinate Difference
//    s16 V_DiffY                 Vertical Direction Y Coordinate Difference
//    s32 StartX                Start X Coordinate
//    s32 StartY                Start Y Coordinate

/*------------------------------------------------------------------*/
/*                   Set OBJ Affine Transformation                   */
/*------------------------------------------------------------------*/

extern void ObjAffineSet(ObjAffineSrcData *Srcp, void *Destp, s32 Num, s32 Offset);

// Calculate and set the OBJ affine parameter.
//
// Arguments:
//  ObjAffineSrcData *Srcp      Source Address
//              void *Destp     Destination Address
//              s32   Num       Number of times calculated
//              s32   Offset    Parameter address offset byte size (Normally 2|8)
//                              Designate "8" when directly setting to OAM
//
// ObjAffineSrcData Structure
//    s16 RatioX                Scaling Ratio (8bits to the right of the decimal 
//                              point)
//    s16 RatioY
//    u16 Theta                 Rotation Angle (8bits after decimal point)
//                                  Valid Range    0 - 0xffff
// ObjAffineDestData Structure
//    s16 H_DiffX               Line Direction X Coordinate Difference
//    s16 V_DiffX                 Vertical Direction X Coordinate Difference
//    s16 H_DiffY               Line Direction Y Coordinate Difference
//    s16 V_DiffY                 Vertical Direction Y Coordinate Difference

/*------------------------------------------------------------------*/
/*                       Bit Compressed Data Expansion              */
/*------------------------------------------------------------------*/

extern void BitUnPack(void  *Srcp, void *Destp, BitUnPackParam *BitUnPackParamp);

// Expand data with 0 fixed bit.
// Match the destination address to a 4 byte boundary.
//
// Arguments:
//            void *Srcp    Source Address
//            void *Destp   Destination Address
//  BitUnPackParam *Paramp  BitUnPackParam Structure Data Address
//
// BitUnPackParam Structure
//    u16 SrcNum              Source Data Byte Number
//    u8  SrcBitNum           1 Source Data Bit Number
//    u8  DestBitNum          1 Destination Data Bit Number
//    u32 DestOffset:31       Number of offsets that are added to source data
//        DestOffset0_On:1    Flag to indicate whether or not offsett is added to 
//                            0 data

/*------------------------------------------------------------------*/
/*             LZ77 Compressed Data Expansion (-> Work RAM)         */
/*------------------------------------------------------------------*/

extern void LZ77UnCompWram(void *Srcp, void *Destp);

// Expand LZ77 compressed data and write by 8 bits.
// Cannot expand directly to VRAM.
// When the compressed data size is not a multiple of 4, fill as much as possible 
// wtih 0 and adjust.
// Match the source address to a 4-byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 :4                  Reserve
//        CompType:4          Compressed Type (=1)
//        DestSize:24         Post-expansion data size
//
// Flag Data Format
//    u8  Flags               Compressed/Noncompressed flag
//                            (0, 1) = (Noncompressed data, compressed data)
// Code Data Format (Big Endian)
//    u16 Length:4            Expansion Data Length - 3 (Compress only when 
//                            matching length is 3 bytes or more.)
//        Offset:12           Matching Data Offset - 1

/*------------------------------------------------------------------*/
/*                   LZ77 Compressed Data Expansion (-> VRAM)       */
/*------------------------------------------------------------------*/

extern void LZ77UnCompVram(void *Srcp, void *Destp);

// Expand LZ77 compressed data and write with 16 bit units.
// Can expand to Work RAM as well, but slower than LZ77UnCompWram().
// The compressed data should be a matching character string of 2 bytes or more.
// When compressed data size is not a multiple of 4, fill as much as possible 
// with 0 and adjust.
// Match the source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 :4                  Reserve
//        CompType:4          Compressed Type (=1)
//        DestSize:24         Post-expansion data size
//
// Flag Data Format
//    u8  Flags               Compressed/Noncompressed flag
//                            (0, 1) = (Noncompressed data, Compressed data)
// Code Data Format (Big Endian)
//    u16 Length:4            Expanded data length - 3 (Compress only when 
//                            matching length is 3 bytes or more)
//        Offset:12           Matching Data Offset ( >= 2) - 1

/*------------------------------------------------------------------*/
/*                   Huffman Compressed Data Expansion              */
/*------------------------------------------------------------------*/

extern void HuffUnComp(void *Srcp, void *Destp);

// Expand Huffman compressed data and write with 32 bit units.
// When compressed data size is not a multiple of 4, fill as much as possible 
// with 0 and adjust.
// Match the source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 BitSize:4           1 Data Bit Size (Normally 4|8)
//        CompType:4          Compressed Type ( = 2)
//        DestSize:24         Post-expansion data size
//
// Tree Table
//    u8           TreeSize        Tree Table Size/2 - 1
//    TreeNodeData RootNode        Root Node
//
//    TreeNodeData LeftNode        Root Left Node
//    TreeNodeData RightNode       Root Right Node
//
//    TreeNodeData LeftleftNode    Left Left Node
//    TreeNodeData leftRightNode   Left Right Node
//
//    TreeNodeData RightLeftNode   Right Left Node
//    TreeNodeData RightRightNode  Right Right Node
//
//            .
//            .
//
// Following is Main Body of Compressed Data
//
// TreeNodeData Structure
//    u8  NextNodeOffset:6    Offset to next node data - 1 (2 byte unit)
//        RightEndFlag:1      Right node end flag
//        LeftEndFlag:1       Left node end flag
//                            When end flag is set
//                            Data in next node

/*------------------------------------------------------------------*/
/*           Run Length Compressed Data Expansion (->Work RAM)      */
/*------------------------------------------------------------------*/

extern void RLUnCompWram(void *Srcp, void *Destp);

// Expand run length compressed data and write with 8 bit units.
// Cannot directly expand to VRAM.
// When compressed data size is not a multiple of 4, fill as much as possible 
// with 0 and adjust.
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 :4                  Reserve
//        CompType:4          Compressed Type (=3)
//        DestSize:24         Post-expansion Data Size
//
// Flag Data Format 
//    u8  Length:7            Expanded Data Length - 1 (When not compressed)
//                            Expanded Data Length - 3 (Compress only when a 
//                            continuous length is 3 bytes or more)
//        Flag:1              (0, 1) = (Noncompressed data, Compressed data)

/*------------------------------------------------------------------*/
/*              Run Length Compressed Data Expansion (->VRAM)       */
/*------------------------------------------------------------------*/

extern void RLUnCompVram(void *Srcp, void *Destp);

// Expand run length compressed data and write with 16 bit units.
// Can expand to Work RAM, but slower than RLUnCompWram().
// When compressed data size is not a multiple of 4, fill as much as possible 
// with 0 and adjust.
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 :4                  Reserve
//        CompType:4          Compressed Type (=3)
//        DestSize:24         Post-expansion data size
//
// Flag Data Format
//    u8  Length:7            Expansion Data Length - 1 (When not compressed)
//                            Expansion Data Length -3 (Compress only when a 
//                            consecutive length is  3 bytes or more)
//        Flag:1              (0, 1) = (Noncompressed Data, Compressed Data)

/*------------------------------------------------------------------*/
/*          Difference Filter Expansion (8bits -> Work RAM)         */
/*------------------------------------------------------------------*/

extern void Diff8bitUnFilterWram(void *Srcp, void *Destp);

// Expand 8 bit difference filter process data and write with 8 bit units.
// Cannot directly expand to VRAM.
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 ByteSize:4          1 data byte size ( = 1)
//        FiltType:4          Filter Type ( = 8)
//        DestSize:24         Post-expansion data size
//
// Data Format
//    u8  Origin              Source Data
//    u8  Diff                Difference Data
//         .
//         .

/*------------------------------------------------------------------*/
/*          Difference Filter Expansion (8 bit -> VRAM)             */
/*------------------------------------------------------------------*/

extern void Diff8bitUnFilterVram(void *Srcp, void *Destp);

// Expand 8 bit difference filter processed data and write with 16 bit units.
// Can expand to Work RAM, but slower than Diff8bitUnFilterVram().
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 ByteSize:4          1 data byte size ( = 1)
//        FilterType:4        Filter Type ( = 8)
//        DestSize:24         Post-expansion data size
//
// Data Format
//    u8  Origin              Source Data
//    u8  Diff                Difference Data
//         .
//         .

/*------------------------------------------------------------------*/
/*                   Difference Filter Expansion (16Bit)            */
/*------------------------------------------------------------------*/

extern void Diff16bitUnFilter(void *Srcp, void *Destp);

// Expand 16 bit difference filter processed data and write with 16 bit units.
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 ByteSize:4          1 data byte size ( = 2)
//        FilterType:4        Filter Type ( = 8)
//        DestSize:24         Post-expansion data size
//
// Data Format
//    u16 Origin              Source Data
//    u16 Diff                Difference Data
//         .
//         .

/*------------------------------------------------------------------*/
/*                       Sound BIAS Set                             */
/*------------------------------------------------------------------*/

extern void SoundBiasSet(void);

// Move sound BIAS from 0 to an intermediate value (0x200).

/*------------------------------------------------------------------*/
/*                       Sound BIAS Reset                           */
/*------------------------------------------------------------------*/

extern void SoundBiasReset(void);

// Move sound BIAS from 0 to an intermediate value (0x200).

/*------------------------------------------------------------------*/
/*              Sound Driver Initialization                         */
/*------------------------------------------------------------------*/

extern void SoundDriverInit(SoundArea *sa);

// Initialize sound driver.
// Call only once when starting up game.
// At that time, you must set aside the work area, sa, in advance.
// Also, even if you prepare in advance, you cannot execute this driver multiple 
// times.

/*------------------------------------------------------------------*/
/*              Sound Driver Operation Mode                         */
/*------------------------------------------------------------------*/

extern void SoundDriverMode(u32 mode);

// Set operation mode of sound driver.
//  
//  * Direct Sound Reverb (Initial value 0)
//      mode = SOUND_MODE_REVERB_SET + (Reverb value 0~127);
//  
//  * Direct Sound Simultaneous Sound Number (Initial value 8)
//      mode = (Simultaneous sound number 1~12) << SOUND_MODE_MAXCHN_SHIFT;
//  
//  * Direct Sound Master Volume (Initial value 15)
//      mode = (Volume 1~15) << SOUND_MODE_MASVOL_SHIFT;
//  
//  * Direct Sound Replay Frequency (Initial value 13379Hz)
//      mode = SOUND_MODE_FREQ_?????;
//             (????? value) Value defined in AgbSound.h (12 types)
//  
//  * Final D/A Converter Bit Number (Initial value 8 bits)
//      mode = SOUND_MODE_DA_BIT_?;
//                            (? value) 9~6
//  
//  * It is possible to set the values above at the same time using OR.

/*------------------------------------------------------------------*/
/*                    Sound Driver Main                             */
/*------------------------------------------------------------------*/

extern void SoundDriverMain(void);

// Sound driver main
// Call every 1/60 second.  The flow of the process is, immediately after V-Blank
// interrupt, call SoundDriverVSync() (described later), then process BG and OBJ.  
// Then, call this routine.

/*------------------------------------------------------------------*/
/*                       Sound Driver DMA Reset                     */
/*------------------------------------------------------------------*/

extern void SoundDriverVSync(void);

// Extremely short system call that resets sound DMA.
// The timing is severe so call immediately after the V-blank interrupt is 
// entered every 1/60 second.

/*------------------------------------------------------------------*/
/*                    Sound Channel Clear                           */
/*------------------------------------------------------------------*/

extern void SoundChannelClear(void);

//  Clear all the channels of direct sound to stop sound.
//  This function may not operate properly when the library which expands the function of sound driver
//  is installed.  Do not use if such malfunction occurs.

/*------------------------------------------------------------------*/
/*                       Stop Sound DMA                             */
/*------------------------------------------------------------------*/

extern void SoundDriverVSyncOff(void);

// It is necessary to stop sound DMA by using this function when 
// SoundDriverVSync() cannot be called every 1/60 second in such cases as 
// stopping V-Blank interrupt because of main program.
// Otherwise, DMA will not stop even if buffer is over, and noise will occur.

/*------------------------------------------------------------------*/
/*                    Restart Sound DMA                             */
/*------------------------------------------------------------------*/

extern void SoundDriverVSyncOn(void);

// This is a function that restarts Sound DMA which is stopped by 
// SoundDriverVSyncOff() stated above.
// Set it so that V-Blank interrupt enters within 1/30 second after calling this 
// function and SoundDriverVSync() is called.

/*------------------------------------------------------------------*/
/*               Sound Interval Calculation with MIDI Key           */
/*------------------------------------------------------------------*/

extern u32  MidiKey2Freq(WaveData *wa, u8 mk, u8 fp);

// When producing sound with waveform data wa with sound interval (MIDI KEY) mk
// and fine control value fp, calculate a value that is substituted into 
// ((SoundArea)sa).vchn[x].fr.

/*------------------------------------------------------------------*/
/*                           Music Player Open                      */
/*------------------------------------------------------------------*/

extern void MusicPlayerOpen(MusicPlayerArea *ma, MusicPlayerTrack *ta, u8 tn);

// Open music player.
// ma is a work area, ta is a work area per track, and tn is track number 
// (maximum 16).
// By preparing ma and ta[tn] separately, it is possible to open multiple players 
// to play multiple music simultaneously.  For example, you can open one for BGM 
// and four for SE.
//  
//  * Music player functions are upper functions of sound driver functions.

/*------------------------------------------------------------------*/
/*                       Start Playing Music                        */
/*------------------------------------------------------------------*/

extern void MusicPlayerStart(MusicPlayerArea *ma, SongHeader *so);

// Play music so with music player in the work area ma.

/*------------------------------------------------------------------*/
/*                     Pause (Temporarily) Music                    */
/*------------------------------------------------------------------*/

extern void MusicPlayerStop(MusicPlayerArea *ma);

// Pause music that is played with music player of the work area ma.

/*------------------------------------------------------------------*/
/*                        Restart Music                             */
/*------------------------------------------------------------------*/

extern void MusicPlayerContinue(MusicPlayerArea *ma);

// Restart music that was paused with music player of the work area ma.

/*------------------------------------------------------------------*/
/*                           Fade out Music                         */
/*------------------------------------------------------------------*/

extern void MusicPlayerFadeOut(MusicPlayerArea *ma, u16 sp);

// Fade out the music playing in the work area ma with speed sp and pause.


/*------------------------------------------------------------------*/
/*                      Multi-play Boot                             */
/*------------------------------------------------------------------*/

extern int MultiBoot(MultiBootParam *mp);

// Main process for server of multi-play boot.
// You must have a set procedure in advance for recognition among all the 
// connected AGB client terminals.


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* _AGB_SYSTEM_CALL_H */
