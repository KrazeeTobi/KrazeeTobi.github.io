;********************************************************************
;*          AgbSyscallDefineArm.s                                   *
;*            AGB System Call  (ARMASM)                          *
;*                                                                  *
;*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               *
;********************************************************************


;--------------------------------------------------------------------
;-                   System Call No.                             -
;--------------------------------------------------------------------

SWI_NO_RESTART                  *   0       ; SoftReset()
SWI_NO_REGISTER_RAM_RESET       *   1       ; SoftReset()/RegisterRamReset()
SWI_NO_HALT                     *   2       ; Halt()
SWI_NO_STOP                     *   3       ; Stop()

SWI_NO_INTR_WAIT                *   4       ; IntrWait()
SWI_NO_VBLANK_INTR_WAIT         *   5       ; VBlankIntrWait()

SWI_NO_DIV                      *   6       ; Div()/DivRem()
SWI_NO_DIV_ARM                  *   7       ; DivArm()/DivRemArm()
SWI_NO_SQRT                     *   8       ; Sqrt()
SWI_NO_ARCTAN                   *   9       ; ArcTan()
SWI_NO_ARCTAN2                  *   10      ; ArcTan2()

SWI_NO_CPU_SET                  *   11      ; CpuSet()
SWI_NO_CPU_FAST_SET             *   12      ; CpuFastSet()
SWI_NO_BG_AFFINE_SET            *   14      ; BgAffineSet()
SWI_NO_OBJ_AFFINE_SET           *   15      ; ObjAffineSet()
SWI_NO_BIT_UNPACK               *   16      ; BitUnPack()
SWI_NO_LZ77_UNCOMP_WRAM         *   17      ; LZ77UnCompWram()
SWI_NO_LZ77_UNCOMP_VRAM         *   18      ; LZ77UnCompVram()
SWI_NO_HUFF_UNCOMP              *   19      ; HuffUnComp()
SWI_NO_RL_UNCOMP_WRAM           *   20      ; RLUnCompWram()
SWI_NO_RL_UNCOMP_VRAM           *   21      ; RLUnCompVram()
SWI_NO_DIFF_8BIT_UNFILTER_WRAM  *   22      ; Diff8bitUnFilterWram()
SWI_NO_DIFF_8BIT_UNFILTER_VRAM  *   23      ; Diff8bitUnFilterVram()
SWI_NO_DIFF_16BIT_UNFILTER      *   24      ; Diff16bitUnFilter()

SWI_NO_SOUND_BIAS_CHANGE        *   25      ; SoundBiasSet()/SoundBiasReset()
SWI_NO_SOUND_DRIVER_INIT        *   26      ; SoundDriverInit()
SWI_NO_SOUND_DRIVER_MODE        *   27      ; SoundDriverMode()
SWI_NO_SOUND_DRIVER_MAIN        *   28      ; SoundDriverMain()
SWI_NO_SOUND_DRIVER_VSYNC       *   29      ; SoundDriverVSync()
SWI_NO_SOUND_DRIVER_VSYNC_OFF   *   40      ; SoundDriverVSyncOff()
SWI_NO_SOUND_DRIVER_VSYNC_ON    *   41      ; SoundDriverVSyncOn()
SWI_NO_SOUND_CHANNEL_CLEAR      *   30      ; SoundChannelClear()
SWI_NO_MIDI_KEY_2_FREQ          *   31      ; MidiKey2Freq()
SWI_NO_MUSIC_PLAYER_OPEN        *   32      ; MusicPlayerOpen()
SWI_NO_MUSIC_PLAYER_START       *   33      ; MusicPlayerStart()
SWI_NO_MUSIC_PLAYER_STOP        *   34      ; MusicPlayerStop()
SWI_NO_MUSIC_PLAYER_CONTINUE    *   35      ; MusicPlayerContinue()
SWI_NO_MUSIC_PLAYER_FADEOUT     *   36      ; MusicPlayerFadeOut()

SWI_NO_MULTI_BOOT               *   37      ; MultiBoot()


;--------------------------------------------------------------------
;-                   Reset Software                                -
;--------------------------------------------------------------------

    EXTERN SoftReset

; * Set the register and RAM that were specified by ResetFlags and return to address 0x8000000.
; * Clear CPU core register and the area 0x3007e00~0x3007fff of CPU internal RAM forcefully.
;
; * Arguments: 
;    r0:                  Specify the register and RAM that are to be reset  (See AgbDefineArm.s for reference) 

;--------------------------------------------------------------------
;-               Reset Register & RAM                          -
;--------------------------------------------------------------------

    EXTERN RegisterRamReset

; * Reset the register and RAM that were specified by ResetFlags.
; * However, it does not clear the area 0x3007e00~0x3007fff of CPU internal RAM.
;
; * Arguments: 
;    r0:                  Specify the register and RAM that are to be reset  (See AgbDefineArm.s for reference) 

;--------------------------------------------------------------------
;-                   HALT                                       -
;--------------------------------------------------------------------

;   EXTERN Halt

; * Halts CPU only.
; * Applicable interrupt is enabled (set to IE).
;  Return by interrupt request (set to IF).

;--------------------------------------------------------------------
;-                   STOP                                       -
;--------------------------------------------------------------------

    EXTERN SoundBiasSet
    EXTERN SoundBiasReset

;   EXTERN Stop

; * Stop source oscillation.
; * When applicable interrupt is enabled (set to IE), return when interrupt request condition
;  from key, game pak or SIO generates.
; * Since source oscillation is stopped, it does not set IF flag.
; * LCDC must be OFF when executed.

;--------------------------------------------------------------------
;-               Interrupt Wait                                   -
;--------------------------------------------------------------------

    EXTERN IntrWait

; * Continue to wait in the Halt status until the interrupt specified by IntrFlags generates.
; * Set applicable flags to INTR_CHECK_BUF(0x3007ff8) by processing interrupts.
; * By using multiple interrupts simultaneously,  overhead that calls for system call can be reduced
;  compared with when Halt() is called back repeatedly.
;
; * Arguments: 
;    r0:                 Specify whether or not to clear when applicable flags have already been set.
;    r1:                 specify the interrupts that wait. (See AgbDefineArm.s for reference) 

;--------------------------------------------------------------------
;-               V-blank Interrupt Wait                         -
;--------------------------------------------------------------------

    EXTERN VBlankIntrWait

; * Continue to wait in the Halt status until V-blank interrupt generates.
; * Set applicable flags to INTR_CHECK_BUF(0x3007ff8) by processing interrupts.
; * By using multiple interrupts simultaneously, overhead that calls for system call can be reduced
;  compared with when Halt() is called back repeatedly.
; * It is equivalent to IntrWait(1, V_BLANK_INTR_FLAG).

;--------------------------------------------------------------------
;-                   Devision with codes (Quontient)                           -
;--------------------------------------------------------------------

    EXTERN Div                 ; Compatible with the library by RedHat (Formerly Cygnus)
    EXTERN DivArm              ; Compatible with the library by ARM

; * Calculate Number/Denom.
; * The register value returns by r0=Number/Denom, r1=Number%Denom and 
;  r3=|Number/Denom|.
;
; * Arguments:  (Reversal for the library by ARM) 
;    r0:                 Numerator
;    r1:                 Denominator

;--------------------------------------------------------------------
;-                   Devision with codes (Remainder)                         -
;--------------------------------------------------------------------

    EXTERN DivRem              ; Compatible with the library by RedHat (Formerly Cygnus)
    EXTERN DivRemArm           ; Compatible with the library by ARM

; * Calculate Number%Denom.
; * The register value returns by r0=Number%Denom, r1=Number%Denom and
;  r3=|Number/Denom|.
;
; * Arguments:  (Reversal for the library by ARM) 
;    r0:                 Numerator
;    r1:                 Denominator

;--------------------------------------------------------------------
;-                   Square Root                                         -
;--------------------------------------------------------------------

    EXTERN Sqrt

; * Calculate square root.
; * In order to make it accurate, shift argumentX by the multiple of 2 to the 
;  left, and shift return value to the right by the multiplied number used to 
;  match digit.

;--------------------------------------------------------------------
;-                   Arc Tangent                                         -
;--------------------------------------------------------------------

    EXTERN ArcTan

; * Calculate arc tangent value.
; * For return value, return -pi/2ƒƒÆƒpi/2 in the range of 0xc000~0x4000.
; * However, the area ƒÆƒ-pi/4,pi/4ƒƒÆ has a problem with accuracy.
;
; * Arguments: 
;    r0:
;        Code:1
;        Integer part:1
;        Decimal part:14

;--------------------------------------------------------------------
;-                   Arc Tangent 2                                       -
;--------------------------------------------------------------------

    EXTERN ArcTan2

; * Calculate the arc tangent value after correction process.
; * Use this for regular purpose.
; * For return value, return 0…ƒÆƒ2pi in the range of 0~0xffff.
;
; * Arguments: 
;    r0, r1:
;        Code:1
;        Integer part:1
;        Decimal part:14

;--------------------------------------------------------------------
;-                   Set CPU                                   -
;--------------------------------------------------------------------

    EXTERN CpuSet

; * Clear or copy RAM by a parameter which is compatible with DmaSet macro.
; * At 32-bit transfer, RAM is accessed forcefully by 4 byte boundary, and 
;  at 16-bit transfer, it is necessary to set arguments by 2 byte boundary 
;  to access RAM.
;
; * Arguments: 
;    r0:                 Source address
;    r1:                 Destination address
;    r2:                 Only DMA_SRC_FIX/DMA_32BIT_BUS/DMA_COUNT_MASK is valid.
;          DMA_SRC_FIX(  0, 1) = (Source address increment, Source address fixed)
;          DMA_32BIT_BUS(0, 1) = (16-bit transfer, 32-bit transfer)
;          DMA_COUNT_MASK & DmaCntData = Number of times transferred
;
; * Upper macro: 
;  CpuClear, CpuArrayClear, CpuCopy, CpuArrayCopy

;--------------------------------------------------------------------
;-                   High Speed Set CPU                               -
;--------------------------------------------------------------------

    EXTERN CpuFastSet

; * Clear or copy RAM in high speed by a parameter that is compatible
;  with DmaSet macro.
; * However, it is a 32-bit transfer by 32 bytes (8 words).
; * Even if arguments other than 4 byte boundary are given, RAM is accessed by 4 byte boundary forcefully.

; * Arguments: 
;    r0:                 Source address
;    r1:                 Destination address
;    r2:                 Only DMA_SRC_FIX/DMA_COUNT_MASK is valid
;          DMA_SRC_FIX(0, 1) = (Source address increment, Source address fixed)
;          DMA_COUNT_MASK & DmaCntData = Number of times transferred
;
; * Upper macro: 
;  CpuFastClear, CpuFastArrayClear, CpuFastCopy, CpuFastArrayCopy

;--------------------------------------------------------------------
;-                   Set BG Affine Transformation                        -
;--------------------------------------------------------------------

    EXTERN BgAffineSet

; * Calculate and set affine parameter of BG.
;
; * Arguments: 
;    r0:                       Source address
;    r1:                       Destination address
;    r2:                       Number of times calculated
;
; * BgAffineSrcData Structure
;    s32 SrcCenterX            Source data center coordinate (8 bits to the right of the decimal point)
;    s32 SrcCenterY
;    s16 DispCenterX           Display center coordinate
;    s16 DispCenterY
;    s16 RatioX                Scaling ratio (8 bits to the right of the decimal point) 
;    s16 RatioY
;    u16 Theta                 Rotation angle (8 bits to the right of the decimal point) 
;                                  Valid range    0 - 0xffff
; * BgAffineDestData Structure
;    s16 H_DiffX               Line direction X coordinate difference
;    s16 V_DiffX                 Vertical direction X coordinate difference
;    s16 H_DiffY               Line direction Y coordinate difference
;    s16 V_DiffY                 Vertical direction Y coordinate difference
;    s32 StartX                Start X coordinate
;    s32 StartY                Start Y coordinate

;--------------------------------------------------------------------
;-                   Set OBJ Affine Transformation                      -
;--------------------------------------------------------------------

    EXTERN ObjAffineSet

; * Calculate and set affine parameter of OBJ.
;
; * Arguments: 
;    r0:                       Source address
;    r1:                       Destination address
;    r2:                       Number of times calculated
;    r3:                       Offset byte number of parameter address (Normally 2|8) 
;                              Specify "8" if setting directly to OAM.
;
; * ObjAffineSrcData Structure
;    s16 RatioX                Scaling ratio (8 bits to the right of the decimal point) 
;    s16 RatioY
;    u16 Theta                 Rotation angle (8 bits to the right of the decimal point) 
;                                  Valid range    0 - 0xffff
; * ObjAffineDestData Structure
;    s16 H_DiffX               Line direction X coordinate difference
;    s16 V_DiffX                 Vertical direction X coordinate difference
;    s16 H_DiffY               Line direction Y coordinate difference
;    s16 V_DiffY                 Vertical direction Y coordinate difference

;--------------------------------------------------------------------
;-                       Expand Bit Compressed Data                         -
;--------------------------------------------------------------------

    EXTERN BitUnPack

; * Expand the data filled with bit that is fixed to 0.
; * Match destination address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;    r2:                     Address of BitUnPackParam structure data
;
; * BitUnPackParam Structure
;    u16 SrcNum              Source data byte number
;    u8  SrcBitNum           1 source data bit number
;    u8  DestBitNum          1 destination data bit number
;    u32 DestOffset:31       Offset number that is added to source data
;        DestOffset0_On:1    Flag whether or not to add offset to the data 0.

;--------------------------------------------------------------------
;-                   Expand LZ77 Compressed Data (-> Work RAM)        -
;--------------------------------------------------------------------

    EXTERN LZ77UnCompWram

; * Expand LZ77 compressed data and write by 8 bits.
; * Cannot expand directly to VRAM.
; * When compressed data size is not a multiple of 4, fill with 0 to adjust.
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 :4                  Reserve
;        CompType:4          Compressed type ( = 1) 
;        DestSize:24         Post-expansion data size
;
; * Flag data format
;    u8  Flags               Compressed/Non-compressed flag
;                             (0, 1)  =  (Non-compressed data, Compressed data) 
; * Code data format (Big Endian) 
;    u16 Length:4            Expansion data length - 3 (Compress only when matching length is 3 bytes or more.) 
;        Offset:12           Matching data offset - 1

;--------------------------------------------------------------------
;-                   Expand LZ77 Compressed Data (-> VRAM)           -
;--------------------------------------------------------------------

    EXTERN LZ77UnCompVram

; * Expand LZ77 compressed data and write by 16 bits.
; * Can expand to work RAM, but it is slower than LZ77UnCompWram().
; * Specify the compressed data in which matching character array was retrieved by 2 bytes before.
; * When compressed data size is not a multiple of 4, fill with 0 to adjust.
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 :4                  Reserve
;        CompType:4          Compressed type ( = 1) 
;        DestSize:24         Post-expansion data size
;
; * Flag data format
;    u8  Flags               Compressed/Non-compressed flag
;                             (0, 1)  =  (Non-compressed data, Compressed data) 
; * Code data format (Big Endian) 
;    u16 Length:4            Expansion data length - 3 (Compress only when matching length is 3 bytes or more.) 
;        Offset:12           Matching data offset ( >= 2)  - 1

;--------------------------------------------------------------------
;-                   Expand Huffman Compressed Data                 -
;--------------------------------------------------------------------

    EXTERN HuffUnComp

; * Expand Huffman compressed data and write by 32 bits.
; * When compressed data size is not a multiple of 4, fill with 0 to adjust.
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 BitSize:4           1 data bit size (Normally 4|8) 
;        CompType:4          Compressed type ( = 2) 
;        DestSize:24         Post-expansion data size
;
; * Tree table
;    u8           TreeSize        Tree table size/2 - 1
;    TreeNodeData RootNode        Root node
;
;    TreeNodeData LeftNode        Root left node
;    TreeNodeData RightNode       Root right node
;
;    TreeNodeData LeftleftNode    Left left node
;    TreeNodeData leftRightNode   Left right node
;
;    TreeNodeData RightLeftNode   Right left node
;    TreeNodeData RightRightNode  Right right node
;
;             * 
;             * 
;
;  Compressed data main unit after this
;
; * TreeNodeData Structure
;    u8  NextNodeOffset:6    Offset to the next node data - 1 (2 bytes unit) 
;        RightEndFlag:1      Right node end flag
;        LeftEndFlag:1       Left node end flag
;                            When end flag is set, data is in the next node.

;--------------------------------------------------------------------
;-                   Expand Run Length Compressed Data (-> Work RAM)   -
;--------------------------------------------------------------------

    EXTERN RLUnCompWram

; * Expand run length compressed data and write by 8 bits.
; * Cannot expand directly to VRAM.
; * When compressed data size is not a multiple of 4, fill with 0 to adjust.
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 :4                  Reserve
;        CompType:4          Compressed type ( = 3) 
;        DestSize:24         Post-expansion data size
;
; * Flag data format
;    u8  Length:7            Expansion data length - 1 (When not compressed) 
;                            Expansion data length - 3 (Compress only when consecutive length is 3 bytes or more)
;        Flag:1               (0, 1)  =  (Non-compressed data, Compressed data) 

;--------------------------------------------------------------------
;-                   Expand Run Length Compressed Data (-> VRAM)    -
;--------------------------------------------------------------------

    EXTERN RLUnCompVram

; * Expand run length compressed data and write by 16 bytes.
; * Can expand to work RAM, it is slower than RLUnCompWram().
; * When compressed data size is not a multiple of 4, fill with 0 to adjust.
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header			
;    u32 :4                  Reserve
;        CompType:4          Compressed type ( = 3) 
;        DestSize:24         Post-expansion data size
;
; * Flag data format
;    u8  Length:7            Expansion data length - 1 (When not compressed) 
;                            Expansion data length - 3 (Compress only when consecutive length is 3 bytes or more.)
;        Flag:1               (0, 1)  =  (Non-compressed data, Compressed data)

;--------------------------------------------------------------------
;-                   Expand difference filter (8 bits -> Work RAM)  -
;--------------------------------------------------------------------

    EXTERN Diff8bitUnFilterWram

; * Expand 8-bit difference filter manipulation data and write by 8 bits.
; * Cannot expand directly to VRAM.
; * Match source address to 4 byte boundary.
;
; * Argumetns: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 ByteSize:4          1 data byte size ( = 1) 
;        FiltType:4          Filter type ( = 8) 
;        DestSize:24         Post-expansion data size
;
; * Data format
;    u8  Origin              Source data
;    u8  Diff                Difference data
;          * 
;          * 

;--------------------------------------------------------------------
;-                   Expand difference filter (8 bits -> VRAM)      -
;--------------------------------------------------------------------

    EXTERN Diff8bitUnFilterVram

; * Expand 8-bit difference filter manipulation data and write by 16 bits.
; * Can expand to work RAM, but it is slower than Diff8bitUnFilterVram().
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 ByteSize:4          1 data byte size ( = 1) 
;        FilterType:4        Filter type ( = 8) 
;        DestSize:24         Post-expansion data size
;
; * Data format
;    u8  Origin              Source data
;    u8  Diff                Difference data
;          * 
;          * 

;--------------------------------------------------------------------
;-                   Expand difference filter (16 bits)                       -
;--------------------------------------------------------------------

    EXTERN Diff16bitUnFilter

; * Expand 16-bit difference filter manipulation data and write by 16 bits.
; * Match source address to 4 byte boundary.
;
; * Arguments: 
;    r0:                     Source address
;    r1:                     Destination address
;
; * Data header
;    u32 ByteSize:4          1 data byte size ( = 2) 
;        FilterType:4        Filter type ( = 8) 
;        DestSize:24         Post-expansion data size
;
; * Data format
;    u16 Origin              Source data
;    u16 Diff                Difference data
;          * 
;          * 

;--------------------------------------------------------------------
;-              Set Sound BIAS                             -
;--------------------------------------------------------------------

    EXTERN SoundBiasSet

; * Move sound BIAS from 0 to intermediate value (0x200) .

;--------------------------------------------------------------------
;-              Reset sound BIAS                           -
;--------------------------------------------------------------------

    EXTERN SoundBiasReset

; * Move sound BIAS from intermediate value (0x200) to 0.

;--------------------------------------------------------------------
;-              Initialize sound driver                             -
;--------------------------------------------------------------------

    EXTERN SoundDriverInit

;  Initialize sound driver.
;  Call just once when game starts.
;  At that time, it is necessary to obtain the work area "sa" in advance.
;  Even if work area is prepared separately, the main driver cannot be executed ;  multiple times simultaneously.

;--------------------------------------------------------------------
;-              Sound Driver Move Mode                         -
;--------------------------------------------------------------------

    EXTERN SoundDriverMode

;  Set the move mode of sound driver.
;  
;  | Reverb of direct sound (Initial value 0)
;      mode = SOUND_MODE_REVERB_SET + (Reverb value 0~127);
;  
;  | Simultaneous sound number of direct sound (Initial value 8)
;      mode = (Simultaneous sound number 1~12) << SOUND_MODE_MAXCHN_SHIFT;
;  
;  | Master volume of direct sound (Initial value 15)
;      mode = (Volume 1~15) << SOUND_MODE_MASVOL_SHIFT;
;  
;  | Play frequency of direct sound (Initial value 13379Hz)
;      mode = SOUND_MODE_FREQ_?????;
;             (up) the value defined in AgbSound.h (12 types).
;  
;  | Bit number of final D/A converter (Initial value 8 bits)
;      mode = SOUND_MODE_DA_BIT_?;
;                            (up) 9~6
;  
;  | The values above can be set simultaneously by conducting OR.

;--------------------------------------------------------------------
;-              Sound Driver Main                             -
;--------------------------------------------------------------------

    EXTERN SoundDriverMain

;  Main of sound driver.
;  Call every 1/60 second.  The process flow is to call SoundDriverVSync(), 
;  described later, immediately after V-blank interrupt, then to call main 
;  routine after processing BG and OBJ.
;  
;--------------------------------------------------------------------
;-              Reset Sound Driver DMA                     -
;--------------------------------------------------------------------

    EXTERN SoundDriverVSync

;  A very short system call that resets sound DMA.
;  Since the timing is very severe, call IMMEDIATELY AFTER V-blank interrupt 
;  of every 1/60 second is entered.

;--------------------------------------------------------------------
;-              Clear Sound Channel                           -
;--------------------------------------------------------------------

    EXTERN SoundChannelClear

;  Clear all the channels of direct sound and stop sound.
;  This function may not operate properly when the library that expands the 
;  feature of sound driver is installed. Do not use if such malfunction occurs.

;--------------------------------------------------------------------
;-                 Pause Sound DMA                             -
;--------------------------------------------------------------------

    EXTERN SoundDriverVSyncOff

;  When SoundDriverVSync() cannot be called every 1/60 second because V-blank 
;  interrupt is paused due to the status of the main program, etc., it is 
;  necessary to pause sound DMA by using this function.
;  Otherwise, DMA will not stop even when it goes over the buffer, which causes ;  terrible noise.

;--------------------------------------------------------------------
;-                 Re-open Sound DMA                             -
;--------------------------------------------------------------------

    EXTERN SoundDriverVSyncOn

;  This is a function that re-opens the sound DMA that was paused by 
;  SoundDriverVSyncOff(), which was described above.  Set it so that V-blank 
;  interrupt is entered and SoundDriverVSync() is called within 2/60 seconds
;  after this function is called.

;--------------------------------------------------------------------
;-               Calculate Interval by MIDI Key                     -
;--------------------------------------------------------------------

    EXTERN MidiKey2Freq

;  When the waveform "wa" is played by the interval (MIDI KEY) mk or fine adjustment value fp, calculate the value that is assigned to ((SoundArea)sa).vchn[x].fr.

;--------------------------------------------------------------------
;-            Open Music Player                      -
;--------------------------------------------------------------------

    EXTERN MusicPlayerOpen

;  Open music player.
;  "ma" is a work area, "ta" is a work area by track, and "tn" is the number of tracks (Maximum 16).
;  If "ma" and "ta[tn]" are prepared separately, multiple players can be opened, which enables multiple songs to be played simultaneously.  For example, it is possible to use one music player for BGM and four music players for SE.
;  
;  * Music player function group is the upper functions of sound driver function group.

;--------------------------------------------------------------------
;-                       Start Playing Songs                             -
;--------------------------------------------------------------------

    EXTERN MusicPlayerStart

;  Play the song "so" by using the music player of the work area "ma".

;--------------------------------------------------------------------
;-                     Pause the song that is currently played      -
;--------------------------------------------------------------------

    EXTERN MusicPlayerStop

;  Pause the music that is currently played on the music player of the work area "ma".

;--------------------------------------------------------------------
;-                        Restart the song that is currently paused -
;--------------------------------------------------------------------

    EXTERN MusicPlayerContinue

;  Restart the song that was paused on the music player of the work area "ma".
\
;--------------------------------------------------------------------
;-                       Fade out songs                         -
;--------------------------------------------------------------------

    EXTERN MusicPlayerFadeOut

;  Fade out the song that is played in the work area "ma" by the speed "sp" and stop.


;--------------------------------------------------------------------
;-                   Multi-play Boot                             -
;--------------------------------------------------------------------

    EXTERN MultiBoot

; * Main process for the server of multi-play boot.
; * The specific recognition process must be done between all the connected
;  client AGBs.


