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

#if !defined(AFX_XSBITMAP_H__FD83396D_73B7_11D1_AB26_742502C10000__INCLUDED_)
#define AFX_XSBITMAP_H__FD83396D_73B7_11D1_AB26_742502C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------
// Forward declarations
class CXSPalette;

// -------------------------------------------------------------
// Schema Definition for Serialization
#define XS_DIB_SCHEMA                1

// -------------------------------------------------------------
// Enumerated painting operations
enum PaintType
{
    NormalPaint = 0,
    StretchPaint,
    TransparentPaint,
    TransparentStretchPaint
};


////////////////////////////////////////////////////////////////
// CXSBitmap

//class XSCLASS
class CXSBitmap : public CBitmap
{
    DECLARE_SERIAL(CXSBitmap);

// Construction
public:
                    CXSBitmap();
    virtual         ~CXSBitmap();

    virtual BOOL    DoDeleteObject();

    virtual BOOL    DoAttach(HDIB hDIB, HPALETTE hPal = NULL);

// Attributes
public:
    CXSPalette        m_Palette;
    BITMAP            m_bm;

    CSize            Size();
    DWORD            Width();
    DWORD            Height();

// Operations
public:
    virtual BOOL    DoLoad(CString strFileName);
    virtual BOOL    DoLoad(HINSTANCE hInst, UINT nID);
    virtual BOOL    DoLoad(UINT nID);
    virtual BOOL    DoSave(CString strFileName);

    virtual BOOL    DoPaintNormal(CDC* pDC, CRect rcDest, 
                        BOOL bTile = FALSE);
    virtual BOOL    DoPaintTransparent(CDC* pDC, CRect rcDest, 
                        COLORREF crTransparentColor, 
                        BOOL bTile = FALSE);
    virtual BOOL    DoPaintStretch(CDC* pDC, CRect rcDest);
    virtual BOOL    DoPaintTransparentStretch(CDC* pDC, CRect rcDest, 
                        COLORREF crTransparentColor);

    virtual BOOL    DoPaint(CDC* pDC, int x1, int y1, 
                        int cx1, int cy1, CDC* srcDC, 
                        int x2, int y2, int cx2, int cy2, 
                        DWORD dwROP, PaintType pntType);
    virtual BOOL    DoPaint(CDC* pDC, CRect rcDest, 
                        CDC* srcDC, CRect rcSrc, DWORD dwROP, 
                        PaintType pntType);

    virtual void    DoSerialize(CArchive& ar);

    BOOL            Rotate(BOOL bClockwise);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSBITMAP_H__FD83396D_73B7_11D1_AB26_742502C10000__INCLUDED_)
