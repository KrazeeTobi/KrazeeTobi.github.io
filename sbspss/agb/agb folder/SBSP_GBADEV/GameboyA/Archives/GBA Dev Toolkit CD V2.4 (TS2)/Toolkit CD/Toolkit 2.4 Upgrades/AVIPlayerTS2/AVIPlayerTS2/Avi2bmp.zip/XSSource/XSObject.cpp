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
//#include "XSObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXSObject, CXSSubWndCtrl)

// -------------------------------------------------------------
// Function  :
//    CXSObject::CXSObject
// Purpose   :
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSObject::CXSObject() :
    m_pWnd((CWnd*&)m_pSubWnd)
{
}

// -------------------------------------------------------------
// Function  :
//     CXSObject::~CXSObject
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSObject::~CXSObject()
{
    // Because children are destroyed before parents, we have
    // to explicitly remove the subclass notify handler for
    // the parent
    if (m_Notify.IsSubclassed())
        m_Notify.Remove();
}

// -------------------------------------------------------------
// Function  :
//  CXSObject::DoPreInstall
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
CXSObject::DoPreInstall()
{
    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//    CXSObject::DoInstall
// Purpose   :
//    Installs the CXSObject instance as the handler for the
//    passed CWnd pointer
// Parameters:
//    CWnd* pWnd - The CWnd to attach to
//    BOOL bNotify - Install message reflection into parent
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSObject::DoInstall(CWnd* pWnd, BOOL bNotify)
{
    ASSERT_KINDOF(CWnd, pWnd);

    if (!DoPreInstall())
        return FALSE;

    BOOL bResult = SubclassWindow(pWnd);

    // The User asked to have WM_NOTIFY messages sent from
    // the parent to this class
    if (bNotify)
    {
        CWnd* pParent = pWnd->GetParent();
        if (pParent)
            m_Notify.DoInstall(pParent, this);
    }

    return bResult;
}

// -------------------------------------------------------------
// Function  :
//    CXSObject::DoWindowProc
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
CXSObject::DoWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = 0;

    switch(nMsg)
    {
    // ---------------------------------------------------------
    // Regular messages
    case WM_CREATE:                                 // 0x0001 - returns an int
        if (!OnCreate(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_DESTROY:                                // 0x0002
        if (!OnDestroy(wParam, lParam))
            return Default();
        return 0;

    case WM_MOVE:                                   // 0x0003
        if (!OnMove(wParam, lParam))
            return Default();
        return 0;

    case WM_SIZE:                                   // 0x0005
        if (!OnSize(wParam, lParam))
            return Default();
        return 0;

    case WM_ACTIVATE:                               // 0x0006
        if (!OnActivate(wParam, lParam))
            return Default();
        return 0;

    case WM_SETFOCUS:                               // 0x0007
        if (!OnSetFocus(wParam, lParam))
            return Default();
        return 0;

    case WM_KILLFOCUS:                              // 0x0008
        if (!OnKillFocus(wParam, lParam))
            return Default();
        return 0;

    case WM_ENABLE:                                 // 0x000A
        if (!OnEnable(wParam, lParam))
            return Default();
        return 0;

    case WM_SETREDRAW:                              // 0x000B
        if (!OnSetRedraw(wParam, lParam))
            return Default();
        return 0;

    case WM_SETTEXT:                                // 0x000C - returns an int
        if (!OnSetText(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_GETTEXT:                                // 0x000D - returns an int
        if (!OnGetText(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_GETTEXTLENGTH:                          // 0x000E - returns an int
        if (!OnGetTextLength(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_PAINT:                                  // 0x000F
        if (!OnPaint(wParam, lParam))
            return Default();
        return 0;

    case WM_CLOSE:                                  // 0x0010
        if (!OnClose(wParam, lParam))
            return Default();
        return 0;

    case WM_QUERYENDSESSION:                        // 0x0011
        if (!OnQueryEndSession(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_QUIT:                                   // 0x0012
        if (!OnQuit(wParam, lParam))
            Default();
        return 0;

    case WM_QUERYOPEN:                              // 0x0013
        if (!OnQueryOpen(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_ERASEBKGND:                             // 0x0014
        if (!OnEraseBkgnd(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_SYSCOLORCHANGE:                         // 0x0015
        if (!OnSysColorChange(wParam, lParam))
            Default();
        return 0;

    case WM_ENDSESSION:                             // 0x0016
        if (!OnEndSession(wParam, lParam))
            return Default();
        return 0;

    case WM_SHOWWINDOW:                             // 0x0018
        if (!OnShowWindow(wParam, lParam))
            return Default();
        return 0;

    case WM_SETTINGCHANGE:                          // 0x001A
        if (!OnSettingChange(wParam, lParam))
            return Default();
        return 0;

    case WM_DEVMODECHANGE:                          // 0x001B
        if (!OnDevModeChange(wParam, lParam))
            return Default();
        return 0;

    case WM_ACTIVATEAPP:                            // 0x001C
        if (!OnActivateApp(wParam, lParam))
            return Default();
        return 0;

    case WM_FONTCHANGE:                             // 0x001D
        if (!OnFontChange(wParam, lParam))
            Default();
        return 0;

    case WM_TIMECHANGE:                             // 0x001E
        if (!OnTimeChange(wParam, lParam))
            return Default();
        return 0;

    case WM_CANCELMODE:                             // 0x001F
        if (!OnCancelMode(wParam, lParam))
            return Default();
        return 0;

    case WM_SETCURSOR:                              // 0x0020
        if (!OnSetCursor(wParam, lParam))
            return Default();
        return lResult;

    case WM_MOUSEACTIVATE:                          // 0x0021 - returns an int
        if (!OnMouseActivate(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CHILDACTIVATE:                          // 0x0022
        if (!OnChildActivate(wParam, lParam))
            return Default();
        return 0;

    case WM_QUEUESYNC:                              // 0x0023
        if (!OnQueueSync(wParam, lParam))
            return Default();
        return 0;

    case WM_GETMINMAXINFO:                          // 0x0024
        if (!OnGetMinMaxInfo(wParam, lParam))
            return Default();
        return 0;

    case WM_PAINTICON:                              // 0x0026
        if (!OnPaintIcon(wParam, lParam))
            return Default();
        return 0;

    case WM_ICONERASEBKGND:                         // 0x0027
        if (!OnIconEraseBkgnd(wParam, lParam))
            return Default();
        return 0;

    case WM_NEXTDLGCTL:                             // 0x0028
        if (!OnNextDlgCtl(wParam, lParam))
            return Default();
        return 0;

    case WM_SPOOLERSTATUS:                          // 0x002A
        if (!OnSpoolerStatus(wParam, lParam))
            return Default();
        return 0;

    case WM_DRAWITEM:                               // 0x002B
        if (!OnDrawItem(wParam, lParam))
            return Default();
        return TRUE;

    case WM_MEASUREITEM:                            // 0x002C
        if (!OnMeasureItem(wParam, lParam))
            return Default();
        return TRUE;

    case WM_DELETEITEM:                             // 0x002D
        if (!OnDeleteItem(wParam, lParam))
            return Default();
        return TRUE;

    case WM_VKEYTOITEM:                             // 0x002E - returns an int
        if (!OnVKeyToItem(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CHARTOITEM:                             // 0x002F - returns an int
        if (!OnCharToItem(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_SETFONT:                                // 0x0030
        if (!OnSetFont(wParam, lParam))
            Default();
        return 0;

    case WM_GETFONT:                                // 0x0031 - returns an LRESULT
        if (!OnGetFont(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_SETHOTKEY:                              // 0x0032 - returns an int
        if (!OnSetHotKey(wParam, lParam, lResult))
            return Default();
        return 0;

    case WM_GETHOTKEY:                              // 0x0033 - returns an int
        if (!OnGetHotKey(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_QUERYDRAGICON:                          // 0x0037 - returns an LRESULT
        if (!OnQueryDragIcon(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_COMPAREITEM:                            // 0x0039 - returns an int
        if (!OnCompareItem(wParam, lParam, lResult))
            return Default();
         return lResult;

    case WM_COMPACTING:                             // 0x0041
        if (!OnCompacting(wParam, lParam))
            return Default();
         return 0;

    case WM_WINDOWPOSCHANGING:                      // 0x0046
        if (!OnWindowPosChanging(wParam, lParam))
            return Default();
        return 0;

    case WM_WINDOWPOSCHANGED:                       // 0x0047
        if (!OnWindowPosChanged(wParam, lParam))
            return Default();
        return 0;

// ** OBSOLETE in 32-bit**
//  case WM_POWER:                                  // 0x0048 - returns an int
// ** Use WM_POWERBROADCAST instead **

    case WM_COPYDATA:                               // 0x004A
        if (!OnCopyData(wParam, lParam))
            return Default();
        return TRUE;

// We're not handling Journals
//    case WM_CANCELJOURNAL:                          // 0x004B

    case WM_NOTIFY:                                 // 0x004E - returns an LRESULT
        if (!OnNotify(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_INPUTLANGCHANGEREQUEST:                 // 0x0050
        if (!OnInputLangChangeRequest(wParam, lParam))
            Default();
        return 0;

    case WM_INPUTLANGCHANGE:                        // 0x0051
        if (!OnInputLangChange(wParam, lParam))
            return Default();
        return TRUE;

    case WM_TCARD:                                  // 0x0052
        if (!OnTCard(wParam, lParam))
            Default();
        return 0;

    case WM_HELP:                                   // 0x0053
        if (!OnHelp(wParam, lParam))
            return Default();
        return TRUE;

    case WM_USERCHANGED:                            // 0x0054
        if (!OnUserChanged(wParam, lParam))
            return Default();
        return 0;

    case WM_NOTIFYFORMAT:                           // 0x0055 - returns an int
        if (!OnNotifyFormat(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CONTEXTMENU:                            // 0x007B
        if (!OnContextMenu(wParam, lParam))
            Default();
        return 0;

    case WM_STYLECHANGING:                          // 0x007C
        if (!OnStyleChanging(wParam, lParam))
            return Default();
        return 0;

    case WM_STYLECHANGED:                           // 0x007D
        if (!OnStyleChanged(wParam, lParam))
            return Default();
        return 0;

    case WM_DISPLAYCHANGE:                          // 0x007E
        if (!OnDisplayChange(wParam, lParam))
            Default();
        return 0;

    case WM_GETICON:                                // 0x007F - returns an LRESULT
        if (!OnGetIcon(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_SETICON:                                // 0x0080 - returns an LRESULT
        if (!OnSetIcon(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_NCCREATE:                               // 0x0081
        if (!OnNcCreate(wParam, lParam))
            return Default();
        return TRUE;

    case WM_NCDESTROY:                              // 0x0082
        if (!OnNcDestroy(wParam, lParam))
            return Default();
        return 0;

    case WM_NCCALCSIZE:                             // 0x0083 - returns an int
        if (!OnNcCalcSize(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_NCHITTEST:                              // 0x0084 - returns an int
        if (!OnNcHitTest(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_NCPAINT:                                // 0x0085
        if (!OnNcPaint(wParam, lParam))
            return Default();
        return 0;

    case WM_NCACTIVATE:                             // 0x0086
        if (!OnNcActivate(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_GETDLGCODE:                             // 0x0087 - returns an int
        if (!OnGetDlgCode(wParam, lParam, lResult))
            return Default();
        return lResult;

#if WINVER >= 0x0500
	case WM_NCMOUSEHOVER:
		if (!OnNcMouseHover(wParam, lParam))
			return Default();
		return 0;

	case WM_NCMOUSELEAVE:
		if (!OnNcMouseLeave(wParam, lParam))
			return Default();
		return 0;
#endif


    case WM_NCMOUSEMOVE:                            // 0x00A0
        if (!OnNcMouseMove(wParam, lParam))
            return Default();
        return 0;

    case WM_NCLBUTTONDOWN:                          // 0x00A1
        if (!OnNcLButtonDown(wParam, lParam))
            return Default();
        return 0;

    case WM_NCLBUTTONUP:                            // 0x00A2
        if (!OnNcLButtonUp(wParam, lParam))
            return Default();
        return 0;

    case WM_NCLBUTTONDBLCLK:                        // 0x00A3
        if (!OnNcLButtonDblClk(wParam, lParam))
            return Default();
        return 0;

    case WM_NCRBUTTONDOWN:                          // 0x00A4
        if (!OnNcRButtonDown(wParam, lParam))
            return Default();
        return 0;

    case WM_NCRBUTTONUP:                            // 0x00A5
        if (!OnNcRButtonUp(wParam, lParam))
            return Default();
        return 0;

    case WM_NCRBUTTONDBLCLK:                        // 0x00A6
        if (!OnNcRButtonDblClk(wParam, lParam))
            return Default();
        return 0;

    case WM_NCMBUTTONDOWN:                          // 0x00A7
        if (!OnNcMButtonDown(wParam, lParam))
            return Default();
        return 0;

    case WM_NCMBUTTONUP:                            // 0x00A8
        if (!OnNcMButtonUp(wParam, lParam))
            return Default();
        return 0;

    case WM_NCMBUTTONDBLCLK:                        // 0x00A9
        if (!OnNcMButtonDblClk(wParam, lParam))
            return Default();
        return 0;

// Not a real message
//    case WM_KEYFIRST:                             // 0x0100

    case WM_KEYDOWN:                                // 0x0100
        if (!OnKeyDown(wParam, lParam))
            return Default();
        return 0;

    case WM_KEYUP:                                  // 0x0101
        if (!OnKeyUp(wParam, lParam))
            return Default();
        return 0;

    case WM_CHAR:                                   // 0x0102
        if (!OnChar(wParam, lParam))
            return Default();
        return 0;

    case WM_DEADCHAR:                               // 0x0103
        if (!OnDeadChar(wParam, lParam))
            return Default();
        return 0;

    case WM_SYSKEYDOWN:                             // 0x0104
        if (!OnSysKeyDown(wParam, lParam))
            return Default();
        return 0;

    case WM_SYSKEYUP:                               // 0x0105
        if (!OnSysKeyUp(wParam, lParam))
            return Default();
        return 0;

    case WM_SYSCHAR:                                // 0x0106
        if (!OnSysChar(wParam, lParam))
            return Default();
        return 0;

    case WM_SYSDEADCHAR:                            // 0x0107
        if (!OnSysDeadChar(wParam, lParam))
            return Default();
        return 0;

// Not a real message
//    case WM_KEYLAST:                              // 0x0108

// We're not handling IME
//    case WM_IME_STARTCOMPOSITION:                 // 0x010D
//    case WM_IME_ENDCOMPOSITION:                   // 0x010E
//    case WM_IME_COMPOSITION:                      // 0x010F
//    case WM_IME_KEYLAST:                          // 0x010F - unknown message

    case WM_INITDIALOG:                             // 0x0110
        if (!OnInitDialog(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_COMMAND:                                // 0x0111
        if (!OnCommand(wParam, lParam))
            return Default();
        return 0;

    case WM_SYSCOMMAND:                             // 0x0112
        if (!OnSysCommand(wParam, lParam))
            return Default();
        return 0;

    case WM_TIMER:                                  // 0x0113
        if (!OnTimer(wParam, lParam))
            return Default();
        return 0;

    case WM_HSCROLL:                                // 0x0114
        if (!OnHScroll(wParam, lParam))
            return Default();
        return 0;

    case WM_VSCROLL:                                // 0x0115
        if (!OnVScroll(wParam, lParam))
            return Default();
        return 0;

    case WM_INITMENU:                               // 0x0116
        if (!OnInitMenu(wParam, lParam))
            return Default();
        return 0;

    case WM_INITMENUPOPUP:                          // 0x0117
        if (!OnInitMenuPopup(wParam, lParam))
            return Default();
        return 0;

    case WM_MENUSELECT:                             // 0x011F
        if (!OnMenuSelect(wParam, lParam))
            return Default();
        return 0;

    case WM_MENUCHAR:                               // 0x0120 - returns an int
        if (!OnMenuChar(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_ENTERIDLE:                              // 0x0121
        if (!OnEnterIdle(wParam, lParam))
            return Default();
        return 0;

    case WM_CTLCOLORMSGBOX:                         // 0x0132 - returns an LRESULT
        if (!OnCtlColorMsgBox(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CTLCOLOREDIT:                           // 0x0133 - returns an LRESULT
        if (!OnCtlColorEdit(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CTLCOLORLISTBOX:                        // 0x0134 - returns an LRESULT
        if (!OnCtlColorListBox(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CTLCOLORBTN:                            // 0x0135 - returns an LRESULT
        if (!OnCtlColorBtn(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CTLCOLORDLG:                            // 0x0136 - returns an LRESULT
        if (!OnCtlColorDlg(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CTLCOLORSCROLLBAR:                      // 0x0137 - returns an LRESULT
        if (!OnCtlColorScrollBar(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_CTLCOLORSTATIC:                         // 0x0138 - returns an LRESULT
        if (!OnCtlColorStatic(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_MOUSEMOVE:                              // 0x0200
        if (!OnMouseMove(wParam, lParam))
            Default();
        return 0;

    case WM_LBUTTONDOWN:                            // 0x0201
        if (!OnLButtonDown(wParam, lParam))
            return Default();
        return 0;

    case WM_LBUTTONUP:                              // 0x0202
        if (!OnLButtonUp(wParam, lParam))
            return Default();
        return 0;

    case WM_LBUTTONDBLCLK:                          // 0x0203
        if (!OnLButtonDblClk(wParam, lParam))
            return Default();
        return 0;

    case WM_RBUTTONDOWN:                            // 0x0204
        if (!OnRButtonDown(wParam, lParam))
            return Default();
        return 0;

    case WM_RBUTTONUP:                              // 0x0205
        if (!OnRButtonUp(wParam, lParam))
            return Default();
        return 0;

    case WM_RBUTTONDBLCLK:                          // 0x0206
        if (!OnRButtonDblClk(wParam, lParam))
            return Default();
        return 0;

    case WM_MBUTTONDOWN:                            // 0x0207
        if (!OnMButtonDown(wParam, lParam))
            return Default();
        return 0;

    case WM_MBUTTONUP:                              // 0x0208
        if (!OnMButtonUp(wParam, lParam))
            return Default();
        return 0;

    case WM_MBUTTONDBLCLK:                          // 0x0209
        if (!OnMButtonDblClk(wParam, lParam))
            return Default();
        return 0;

    case WM_MOUSEWHEEL:                             // 0x020A
        if (!OnMouseWheel(wParam, lParam))
            Default();
        return 0;

    case WM_PARENTNOTIFY:                           // 0x0210
        if (!OnParentNotify(wParam, lParam))
            return Default();
        return 0;

    case WM_ENTERMENULOOP:                          // 0x0211
        if (!OnEnterMenuLoop(wParam, lParam))
            return Default();
        return 0;

    case WM_EXITMENULOOP:                           // 0x0212
        if (!OnExitMenuLoop(wParam, lParam))
            return Default();
        return 0;

    case WM_NEXTMENU:                               // 0x0213
        if (!OnNextMenu(wParam, lParam))
            Default();
        return 0;

    case WM_SIZING:                                 // 0x0214
        if (!OnSizing(wParam, lParam))
            return Default();
        return TRUE;

    case WM_CAPTURECHANGED:                         // 0x0215
        if (!OnCaptureChanged(wParam, lParam))
            return Default();
        return 0;

    case WM_MOVING:                                 // 0x0216
        if (!OnMoving(wParam, lParam))
            return Default();
        return TRUE;

    case WM_POWERBROADCAST:                         // 0x0218 - returns an int
        if (!OnPowerBroadcast(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_DEVICECHANGE:                           // 0x0219 - returns an int
        if (!OnDeviceChange(wParam, lParam, lResult))
            return Default();
        return lResult;

// We're not handling IME
//    case WM_IME_SETCONTEXT:                       // 0x0281
//    case WM_IME_NOTIFY:                           // 0x0282
//    case WM_IME_CONTROL:                          // 0x0283
//    case WM_IME_COMPOSITIONFULL:                  // 0x0284
//    case WM_IME_SELECT:                           // 0x0285
//    case WM_IME_CHAR:                             // 0x0286
//    case WM_IME_KEYDOWN:                          // 0x0290
//    case WM_IME_KEYUP:                            // 0x0291

    case WM_MDICREATE:                              // 0x0220 - returns an LRESULT
        if (!OnMdiCreate(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_MDIDESTROY:                             // 0x0221
        if (!OnMdiDestroy(wParam, lParam))
            return Default();
        return 0;

    case WM_MDIACTIVATE:                            // 0x0222
        if (!OnMdiActivate(wParam, lParam))
            return Default();
        return 0;

    case WM_MDIRESTORE:                             // 0x0223
        if (!OnMdiRestore(wParam, lParam))
            return Default();
        return 0;

    case WM_MDINEXT:                                // 0x0224
        if (!OnMdiNext(wParam, lParam))
            return Default();
        return 0;

    case WM_MDIMAXIMIZE:                            // 0x0225
        if (!OnMdiMaximize(wParam, lParam))
            return Default();
        return 0;

    case WM_MDITILE:                                // 0x0226
        if (!OnMdiTile(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_MDICASCADE:                             // 0x0227
        if (!OnMdiCascade(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_MDIICONARRANGE:                         // 0x0228
        if (!OnMdiIconArrange(wParam, lParam))
            Default();
        return 0;

    case WM_MDIGETACTIVE:                           // 0x0229 - returns an LRESULT
        if (!OnMdiGetActive(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_MDISETMENU:                             // 0x0230 - returns an LRESULT
        if (!OnMdiSetMenu(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_ENTERSIZEMOVE:                          // 0x0231
        if (!OnEnterSizeMove(wParam, lParam))
            return Default();
        return 0;

    case WM_EXITSIZEMOVE:                           // 0x0232
        if (!OnExitSizeMove(wParam, lParam))
            return Default();
        return 0;

    case WM_DROPFILES:                              // 0x0233
        if (!OnDropFiles(wParam, lParam))
            return Default();
        return 0;

    case WM_MDIREFRESHMENU:                         // 0x0234 - returns an LRESULT
        if (!OnMdiRefreshMenu(wParam, lParam, lResult))
            return Default();
        return lResult;

#if WINVER >= 0x0500
    case WM_MOUSEHOVER:                             // 0x02A1 - TrackMouseEvent
        if (!OnMouseHover(wParam, lParam))
            return Default();
        return 0;

    case WM_MOUSELEAVE:                             // 0x02A3 - TrackMouseEvent
        if (!OnMouseLeave(wParam, lParam))
            return Default();
        return 0;
#endif

    case WM_CUT:                                    // 0x0300
        if (!OnCut(wParam, lParam))
            Default();
        return 0;

    case WM_COPY:                                   // 0x0301
        if (!OnCopy(wParam, lParam))
            Default();
        return 0;

    case WM_PASTE:                                  // 0x0302
        if (!OnPaste(wParam, lParam))
            Default();
        return 0;

    case WM_CLEAR:                                  // 0x0303
        if (!OnClear(wParam, lParam))
            Default();
        return 0;

    case WM_UNDO:                                   // 0x0304
        if (!OnUndo(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_RENDERFORMAT:                           // 0x0305
        if (!OnRenderFormat(wParam, lParam))
            return Default();
        return 0;

    case WM_RENDERALLFORMATS:                       // 0x0306
        if (!OnRenderAllFormats(wParam, lParam))
            return Default();
        return 0;

    case WM_DESTROYCLIPBOARD:                       // 0x0307
        if (!OnDestroyClipboard(wParam, lParam))
            return Default();
        return 0;

    case WM_DRAWCLIPBOARD:                          // 0x0308
        if (!OnDrawClipboard(wParam, lParam))
            Default();
        return 0;

    case WM_PAINTCLIPBOARD:                         // 0x0309
        if (!OnPaintClipboard(wParam, lParam))
            return Default();
        return 0;

    case WM_VSCROLLCLIPBOARD:                       // 0x030A
        if (!OnVScrollClipboard(wParam, lParam))
            return Default();
        return 0;

    case WM_SIZECLIPBOARD:                          // 0x030B
        if (!OnSizeClipboard(wParam, lParam))
            Default();
        return 0;

    case WM_ASKCBFORMATNAME:                        // 0x030C
        if (!OnAskCbFormatName(wParam, lParam))
            return Default();
        return 0;

    case WM_CHANGECBCHAIN:                          // 0x030D
        if (!OnChangeCbChain(wParam, lParam))
            return Default();
        return 0;

    case WM_HSCROLLCLIPBOARD:                       // 0x030E
        if (!OnHScrollClipboard(wParam, lParam))
            return Default();
        return 0;

    case WM_QUERYNEWPALETTE:                        // 0x030F
        if (!OnQueryNewPalette(wParam, lParam, lResult))
            return Default();
        return lResult;

    case WM_PALETTEISCHANGING:                      // 0x0310
        if (!OnPaletteIsChanging(wParam, lParam))
            return Default();
        return 0;

    case WM_PALETTECHANGED:                         // 0x0311
        {
            // To prevent recursion, do not process this
            // message if it was originally sent from this
            // class. To see if it was sent from this class,
            // check the HWND against the one used by this
            // class. If they are the same, do not process.
            HWND hWnd = (HWND)wParam;
            ASSERT(hWnd && ::IsWindow(hWnd));
            ASSERT(DoGetWnd() && DoGetWnd()->m_hWnd && 
                ::IsWindow(DoGetWnd()->m_hWnd));

            if (hWnd != DoGetWnd()->m_hWnd)
                if (!OnPaletteChanged(wParam, lParam))
                    return Default();
                else
                    return 0;
            else
                return Default();
        }

    case WM_HOTKEY:                                 // 0x0312
        if (!OnHotKey(wParam, lParam))
            Default();
        return 0;

    case WM_PRINT:                                  // 0x0317
        if (!OnPrint(wParam, lParam))
            Default();
        return 0;

    case WM_PRINTCLIENT:                            // 0x0318
        if (!OnPrintClient(wParam, lParam))
            Default();
        return 0;

    // ---------------------------------------------------------
    // Generic notification messages
    case NM_OUTOFMEMORY:
        if (!OnNotifyOutOfMemory(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case NM_CLICK:
        if (!OnNotifyClick(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case NM_DBLCLK:
        if (!OnNotifyDblClk(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case NM_RETURN:
        if (!OnNotifyReturn(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case NM_RCLICK:
        if (!OnNotifyRClick(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case NM_RDBLCLK:
        if (!OnNotifyRDblClk(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case NM_SETFOCUS:
        if (!OnNotifySetFocus(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case NM_KILLFOCUS:
        if (!OnNotifyKillFocus(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#if (_WIN32_IE >= 0x0300)
    case NM_CUSTOMDRAW:
        if (!OnNotifyCustomDraw(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case NM_HOVER:
        if (!OnNotifyHover(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;
#endif

#if (_WIN32_IE >= 0x0400)
    case NM_NCHITTEST:
        if (!OnNotifyNcHitTest(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case NM_KEYDOWN:
        if (!OnNotifyKeyDown(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case NM_RELEASEDCAPTURE:
        if (!OnNotifyReleasedCapture(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case NM_SETCURSOR:
        if (!OnNotifySetCursor(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case NM_CHAR:
        if (!OnNotifyChar(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif

#if WINVER >= 0x0500
	case NM_TOOLTIPSCREATED:
        if (!OnNotifyTooltipsCreated(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif

    // ---------------------------------------------------------
    // Property Sheet notification messages

    case PSN_APPLY:
    if (!OnPropSheetApply(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

#if (_WIN32_IE >= 0x0400)
    case PSN_GETOBJECT:
    if (!OnPropSheetGetObject(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;
#endif

    case PSN_HELP:
    if (!OnPropSheetHelp(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_KILLACTIVE:
    if (!OnPropSheetKillActive(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_QUERYCANCEL:
    if (!OnPropSheetQueryCancel(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_RESET:
    if (!OnPropSheetReset(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_SETACTIVE:
    if (!OnPropSheetSetActive(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_WIZBACK:
    if (!OnPropSheetWizBack(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_WIZFINISH:
    if (!OnPropSheetWizFinish(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case PSN_WIZNEXT:
    if (!OnPropSheetWizNext(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    // ---------------------------------------------------------
    // Header notification messages

    case HDN_ITEMCHANGING:
        if (!OnHeaderItemChanging(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case HDN_ITEMCHANGED:
        if (!OnHeaderItemChanged(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case HDN_ITEMCLICK:
        if (!OnHeaderItemClick(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case HDN_ITEMDBLCLICK:
        if (!OnHeaderItemDblClick(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case HDN_DIVIDERDBLCLICK:
        if (!OnHeaderDividerDblClick(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case HDN_BEGINTRACK:
        if (!OnHeaderBeginTrack(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;
    
    case HDN_ENDTRACK:
        if (!OnHeaderEndTrack(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case HDN_TRACK:
        if (!OnHeaderTrack(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

#if (_WIN32_IE >= 0x0300)
    case HDN_GETDISPINFO:                           // unknown message
        if (!OnHeaderGetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case HDN_BEGINDRAG:                             // unknown message
        if (!OnHeaderBeginDrag(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case HDN_ENDDRAG:                               // unknown message
        if (!OnHeaderEndDrag(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;
#endif

    // ---------------------------------------------------------
    // Toolbar notification messages
    
    case TBN_GETBUTTONINFO:
        if (!OnToolbarGetButtonInfo(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TBN_BEGINDRAG:
        if (!OnToolbarBeginDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_ENDDRAG:
        if (!OnToolbarEndDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_BEGINADJUST:
        if (!OnToolbarBeginAdjust(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_ENDADJUST:
        if (!OnToolbarEndAdjust(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_RESET:
        if (!OnToolbarReset(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_QUERYINSERT:
        if (!OnToolbarQueryInsert(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TBN_QUERYDELETE:
        if (!OnToolbarQueryDelete(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TBN_TOOLBARCHANGE:
        if (!OnToolbarToolbarChange(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_CUSTHELP:
        if (!OnToolbarCustHelp(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#if (_WIN32_IE >= 0x0300)
    case TBN_DROPDOWN:                                  // unknown message
        if (!OnToolbarDropDown(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;
#endif

#if (_WIN32_IE >= 0x0400)
    case TBN_GETOBJECT:                                 // unknown message
        if (!OnToolbarGetObject(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_HOTITEMCHANGE:                             // unknown message
        if (!OnToolbarHotItemChange(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TBN_DRAGOUT:                                   // unknown message
        if (!OnToolbarDragOut(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_DELETINGBUTTON:                            // unknown message
        if (!OnToolbarDeletingButton(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_GETDISPINFO:                               // unknown message
        if (!OnToolbarGetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TBN_GETINFOTIP:                                // unknown message
        if (!OnToolbarGetInfoTip(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif

    // ---------------------------------------------------------
    // Rebar notification messages
    case RBN_HEIGHTCHANGE:                              // unknown message
        if (!OnRebarHeightChange(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#if (_WIN32_IE >= 0x0400)
    case RBN_GETOBJECT:
        if (!OnRebarGetObject(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case RBN_LAYOUTCHANGED:
        if (!OnRebarLayoutChanged(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case RBN_AUTOSIZE:
        if (!OnRebarAutoSize(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case RBN_BEGINDRAG:
        if (!OnRebarBeginDrag(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case RBN_ENDDRAG:
        if (!OnRebarEndDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case RBN_DELETINGBAND:
        if (!OnRebarDeletingBand(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case RBN_DELETEDBAND:
        if (!OnRebarDeleteBand(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case RBN_CHILDSIZE:
        if (!OnRebarChildSize(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif

    // ---------------------------------------------------------
    // Tooltip notification messages
//    case TTN_NEEDTEXT:	// superceeded by TTN_GETDISPINFO
    case TTN_GETDISPINFO:  
        if (!OnTooltipGetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TTN_SHOW:
        if (!OnTooltipShow(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TTN_POP:
        if (!OnTooltipPop(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    // ---------------------------------------------------------
    // Status bar notification messages
#if (_WIN32_IE >= 0x0400)
    case SBN_SIMPLEMODECHANGE:
        if (!OnStatusBarSimpleModeChange(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#endif

    // ---------------------------------------------------------
    // Up/Down Ctrl notification messages
    case UDN_DELTAPOS:
        if (!OnUpDownDeltaPos(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    // ---------------------------------------------------------
    // Listview notification messages
    case LVN_ITEMCHANGING:
        if (!OnListviewItemChanging(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case LVN_ITEMCHANGED:
        if (!OnListviewItemChanged(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_INSERTITEM:
        if (!OnListviewInsertItem(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_DELETEITEM:
        if (!OnListviewDeleteItem(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_DELETEALLITEMS:
        if (!OnListviewDeleteAllItems(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case LVN_BEGINLABELEDIT:
        if (!OnListviewBeginLabelEdit(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case LVN_ENDLABELEDIT:
        if (!OnListviewEndLabelEdit(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case LVN_COLUMNCLICK:
        if (!OnListviewColumnClick(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_BEGINDRAG:
        if (!OnListviewBeginDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_BEGINRDRAG:
        if (!OnListviewBeginRDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#if (_WIN32_IE >= 0x0300)
    case LVN_ODCACHEHINT:                               // unknown message
        if (!OnListviewOdCacheHit(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_ODFINDITEM:                                // unknown message
        if (!OnListviewOdFindItem(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_ITEMACTIVATE:                              // unknown message
        if (!OnListviewItemActivate(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_ODSTATECHANGED:                            // unknown message
        if (!OnListviewOdStateChanged(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif

#if (_WIN32_IE >= 0x0400)
    case LVN_HOTTRACK:                                  // unknown message
        if (!OnListviewHotTrack(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case LVN_GETINFOTIP:
        if (!OnListviewGetInfoTip(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_MARQUEEBEGIN:
        if (!OnListviewMarqueeBegin(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;
#endif

    case LVN_GETDISPINFO:
        if (!OnListviewGetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_SETDISPINFO:
        if (!OnListviewSetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case LVN_KEYDOWN:
        if (!OnListviewKeyDown(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    // ---------------------------------------------------------
    // Treeview notification messages
    
    case TVN_SELCHANGING:
        if (!OnTreeviewSelChanging(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_SELCHANGED:
        if (!OnTreeviewSelChanged(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_GETDISPINFO:
        if (!OnTreeviewGetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_SETDISPINFO:
        if (!OnTreeviewSetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_ITEMEXPANDING:
        if (!OnTreeviewItemExpanding(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TVN_ITEMEXPANDED:
        if (!OnTreeviewItemExpanded(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_BEGINDRAG:
        if (!OnTreeviewBeginDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_BEGINRDRAG:
        if (!OnTreeviewBeginRDrag(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_DELETEITEM:
        if (!OnTreeviewDeleteItem(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_BEGINLABELEDIT:
        if (!OnTreeviewBeginLabelEdit(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TVN_ENDLABELEDIT:
        if (!OnTreeviewEndLabelEdit(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case TVN_KEYDOWN:
        if (!OnTreeviewKeyDown(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#if (_WIN32_IE >= 0x0400)
    case TVN_GETINFOTIP:
        if (!OnTreeviewGetInfoTip(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TVN_SINGLEEXPAND:
        if (!OnTreeviewSingleExpand(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif


    // ---------------------------------------------------------
    // ComboBoxEx notification messages
#if (_WIN32_IE >= 0x0400)
    case CBEN_GETDISPINFO:                              // unknown message
        if (!OnCbeGetDispInfo(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case CBEN_INSERTITEM:                               // unknown message
        if (!OnCbeInsertItem(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case CBEN_DELETEITEM:                               // unknown message
        if (!OnCbeDeleteItem(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case CBEN_BEGINEDIT:                                // unknown message
        if (!OnCbeBeginEdit(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case CBEN_ENDEDIT:                                  // unknown message
        if (!OnCbeEndEdit(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

    case CBEN_DRAGBEGIN:
        if (!OnCbeDragBegin(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

#endif

    // ---------------------------------------------------------
    // Tab Ctrl notification messages
    case TCN_KEYDOWN:
        if (!OnTabKeyDown(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TCN_SELCHANGE:
        if (!OnTabSelChange(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case TCN_SELCHANGING:
        if (!OnTabSelChanging(wParam, lParam, lResult))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return lResult;

#if (_WIN32_IE >= 0x0400)
    case TCN_GETOBJECT:
        if (!OnTabGetObject(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif

    // ---------------------------------------------------------
    // Month/Calendar Ctrl notification messages
    case MCN_SELCHANGE:
        if (!OnMonCalSelChange(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case MCN_GETDAYSTATE:
        if (!OnMonCalGetDayState(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case MCN_SELECT:
        if (!OnMonCalSelect(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;


    // ---------------------------------------------------------
    // Date/Time Picker Ctrl notification messages
    case DTN_DATETIMECHANGE:
        if (!OnDateTimeChange(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case DTN_USERSTRING:
        if (!OnDateTimeUserString(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case DTN_WMKEYDOWN:
        if (!OnDateTimeWmKeyDown(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case DTN_FORMAT:
        if (!OnDateTimeFormat(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case DTN_FORMATQUERY:
        if (!OnDateTimeFormatQuery(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case DTN_DROPDOWN:
        if (!OnDateTimeDropDown(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case DTN_CLOSEUP:
        if (!OnDateTimeCloseUp(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    // ---------------------------------------------------------
    // Pager Ctrl notification messages
#if (_WIN32_IE >= 0x0400)
    case PGN_SCROLL:
        if (!OnPagerScroll(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;

    case PGN_CALCSIZE:
        if (!OnPagerCalcSize(wParam, lParam))
        {
            // We didn't handle it, so call 
            // the parent's default handler
            return CallParentDefault();
        }
        return 0;
#endif


    // ---------------------------------------------------------
    // MFC messages

    // lResult = 1 if processed by AfxWndProc
    case WM_QUERYAFXWNDPROC:                // 0x0360
        if (!OnQueryAfxWndProc(wParam, lParam, lResult))
            return Default();
       return lResult;

    // lParam = &AFX_SIZEPARENTPARAMS
    case WM_SIZEPARENT:                     // 0x0361
        if (!OnSizeParent(wParam, lParam, lResult))
            return Default();
        return lResult;

    // wParam = nIDS (or 0), lParam = lpszOther (or NULL)
    case WM_SETMESSAGESTRING:               // 0x0362
        if (!OnSetMessageString(wParam, lParam, lResult))
            return Default();
        return lResult;

    // wParam == bDisableIfNoHandler
    case WM_IDLEUPDATECMDUI:                // 0x0363
        if (!OnIdleUpdateCmdUi(wParam, lParam))
            return Default();
        return lResult;

    // (params unused) - sent to children
    case WM_INITIALUPDATE:                  // 0x0364
        if (!OnInitialUpdate(wParam, lParam))
            return Default();
        return 0;

    // lResult = TRUE/FALSE, lParam = dwContext
    case WM_COMMANDHELP:                    // 0x0365
        if (!OnCommandHelp(wParam, lParam))
            return Default();
        return TRUE;

    // lResult = dwContext, lParam = MAKELONG(x,y)
    case WM_HELPHITTEST:                    // 0x0366
        if (!OnHelpHitTest(wParam, lParam, lResult))
            return Default();
        return lResult;

    // (params unused)
    case WM_EXITHELPMODE:                   // 0x0367
        if (!OnExitHelpMode(wParam, lParam))
            return Default();
        return 0;

    // force RecalcLayout on frame window
    // (only for inplace frame windows)
    case WM_RECALCPARENT:                   // 0x0368
        if (!OnRecalcParent(wParam, lParam, lResult))
            return Default();
        return lResult;

    // special notify from COleResizeBar
    // wParam = ID of child window
    // lParam = lpRectNew (new position/size)
    case WM_SIZECHILD:                      // 0x0369
        if (!OnSizeChild(wParam, lParam, lResult))
            return Default();
        return lResult;

    // (params unused) causes idles to kick in
    case WM_KICKIDLE:                       // 0x036A
        if (!OnKickIdle(wParam, lParam))
            return Default();
        return 0;

    // lParam = HWND to use as centering parent
    case WM_QUERYCENTERWND:                 // 0x036B
        if (!OnQueryCenterWnd(wParam, lParam))
            return Default();
        return 0;

    // lResult = 0, disable during modal state
    // lResult = 1, don't disable
    case WM_DISABLEMODAL:                   // 0x036C
        if (!OnDisableModal(wParam, lParam, lResult))
            return Default();
        return lResult;

    // wParam combination of FS_* flags
    // See MFC documentation
    case WM_FLOATSTATUS:                    // 0x036D
        if (!OnFloatStatus(wParam, lParam, lResult))
            return Default();
        return lResult;

    // WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP 
    // but works with hierarchies of mixed processes 
    // (as is the case with OLE in-place activation)
    // wParam = nState (like WM_ACTIVATE)
	// lParam = pointer to HWND[2]
	//  lParam[0] = hWnd getting WM_ACTIVATE
	//  lParam[1] = hWndOther
    case WM_ACTIVATETOPLEVEL:               // 0x036E
        if (!OnActivateTopLevel(wParam, lParam))
            return Default();
        return 0;

    // lResult != 0 if 3D controls wanted
    case WM_QUERY3DCONTROLS:                // 0x036F
        if (!OnQuery3dControls(wParam, lParam, lResult))
            return Default();
        return lResult;

    // WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used 
    // internally by MFC's Windows sockets implementation.  
    // For more information, see sockcore.cpp
    case WM_SOCKET_NOTIFY:                  // 0x0373
        if (!OnSocketNotify(wParam, lParam))
            return Default();
        return 0;

    case WM_SOCKET_DEAD:                    // 0x0374
        if (!OnSocketDead(wParam, lParam))
            return Default();
        return 0;

    // same as WM_SETMESSAGESTRING except not popped 
    // if IsTracking()
    case WM_POPMESSAGESTRING:               // 0x0375
        if (!OnPopMessageString(wParam, lParam, lResult))
            return Default();
        return lResult;

    // Marker used while rearranging the message queue
    case WM_QUEUE_SENTINEL:                 // 0x0379
        if (!OnQueueSentinel(wParam, lParam))
            return Default();
        return 0;
    }

    // ---------------------------------------------------------
    // XSEL messages

    if (WM_SETPARENTNOTIFY == nMsg)         // XSEL message
    {
        // wParam = HWND of new parent
        return OnSetParentNotify(wParam, lParam);
    }
    else if (WM_PRENCDESTROY == nMsg)       // XSEL message
    {
        // We can't handle WM_NCDESTROY as we use this message
        // to remove the subclass handler.  Instead, XSEL sends
        // the message WM_PRENCDESTROY, which is where you put
        // your code you would normally put in your 
        // WM_NCDESTROY handler.

        // no valid parameters (0,0)
        return OnPreNcDestroy(wParam, lParam);
    }

    // default - call base class
    return CXSSubWndCtrl::DoWindowProc(nMsg, wParam, lParam);
}

// -------------------------------------------------------------
// Function  : 
//    CXSObject::SetParentNotify
// Purpose   : 
//    Call this function to set up Parent Notification
//    Reflection for the managed child window.
//    In your own code, you should never call SetParent to 
//    change the parent of your child window, unless you know
//    you have not set up Notification Reflection for the 
//    parent.  If you have set up Notification Reflection, use 
//    this clas to change the parent.  It also uninstalls the 
//    Notification event handler from the previous parent and
//    sets it up for the new parent.
// Parameters: 
//    CWnd* pWnd - The CWnd to become the new parent
//               - If pWnd is NULL, it will set up the
//                 Notification Reflection for the current
//                 parent.
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSObject::SetParentNotify(CWnd* pWnd)
{
    HWND hWnd = pWnd ? pWnd->m_hWnd : NULL;
    return DoGetWnd()->SendMessage(WM_SETPARENTNOTIFY, (WPARAM)hWnd, 0);
}

// -------------------------------------------------------------
// Function  : 
//    CXSObject::OnSetParentNotify
// Purpose   : 
//    Called when the window receives the XSEL message 
//    WM_PARENTNOTIFY.  This function is over-ridable by 
//    derived classes.
//    See info on SetParentNotify for a full explanation.
// Parameters: 
//    WPARAM wParam - HWND of new parent (may be NULL)
// Returns   : 
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSObject::OnSetParentNotify(WPARAM wParam, LPARAM lParam)
{
    // wParam = HWND of new parent

    // A request has been made to change the parent
    // We need this because if the current parent has 
    // been set up to reflect notification message, 
    // it will have to be removed and the new parent 
    // will have to be set up
    
    HWND hWnd = (HWND)wParam;

    // Verify the new parent
    if (!hWnd)
    {
        // If a NULL was passed, then the code
        // retrieves the parent handle
        hWnd = ::GetParent(DoGetWnd()->m_hWnd);

        // If it's still NULL, then we are at the
        // top-most level of windows
        if (NULL == hWnd)
            return FALSE;
    }

    // Sanity check
    ASSERT(::IsWindow(hWnd));

    // Make sure we're not trying to set a window to
    // be its own parent
    if (DoGetWnd()->m_hWnd != hWnd)
        return FALSE;

    // Check to make sure the passed window is
    // not already the parent
    if (hWnd && DoGetWnd()->GetParent() && 
        DoGetWnd()->GetParent()->m_hWnd != hWnd)
    {
        // Make windows set the new parent
        if (!::SetParent(DoGetWnd()->m_hWnd, hWnd))
            return FALSE;
    }
    else
    {
        return FALSE;
    }

    // See if the previous parent has been set up
    // for notification reflection
    BOOL bNotify = FALSE;
    if (m_Notify.IsSubclassed())
    {
        // Disengage it
        m_Notify.Remove();

        bNotify = TRUE;
    }

    if (bNotify)
    {
        // Now set up the new Parent for automatic 
        // message notification reflection
        CWnd* pParent = DoGetWnd()->GetParent();
        if (pParent && pParent->m_hWnd == hWnd)
            return m_Notify.DoInstall(pParent, this);
    }
    
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSObject::CallParentDefault
// Purpose   : 
//    Calls the parent window handler to handle the 
//    Notification message.
// Parameters: 
//    None
// Returns   : 
//    Depends on message
// -------------------------------------------------------------
LRESULT
CXSObject::CallParentDefault()
{
    // Is the parent subclassed to handle the Notification
    // Reflection, and, if so, is it still a valid window?
    if (m_Notify.IsSubclassed() && 
        ::IsWindow(m_Notify.DoGetWnd()->m_hWnd))
    {
        return m_Notify.Default();
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSObject::OnPreNcDestroy
// Purpose   : 
//    Called when WM_NCDESTROY is called.  WM_NCDESTROY is the 
//    last windows message received before a window is fully
//    destroyed.  The subclass handler uses this message to 
//    remove (uninstall) itself as the message proc handler.
//    Because the WM_NCDESTROY message is never received by this
//    framework, the virtual function OnPreNcDestroy is called
//    before the subclass handler removes itself.
// Parameters: 
//    Ignored.
// Returns   : 
//    TRUE if the message was handled, FALSE if it was not.
// -------------------------------------------------------------
BOOL 
CXSObject::OnPreNcDestroy(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//    CXSObject::On<MessageId>
// Purpose   : 
//    The functions below are the virtual function that you will 
//    override in your derived classes.  Each function returns
//    a BOOL.  This is quite simple.  If you handle the message,
//    return TRUE. If you want default processing, return FALSE.
//    Even if you handle it, but want the default processing,
//    you can return FALSE.
//    The function is passed the WPARAM and LPARAM paramaters.
//    Check with the message ID to see how they are used.
//    If the message is expected to return a value, a third 
//    parameter is used, a reference to LRESULT. Set this 
//    parameter to the value to return. If a function sets this
//    parameter, but returns FALSE, it will not be used.  In this
//    case, call Default() for regular messages, of call
//    CallParentDefault() for reflected messages and return TRUE.
// Parameters: 
//    WPARAM wParam - Depends on message
//    LPARAM lParam - Depends on message
//    LRESULT& lResult - Depends on message
// Returns   : 
//    BOOL - TRUE, the message was handled. 
//         - FALSE, do default processing.
// -------------------------------------------------------------


BOOL
CXSObject::OnCreate(WPARAM wParam, LPARAM lParam, 
                    LRESULT& lResult)
{
    // ---------------------------------------------------------
    // PLEASE NOTE!
    // ---------------------------------------------------------
    // This function will never be called.
    // ---------------------------------------------------------
    ASSERT(FALSE);
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDestroy
// Message : WM_DESTROY
// WPARAM  : 0
// LPARAM  : 0
// -------------------------------------------------------------
BOOL
CXSObject::OnDestroy(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMove
// Message : WM_MOVE
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMove(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSize
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSize(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnActivate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnActivate(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetFocus
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnKillFocus
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnEnable
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnEnable(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetRedraw
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetRedraw(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetText
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetText(WPARAM wParam, LPARAM lParam, 
                     LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetText
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetText(WPARAM wParam, LPARAM lParam, 
                     LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetTextLength
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetTextLength(WPARAM wParam, LPARAM lParam, 
                           LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPaint
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPaint(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnClose
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnClose(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueryEndSession
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueryEndSession(WPARAM wParam, LPARAM lParam, 
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQuit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQuit(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueryOpen
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueryOpen(WPARAM wParam, LPARAM lParam, 
                       LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnEraseBkgnd
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnEraseBkgnd(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSysColorChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSysColorChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnEndSession
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnEndSession(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnShowWindow
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnShowWindow(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSettingChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDevModeChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDevModeChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnActivateApp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnFontChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnFontChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTimeChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTimeChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCancelMode
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCancelMode(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetCursor
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMouseActivate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMouseActivate(WPARAM wParam, LPARAM lParam, 
                           LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnChildActivate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnChildActivate(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueueSync
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueueSync(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetMinMaxInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPaintIcon
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPaintIcon(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnIconEraseBkgnd
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNextDlgCtl
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNextDlgCtl(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSpoolerStatus
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSpoolerStatus(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDrawItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMeasureItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMeasureItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDeleteItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL
CXSObject::OnDeleteItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnVKeyToItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
int 
CXSObject::OnVKeyToItem(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCharToItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCharToItem(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetFont
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetFont(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetFont
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetFont(WPARAM wParam, LPARAM lParam, 
                     LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetHotKey
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetHotKey(WPARAM wParam, LPARAM lParam, 
                       LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetHotKey
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetHotKey(WPARAM wParam, LPARAM lParam, 
                       LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueryDragIcon
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueryDragIcon(WPARAM wParam, LPARAM lParam, 
                           LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCompareItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCompareItem(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCompacting
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCompacting(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnWindowPosChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnWindowPosChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnWindowPosChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPower
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPower(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCopyData
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCopyData(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotify
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotify(WPARAM wParam, LPARAM lParam, 
                    LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnInputLangChangeRequest
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnInputLangChangeRequest(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}
            
// -------------------------------------------------------------
// Function: OnInputLangChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnInputLangChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTCard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTCard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHelp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHelp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnUserChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnUserChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyFormat
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyFormat(WPARAM wParam, LPARAM lParam, 
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnContextMenu
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnContextMenu(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnStyleChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnStyleChanging(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnStyleChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnStyleChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDisplayChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetIcon
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetIcon(WPARAM wParam, LPARAM lParam, 
                     LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetIcon
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetIcon(WPARAM wParam, LPARAM lParam, 
                     LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcCreate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcCreate(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcDestroy(WPARAM wParam, LPARAM lParam)
{
    // ---------------------------------------------------------
    // PLEASE NOTE!
    // ---------------------------------------------------------
    // This function will never be called.  The subclass handler
    // uses the WM_NCDESTROY function to uninstall it's
    // window procedure from the window.  However, before doing 
    // this, it sends an XSEL message, WM_PRENCDESTROY, which
    // is caught in the virtual function OnPreNcDestroy.  Use
    // this function instead to do your WM_NCDESTROY work.
    // Immediately following this function, the subclass handler 
    // will be uninstalled and the HWND will be destroyed.
    // ---------------------------------------------------------
    ASSERT(FALSE);
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcCalcSize
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcCalcSize(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcHitTest
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcHitTest(WPARAM wParam, LPARAM lParam, 
                       LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcPaint
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcActivate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcActivate(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnGetDlgCode
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnGetDlgCode(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcMouseHover
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcMouseHover(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcMouseLeave
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcMouseLeave(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcMouseMove
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcMouseMove(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcLButtonDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcLButtonDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcLButtonUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcLButtonUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcLButtonDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcRButtonDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcRButtonDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcRButtonUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcRButtonUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcRButtonDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcMButtonDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcMButtonDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcMButtonUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcMButtonUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNcMButtonDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNcMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnKeyUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnChar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnChar(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDeadChar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDeadChar(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSysKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSysKeyUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSysKeyUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSysChar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSysChar(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSysDeadChar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSysDeadChar(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnInitDialog
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnInitDialog(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCommand
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCommand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSysCommand
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTimer
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTimer(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHScroll
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHScroll(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnVScroll
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnVScroll(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnInitMenu
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnInitMenu(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnInitMenuPopup
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnInitMenuPopup(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMenuSelect
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMenuSelect(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMenuChar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMenuChar(WPARAM wParam, LPARAM lParam, 
                      LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnEnterIdle
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnEnterIdle(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorMsgBox
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorMsgBox(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorEdit(WPARAM wParam, LPARAM lParam, 
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorListBox
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorListBox(WPARAM wParam, LPARAM lParam, 
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorBtn
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorBtn(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorDlg
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorDlg(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorScrollBar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorScrollBar(WPARAM wParam, LPARAM lParam, 
                               LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCtlColorStatic
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCtlColorStatic(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMouseMove
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnLButtonDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnLButtonUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnLButtonDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRButtonDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRButtonUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRButtonDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMButtonDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMButtonDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMButtonUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMButtonUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMButtonDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMouseWheel
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnParentNotify
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnParentNotify(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnEnterMenuLoop
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnEnterMenuLoop(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnExitMenuLoop
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnExitMenuLoop(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNextMenu
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNextMenu(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSizing
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSizing(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCaptureChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCaptureChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMoving
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMoving(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPowerBroadcast
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPowerBroadcast(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDeviceChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDeviceChange(WPARAM wParam, LPARAM lParam, 
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiCreate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiCreate(WPARAM wParam, LPARAM lParam, 
                       LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiDestroy
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiDestroy(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiActivate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiActivate(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiRestore
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiRestore(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiNext
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiNext(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiMaximize
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiMaximize(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiTile
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiTile(WPARAM wParam, LPARAM lParam, 
                     LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiCascade
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiCascade(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiIconArrange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiIconArrange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiGetActive
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiGetActive(WPARAM wParam, LPARAM lParam, 
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiSetMenu
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiSetMenu(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnEnterSizeMove
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnExitSizeMove
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDropFiles
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDropFiles(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMdiRefreshMenu
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMdiRefreshMenu(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMouseHover
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMouseLeave
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCut
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCut(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCopy
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCopy(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPaste
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPaste(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnClear
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnClear(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnUndo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnUndo(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRenderFormat
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRenderFormat(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRenderAllFormats
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRenderAllFormats(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDestroyClipboard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDestroyClipboard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDrawClipboard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDrawClipboard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPaintClipboard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPaintClipboard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnVScrollClipboard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnVScrollClipboard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSizeClipboard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSizeClipboard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnAskCbFormatName
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnAskCbFormatName(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnChangeCbChain
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnChangeCbChain(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHScrollClipboard
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHScrollClipboard(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueryNewPalette
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueryNewPalette(WPARAM wParam, LPARAM lParam, 
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPaletteIsChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPaletteIsChanging(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPaletteChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPaletteChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHotKey
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHotKey(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPrint
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPrint(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPrintClient
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPrintClient(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyOutOfMemory
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyOutOfMemory(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyClick
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyClick(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyDblClk(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyReturn
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyReturn(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyRClick
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyRClick(WPARAM wParam, LPARAM lParam,
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyRDblClk
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyRDblClk(WPARAM wParam, LPARAM lParam,
                           LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifySetFocus
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifySetFocus(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyKillFocus
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyKillFocus(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyCustomDraw
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyCustomDraw(WPARAM wParam, LPARAM lParam,
                              LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyHover
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyHover(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyNcHitTest
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyNcHitTest(WPARAM wParam, LPARAM lParam,
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyKeyDown(WPARAM wParam, LPARAM lParam,
                           LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyReleasedCapture
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyReleasedCapture(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifySetCursor
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifySetCursor(WPARAM wParam, LPARAM lParam,
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnNotifyChar
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnNotifyChar(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL 
CXSObject::OnNotifyTooltipsCreated(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetApply(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetGetObject(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetHelp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetKillActive(WPARAM wParam, LPARAM lParam, 
                                 LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetQueryCancel(WPARAM wParam, LPARAM lParam, 
                                  LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetReset(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetSetActive(WPARAM wParam, LPARAM lParam, 
                                LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetWizBack(WPARAM wParam, LPARAM lParam, 
                              LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetWizFinish(WPARAM wParam, LPARAM lParam, 
                                LRESULT& lResult)
{
    return FALSE;
}

BOOL 
CXSObject::OnPropSheetWizNext(WPARAM wParam, LPARAM lParam, 
                              LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderBeginDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderBeginDrag(WPARAM wParam, LPARAM lParam,
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderEndDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderEndDrag(WPARAM wParam, LPARAM lParam,
                           LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderItemChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderItemChanging(WPARAM wParam, LPARAM lParam, 
                                LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderItemChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderItemChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderItemClick
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderItemClick(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderItemDblClick
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderItemDblClick(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderDividerDblClick
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL
CXSObject::OnHeaderDividerDblClick(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderBeginTrack
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderBeginTrack(WPARAM wParam, LPARAM lParam, 
                              LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderEndTrack
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderEndTrack(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderTrack
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderTrack(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHeaderGetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHeaderGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarGetButtonInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarGetButtonInfo(WPARAM wParam, LPARAM lParam, 
                                  LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarBeginDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarBeginDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarEndDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarEndDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarBeginAdjust
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarBeginAdjust(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarEndAdjust
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarEndAdjust(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarReset
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarReset(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarQueryInsert
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarQueryInsert(WPARAM wParam, LPARAM lParam, 
                                LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarQueryDelete
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarQueryDelete(WPARAM wParam, LPARAM lParam, 
                                LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarToolbarChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarToolbarChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarCustHelp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarCustHelp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarDropDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarDropDown(WPARAM wParam, LPARAM lParam,
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarGetObject
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarGetObject(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarHotItemChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarHotItemChange(WPARAM wParam, LPARAM lParam,
                                  LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarDragOut
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarDragOut(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarDeletingButton
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarDeletingButton(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarGetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnToolbarGetInfoTip
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnToolbarGetInfoTip(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarHeightChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarHeightChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarGetObject
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarGetObject(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarLayoutChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarLayoutChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarAutoSize
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarAutoSize(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarBeginDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarBeginDrag(WPARAM wParam, LPARAM lParam,
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarEndDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarEndDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarDeletingBand
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarDeletingBand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarDeleteBand
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarDeleteBand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRebarChildSize
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRebarChildSize(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTooltipGetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL
CXSObject::OnTooltipGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTooltipNeedText
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTooltipNeedText(WPARAM wParam, LPARAM lParam)
{
    return OnTooltipGetDispInfo(wParam, lParam);
}

// -------------------------------------------------------------
// Function: OnTooltipShow
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTooltipShow(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTooltipPop
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTooltipPop(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnStatusBarSimpleModeChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnStatusBarSimpleModeChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnUpDownDeltaPos
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnUpDownDeltaPos(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewItemChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewItemChanging(WPARAM wParam, LPARAM lParam, 
                                  LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewItemChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewItemChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewInsertItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewInsertItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewDeleteItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewDeleteItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewDeleteAllItems
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewDeleteAllItems(WPARAM wParam, LPARAM lParam,
                                    LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewBeginLabelEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewBeginLabelEdit(WPARAM wParam, LPARAM lParam, 
                                    LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewEndLabelEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewEndLabelEdit(WPARAM wParam, LPARAM lParam,
                                  LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewColumnClick
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewColumnClick(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewBeginDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewBeginDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewBeginRDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewBeginRDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewOdCacheHit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewOdCacheHit(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewOdFindItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewOdFindItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewItemActivate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewItemActivate(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewOdStateChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewOdStateChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewHotTrack
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewHotTrack(WPARAM wParam, LPARAM lParam,
                              LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewGetInfoTip
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewGetInfoTip(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewMarqueeBegin
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewMarqueeBegin(WPARAM wParam, LPARAM lParam,
                                  LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewGetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewSetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewSetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnListviewKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnListviewKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewSelChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewSelChanging(WPARAM wParam, LPARAM lParam, 
                                 LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewSelChanged
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewSelChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewGetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewSetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewSetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewItemExpanding
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewItemExpanding(WPARAM wParam, LPARAM lParam, 
                                   LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewItemExpanded
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewItemExpanded(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewBeginDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewBeginDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewBeginRDrag
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewBeginRDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewDeleteItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewDeleteItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewBeginLabelEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewBeginLabelEdit(WPARAM wParam, LPARAM lParam, 
                                    LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewEndLabelEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewEndLabelEdit(WPARAM wParam, LPARAM lParam, 
                                  LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewGetInfoTip
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewGetInfoTip(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTreeviewSingleExpand
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTreeviewSingleExpand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCbeGetDispInfo
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCbeGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCbeInsertItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCbeInsertItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCbeDeleteItem
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCbeDeleteItem(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCbeBeginEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCbeBeginEdit(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCbeEndEdit
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCbeEndEdit(WPARAM wParam, LPARAM lParam,
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCbeDragBegin
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCbeDragBegin(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTabKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTabKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTabSelChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTabSelChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTabSelChanging
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTabSelChanging(WPARAM wParam, LPARAM lParam, 
                            LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnTabGetObject
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnTabGetObject(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMonCalSelChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMonCalSelChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMonCalGetDayState
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMonCalGetDayState(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnMonCalSelect
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnMonCalSelect(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeChange
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeChange(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeUserString
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeUserString(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeWmKeyDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeWmKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeFormat
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeFormat(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeFormatQuery
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeFormatQuery(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeDropDown
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeDropDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDateTimeCloseUp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDateTimeCloseUp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPagerScroll
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPagerScroll(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPagerCalcSize
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPagerCalcSize(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// =============================================================
// MFC Messages
// =============================================================

// -------------------------------------------------------------
// Function: OnQueryAfxWndProc
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueryAfxWndProc(WPARAM wParam, LPARAM lParam, 
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSizeParent
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSizeParent(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSetMessageString
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSetMessageString(WPARAM wParam, LPARAM lParam, 
                              LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnIdleUpdateCmdUi
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnIdleUpdateCmdUi(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnInitialUpdate
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnInitialUpdate(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnCommandHelp
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnHelpHitTest
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnHelpHitTest(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnExitHelpMode
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnExitHelpMode(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnRecalcParent
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnRecalcParent(WPARAM wParam, LPARAM lParam, 
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSizeChild
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSizeChild(WPARAM wParam, LPARAM lParam, 
                       LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnKickIdle
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueryCenterWnd
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueryCenterWnd(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnDisableModal
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnDisableModal(WPARAM wParam, LPARAM lParam, 
                          LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnFloatStatus
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnFloatStatus(WPARAM wParam, LPARAM lParam, 
                         LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnActivateTopLevel
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnActivateTopLevel(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQuery3dControls
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQuery3dControls(WPARAM wParam, LPARAM lParam, 
                             LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSocketNotify
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnSocketDead
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnSocketDead(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnPopMessageString
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnPopMessageString(WPARAM wParam, LPARAM lParam,
                              LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function: OnQueueSentinel
// Message : 
// WPARAM  :
// LPARAM  :
// -------------------------------------------------------------
BOOL 
CXSObject::OnQueueSentinel(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}


