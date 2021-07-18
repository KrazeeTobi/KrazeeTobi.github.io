//----------------------------------------------------------------------------------
// Copyright © 1995-1998, Xendra Software (http://www.xendra.com). All Rights Reserved."
//----------------------------------------------------------------------------------
// THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO AS 
// "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY 
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL XENDRA SOFTWARE OR ITS 
// SUPPLIERS BE LIABLE FOR ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, 
// INCIDENTAL, CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF 
// XENDRA SOFTWARE OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGES.
//
// This Software may be copied and distributed royalty-free subject to the following 
// conditions:
//
// 1. You must copy all Software without modification and must include all pages, if 
//    the Software is to be distributed without inclusion in your software product.  
//    If you are incorporating the Software in conjunction with and as part of your 
//    software product which adds substantial value, you may modify and include 
//    portions of the Software.  Any modifications or additions to the Software 
//    should be sent to submit@xendra.com in order to be incorporated into the 
//    Software for the benefit of all those who may use the Software.
//
// 2. You must place all copyright notices and other protective disclaimers and 
//    notices contained on the Software on all copies of the Software and your 
//    software product.  If you are incorporating the Software in conjunction with 
//    and as part of your software product which adds substantial value, you must 
//    display the following statement somewhere that is easily assessable by the 
//    User of your product:
//
//    "Various Extensions Copyright © 1995-1998, 
//     Xendra Software (http://www.xendra.com).  
//     All Rights Reserved."
//
// 3. Unless the Software is incorporated in your software product which adds 
//    substantial value, you may not distribute this Software for profit.
//
// 4. You may not incorporate the Software into any product that would compete against 
//    the Software.
//
// 5. You agree to indemnify, hold harmless, and defend Xendra Software and its 
//    suppliers from and against any claims or lawsuits, including attornys' fees, 
//    that arise or result from the use or distribution of your software product and 
//    any modifications to the Software.
//----------------------------------------------------------------------------------

#if !defined(AFX_SUBWNDCTRL_H__8D29800B_8683_11D1_875C_CBBE399A3F74__INCLUDED_)
#define AFX_SUBWNDCTRL_H__8D29800B_8683_11D1_875C_CBBE399A3F74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------
// Global messages
extern const UINT XSDATA WM_SETPARENTNOTIFY;
extern const UINT XSDATA WM_PRENCDESTROY;

// -------------------------------------------------------------
// Forward declaration
class CXSSubWndCtrlMap;

class XSCLASS
CXSSubWndCtrl : public CObject
{
protected:
    DECLARE_DYNAMIC(CXSSubWndCtrl);

    CWnd*           m_pSubWnd;     // The subclassed window
    WNDPROC         m_pOldWndProc; // Pointer to replaced wndproc
    CXSSubWndCtrl*  m_pNext;       // Next subclass handler
    CWnd*           m_pWindow;     // For passed HWND's

    // Derive this to handle specific messages
    virtual LRESULT DoWindowProc(UINT nMsg, WPARAM wParam, 
        LPARAM lParam);

    // Call this at the end of a message handler
    LRESULT Default();                    

public:
    CXSSubWndCtrl();
    virtual ~CXSSubWndCtrl();

    BOOL SubclassWindow(CWnd* pWnd);
    BOOL SubclassWindow(HWND hWnd);
    BOOL IsSubclassed();
    BOOL Remove();
    virtual CWnd* DoGetWnd();

    LRESULT CallWindowProc(UINT nMsg, WPARAM wParam, 
        LPARAM lParam);
};


class XSCLASS
CXSSubWndCtrlMap : private CMapPtrToPtr
{
public:
    CXSSubWndCtrlMap();
    virtual ~CXSSubWndCtrlMap();

    // static function to return "this"
    static CXSSubWndCtrlMap& GetSubWndCtrlMap();

    // Mapping functions
    void Add(HWND hwnd, CXSSubWndCtrl* pSubWnd);
    void Remove(CXSSubWndCtrl* pSubWnd);
    void RemoveAll(HWND hwnd);
    CXSSubWndCtrl* Lookup(HWND hwnd);
};

// -------------------------------------------------------------
// This macro allows us to access the static function 
// CXSSubWndCtrlMap::GetSubclassWndMap in a nice and clean 
// manner that makes it very readable.
#define macXSSubWndCtrlMap (CXSSubWndCtrlMap::GetSubWndCtrlMap())



#endif // !defined(AFX_SUBWNDCTRL_H__8D29800B_8683_11D1_875C_CBBE399A3F74__INCLUDED_)

