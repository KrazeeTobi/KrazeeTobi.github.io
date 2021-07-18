//------------------------------------------------------------------------------
// Copyright © 1995-1998, Xendra Software (http://www.xendra.com).
// All Rights Reserved.
//------------------------------------------------------------------------------
// THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO AS
// "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL
// XENDRA SOFTWARE OR ITS SUPPLIERS BE LIABLE FOR ANY DAMAGES WHATSOEVER
// INCLUDING DIRECT, INDIRECT, INCIDENTAL, CONSEQUENTIAL, LOSS OF BUSINESS
// PROFITS OR SPECIAL DAMAGES, EVEN IF XENDRA SOFTWARE OR ITS SUPPLIERS HAVE
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// This Software may be copied and distributed royalty-free subject to the
// following conditions:
//
// 1. You must copy all Software without modification and must include all
//    pages, if the Software is to be distributed without inclusion in your
//    software product.  If you are incorporating the Software in conjunction
//    with and as part of your software product which adds substantial value,
//    you may modify and include portions of the Software.  Any modifications
//    or additions to the Software should be sent to submit@xendra.com in
//    order to be incorporated into  the Software for the benefit of all those
//    who may use the Software.
//
// 2. You must place all copyright notices and other protective disclaimers
//    and notices contained on the Software on all copies of the Software and
//    your software product.  If you are incorporating the Software in
//    conjunction with and as part of your software product which adds
//    substantial value, you must display the following statement somewhere
//    that is easily assessable by the User of your product:
//
//     "Extensions Copyright © 1995-1998,
//      Xendra Software (http://www.xendra.com). All Rights Reserved."
//
// 3. Unless the Software is incorporated in your software product which
//    adds substantial value, you may not distribute this Software for
//    profit.
//
// 4. You may not incorporate the Software into any product that would
//    compete against the Software.
//
// 5. You agree to indemnify, hold harmless, and defend Xendra Software
//    and its suppliers from and against any claims or lawsuits, including
//    attorneys' fees, that arise or result from the use or distribution of
//    your software product and any modifications to the Software.
// ------------------------------------------------------------------------------

#include "stdafx.h"
#include "XSmain.h"

//#include "XSPalApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------
// PalEntriesOnDevice
//	Parameter:    HDC hDC - device context
//	Return Value: int - number of palette entries on device
//	Description:
//		This function gets the number of palette entries on the
//      specified device
// -------------------------------------------------------------
int XSFUNC
XSPal_EntriesOnDevice(HDC hDC)
{
	int nColors;  // number of colors

	// Find out the number of palette entries on this
	// device.
	nColors = GetDeviceCaps(hDC, SIZEPALETTE);

	// For non-palette devices, we'll use the # of system
	// colors for our palette size.
	if (!nColors)
		nColors = GetDeviceCaps(hDC, NUMCOLORS);

	ASSERT(nColors);
	return nColors;
}

// -------------------------------------------------------------
// GetSystemPalette
// Parameters  : None
// Return Value: HPALETTE - handle to a copy of the current
//               system palette
// Description :
//      This function returns a handle to a palette which
//      represents the system palette.  The system RGB values
//      are copied into our logical palette using the
//      GetSystemPaletteEntries function.
// -------------------------------------------------------------
HPALETTE XSFUNC
XSPal_GetSystemPalette()
{
	HDC hDC;				// handle to a DC
	HPALETTE hPal = NULL;	// handle to a palette
	HANDLE hLogPal;			// handle to a logical palette
	LPLOGPALETTE lpLogPal;	// pointer to a logical palette
	int nColors;			// number of colors

    hDC = ::GetDC(NULL);
	if (!hDC)
		return NULL;

    // Number of palette entries
    nColors = ::XSPal_EntriesOnDevice(hDC);

	// Allocate room for the palette and lock it
    hLogPal = ::GlobalAlloc(GHND, sizeof(LOGPALETTE) +
		nColors * sizeof(PALETTEENTRY));

	// if we didn't get a logical palette, return NULL
	if (!hLogPal)
		return NULL;

	// get a pointer to the logical palette
    lpLogPal = (LPLOGPALETTE)::GlobalLock(hLogPal);

	// set some important fields
	lpLogPal->palVersion = PALVERSION;
	lpLogPal->palNumEntries = nColors;

	// Copy the current system palette into our logical palette
    ::GetSystemPaletteEntries(hDC, 0, nColors,
        (LPPALETTEENTRY)(lpLogPal->palPalEntry));

	// Go ahead and create the palette.  Once it's created,
	// we no longer need the LOGPALETTE, so free it.
	hPal = ::CreatePalette(lpLogPal);

	// Clean up
    ::GlobalUnlock(hLogPal);
    ::GlobalFree(hLogPal);
    ::ReleaseDC(NULL, hDC);

	return hPal;
}
