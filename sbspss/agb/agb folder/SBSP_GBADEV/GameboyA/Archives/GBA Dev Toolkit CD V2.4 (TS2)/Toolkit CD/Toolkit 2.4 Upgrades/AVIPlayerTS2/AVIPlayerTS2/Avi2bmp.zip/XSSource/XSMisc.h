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

#if !defined(AFX_XSMISC_H__C1FAE059_43D4_11D1_8754_006097727DCB__INCLUDED_)
#define AFX_XSMISC_H__C1FAE059_43D4_11D1_8754_006097727DCB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Luminosity definitions
#define HLSMAX 240	// Max HSL value is 240
#define RGBMAX 255	// Max RGB value is 255
                    // HLSMAX BEST IF DIVISIBLE BY 6
                    // RGBMAX, HLSMAX must each fit in a byte.

// Additional color definitions
#define COLOR_WHITE (RGB(255,255,255))
#define COLOR_BLACK (RGB(0,0,0))

// Hue is undefined if Saturation is 0 (grey-scale)
// This value determines where the Hue scrollbar is
// initially set for achromatic colors
#define UNDEFINED (HLSMAX * 2 / 3)

// define HSL accessors
#ifndef GetHValue
  #define GetHValue(hsl)  ((BYTE)(hsl))
  #define GetSValue(hsl)  ((BYTE)(((WORD)(hsl)) >> 8))
  #define GetLValue(hsl)  ((BYTE)((hsl)>>16))
  #define HSL(h,s,l)      ((COLORREF)(((BYTE)(h)|((WORD)((BYTE)(s))<<8))|(((DWORD)(BYTE)(l))<<16)))
  #define HSLCOLOR        COLORREF
#endif

// Miscellaneous Support Functions
int      XSFUNC XSColor_RGBtoLum(COLORREF crColor);
HSLCOLOR XSFUNC XSColor_RGBtoHLS(COLORREF crColor);
WORD     XSFUNC XSColor_HueToRGB(WORD n1, WORD n2, WORD hue);
COLORREF XSFUNC XSColor_HLStoRGB(HSLCOLOR hslColor);

BOOL XSFUNC XSPaint_Rect(CDC* pDC, int x, int y, int w, int h, 
            COLORREF color);
BOOL XSFUNC XSPaint_Rect(CDC* pDC, CRect rect, COLORREF color);

BOOL XSFUNC XSPaint_Gradient(CDC* pDC, CRect& rcRect, 
            COLORREF crColor, int nGradFills = 1);

BOOL XSFUNC XSCaption_SetText(HWND hwnd, LPCTSTR lpText, 
            BOOL bRedraw = TRUE);

// -------------------------------------------------------------

#endif // !defined(AFX_XSMISC_H__C1FAE059_43D4_11D1_8754_006097727DCB__INCLUDED_)
