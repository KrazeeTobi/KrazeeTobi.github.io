#ifndef _MUSYX_H_
#define _MUSYX_H_


typedef u32	MUSYXBool;
typedef u32 MUSYXId;


//
// System information flags
//
#define MUSYX_FLG_STANDARD			(0)			// All features on
#define MUSYX_FLG_NO_INTERPOLATION	(1<<0)		// No interpolation during resampling.
#define MUSYX_FLG_MONAURAL			(1<<1)		// Mono mixing only. Implies mono delay buffer if delay enabled.
#define MUSYX_FLG_MONO_DELAY_BUFFER	(1<<2)		// Mono delay buffer even in stereo mode
#define MUSYX_FLG_NO_RAM_CODE		(1<<3)		// Leave time critical mixing code in ROM (bad idea)
#define MUSYX_FLG_PSG_MONO			(1<<4)		// PSG (Sound1,2,3,4 monaural?)

//
// System initialization structures
//
typedef struct MUSYXInitParam {
	u16		desiredMixingRate;					// Desired sample mixing rate in Hz (2000-22050)
	u8		numberOfSampleVoices;				// Number of sample voices (0-250)
	u8		mixingFlags;						// Flags (MUSYX_FLG_xxxx or'ed together, see above)
	u16		delayInMSec;						// Size of the delay effect buffer in msec (0-1000)
	void	*projectData;						// Pointer to the MusyX project in ROM
} MUSYXInitParam;

typedef struct MUSYXMemRequirements {
	u32		structureSize;						// Size required for structures
	u32		ramCodeSize;						// Size required for code copied into RAM
	u32		mixBufferSize;						// Size required for mixing buffers
	u32		delayBufferSize;					// Size required for the delay effect buffer
} MUSYXMemRequirements;

typedef struct MUSYXMemLocations {
	void	*structures;						// Where to store structures and variables
	void	*ramCode;							// Where to put timing critical code in RAM
	void	*mixBuffer;							// Location of the mixing buffers
	void	*delayBuffer;						// Location of the delay buffer
} MUSYXMemLocations;


// Call this function to get information about the required memory sizes
extern u32			musyxCalcMemUsage(const MUSYXInitParam *WithTheseParameters, MUSYXMemRequirements *MemInfo);
extern void			musyxCalcSimpleMemLayout(const MUSYXMemRequirements *Info, const void *Base, MUSYXMemLocations *Mem);

// Initializes MusyX sound system with given parameters at given memory locations
extern MUSYXBool	musyxInit(const MUSYXInitParam *Parameters, const MUSYXMemLocations *MemLocations);

extern void			musyxShutdown(void);


// Sets a new number of sample voices to use
// Note: The number you specify in this call cannot exceed the number of voices specified
//        when musyxInit() was called. If you need to increase this number you have to call
//        musyxInit() again (without calling the IRQ service functions please!)
extern void			musyxSetNewNumberOfSampleVoices(u8 Max);


//
// Call this every VBL interrupt.
//
// NOTE: NEVER CALL THIS DURING A musyxTimerIRQ() HANDLING!!!
//       You have to setup semaphores if necessary.
//
extern void			musyxHandle(void);

//
// Call this from within TIMER 1 interrupt
//
// NOTE: You must ensure (depending on the sample output rate) to call this within
//       1 ms after the actual IRQ occurance. (1ms @ 11025Hz. Slower on smaller rates, quicker on higher).
//
extern void			musyxTimerIRQ(void);




// Silence all sound output immediately
extern void			musyxSilence(void);




//
// Song functions
//
#define MUSYX_SONGOFF_SEQ_ONLY		0
#define MUSYX_SONGOFF_SEND_KEYOFF	1
#define MUSYX_SONGOFF_VOICES_OFF	2
extern MUSYXBool	musyxInitSong(MUSYXId SongID);
extern MUSYXBool	musyxStartSong(void);
extern MUSYXBool	musyxStopSong(u32 OffMode);
extern MUSYXBool	musyxPauseSong(u32 OffMode);
extern MUSYXBool	musyxResumeSong(void);
extern MUSYXBool	musyxSongActive(void);
extern MUSYXBool	musyxChangeSongSpeed(u16 Scale);			// 0x1000 = 1.0, 0x2000 = 2.0, 0x0800 = 0.5
extern s32			musyxGetSeqStateSize(void);
extern MUSYXBool	musyxSaveSeqState(void *Buffer);
extern MUSYXBool	musyxRestoreSeqState(const void *Buffer);





//
// Sound effect functions
//
#define MUSYX_SFX_DEF_KEY	255
#define MUSYX_SFX_DEF_VEL	255
#define MUSYX_SFX_DEF_PAN	255

extern MUSYXId		musyxFXStart(MUSYXId SfxID, s32 Key, s32 Velocity, s32 Panning);
extern MUSYXBool	musyxFXKeyoff(MUSYXId ActiveID);
extern s32			musyxFXKeyoffAll(void);
extern MUSYXBool	musyxFXActive(MUSYXId fxID);
extern s32			musyxFXGetVolume(MUSYXId fxID);
extern s32			musyxFXVolume(MUSYXId fxID, s32 Volume);
extern s32			musyxFXGetPanning(MUSYXId fxID);
extern s32			musyxFXPanning(MUSYXId fxID, s32 Panning);
extern u16			musyxFXGetPitch(MUSYXId fxID);
extern u16			musyxFXSetPitch(MUSYXId fxID, u16 Pitch);




//
// Delay effect functions
//
extern void			musyxDelayParam(u16 Feedback, u16 Dryness, u16 Wetness);
extern void			musyxDelayEnable(MUSYXBool OnOff);





//
// User flag functions
//
extern u32			musyxGetFlags(void);
extern u32			musyxSetFlags(u32 Flags);
extern MUSYXBool	musyxGetFlag(s32 FlagNr);
extern MUSYXBool	musyxSetFlag(s32 FlagNr);
extern MUSYXBool	musyxClearFlag(s32 FlagNr);




//
// Master volumes to start new notes/effects with. Does not affect already active notes/effects.
// 0=silence, 255=max.volume
//
extern void			musyxMasterVolSong(u8 MasterVolume);
extern void			musyxMasterVolFX(u8 MasterVolume);





//
// Hardware volume scalers. See AGB programming manual.
//
extern void			musyxAGBVolScaler(u8 SGCNT0_H_LOW8BITS);			// Default: 0x0d
extern void			musyxGBVolScaler(u8 SGCNT0_L_LOW8BITS);				// Default: 0x77



#endif


