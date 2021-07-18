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

#if !defined(AFX_XSBGCTRL_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
#define AFX_XSBGCTRL_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------
// Enumerated background types
enum BackgroundType
{
    BackgroundNormal = 0,
    BackgroundColor,
    BackgroundGradient,
    BackgroundBitmap,
    BackgroundCustom
};

class XSCLASS
CXSBgCtrl : public CXSObject
{
// Construction
public:
    CXSBgCtrl();
    virtual ~CXSBgCtrl();

    virtual void DoInvalidate();

    // Pass-thru messages
            void InvalidateWindow(BOOL bErase = TRUE);
            void UpdateWindow();


    // Background handling functions
    int         GetBackgroundType();
    
    int         SetNormal();
    
    int         SetColor(COLORREF crActive, COLORREF crInactive);
    void        GetColor(COLORREF& crActive, COLORREF& crInactive);
    COLORREF    GetActiveColor();
    COLORREF    GetInactiveColor();
    
    int         SetGradient(COLORREF crActive, 
                    COLORREF crInactive, int nGradFills);
    int         GetGradientCount();
    
    int         SetBitmaps(HINSTANCE hinst, UINT nActiveID, 
                    UINT nInactiveID, BOOL bTile = TRUE);
    int         SetBitmaps(LPCTSTR lpszActiveFileName, 
                    LPCTSTR lpszInactiveFileName, 
                    BOOL bTile = TRUE);
    
    CXSBitmap&  GetActiveBitmap();
    CXSBitmap&  GetInactiveBitmap();
    
    void        SetButtonBorder(BOOL bBorder = TRUE);
    BOOL        GetButtonBorder();

protected:
    // Background handling functions
    virtual void DoResetBitmaps();
    virtual void DoResetAll();
    
    virtual BOOL DoCreateBackgroundBmp(CDC* pDC, BOOL bState, 
                    CXSBitmap& bmp, CRect& rcDim);

    BOOL         CreateGradientBmp(CDC* pDC, BOOL bState, 
                    CXSBitmap& bmp, CRect& rcDim);
    BOOL         CreateBitmapBmp(CDC* pDC, BOOL bState, 
                    CXSBitmap& bmp, CRect& rcDim);
    virtual BOOL DoCreateCustomBmp(CDC* pDC, BOOL bState, 
                    CXSBitmap& bmp, CRect& rcDim);

    virtual BOOL  DoDrawBackground(CDC* pDC, CXSBitmap& bmp, 
                    CRect& rcDim) { return TRUE; }
    virtual void  DoDrawButtonBorder(CDC* pDC, CXSBitmap& bmp, 
                    CRect rcDim);
    virtual BOOL  DoPaint(CDC* pDC, CXSBitmap& bmp, CRect rcDim);
    virtual CRect DoGetBitmapRect(CWnd& wnd);
    virtual CRect DoGetPaintRect(CWnd& wnd);
    virtual CDC*  DoGetDC(CWnd& wnd);
    virtual BOOL  DoGetState(CWnd& wnd);
    virtual BOOL  DoCheckIconic(CWnd& wnd);

protected:
    // Background handling variables
    CSize        m_szBackground;     // Size of background
    int          m_nBackgroundType;  // Background Type
    CXSBitmap    m_bmpBackground[2]; // Background Bitmaps
    BOOL         m_bState;           // Focus/Active State
    COLORREF     m_crColor[2];       // Color Fill
    int          m_nGradFills;       // Gradients for Color
    CXSBitmap    m_bmp[2];           // Original Bitmaps
    BOOL         m_bTile;            // TRUE=Tile, FALSE=Stretch
    BOOL         m_bButtonBorder;    // Draw a 3-D button Border

protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSBgCtrl);

protected:
    // The message handlers
    virtual BOOL OnActivate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnEraseBkgnd(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnKillFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSysColorChange(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPaletteChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSetFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnPaint(WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_XSBGCTRL_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
