/****************************************************************/
/*                          sound.c                             */
/****************************************************************/
#include <Agb.h>

// Include header files for wave files
#include "pikachu.h"

// Define WavePoint as the address of wave data
#define WavePoint binary_pikachu_bin_start


/*-------------------- Global variables  -----------------------*/

    u32 waveBufferL[0x400/4];
    u32 waveBufferR[0x400/4];

    u8 *wavePointerL;
    u8 *wavePointerR;

    u8 vblankFlag;
    u8 dmaCounter;
    u32 frameCounter;
    u16 bytesPerFrame = (SampleRate/45);


/*==============================================================*/
/*                  PCM sound start routine                     */
/*          This function is called beginning of sound          */
/*==============================================================*/
void soundStart(void)
{
    // Initialize frame counter
    frameCounter = 0;

    // Copy sound data from ROM to buffer in work RAM
    // "WavePoint" is the head address of wave data
    wavePointerL = (u8 *)WavePoint;
    DmaCopy(3, wavePointerL, waveBufferL, bytesPerFrame, 16);

#if Channel==2
    wavePointerR = (u8 *)(WavePoint + Samples);
    DmaCopy(3, wavePointerR, waveBufferR, bytesPerFrame, 16);
#endif // Channel

    // Initialize sound control registers
    *(vu16 *)REG_SOUNDCNT_X = SOUND_DMG_ON; // Enable all sound channels (includes PCM channels)
    *(vu16 *)REG_SOUNDCNT_H =
            ((SOUND_A_FIFO_RESET | SOUND_B_FIFO_RESET
            | SOUND_A_TIMER_0    | SOUND_B_TIMER_0
            | SOUND_A_SO2_ON     | SOUND_B_SO1_ON) << 8);

    // Set DMA1,2 control registers
    *(vu32 *)REG_DMA1DAD = REG_FIFO_A;  // Destination address
    *(vu32 *)REG_DMA2DAD = REG_FIFO_B;

    *(vu32 *)REG_DMA1CNT =
              DMA_ENABLE    | DMA_TIMMING_SOUND
            | DMA_32BIT_BUS | DMA_CONTINUOUS_ON
            | DMA_SRC_INC   | DMA_DEST_RELOAD
            | 0x4;
    *(vu32 *)REG_DMA2CNT =
              DMA_ENABLE    | DMA_IF_ENABLE | DMA_TIMMING_SOUND
            | DMA_32BIT_BUS | DMA_CONTINUOUS_ON
            | DMA_SRC_INC   | DMA_DEST_RELOAD
            | 0x4;

    // Start timer 0 (for sound A,B)
    *(vu32 *)REG_TM0CNT =
              TMR_ENABLE
            |  TMR_PRESCALER_1CK
            | (u16)(0x10000-(16777216/SampleRate));
}


/*==============================================================*/
/*                  PCM sound stop routine                      */
/*          This function is called when sound stops            */
/*==============================================================*/
void soundStop(void)
{
    // Disable all sound channels (includes PCM channels)
    *(vu16 *)REG_SOUNDCNT_X = 0;

    // Stop DMA 1,2 (for sound A,B)
    *(vu32 *)REG_DMA1CNT = 0;
    *(vu32 *)REG_DMA2CNT = 0;

    // Stop timer 0 (for sound A,B)
    *(vu32 *)REG_TM0CNT = 0;
}


/*==============================================================*/
/*                  Sound v-blank routine                       */
/*      This function is must be called                         */
/*                      at the end of V-blank routine           */
/*==============================================================*/
void soundVblank(void)
{
    vblankFlag = 1;
}


/*==============================================================*/
/*              Sound DMA(2) Interrupt routine                  */
/*      This function refreshes wave buffer every frame         */
/*==============================================================*/
void soundDmaIrq(void)
{
    // Check V-blank routine is done
    if(!vblankFlag) {
        dmaCounter++;
        return;
    }

    // Increase and check frame counter
    if(frameCounter++ >= Frames)
        soundStop();

// Change DMA source addresses
    // Stop DMAs
    *(vu32 *)REG_DMA1CNT = 0;
    *(vu32 *)REG_DMA2CNT = 0;

    *(vu32 *)REG_DMA1SAD = (u32)waveBufferL;
#if Channel==1
    *(vu32 *)REG_DMA2SAD = (u32)waveBufferL;
#else
    *(vu32 *)REG_DMA2SAD = (u32)waveBufferR;
#endif //Channel

    // Restert DMAs
    *(vu32 *)REG_DMA1CNT =
              DMA_ENABLE    | DMA_TIMMING_SOUND
            | DMA_32BIT_BUS | DMA_CONTINUOUS_ON
            | DMA_SRC_INC   | DMA_DEST_RELOAD
            | 0x4;

    *(vu32 *)REG_DMA2CNT =
              DMA_ENABLE    | DMA_IF_ENABLE | DMA_TIMMING_SOUND
            | DMA_32BIT_BUS | DMA_CONTINUOUS_ON
            | DMA_SRC_INC   | DMA_DEST_RELOAD
            | 0x4;

    // Move wave data pointer
    wavePointerL += (dmaCounter+1) * 16;
#if Channel==2
    wavePointerR += (dmaCounter+1) * 16;
#endif //Channel

    // DMA wave data from ROM to Work RAM
    // (Not necessary for product AGBs)
    DmaCopy(3, wavePointerL, waveBufferL, bytesPerFrame, 16);
#if Channel==2
    DmaCopy(3, wavePointerR, waveBufferR, bytesPerFrame, 16);
#endif //Channel

    // Reset V-blank flag
    vblankFlag = 0;

    // Reset DMA counter
    dmaCounter = 0;
}
