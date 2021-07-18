/********************************************************************/
/*          AgbDacs.h 		                                    */
/*            1Mbit DACS Library Header    ver. 1.1.1               */
/*                                                                  */
/*                                         last modified 2001.01.11 */
/*                                                                  */
/*          Copyright (C) 2000 Nintendo of America Inc.             */
/********************************************************************/
#ifndef __AGBDACS_H__
#define __AGBDACS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <AgbTypes.h>

// define data----------------------------------
#define	DACS_ADR	0x0dfe0000	// DACS Write Start Address
#define	DACS_READ_TOP	0x09fe0000      // DACS Read Start Address

// The access cycle for DACS during read and write is different
// so changed address accessed.

typedef struct dacsSectorTag {
	u32			size;	// Sector Size
	u8			shift;	// Value converted from sector 
                                        // size to shift count
	u16			count;	// Sector Count
	u16			top;	// Usable start sector No.
}dacsSector;

typedef struct dacsTypeTag {
	u32 		romSize;		// ROM Size
	u16			totalSector;	// Total Sector Count
	dacsSector	s_sector;		// Small Size Sector Information	
        dacsSector	h_sector;		// Large Size Sector Information	
	u16			agbWait[2];	// AGB Game Pak Bus read/write
						// wait value(ROM 2 Area)
	u16			makerID;		// Maker ID
	u16			deviceID;		// Device ID
}dacsType;

		/* Determine if have multi-size sector as follows:
		   When targetSector < totalSector,
		   if targetSector < s_sector.count have multi-size sector
		   if targetSector >=s_sector.count no multi-size sector
		*/

/*------------------------------------------------------------------*/
/*          Global Variable                                         */
/*------------------------------------------------------------------*/

extern const dacsType *dacs;	// Pointer to data showing content of DACS
				// (See definition of above data for details)
extern u32 dacs_remainder;	// Barometer showing progress during DACS write

/*------------------------------------------------------------------*/
/*          Device Identification and Initial Settings              */
/*------------------------------------------------------------------*/

extern u16 IdentifyDacs();

/*   Identifies DACS device being used with Game Pak. Gets flash capacity 
     and sector size, and sets up access speed. The obtained data can be 
     referenced using the global variable dacsType *dacs.
     (See the header file dacs.h for more details on dacsType.)
	Prior to accessing DACS(including reads), please call once.
	If cannot identify device an error is returned and the following 
        access functions can no longer be used.
	
	<Arguments>
	 None
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Access Timer Interrupt Settings                         */
/*------------------------------------------------------------------*/

extern u16 SetDacsTimerIntr(u8 timerNo, void (**IntrFunc)(void));

/*   Selects timer interrupt for determining timeouts during access to DACS. 
     Transfers timeout determination function and DACS status polling 
     function to buffer set aside in WRAM.
     You must call at least once before each access routine is called. Once 
     you have set the timer interrupt to be used with this routine, and as 
     long as you don't use the timer interrupt for the set No. with other 
     processing, or use a different interrupt table, it is not necessary to 
     call this routine again. However, if you overlay and use the RAM area of 
     this library, it is possible that the functions transfered to the RAM were 
     overwritten. 
     If timer No. is not from 0-3, error.
     *According to the library specifications, when this routing is called, a 
     specific timer interrupt routine is forcibly set for the library functions
     so the interrupt table when accessing DACS must be in the RAM area.
	<Arguments>
	 u8 timerNo	:Number of timer used by timeout routine.
	 void (**IntrFunc)(void):Pointer to compatible timer interrupt 
                                 address in interrupt table.
	<Return Values>
	 u16 result	:0 is normal end, Not 0 is error



/*------------------------------------------------------------------*/
/*          Erase Chip                                              */
/*------------------------------------------------------------------*/

extern u16 EraseDacsChip();
/*	Erase entire chip.
	<Arguments>
	None
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
/*------------------------------------------------------------------*/
/*          Erase Sector                                            */
/*------------------------------------------------------------------*/

extern u16 EraseDacsSector(u16 secNo);

/*   Erase sector of target sector No.
     This routine is called in write routine, so usually you don't
     need to call it before a write.
	Error results if target sector No. is outside range (Not 2-15).
	<Arguments>
	 u16 secNo	:Target Sector No.
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Write of Sector Unit Data                               */
/*------------------------------------------------------------------*/

extern u16 ProgramDacsSector(u16 secNo,u16 *src);

/*   Write 1 sector (8 kbytes) to target sector No. from src address.
     Call the above EraseDacsSector in this routine, and write after 
     erasing sector. If target sector No. is outside range, error.
	<Arguments>
	 u16 secNo	:Target Sector No.
	 u8 *src	:Write Source Address
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGBDACS_H__
