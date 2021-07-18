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
// 3. Unless the Software is incorporated in your software product which//    adds substantial value, you may not distribute this Software for
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

// -------------------------------------------------------------
// Some of these functions were originally published in MSJ by
// Paul Dilascia and have been modified from their original
// content.
// -------------------------------------------------------------

#include "stdafx.h"
#include "XSmain.h"

#if 0
#include "XSError.h"
#include "XSMisc.h"
#include "XSPalApi.h"
#include "XSPalette.h"
#include "XSDibApi.h"
#include "XSBitmap.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------
// Function  :
//  XSColor_RGBtoLum
// Purpose   :
//  Converts an RGB Color value to a Luminosity Color value
// Parameters:
//  COLORREF crColor - The color to convert to aluminosity
//                     color value
// Returns   :
//  int - the luminosity of the passed color
// -------------------------------------------------------------
int XSFUNC
XSColor_RGBtoLum(COLORREF crColor)
{
	int r = GetRValue(crColor);
	int g = GetGValue(crColor);
	int b = GetBValue(crColor);
	int rgbMax = max(max(r,g), b);
	int rgbMin = min(min(r,g), b);
	return (((rgbMax + rgbMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);
}

// -------------------------------------------------------------
// Function  :
//  XSColor_RGBtoHLS
// Purpose   :
//  Converts an RGB Color value to an HLS Color value.
// Parameters:
//  COLORREF crColor - The color to convert to an HSL value
// Returns   :
//  HSLCOLOR - the HSL Color value
// -------------------------------------------------------------
HSLCOLOR XSFUNC
XSColor_RGBtoHLS(COLORREF crColor)
{
    WORD R,G,B;                 // input RGB values
    BYTE cMax,cMin;             // max and min RGB values
    WORD Rdelta,Gdelta,Bdelta;  // intermediate value: % of spread from max
    WORD H = 0, L = 0, S = 0;   // Output HLS values

    // get R, G, and B out of DWORD
    R = GetRValue(crColor);
    G = GetGValue(crColor);
    B = GetBValue(crColor);

    // calculate lightness
    cMax = (BYTE)max( max(R,G), B);
    cMin = (BYTE)min( min(R,G), B);
    L = (((cMax + cMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);

    if (cMax == cMin)
    {
        // r=g=b --> achromatic case
        S = 0;          // saturation
        H = UNDEFINED;  // hue
    }
    else
    {
        // chromatic case
        // saturation
        if (L <= (HLSMAX / 2))
            S = (((cMax - cMin) * HLSMAX) +
            ((cMax + cMin) / 2)) / (cMax + cMin);
        else
            S = (((cMax - cMin) * HLSMAX) +
            ((2 * RGBMAX - cMax - cMin) / 2))
            / (2 * RGBMAX - cMax - cMin);

        // hue
        Rdelta = (((cMax - R) * (HLSMAX / 6)) +
            ((cMax - cMin) / 2)) / (cMax - cMin);
        Gdelta = (((cMax - G) * (HLSMAX / 6)) +
            ((cMax - cMin) / 2)) / (cMax - cMin);
        Bdelta = (((cMax - B) * (HLSMAX / 6)) +
            ((cMax - cMin) / 2)) / (cMax - cMin);

        if (R == cMax)
            H = Bdelta - Gdelta;
        else if (G == cMax)
            H = (HLSMAX / 3) + Rdelta - Bdelta;
        else // B == cMax
            H = ((2 * HLSMAX) / 3) + Gdelta - Rdelta;

        if (H < 0)
            H += HLSMAX;
        if (H > HLSMAX)
            H -= HLSMAX;
    }

    return HSL(H, S, L);
}

// -------------------------------------------------------------
// Function  :
//  XSColor_HueToRGB
// Purpose   :
//  Converts a Hue value to it's Red, Green, or Blue RGB
//  counterpart
// Parameters:
//  n1  - Magic number 1
//  n2  - Magic number 2
//  hue - The Hue value
// Returns   :
//  HSLCOLOR - the HSL Color value
// -------------------------------------------------------------
WORD XSFUNC
XSColor_HueToRGB(WORD n1,WORD n2,WORD hue)
{

    // range check: note values passed add/subtract thirds of range
    if (hue < 0)
        hue += HLSMAX;

    if (hue > HLSMAX)
        hue -= HLSMAX;

    // return r,g, or b value from this tridrant
    if (hue < (HLSMAX / 6))
        return (n1 + (((n2 - n1) * hue + (HLSMAX / 12)) / (HLSMAX / 6)) );
    if (hue < (HLSMAX / 2))
        return (n2 );
    if (hue < ((HLSMAX * 2) / 3))
        return (n1 + (((n2 - n1) * (((HLSMAX * 2) / 3) - hue) +
        (HLSMAX / 12)) / (HLSMAX / 6)));
   else
      return ( n1 );
}

// -------------------------------------------------------------
// Function  :
//  XSColor_HLStoRGB
// Purpose   :
//  Converts an HSL Color value to it's RGB Color value
//  counterpart
// Parameters:
//  hslColor - The HSL Color value to convert to an RGB Color
//             value
// Returns   :
//  COLORREF - the RGB Color value
// -------------------------------------------------------------
COLORREF XSFUNC
XSColor_HLStoRGB(HSLCOLOR hslColor)
{

    WORD R, G, B;         // RGB component values
    WORD Magic1, Magic2;  // calculated magic numbers (really!)
    WORD H, S, L;         // HSL component values

    // get R, G, and B out of DWORD
    H = GetHValue(hslColor);
    S = GetSValue(hslColor);
    L = GetLValue(hslColor);

    if (S == 0)
    {                     // achromatic case
        R = G = B = (L * RGBMAX) / HLSMAX;
        if (H != UNDEFINED)
        {
            // ERROR
        }
    }
    else
    {                    // chromatic case
        // set up magic numbers
        if (L <= (HLSMAX / 2))
            Magic2 = (L * (HLSMAX + S) + (HLSMAX / 2)) / HLSMAX;
        else
            Magic2 = L + S - ((L * S) + (HLSMAX / 2)) / HLSMAX;

        Magic1 = 2 * L - Magic2;

        // get RGB, change units from HLSMAX to RGBMAX
        R = (XSColor_HueToRGB(Magic1, Magic2, H + (HLSMAX / 3)) * RGBMAX +
            (HLSMAX / 2)) / HLSMAX;
        G = (XSColor_HueToRGB(Magic1, Magic2, H) * RGBMAX +
            (HLSMAX / 2)) / HLSMAX;
        B = (XSColor_HueToRGB(Magic1, Magic2, H - (HLSMAX / 3)) * RGBMAX +
            (HLSMAX / 2)) / HLSMAX;
    }

   return(RGB(R, G, B));
}

// -------------------------------------------------------------
// Function  :
//  XSPaint_Rect
// Purpose   :
//  Paint a RECT within a DC the passed color
// Parameters:
//  CDC* pDC - The frame (or window) that is to have
//  int x - the left side of the RECT
//  int y - the top of the RECT
//  int w - the width of the rect
//  int h - the height of the RECT
//  COLORREF color - the color to paint with
// Returns   :
// TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL XSFUNC
XSPaint_Rect(CDC* pDC, int x, int y, int w, int h, COLORREF color)
{
    BOOL bResult = FALSE;

    // Create the brush and select it into the DC
    CBrush brush(color);
    CBrush* pOldBrush = pDC->SelectObject(&brush);

    // Paint according to the passed dimensions
    bResult = pDC->PatBlt(x, y, w, h, PATCOPY);

    // Set the old brush back
    pDC->SelectObject(pOldBrush);

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//  XSCaption_SetText
// Purpose   :
//  Paint a RECT within a DC the passed color
// Parameters:
//  CDC* pDC - The frame (or window) that is to have
//  CRect rect - the RECT of the area to paint
//  COLORREF color - the color to paint with
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL XSFUNC
XSPaint_Rect(CDC* pDC, CRect rect, COLORREF color)
{
    return ::XSPaint_Rect(pDC, rect.left, rect.top, rect.Width(),
        rect.Height(), color);
}

// -------------------------------------------------------------
// Function  :
//  XSPaint_Gradient
// Purpose   :
//  Draws a gradient from right to left of the color to black
// Parameters:
//  CDC* pDC - The DC to paint into
//  CRect& rcRect - The RECT to paint
//  COLORREF crColor - The color to use
//  int nGradFills - The number of gradients to use
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL XSFUNC
XSPaint_Gradient(CDC* pDC, CRect& rcRect, COLORREF crColor,
                 int nGradFills)
{
    ASSERT(pDC);
    ASSERT(nGradFills >= 1);

    BOOL bResult = FALSE;

    // Do this if we're doing a single color
    if (1 == nGradFills)
    {
        if (::XSPaint_Rect(pDC, 0, 0, rcRect.Width(),
            rcRect.Height(), crColor))
            bResult = TRUE;
    }
    else
    {
        // Get Red, Green, and Blue color values
        int r = GetRValue(crColor);
        int g = GetGValue(crColor);
        int b = GetBValue(crColor);

        // start 5/6 of the way right
        int x = 5 * rcRect.right / 6;

        // width of area to shade
        int w = x - rcRect.left;

        // height of area to shade
        int h = rcRect.Height();

        // width of one shade band
        int xDelta= max(w / nGradFills, 1);

        // Paint far right 1/6 of caption the background color
        ::XSPaint_Rect(pDC, x, 0, rcRect.right - x, h, crColor);

        // Compute new color brush for each band from
        // x to x + xDelta.
        // Excel uses a linear algorithm from black to normal:
        //
        //  color = crColor * r
        //
        // where r is the ratio x/w, which ranges from 0
        // (x = 0, left) to 1 (x=w, right). This results in a
        // mostly black title bar, since we humans don't
        // distinguish dark colors as well as light ones. So
        // instead, I use the formula:
        //
        //  color = crColor * [1-(1-r)^2]
        //
        // which still equals black when r = 0 and crColor when
        // r = 1, but spends more time near crColor. For
        // example, when r = .5, the multiplier is
        // [1 - (1 - .5) ^ 2] = .75, closer to 1 than .5.
        // I leave the algebra to the reader to verify that the
        // above formula is equivalent to
        //
        //  color = crColor - (crColor * (w - x) * (w - x)) / (w * w)

        // paint bands right to left
        while (x > xDelta)
        {
            // next band
            x -= xDelta;

            // w minus x squared
            int wmx2 = (w - x) * (w - x);

            // w squared
            int w2  = w * w;

            // Paint it
            ::XSPaint_Rect(pDC, x, 0, xDelta, h,
                RGB(r - (r * wmx2) / w2,
                    g - (g * wmx2) / w2,
                    b - (b * wmx2) / w2));
        }

        // Paint whatever is left black
        ::XSPaint_Rect(pDC, 0, 0, x, h, COLOR_BLACK);

        bResult = TRUE;
    }

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//  XSCaption_SetText
// Purpose   :
//  Changes the text of the passed HWND
// Parameters:
//  HWND hwnd - The frame (or window) that is to have its text
//		changed
//  LPCTSTR lpText - The text to change to
//  BOOL bRedraw - TRUE to redraw the text
//                 FALSE to not repaint immediately
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL XSFUNC
XSCaption_SetText(HWND hwnd, LPCTSTR lpText, BOOL bRedraw)
{
    // Turn off WS_VISIBLE if necessary to avoid painting
    DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);

    // If this HWND has no caption, then return
    if (!(dwStyle & WS_CAPTION))
        return FALSE;

    if (!bRedraw)
    {
        if (dwStyle & WS_VISIBLE)
            ::SetWindowLong(hwnd, GWL_STYLE,
            (dwStyle & ~WS_VISIBLE));
    }

    // Call DefWindowProc directly to set internal window text
    DefWindowProc(hwnd, WM_SETTEXT, 0, (LPARAM)lpText);

    if (!bRedraw)
    {
        if (dwStyle & WS_VISIBLE)
            ::SetWindowLong(hwnd, GWL_STYLE, dwStyle);
    }

    return TRUE;
}

