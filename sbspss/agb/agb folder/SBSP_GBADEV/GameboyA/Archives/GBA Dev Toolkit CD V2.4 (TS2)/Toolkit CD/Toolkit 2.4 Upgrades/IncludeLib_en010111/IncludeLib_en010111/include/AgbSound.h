/********************************************************************/
/*          AgbSound.h                                              */
/*            AGB Standard Sound Driver Declaration                 */
/*                                                                  */
/*          Copyright (C) 1999-2000 Nintendo of America Inc.        */
/*          Programed by SMASH Co.,Ltd.                             */
/********************************************************************/
#ifndef _AGB_SOUND_H
#define _AGB_SOUND_H

#ifdef __cplusplus
extern "C" {
#endif


#include <AgbTypes.h>


//Waveform Data Structure
typedef struct {
    u16 type;   //Type
    u16 stat;   //Status
    u32 freq;   //Frequency Calculation Value
    u32 loop;   //Loop Start Point
    u32 size;   //Sampling Number
    s8 data[1]; //Sampling Data Order
} WaveData;

#define WAVE_STAT_LOOP  0xc000


//Sound Quality Data Structure
typedef struct {
    u8 typ;         //Type
    u8 key;         //Original Key
    u8 len;         //Sound Length (Compatible Sound)
    u8 p_s;         //Pan or Sweep (Compatible Sound 1)
    WaveData *wav;  //Wave Data Address
    u8 att;         //Attack
    u8 dec;         //Decay
    u8 sus;         //Sustain
    u8 rel;         //Release
} ToneData;

#define TONEDATA_TYP_RHY    0x80
#define TONEDATA_TYP_SPL    0x40
#define TONEDATA_TYP_FIX    0x08
#define TONEDATA_TYP_CGB    0x07

#define TONEDATA_P_S_PAN    0xc0
#define TONEDATA_P_S_PAM    TONEDATA_P_S_PAN

typedef struct { u32 typ; ToneData *ta; u8 *st; } SplitTone;
typedef union { ToneData t; SplitTone s; } ToneDataArr;

#define RHYTHM_TONE(TA)     {TONEDATA_TYP_RHY,0,0,0,(WaveData *)(TA)}
#define SPLIT_TONE(TA,ST)   (ToneDataArr)(SplitTone)\
                {TONEDATA_TYP_SPL, (ToneData *)(TA), (u8 *)(ST)}
#define RHY_SPL_TONE(TA,ST) (ToneDataArr)(SplitTone)\
                {TONEDATA_TYP_RHY|TONEDATA_TYP_SPL, (ToneData *)(TA), (u8 *)(ST)}


//Virtual Channel Structure
typedef struct {
    u8 sf;          //Status
    u8 ty;          //Type
    u8 rv;          //Right Volume
    u8 lv;          //Left Volume
    u8 at;          //Attack
    u8 de;          //Decay
    u8 su;          //Sustain
    u8 re;          //Release
    u8 r1[24];      // (reserved)
    u32 fr;         //Frequency Calculation Value
    WaveData *wp;   //Wave Pointer
    u32 r3[6];      // (reserved)
} SoundChannel;

#define MAX_DIRECTSOUND_CHANNEL 12
#define SOUND_CHANNEL_SF_START  0x80
#define SOUND_CHANNEL_SF_STOP   0x40
#define SOUND_CHANNEL_SF_LOOP   0x10
#define SOUND_CHANNEL_SF_IEC    0x04
#define SOUND_CHANNEL_SF_ENV    0x03
#define SOUND_CHANNEL_SF_ON     (SOUND_CHANNEL_SF_START|SOUND_CHANNEL_SF_STOP\
                                |SOUND_CHANNEL_SF_IEC|SOUND_CHANNEL_SF_ENV)

#define SOUND_CHANNEL_TY_FIX    TONEDATA_TYP_FIX
#define SOUND_CHANNEL_TY_CGB    TONEDATA_TYP_CGB


//Size of Direct Sound Transmission Buffer
#define PCM_DMA_BUF 1584


//Sound Work Area Structure
typedef struct {
    u32 r1;     // (reserved)
    vu8 DmaCount;
    u8 reverb;  //Direct Sound  Reverb Value
    u8 maxchn;  //Direct Sound  Simultaneous Sound Number
    u8 masvol;  //Direct Sound  Master Volume
    u8 freq;    //Direct Sound  Replay Frequency Number(1=5734Hz ~ 12=42048Hz)
    u8 mode;    //Sound Driver  Operation Mode
    u8 r2[6];   // (reserved)
    u32 r3[16]; // (reserved)
    SoundChannel vchn[MAX_DIRECTSOUND_CHANNEL];
    #ifndef ONLY_DMA1_SOUND
    s8 pcmbuf[PCM_DMA_BUF*2];
#else
    s8 pcmbuf[PCM_DMA_BUF];
#endif
} SoundArea;

#define SOUND_MODE_REVERB_VAL   0x0000007f
#define SOUND_MODE_REVERB_SET   0x00000080
#define SOUND_MODE_MAXCHN       0x00000f00
#define SOUND_MODE_MAXCHN_SHIFT 8
#define SOUND_MODE_MASVOL       0x0000f000
#define SOUND_MODE_MASVOL_SHIFT 12
#define SOUND_MODE_FREQ_05734   0x00010000
#define SOUND_MODE_FREQ_07884   0x00020000
#define SOUND_MODE_FREQ_10512   0x00030000
#define SOUND_MODE_FREQ_13379   0x00040000
#define SOUND_MODE_FREQ_15768   0x00050000
#define SOUND_MODE_FREQ_18157   0x00060000
#define SOUND_MODE_FREQ_21024   0x00070000
#define SOUND_MODE_FREQ_26758   0x00080000
#define SOUND_MODE_FREQ_31536   0x00090000
#define SOUND_MODE_FREQ_36314   0x000a0000
#define SOUND_MODE_FREQ_40137   0x000b0000
#define SOUND_MODE_FREQ_42048   0x000c0000
#define SOUND_MODE_FREQ_SHIFT   16
#define SOUND_MODE_DA_BIT_9     0x00800000
#define SOUND_MODE_DA_BIT_8     0x00900000
#define SOUND_MODE_DA_BIT_7     0x00a00000
#define SOUND_MODE_DA_BIT_6     0x00b00000
#define SOUND_MODE_DA_BIT_SHIFT 20


//Song Data Structure
typedef struct {
    u8 trks;            //Track Number
    u8 blks;            //Block Number
    u8 prio;            //Priority
    u8 rvrb;            //Reverb
    ToneData *tone;     //Tone Table
    u8 *part[1];
} SongHeader;


//Music Player Work Area Structure
typedef struct {
    SongHeader *song;   //Current Song Pointer
    u32 stat;           //Status
    u8 mtrk;            //Track Number
    u8 prio;            //Current Priority
    u8 d1[2];
    u32 clock;          //Calculation Clock from Performance Start
    u8 d2[48];
} MusicPlayerArea;

//Each Track Structure of Music Player
typedef struct {
    u8 d[80];
} MusicPlayerTrack;

#define MAX_MUSICPLAYER_TRACK       16
#define MUSICPLAYER_STATUS_TRACK    0x0000ffff
#define MUSICPLAYER_STATUS_PAUSE    0x80000000


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif // _AGB_SOUND_H
