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
#include "XSMain.h"


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
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXSBgCtrl, CXSObject)

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::CXSBgCtrl
// Purpose   : 
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSBgCtrl::CXSBgCtrl()
{
    // Set defaults
    m_bState = 1;
    m_bButtonBorder = FALSE;
    m_nBackgroundType = BackgroundNormal;

    // Initialize 
    DoResetAll();
}

// -------------------------------------------------------------
// Function  : 
//     CXSBgCtrl::~CXSBgCtrl
// Purpose   : 
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSBgCtrl::~CXSBgCtrl()
{
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoInvalidate
// Purpose   : 
//    Invalidates the CXSBgCtrlso that the bitmaps are 
//    recreated the next time they are redrawn
// Parameters: 
//    None
// Returns   : 
//    Nothing
// -------------------------------------------------------------
void
CXSBgCtrl::DoInvalidate()
{
    m_szBackground = CSize(0,0); 
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::InvalidateWindow
// Purpose   : 
//  Calls CWnd::Invalidate. Invalidates the entire client area 
//  of CWnd. The client area is marked for painting when the 
//  next WM_PAINT message occurs. The region can also be 
//  validated before a WM_PAINT message occurs by the 
//  ValidateRect or ValidateRgn member function.
// Parameters: 
//  BOOL bErase - TRUE to erase background (default)
//              - FALSE to leave background unchanged
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSBgCtrl::InvalidateWindow(BOOL bErase)
{
    DoGetWnd()->Invalidate(bErase);
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::UpdateWindow
// Purpose   : 
//  Calls CWnd::UpdateWindow. Updates the client area by sending 
//  a WM_PAINT message if the update region is not empty. The 
//  UpdateWindow member function sends a WM_PAINT message 
//  directly, bypassing the application queue. If the update 
//  region is empty, WM_PAINT is not sent.
// Parameters: 
//  None
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSBgCtrl::UpdateWindow()
{
    DoGetWnd()->UpdateWindow();
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::GetBackgroundType
// Purpose   : 
//  Returns the background type in use.
// Parameters: 
//  Nothing
// Returns   : 
//  int - The background type
// -------------------------------------------------------------
int
CXSBgCtrl::GetBackgroundType()
{ 
    return m_nBackgroundType; 
}

// -------------------------------------------------------------
// Windows Message Handlers
// -------------------------------------------------------------

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::OnActivate
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnActivate(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    // Make sure we repaint the background
    DoGetWnd()->InvalidateRect(DoGetPaintRect(*DoGetWnd()));

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::OnEraseBkgnd
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnEraseBkgnd(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    // Don't allow background paints
    lResult = FALSE;
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::OnKillFocus
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    // Make sure we can repaint the background
    DoGetWnd()->InvalidateRect(DoGetPaintRect(*DoGetWnd()));

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::OnSysColorChange
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnSysColorChange(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    // Make sure we repaint the background
    // and recreate the bitmaps
    InvalidateWindow();
    DoInvalidate();
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::OnPaletteChanged
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnPaletteChanged(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    InvalidateWindow();
    DoInvalidate();
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::OnSetFocus
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return FALSE;

    // Make sure we repaint the background
    DoGetWnd()->InvalidateRect(DoGetPaintRect(*DoGetWnd()));

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::OnPaint
// Purpose   : 
//    Paints the desired background type.  If the CWnd is in an
//    iconic state, it calls the default processing handler.
// Parameters: 
//    None
// Returns   : 
//    Nothing
// -------------------------------------------------------------
BOOL
CXSBgCtrl::OnPaint(WPARAM wParam, LPARAM lParam)
{
    // If we're normal, then let Windows/MFC
    // do all of the work
    if (BackgroundNormal == m_nBackgroundType)
        return CXSObject::OnPaint(wParam, lParam);

    // If the window is an icon, no need to paint a background
    if (!DoCheckIconic(*DoGetWnd()))
    {
        // Just call the default handler
        Default();
        return TRUE;
    }

    // Get the window state
    m_bState = DoGetState(*DoGetWnd());

    // Get the window dimensions
    CRect rcBitmap = DoGetBitmapRect(*DoGetWnd());
    CRect rcPaint = DoGetPaintRect(*DoGetWnd());

    // Get background DC
    CDC* pDC = DoGetDC(*DoGetWnd());
    ASSERT(pDC);
    CDC dc;
    dc.CreateCompatibleDC(pDC);
    
    // Are we going to be creating new bitmaps?
    if (rcPaint.Size() != m_szBackground)
    {
        // Invalidate bitmaps
        m_bmpBackground[0].DoDeleteObject();
        m_bmpBackground[1].DoDeleteObject();

        // Set new dimensions
        m_szBackground = rcPaint.Size();
    }

    // Get active/inactive bitmap and determine if 
    // regeneration is required
    CXSBitmap& bmp = m_bmpBackground[m_bState];
    BOOL bPaintIt = TRUE;

    // If the bitmap does not exist, then create one
    if (!bmp.GetSafeHandle())
    {
        bmp.CreateCompatibleBitmap(pDC, rcBitmap.Width(), 
            rcBitmap.Height());

        BOOL bResult = DoCreateBackgroundBmp(&dc, m_bState,
            bmp, rcBitmap);
        ASSERT(bResult);  // problems? Sanity check...

        // Get ImageSize info
        if (bResult)
            bmp.Size();
        else
            bPaintIt = FALSE;
    }

    // If it's OK to paint and we have a valid bitmap, 
    // paint the background, icon, and buttons
    if (bPaintIt && bmp.GetSafeHandle())
    {
        DoDrawBackground(&dc, bmp, rcBitmap);

        // Check to see if we are drawing a button border
        if (m_bButtonBorder)
            DoDrawButtonBorder(&dc, bmp, rcBitmap);

        // Now, paint the background onto the window
        DoPaint(pDC, bmp, rcPaint);
    }

    if (pDC)
        delete pDC;

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoResetBitmaps
// Purpose   : 
//    Sets the bitmaps back to the default.  Uses system color
//    COLOR_WINDOW, which may or may not appropriate for your
//    derived control.
// Parameters: 
//    None
// Returns   : 
//    Nothing
// -------------------------------------------------------------
void 
CXSBgCtrl::DoResetBitmaps()
{
    m_nBackgroundType = BackgroundNormal;
    m_crColor[0] = ::GetSysColor(COLOR_WINDOW);
    m_crColor[1] = ::GetSysColor(COLOR_WINDOW);
    m_nGradFills = 1;

    // initialize bitmaps
    for( int x = 0; x < 2; x++)
        m_bmp[x].DeleteObject();
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoResetAll
// Purpose   : 
//    Calls all appropriate reset functions.
// Parameters: 
//    None
// Returns   : 
//    Nothing
// -------------------------------------------------------------
void 
CXSBgCtrl::DoResetAll()
{
    DoResetBitmaps();
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::SetNormal
// Purpose   : 
//    Sets background to "Normal".  Normal is defined by this
//    class programmatically.  If you really want Normal, as 
//    defined by Windows, then uninstall the handler.
// Parameters: 
//    None
// Returns   : 
//    Nothing
// -------------------------------------------------------------
int 
CXSBgCtrl::SetNormal()
{
    int nOldBGType = m_nBackgroundType;

    // Set background type
    m_nBackgroundType = BackgroundNormal;

    // Invalidate the dimensions, the HWND, and then paint
    DoResetAll();
    DoInvalidate();
    InvalidateWindow();
    UpdateWindow();

    return nOldBGType;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::SetColor
// Purpose   : 
//    Sets background to Color.
// Parameters: 
//    COLORREF crActive - The color to use when active
//    COLORREF crInactive - The color to use when inactive
// Returns   : 
//    int - The previous caption type
// -------------------------------------------------------------
int 
CXSBgCtrl::SetColor(COLORREF crActive, 
                     COLORREF crInactive)
{
    int nOldBGType = SetGradient(crActive, crInactive, 1);

    // Set background type
    m_nBackgroundType = BackgroundColor;

    return nOldBGType;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::GetColor
// Purpose   : 
//    Gets active and inactive background colors.
// Parameters: 
//    COLORREF& crActive - The color used when active
//    COLORREF& crInactive - The color used when inactive
// Returns   : 
//    int - The previous caption type
// -------------------------------------------------------------
void
CXSBgCtrl::GetColor(COLORREF& crActive, COLORREF& crInactive)
{ 
    crActive = m_crColor[1]; 
    crInactive = m_crColor[0]; 
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::GetActiveColor
// Purpose   : 
//    Gets active background color
// Parameters: 
//    None
// Returns   : 
//    COLORREF - The active color
// -------------------------------------------------------------
COLORREF
CXSBgCtrl::GetActiveColor()
{ 
    return m_crColor[1];
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::GetInactiveColor
// Purpose   : 
//    Gets inactive background color
// Parameters: 
//    None
// Returns   : 
//    COLORREF - The inactive color
// -------------------------------------------------------------
COLORREF
CXSBgCtrl::GetInactiveColor()
{ 
    return m_crColor[0];
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::SetGradient
// Purpose   : 
//    Sets background to Gradient.  The passed color is used to
//    create a gradient from color to black, right to left.
// Parameters: 
//    COLORREF crActive - The color to use when active
//    COLORREF crInactive - The color to use when inactive
//    int nGradFills - The number of gradients to use.
// Returns   : 
//    int - The previous caption type
// -------------------------------------------------------------
int 
CXSBgCtrl::SetGradient(COLORREF crActive, 
                        COLORREF crInactive, 
                        int nGradFills)
{
    ASSERT(crActive >= 0 && crActive <= RGB(255,255,255));

    int nOldBGType = GetBackgroundType();

    // Reset bitmaps
    DoResetBitmaps();

    // Set background type
    m_nBackgroundType = BackgroundGradient;

    // Set color options
    m_crColor[0] = crInactive;
    m_crColor[1] = crActive;
    m_nGradFills = nGradFills;

    // Invalidate the dimensions, the HWND, and then paint
    DoInvalidate();
    InvalidateWindow();
    UpdateWindow();

    return nOldBGType;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::GetGradientCount
// Purpose   : 
//  Returns the number of gradients in use when background type 
//  is of type BackgroundGradient.
// Parameters: 
//  Nothing
// Returns   : 
//  int - The number of gradients
// -------------------------------------------------------------
int
CXSBgCtrl::GetGradientCount()
{ 
    return m_nGradFills; 
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::SetBitmaps
// Purpose   : 
//    Sets background to Bitmaps.
// Parameters: 
//    HINSTANCE hinst - HINSTANCE of the resources
//    UINT nActiveID - The bitmap to use when active
//    UINT nInactiveID - The bitmap to use when inactive
//    BOOL bTile - TRUE if the bitmaps should be tile
//               - FALSE if the bitmaps should be stretched
// Returns   : 
//    int - The previous caption type, -1 on error
// -------------------------------------------------------------
int 
CXSBgCtrl::SetBitmaps(HINSTANCE hinst, UINT nActiveID, 
                       UINT nInactiveID, BOOL bTile)
{
    int nOldBGType = GetBackgroundType();

    // Reset bitmaps
    DoResetBitmaps();

    // Set background type
    m_nBackgroundType = BackgroundBitmap;

    // Load bitmaps
    if (!m_bmp[0].DoLoad(hinst, nInactiveID))
        return -1;
    
    if (!m_bmp[1].DoLoad(hinst, nActiveID))
    {
        m_bmp[0].DoDeleteObject();
        return -1;
    }
 
    // Set tile options
    m_bTile = bTile;

    // Invalidate the dimensions, the HWND, and then paint
    DoInvalidate();
    InvalidateWindow();
    UpdateWindow();

    return nOldBGType;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::SetBitmaps
// Purpose   : 
//    Sets background to Bitmaps.
// Parameters: 
//    LPCTSTR lpszActiveFileName - The bitmap file to use when 
//     active.
//    LPCTSTR lpszInactiveFileName - The bitmap file to use 
//     when inactive
//    BOOL bTile - TRUE if the bitmaps should be tiled
//               - FALSE if the bitmaps should be stretched
// Returns   : 
//    int - The previous caption type, -1 on error
//    This function does not verify that the files exist.
// -------------------------------------------------------------
int 
CXSBgCtrl::SetBitmaps(LPCTSTR lpszActiveFileName, 
                      LPCTSTR lpszInactiveFileName, 
                      BOOL bTile)
{
    int nOldBGType = GetBackgroundType();

    // Reset bitmaps
    DoResetBitmaps();

    // Set background type
    m_nBackgroundType = BackgroundBitmap;

    // Load bitmaps
    if (!m_bmp[0].DoLoad(lpszInactiveFileName))
        return -1;

    if (!m_bmp[1].DoLoad(lpszActiveFileName))
    {
        m_bmp[0].DoDeleteObject();
        return -1;
    }

    // Set tile options
    m_bTile = bTile;

    // Invalidate the dimensions, the HWND, and then paint
    DoInvalidate();
    InvalidateWindow();
    UpdateWindow();

    return nOldBGType;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::GetActiveBitmap
// Purpose   : 
//  Returns a reference to the active bitmap
// Parameters: 
//  None
// Returns   : 
//  CXSBitmap& - The active bitmap
// -------------------------------------------------------------
CXSBitmap&
CXSBgCtrl::GetActiveBitmap()
{ 
    return m_bmp[1]; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::GetInactiveBitmap
// Purpose   : 
//  Returns a reference to the inactive bitmap
// Parameters: 
//  None
// Returns   : 
//  CXSBitmap& - The inactive bitmap
// -------------------------------------------------------------
CXSBitmap&
CXSBgCtrl::GetInactiveBitmap()
{ 
    return m_bmp[0]; 
}
    
// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::SetButtonBorder
// Purpose   : 
//  Turns button border use on or off
// Parameters: 
//  BOOL bBorder - TRUE to turn on button border (default)
//               - FALSE to turn off button border
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSBgCtrl::SetButtonBorder(BOOL bBorder) 
{ 
    m_bButtonBorder = bBorder; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::GetButtonBorder
// Purpose   : 
//  Returns the BOOL determing if ButtonBorder is in use.
// Parameters: 
//  None
// Returns   : 
//  BOOL - TRUE if use button border is turned on
//       - FALSE if button border is off
// -------------------------------------------------------------
BOOL
CXSBgCtrl::GetButtonBorder() 
{ 
    return m_bButtonBorder; 
}


// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoCreateBackgroundBmp
// Purpose   : 
//    Creates the background bitmap by calling the appropriate
//    function to create the background type.
// Parameters: 
//    CDC* pDC - DC to use for painting
//    BOOL bActive - determines which active state to draw.
//     0 for inactive state, 1 for active state
//    CXSBitmap& bmp - The bitmap to receive the end result of
//     the paint
//    CRect& rcDim - the dimensions of what to paint
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBgCtrl::DoCreateBackgroundBmp(CDC* pDC, BOOL bActive, 
                                 CXSBitmap& bmp, CRect& rcDim)
{
    switch(m_nBackgroundType)
    {
    case BackgroundNormal:
    case BackgroundColor:
    case BackgroundGradient:
        return CreateGradientBmp(pDC, bActive, bmp, rcDim);
    case BackgroundBitmap:
        return CreateBitmapBmp(pDC, bActive, bmp, rcDim);
    case BackgroundCustom:
        return DoCreateCustomBmp(pDC, bActive, bmp, rcDim);
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::CreateGradientBmp
// Purpose   : 
//    Paints a bitmap with a gradient.  If m_nGradFills == 1,
//    then the color will be solid.
// Parameters: 
//    CDC* pDC - DC to use for painting
//    BOOL bActive - determines which active state to draw.
//     0 for inactive state, 1 for active state
//    CXSBitmap& bmp - The bitmap to receive the end result of
//     the paint
//    CRect& rcDim - the dimensions of what to paint
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBgCtrl::CreateGradientBmp(CDC* pDC, BOOL bActive, 
                             CXSBitmap& bmp, CRect& rcDim)
{
    ASSERT(bmp.GetSafeHandle());
    ASSERT(m_nGradFills >= 1);
    ASSERT(pDC);

    BOOL bResult; 

    // Select the bitmap into the DC so it gets painted on
    CBitmap* pOldBitmap = pDC->SelectObject(&bmp);

    // Select the main color to be used for the caption
    COLORREF crBG = m_crColor[0 != bActive];

    // Paint the bitmap
    bResult = ::XSPaint_Gradient(pDC, rcDim, crBG, m_nGradFills);

    // Select old bitmap back into DC
    pDC->SelectObject(pOldBitmap);

    return bResult;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::CreateBitmapBmp
// Purpose   : 
//    Creates the background bitmap by using a DDB.  If the DDB
//    is smaller than rcDim and m_bTile == TRUE, the bitmap is 
//    tiled, otherwise it is stretched.
// Parameters: 
//    CDC* pDC - DC to use for painting
//    BOOL bActive - determines which active state to draw.
//     0 for inactive state, 1 for active state
//    CXSBitmap& bmp - The bitmap to receive the end result of
//     the paint
//    CRect& rcDim - the dimensions of what to paint
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSBgCtrl::CreateBitmapBmp(CDC* pDC, BOOL bActive, 
                           CXSBitmap& bmp, CRect& rcDim)
{
    ASSERT(pDC);
    ASSERT(bmp.GetSafeHandle());
    
    // Make sure the bitmaps are available
    ASSERT(m_bmp[0].GetSafeHandle() && 
        m_bmp[1].GetSafeHandle());

    // Draw the holder bitmaps to the caption bitmaps
    CDC dc;
    dc.CreateCompatibleDC(pDC);
    CBitmap* pOldBitmap = dc.SelectObject(&bmp);

    // Paint the bitmap
    m_bmp[bActive].DoPaintNormal(&dc, CRect(0, 0, rcDim.Width(), 
        rcDim.Height()), m_bTile);

    // Select old bitmap back into DC
    dc.SelectObject(pOldBitmap);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoCreateCustomBmp
// Purpose   : 
//    Virtual function that allows a derived class to paint a
//    custom background bitmap.
// Parameters: 
//    CDC* pDC - DC to use in painting the border
//    BOOL bState -
//    CXSBitmap& bmp - The bitmap to receive the end result of
//     the paint
//    CRect rcDim - dimensions of where to paint the bitmap
//     within the DC
// Returns   : 
//    Nothing
// -------------------------------------------------------------
BOOL 
CXSBgCtrl::DoCreateCustomBmp(CDC* pDC, BOOL bState, 
                             CXSBitmap& bmp, CRect& rcDim)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::OnDrawButtonBorder
// Purpose   : 
//    Virtual function that paints a border to create a 3D or
//    button-type look.  Uses white for the top and left, black 
//    for the bottom and right.
// Parameters: 
//    CDC* pDC - DC to use in painting the border
//    CXSBitmap& bmp - The bitmap to receive the end result of
//     the paint
//    CRect rect - dimensions of where to paint the border 
//     within the DC
// Returns   : 
//    Nothing
// -------------------------------------------------------------
void
CXSBgCtrl::DoDrawButtonBorder(CDC* pDC, CXSBitmap& bmp, 
                              CRect rcDim)
{
    ASSERT_VALID(pDC);

    // Select the bitmap into the DC so it gets painted on
    CBitmap* pOldBitmap = pDC->SelectObject(&bmp);

    // Paint the Border
    pDC->Draw3dRect(rcDim, RGB(255,255,255), RGB(0,0,0));

    // Select old bitmap back into DC
    pDC->SelectObject(pOldBitmap);
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoPaint
// Purpose   : 
//    Paints the background to the window
// Parameters: 
//    CDC* pDC - DC to use in painting the border
//    CXSBitmap& bmp - The bitmap to receive the end result of
//     the paint
//    CRect rect - dimensions of where to paint the border 
//     within the DC
// Returns   : 
//    Nothing
// -------------------------------------------------------------
BOOL
CXSBgCtrl::DoPaint(CDC* pDC, CXSBitmap& bmp, CRect rcDim)
{
    return bmp.DoPaintNormal(pDC, rcDim, FALSE);
}

// -------------------------------------------------------------
// Function  : 
//    CXSBgCtrl::DoGetBitmapRect
// Purpose   : 
//    Virtual function that returns the dimensions of the needed
//     bitmap dimensions.
// Parameters: 
//    CWnd& wnd - Reference to a CWnd
// Returns   : 
//    CRect - The dimensions of the needed bitmap size
// -------------------------------------------------------------
CRect
CXSBgCtrl::DoGetBitmapRect(CWnd& wnd)
{
    return CXSClientRect(wnd);
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
CXSBgCtrl::DoGetPaintRect(CWnd& wnd)
{
    return CXSClientRect(wnd);
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::DoGetDC
// Purpose   : 
//  Virtual function to return the DC for painting
// Parameters: 
//  CWnd& wnd - reference to the window that will be used for 
//  painting operations
// Returns   : 
//  CDC* - pointer to the requested device context
// -------------------------------------------------------------
CDC*
CXSBgCtrl::DoGetDC(CWnd& wnd)
{
    CPaintDC* pDC = new CPaintDC(&wnd);
    return pDC;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::DoGetState
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
CXSBgCtrl::DoGetState(CWnd& wnd)
{
    BOOL bState = 1;

    // Find out what state the CWnd is in.  For a CWnd that is 
    // the active window, or has focus, the state = 1, 
    // otherwise state = 0
    CWnd* pWnd = DoGetWnd()->GetFocus();
    if (pWnd->GetSafeHwnd() == DoGetWnd()->GetSafeHwnd())
        bState = 1;
    else
    {
        // It didn't have focus, so check to see if this CWnd
        // is the active window
        pWnd = DoGetWnd()->GetActiveWindow();

        if (pWnd->GetSafeHwnd() == DoGetWnd()->GetSafeHwnd())
            bState = 1;
        else
            bState = 0;
    }

    return bState;
}

// -------------------------------------------------------------
// Function  : 
//  CXSBgCtrl::DoCheckIconic
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
CXSBgCtrl::DoCheckIconic(CWnd& wnd)
{
    if (DoGetWnd()->IsIconic())
    {
        return FALSE;
    }

    return TRUE;
}