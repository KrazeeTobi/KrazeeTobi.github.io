/****************************************************************/
/*                          sound.h                             */
/****************************************************************/

#ifndef	__SOUND_H__
#define	__SOUND_H__

#include <agb.h>

//--------------------------- Functions -----------------------------
void soundStart(void);
void soundStop(void);
void soundVblank(void);
void soundDmaIrq(void);

#endif	//  __SOUND_H__
