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

#if 0
#include "XSRect.h"
#include "XSMisc.h"
#include "XSDibApi.h"
#include "XSPalette.h"
#include "XSBitmap.h"
#include "XSSubWndCtrl.h"
#include "XSNotify.h"
#include "XSObject.h"
#include "XSBgCtrl.h"
#include "XSNodeData.h"
#include "XSCheckType.h"
#include "XSTreeNode.h"
#include "XSTreeCtrl.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXSTreeCtrl, CXSBgCtrl)

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::CXSTreeCtrl
// Purpose   :
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSTreeCtrl::CXSTreeCtrl()
{
    // Variable initialization
    m_bNodeAttrib = FALSE;
    m_bEdit = FALSE;
    m_bDrag = FALSE;
    m_dwDragDelay = 0;
    m_bRDrag = FALSE;
    m_nDragTimerID = 0;
    m_nEditTimerID = 0;
    m_nTimerTicks = 0;
    m_pDragImage = NULL;
    m_bNodeMove = FALSE;
    m_nTextPos = DT_LEFT|DT_SINGLELINE;
    m_nBoundText = 0;
    m_bTextBackground = FALSE;
    m_bNodeSelector = FALSE;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::~CXSTreeCtrl
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSTreeCtrl::~CXSTreeCtrl()
{
}

// -------------------------------------------------------------
// Function  :
//    CXSTreeCtrl::DoInstall
// Purpose   :
//    Installs the CXSTreeCtrl instance as the handler for the
//    passed CWnd pointer (either a CTreeCtrl or a CTreeView).
// Parameters:
//    CWnd* pWnd - The CWnd with a Treeview Control to attach to
// Returns   :
//    TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoInstall(CWnd* pWnd, BOOL bNotify)
{
    // Types this class can into install into
    if (!pWnd->IsKindOf(RUNTIME_CLASS(CTreeCtrl)) &&
        !pWnd->IsKindOf(RUNTIME_CLASS(CTreeView)))
    {
        // You are trying to install the wrong type!
        ASSERT(FALSE);
        return FALSE;
    }

    return CXSBgCtrl::DoInstall(pWnd, bNotify);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoCreateBackgroundBmp
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
CXSTreeCtrl::DoCreateBackgroundBmp(CDC* pDC, BOOL bState,
                                   CXSBitmap& bmp, CRect& rcDim)
{
    // If we're not in BackgroundNormal mode, then it's
    // OK to call the base class to do the processing
    if (BackgroundNormal == m_nBackgroundType)
    {
        m_crColor[0] = m_crColor[1] = ::GetSysColor(COLOR_WINDOW);
        return CXSBgCtrl::CreateGradientBmp(pDC, bState, bmp, rcDim);
    }
    else
        return CXSBgCtrl::DoCreateBackgroundBmp(pDC, bState, bmp, rcDim);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoIsSearchNodeValid
// Purpose   :
//  Called by CXSTreeNode::SearchItem and
//  CXSTreeNode::SearchItemByString to determine if searching
//  should continue or stop.
// Parameters:
//  CXSTreeNode& treeNode - The node that was found by the
//      search criteria.
// Returns   :
//  TRUE to stop search processing, FALSE to continue searching
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoIsSearchNodeValid(CXSTreeNode& treeNode)
{
    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoItemCopied
// Purpose   :
//  Called whenever a node is copied from one destination to
//  another.
// Parameters:
//  CXSTreeNode& nodeSrc - The source node
//  CXSTreeNode& nodeDest - The destination node
// Returns   :
//  Nothing
// -------------------------------------------------------------
void
CXSTreeCtrl::DoItemCopied(CXSTreeNode& nodeSrc,
                          CXSTreeNode& nodeDest)
{
    return;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoItemMoved
// Purpose   :
//  Called whenever a node is moved from one destination to
//  another.
// Parameters:
//  CXSTreeNode& nodeSrc - The source node
//  CXSTreeNode& nodeDest - The destination node
// Returns   :
//  Nothing
// -------------------------------------------------------------
void
CXSTreeCtrl::DoItemMoved(CXSTreeNode& nodeSrc,
                         CXSTreeNode& nodeDest)
{
    return;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoItemDelete
// Purpose   :
//  Called whenever a node is deleted.
// Parameters:
//  CXSTreeNode& treeNode - Node to be deleted
// Returns   :
//  Nothing
// -------------------------------------------------------------
void
CXSTreeCtrl::DoItemDelete(CXSTreeNode& treeNode)
{
    return;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::OnPaint
// Purpose   :
//  Does the necessary painting for the treeview control
// Parameters:
//  WPARAM wParam - As per WM_PAINT
//  LPARAM lParam - As per WM_PAINT
// Returns   :
//  TRUE if the message was handled, FALSE if it wasn't
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnPaint(WPARAM wParam, LPARAM lParam)
{
    // If we're not in BackgroundNormal mode, then it's
    // OK to call the base class to do the processing
    if (BackgroundNormal != m_nBackgroundType)
        return CXSBgCtrl::OnPaint(wParam, lParam);

    BOOL bResult;

    // If the window is an icon, no need to paint a background
    if (!DoCheckIconic(*DoGetWnd()))
    {
        // Just call the default handler
        Default();
        return TRUE;
    }

    // Get the window dimensions
    CRect rcBitmap = DoGetBitmapRect(*DoGetWnd());

    // Get background DC
    CDC* pDC = DoGetDC(*DoGetWnd());
    ASSERT(pDC);
    CDC dcDraw;
    dcDraw.CreateCompatibleDC(pDC);

    // Are we going to be creating a new bitmap?
    if (rcBitmap.Size() != m_szBackground)
    {
        // Invalidate bitmap
        m_bmpBackground[0].DeleteObject();

        // Set new dimensions
        m_szBackground = rcBitmap.Size();
    }

    // Get bitmap and determine if regeneration is required
    CXSBitmap& bmp = m_bmpBackground[0];
    BOOL bPaintIt = TRUE;

    // If the bitmap does not exist, then create one
    if (!bmp.GetSafeHandle())
    {
        bmp.CreateCompatibleBitmap(pDC, rcBitmap.Width(),
            rcBitmap.Height());

        // Select the bitmap into the DC so it gets painted on
        CBitmap* pOldBitmap = dcDraw.SelectObject(&bmp);

        // Paint the bitmap background
        bResult = ::XSPaint_Gradient(&dcDraw, rcBitmap,
            ::GetSysColor(COLOR_WINDOW), 1);
        ASSERT(bResult);  // problems? Sanity check...

        // Select old bitmap back into DC
        dcDraw.SelectObject(pOldBitmap);

        // Get ImageSize info
        if (bResult)
            bmp.Size();
        else
            bPaintIt = FALSE;
    }

    // If it's OK to paint and we have a valid bitmap,
    // paint the background
    if (bPaintIt && bmp.GetSafeHandle())
        bResult = DoPaint(pDC, bmp, rcBitmap);

    if (pDC)
        delete pDC;

    if (bResult)
        return TRUE;
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::OnEraseBkgnd
// Purpose   :
//  Defers background erasing
// Parameters:
//  As per WM_ERASEBKGND message
// Returns   :
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnEraseBkgnd(WPARAM wParam, LPARAM lParam,
                          LRESULT& lResult)
{
    // Don't allow background erasing
    lResult = FALSE;
    return TRUE;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoPaint
// Purpose   :
//  Called by OnPaint to handle extra painting that may be
//  needed.
// Parameters:
//  CDC* pDC - DC to paint into
//  CXSBitmap& bmp - Bitmap to use for painting. You must select
//      this into the DC yourself.
//  CRect rcDim - The dimensions of where to paint.
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoPaint(CDC* pDC, CXSBitmap& bmp, CRect rcDim)
{
    // By now, the background bitmap is ready to be painted.
    // What we want to accomplish in this function, is to
    // paint the actual tree control.  We don't do this on
    // our background bitmap because it will only change if
    // the active state changes, or the size changes.  Things
    // would look pretty messy if we kept painting the
    // Treeview Control over it each time.
    // Instead, we create a new bitmap, copy our background
    // to it and use that one as the canvas for drawing the
    // Treeview Control.

    // Create the memory DC's
    CDC dcDraw, dcTree;
    dcDraw.CreateCompatibleDC(pDC);
    dcTree.CreateCompatibleDC(pDC);

    // Declare the bitmaps
    CXSBitmap bmpDraw;
    CBitmap*  pbmpDraw;
    CXSBitmap bmpTree;
    CBitmap*  pbmpTree;

    // Create the bitmaps
    bmpDraw.CreateCompatibleBitmap(pDC, rcDim.Width(),
        rcDim.Height());
    bmpTree.CreateCompatibleBitmap(pDC, rcDim.Width(),
        rcDim.Height());

    // Select our bitmaps into their respective DC's
    pbmpDraw = dcDraw.SelectObject(&bmpDraw);
    pbmpTree = dcTree.SelectObject(&bmpTree);

    // Paint the actual background into the Draw DC
    bmp.DoPaintNormal(&dcDraw, rcDim, FALSE);

    // Paint the Treeview Control
    DoPaintTreeCtrl(&dcTree);

    // Deselect the bmpTree from the dcTree
    // so we can paint with it
    dcTree.SelectObject(pbmpTree);

    // Now, transparently paint the Treeview
    // control on top of the dcDraw
    bmpTree.DoPaintTransparent(&dcDraw, rcDim,
        ::GetSysColor(COLOR_WINDOW), FALSE);

    // Deselect the bmpDraw so we can paint it to the screen DC
    dcDraw.SelectObject(pbmpDraw);

    // Paint the bmpDraw bitmap
    return CXSBgCtrl::DoPaint(pDC, bmpDraw, rcDim);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::DoPaintTreeControl
// Purpose   :
//  Called by DoPaint to paint the actual treeview control
// Parameters:
//  CDC* pDC - the DC to use for painting
// Returns   :
//  Nothing
// -------------------------------------------------------------
void
CXSTreeCtrl::DoPaintTreeCtrl(CDC* pDC)
{
    // Draw the Tree into the pDC
    // Let the TreeView control do it's default drawing
    // into the memory DC
    //
    // Our objective here is to really call CWnd:DefWindowProc.
    // However, since this is a protected function and we're not
    // derived from CWnd, we call our own base implementation.
    // It eventually makes it to the proper routine.
    CXSSubWndCtrl::DoWindowProc(WM_PAINT, (WPARAM)pDC->m_hDC, 0);

    if (m_bNodeAttrib)
    {
        // Now do the node data (custom fonts and colors)
        CXSTreeNode treeNode = GetFirstVisibleItem();
        int nCount = GetTreeCtrl()->GetVisibleCount() + 2;
        while (--nCount && treeNode.GetSafeHandle())
        {
            UINT nFlags = TVIS_DROPHILITED | TVIS_SELECTED;
            int nItemState = treeNode.GetItemState(nFlags);

            // We do not want to handle selected or drop
            // highlighted nodes if m_bNodeSelector = FALSE
            if (!m_bNodeSelector && !(nItemState & nFlags))
            {
                DoDrawNodeText(pDC, treeNode);
            }
            else if(m_bNodeSelector)
            {
                DoDrawNodeText(pDC, treeNode);

                if ((treeNode.GetItemState(nFlags) & nFlags))
                {
                    DoDrawNodeSelector(pDC, treeNode);
                }
            }

            treeNode = treeNode.GetNextVisibleItem();
        }
    }
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::InEditMode
// Purpose   :
//
// Parameters:
//
// Returns   :
//
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::InEditMode()
{
    return m_bEdit;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::InDragMode
// Purpose   :
//
// Parameters:
//
// Returns   :
//
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::InDragMode()
{
    return m_bDrag;
}


// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::OnMouseMove
// Purpose   :
//  Called by the system when the mouse is moved
// Parameters:
//  As per WM_MOUSEMOVE message
// Returns   :
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
    if (InDragMode() && m_pDragImage)
    {
        UINT nFlags = (UINT)wParam;
        CPoint pt(LOWORD(lParam), HIWORD(lParam));
        CPoint point = pt;

        GetTreeCtrl()->ClientToScreen(&pt);

        CImageList::DragMove(pt);

        CXSTreeNode treeNode(HitTest(point, &nFlags));
        if (treeNode.GetSafeHandle() && treeNode !=
            m_nodeDrop && DoCanDropTarget(treeNode))
        {
            CImageList::DragShowNolock(FALSE);

            // Programmatically select the node
            treeNode.SelectDropTarget();

            // Save the node information
            m_nodeDrop = treeNode;

            // Does the user want node expansion
            if ((nFlags & TVHT_ONITEMBUTTON) &&
                m_nodeDrop.ItemHasChildren())
            {
                DoGetWnd()->LockWindowUpdate();
                m_nodeDrop.Expand(TVE_EXPAND);
                DoGetWnd()->UnlockWindowUpdate();
                UpdateWindow();
            }

            CImageList::DragShowNolock(TRUE);
        }

    }

    return CXSBgCtrl::OnMouseMove(wParam, lParam);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnKeyDown
// Purpose   : 
//  Called by the system when a key press is detected
// Parameters: 
//  As per WM_KEYDOWN message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
    int nVertKey = (int)wParam;
    long lKeyData = (long)lParam;

    if (InDragMode() && m_pDragImage)
    {
        if (VK_ESCAPE == nVertKey)
        {
            m_bDrag = FALSE;
            CImageList::DragLeave(NULL);
            CImageList::EndDrag();
            ::ReleaseCapture();

            delete m_pDragImage;

            // Remove the drop target highlighting
            GetTreeCtrl()->SelectDropTarget(NULL);

            // Kill timer
            GetTreeCtrl()->KillTimer(ID_DRAG_TIMER);
            m_nDragTimerID = 0;

            return TRUE;
        }
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnLButtonDown
// Purpose   : 
//  Called by the system when a left mouse button click down is 
//  detected
// Parameters: 
//  As per WM_LBUTTONDOWN message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
    UINT nFlags = (UINT)wParam;
    CPoint point(LOWORD(lParam), HIWORD(lParam));
    CXSTreeNode treeNode = HitTest(point, &nFlags);

    if (treeNode.GetSafeHandle())
    {
        // Did User click on a state image?
        if (nFlags & TVHT_ONITEMSTATEICON)
        {
            if (DoSetCheck(treeNode))
                treeNode.SetCheck(DoGetCheckType(treeNode));
            return TRUE;
        }
        
        if(m_bNodeAttrib)
        {
            if (treeNode.GetNodeRect().PtInRect(point))
            {
                // See if the point is in the regular box, 
                // or our extended box
                CRect rect;
                treeNode.GetItemRect(&rect, TRUE);
                if (rect.PtInRect(point))
                    return FALSE;

                // Adjust the point so it is in the rect
                MSG& msg = AfxGetThreadState()->m_lastSentMsg;
                msg.lParam = MAKELPARAM(rect.left + rect.Width() / 2, 
                    rect.top + rect.Height() / 2); // set new point
                Default();
                return TRUE;
            }
        }
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnLButtonUp
// Purpose   : 
//  Called by the system when a left mouse button click up is 
//  detected
// Parameters: 
//  As per WM_LBUTTONUP message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL 
CXSTreeCtrl::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
    InvalidateWindow();

    if (InDragMode() && m_pDragImage)
    {
        DoGetWnd()->LockWindowUpdate();

        m_bDrag = FALSE;
        CImageList::DragLeave(NULL);
        CImageList::EndDrag();
        ::ReleaseCapture();

        delete m_pDragImage;

        // Remove the drop target highlighting
        GetTreeCtrl()->SelectDropTarget(NULL);

        // Kill timer
        GetTreeCtrl()->KillTimer(ID_DRAG_TIMER);
        m_nDragTimerID = 0;

        if (m_nodeDrop.GetSafeHandle() && 
            m_nodeDrop.ItemHasChildren())
        {
            m_nodeDrop.Expand(TVE_EXPAND);
        }

        CXSTreeNode treeNode;
        if (m_nodeDrop.GetSafeHandle())
        {
            treeNode = m_nodeDrag.MoveItem(m_nodeDrop, TVI_LAST);
            treeNode.SelectItem();
        }

        DoGetWnd()->UnlockWindowUpdate();
        UpdateWindow();

        return TRUE;
    }
    else
    {
        // Get the number of milliseconds since Windows started
        m_dwDragDelay = GetTickCount();
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTimer
// Purpose   : 
//  Called by the system when a timer event occurs
// Parameters: 
//  As per WM_ONTIMER message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTimer(WPARAM wParam, LPARAM lParam)
{
    UINT nTimerID = (UINT)wParam;
    TIMERPROC* pfnTimerProc = (TIMERPROC*)lParam;

    if (ID_EDIT_TIMER == nTimerID)
    {
        if (!m_bEdit)
        {
            GetTreeCtrl()->KillTimer(ID_EDIT_TIMER);
            m_nEditTimerID = 0;
            return TRUE;
        }

        // Because some code wants to change the size of the 
        // edit window after we are finished with it, the 
        // timer is set up to set it to the size we want.
        if (m_nodeEdit.GetSafeHandle())
        {
            CRect rect = GetNodeRect(m_nodeEdit);
            CEdit* pEdit = GetEditControl();
            if (pEdit)
            {
                pEdit->MoveWindow(rect);
            }
        }

        GetTreeCtrl()->KillTimer(ID_EDIT_TIMER);
        return TRUE;
    }

    if (ID_DRAG_TIMER != nTimerID)
        return FALSE;

    m_nTimerTicks++;

    POINT pt;
    ::GetCursorPos(&pt);
    CXSClientRect rect(*GetTreeCtrl());
    rect.ToWindow();

    // We use screen coordinates because the DragEnter uses the
    // Desktop window

    if (pt.y < rect.top + 10)
    {
        // Scroll up
        // Scroll slowly if cursor near the treeview control
        int nSlowScroll = 10 - ((rect.top + 5) - pt.y) / 5;
        if (0 == (m_nTimerTicks % (nSlowScroll > 0 ? 
            nSlowScroll : 1)))
        {
            CXSTreeNode treeNode;
            if (m_nodeDrop.GetSafeHandle())
            {
                treeNode = m_nodeDrop.GetPrevVisibleItem();
                if (treeNode == m_nodeDrag)
                    treeNode = m_nodeDrag.GetPrevVisibleItem();
            }
            else
                treeNode = GetFirstVisibleItem();

            if (!treeNode.GetSafeHandle())
                return TRUE;
            else
                treeNode.EnsureVisible();
            
            if (treeNode.GetSafeHandle() && 
                DoCanDropTarget(treeNode))
            {
                treeNode.SelectDropTarget();
                m_nodeDrop = treeNode;
            }
        }
    }
    else if (pt.y > rect.bottom - 10)
    {
        // Scroll Down
        // Scroll slowly if cursor near the treeview control
        int nSlowScroll = 10 - (pt.y - (rect.bottom - 5)) / 5;
        
        if (0 == (m_nTimerTicks % (nSlowScroll > 0 ? 
            nSlowScroll : 1)))
        {
        CXSTreeNode treeNode;
        if (m_nodeDrop.GetSafeHandle())
        {
            treeNode = m_nodeDrop.GetNextVisibleItem();
            if (treeNode == m_nodeDrag)
                treeNode = m_nodeDrag.GetNextVisibleItem();
        }
        else
        {
            treeNode = GetFirstVisibleItem();
            int nCount = GetVisibleCount();
            for (int i = 0; i < nCount - 1; ++i)
            {
                if (treeNode.GetSafeHandle())
                    treeNode = treeNode.GetNextVisibleItem();
            }
        }

        if (!treeNode.GetSafeHandle())
            return TRUE;
        else
            treeNode.EnsureVisible();

            if (treeNode.GetSafeHandle() && 
                DoCanDropTarget(treeNode))
            {
                treeNode.SelectDropTarget();
                m_nodeDrop = treeNode;
            }
        }
    }

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnHScroll
// Purpose   : 
//  Called by the system when a horizontal scroll is detected
// Parameters: 
//  As per WM_HSCROLL message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL 
CXSTreeCtrl::OnHScroll(WPARAM wParam, LPARAM lParam)
{
    // Invalidating the window turns off the sliding motion
    // that looks ugly with colored text or background bitmaps
    InvalidateWindow();

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnVScroll
// Purpose   : 
//  Called by the system when a vertical scroll is detected
// Parameters: 
//  As per WM_VSCROLL message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL 
CXSTreeCtrl::OnVScroll(WPARAM wParam, LPARAM lParam)
{
    // Invalidating the window turns off the sliding motion
    // that looks ugly with colored text or background bitmaps
    InvalidateWindow();

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewSelChanging
// Purpose   : 
//  Called by the system when the treeview control's selection 
//  is changing
// Parameters: 
//  As per TVN_SELCHANGING message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL 
CXSTreeCtrl::OnTreeviewSelChanging(WPARAM wParam, LPARAM lParam, 
                                   LRESULT& lResult)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewSelChanged
// Purpose   : 
//  Called by the system when the treeview control's selection 
//  is changed
// Parameters: 
//  As per TVN_SELCHANGED message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewSelChanged(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewGetDispInfo
// Purpose   : 
//  Called by the system when information is needed to display 
//  or sort an item
// Parameters: 
//  As per TVN_GETDISPINFO message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewGetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewSetDispInfo
// Purpose   : 
//  Called by the system when information about an item needs to 
//  be updated
// Parameters: 
//  As per TVN_SETDISPINFO message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewSetDispInfo(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewItemExpanding
// Purpose   : 
//  Called by the system when an item is expanding
// Parameters: 
//  As per TVN_ITEMEXPANDING message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewItemExpanding(WPARAM wParam, LPARAM lParam, 
                                     LRESULT& lResult)
{
    DoGetWnd()->LockWindowUpdate();

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewItemExpanded
// Purpose   : 
//  Called by the system when an item is expanded
// Parameters: 
//  As per TVN_ITEMEXPANDED message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewItemExpanded(WPARAM wParam, LPARAM lParam)
{
    DoGetWnd()->UnlockWindowUpdate();

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewBeginDrag
// Purpose   : 
//  Called by the system when a drag-and-drop operation is about 
//  to begin
// Parameters: 
//  As per TVN_BEGINDRAG message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewBeginDrag(WPARAM wParam, LPARAM lParam)
{
    NM_TREEVIEW* pnmTreeView = (NM_TREEVIEW*)lParam;

    ASSERT(pnmTreeView->itemNew.hItem);

    // Don't begin drag unless enough time has elapsed to prevent
    // inadvertant drag and drop operations
    if ((GetTickCount() - m_dwDragDelay) < DRAG_DELAY)
        return FALSE;

    m_nodeDrag.Reset(this);
    m_nodeDrop.Reset(this);

    if (!FindNode(pnmTreeView->itemNew.hItem, m_nodeDrag))
        return FALSE;

    m_nodeDrag.SelectItem();

    if (!DoCanDragNode(m_nodeDrag))
        return FALSE;

    // Get the image for dragging
    m_pDragImage = GetTreeCtrl()->CreateDragImage(m_nodeDrag);

	// CreateDragImage returns NULL if there is no image list
	// associated with the tree control
	if (!m_pDragImage)
		return FALSE;

	m_bDrag = TRUE;
	m_pDragImage->BeginDrag(0, CPoint(-15, -15));
	POINT pt = pnmTreeView->ptDrag;
	GetTreeCtrl()->ClientToScreen(&pt);
	m_pDragImage->DragEnter(NULL, pt);
	GetTreeCtrl()->SetCapture();

    // Set up the timer so we can do scrolling during the drag
    m_nDragTimerID = GetTreeCtrl()->SetTimer(ID_DRAG_TIMER, 
                                             25, NULL);

    return CXSBgCtrl::OnTreeviewBeginDrag(wParam, lParam);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewBeginRDrag
// Purpose   : 
//  Called by the system when a right mouse button drag-and-drop 
//  operation is about to begin
// Parameters: 
//  As per TVN_BEGINRDRAG message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewBeginRDrag(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewDeleteItem
// Purpose   : 
//  Called by the system when an item is removed from the
//  treeview control (if m_bNodeMove==TRUE, this is a move and 
//  orginal item is being deleted).
// Parameters: 
//  As per TVN_DELETEITEM message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewDeleteItem(WPARAM wParam, LPARAM lParam)
{
    NM_TREEVIEW* pnmTreeView = (NM_TREEVIEW FAR*)lParam;
    TV_ITEM& tvItem = pnmTreeView->itemOld;

    if (!tvItem.hItem)
        return FALSE;

    CXSTreeNode treeNode(tvItem.hItem, this);

    // See if it exists in our map
    if (FindNode(treeNode, treeNode))
    {
        // Call virtual function
        DoItemDelete(treeNode);

        // Remove it from the map
        RemoveNode(treeNode);

        InvalidateWindow();
        UpdateWindow();

        return TRUE;
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewBeginLabelEdit
// Purpose   : 
//  Called by the system when an in-place editing session on an 
//  item is about to occur.
// Parameters: 
//  As per TVNBEGINLABELEDIT message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewBeginLabelEdit(WPARAM wParam, LPARAM lParam, 
                                      LRESULT& lResult)
{
    TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)lParam;

    CXSTreeNode treeNode(this);
    if (!pTVDispInfo->item.hItem)
    {
        lResult = TRUE;  // Cancel editing
        return TRUE;
    }
    else
    {
        FindNode(pTVDispInfo->item.hItem, treeNode);
        if (!treeNode.GetSafeHandle())
        {
            lResult = TRUE;
            return TRUE;
        }
    }

    // Set limitations on text edit
    CEdit* pEdit = GetEditControl();
    pEdit->SetLimitText(treeNode.GetNodeLabelLen());

    // Set up a timer
    m_nodeEdit = treeNode;
    m_nEditTimerID = GetTreeCtrl()->SetTimer(ID_EDIT_TIMER, 
                                             25, NULL);

    m_bEdit = TRUE;

    lResult = FALSE;
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewEndLabelEdit
// Purpose   : 
//  Called by the system when an in-place editing session is 
//  ending.
// Parameters: 
//  As per TVN_ENDLABELEDIT message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewEndLabelEdit(WPARAM wParam, LPARAM lParam, 
                                    LRESULT& lResult)
{
    TV_DISPINFO* ptvDispInfo = (TV_DISPINFO*)lParam;

    if (InEditMode())
    {
        // Call virtual handler for derived classes
        lResult = DoEndLabelEdit(ptvDispInfo);

        m_bEdit = FALSE;
    }

    CXSBgCtrl::OnTreeviewEndLabelEdit(wParam, lParam, lResult);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::OnTreeviewKeyDown
// Purpose   : 
//  Called by the systen when a key press down is detected.
// Parameters: 
//  As per TVN_KEYDOWN message
// Returns   : 
//  TRUE if the message was handled, FALSE if it was not
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::OnTreeviewKeyDown(WPARAM wParam, LPARAM lParam)
{
    TV_KEYDOWN* ptvKeyDown = (TV_KEYDOWN*)lParam;

    // Check for Delete key

    return FALSE;
}

// -------------------------------------------------------------

// -------------------------------------------------------------
// Function  :
//  CXSTreeCtrl::GetTreeCtrl()
// Purpose   :
//  Returns the CTreeCtrl associated with this object
// Parameters: 
//  None
// Returns   : 
//  CTreeCtrl* - A pointer to the CTreeCtrl associated with 
//  this object
// -------------------------------------------------------------
CTreeCtrl*
CXSTreeCtrl::GetTreeCtrl()
{
    ASSERT_VALID(m_pWnd);

    if (DoGetWnd()->IsKindOf(RUNTIME_CLASS(CTreeCtrl)))
        return (CTreeCtrl*)m_pWnd;
    else if (DoGetWnd()->IsKindOf(RUNTIME_CLASS(CTreeView)))
        return &(CTreeCtrl&)((CTreeView*)m_pWnd)->GetTreeCtrl();
    else
    {
        ASSERT(FALSE);
        return NULL;
    }
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::AddNode
// Purpose   : 
//  Add a CXSTreeNode to the CMap list
// Parameters: 
//  CXSTreeNode& treeNode - reference to the node object to add
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::AddNode(CXSTreeNode& treeNode)
{
    ASSERT(treeNode.GetSafeHandle());
    m_mapTreeNode.SetAt(HTREEITEM(treeNode), treeNode);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::RemoveNode
// Purpose   : 
//  removes a node object from the CMap list
// Parameters: 
//  CXSTreeNode& treeNode - reference to the object to remove
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::RemoveNode(CXSTreeNode& treeNode)
{
    ASSERT(treeNode.GetSafeHandle());
    return m_mapTreeNode.RemoveKey(HTREEITEM(treeNode));
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::FindNode
// Purpose   : 
//  Look a node object from the CMap list
// Parameters: 
//  HTREEITEM hTreeItem - TreeItem handle of node object to find
//  CXSTreeNode& treeNode - Node object to fill with found data
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::FindNode(HTREEITEM hTreeItem, CXSTreeNode& treeNode)
{
    ASSERT(hTreeItem);
    return m_mapTreeNode.Lookup(hTreeItem, treeNode);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetStartPosition
// Purpose   : 
//  Starts a map iteration by returning a POSITION value that 
//  can be passed to a GetNextAssoc call. The iteration sequence 
//  is not predictable; therefore, the "first element in the 
//  map" has no special significance.
// Parameters: 
//  None
// Returns   : 
//  A POSITION value that indicates a starting position for 
//  iterating the map; or NULL if the map is empty.
// -------------------------------------------------------------
POSITION
CXSTreeCtrl::GetStartPosition()
{
    return m_mapTreeNode.GetStartPosition();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetNextAssoc
// Purpose   : 
//  Retrieves the map element at pos, then updates pos to refer 
//  to the next element in the map. This function is most useful 
//  for iterating through all the elements in the map. Note that 
//  the position sequence is not necessarily the same as the key 
//  value sequence. 
// Parameters: 
//  POSITION pos - Specifies a reference to a POSITION value 
//      returned by a previous GetNextAssoc or GetStartPosition 
//      call. 
//  HTREEITEM hTreeItem - Specifies the returned key of the 
//      retrieved element 
//  CXSTreeNode& treeNode - Specifies the returned value of the 
//  retrieved node object
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeCtrl::GetNextAssoc(POSITION pos, HTREEITEM hTreeItem, 
                          CXSTreeNode& treeNode)
{
    m_mapTreeNode.GetNextAssoc(pos, (void*&)hTreeItem, treeNode);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetNodeData
// Purpose   : 
//  Sets the node data to be associated with this node object
// Parameters: 
//  CXSTreeNode& treeNode - The node object
//  CXSNodeData& nodeData - The Node data
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::SetNodeData(CXSTreeNode& treeNode, 
                         CXSNodeData& nodeData)
{
    ASSERT(treeNode.GetSafeHandle());
	if (m_mapTreeNode.Lookup(HTREEITEM(treeNode), treeNode))
    {
        treeNode.m_NodeData = nodeData;
        m_mapTreeNode.SetAt(HTREEITEM(treeNode), treeNode);
        return TRUE;
    }
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetNodeColor
// Purpose   : 
//  Sets the node color to be associated with this node object
// Parameters: 
//  CXSTreeNode& treeNode - The node object
//  COLORREF crFore - The foreground color (text) for the node 
//      object
//  COLORREF crBack - The background color (window) for the node
//      object
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::SetNodeColor(CXSTreeNode& treeNode, COLORREF crFore, 
                          COLORREF crBack)
{
    ASSERT(treeNode.GetSafeHandle());

	if (m_mapTreeNode.Lookup(HTREEITEM(treeNode), treeNode))
    {
        treeNode.m_NodeData.m_crFore = crFore;
        treeNode.m_NodeData.m_crBack = crBack;
        m_mapTreeNode.SetAt(HTREEITEM(treeNode), treeNode);
        return TRUE;
    }
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetNodeFont
// Purpose   : 
//  Sets the node font information to be associated with this 
//  node object
// Parameters: 
//  CXSTreeNode& treeNode - The node object
//  LOGFONT& logFont - The font info to be associated with the 
//      node object
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::SetNodeFont(CXSTreeNode& treeNode, LOGFONT& logFont)
{
    ASSERT(treeNode.GetSafeHandle());

	if (m_mapTreeNode.Lookup(HTREEITEM(treeNode), treeNode))
    {
        treeNode.m_NodeData.m_lfLogFont = logFont;
        m_mapTreeNode.SetAt(HTREEITEM(treeNode), treeNode);
        return TRUE;
    }
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetNodeLabelLen
// Purpose   : 
//  Sets the maximum allowable edit length for this node object 
//  when doing in-place editing
// Parameters: 
//  CXSTreeNode& treeNode - The node object
//  int nLength - The alolowable length
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::SetNodeLabelLen(CXSTreeNode& treeNode, int nLength)
{
    ASSERT(treeNode.GetSafeHandle());

	if (m_mapTreeNode.Lookup(HTREEITEM(treeNode), treeNode))
        RemoveNode(treeNode);

    treeNode.m_NodeData.m_nLabelLen = nLength;
    AddNode(treeNode);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetFirstVisibleItem
// Purpose   : 
//  Retrieves the first visible item of the tree view control
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - The first visible node object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::GetFirstVisibleItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetFirstVisibleItem();
    CXSTreeNode treeNode(this);
    if (hTreeItem)
    {
        FindNode(hTreeItem, treeNode);
        return treeNode;
    }
    else
        return CXSTreeNode(this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetNextVisibleItem
// Purpose   : 
//  Retrieves the next visible item of the tree view control 
//  from the passed node obejct
// Parameters: 
//  CXSTreeNode& treeNode - operation begins from this object
// Returns   : 
//  CXSTreeNode - The next visible node object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::GetNextVisibleItem(CXSTreeNode& treeNode)
{
    HTREEITEM hTreeItem = 
        GetTreeCtrl()->GetNextVisibleItem(treeNode);
    CXSTreeNode treeNode1;
    if (hTreeItem)
        FindNode(hTreeItem, treeNode1);
    return treeNode1;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetPrevVisibleItem
// Purpose   : 
//  Retrieves the previous visible item of the tree view control 
//  from the passed node obejct
// Parameters: 
//  CXSTreeNode& treeNode - operation begins from this object
// Returns   : 
//  CXSTreeNode - The previous visible node object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::GetPrevVisibleItem(CXSTreeNode& treeNode)
{
    HTREEITEM hTreeItem = 
        GetTreeCtrl()->GetPrevVisibleItem(treeNode);
    CXSTreeNode treeNode1;
    if (hTreeItem)
        FindNode(hTreeItem, treeNode1);
    return treeNode1;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetSelectedItem
// Purpose   : 
//  Retrieves the currently selected item of the tree view 
//  control.
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - The selected node object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::GetSelectedItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetSelectedItem();
    CXSTreeNode treeNode(this);
    if (hTreeItem)
    {
        FindNode(hTreeItem, treeNode);
        return treeNode;
    }
    else
        return CXSTreeNode(this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetDropHilightItem
// Purpose   : 
//  Retrieves the item that is the target of a drag-and-drop 
//  operation.
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - The drop-highlighted node object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::GetDropHilightItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetDropHilightItem();
    CXSTreeNode treeNode(this);
    if (hTreeItem)
    {
        FindNode(hTreeItem, treeNode);
        return treeNode;
    }
    else
        return CXSTreeNode(this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetRootItem
// Purpose   : 
//  Retrieves the root item of the tree view control
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - The root node object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::GetRootItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetRootItem();
    CXSTreeNode treeNode(this);
    if (hTreeItem)
    {
        FindNode(hTreeItem, treeNode);
        return treeNode;
    }
    else
        return CXSTreeNode(this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetItem
// Purpose   : 
//  Sets the attributes of the specified tree view item
// Parameters: 
//  TV_ITEM* pItem - A pointer to a TV_ITEM structure that 
//      contains the new item attributes. For more information 
//      on the TV_ITEM structure, see CTreeCtrl::GetItem. 
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::SetItem(TV_ITEM* pItem)
{
    return GetTreeCtrl()->SetItem(pItem);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetVisibleCount
// Purpose   : 
//  Retrieves a count of the possible visible items in a tree 
//  view control.
// Parameters: 
//  None
// Returns   : 
//  UINT - The number of possible visible items
// -------------------------------------------------------------
UINT
CXSTreeCtrl::GetVisibleCount()
{
    return GetTreeCtrl()->GetVisibleCount();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetEditControl
// Purpose   : 
//  Retreives the CEdit pointer to the in-place edit control.
// Parameters: 
//  None
// Returns   : 
//  The pointer to the in-place edit control on success, or NULL
//  on failure.
// -------------------------------------------------------------
CEdit*
CXSTreeCtrl::GetEditControl()
{
    return GetTreeCtrl()->GetEditControl();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::InsertItem
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::InsertItem(LPTV_INSERTSTRUCT pTVIns, 
                        CXSNodeData* pNodeData)
{
    CXSTreeNode treeNode(((CTreeCtrl*)DoGetWnd())->
                            InsertItem(pTVIns), this);
    ASSERT_VALID(&treeNode);
    
    // Add it to the map
    if (treeNode.GetSafeHandle())
    {
        if (pNodeData)
            treeNode.m_NodeData = *pNodeData;
        else
        {
            CXSNodeData nodeData;
            treeNode.m_NodeData = nodeData;
        }

        AddNode(treeNode);
    }

    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::InsertItem
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode 
CXSTreeCtrl::InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
                        int nSelectedImage, UINT nState, 
                        UINT nStateMask, LPARAM lParam, 
                        HTREEITEM hParent, HTREEITEM hInsertAfter, 
                        CXSNodeData* pNodeData)
{	
	CXSTreeNode treeNode(((CTreeCtrl*)DoGetWnd())->
        InsertItem(nMask, lpszItem, nImage, nSelectedImage, 
                    nState, nStateMask, lParam, hParent, 
                    hInsertAfter), this);
    ASSERT_VALID(&treeNode);

    // Add it to the map
    if (treeNode.GetSafeHandle())
    {
        if (pNodeData)
            treeNode.m_NodeData = *pNodeData;
        else
        {
            CXSNodeData nodeData;
            treeNode.m_NodeData = nodeData;
        }

        AddNode(treeNode);
    }

    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::InsertItem
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent, 
                        HTREEITEM hInsertAfter, 
                        CXSNodeData* pNodeData)
{
    CXSTreeNode treeNode(((CTreeCtrl*)DoGetWnd())->
                            InsertItem(lpszItem, hParent, 
                            hInsertAfter), this);
    ASSERT_VALID(&treeNode);

    // Add it to the map
    if (treeNode.GetSafeHandle())
    {
        if (pNodeData)
            treeNode.m_NodeData = *pNodeData;
        else
        {
            CXSNodeData nodeData;
            treeNode.m_NodeData = nodeData;
        }

        AddNode(treeNode);
    }

    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::InsertItem
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::InsertItem(LPCTSTR lpszItem, int nImage, 
                        int nSelectedImage, HTREEITEM hParent, 
                        HTREEITEM hInsertAfter, 
                        CXSNodeData* pNodeData)
{
    CXSTreeNode treeNode(((CTreeCtrl*)DoGetWnd())->
                            InsertItem(lpszItem, nImage, 
                            nSelectedImage, hParent, 
                            hInsertAfter), this);
    ASSERT_VALID(&treeNode);

    // Add it to the map
    if (treeNode.GetSafeHandle())
    {
        if (pNodeData)
            treeNode.m_NodeData = *pNodeData;
        else
        {
            CXSNodeData nodeData;
            treeNode.m_NodeData = nodeData;
        }

        AddNode(treeNode);
    }

    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetTextPos
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::SetTextPos(int nTextPos)
{
    // Filter out what we don't support
    ASSERT(!(nTextPos & DT_CALCRECT));
    ASSERT(!(nTextPos & DT_EDITCONTROL));
    ASSERT(!(nTextPos & DT_EXPANDTABS));
    ASSERT(!(nTextPos & DT_EXTERNALLEADING));
    ASSERT(!(nTextPos & DT_MODIFYSTRING));
    ASSERT(!(nTextPos & DT_NOCLIP));
    ASSERT(!(nTextPos & DT_NOPREFIX));
    ASSERT(!(nTextPos & DT_TABSTOP));
    ASSERT(!(nTextPos & DT_WORDBREAK));

    nTextPos &= ~(DT_CALCRECT|DT_EDITCONTROL|DT_EXPANDTABS|
        DT_EXTERNALLEADING|DT_MODIFYSTRING|DT_NOCLIP|
        DT_NOPREFIX|DT_TABSTOP|DT_WORDBREAK);

    m_nTextPos = nTextPos | DT_SINGLELINE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetTextPos
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
int
CXSTreeCtrl::GetTextPos()
{ 
    return m_nTextPos; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetBoundText
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::SetBoundText(int nBoundText)
{
    m_nBoundText = nBoundText;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetBoundText
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
int
CXSTreeCtrl::GetBoundText()
{ 
    return m_nBoundText; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetTextBackground
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::SetTextBackground(BOOL bTextBackground)
{
    m_bTextBackground = bTextBackground;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetTextBackground
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::GetTextBackground()
{ 
    return m_bTextBackground; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetNodeSelector
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::SetNodeSelector(BOOL bNodeSelector)
{ 
    m_bNodeSelector = bNodeSelector; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetNodeSelector
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::GetNodeSelector()
{ 
    return m_bNodeSelector; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SetNodeAttrib
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::SetNodeAttrib(BOOL bNodeAttrib)
{ 
    m_bNodeAttrib = bNodeAttrib; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetNodeAttrib
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::GetNodeAttrib()
{ 
    return m_bNodeAttrib; 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::AddHead
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode 
CXSTreeCtrl::AddHead(LPCTSTR strItem, int nImageIndex, 
                     int nSelImageIndex, CXSNodeData* pNodeData)
{ 
	return InsertItem(strItem, nImageIndex, nSelImageIndex, 
        TVI_ROOT, TVI_FIRST, pNodeData);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::AddTail
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode 
CXSTreeCtrl::AddTail(LPCTSTR strItem, int nImageIndex, 
                     int nSelImageIndex, CXSNodeData* pNodeData)
{ 
	return InsertItem(strItem, nImageIndex, nSelImageIndex, 
        TVI_ROOT, TVI_LAST, pNodeData);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DeleteAllItems
// Purpose   : 
// Parameters: 
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DeleteAllItems()
{
    m_mapTreeNode.RemoveAll();
    return GetTreeCtrl()->DeleteAllItems();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::HitTest
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::HitTest(CPoint pt, UINT* pFlags)
{
    HTREEITEM hTreeItem = GetTreeCtrl()->HitTest(pt, pFlags);
    CXSTreeNode treeNode(this);
    if (hTreeItem)
    {
        FindNode(hTreeItem, treeNode);
        return treeNode;
    }
    else
        return CXSTreeNode(this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::HitTest
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode
CXSTreeCtrl::HitTest(TV_HITTESTINFO* pHitTestInfo)
{
    HTREEITEM hTreeItem = GetTreeCtrl()->HitTest(pHitTestInfo);
    CXSTreeNode treeNode(this);
    if (hTreeItem)
    {
        FindNode(hTreeItem, treeNode);
        return treeNode;
    }
    else
        return CXSTreeNode(this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::SortChildrenCB
// Purpose   : 
// Parameters: 
// Returns   : 
//  TRUE on sucess, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::SortChildrenCB(LPTV_SORTCB pSort)
{
    return GetTreeCtrl()->SortChildrenCB(pSort);
}

// =============================================================

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoEndLabelEdit
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoEndLabelEdit(TV_DISPINFO* ptvDispInfo)
{
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoCanDragNode
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoCanDragNode(CXSTreeNode& treeNode)
{
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoCanDropTarget
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoCanDropTarget(CXSTreeNode& treeNode)
{
    // Don't drop on node on itself or it's Parent
    // as this would be redundant work.  However, if you want
    // this functionality, you will need to derive this class 
    // and override this virtual function.
    if (treeNode == m_nodeDrag || 
        treeNode == m_nodeDrag.GetParentItem())
    {
        return FALSE;
    }

    // Never ever drop a Parent on a Decendant!
    if (treeNode.IsParentItem(m_nodeDrag))
        return FALSE;

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoDrawNodeText
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoDrawNodeText(CDC* pDC, CXSTreeNode& treeNode)
{
    CFont*  pOldFont;
    CFont   font;
    LOGFONT logFont;

    logFont = treeNode.GetNodeFont();
    if (!logFont.lfFaceName[0])
    {
        // No font was specified, so use the default font
        CFont* pfntFont = GetTreeCtrl()->GetFont();
        pfntFont->GetLogFont(&logFont);
    }

    if (treeNode.GetBoldState())
        logFont.lfWeight = 700;
    font.CreateFontIndirect(&logFont);

    pOldFont = pDC->SelectObject(&font);
    pDC->SetTextColor(treeNode.GetNodeColorFore());

    CString str = treeNode.GetItemText();

    CXSRect rect = GetNodeRect(treeNode);

    if (m_bTextBackground)
    {
        pDC->FillSolidRect(rect, treeNode.GetNodeColorBack());
        pDC->SetBkColor(treeNode.GetNodeColorBack());
    }
    else
    {
        pDC->FillSolidRect(rect, ::GetSysColor(COLOR_WINDOW));
        pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
    }

    // Make adjustments for text
    rect.left += 2;
    rect.top += 1;

    pDC->DrawText(str, rect, m_nTextPos);
    pDC->SelectObject(pOldFont);

    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::GetNodeRect
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSRect
CXSTreeCtrl::GetNodeRect(CXSTreeNode& treeNode)
{
    ASSERT(treeNode.GetSafeHandle());

    CXSRect rect;
    CRect   rcClient = CXSClientRect(*DoGetWnd());
        
    treeNode.GetItemRect(&rect, TRUE);

    if (0 == m_nBoundText)
    {
        // Default (accounts for Italics)
        rect.right += 5;
    }
    else if (-1 == m_nBoundText)
    {
        // Stretch it all the way to the right
        rect.right = rcClient.right - 1;
    }
    else if (-1 > m_nBoundText)
    {
        // User wants absolute
        rect.right = (m_nBoundText * -1);
    }
    else  // > 0
    {
        // User wants it in a percentage
        rect.right = rcClient.Width() * m_nBoundText / 100;
    }

    return rect;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoDrawNodeSelector
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
void
CXSTreeCtrl::DoDrawNodeSelector(CDC* pDC, CXSTreeNode& treeNode)
{
    if (m_bNodeSelector)
    {
        ASSERT_VALID(pDC);

        CXSRect rect = GetNodeRect(treeNode);
        pDC->Draw3dRect(rect, RGB(192,192,192), RGB(0,0,0));
        rect.DeflateRect(1,1);
        pDC->Draw3dRect(rect, RGB(128,128,128), RGB(92,92,92));

        // See if there is room to do this
        if (0 != m_nBoundText)
        {
            CXSRect rcEllipse = rect;

            if (m_nTextPos & DT_RIGHT)
                rcEllipse.right = rect.left + rect.Height();
            else // (DT_LEFT||DT_CENTER)
                rcEllipse.left = rect.right - rect.Height();

            rcEllipse.DeflateRect(3,3);
            pDC->Ellipse(rcEllipse);
            rcEllipse.DeflateRect(2,2);
            pDC->Ellipse(rcEllipse);
        }
    }
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoSetCheck
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
BOOL
CXSTreeCtrl::DoSetCheck(CXSTreeNode& treeNode)
{
    return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeCtrl::DoGetCheckType
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CheckType
CXSTreeCtrl::DoGetCheckType(CXSTreeNode& treeNode)
{
    return Toggle;
}

