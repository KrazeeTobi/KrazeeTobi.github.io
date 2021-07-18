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

#if !defined(AFX_XSRECT_H__C1FAE059_43D4_11D1_8754_006097727DCB__INCLUDED_)
#define AFX_XSRECT_H__C1FAE059_43D4_11D1_8754_006097727DCB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------
// Mini-class to act as a base class for CXSClientRect, 
// CXSWindowRect, and CXSCaptionRect
class XSCLASS
CXSRect : public CRect 
{
public:
	CXSRect();

    CXSRect& ToWindow();
    CXSRect& ToWindow(const CWnd& wnd);
    CXSRect& ToClient();
    CXSRect& ToClient(const CWnd& wnd);

protected:
    const CWnd* m_pWnd;

protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSRect);
};

// -------------------------------------------------------------
// Mini-class to get the rectangle of a window in client 
// coordinates
class XSCLASS
CXSClientRect : public CXSRect
{
public:
    // use reference to deny NULL ptr
	CXSClientRect(const CWnd& wnd);

protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSClientRect);
};

// -------------------------------------------------------------
// Mini-class to get the rectangle of a window in screen 
// coordinates
class XSCLASS
CXSWindowRect : public CXSRect
{
public:
    // use reference to deny NULL ptr
	CXSWindowRect(const CWnd& wnd);

protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSWindowRect);
};

// -------------------------------------------------------------
// Mini-class to get the caption rectangle of a window in 
// window coordinates.  This is the area of the title bar inside
// the window frame.
class XSCLASS
CXSCaptionRect : public CXSRect
{
public:
    // use reference to deny NULL ptr
	CXSCaptionRect(const CWnd& wnd);

protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSCaptionRect);
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_XSRECT_H__C1FAE059_43D4_11D1_8754_006097727DCB__INCLUDED_)
