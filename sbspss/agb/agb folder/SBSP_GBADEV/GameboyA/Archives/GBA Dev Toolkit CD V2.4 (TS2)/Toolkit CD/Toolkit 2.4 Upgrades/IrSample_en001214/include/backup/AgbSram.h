/********************************************************************/
/*          AgbSram.h                                               */
/*            256kbit SRAM Library Header ver. 1.1.0                */
/*                                                                  */
/*                                         last modified 2000.11.30 */
/*                                                                  */
/*          Copyright (C) 2000 Nintendo of America Inc.             */
/********************************************************************/
#ifndef	__AGB_SRAM_H__
#define	__AGB_SRAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>

#define	SRAM_ADR		0x0e000000	// SRAM Start Address
#define	SRAM_SIZE_256K		0x00008000	// 256KSRAM
#define	SRAM_SIZE_512K		0x00010000	// 512KSRAM 

/*------------------------------------------------------------------
The function group in this header file was also used in the old version.
The static variable area of the main unit WRAM is not used, but please 
note that the compared to the function group AgbSramFast.h, access to 
SRAM lower in speed. 
--------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*          Read Data                                               */
/*------------------------------------------------------------------*/

extern void ReadSram(u8 *src,u8 *dst,u32 size);

/*   From the SRAM address specified by the argument, read the size 
     byte data to area starting from work dst address.
     <Arguments>
     u8 *src 	: Read source SRAM address (Address on AGB memory map)
     u8 *dst    : Address of work area where read data is stored
                  (Address on AGB memory map)
     u32 size   : Read size in bytes
     <Return Values>
	 None
*/


/*------------------------------------------------------------------*/
/*          Write Data                                              */
/*------------------------------------------------------------------*/

extern void WriteSram(u8 *src,u8 *dst,u32 size);

/*   From the work area address specified by the argument, write the size 
     byte data to area starting from SRAM dst address.
     <Arguments>
     u8 *src	: Write source work area address
     u8 *dst	: Write destination SRAM address
		  (Address on AGB memory map)
     u32 size	: Write size in bytes
     <Return Values>
     None
*/
/*------------------------------------------------------------------*/
/*          Verify Data                                             */
/*------------------------------------------------------------------*/

extern u32 VerifySram(u8 *src,u8 *tgt,u32 size);

/*   Verify size byte portion of data from the work area src address 
     and SRAM tgt address. 
     If verify ends normally this function returns a 0, if a verify error 
     occurred, the address where it happened is returned.
     <Arguments>
     u8 *src	: Pointer to verify source work area address(original data)
     u8 *tgt	: Pointer to verify target SRAM address
		(write destination data, address on AGB memory map)
     u32 size	:Verify size in bytes
     <Return Values>
     u32 errorAdr: 0 if normal end. Error address if verify error. 
*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGB_SRAM_H__
