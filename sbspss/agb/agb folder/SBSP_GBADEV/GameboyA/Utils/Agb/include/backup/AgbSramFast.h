/********************************************************************/
/*         AgbSramFast.h                                            */
/*         256kbit SRAM High Speed Access Library Headerver. 1.0.0  */
/*                                                                  */
/*                                         last modified 2000.12.13 */
/*                                                                  */
/*          Copyright (C) 2000 Nintendo of America Inc.             */
/********************************************************************/
#ifndef	__AGB_SRAM_FAST_H__
#define	__AGB_SRAM_FAST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>

#define	SRAM_ADR		0x0e000000	// SRAM Start Address
#define	SRAM_SIZE_256K		0x00008000	// 256KSRAM
#define	SRAM_SIZE_512K		0x00010000	// 512KSRAM

/*------------------------------------------------------------------
  Compared to the function group for AgbSram.h, the function group 
  in this header file can access SRAM at a high speed.
  However, note that it uses a static variable area of approximately
  300 bytes.
--------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*          Access Routine Settings                                 */
/*------------------------------------------------------------------*/
extern void SetSramFastFunc();

/*   According to the specifications for the routines ReadSram() and
     VerifySram(), they need to operate on WRAM so these routines are
     transfered to the WRAM static area.
     Call this function once before accessing SRAM(including reads).
     <Arguments>
      None
     <Return Values>
      None
*/


/*------------------------------------------------------------------*/
/*          Read Data                                               */
/*------------------------------------------------------------------*/

extern void (*ReadSramFast)(u8 *src,u8 *dst,u32 size);

/*   Read size byte data from SRAM address specified with argument to 
     area starting from work dst address.
     <Arguments>
         u8 *src : Read source SRAM address (Address on AGB memory map)
         u8 *dst : Address of work area where read data is stored
         (Address on AGB memory map)
        u32 size : Read size in bytes
     <Return Values>
	 None
*/


/*------------------------------------------------------------------*/
/*          Write Data                                              */
/*------------------------------------------------------------------*/

extern void WriteSramFast(u8 *src,u8 *dst,u32 size);

/*   Write size byte data from work area address specified with argument 
     to area starting from SRAM dst address.
     <Arguments>
	 u8 *src : Write source work area address
	 u8 *dst : Write destination SRAM address(Address on AGB memory map)
	 u32 size : Write size in bytes
     <Return Values>
	 None
*/

/*------------------------------------------------------------------*/
/*          Verify Data                                             */
/*------------------------------------------------------------------*/

extern u32 (*VerifySramFast)(u8 *src,u8 *tgt,u32 size);

/*   Verify size byte portion of data from work area src address and 
     SRAM tgt address.
     If verify ends normally this function returns a 0, if a verify 
     error occurred, the address where it happened is returned.
     <Arguments>
	 u8 *src : Pointer to verify source work area address (original data)
	 u8 *tgt : Pointer to verify destination SRAM address
		  (Write destination data, address on AGB memory map)
	 u32 size: Verify size in bytes
     <Return Values>
	 u32 errorAdr: If normal end 0. If verify error, error address.
*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGB_SRAM_FAST_H__
