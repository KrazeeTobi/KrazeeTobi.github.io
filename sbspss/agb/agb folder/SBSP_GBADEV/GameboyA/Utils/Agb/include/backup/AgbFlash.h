/********************************************************************/
/*          AgbFlash.h		                                    */
/*            512kbit FLASH Library Header    ver. 1.2.1            */
/*                                                                  */
/*                                         last modified 2001.01.11 */
/*                                                                  */
/*          Copyright (C) 2000, 2001 Nintendo of America Inc.       */
/********************************************************************/
#ifndef	__AGB_FLASH_H__
#define	__AGB_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>

// define data----------------------------------
#define	FLASH_ADR			0x0e000000  // Flash Start Address

typedef struct flashSectorTag {
	u32			size;		 // Sector Size
	u8			shift;		 // Value converted from sector
						 // size to shift count
	u16			count;	         // Sector Count
	u16			top;		 // Usable start sector No.
}flashSector;

typedef struct flashTypeTag {
	u32 		romSize;		// ROM Size
	flashSector	sector;			// Sector Information
                                                // (See flashSector above)
	u16			agbWait[2];	// AGB Game Pak Bus 
                                                // read/write wait value
	u8			makerID;		// Maker ID
	u8			deviceID;		// Device ID
}flashType;

/*------------------------------------------------------------------*/
/*          Global Variable                                         */
/*------------------------------------------------------------------*/
extern const flashType *flash;	// Pointer to data showing content of flash
			        // (See definition of above data for details)
extern u16 flash_remainder;	// Barometer showing progress during flash write
/*------------------------------------------------------------------*/
/*          Device Identification and Initial Settings              */
/*------------------------------------------------------------------*/

extern u16 IdentifyFlash();

/*   Reads flash ID. Identifies what flash is in Game Pak. Gets flash 
     capacity and sector size, sets up access speed, and sets the corresponding
     access functions for flash. The flash data obtained can be referenced with
     the global variable flashType *flash. (See definition of above for details
     on flashType)
     Call this function once before accessing flash(including read).
     If device cannot be identified an error is returned and the following 
     access function cannot be used.
	<Arguments>
	 None
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Timer Interrupt Settings for Access                     */
/*------------------------------------------------------------------*/

extern u16 SetFlashTimerIntr(u8 timerNo, void (**IntrFunc)(void));

/*   Selects timer interrupt for determining timeouts during access to 
     flash. Prior to calling each routine, except for IdentifyFlash, you 
     must call at least once.  Once you have set the timer interrupt to 
     be used with this routine, and as long as you don't use the timer 
     interrupt for the set No. with other processing, or use a different 
     interrupt table, it is not necessary to call this routine again.
     If timer No. is not from 0-3, error.
     *According to the library specifications, when this routing is called, a 
     specific timer interrupt routine is forcibly set for the library functions
     so the interrupt table when accessing flash must be in the RAM area.
     <Arguments>
	 u8 timerNo	:Number of timer used by timeout routine.
	 void (**IntrFunc)(void):Pointer to compatible timer interrupt 
                                 address in interrupt table.
     <Return Values>
	 u16 result	:0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Erase Chip                                              */
/*------------------------------------------------------------------*/

extern u16 (*EraseFlashChip)();

/*	Completely erase all of chip.
	<Arguments>
	 None
	<Return Values>
	 u16 result      : 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Erase Sector                                            */
/*------------------------------------------------------------------*/

extern u16 (*EraseFlashSector)(u16 secNo);

/*   Erase sector of target sector number.
     This routine is called in the write routine so it is usually not 
     necessary to call it before a write. If the target sector No. is 
     outside the range an error is returned. 
	<Arguments>
	 u16 secNo	: Target sector No.
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error

*Please note all interrupts are prohibited during a certain period when Flash 
	manufactured by Atmel is used.  
	Refer to "Cautions when Flash access function is used." in the "AGB
	Backup Library Manual" for details.  Do not use the direct sound when 
	this function is called. 
*/

/*------------------------------------------------------------------*/
/*          Write of Sector Unit Data                               */
/*------------------------------------------------------------------*/

extern u16 (*ProgramFlashSector)(u16 secNo,u8 *src);

/*   Write 1 sector (4 kbytes) to target sector No. from src address.
     Call the above EraseFlashSector in this routine, and write after 
     erasing sector. If target sector No. is outside range, error is 
     returned.
     When executing this routine, you can determine the remaining byte 
     count by referencing the global variable flash_remainder.
	<Arguments>
	 u16 secNo	:Target sector No.
	 u8 *src	:Write source address
	<Return Values>
	 u16 result	:0 is normal end, Not 0 is error

*Please note all interrupts are prohibited during a certain period when Flash 
	manufactured by Atmel is used.  
	Refer to "Cautions when Flash access function is used." in the "AGB
	Backup Library Manual" for details.  Do not use the direct sound when 
	this function is called. 

*/

/*------------------------------------------------------------------*/
/*          Verify Data                                             */
/*------------------------------------------------------------------*/

extern u32 VerifyFlashSector(u16 secNo,u8 *src);

/*   Verify data from src address and one sector (4kbytes) of data 
     from flash target sector No. If verify ends normally 0 is returned. 
     If error occurred, returns the address where error happened. 
	<Arguments>
	 u16 secNo	:Target sector No.
	 u8 *src	:Verify source address(original data)
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*         Read Data                                                */
/*------------------------------------------------------------------*/

extern void ReadFlash(u16 secNo,u32 offset,u8 *dst,u32 size);

/*   From offset byte start address in flash target sector No., read 
     data equivalent to size(bytes) to area starting from work dst address.
	<Arguments>
	 u16 secNo	:Target sector No.
	 u32 offset	:Offset bytes in sector
	 u8 *dst	:Address of work area where read data stored
	 u32 size	:Read size in bytes
	<Return Values>
	 None
*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGB_FLASH_H__
