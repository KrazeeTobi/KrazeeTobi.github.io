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

#if !defined(AFX_XSCAPTION_H__3B0B0700_ECB1_11D1_AB25_54AB02C10000__INCLUDED_)
#define AFX_XSCAPTION_H__3B0B0700_ECB1_11D1_AB25_54AB02C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class XSCLASS
CXSCaption : public CXSBgCtrl
{
// Construction
public:
	             CXSCaption();
	virtual      ~CXSCaption();

    virtual BOOL DoInstall(CWnd* pWnd);
    virtual void DoInvalidate();

protected:
    virtual BOOL OnNcPaint(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnNcActivate(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnNcHitTest(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnSetText(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnActivate(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnSetFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnKillFocus(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnEraseBkgnd(WPARAM wParam, LPARAM lParam, 
        LRESULT& lResult);
    virtual BOOL OnPaint(WPARAM wParam, LPARAM lParam);

    // font info
    struct _fontInfo
    {
        CFont           m_fntCap;
        COLORREF        m_crCap;
        BOOL            m_bBold;
        BOOL            m_bItalic;
        LOGFONT         m_lf;
        CString         m_str;
    } m_FontInfo[2];  // (inactive/active state)


public:
    virtual BOOL DoSetFonts(CString strActiveFontName = _T(""),
                            CString strInactiveFontName = _T(""));

protected: 
    virtual void DoResetFontInfo();
    virtual void DoResetBitmaps();
    virtual void DoResetAll();

    virtual CRect DoGetBitmapRect(CWnd& wnd);
    virtual CRect DoGetPaintRect(CWnd& wnd);
    virtual CDC*  DoGetDC(CWnd& wnd);
    virtual BOOL  DoGetState(CWnd& wnd);
    virtual BOOL  DoCheckIconic(CWnd& cwnd);

    virtual BOOL DoDrawBackground(CDC* pDC, CXSBitmap& bmp, 
        CRect& rcDim);
    virtual BOOL DoDrawIcon(CDC* pDC);
    virtual BOOL DoDrawButtons(CDC* pDC);
    virtual BOOL DoPreCreateFonts();
    virtual BOOL DoDrawText(CDC* pDC);
    virtual BOOL DoGetCaptionText();

    // create from serialization only
    DECLARE_DYNCREATE(CXSCaption);
};

#endif // !defined(AFX_XSCAPTION_H__3B0B0700_ECB1_11D1_AB25_54AB02C10000__INCLUDED_)
