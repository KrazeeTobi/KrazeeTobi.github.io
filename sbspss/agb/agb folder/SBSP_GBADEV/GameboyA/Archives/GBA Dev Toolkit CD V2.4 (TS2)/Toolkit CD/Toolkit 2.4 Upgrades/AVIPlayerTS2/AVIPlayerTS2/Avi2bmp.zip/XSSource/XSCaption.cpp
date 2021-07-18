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

#if 0
#include "XSMisc.h"
#include "XSRect.h"
#include "XSPalette.h"
#include "XSDibApi.h"
#include "XSBitmap.h"
#include "XSSubWndCtrl.h"
#include "XSNotify.h"
#include "XSObject.h"
#include "XSBgCtrl.h"
#include "XSCaption.h"
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXSCaption, CXSBgCtrl)

// -------------------------------------------------------------
// Function  :
//    CXSCaption::CXSCaption
// Purpose   :
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSCaption::CXSCaption()
{
    m_crColor[0] = ::GetSysColor(COLOR_INACTIVECAPTION);
    m_crColor[1] = ::GetSysColor(COLOR_ACTIVECAPTION);
    m_nGradFills = 1;
    m_nBackgroundType = BackgroundNormal;
}

// -------------------------------------------------------------
// Function  :
//     CXSCaption::~CXSCaption
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSCaption::~CXSCaption()
{
}

// -------------------------------------------------------------
// Function  :
//    CXSCaption::DoInstall
// Purpose   :
//    Installs the CXSCaption instance as the handler for the
//    passed CWnd pointer
// Parameters:
//    CWnd* pWnd - The CWnd to attach to
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSCaption::DoInstall(CWnd* pWnd)
{
    // Types this class can into install into
    if (!pWnd->IsKindOf(RUNTIME_CLASS(CWnd)) &&
        !pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)) &&
        !pWnd->IsKindOf(RUNTIME_CLASS(CDialog)))
    {
        // You are trying to install the wrong type!
        ASSERT(FALSE);
        return FALSE;
    }

    return SubclassWindow(pWnd);
}

// -------------------------------------------------------------
// Function  :
//    CXSCaption::DoInvalidate
// Purpose   :
//    Invalidates the CXSCaption so that the bitmaps are
//    recreated and they are redrawn
// Parameters:
//    None
// Returns   :
//    Nothing
// -------------------------------------------------------------
void
CXSCaption::DoInvalidate()
{
    m_szBackground = CSize(0,0);
    DoGetWnd()->SendMessage(WM_NCPAINT);
}

// -------------------------------------------------------------
// Windows Message Handlers
// -------------------------------------------------------------

// -------------------------------------------------------------
// Function  :
//    CXSCaption::OnNcPaint
// Purpose   :
//    Called when Windows asks for the non-client areas  to be
//    painted.
// Parameters:
//    HRGN hRgn - region that needs repainting
// Returns   :
//    Nothing
// -------------------------------------------------------------
BOOL
CXSCaption::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    HRGN hRgn = (HRGN)wParam;

    // caption rect
    CXSCaptionRect rcDim(*DoGetWnd());

    // Get window cordinates
    CRect rcWin = CXSWindowRect(*DoGetWnd());

    // convert to screen coordinates
    rcDim += rcWin.TopLeft();

    // Don't paint if caption isn't within region to be
    // updated, just do the Default
    if ((WORD)hRgn > 1 && !::RectInRegion(hRgn, &rcDim))
        return FALSE;

    // Exclude caption from update region
    HRGN hRgnCaption = ::CreateRectRgnIndirect(&rcDim);
    HRGN hRgnNew = ::CreateRectRgnIndirect(&rcDim);
    if ((WORD)hRgn > 1)
    {
        // wParam is a valid region - subtract caption bar
        // from it
        ::CombineRgn(hRgnNew, hRgn, hRgnCaption, RGN_DIFF);
    }
    else
    {
        // wParam is not a valid region
        // create a region containing the whole window
        // minus the caption bar
        HRGN hRgnAll = ::CreateRectRgnIndirect(&rcWin);
        ::CombineRgn(hRgnNew, hRgnAll, hRgnCaption, RGN_DIFF);
        ::DeleteObject(hRgnAll);
    }

    // Call windows to do WM_NCPAINT with altered update region
    MSG& msg = AfxGetThreadState()->m_lastSentMsg;
    WPARAM wpSave = msg.wParam;     // save original wParam
    msg.wParam = (WPARAM)hRgnNew;   // set new region
    Default();                      // call normal WM_NCPAINT
    msg.wParam = wpSave;            // restore original wParam

    ::DeleteObject(hRgnCaption);
    ::DeleteObject(hRgnNew);

    DoGetWnd()->SendMessage(WM_PAINT, 0, 0);

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//    CXSCaption::OnNcActivate
// Purpose   :
//    Determines if caption needs to be repainted
// Parameters:
//    BOOL bState - if this is 1, then it is the active state,
//      otherwise if it is 0, then it is the inactive state.
// Returns   :
//    BOOL - TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSCaption::OnNcActivate(WPARAM wParam, LPARAM lParam,
                         LRESULT& lResult)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    BOOL bState = (BOOL)wParam;
    lResult = TRUE;

    // Mimic MFC to stay active if WM_STAYACTIVE bit is on
    if (DoGetWnd()->m_nFlags & WF_STAYACTIVE)
        bState = TRUE;

    // Check to see if window is in inactive state
    if (!DoGetWnd()->IsWindowEnabled())
        bState = FALSE;

    // If this is an MDI app, manually activate/paint active
    // MDI child window, because windows won't do it if parent
    // frame is invisible. MUST do this before calling Default
    // or it will not work.
    if (DoGetWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
    {
        CMDIFrameWnd* pMDIFrame = (CMDIFrameWnd*)m_pWnd;
        CFrameWnd* pFrame = pMDIFrame->GetActiveFrame();
        if (pFrame != pMDIFrame)
        {
            pFrame->SendMessage(WM_NCACTIVATE, bState);
            pFrame->SendMessage(WM_NCPAINT);
        }
    }

    // Turn WS_VISIBLE off before calling DefWindowProc,
    // so DefWindowProc won't paint and thereby cause flicker
    DWORD dwStyle = DoGetWnd()->GetStyle();
    if (dwStyle & WS_VISIBLE)
        ::SetWindowLong(*DoGetWnd(), GWL_STYLE,
            (dwStyle & ~WS_VISIBLE));

    MSG& msg = AfxGetThreadState()->m_lastSentMsg;
    msg.wParam = bState;
    Default();
    if (dwStyle & WS_VISIBLE)
        ::SetWindowLong(*DoGetWnd(), GWL_STYLE, dwStyle);

    // Nothing has happened yet because WS_VISIBLE was
    // turned off.
    // Now it's time to rock'n'roll
    m_bState = bState;                // update the state
    DoGetWnd()->SendMessage(WM_NCPAINT);  // do paint

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSCaption::OnNcHitTest
// Purpose   :
//  To correct a bug in Windows that repaints the caption
//  buttons directly when a WM_NCHITTEST is detected.
// Parameters:
// -------------------------------------------------------------
BOOL
CXSCaption::OnNcHitTest(WPARAM wParam, LPARAM lParam,
                        LRESULT& lResult)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    // Call Default handling
    lResult = Default();

    // Repaint caption because of bug
    DoInvalidate();

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSCaption::OnSetText
// Purpose   :
//  Changes the text of the caption for this dialog
// Parameters:
// -------------------------------------------------------------
BOOL
CXSCaption::OnSetText(WPARAM wParam, LPARAM lParam,
                      LRESULT& lResult)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    LPCTSTR lpText = (LPCTSTR)lParam;

    // Turn WS_VISIBLE off before calling windows to set the
    // text then turn it back on again
    ::XSCaption_SetText(*DoGetWnd(), lpText, FALSE);

    DoInvalidate();   // Set repaint flag

    lResult = TRUE;

    InvalidateWindow();
    DoGetWnd()->SendMessage(WM_PAINT, 0, 0);

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSCaption::DoGetCaptionText
// Purpose   :
//  Gets the caption text of the subclassed window
// Returns   :
//  BOOL - TRUE on success
//       - FALSE on failure
// -------------------------------------------------------------
BOOL
CXSCaption::DoGetCaptionText()
{
    CString str;

    // Get the text from the window
    DoGetWnd()->GetWindowText(str);

    m_FontInfo[0].m_str = str;
    m_FontInfo[1].m_str = str;

    // Returning FALSE calls Default()
    return FALSE;
}

// -------------------------------------------------------------
// Function  :
// Purpose   :
// Parameters:
// Returns   :
// -------------------------------------------------------------
BOOL
CXSCaption::OnActivate(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    return CXSBgCtrl::OnActivate(wParam, lParam);

    // Returning FALSE calls Default()
    return FALSE;
}

// -------------------------------------------------------------
// Function  :
// Purpose   :
// Parameters:
// Returns   :
// -------------------------------------------------------------
BOOL
CXSCaption::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    return CXSBgCtrl::OnSetFocus(wParam, lParam);

    // Returning FALSE calls Default()
    return FALSE;
}

// -------------------------------------------------------------
// Function  :
// Purpose   :
// Parameters:
// Returns   :
// -------------------------------------------------------------
BOOL
CXSCaption::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    return CXSBgCtrl::OnKillFocus(wParam, lParam);

    // Returning FALSE calls Default()
    return FALSE;
}

// -------------------------------------------------------------
// Function  :
// Purpose   :
// Parameters:
// Returns   :
// -------------------------------------------------------------
BOOL
CXSCaption::OnEraseBkgnd(WPARAM wParam, LPARAM lParam,
                         LRESULT& lResult)
{
    // Returning FALSE calls Default()
    return FALSE;
}


// -------------------------------------------------------------
// Function  :
//    CXSCaption::DoResetBitmaps
// Purpose   :
//    Sets the bitmaps back to the default.  Uses system colors
//    COLOR_INACTIVECAPTION and COLOR_ACTIVECAPTION.
// Parameters:
//    None
// Returns   :
//    Nothing
// -------------------------------------------------------------
void
CXSCaption::DoResetBitmaps()
{
    // re-initialize attribute info
	m_nBackgroundType   = BackgroundNormal;
	m_crColor[0] = ::GetSysColor(COLOR_INACTIVECAPTION);
	m_crColor[1] = ::GetSysColor(COLOR_ACTIVECAPTION);
    m_nGradFills = 1;

    // initialize bitmaps
    for( int x = 0; x < 2; x++)
        m_bmp[x].DeleteObject();
}

// -------------------------------------------------------------
// Function  :
//    CXSCaption::DoResetFontInfo
// Purpose   :
//    Sets the font info back to the default.
// Parameters:
//    None
// Returns   :
//    Nothing
// -------------------------------------------------------------
void
CXSCaption::DoResetFontInfo()
{
    // initialize font attributes
    for( int x = 0; x < 2; x++)
    {
	    m_FontInfo[x].m_fntCap.DeleteObject();
        m_FontInfo[x].m_crCap = (COLORREF)-1;
	    m_FontInfo[x].m_bBold = TRUE;
	    m_FontInfo[x].m_bItalic = FALSE;
        memset(&m_FontInfo[x].m_lf, 0, sizeof(LOGFONT));
        m_FontInfo[x].m_str = _T("");
    }
}

// -------------------------------------------------------------
// Function  :
//    CXSCaption::ResetAll
// Purpose   :
//    Calls all appropriate reset functions.
// Parameters:
//    None
// Returns   :
//    Nothing
// -------------------------------------------------------------
void
CXSCaption::DoResetAll()
{
    DoResetFontInfo();
    DoResetBitmaps();
}

// -------------------------------------------------------------
// Function  :
//    CXSCaption::SetFonts
// Purpose   :
//    Sets the fonts to be used when painting the caption
// Parameters:
//    CString strActiveFontName - face name of the active font
//    CString strInactiveFontName - face name of the inactive
//      font
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSCaption::DoSetFonts(CString strActiveFontName,
                     CString strInactiveFontName)
{
    // Rest the font information
    DoResetFontInfo();

	// Get current system caption font, just to get its size
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0,
                                &ncm, 0));

    // See if the strings are empty.  If they are, use
    // the default system font for captions
    if (strActiveFontName.IsEmpty())
        strActiveFontName = ncm.lfCaptionFont.lfFaceName;

    if (strInactiveFontName.IsEmpty())
        strInactiveFontName = ncm.lfCaptionFont.lfFaceName;

    // used for getting installed font information
    CFont fnt;

	// Create fonts the same size as caption
    // font, but use passed font name
	fnt.CreatePointFont(120, strInactiveFontName);
    fnt.GetLogFont(&m_FontInfo[0].m_lf);
    fnt.DeleteObject();

	fnt.CreatePointFont(120, strActiveFontName);
    fnt.GetLogFont(&m_FontInfo[1].m_lf);
    fnt.DeleteObject();

    // Set up the default colors for the fonts
    m_FontInfo[0].m_crCap =
        ::GetSysColor(COLOR_INACTIVECAPTIONTEXT);
    m_FontInfo[1].m_crCap =
        ::GetSysColor(COLOR_CAPTIONTEXT);

    // Default caption fonts are bold
    m_FontInfo[0].m_bBold = TRUE;
    m_FontInfo[1].m_bBold = TRUE;

    // Call virtual function so attributes can be changed
    // before font creation by any derived classes
    DoPreCreateFonts();

    // Make the fonts are the same height as caption font
    m_FontInfo[0].m_lf.lfHeight = ncm.lfCaptionFont.lfHeight;
    m_FontInfo[1].m_lf.lfHeight = ncm.lfCaptionFont.lfHeight;

    // Create the fonts
    m_FontInfo[0].m_fntCap.
        CreateFontIndirect(&m_FontInfo[0].m_lf);
    m_FontInfo[1].m_fntCap.
        CreateFontIndirect(&m_FontInfo[1].m_lf);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSCaption::DoPreCreateFonts
// Purpose   : 
//    Creates the fonts to be used for painting the screen.  
//    This virtual function allows a derived class 
//    to modify the defaults.
// Parameters: 
//    None
// Returns   : 
//    BOOL - TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSCaption::DoPreCreateFonts()
{
    // Check for bold attribute
    if (m_FontInfo[0].m_bBold)
        m_FontInfo[0].m_lf.lfWeight |= FW_BOLD;

    if (m_FontInfo[1].m_bBold)
        m_FontInfo[1].m_lf.lfWeight |= FW_BOLD;

    // Check for italic attribute
    m_FontInfo[0].m_lf.lfItalic = m_FontInfo[0].m_bItalic;
    m_FontInfo[1].m_lf.lfItalic = m_FontInfo[1].m_bItalic;

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoDrawBackground
// Purpose   : 
//  This is the actual function that processes the painting of 
//  the caption.  It works as a director, calling the 
//  appropriate functions.  To change the default behavior, 
//  derive this class and provide the appropriate virtual 
//  functions.
// Parameters: 
//  CDC* pDC - Device context to draw on
//  CXSBitmap& bmp - Bitmap to paint in to
//  const CRect& rcDim - RECT of where to paint
// Returns   : TRUE on success
//             FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSCaption::DoDrawBackground(CDC* pDC, CXSBitmap& bmp,
                             CRect& rcDim)
{
    // Select bitmap to draw on to
    CBitmap* pOldBitmap;
    pOldBitmap = pDC->SelectObject(&bmp);

    // Draw onto the bitmap
    DoDrawIcon(pDC);
    DoDrawButtons(pDC);
    DoDrawText(pDC);

    // Done drawing
    pDC->SelectObject(pOldBitmap);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoDrawIcon
// Purpose   : 
//  Draws the Icon on the caption on the specified device 
//  context
// Parameters: 
//  CDC* pDC - Device context to draw on to
// Returns   : TRUE on success
//             FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSCaption::DoDrawIcon(CDC* pDC)
{
    ASSERT(pDC);

    HICON hIcon;
    hIcon = (HICON)::GetClassLong(DoGetWnd()->m_hWnd, 
        GCL_HICONSM);
    if (!hIcon)
        return FALSE;

    DWORD dwExStyle = DoGetWnd()->GetExStyle();
    BOOL bToolWindow = (dwExStyle & WS_EX_TOOLWINDOW);

    // Get caption rect
    CRect rcDim = DoGetBitmapRect(*DoGetWnd());

    // Within the basic button rectangle, Windows uses 
    // a 1 or 2 pixel border.  The Icon has 2 pixel border 
    // on left, 1 pixel on top/bottom, 0 on the right
    int cxIcon = bToolWindow ? ::GetSystemMetrics(SM_CXSMSIZE) : 
        ::GetSystemMetrics(SM_CXSIZE);
        int cyIcon = bToolWindow ? 
            ::GetSystemMetrics(SM_CYSMSIZE) : 
            ::GetSystemMetrics(SM_CYSIZE);

    CRect rc(rcDim.left, rcDim.top, rcDim.left + cxIcon, 
        rcDim.top + cyIcon);
    rc.DeflateRect(0,1);
    rc.left += 2;

    // Get the registered icon and display it
    return ::DrawIconEx(pDC->m_hDC, rc.left, rc.top,
              hIcon, rc.Width(), rc.Height(), 0, NULL, 
              DI_NORMAL);
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoDrawButtons
// Purpose   : 
//  Draws the standard 32-bit Windows buttons (minimize, restore, 
//  close, and help) on the passed device context
// Parameters: 
//  CDC* pDC - Device context to draw on to
// Returns   : TRUE on success
//             FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSCaption::DoDrawButtons(CDC* pDC)
{
    ASSERT(pDC);

    // Get the window style
    DWORD dwStyle = DoGetWnd()->GetStyle();
    DWORD dwExStyle = DoGetWnd()->GetExStyle();
    BOOL bMdiChild = (dwExStyle & WS_EX_MDICHILD);
    BOOL bToolWindow = (dwExStyle & WS_EX_TOOLWINDOW);

    // Get system icon sizes
    int cxIcon = bToolWindow ? ::GetSystemMetrics(SM_CXSMSIZE) : 
        ::GetSystemMetrics(SM_CXSIZE);
    int cyIcon = bToolWindow ? ::GetSystemMetrics(SM_CYSMSIZE) : 
        ::GetSystemMetrics(SM_CYSIZE);

    // Get caption rect
    CRect rcDim = DoGetBitmapRect(*DoGetWnd());

    // Draw caption buttons. These are all drawn inside a 
    // rectangle of dimensions SM_CXSIZE by SM_CYSIZE
    CRect rc(rcDim.right - cxIcon, rcDim.top, 
        rcDim.right, rcDim.top + cyIcon);

    // If the window is a MDI child window in it's iconic
    // state, then the buttons are drawn different then
    // a regular window with a caption
    if (DoGetWnd()->IsIconic() && bMdiChild)
        rc.DeflateRect(1, 1, 1, 3);  // iconic MDI child
    else
        rc.DeflateRect(0, 2, 2, 2);  // regular caption window

    pDC->DrawFrameControl(&rc, DFC_CAPTION, DFCS_CAPTIONCLOSE);

    // Max/restore button is like close box; just shift 
    // rectangle left.  Also does help button, if any.
    BOOL bMaxBox = dwStyle & WS_MAXIMIZEBOX;
    if (bMaxBox || (dwExStyle & WS_EX_CONTEXTHELP)) 
    {
        rc -= CPoint(cxIcon, 0);
        if (DoGetWnd()->IsIconic() && bMdiChild)
        {
            pDC->DrawFrameControl(&rc, DFC_CAPTION,
                bMaxBox ? (DoGetWnd()->IsZoomed() ? 
                DFCS_CAPTIONRESTORE : DFCS_CAPTIONMAX) :
                DFCS_CAPTIONHELP);
        }
        else
        {
            pDC->DrawFrameControl(&rc, DFC_CAPTION,
                bMaxBox ? (DoGetWnd()->IsZoomed() ? 
                DFCS_CAPTIONRESTORE : DFCS_CAPTIONMAX) :
                DFCS_CAPTIONHELP);
        }
    }

    // Minimize button has 2 pixel border on all sides but right.
    if (dwStyle & WS_MINIMIZEBOX) 
    {
        rc -= CPoint(cxIcon-2,0);
        if (DoGetWnd()->IsIconic() && bMdiChild)
            pDC->DrawFrameControl(&rc, DFC_CAPTION, 
            DFCS_CAPTIONRESTORE);
        else
            pDC->DrawFrameControl(&rc, DFC_CAPTION, 
            DFCS_CAPTIONMIN);
    }

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoDrawText
// Purpose   : 
//  Draws the text to be used on the internal bitmaps before 
//  painting them to the caption
// Parameters: 
//  CDC* pDC - The device context on which to draw
// Returns   : TRUE on success
//             FALSE on failure
// -------------------------------------------------------------
BOOL
CXSCaption::DoDrawText(CDC* pDC)
{
    ASSERT(pDC);
    
    // If one is set, they are all set
    if (!m_FontInfo[0].m_fntCap.GetSafeHandle())
        DoSetFonts(); // create default fonts

    // Call virtual function to retrieve text
    // Default function gets regular text
    // Programmer can change this by deriving from virtual 
    // function
    DoGetCaptionText();

    // Get caption rect
    CRect rcDim = DoGetBitmapRect(*DoGetWnd());

    // Shift away from the border
    rcDim.left += 3;

    HICON hIcon;
    hIcon = (HICON)GetClassLong(DoGetWnd()->m_hWnd, GCL_HICONSM);
    if (hIcon)
    {
        // We want to draw to the right of the icon, not on it
        int cxIcon = GetSystemMetrics(SM_CXSIZE);
        rcDim.left += cxIcon;
    }

    // Now, let's draw the text
    CFont* pOldFont;

    // draw on top of our background
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(m_FontInfo[m_bState].m_crCap);
    pOldFont = pDC->SelectObject(&m_FontInfo[m_bState].
                                 m_fntCap);
    pDC->DrawText(m_FontInfo[m_bState].m_str, &rcDim, 
        DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

    pDC->SelectObject(pOldFont);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::DoGetBitmapRect
// Purpose   : 
//  Gets the dimensions of the needed bitmap
// Parameters: 
//  CWnd& wnd - Reference to a CWnd
// Returns   : 
// -------------------------------------------------------------
CRect
CXSCaption::DoGetBitmapRect(CWnd& wnd)
{
    CXSCaptionRect rcDim(wnd);

    // Normalize the CRect to 0,0 coordinates
    CRect rcTemp = rcDim;
    rcTemp.left -= rcDim.left;
    rcTemp.right -= rcDim.left;
    rcTemp.top -= rcDim.top;
    rcTemp.bottom -= rcDim.top;

    return rcTemp;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoGetPaintRect
// Purpose   : 
//    Virtual function that returns the dimensions in client 
//     coordinates of where to paint.
// Parameters: 
//    CWnd& wnd - Reference to a CWnd
// Returns   : 
//    CRect - The dimensions in client coordinates within the 
//     CWnd to use for painting.
// -------------------------------------------------------------
CRect
CXSCaption::DoGetPaintRect(CWnd& wnd)
{
    return CXSCaptionRect(wnd);
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoGetDC
// Purpose   : 
//  Gets the DC to paint on to
// Parameters: 
//  CWnd& wnd - window to get DC from
// Returns   : 
//  CDC* - pointer to the needed DC.  
// Comments  :
//  Remember to release this DC when you are done with it.
// -------------------------------------------------------------
CDC*
CXSCaption::DoGetDC(CWnd& wnd)
{
    CWindowDC* pDC = new CWindowDC(&wnd);
    return pDC;
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoGetState
// Purpose   : 
//  Returns the state of the passed CWnd
// Parameters: 
//  CWnd& wnd - reference to the window that needs the state 
//  reported
// Returns   : 
//  BOOL - TRUE if the state is active
//       - FALSE if the state is inactive
// -------------------------------------------------------------
BOOL
CXSCaption::DoGetState(CWnd& wnd)
{
    BOOL bState = 1;  // Assume active

    // Child Frames in an MDI app need help knowing what state 
    // they are in...
    if (DoGetWnd()->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)))
    {
        CMDIFrameWnd* pMDIFrame = 
            (CMDIFrameWnd*)((CMDIChildWnd*)DoGetWnd())->
            GetParentFrame();
        if (pMDIFrame)
        {
            CFrameWnd* pFrame = pMDIFrame->GetActiveFrame();
            if (pFrame && pFrame == m_pWnd)
            {
                // This is the active frame, but is the 
                // parent frame
                if (pFrame->GetForegroundWindow() == pMDIFrame)
                {
                    bState = 1;
                }
                else
                {
                    bState = 0;
                }
            }
        }
    }
    else
    {
        bState = CXSBgCtrl::DoGetState(wnd);
    }

    return bState;
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::DoCheckIconic
// Purpose   : 
//  Checks to see if the passed CWnd is in an iconic state.
//  There is no need to draw the background bitmaps if the CWnd
//  is in an iconic state.
// Parameters: 
//  CWnd& wnd - reference to the window that needs the iconic 
//  state reported
// Returns   : 
//  BOOL - TRUE if the window is in an iconic state
//       - FALSE if the window is not in an iconic state
// -------------------------------------------------------------
BOOL
CXSCaption::DoCheckIconic(CWnd& cwnd)
{
    if (DoGetWnd()->IsIconic())
    {
        // EXCEPTION: If it is a MDI child window, 
        // then we do draw it
        if (!(DoGetWnd()->GetExStyle() & WS_EX_MDICHILD))
            return TRUE;
        else
        {
            // Don't draw caption if MDI child is zommed
            if (DoGetWnd()->IsZoomed())
                return TRUE;
            else
                return FALSE;
        }
    }

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaption::OnPaint
// Purpose   : 
//  Calls CXSBgCtrl::Paint in case other painting is needed.
// Parameters: 
// Returns   : 
// Comments  : 
//  This function exists in this class because there
//  are really two painting operations happening here.  The
//  appropriate variables have been set up so that only the
//  caption (title bar) is painted by calling the base class
//  CXSBgCtrl::OnPaint.  However, if we left it at this, then 
//  the rest of the client area of the window would not get 
//  painted.  So, we then return FALSE so that default 
//  processing can finish up what is needed.
// -------------------------------------------------------------
BOOL
CXSCaption::OnPaint(WPARAM wParam, LPARAM lParam)
{
    CXSBgCtrl::OnPaint(wParam, lParam);

    // Provide default processing for client area
    return FALSE;
}