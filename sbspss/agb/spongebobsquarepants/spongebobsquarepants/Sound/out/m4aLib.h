//------------------------------------------------------------//
//             mks4agbLib.h ( m4aLib.h ) ver1.05              //
//                                                            //
//          Copyright (C) 1999-2001 NINTENDO Co.,Ltd.         //
//------------------------------------------------------------//

#ifndef _M4A_LIB_H
#define _M4A_LIB_H

#define _M4A_LIB_VER 105

#include <AgbSound.h>


//Structure of CGB Virtual Channel
typedef struct {
    u8 ch1[64];
    u8 ch2[64];
    u8 ch3[64];
    u8 ch4[64];
} CgbChannels;

//Structure of Music Player Table
typedef struct {
    MusicPlayerArea *ma;
    MusicPlayerTrack *ta;
    u32 tn;
} MPlayTable;

//Structure of Song Table
typedef struct {
    SongHeader *so;
    u16 ms, me;
} SongTable;


#define CGB1_P12 ((WaveData *)0)
#define CGB1_P25 ((WaveData *)1)
#define CGB1_P50 ((WaveData *)2)
#define CGB1_P75 ((WaveData *)3)
#define CGB2_P12 CGB1_P12
#define CGB2_P25 CGB1_P25
#define CGB2_P50 CGB1_P50
#define CGB2_P75 CGB1_P75
#define CGB4_C15 ((WaveData *)0)
#define CGB4_C07 ((WaveData *)1)


extern const u8 __sound_mode_i[];
#define sound_mode_i ((u32)__sound_mode_i)
extern const u8 __total_mplay_n[];
#define total_mplay_n ((u16)__total_mplay_n)
extern const u8 __total_song_n[];
#define total_song_n ((u16)__total_song_n)

extern SoundArea m4a_sound;
extern const MPlayTable mplay_table[];
extern const SongTable song_table[];
extern u8 m4a_memacc_area[];


extern void m4aSoundInit(void);

#define m4aSoundMode(P1) SoundMode_rev01(P1)
extern void SoundMode_rev01(u32 mode);

extern void m4aSoundMain(void);

#define m4aSoundVSync() SoundVSync_rev01()
extern void SoundVSync_rev01(void);

#define m4aSoundVSyncOff() SoundVSyncOff_rev01()
extern void SoundVSyncOff_rev01(void);

#define m4aSoundVSyncOn() SoundVSyncOn_rev01()
extern void SoundVSyncOn_rev01(void);

#define m4aMPlayStart(P1,P2) MPlayStart_rev01(P1,P2)
extern void MPlayStart_rev01(MusicPlayerArea *ma, SongHeader *so);

extern void m4aSongNumStart(u16 n);

extern void m4aSongNumStartOrChange(u16 n);

extern void m4aSongNumStartOrContinue(u16 n);

extern void m4aMPlayImmInit(MusicPlayerArea *ma);

#define m4aMPlayStop(P1) MPlayStop_rev01(P1)
extern void MPlayStop_rev01(MusicPlayerArea *ma);

extern void m4aSongNumStop(u16 n);

extern void m4aMPlayAllStop(void);

extern void m4aMPlayContinue(MusicPlayerArea *ma);

extern void m4aSongNumContinue(u16 n);

extern void m4aMPlayAllContinue(void);

extern void m4aMPlayFadeOut(MusicPlayerArea *ma, u16 sp);

#define m4aMPlayTempoControl(P1,P2) MPlayTempoControl(P1,P2)
extern void MPlayTempoControl(MusicPlayerArea *ma, u16 te);

#define m4aMPlayVolumeControl(P1,P2,P3) MPlayVolumeControl(P1,P2,P3)
extern void MPlayVolumeControl(MusicPlayerArea *ma, u16 tb, u16 vo);

#define m4aMPlayPitchControl(P1,P2,P3) MPlayPitchControl(P1,P2,P3)
extern void MPlayPitchControl(MusicPlayerArea *ma, u16 tb, s16 pi);

#define m4aMPlayPampotControl(P1,P2,P3) MPlayPanpotControl(P1,P2,P3)
#define m4aMPlayPanpotControl(P1,P2,P3) MPlayPanpotControl(P1,P2,P3)
extern void MPlayPanpotControl(MusicPlayerArea *ma, u16 tb, s8 pa);

#define m4aMPlayModDepthSet(P1,P2,P3) MPlayModDepthSet(P1,P2,P3)
extern void MPlayModDepthSet(MusicPlayerArea *ma, u16 tb, u8 md);

#define m4aMPlayLFOSpeedSet(P1,P2,P3) MPlayLFOSpeedSet(P1,P2,P3)
extern void MPlayLFOSpeedSet(MusicPlayerArea *ma, u16 tb, u8 ls);


#endif // _M4A_LIB_H

// MusicPlayers
extern MusicPlayerArea m4a_mplay000;
extern MusicPlayerArea m4a_mplay001;

// Song files
extern SongHeader ch1_1_2;
extern SongHeader ch1_3;
extern SongHeader ch1_4;
extern SongHeader ch1_b;
extern SongHeader ch2_1_3;
extern SongHeader ch2_2;
extern SongHeader ch2_4;
extern SongHeader ch2_b;
extern SongHeader ch3_1;
extern SongHeader ch3_2_3;
extern SongHeader ch3_4;
extern SongHeader ch3_b1;
extern SongHeader ch3_b2;
extern SongHeader ch4_1;
extern SongHeader ch4_2_4;
extern SongHeader ch4_3;
extern SongHeader ch4_b;
extern SongHeader ch5_1_3;
extern SongHeader ch5_2;
extern SongHeader ch5_4;
extern SongHeader ch5_b;
extern SongHeader ch6_b_t;
extern SongHeader ch6_g;
extern SongHeader ch6_r_s;
extern SongHeader ch6_top;
extern SongHeader gameover;
extern SongHeader options;
extern SongHeader titlemusic;
extern SongHeader zfx00;
extern SongHeader zfx01;
extern SongHeader zfx02;
extern SongHeader zfx03;
extern SongHeader zfx04;
extern SongHeader zfx05;
extern SongHeader zfx06;
extern SongHeader zfx07;
extern SongHeader zfx08;
extern SongHeader zfx09;
extern SongHeader zfx10;
extern SongHeader zfx11;
extern SongHeader zfx12;
extern SongHeader zfx13;
extern SongHeader zfx14;
extern SongHeader zfx15;
extern SongHeader zfx16;
extern SongHeader zfx17;
extern SongHeader zfx18;
extern SongHeader zfx19;
extern SongHeader zfx20;
extern SongHeader zfx21;
extern SongHeader zfx22;
extern SongHeader zfx23;
extern SongHeader zfx24;
extern SongHeader zfx25;
extern SongHeader zfx26;
extern SongHeader zfx27;
extern SongHeader zfx28;
extern SongHeader zfx29;
extern SongHeader zfx30;
extern SongHeader zfx31;
extern SongHeader zfx32;
extern SongHeader zfx33;
extern SongHeader zfx34;
extern SongHeader zfx35;
extern SongHeader zfx36;
extern SongHeader zfx37;
extern SongHeader zfx38;
extern SongHeader zfx39;
extern SongHeader zfx40;
extern SongHeader zfx41;
extern SongHeader zfx42;
extern SongHeader zfx43;
extern SongHeader zfx44;
extern SongHeader zfx45;
extern SongHeader zfx46;
extern SongHeader zfx47;
extern SongHeader zfx48;
extern SongHeader zfx49;
extern SongHeader zfx50;
extern SongHeader zfx51;
extern SongHeader zfx52;
extern SongHeader zfx53;
extern SongHeader zfx54;
extern SongHeader zfx55;
extern SongHeader zfx56;
extern SongHeader zfx57;
extern SongHeader zfx58;
extern SongHeader zfx59;
extern SongHeader zfx60;
extern SongHeader zfx61;
extern SongHeader zfx62;
extern SongHeader zfx63;
extern SongHeader zfx64;
extern SongHeader zfx65;
extern SongHeader zfx66;
extern SongHeader zfx67;
extern SongHeader zfx68;
extern SongHeader zfx69;
extern SongHeader zfx70;
extern SongHeader zfx71;
extern SongHeader zfx72;
extern SongHeader zfx73;
extern SongHeader zfx74;
extern SongHeader zfx75;
extern SongHeader zfx76;
extern SongHeader zfx77;
extern SongHeader zfx78;
extern SongHeader zfx79;
extern SongHeader zfx80;
extern SongHeader zfx81;
extern SongHeader zfx82;
extern SongHeader zfx83;
extern SongHeader zfx84;
extern SongHeader zfx85;
extern SongHeader zfx86;
extern SongHeader zfx87;
extern SongHeader zfx88;
extern SongHeader zfx89;
extern SongHeader zfx90;
extern SongHeader zfx91;
