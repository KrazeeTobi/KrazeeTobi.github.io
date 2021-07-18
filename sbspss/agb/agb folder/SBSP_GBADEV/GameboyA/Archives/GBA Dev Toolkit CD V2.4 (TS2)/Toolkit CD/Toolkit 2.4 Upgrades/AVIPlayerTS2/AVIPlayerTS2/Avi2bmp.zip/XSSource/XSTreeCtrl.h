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

#if !defined(AFX_XSTREECTRL_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
#define AFX_XSTREECTRL_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Forward declarations
class CXSBgCtrl;
class CXSTreeNode;

#define DRAG_DELAY      100
#define ID_DRAG_TIMER   1
#define ID_EDIT_TIMER   2

class XSCLASS
CXSTreeCtrl : public CXSBgCtrl
{
protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSTreeCtrl);

public:
	                CXSTreeCtrl();
	virtual         ~CXSTreeCtrl();

    virtual BOOL    DoInstall(CWnd* pWnd, BOOL bNotify);

    CTreeCtrl*      GetTreeCtrl();
    BOOL            InEditMode();
    BOOL            InDragMode();

protected:
    // Map of CXSTreeNode's based on HTREEITEM association
    CMap< void*, void*, CXSTreeNode, CXSTreeNode&> m_mapTreeNode;
    BOOL            m_bNodeAttrib;  // Node attributes on/off
    int             m_nTextPos;     // Text position
        // Valid options are:
        //  DT_LEFT
        //  DT_CENTER
        //  DT_RIGHT
        //  DT_BOTTOM
        //  DT_END_ELLIPSES
        //  DT_RTLREADING
        //  DT_TOP
        //  DT_VCENTER

    // Text boxes should stretch to right of window
    int             m_nBoundText;
    BOOL            m_bTextBackground;
    BOOL            m_bNodeSelector;// Bounding selector box

    BOOL            m_bEdit;        // In edit mode
    BOOL            m_bDrag;        // In drag mode
    DWORD           m_dwDragDelay;  // Avoid inadvertant begin drag
    BOOL            m_bRDrag;       // In right mouse button drag mode
    UINT            m_nDragTimerID; // ID for drag timer
    UINT            m_nEditTimerID; // ID for edit timer
    CXSTreeNode     m_nodeEdit;     // Node for editing
    UINT            m_nTimerTicks;  // Tick count for Timer
    CImageList*     m_pDragImage;   // Image while dragging
    CXSTreeNode     m_nodeDrag;     // Dragging node
    CXSTreeNode     m_nodeDrop;     // Drop node
    BOOL            m_bNodeMove;    // Node is moving, not copying


    virtual BOOL    DoPaint(CDC* pDC, CXSBitmap& bmp, CRect rcDim);
    virtual void    DoPaintTreeCtrl(CDC* pDC);
    virtual BOOL    DoCreateBackgroundBmp(CDC* pDC, BOOL bState, 
                        CXSBitmap& bmp, CRect& rcDim);
    virtual BOOL    DoEndLabelEdit(TV_DISPINFO* ptvDispInfo);
    virtual BOOL    DoCanDragNode(CXSTreeNode& treeNode);
    virtual BOOL    DoCanDropTarget(CXSTreeNode& treeNode);
    virtual BOOL    DoIsSearchNodeValid(CXSTreeNode& treeNode);
    virtual void    DoItemCopied(CXSTreeNode& nodeSrc, 
                        CXSTreeNode& nodeDest);
    virtual void    DoItemMoved(CXSTreeNode& nodeSrc, 
                        CXSTreeNode& nodeDest);
    virtual void    DoItemDelete(CXSTreeNode& treeNode);
    virtual BOOL    DoDrawNodeText(CDC* pDC, 
                        CXSTreeNode& treeNode);
    virtual void    DoDrawNodeSelector(CDC* pDC, 
                        CXSTreeNode& treeNode);
    virtual BOOL    DoSetCheck(CXSTreeNode& treeNode);
    virtual CheckType DoGetCheckType(CXSTreeNode& treeNode);

    virtual BOOL    OnPaint(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnEraseBkgnd(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult);
    virtual BOOL    OnMouseMove(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnLButtonDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnLButtonUp(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnKeyDown(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTimer(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnHScroll(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnVScroll(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewSelChanging(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult);
    virtual BOOL    OnTreeviewSelChanged(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewGetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewSetDispInfo(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewItemExpanding(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult);
    virtual BOOL    OnTreeviewItemExpanded(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewBeginDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewBeginRDrag(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewDeleteItem(WPARAM wParam, LPARAM lParam);
    virtual BOOL    OnTreeviewBeginLabelEdit(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult);
    virtual BOOL    OnTreeviewEndLabelEdit(WPARAM wParam, LPARAM lParam, 
                        LRESULT& lResult);
    virtual BOOL    OnTreeviewKeyDown(WPARAM wParam, LPARAM lParam);

public:
    void            SetNodeAttrib(BOOL bNodeAttrib = TRUE);
    BOOL            GetNodeAttrib();
    void            SetTextPos(int nTextPos = DT_LEFT);
    int             GetTextPos();
    void            SetBoundText(int nBoundText = 0);
    int             GetBoundText();
    void            SetTextBackground(BOOL bTextBackground = FALSE);
    BOOL            GetTextBackground();
    CXSRect         GetNodeRect(CXSTreeNode& treeNode);
    void            SetNodeSelector(BOOL bNodeSelector = TRUE);
    BOOL            GetNodeSelector();


    CXSTreeNode     AddHead(LPCTSTR strItem, int nImageIndex = -1, 
                        int nSelImageIndex = -1, 
                        CXSNodeData* pNodeData = NULL);
    CXSTreeNode     AddTail(LPCTSTR strItem, int nImageIndex = -1, 
                        int nSelImageIndex = -1, 
                        CXSNodeData* pNodeData = NULL);

    void            AddNode(CXSTreeNode& treeNode);
    BOOL            RemoveNode(CXSTreeNode& treeNode);
    BOOL            FindNode(HTREEITEM hTreeItem, 
                        CXSTreeNode& treeNode);
    POSITION        GetStartPosition();
    void            GetNextAssoc(POSITION pos, HTREEITEM hTreeItem, 
                        CXSTreeNode& treeNode);

    BOOL            SetNodeData(CXSTreeNode& treeNode, 
                        CXSNodeData& nodeData);
    BOOL            SetNodeColor(CXSTreeNode& treeNode, 
                        COLORREF crFore = ::GetSysColor(COLOR_WINDOWTEXT), 
                        COLORREF crBack = ::GetSysColor(COLOR_WINDOW));
    BOOL            SetNodeFont(CXSTreeNode& treeNode, 
                        LOGFONT& logFont);
    BOOL            SetNodeLabelLen(CXSTreeNode& treeNode, 
                        int nLength = 0);

    // Remapped functions from CTreeCtrl/CTreeView
    CXSTreeNode     GetFirstVisibleItem();
    CXSTreeNode     GetNextVisibleItem(CXSTreeNode& treeNode);
    CXSTreeNode     GetPrevVisibleItem(CXSTreeNode& treeNode);
    CXSTreeNode     GetSelectedItem();
    CXSTreeNode     GetDropHilightItem();
    CXSTreeNode     GetRootItem();
    BOOL            SetItem(TV_ITEM* pItem);
    CEdit*          GetEditControl();
    UINT            GetVisibleCount();
    CXSTreeNode     InsertItem(LPTV_INSERTSTRUCT pTVIns, 
                        CXSNodeData* pNodeData = NULL);
    CXSTreeNode     InsertItem(UINT nMask, LPCTSTR lpszItem, 
                        int nImage, int nSelectedImage, 
                        UINT nState, UINT nStateMask, 
                        LPARAM lParam, HTREEITEM hParent, 
                        HTREEITEM hInsertAfter, 
                        CXSNodeData* pNodeData = NULL);
    CXSTreeNode     InsertItem( LPCTSTR lpszItem, 
                        HTREEITEM hParent = TVI_ROOT, 
                        HTREEITEM hInsertAfter = TVI_LAST, 
                        CXSNodeData* pNodeData = NULL);
    CXSTreeNode     InsertItem( LPCTSTR lpszItem, int nImage, 
                        int nSelectedImage, 
                        HTREEITEM hParent = TVI_ROOT, 
                        HTREEITEM hInsertAfter = TVI_LAST, 
                        CXSNodeData* pNodeData = NULL);
    BOOL            DeleteAllItems();
    CXSTreeNode     HitTest(CPoint pt, UINT* pFlags);
    CXSTreeNode     HitTest(TV_HITTESTINFO* pHitTestInfo);
    BOOL            SortChildrenCB(LPTV_SORTCB pSort);

protected:
    friend CXSTreeNode;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSTREECTRL_H__FD09DE60_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
