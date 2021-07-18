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

//#include "XSSubWndCtrl.h"
//#include "XSNotify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXSNotify, CXSSubWndCtrl)

// -------------------------------------------------------------
// Function  :
//    CXSNotify::CXSNotify
// Purpose   :
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSNotify::CXSNotify() :
    m_pWnd((CWnd*&)m_pSubWnd)
{
    m_pChild = NULL;
}

// -------------------------------------------------------------
// Function  :
//     CXSNotify::~CXSNotify
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSNotify::~CXSNotify()
{
}

// -------------------------------------------------------------
// Function  :
//    CXSNotify::DoInstall
// Purpose   :
//    Installs the CXSNotify instance as the handler for the
//    passed CWnd pointer
// Parameters:
//    CWnd* pParentWnd - The parent CWnd to attach to
//    CWnd* pChild - Child to receive ON_NOTIFY messages
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSNotify::DoInstall(CWnd* pParentWnd, CXSSubWndCtrl* pChild)
{
    ASSERT_KINDOF(CWnd, pParentWnd);
    ASSERT_KINDOF(CXSSubWndCtrl, pChild);
    ASSERT(pParentWnd->m_hWnd);

    m_pChild = pChild;

    if (!DoPreInstall())
        return FALSE;

    BOOL bResult = SubclassWindow(pParentWnd);

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//  CXSNotify::DoPreInstall
// Purpose   :
//  Virtual function to be used by derived classes to have
//  functionality called before the subclassing takes place.
// Parameters:
//  None
// Returns   :
//  BOOL - Return TRUE if DoPreInstall is successful,
//         otherwise return FALSE.
// -------------------------------------------------------------
BOOL
CXSNotify::DoPreInstall()
{
    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//    CXSNotify::DoWindowProc
// Purpose   :
//    The DoWindowProc that is used by the subclasser. This
//    function calls the appropriate member functions that we
//    want for processing based on the received windows
//    messages.
// Parameters:
//    UINT nMsg - The windows message
//    WPARAM wParam - parameter applicable for windows message
//    LPARAM lParam - parameter applicable for windows message
// Returns   :
//    LRESULT - Depends on windows message
// -------------------------------------------------------------
LRESULT
CXSNotify::DoWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch(nMsg)
    {
    case WM_NOTIFY:
        {
            ASSERT_VALID(m_pWnd);

            // Check the validity of the child handler
            // Make sure it hasn't been destroyed
            ASSERT_VALID(m_pChild);
            if (m_pChild && m_pChild->DoGetWnd() &&
                ::IsWindow(m_pChild->DoGetWnd()->m_hWnd))
            {
                // Check to see if the parent<=>child
                // relationship is still valid
                if (m_pChild->DoGetWnd()->GetParent() != m_pWnd)
                    break;

                // Get the Msg
                NMHDR* pNMHDR = (NMHDR*)lParam;
                UINT nMsg = pNMHDR->code;

                // Verify the Notify message is for this control
                UINT nID = ((UINT)(WORD)::GetDlgCtrlID(
                    m_pChild->DoGetWnd()->m_hWnd));
                if (pNMHDR->idFrom != nID)
                    break;

                // If the child handles this message, return TRUE
                if (m_pChild->CallWindowProc(nMsg, 0, lParam))
                    return TRUE;
            }
        }
        break;

    default:
        break;
    }

    // default - call base class
    return CXSSubWndCtrl::DoWindowProc(nMsg, wParam, lParam);
}

