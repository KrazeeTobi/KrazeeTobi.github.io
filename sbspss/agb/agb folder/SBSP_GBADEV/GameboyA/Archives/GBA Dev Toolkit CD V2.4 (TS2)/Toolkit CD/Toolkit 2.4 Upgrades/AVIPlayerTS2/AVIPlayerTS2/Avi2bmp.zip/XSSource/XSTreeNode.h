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

#if !defined(AFX_XSTREENODE_H__FD09DE61_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
#define AFX_XSTREENODE_H__FD09DE61_EACE_11D1_AB25_54AB02C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -----------------------------------------------------------
// Forward declarations
class CXSTreeCtrl;
class CXSNodeData;

// Definitions ----------------------------------------------------------------
#define NodeNull		CXSTreeNode(m_pXSTreeCtrl)

class XSCLASS
CXSTreeNode : public CObject
{
protected:
    // create from serialization only
    DECLARE_DYNCREATE(CXSTreeNode);

public:
                    CXSTreeNode();
                    CXSTreeNode(HTREEITEM hTreeItem, CXSTreeCtrl* pXSTreeCtrl);
                    CXSTreeNode(CXSTreeNode& nodeSrc);
                    CXSTreeNode::CXSTreeNode(CXSTreeCtrl* pXSTreeCtrl);
    virtual         ~CXSTreeNode();
    virtual         CXSTreeNode& operator=(CXSTreeNode& nodeSrc);
    virtual         CXSTreeNode& operator=(HTREEITEM hTreeItem);
    virtual         BOOL operator==(HTREEITEM hTreeItem);
    virtual         BOOL operator==(CXSTreeNode& nodeSrc);
    virtual         BOOL operator!=(HTREEITEM hTreeItem);
    virtual         BOOL operator!=(CXSTreeNode& nodeSrc);
                    operator HTREEITEM();

public:
protected:
    HTREEITEM       m_hTreeItem;    // this item
    CXSTreeCtrl*    m_pXSTreeCtrl;  // parent class
    CXSNodeData     m_NodeData;     // stored attribute info

public:
    // XSEL Attribute functions
    HTREEITEM       GetSafeHandle();
    void            Reset(CXSTreeCtrl* pXSTreeCtrl = NULL);
    void            SetParentTree(CXSTreeCtrl* pXSTreeCtrl);
    CXSTreeCtrl*    GetParentTree() { return m_pXSTreeCtrl; }

    BOOL            SetNodeData(CXSNodeData* pNodeData = NULL);
    CXSNodeData     GetNodeData();
    BOOL            SetNodeColor(
                        COLORREF crFore = ::GetSysColor(COLOR_WINDOWTEXT), 
                        COLORREF crBack = ::GetSysColor(COLOR_WINDOW));
    COLORREF        GetNodeColorFore();
    COLORREF        GetNodeColorBack();
    BOOL            SetNodeFont(LOGFONT& logFont);
    LOGFONT         GetNodeFont();
    BOOL            SetNodeLabelLen(int nLength = 0);
    int             GetNodeLabelLen();

    BOOL            RefreshItem();

    void            SetBoldState(BOOL bBold);
    BOOL            GetBoldState();

    // Remapped functions from CTreeCtrl
    CEdit*          GetEditControl();
    CXSTreeNode     GetNextItem(UINT nCode);
    BOOL            ItemHasChildren();
    CXSTreeNode     GetChildItem();
    CXSTreeNode     GetNextSiblingItem();
    CXSTreeNode     GetPrevSiblingItem();
    CXSTreeNode     GetParentItem();
    CXSTreeNode     GetFirstVisibleItem();
    CXSTreeNode     GetNextVisibleItem();
    CXSTreeNode     GetPrevVisibleItem();
    CXSTreeNode     GetRootItem();
    CXSTreeNode     GetSelectedItem();
    BOOL            GetItem(TV_ITEM* ptvItem);
    BOOL            SetItem(UINT nMask, LPCTSTR lpszItem, 
                        int nImage, int nSelectedImage, 
                        UINT nState, UINT nStateMask, 
                        LPARAM lParam);
    UINT            GetItemState(UINT nStateMask);
    BOOL            SetItemState(UINT nState, UINT nStateMask);
    BOOL            GetItemImage(int& nImage, int& nSelectedImage);
    BOOL            SetItemImage(int nImage, int nSelectedImage);
    BOOL            SetItemText(LPCTSTR lpszItem);
    CString         GetItemText();
    DWORD           GetItemData();
    BOOL            SetItemData(DWORD dwData);
    BOOL            GetItemRect(LPRECT lpRect, BOOL bTextOnly);
    UINT            GetVisibleCount();
    BOOL            DeleteItem();
    BOOL            Expand(UINT nCode);
    BOOL            Select(UINT nCode);
    BOOL            SelectItem();
    BOOL            SelectDropTarget();
    BOOL            SelectSetFirstVisible();
    CEdit*          EditLabel();
    CImageList*     CreateDragImage();
    BOOL            SortChildren();
    BOOL            EnsureVisible();

    // XSEL extended functions
    BOOL            IsParentItem(CXSTreeNode& treeNode);
    CXSTreeNode     CopyItemToDest(CXSTreeNode& nodeParent, 
                        HTREEITEM hNodeAfter);
    CXSTreeNode     CopyItem(CXSTreeNode& nodeParent, 
                        HTREEITEM hNodeAfter = TVI_LAST);
    CXSTreeNode     MoveItem(CXSTreeNode& nodeParent, 
                        HTREEITEM hNodeAfter = TVI_LAST);
    CXSTreeNode     CopyItemBranch(CXSTreeNode& nodeParent, 
                        HTREEITEM hNodeAfter = TVI_LAST);
    CXSTreeNode     MoveItemBranch(CXSTreeNode& nodeParent, 
                        HTREEITEM hNodeAfter = TVI_LAST);
    void            SetBranch(UINT nCode);
    void            ExpandBranch();
    void            CollapseBranch();
    void            ToggleBranch();
    void            ExpandAllBranches();
    void            CollapseAllBranches();
    CXSTreeNode     GetLastBranchItem();

    CXSTreeNode     GetNextItem();
    CXSTreeNode     GetPrevItem();

    CXSTreeNode     SearchItem(BOOL bDown = TRUE);
    CXSTreeNode     SearchItemByString(
                        CString& str, 
                        BOOL bCaseSensitive = FALSE,
                        BOOL bDown = TRUE,
                        BOOL bPartial = TRUE);

    BOOL            SetCheck(CheckType nCheck);
    CXSTreeNode     GetFirstChecked();
    CXSTreeNode     GetNextChecked();
    CXSTreeNode     GetPrevChecked();
    BOOL            IsChecked();
    CXSRect         GetNodeRect();

protected:
    virtual void    DoAssertValidPtrs();
    CTreeCtrl*      GetTreeCtrl();

protected:
    friend CXSTreeCtrl;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSTREENODE_H__FD09DE61_EACE_11D1_AB25_54AB02C10000__INCLUDED_)
