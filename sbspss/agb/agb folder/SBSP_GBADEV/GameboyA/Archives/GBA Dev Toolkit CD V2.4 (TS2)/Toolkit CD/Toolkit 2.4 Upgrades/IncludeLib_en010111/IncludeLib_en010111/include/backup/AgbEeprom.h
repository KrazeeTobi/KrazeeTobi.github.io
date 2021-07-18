/********************************************************************/
/*          AgbEeprom.h	                                            */
/*            4kbit EEPROM Library Header    ver. 1.1.1             */
/*                                                                  */
/*                                         last modified 2001.01.11 */
/*                                                                  */
/*          Copyright (C) 2000, 2001 Nintendo of America Inc.       */
/********************************************************************/
#ifndef	__AGB_EEPROM_H__
#define	__AGB_EEPROM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>

// define data----------------------------------
#define EEPROM_SIZE	   512  // EEPROM Size(byte) 64*64/8=512byte(4kbit)
#define	EEPROM_ADR_COUNT   64   // EEPROM Address Count(Range 0x00-0x3f)

/*------------------------------------------------------------------*/
/*          Timer Interrupt Settings for Access                     */
/*------------------------------------------------------------------*/

extern u16 SetEepromTimerIntr(u8 timerNo, void (**IntrFunc)(void));

/*   Selects timer interrupt for determining timeouts during access to EEPROM.
     You must call at least once before each access routine is called. Once 
     you have set the timer interrupt to be used with this routine, and as 
     long as you don't use the timer interrupt for the set No. with other 
     processing, or use a different interrupt table, it is not necessary to 
     call this routine again.
     If timer No. is not from 0-3, error.
     *According to the library specifications, when this routing is called, a 
     specific timer interrupt routine is forcibly set for the library functions
     so the interrupt table when accessing EEPROM must be in the RAM area.
	<Arguments>
	 u8 timerNo	:Number of timer used by timeout routine.
	 void (**IntrFunc)(void): Pointer to compatible timer interrupt 
                                 address in interrupt table.
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Read Doubleword (8 bytes) Data                          */
/*------------------------------------------------------------------*/

extern u16 ReadEepromDword(u16 epAdr,u16 *dst);

/*	Read 8 bytes of data from target EEPROM address to dst address.
	If outside range with target EEPROM address, error.
	*This routine uses DMA 3. When DMA is being used in this routine,
         all interrupts are prohibited.
	<Arguments>
	 u32 epAdr	:Target EEPROM Address (0x00-0x3f)
	 u16 *dst	:Read Data transfer destination
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error

	* Please note all interrupts are prohibited during a certain period 
	  (about 40us) when this function is called.   
   Refer to "Cautions when EEPROM access function is used." in the "AGB 
   Backup Library Manual" for details.   
   Do not use the direct sound when this function is called. 
*/

/*------------------------------------------------------------------*/
/*          Doubleword (8 bytes) Write Data                         */
/*------------------------------------------------------------------*/

extern u16 ProgramEepromDword(u16 epAdr,u16 *src);

/*	Write 8 bytes of data from src address to target EEPROM address.
	If outside range with target EEPROM address, error.
	*This routine uses DMA 3. When DMA is being used in this routine,
         all interrupts are prohibited.
	<Arguments>
	 u32 epAdr	:Target EEPROM Address (0x00-0x3f)
	 u16 *dst	:Write source data address
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error

	* Please note all interrupts are prohibited during a certain period 
	  (about 40us) when this function is called.   
	Refer to "Cautions when EEPROM access function is used." in the "AGB 
	Backup Library Manual" for details.   
	Do not use the direct sound when this function is called. 
*/

/*------------------------------------------------------------------*/
/*          Verify Doubleword (8 bytes) Data                        */
/*------------------------------------------------------------------*/

extern u16 VerifyEepromDword(u16 epAdr,u16 *src);

/*	Verify 8 bytes of data for src address and target EEPROM address.
	*This routine uses DMA 3. When DMA is being used in this routine,
         all interrupts are prohibited.
	<Arguments>
	 u16 epAdr	:Target EEPROM Address (0x00-0x3f)
	 u8 *src	:Verify source address
	<Return Values>
	 u16 	:0 is normal end, Not 0 is error


	* Please note all interrupts are prohibited during a certain period 
	  (about 40us) when this function is called.   
	Refer to "Cautions when EEPROM access function is used." in the "AGB 
	Backup Library Manual" for details.   
	Do not use the direct sound when this function is called. 
*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGB_EEPROM_H__
