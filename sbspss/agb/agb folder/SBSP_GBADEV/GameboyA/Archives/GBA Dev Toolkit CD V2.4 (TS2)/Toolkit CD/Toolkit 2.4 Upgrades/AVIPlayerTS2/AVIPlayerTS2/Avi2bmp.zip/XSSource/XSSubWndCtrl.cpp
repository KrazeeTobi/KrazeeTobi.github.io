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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--------------------------------------------------------------
// Register global messages
const UINT WM_SETPARENTNOTIFY = ::RegisterWindowMessage(_T("WM_SETPARENTNOTIFY"));
const UINT WM_PRENCDESTROY    = ::RegisterWindowMessage(_T("WM_PRENCDESTROY"));

IMPLEMENT_DYNAMIC(CXSSubWndCtrl, CWnd);

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrl::CXSSubWndCtrl
// Purpose   :
//    Constructor, initializes memory
//--------------------------------------------------------------
CXSSubWndCtrl::CXSSubWndCtrl()
{
    m_pNext = NULL;
    m_pOldWndProc = NULL;
    m_pSubWnd = NULL;
    m_pWindow = NULL;
}

// -------------------------------------------------------------
// Function  :
//    CXSSubWndCtrl::~CXSSubWndCtrl
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSSubWndCtrl::~CXSSubWndCtrl()
{
    ASSERT(m_pSubWnd == NULL);
    ASSERT(m_pOldWndProc==NULL);

    // Clean up any allocated memory
    if (m_pWindow)
    {
        // Because we "attached" the HWND to the CWnd,
        // we "detach" it when we're done with it
        m_pWindow->Detach();
        delete m_pWindow;
    }
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrl::SubclassWindow
// Purpose   :
//    Subclasses a window procedure.  This function installs a
//    new window proc that directs messages to the
//    CXSSubWndCtrl.
// Parameters:
//    CWnd* pWnd - window to subclass
// Returns   :
//    BOOL - TRUE on success, FALSE on failue
// Comments  :
//    Set pWnd = NULL to remove (uninstall) the subclassed
//      procedure
//--------------------------------------------------------------
BOOL
CXSSubWndCtrl::SubclassWindow(CWnd* pWnd)
{
    ASSERT_VALID(pWnd);

    // Make sure this instance has not already been set up
    // to be a subclasser
    ASSERT(m_pSubWnd == NULL);

    // Verify window exists and make assignment
    ASSERT(pWnd->m_hWnd && ::IsWindow(pWnd->m_hWnd));
    HWND hwnd = pWnd->m_hWnd;

    // Add window to the mapper
    macXSSubWndCtrlMap.Add(hwnd, this);

    m_pSubWnd = pWnd;

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSSubWndCtrl::SubclassWindow
// Purpose   :
//  Subclasses the passes HWND
// Parameters:
//  HWND hWnd - the window to subclass
// Returns   :
//  BOOL - TRUE on success, FALSE on failue
// Comments  :
//  Call SubclassWindow(NULL) to remove (uninstall) the
//  subclassed procedure.
// Notes     :
//  The prefered method to to call the other SubclassWindow with
//  a CWnd.  This function may not be available in future
//  releases.
// -------------------------------------------------------------
BOOL
CXSSubWndCtrl::SubclassWindow(HWND hWnd)
{
    ASSERT(::IsWindow(hWnd));

    m_pWindow = new CWnd;
    m_pWindow->Attach(hWnd);
    return SubclassWindow(m_pWindow);
}

// -------------------------------------------------------------
// Function  :
//  CXSSubWndCtrl::IsSubclassed
// Purpose   :
//  Verifies that this object has a subclassed window
// Parameters:
//  None
// Returns   :
//  BOOL - TRUE if the object has subclassed a window
//       - FALSE if the object has not subclassed a window
// -------------------------------------------------------------
BOOL
CXSSubWndCtrl::IsSubclassed()
{
    return m_pSubWnd != NULL;
}

// -------------------------------------------------------------
// Function  :
//  CXSSubWndCtrl::Remove
// Purpose   :
//  Removes (uninstalls) the subclass handler
// Parameters:
//  None
// Returns   :
//  BOOL - TRUE on success
//       - FALSE on failure
// -------------------------------------------------------------
BOOL
CXSSubWndCtrl::Remove()
{
    // The subclasser is uninstalling. Verify we've been
    // subclassed before proceeding
    ASSERT(m_pSubWnd != NULL);

    // Remove the window from the mapper
    macXSSubWndCtrlMap.Remove(this);
    m_pOldWndProc = NULL;

    m_pSubWnd = NULL;

    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSSubWndCtrl::DoGetWnd
// Purpose   :
//  Returns a pointer to the passed CWnd
// Parameters:
//  None
// Returns   :
//  CWnd* - pointer to the passed CWnd
// -------------------------------------------------------------
CWnd*
CXSSubWndCtrl::DoGetWnd()
{
    ASSERT_VALID(m_pSubWnd);
    return m_pSubWnd;
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrl::DoWindowProc
// Purpose   :
//    Chains through the old window procedures and calls each.
//    Typically, when you derive from this class, you will write
//    your own DoWindowProc procedure.  Anything you do not
//    handle, should call the base class function.
//    If you have subclassed a window more than once, this
//    function will call the previous subclassed procedure. If
//    you have not subclassed, or the last subclassed procedure
//    is reached, then the original window's procedure is called.
//    The chaining only happens until one of the procedures does
//    not call the base implementation.
// Parameters:
//    UINT nMsg - The windows message
//    WPARAM wParam - parameter applicable for windows message
//    LPARAM lParam - parameter applicable for windows message
// Returns   :
//    LRESULT - Depends on windows message
//--------------------------------------------------------------
LRESULT
CXSSubWndCtrl::DoWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    ASSERT(m_pOldWndProc);

    // Either call the next chained subclassed window procedure,
    // or call the window's implementation.
    return m_pNext ? m_pNext->DoWindowProc(nMsg, wParam, lParam) :
        ::CallWindowProc(m_pOldWndProc, m_pSubWnd->m_hWnd,
            nMsg, wParam, lParam);
}

// -------------------------------------------------------------
// Function  :
//  CXSSubWndCtrl::CallWindowProc
// Purpose   :
//  For convenience only.  Calls CXSSubWndCtrl::DoWindowProc
// Parameters:
// Returns   :
// -------------------------------------------------------------
LRESULT
CXSSubWndCtrl::CallWindowProc(UINT nMsg, WPARAM wParam,
                               LPARAM lParam)
{
    return DoWindowProc(nMsg, wParam, lParam);
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrl::Default
// Purpose   :
//    Provides default message handling.  You can call this
//    function when you have not stored the message parameters
//    from the last Windows message.  MFC stores the message in
//    its thread state.
// Parameters:
//    None
// Returns   :
//    LRESULT of the called procedure
//--------------------------------------------------------------
LRESULT
CXSSubWndCtrl::Default()
{
    // MFC stores current MSG in thread state
    MSG& msgCur = AfxGetThreadState()->m_lastSentMsg;

    // Note: must explicitly call CXSSubWndCtrl::DoWindowProc to
    // avoid infinite recursion on virtual function
    return CXSSubWndCtrl::DoWindowProc(msgCur.message,
        msgCur.wParam, msgCur.lParam);
}

//--------------------------------------------------------------
// Function  :
//    XSSubclass_WndProc
// Purpose   :
//    This is the actual function that gets subclassed and is
//    eventually called by Windows. This functiion then calls
//    the appropriate subclassed window proc. If this function
//    receives a WM_NCDESTROY window message, it uninstalls
//    itself as the window proc handler. This save the
//    programmer from having to uninstall the handler when the
//    window is destroyed.
// Parameters:
//    UINT nMsg - The windows message
//    WPARAM wParam - parameter applicable for windows message
//    LPARAM lParam - parameter applicable for windows message
// Returns   :
//    LRESULT - Depends on windows message
// Comments:
//    Subclassed window proc for message hooks.  Replaces
//    AfxWndProc or previously installed wnd proc.
//--------------------------------------------------------------
LRESULT CALLBACK
XSSubclass_WndProc(HWND hWnd, UINT nMsg,
                   WPARAM wParam, LPARAM lParam)
{
#ifdef _USRDLL
    // if this code is in a user DLL,
    // we need to set up the MFC state
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

    // This looks just like AfxCallWindowProc, but we
    // can't use that because CXSSubWndCtrl is not really
    // derived from CWnd.
    MSG& msgCur = AfxGetThreadState()->m_lastSentMsg;
    MSG msgOld = msgCur;
    msgCur.hwnd = hWnd;
    msgCur.message = nMsg;
    msgCur.wParam = wParam;
    msgCur.lParam = lParam;

    // Look up the wndproc handler
    CXSSubWndCtrl* pSubWnd =
        macXSSubWndCtrlMap.Lookup(hWnd);
    ASSERT(pSubWnd);

    LRESULT lResult = 0;

    if (nMsg == WM_NCDESTROY)
    {
        // Just in case we need a handler
        ::SendMessage(hWnd, WM_PRENCDESTROY, 0, 0);

        // Disengage all hooks for this window before it is
        // destoyed and pass msg to original window proc
        WNDPROC wndProc = pSubWnd->m_pOldWndProc;
        macXSSubWndCtrlMap.RemoveAll(hWnd);
        lResult = ::CallWindowProc(wndProc, hWnd, nMsg,
            wParam, lParam);
    }
    else
    {
        // Call the appropriate wndproc handler
        lResult = pSubWnd->DoWindowProc(nMsg, wParam, lParam);
    }

    msgCur = msgOld;

    return lResult;
}

//==============================================================

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::CXSSubWndCtrlMap
// Purpose   :
//    Constructor, initializes memory
//--------------------------------------------------------------
CXSSubWndCtrlMap::CXSSubWndCtrlMap()
{
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::~CXSSubWndCtrlMap
// Purpose   :
//    Destructor, cleans up memory.
//--------------------------------------------------------------
CXSSubWndCtrlMap::~CXSSubWndCtrlMap()
{
    if (!IsEmpty())
        CMapPtrToPtr::RemoveAll();

    ASSERT(IsEmpty());
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::GetSubclassWndMap
// Purpose   :
//    Returns the static CXSSubWndCtrlMap variable.  It is
//    initialized the first time this function is called.
// Parameters:
//    None
// Returns   :
//    See above.
//--------------------------------------------------------------
CXSSubWndCtrlMap&
CXSSubWndCtrlMap::GetSubWndCtrlMap()
{
    // By creating the static variable here, C++ doesn't
    // instantiate it until/unless it's ever used.  This is a
    // good way of encapsulating a static object.
    static CXSSubWndCtrlMap XSSubWndCtrlMap;
    return XSSubWndCtrlMap;
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::Add
// Purpose   :
//    Associates a new CXSSubWndCtrl procedure to a windows
//      handle (HWND)
// Parameters:
//    HWND hwnd - the window to deal with
//    CXSSubWndCtrl* pSubclassWnd - pointer to new procedure
// Returns   :
//    Nothing
//--------------------------------------------------------------
void
CXSSubWndCtrlMap::Add(HWND hwnd, CXSSubWndCtrl* pSubWnd)
{
    ASSERT(hwnd && ::IsWindow(hwnd));

    // Add to front of list
    pSubWnd->m_pNext = Lookup(hwnd);
    SetAt(hwnd, pSubWnd);

    if (pSubWnd->m_pNext == NULL)
    {
        // If this is the first hook added,
        // then subclass the window
        pSubWnd->m_pOldWndProc =
            (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC,
            (DWORD)XSSubclass_WndProc);
    }
    else
    {
        // Just copy wndproc from next hook as this class has
        // already been subclassed
        pSubWnd->m_pOldWndProc =
            pSubWnd->m_pNext->m_pOldWndProc;
    }

    ASSERT(pSubWnd->m_pOldWndProc);
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::Remove
// Purpose   :
//    Removes a subclassed window procedure
// Parameters:
//    CXSSubWndCtrl* pUnSubclassWnd - Pointer to the
//      CXSSubWndCtrl to remove
// Returns   :
//    Nothing
//--------------------------------------------------------------
void
CXSSubWndCtrlMap::Remove(CXSSubWndCtrl* pUnSubWnd)
{
    HWND hwnd = pUnSubWnd->m_pSubWnd->GetSafeHwnd();
    ASSERT(hwnd && ::IsWindow(hwnd));

    // Look up the proceedure
    CXSSubWndCtrl* pSubWnd = Lookup(hwnd);
    ASSERT(pSubWnd);

    if (pUnSubWnd == pSubWnd)
    {
        if (pSubWnd->m_pNext)
        {
            // If there are chained handlers, set the next one
            // to be the current one
            SetAt(hwnd, pSubWnd->m_pNext);
        }
        else
        {
            // last hook; restore original wndproc
            RemoveKey(hwnd);
            SetWindowLong(hwnd, GWL_WNDPROC,
                (DWORD)pSubWnd->m_pOldWndProc);
        }
    }
    else
    {
        // The hook is in the middle, so remove and patch
        // linked list
        while (pSubWnd->m_pNext != pUnSubWnd)
            pSubWnd = pSubWnd->m_pNext;

        ASSERT(pSubWnd && pSubWnd->m_pNext ==
            pUnSubWnd);

        pSubWnd->m_pNext = pUnSubWnd->m_pNext;
    }
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::RemoveAll
// Purpose   :
//    Removes all of the subclassed window procedures
// Parameters:
//    HWND hwnd - The HWND of the window to remove the
//      procedures from
// Returns   :
//    Nothing
//--------------------------------------------------------------
void
CXSSubWndCtrlMap::RemoveAll(HWND hwnd)
{
    CXSSubWndCtrl* pSubWnd;

    while ((pSubWnd = Lookup(hwnd)) != NULL)
        pSubWnd->Remove();  // Unhook
}

//--------------------------------------------------------------
// Function  :
//    CXSSubWndCtrlMap::Lookup
// Purpose   :
//    Returns the CXSSubWndCtrl pointer with the procedure for
//      the passed window
// Parameters:
//    HWND hwnd - The HWND of the window to search for
// Returns   :
//    See above.
//--------------------------------------------------------------
CXSSubWndCtrl*
CXSSubWndCtrlMap::Lookup(HWND hwnd)
{
    CXSSubWndCtrl* pSubWnd = NULL;

    // Look up the window and make sure it is in our map
    if (!CMapPtrToPtr::Lookup(hwnd, (void*&)pSubWnd))
        return NULL;

    // Make sure the procedure has been derived from
    // CXSSubWndCtrl
    ASSERT_KINDOF(CXSSubWndCtrl, pSubWnd);

    // Return it
    return pSubWnd;
}
