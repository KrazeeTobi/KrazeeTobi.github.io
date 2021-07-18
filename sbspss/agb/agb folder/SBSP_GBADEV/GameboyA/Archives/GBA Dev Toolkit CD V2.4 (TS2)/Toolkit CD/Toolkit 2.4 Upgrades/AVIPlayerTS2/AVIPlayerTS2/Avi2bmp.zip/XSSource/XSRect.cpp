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

//#include "XSRect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CXSRect, CObject);
IMPLEMENT_DYNAMIC(CXSClientRect, CXSRect);
IMPLEMENT_DYNAMIC(CXSWindowRect, CXSRect);
IMPLEMENT_DYNAMIC(CXSCaptionRect, CXSRect);


// -------------------------------------------------------------
// Function  :
//  CXSRect::CXSRect
// Purpose   :
//  To act as a base class for CXSClientRect, CXSWindowRect,
//  and CXSCaptionRect
// -------------------------------------------------------------
CXSRect::CXSRect()
{
    m_pWnd = NULL;
}

// -------------------------------------------------------------
// Function  :
//  CXSRect::ToWindow
// Purpose   :
//  Converts the current RECT dimensions to Screen coordinates
//  based on the stored m_pWnd.
// Parameters:
//  None
// Returns   :
//  Reference to this
// -------------------------------------------------------------
CXSRect&
CXSRect::ToWindow()
{
    ASSERT(m_pWnd);
    ASSERT(::IsWindow(*m_pWnd));

    m_pWnd->ClientToScreen(this);
    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSRect::ToWindow
// Purpose   :
//  Converts the current RECT dimensions to Screen coordinates.
// Parameters:
//  CWnd wnd - The CWnd to use as a base in converting to
//  screen coords
// Returns   :
//   Reference to this
// -------------------------------------------------------------
CXSRect&
CXSRect::ToWindow(const CWnd& wnd)
{
    ASSERT(::IsWindow(wnd));

    wnd.ClientToScreen(this);
    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSRect::ToClient
// Purpose   :
//  Converts the current RECT dimensions to client coordinates.
//  based on the stored m_pWnd.
// Parameters:
//  None
// Returns   :
//  Reference to this
// -------------------------------------------------------------
CXSRect&
CXSRect::ToClient()
{
    ASSERT(m_pWnd);
    ASSERT(::IsWindow(*m_pWnd));

    m_pWnd->ScreenToClient(this);
    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSRect::ToClient
// Purpose   :
//  Converts the current RECT dimensions to client coordinates.
// Parameters:
//  CWnd wnd - The CWnd to use as a base in converting to
//  client coordinates
// Returns   :
//  Reference to this
// -------------------------------------------------------------
CXSRect&
CXSRect::ToClient(const CWnd& wnd)
{
    ASSERT(::IsWindow(wnd));

    wnd.ScreenToClient(this);
    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSClientRect::CXSClientRect
// Purpose   :
//  To return the client coordinates of the passed CWnd
// Parameters:
//  CWnd wnd - The CWnd for which to get client coordinates
// Returns   :
//  Nothing
// Comments  :
//  Typical usage of this class would be in the following
//  format:
//     CXSRect rect = CXSClientRect(*pWnd);
// -------------------------------------------------------------
CXSClientRect::CXSClientRect(const CWnd& wnd)
{
    ASSERT(::IsWindow(wnd));

    m_pWnd = &wnd;

    // Compute rectangle
    wnd.GetClientRect(this);  // client rect
}

// -------------------------------------------------------------
// Function  :
//  CXSWindowRect::CXSWindowRect
// Purpose   :
//  To return the screen coordinates of the passed CWnd
// Parameters:
//  CWnd wnd - The CWnd for which to get screen coordinates
// Returns   :
//  Nothing
// Comments  :
//  Typical usage of this class would be in the following
//  format:
//     CXSRect rect = CXSWindowRect(*pWnd);
// -------------------------------------------------------------
CXSWindowRect::CXSWindowRect(const CWnd& wnd)
{
    ASSERT(::IsWindow(wnd));

    m_pWnd = &wnd;

    // Compute rectangle
    wnd.GetWindowRect(this);  // window rect
}

// -------------------------------------------------------------
// Function  : 
//  CXSCaptionRect::CXSCaptionRect
// Purpose   : 
//  To return the client coordinates of the caption bar of the
//  passed CWnd
// Parameters: 
//  CWnd wnd - The CWnd for which to get caption bar 
//  coordinates
// Returns   : 
//  Nothing
// Comments  :
//  Typical usage of this class would be in the following 
//  format:
//     CXSRect rect = CXSCaptionRect(*pWnd);
// -------------------------------------------------------------
CXSCaptionRect::CXSCaptionRect(const CWnd& wnd)
{
    ASSERT(::IsWindow(wnd));

    m_pWnd = &wnd;

    // Get size of frame around window
    DWORD dwStyle = wnd.GetStyle();
    ASSERT(dwStyle & WS_CAPTION);
    CSize szFrame = (dwStyle & WS_THICKFRAME) ?
        CSize(::GetSystemMetrics(SM_CXSIZEFRAME),
            ::GetSystemMetrics(SM_CYSIZEFRAME)) :
        CSize(::GetSystemMetrics(SM_CXFIXEDFRAME),
            ::GetSystemMetrics(SM_CYFIXEDFRAME));

    // Compute rectangle
    // ---------------------------------------------------------
    // window rect in screen coordinates
    wnd.GetWindowRect(this);

    // shift origin to (0,0) - makes client coordinates
    *this -= CPoint(left, top);

    left  += szFrame.cx;
    right -= szFrame.cx;
    top   += szFrame.cy;

    // height of caption minus gray shadow border
    bottom = top + ::GetSystemMetrics(SM_CYCAPTION)
        - ::GetSystemMetrics(SM_CYBORDER);
}