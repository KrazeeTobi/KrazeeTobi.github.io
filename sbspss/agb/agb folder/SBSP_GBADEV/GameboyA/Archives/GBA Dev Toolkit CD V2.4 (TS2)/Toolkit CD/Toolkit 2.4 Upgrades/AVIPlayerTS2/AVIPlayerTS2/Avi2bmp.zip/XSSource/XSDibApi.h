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

#if !defined(AFX_XSDIBAPI_H__FD83396E_73B7_11D1_AB26_742502C10000__INCLUDED_)
#define AFX_XSDIBAPI_H__FD83396E_73B7_11D1_AB26_742502C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------
// DIB Definition
DECLARE_HANDLE(HDIB);

// -------------------------------------------------------------
// DIB Macros
#define macDibHeaderMarker   ((WORD) ('M' << 8) | 'B')
#define macIsWinDib(lpbi)		((*(LPDWORD)(lpbi)) == \
								sizeof(BITMAPINFOHEADER))
#define macDibWidthBytes(bits)	(((bits) + 31) / 32 * 4)

// -------------------------------------------------------------
// Create a new DIB based on passed parameters
HDIB        XSFUNC XSDib_Create(DWORD dwWidth, DWORD dwHeight, 
                    WORD wBitCount);
HDIB        XSFUNC XSDib_Template(BITMAPINFOHEADER& bi, 
                    HBITMAP hBitmap);

// -------------------------------------------------------------
// Load a DDB/DIB from a Resource
HBITMAP     XSFUNC XSBmp_Load(HINSTANCE hInst, UINT nID);

// -------------------------------------------------------------
// Load and Save DIBs from/to a File
HDIB        XSFUNC XSDib_Load(CString strFileName);
HDIB        XSFUNC XSDib_ReadFile(CFile& file, 
                    DWORD dwOffset = 0L);
WORD        XSFUNC XSDib_Save(HDIB hDib, CString strFileName);
WORD        XSFUNC XSDib_WriteFile(HDIB hDib, CFile& file);

// -------------------------------------------------------------
// Destroy DIB Memory
void        XSFUNC XSDib_Destroy(HDIB hDib);

// -------------------------------------------------------------
// DIB Utility Functions
LONG        XSFUNC XSDib_Width(LPVOID lpDib);
LONG        XSFUNC XSDib_Width(HDIB hDib);
LONG        XSFUNC XSDib_Height(LPVOID lpDib);
LONG        XSFUNC XSDib_Height(HDIB hDib);
WORD        XSFUNC XSDib_PaletteSize(LPVOID lpDib);
WORD        XSFUNC XSDib_PaletteSize(HDIB hDib);
WORD        XSFUNC XSDib_NumColors(LPVOID lpDib);
WORD        XSFUNC XSDib_NumColors(HDIB hDib);
LPVOID      XSFUNC XSDib_FindBits(LPVOID lpDib);
LPVOID      XSFUNC XSDib_FindBits(HDIB hDib);
DWORD       XSFUNC XSDib_CalcPadding(DWORD dwBitsPerPixel, 
                    DWORD dwPixels);
DWORD       XSFUNC XSDib_CalcBytesPerLine(DWORD dwBitsPerPixel, 
                    DWORD dwWidth);
DWORD       XSFUNC XSDib_LastByte(DWORD dwBitsPerPixel, 
                    DWORD dwPixels);

// -------------------------------------------------------------
// DIB Palette Functions
HPALETTE    XSFUNC XSDib_CreatePalette(HDIB hDib);

// -------------------------------------------------------------
// DIB/DDB Conversion Functions
HDIB        XSFUNC XSBmp_ToDib(HBITMAP hBitmap, HPALETTE hPal);
HBITMAP     XSFUNC XSDib_ToBmp(HDIB hDib, HPALETTE hPal);
HDIB        XSFUNC XSBmp_ChangeFormat(HBITMAP hBitmap, 
                    WORD wBitCount, DWORD dwCompression, 
                    HPALETTE hPal);
HDIB        XSFUNC XSDib_ChangeFormat(HDIB hDib, WORD wBitCount, 
                    DWORD dwCompression);

// -------------------------------------------------------------
// DIB Painting Functions
BOOL        XSFUNC XSDib_Paint(HDC hDC, CRect rcDim, HDIB hDib, 
                    CRect rcDib, HPALETTE hPal);

// -------------------------------------------------------------
// DIB Operation Functions
HDIB        XSFUNC XSDib_Rotate(HDIB hDibSrc, 
                    BOOL bClockwise = TRUE);


#endif // !defined(AFX_XSDIBAPI_H__FD83396E_73B7_11D1_AB26_742502C10000__INCLUDED_)
