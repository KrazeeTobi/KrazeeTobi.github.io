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

IMPLEMENT_DYNCREATE(CXSTreeNode, CObject)

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::CXSTreeNode
// Purpose   :
//    Constructor, initializes memory
// -------------------------------------------------------------
CXSTreeNode::CXSTreeNode() :
    m_hTreeItem(NULL),m_pXSTreeCtrl(NULL)
{
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::~CXSTreeNode
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSTreeNode::~CXSTreeNode()
{
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::CXSTreeNode
// Purpose   :
//    Constructor, initializes memory
// Parameters:
//  HTREEITEM hTreeItem - The HTREEITEM this object will
//      represent
//  CXSTreeCtrl* pXSTreeCtrl - The parent Treeview Control
//      subclasser
// -------------------------------------------------------------
CXSTreeNode::CXSTreeNode(HTREEITEM hTreeItem, CXSTreeCtrl* pXSTreeCtrl) :
    m_hTreeItem(hTreeItem),m_pXSTreeCtrl(pXSTreeCtrl)
{
    if (hTreeItem && pXSTreeCtrl)
    {
        if (!GetParentTree()->FindNode(hTreeItem, *this))
        {
            hTreeItem = NULL;
        }
    }
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::CXSTreeNode
// Purpose   :
//  Copy Constructor, initializes memory
// Parameters:
//  CXSTreeNode& nodeSrc - reference to an object to copy to
//      this object
// -------------------------------------------------------------
CXSTreeNode::CXSTreeNode(CXSTreeNode& nodeSrc) :
    m_hTreeItem(NULL),m_pXSTreeCtrl(NULL)
{
    *this = nodeSrc;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::CXSTreeNode
// Purpose   :
//  Constructor, initializes memory
// Parameters:
//  CXSTreeCtrl* pXSTreeCtrl - The parent Treeview Control
//      subclasser
// Note      :
//  This object is used to access funtions from the parent
//  subclasser when an HTREEITEM is not necessary.
// -------------------------------------------------------------
CXSTreeNode::CXSTreeNode(CXSTreeCtrl* pXSTreeCtrl) :
    m_hTreeItem(NULL),m_pXSTreeCtrl(pXSTreeCtrl)
{
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator=
// Purpose   :
//  Copies referenced object to "this" object
// Parameters:
//  CXSTreeNode& nodeSrc - object to copy from
// Returns   :
//  A reference to "this"
// -------------------------------------------------------------
CXSTreeNode&
CXSTreeNode::operator=(CXSTreeNode& nodeSrc)
{
    ASSERT_VALID(this);

    // Copy info
    m_hTreeItem = nodeSrc.m_hTreeItem;
    m_pXSTreeCtrl = nodeSrc.m_pXSTreeCtrl;
    m_NodeData = nodeSrc.m_NodeData;

    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator=
// Purpose   :
//  Copies HTREEITEM to "this" object
// Parameters:
//  HTREEITEM hTreeItem - The HTREEITEM this object will
//      represent
// Returns   :
//  CXSTreeNode& - Reference to "this" object
// -------------------------------------------------------------
CXSTreeNode&
CXSTreeNode::operator=(HTREEITEM hTreeItem)
{
    ASSERT_VALID(this);
    ASSERT(hTreeItem);

    // If there is no parent, we can't look it up
    if (!GetParentTree())
    {
        ASSERT(FALSE);
        return *this;
    }

    if (hTreeItem != m_hTreeItem)
    {
        // Look it up
        if (hTreeItem)
            GetParentTree()->FindNode(hTreeItem, *this);
    }

    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator==
// Purpose   :
//  Comparison operator for "is equal to"
// Parameters:
//  HTREEITEM hTreeItem - The HTREEITEM used to compare against
//      "this" objects represented HTREEITEM
// Returns   :
//  TRUE if objects do equal each other
//  FALSE if objects do not equal each other
// -------------------------------------------------------------
BOOL
CXSTreeNode::operator==(HTREEITEM hTreeItem)
{
    ASSERT_VALID(this);
    ASSERT(hTreeItem);

    if (m_hTreeItem == hTreeItem)
        return TRUE;
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator==
// Purpose   :
//  Comparison operator for "is equal to"
// Parameters:
//  CXSTreeNide& nodeSrc - object to use for comparison against
//      "this" object
// Returns   :
//  TRUE if objects do equal each other
//  FALSE if objectss do not equal each other
// -------------------------------------------------------------
BOOL
CXSTreeNode::operator==(CXSTreeNode& nodeSrc)
{
    ASSERT_VALID(this);
    ASSERT_VALID(&nodeSrc);

    if (m_hTreeItem == nodeSrc.m_hTreeItem &&
        m_pXSTreeCtrl == nodeSrc.m_pXSTreeCtrl &&
        m_NodeData == nodeSrc.m_NodeData)
        return TRUE;
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator!=
// Purpose   :
//  Comparison operator for "not equal to"
// Parameters:
//  HTREEITEM hTreeItem - The HTREEITEM used to compare against
//      "this" objects represented HTREEITEM
// Returns   :
//  TRUE if objects do not equal each other
//  FALSE if objectss do equal each other
// -------------------------------------------------------------
BOOL
CXSTreeNode::operator!=(HTREEITEM hTreeItem)
{
    return !(*this == hTreeItem);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator!=
// Purpose   :
//  Comparison operator for "not equal to"
// Parameters:
//  CXSTreeNide& nodeSrc - object to use for comparison against
//      "this" object
// Returns   :
//  TRUE if objects do not equal each other
//  FALSE if objectss do equal each other
// -------------------------------------------------------------
BOOL
CXSTreeNode::operator!=(CXSTreeNode& nodeSrc)
{
    return !(*this == nodeSrc);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::operator HTREEITEM
// Purpose   :
//  Overloaded operator for HTREEITEM
// Parameters:
//  None
// Returns   :
//  The represented HTREEITEM for this object
// -------------------------------------------------------------
CXSTreeNode::operator HTREEITEM()
{
    ASSERT_VALID(this);
    ASSERT(m_hTreeItem);

    return m_hTreeItem;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::DoAssertValidPtrs
// Purpose   :
//  Verifies validity of pointers and objects
// Parameters:
//  None
// Returns   :
//  Nothing. Used as a debugging tool.
// -------------------------------------------------------------
void
CXSTreeNode::DoAssertValidPtrs()
{
    ASSERT_VALID(this);
    ASSERT_VALID(GetParentTree());
    ASSERT_VALID(GetParentTree()->m_pWnd);
    ASSERT(GetParentTree()->m_pWnd->m_hWnd);
    ASSERT(::IsWindow(GetParentTree()->m_pWnd->m_hWnd));
    ASSERT(m_hTreeItem);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::GetTreeCtrl
// Purpose   :
//  Returns a pointer to the MFC CTreeCtrl object that the
//  parent subclasser represents.
// Parameters:
//  None
// Returns   :
//  CTreeCtrl* - Pointer to the underlying MFC CTreeCtrl
// -------------------------------------------------------------
CTreeCtrl*
CXSTreeNode::GetTreeCtrl()
{
    DoAssertValidPtrs();
    return GetParentTree()->GetTreeCtrl();
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::Reset
// Purpose   :
//  Reinitializes the "this" object with a new parent subclasser
// Parameters:
//  CXSTreectrl* pXSTreeCtrl - The new parent subclasser
// Returns   :
//  Nothing
// Note      :
//  This function resets the HTREEITEM to NULL
// -------------------------------------------------------------
void
CXSTreeNode::Reset(CXSTreeCtrl* pXSTreeCtrl)
{
    m_hTreeItem = NULL;
    m_pXSTreeCtrl = pXSTreeCtrl;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::SetParentTree
// Purpose   :
//  Reinitializes the "this" object with a new parent subclasser
// Parameters:
//  CXSTreectrl* pXSTreeCtrl - The new parent subclasser
// Returns   :
//  Nothing
// Note      :
//  This function does not reset the HTREEITEM to NULL like
//  Reset does.
// -------------------------------------------------------------
void
CXSTreeNode::SetParentTree(CXSTreeCtrl* pXSTreeCtrl)
{
    ASSERT_VALID(pXSTreeCtrl);
    m_pXSTreeCtrl = pXSTreeCtrl;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::SetNodeData
// Purpose   :
//  Associate a CXSNodeData object to this object
// Parameters:
//  CXSNodeData* pNodeData - a pointer to a CXSNodeData object
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetNodeData(CXSNodeData* pNodeData)
{
    ASSERT_VALID(this);

    if (pNodeData)
    {
        m_NodeData = *pNodeData;
    }
    else
    {
        // Get defaults
        CXSNodeData nodeData;
        m_NodeData = nodeData;
    }

    return GetParentTree()->SetNodeData(*this, m_NodeData);;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::GetNodeData
// Purpose   :
//  Returns a copy of the  CXSNodeData object associated with
//  this object
// Parameters:
//  None
// Returns   :
//  CXSNodeData - a copy of the CXSNodeData object associated
//  with this object
// -------------------------------------------------------------
CXSNodeData
CXSTreeNode::GetNodeData()
{
    ASSERT_VALID(this);
    return m_NodeData;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::SetNodeColor
// Purpose   :
//  Sets the forground and background colors associated with
//  this object
// Parameters:
//  COLORREF crFore - The forground color to use
//  COLORREF crBack - The background color to use
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetNodeColor(COLORREF crFore, COLORREF crBack)
{
    ASSERT_VALID(this);
    ASSERT_VALID(GetParentTree());
    return GetParentTree()->SetNodeColor(*this, crFore, crBack);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::GetNodeColorFore
// Purpose   :
//  Returns the foreground color used by this object
// Parameters:
//  None
// Returns   :
//  COLORREF - the foreground color used by this object
// -------------------------------------------------------------
COLORREF
CXSTreeNode::GetNodeColorFore()
{
    ASSERT_VALID(this);
    return m_NodeData.m_crFore;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::GetNodeColorBack
// Purpose   :
//  Returns the background color used by this object
// Parameters:
//  None
// Returns   :
//  COLORREF - the background color used by this object
// -------------------------------------------------------------
COLORREF
CXSTreeNode::GetNodeColorBack()
{
    ASSERT_VALID(this);
    return m_NodeData.m_crBack;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::SetNodeFont
// Purpose   :
//  Associates the font information used by this object
// Parameters:
//  LOGFONT& logFont - reference of a LOGFONT object
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetNodeFont(LOGFONT& logFont)
{
    ASSERT_VALID(this);
    ASSERT_VALID(GetParentTree());
    return GetParentTree()->SetNodeFont(*this, logFont);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::GetNodeFont
// Purpose   :
//  Retrieves the associated font information used by this
//  object
// Parameters:
//  None
// Returns   :
//  LOGFONT - A copy of the LOGFONT information associated with
//  this object
// -------------------------------------------------------------
LOGFONT
CXSTreeNode::GetNodeFont()
{
    ASSERT_VALID(this);
    return m_NodeData.m_lfLogFont;
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::SetNodeLabelLen
// Purpose   :
//  Sets the maximum edit length for in-place node editing
// Parameters:
//  int nLength - length of allowable edit string. Use 0 for
//  unlimited length
// Returns   :
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetNodeLabelLen(int nLength) // =0
{
    ASSERT_VALID(this);
    ASSERT_VALID(GetParentTree());
    return GetParentTree()->SetNodeLabelLen(*this, nLength);
}

// -------------------------------------------------------------
// Function  :
//  CXSTreeNode::GetNodeLabelLen
// Purpose   :
//  Retrieves the associated edit length for in-place editing
//  for this object
// Parameters:
//  None
// Returns   :
//  int - The edit length
// -------------------------------------------------------------
int
CXSTreeNode::GetNodeLabelLen()
{
    ASSERT_VALID(this);
    return m_NodeData.m_nLabelLen;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetEditControl
// Purpose   :
//  Utility function for gaining access to the edit control 
//  while in in-place edit mode.
// Parameters: 
//  None
// Returns   : 
//  CEdit* - A pointer to a CEdit object. This will be NULL if 
//  not currently in in-place editing mode.
// -------------------------------------------------------------
CEdit*
CXSTreeNode::GetEditControl()
{
    return GetTreeCtrl()->GetEditControl();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::RefreshItem
// Purpose   : 
//  Refreshes the "this" object
// Parameters: 
//  None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note:
//  You would want to refresh the "this" object when some other
//  object has modified the CXSNodeData attributes for this 
//  object. This function makes "this" aware of those changes.
// -------------------------------------------------------------
BOOL
CXSTreeNode::RefreshItem()
{
    DoAssertValidPtrs();
    return GetParentTree()->FindNode(*this, *this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetBoldState
// Purpose   : 
//  Sets the bold attribute state for this object
// Parameters: 
//  BOOL bBold - TRUE to set bold on, FALSE to turn it off
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeNode::SetBoldState(BOOL bBold)
{
	SetItemState(bBold ? TVIS_BOLD : 0, TVIS_BOLD);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetBoldState
// Purpose   : 
//  Returns the bold state associated with this object
// Parameters: 
//  None
// Returns   : 
//  BOOL - TRUE if bold is on, FALSE if it is off
// -------------------------------------------------------------
BOOL
CXSTreeNode::GetBoldState()
{
	return (GetItemState(TVIS_BOLD) & TVIS_BOLD); 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetNextItem
// Purpose   : 
//  Retrieves a copy of the next item, according to the passed 
//  parameter
// Parameters: 
//  UINT nCode - A flag indicating the relationship to "this" 
//  object
// Returns   : 
//  CXSTreeNode - copy of the returned CXSTreeNode item
// Note
//  See CTreeCtrl::GetNextItem for flag values
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetNextItem(UINT nCode)
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetNextItem(*this, nCode);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::ItemHasChildren
// Purpose   : 
//  Checks to see if this object has children
// Parameters: 
//  None
// Returns   : 
//  TRUE if it has children, FALSE if it does not have children
// -------------------------------------------------------------
BOOL
CXSTreeNode::ItemHasChildren()
{
    return GetTreeCtrl()->ItemHasChildren(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetChildItem
// Purpose   : 
//  Retrieves a copy of the child item to this object
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the CXSTreeNode child item to this 
//  object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetChildItem()
{
    HTREEITEM hTreeItem =  GetTreeCtrl()->GetChildItem(*this);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetNextSiblingItem
// Purpose   : 
//  Retrieves a copy of the next sibling item to this object
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the next sibling item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetNextSiblingItem()
{
    HTREEITEM hTreeItem =  GetTreeCtrl()->GetNextSiblingItem(*this);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetPrevSiblingItem
// Purpose   : 
//  Retrieves a copy of the previous sibling item to this object
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the previous sibling item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetPrevSiblingItem()
{
    HTREEITEM hTreeItem =  GetTreeCtrl()->GetPrevSiblingItem(*this);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetParentItem
// Purpose   : 
//  Retrieves a copy of the parent item for this object
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the parent item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetParentItem()
{
    HTREEITEM hTreeItem =  GetTreeCtrl()->GetParentItem(*this);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetFirstVisibleItem
// Purpose   : 
//  Retrieves a copy of the first visible item
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the first visible item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetFirstVisibleItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetFirstVisibleItem();
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetNextVisibleItem
// Purpose   : 
//  Retrieves a copy of the next visible item
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the next visible item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetNextVisibleItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetNextVisibleItem(*this);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetPrevVisibleItem
// Purpose   : 
//  Retrieves a copy of the previous visible item
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the previous visible item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetPrevVisibleItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetPrevVisibleItem(*this);
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetRootItem
// Purpose   : 
//  Retrieves a copy of the root item
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the root item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetRootItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetRootItem();
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetSelectedItem
// Purpose   : 
//  Retrieves a copy of the selected item
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the selected item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetSelectedItem()
{
    HTREEITEM hTreeItem = GetTreeCtrl()->GetSelectedItem();
    CXSTreeNode treeNode(GetParentTree());
    if (hTreeItem)
        GetParentTree()->FindNode(hTreeItem, treeNode);
    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetItem
// Purpose   : 
//  Retrieves the Treeview attributes for this object
// Parameters: 
//  TV_ITEM* ptvItem - Pointer to a TV_ITEM object
// Returns   : 
//  TRUE on success, FALSE on failure
// Note:
//  See CTreeCtrl::GetItem for TV_ITEM information
// -------------------------------------------------------------
BOOL
CXSTreeNode::GetItem(TV_ITEM* ptvItem)
{
    return GetTreeCtrl()->GetItem(ptvItem);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetItem
// Purpose   : 
//  Set the Treeview attributes for this object
// Parameters: 
//  UINT nMask - Integer spcifying what attributes to set
//  LPCTSTR lpszItem - Address of string containing the item's 
//      text
//  int nImage - Index of the item’s image in the tree view 
//      control’s image list. 
//  int nSelectedImage - Index of the item’s selected image in 
//      the tree view control’s image list. 
//  UINT nState - Specifies values for the item’s states. 
//  UINT nStateMask - Specifies which states are to be set. 
//  LPARAM lParam - A 32-bit application-specific value 
//      associated with the item. 
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::SetItem for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam)
{
    return GetTreeCtrl()->SetItem(*this, nMask, lpszItem, nImage, nSelectedImage, nState, nStateMask, lParam);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetItemState
// Purpose   : 
//  Returns the state of this object
// Parameters: 
//  UINT nStateMask - Mask indicating which states are to be 
//      retrieved. 
// Returns   : 
//  UINT - The state of this object
// Note      :
//  See CTreeCtrl::GetItemState for more information
// -------------------------------------------------------------
UINT
CXSTreeNode::GetItemState(UINT nStateMask)
{
    return GetTreeCtrl()->GetItemState(*this, nStateMask);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetItemState
// Purpose   : 
//  Set the state of this object
// Parameters: 
//  UINT nState - Specifies new states for the item.
//  UINT nStateMask - Specifies which states are to be changed.
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::SetItemState for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetItemState(UINT nState, UINT nStateMask)
{
    return GetTreeCtrl()->SetItemState(*this, nState, nStateMask);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetItemImage
// Purpose   : 
//  Retrieves the indexed items into the associated Treeview's
//  imagelist of the object's image and selected image.
// Parameters: 
//  int& nImage - An integer that receives the index of the 
//      item's image within the tree view control's image list.
//  int& nSelectedImage - An integer that receives the index of 
//      the item's selected image within the tree view control's 
//      image list.
// Returns   : 
//  TRUE on success, FALSE on failure
// Note     :
//  See CTreeCtrl::GetItemImage for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::GetItemImage(int& nImage, int& nSelectedImage)
{
    return GetTreeCtrl()->GetItemImage(*this, nImage, nSelectedImage);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetItemImage
// Purpose   : 
//  Sets the indexed items into the associated Treeview's
//  imagelist of the object's image and selected image.
// Parameters: 
//  int nImage - Index of the item's image in the tree view 
//      control's image list.
//  int nSelectedImage - Index of the item's selected image in 
//      the tree view control's image list.
// Returns   : 
//  TRUE on success, FALSE on failure
// Note     :
//  See CTreeCtrl::SetItemImage for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetItemImage(int nImage, int nSelectedImage)
{
    return GetTreeCtrl()->SetItemImage(*this, nImage, nSelectedImage);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetItemText
// Purpose   : 
//  Retrieves the text associated with this object
// Parameters: 
//  None
// Returns   : 
//  CString - The text associated with this object
// Note     :
//  See CTreeCtrl::GetItemText for more information
// -------------------------------------------------------------
CString
CXSTreeNode::GetItemText()
{
    return GetTreeCtrl()->GetItemText(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetItemText
// Purpose   : 
//  Sets the text to be associated with this object
// Parameters: 
//  LPCTSTR lpszItem - Address of a string containing the new 
//      text for the item
// Returns   : 
//  TRUE on success, FALSE on failure
// Note     :
//  See CTreeCtrl::SetItemText for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetItemText(LPCTSTR lpszItem)
{
    return GetTreeCtrl()->SetItemText(*this, lpszItem);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetItemData
// Purpose   : 
//  Retrieves the 32-bit application-specific value associated 
//  with this object 
// Parameters: 
//  None
// Returns   : 
//  DWORD - The 32-bit application-specific value associated 
//      with this object
// Note     :
//  See CTreeCtrl::GetItemData for more information
// -------------------------------------------------------------
DWORD
CXSTreeNode::GetItemData()
{
    return GetTreeCtrl()->GetItemData(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetItemData
// Purpose   : 
//  Sets the 32-bit application-specific value associated with 
//  this object
// Parameters: 
//  DWORD dwData - A 32-bit application-specific value 
//      associated with this object
// Returns   : 
//  TRUE on success, FALSE on failure
// Note     :
//  See CTreeCtrl::SetItemData for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SetItemData(DWORD dwData)
{
    return GetTreeCtrl()->SetItemData(*this, dwData);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetItemRect
// Purpose   : 
//  Retrieves the bounding rectangle for this object and 
//  determines whether it is visible or not.
// Parameters: 
//  LPRECT lpRect - Pointer to a RECT structure that receives 
//      the bounding rectangle. The coordinates are relative to 
//      the upper-left corner of the tree view control.
//  BOOL bTextOnly - If this parameter is nonzero, the bounding 
//      rectangle includes only the text of the item. Otherwise 
//      it includes the entire line that the item occupies in 
//      the tree view control.
// Returns   : 
//  TRUE if the item is visible, with the bounding rectangle 
//  contained in lpRect. Otherwise, FALSE with lpRect 
//  uninitialized.
// Note     :
//  See CTreeCtrl::GetItemRect for more information
// -------------------------------------------------------------
BOOL 
CXSTreeNode::GetItemRect(LPRECT lpRect, BOOL bTextOnly)
{	
    return GetTreeCtrl()->GetItemRect(*this, lpRect, bTextOnly); 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetVisibleCount
// Purpose   : 
//  Retrieves the count of possible visible items in a tree view 
//  control.
// Parameters: 
//  None
// Returns   : 
//  UINT - The number of visible items in the tree view control; 
//  otherwise -1.
// Note     :
//  See CTreeCtrl::GetVisibleCount for more information
// -------------------------------------------------------------
UINT 
CXSTreeNode::GetVisibleCount()
{	
    return GetTreeCtrl()->GetVisibleCount(); 
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::DeleteItem
// Purpose   : 
//  Deletes this object from the tree view control.
// Parameters: 
// None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note     :
//  See CTreeCtrl::DeleteItem for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::DeleteItem()
{
    // Remove it from the map
    GetParentTree()->RemoveNode(*this);

    // Remove it from the control
    return GetTreeCtrl()->DeleteItem(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::Expand
// Purpose   : 
//  To expand or collapse the list of child objects, if any, 
//  associated with this object as a parent item. 
// Parameters: 
//  UINT nCode - A flag indicating the type of action to be 
//      taken. 
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::Expand for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::Expand(UINT nCode)
{	
    GetTreeCtrl()->LockWindowUpdate();
    BOOL bResult = GetTreeCtrl()->Expand(*this, nCode);
    GetTreeCtrl()->UnlockWindowUpdate();
    return bResult;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::Select
// Purpose   : 
//  Selects the given tree view item, scroll the item into view, 
//  or redraw the item in the style used to indicate the target 
//  of a drag-and-drop operation.
// Parameters: 
//  UINT nCode - The type of action to take. 
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::Select for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::Select(UINT nCode)
{	
    GetTreeCtrl()->LockWindowUpdate();
    BOOL bResult = GetTreeCtrl()->Select(*this, nCode);
    GetTreeCtrl()->UnlockWindowUpdate();
    return bResult;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SelectItem
// Purpose   : 
//  Selects this object in the treeview
// Parameters: 
//  None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::SelectItem for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SelectItem()
{	
    GetTreeCtrl()->LockWindowUpdate();
    BOOL bResult = GetTreeCtrl()->SelectItem(*this);
    GetTreeCtrl()->UnlockWindowUpdate();
    return bResult;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SelectDropTarget
// Purpose   : 
//  Redraw this object in the style used to indicate the target 
//  of a drag-and-drop operation
// Parameters: 
//  None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::SelectDropTarget for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SelectDropTarget()
{
    return GetTreeCtrl()->SelectDropTarget(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SelectSetFirstVisible
// Purpose   : 
//  Scroll the tree view vertically so that this object is the 
//  first visible item
// Parameters: 
//  None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::SelectSetFirstVisible for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SelectSetFirstVisible()
{	
    GetTreeCtrl()->LockWindowUpdate();
    BOOL bResult = GetTreeCtrl()->SelectSetFirstVisible(*this);
    GetTreeCtrl()->UnlockWindowUpdate();
    return bResult;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::EditLabel
// Purpose   : 
//  Begins in-place editing of this object’s text. The editing 
//  is accomplished by replacing the text of this object with a 
//  single-line edit control containing the text. 
// Parameters: 
//  None
// Returns   : 
//  CEdit* - If successful, a pointer to the CEdit object that 
//      is used to edit the object's text; otherwise NULL
// Note      :
//  See CTreeCtrl::EditLabel for more information
// -------------------------------------------------------------
CEdit*
CXSTreeNode::EditLabel()
{	
    return GetTreeCtrl()->EditLabel(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::CreateDragImage
// Purpose   : 
//  Creates a dragging bitmap for this object in a tree view 
//  control, create an image list for the bitmap, and add the 
//  bitmap to the image list. An application uses the image-list 
//  functions to display the image when this object is being 
//  dragged.
// Parameters: 
//  None
// Returns   : 
//  CImageList* - Pointer to the image list to which the 
//      dragging bitmap was added, if successful; otherwise NULL.
// Note      :
//  See CTreeCtrl::CreateDragImage for more information
// -------------------------------------------------------------
CImageList*
CXSTreeNode::CreateDragImage()
{	
    return GetTreeCtrl()->CreateDragImage(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SortChildren
// Purpose   : 
//  Sorts the child items of this parent object in a tree view 
//  control. If m_hTreeItem is NULL, but m_pXSTreeCtrl is valid, 
//  the entire tree control is sorted.
// Parameters: 
//  None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::SortChildren for more information
// -------------------------------------------------------------
BOOL
CXSTreeNode::SortChildren()
{	
    GetTreeCtrl()->LockWindowUpdate();
    BOOL bResult = GetTreeCtrl()->SortChildren(*this);
    GetTreeCtrl()->UnlockWindowUpdate();
    GetTreeCtrl()->UpdateWindow();
    return bResult;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::EnsureVisible
// Purpose   : 
//  Ensures that this object is visible. If necessary, the 
//  function expands the parent object or scrolls the tree view 
//  control so that this object is visible.
// Parameters: 
//  None
// Returns   : 
//  TRUE on success, FALSE on failure
// Note      :
//  See CTreeCtrl::EnsureVisible for more information
// -------------------------------------------------------------
BOOL 
CXSTreeNode::EnsureVisible()
{
    GetTreeCtrl()->LockWindowUpdate();
    BOOL bResult = GetTreeCtrl()->EnsureVisible(*this);
    GetTreeCtrl()->UnlockWindowUpdate();
    return bResult;
}

// =============================================================

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::IsParentItem
// Purpose   : 
//  Tests whether the passed CXSTreeNode object is a parent 
//  object of this object.
// Parameters: 
//  CXSTreeNode& treeNode - the object to test for a parent 
//      relationship.
// Returns   : 
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL
CXSTreeNode::IsParentItem(CXSTreeNode& treeNode)
{
    CXSTreeNode nodeParent = GetParentItem();
    while (nodeParent.GetSafeHandle())
    {
        if (nodeParent == treeNode)
            return TRUE;

        nodeParent = nodeParent.GetParentItem();
    }

    return FALSE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::CopyItemToDest
// Purpose   : 
//  Copies thise object to another destination, using another 
//  CXSTreeNode as a parent.
// Parameters: 
//  CXSTreeNode& nodeParent - Parent object
//  HTREEITEM hNodeAfter - Handle of the object after which this 
//      object is to be copied or one of the following values:
//      TVI_FIRST - Copies the object at the beginning of the 
//                  list.
//      TVI_LAST  - Copies the object at the end of the list.
//      TVI_SORT  - Copies the object into the list in 
//                  alphabetical order.
// Returns   : 
//  CXSTreeNode - Copy of the copied object with a new 
//      associated HTREEITEM
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::CopyItemToDest(CXSTreeNode& nodeParent, HTREEITEM hNodeAfter)
{
    ASSERT_VALID(GetParentTree());

    TV_INSERTSTRUCT tvInsert;
    CXSTreeNode nodeNew(GetParentTree());
    CXSNodeData nodeData;
    CString strText;

    // Get source information
    tvInsert.item.hItem = *this;
    tvInsert.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

    GetItem(&tvInsert.item);
    strText = GetItemText();

    tvInsert.item.cchTextMax = strText.GetLength();
    tvInsert.item.pszText = strText.LockBuffer();

    nodeData = GetNodeData();

    // Insert node at proper location
    tvInsert.hParent = nodeParent;
    tvInsert.hInsertAfter = hNodeAfter;
    tvInsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    nodeNew = GetParentTree()->InsertItem(&tvInsert, &nodeData);
    strText.ReleaseBuffer();

    // Copy item data and item state
    nodeNew.SetItemData(GetItemData());
    nodeNew.SetItemState(GetItemState(TVIS_STATEIMAGEMASK), TVIS_STATEIMAGEMASK);

    // Call parent tree virtual function
    if (GetParentTree()->m_bNodeMove)
        GetParentTree()->DoItemMoved(*this, nodeNew);
    else
        GetParentTree()->DoItemCopied(*this, nodeNew);

    return nodeNew;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::CopyItem
// Purpose   : 
//  Copies thise object to another destination, using another 
//  CXSTreeNode as a parent. If this object has children, they
//  are also copied.
// Parameters: 
//  CXSTreeNode& nodeParent - Parent object
//  HTREEITEM hNodeAfter - Handle of the object after which this 
//      object is to be copied or one of the following values:
//      TVI_FIRST - Copies the object at the beginning of the 
//                  list.
//      TVI_LAST  - Copies the object at the end of the list.
//      TVI_SORT  - Copies the object into the list in 
//                  alphabetical order.
// Returns   : 
//  CXSTreeNode - A Copy of the last copied object with a new 
//      associated HTREEITEM
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::CopyItem(CXSTreeNode& nodeParent, HTREEITEM hNodeAfter)
{
    ASSERT_VALID(GetParentTree());

    // may be a long operation
    CWaitCursor();

    CXSTreeNode nodeNew;
    if (ItemHasChildren())
        nodeNew = CopyItemBranch(nodeParent, hNodeAfter);
    else
        nodeNew = CopyItemToDest(nodeParent, hNodeAfter);

    return nodeNew;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::MoveItem
// Purpose   : 
//  Moves this object to a different location. If there are 
//  children, they are also moved.
// Parameters: 
//  CXSTreeNode& nodeParent - Parent object
//  HTREEITEM hNodeAfter - Handle of the object after which this 
//      object is to be copied or one of the following values:
//      TVI_FIRST - Copies the object at the beginning of the 
//                  list.
//      TVI_LAST  - Copies the object at the end of the list.
//      TVI_SORT  - Copies the object into the list in 
//                  alphabetical order.
// Returns   : 
//  CXSTreeNode - A Copy of the last copied object with a new 
//      associated HTREEITEM
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::MoveItem(CXSTreeNode& nodeParent, HTREEITEM hNodeAfter)
{
    ASSERT_VALID(GetParentTree());

    GetParentTree()->m_bNodeMove = TRUE;

    CXSTreeNode nodeNew;
    if (ItemHasChildren())
        nodeNew = CopyItemBranch(nodeParent, hNodeAfter);
    else
        nodeNew = CopyItemToDest(nodeParent, hNodeAfter);

    DeleteItem();

    GetParentTree()->m_bNodeMove = FALSE;

    return nodeNew;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::CopyItemBranch
// Purpose   : 
//  Copies this object to a new destination. If there are 
//  children, they are also copied.
// Parameters: 
//  CXSTreeNode& nodeParent - Parent object
//  HTREEITEM hNodeAfter - Handle of the object after which this 
//      object is to be copied or one of the following values:
//      TVI_FIRST - Copies the object at the beginning of the 
//                  list.
//      TVI_LAST  - Copies the object at the end of the list.
//      TVI_SORT  - Copies the object into the list in 
//                  alphabetical order.
// Returns   : 
//  CXSTreeNode - A Copy of the last copied object with a new 
//      associated HTREEITEM
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::CopyItemBranch(CXSTreeNode& nodeParent, HTREEITEM hNodeAfter)
{
    ASSERT_VALID(GetParentTree());

    // may be a long operation
    CWaitCursor();

    CXSTreeNode nodeChild(GetParentTree());
    CXSTreeNode nodeNew = CopyItemToDest(nodeParent, hNodeAfter);

    nodeChild = GetChildItem();
    while (nodeChild.GetSafeHandle())
    {
        // Transfer all items semi-recursively
        nodeChild.CopyItemBranch(nodeNew);
        nodeChild = nodeChild.GetNextSiblingItem();
    }

    return nodeNew;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::MoveItemBranch
// Purpose   : 
//  Moves this object to a new destination. If there are 
//  children, they are also moved.
// Parameters: 
//  CXSTreeNode& nodeParent - Parent object
//  HTREEITEM hNodeAfter - Handle of the object after which this 
//      object is to be copied or one of the following values:
//      TVI_FIRST - Copies the object at the beginning of the 
//                  list.
//      TVI_LAST  - Copies the object at the end of the list.
//      TVI_SORT  - Copies the object into the list in 
//                  alphabetical order.
// Returns   : 
//  CXSTreeNode - A Copy of the last copied object with a new 
//      associated HTREEITEM
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::MoveItemBranch(CXSTreeNode& nodeParent, HTREEITEM hNodeAfter)
{
    GetParentTree()->m_bNodeMove = TRUE;

    CXSTreeNode nodeNew = CopyItemBranch(nodeParent, hNodeAfter);

    DeleteItem();

    GetParentTree()->m_bNodeMove = FALSE;

    return nodeNew;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetBranch
// Purpose   : 
//  Expands, Collapses, or Toggles the branch associated with 
//  this object
// Parameters: 
//  UINT nCode - A flag indicating the type of action to be 
//      taken. 
// Returns   : 
//  Nothing
// Note      :
//  See CTreeCtrl::Expand for flag information
// -------------------------------------------------------------
void
CXSTreeNode::SetBranch(UINT nCode)
{
    // Don't allow resetting for this as we are working 
    // on children
    ASSERT(nCode & TVE_COLLAPSERESET);

    ASSERT_VALID(GetParentTree());
    CXSTreeNode treeNode(GetParentTree());;

    if (ItemHasChildren())
    {
        Expand(nCode);
        treeNode = GetChildItem();
        do
        {
            treeNode.SetBranch(nCode);
            treeNode = treeNode.GetNextSiblingItem();
        } while (treeNode.GetSafeHandle());
    }

    GetParentTree()->GetSelectedItem().EnsureVisible();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::ExpandBranch
// Purpose   : 
//  Expands the entire branch associated with this object
// Parameters: 
//  None
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeNode::ExpandBranch()
{
    SetBranch(TVE_EXPAND);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::CollapseBranch
// Purpose   : 
//  Collapses the entire branch associated with this object
// Parameters: 
//  None
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeNode::CollapseBranch()
{
    SetBranch(TVE_COLLAPSE);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::ToggleBranch
// Purpose   : 
//  Toggles the entire branch associated with this object
// Parameters: 
//  None
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeNode::ToggleBranch()
{
    SetBranch(TVE_TOGGLE);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::ExpandAllBranches
// Purpose   : 
//  Expands all branches in the treeview control
// Parameters: 
//  None
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeNode::ExpandAllBranches()
{
    ASSERT_VALID(GetParentTree());
    CXSTreeNode treeNode = GetRootItem();

    do
    {
        treeNode.ExpandBranch();
        treeNode = treeNode.GetNextSiblingItem();
    } while (treeNode.GetSafeHandle());

    GetParentTree()->GetSelectedItem().EnsureVisible();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::CollapseAllBranches
// Purpose   : 
//  Collapses all branches in the treeview control
// Parameters: 
//  None
// Returns   : 
//  Nothing
// -------------------------------------------------------------
void
CXSTreeNode::CollapseAllBranches()
{
    ASSERT_VALID(GetParentTree());
    CXSTreeNode treeNode = GetRootItem();

    do
    {
        treeNode.CollapseBranch();
        treeNode = treeNode.GetNextSiblingItem();
    } while (treeNode.GetSafeHandle());

    GetParentTree()->GetSelectedItem().EnsureVisible();
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetLastBranchItem
// Purpose   : 
//  Retrieves the very last item in the treeview control
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the object that is the last item in
//      the treeview control.
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetLastBranchItem()
{
    ASSERT_VALID(GetParentTree());
    CXSTreeNode treeNode(GetParentTree());

    if (!GetSafeHandle())
    {
        // Get the last item starting from root level
        treeNode = GetRootItem();

        while (treeNode.GetSafeHandle())
        {
            *this = treeNode;
            treeNode = treeNode.GetNextSiblingItem();
        }
    }

    while (ItemHasChildren())
    {
        treeNode = GetChildItem();

        while (treeNode.GetSafeHandle())
        {
            *this = treeNode;
            treeNode = treeNode.GetNextSiblingItem();
        }
    }

    return *this;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetNextItem
// Purpose   : 
//  Retrieves the next object of this object. It may be a child,
//  or if this is the last child of a branch, it retrieves the
//  next sibling of the parent item.
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the next item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetNextItem()
{
    ASSERT_VALID(GetParentTree());
    CXSTreeNode treeNode(GetParentTree());

    if (ItemHasChildren())
    {
        treeNode = GetChildItem();
    }
    else
    {
        // Return the next sibling item
        // Travel up the tree to find the parent sibling, if needed
        for (treeNode = GetNextSiblingItem(); !treeNode.GetSafeHandle(); 
            treeNode = GetNextSiblingItem())
        {
            treeNode = GetParentItem();
            if (!treeNode.GetSafeHandle())
                return NodeNull;  // NULL Node
        }
    }

    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetPrevItem
// Purpose   : 
//  Retrieves the previous object of this object. It may be a child,
//  or if this is the first child of a branch, it retrieves the
//  previous sibling of the parent item.
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the next item
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetPrevItem()
{
    CXSTreeNode treeNode(GetParentTree());

    treeNode = GetPrevSiblingItem();
    if (!treeNode.GetSafeHandle())
        treeNode = GetParentItem();
    else
        treeNode = GetLastBranchItem();

    return treeNode;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SearchItem
// Purpose   : 
// Parameters: 
// Returns   : 
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::SearchItem(BOOL bDown) // = TRUE
{
    ASSERT_VALID(GetParentTree());

    CXSTreeNode nodeSel = !GetSafeHandle() ? GetParentTree()->GetSelectedItem() : *this;
    CXSTreeNode nodeCur = bDown ? nodeSel.GetNextItem() : nodeSel.GetPrevItem();

    if (!nodeCur.GetSafeHandle())
    {
        if (bDown)
            nodeCur = GetRootItem();
        else
            nodeCur = GetLastBranchItem();
    }

    while (nodeCur.GetSafeHandle() && nodeCur != nodeSel)
    {
        if (GetParentTree()->DoIsSearchNodeValid(nodeCur))
            return nodeCur;

        nodeCur = bDown ? nodeCur.GetNextItem() : nodeCur.GetPrevItem();
        if (!nodeCur.GetSafeHandle())
        {
            if (bDown)
                nodeCur = GetRootItem();
            else
                nodeCur = GetLastBranchItem();
        }
    }

    // Node not found
    return NodeNull;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SearchItemByString
// Purpose   : 
//  Search for the passed string starting with this object and
//  working down the branches. If this object's HTREEITEM is
//  NULL, it starts at the root item (note: the parent must be
//  valid!)
// Parameters: 
//  CString& str - the string to search for
//  BOOL bCaseSensitive - TRUE for case-sensitive, FALSE for not
//      case-sensitive. Default is FALSE.
//  BOOL bDown - TRUE to search downwards, FALSE to search 
//      upwards. Default is TRUE.
//  BOOL bPartial - TRUE to search for a partial string, FALSE
//      to search for the full string. Default is TRUE.
// Returns   : 
//  CXSTreeNode - A copy of the found item. HTREEITEM is NULL
//  (use GetSafeHandle()) if it is not found.
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::SearchItemByString(CString& str, 
                                BOOL bCaseSensitive,  // = FALSE
                                BOOL bDown,           // = TRUE
                                BOOL bPartial)        // = TRUE
{
    ASSERT_VALID(GetParentTree());

    int nStrLen = str.GetLength();
    if (0 == nStrLen)
        return NodeNull;

    CXSTreeNode nodeSel = !GetSafeHandle() ? GetParentTree()->GetSelectedItem() : *this;
    CXSTreeNode nodeCur = bDown ? nodeSel.GetNextItem() : nodeSel.GetPrevItem();
    CString strSearch = str;

    if (!nodeCur.GetSafeHandle())
    {
        if (bDown)
            nodeCur = GetRootItem();
        else
            nodeCur = GetLastBranchItem();
    }

    if (!bCaseSensitive)
        strSearch.MakeLower();

    while (nodeCur.GetSafeHandle() && nodeCur != nodeSel)
    {
        CString strItemText = nodeCur.GetItemText();
        if (!bCaseSensitive)
            strItemText.MakeLower();
        
        int n;
        while (-1 != ( n = strItemText.Find(strSearch)))
        {
            // String found
            if (!bPartial)
            {
                if (0 != n)
                {
                    if (isalpha(strItemText[n - 1]) || '_' == strItemText[n - 1])
                    {
                        // Not whole word
                        strItemText = strItemText.Right(strItemText.GetLength() - n - nStrLen);
                        continue;
                    }
                }

                if (strItemText.GetLength() > n + nStrLen && (isalpha(strItemText[n + nStrLen]) || '_' == strItemText[n + nStrLen]))
                {
                    // Not whole word
                    strItemText = strItemText.Right(strItemText.GetLength() - n - strSearch.GetLength());
                    continue;
                }
            }

            if (GetParentTree()->DoIsSearchNodeValid(nodeCur))
                return nodeCur;
            else
                break;
        }

        nodeCur = bDown ? nodeCur.GetNextItem() : nodeCur.GetPrevItem();
        if (!nodeCur.GetSafeHandle())
        {
            if (bDown)
                nodeCur = GetRootItem();
            else
                nodeCur = GetLastBranchItem();
        }
    }

    // Node not found
    return NodeNull;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::SetCheck
// Purpose   : 
//  Depending on the value of nCheck, the function 
//  determines what the new state of the item should be. 
//  If nCheck is "Refresh", only the immediate children items 
//  are scanned to determine if the checkbox should be read 
//  (to indicate the child is checked). The function then 
//  updates the parent object.
// Parameters: 
//  CheckType nCheck - Flag indicating what action to take.
//      Values are:
//      Check - Check the object's state
//      Uncheck - Uncheck the object's state
//      Toggle - Check if unchecked, uncheck if checked
//      Refresh - Update the object's state depanding on child
//          states
// Returns   : 
//  TRUE on success, FALSE on failure
// -------------------------------------------------------------
BOOL 
CXSTreeNode::SetCheck(CheckType nCheck)
{
	if (!GetSafeHandle())
		return FALSE;

	UINT nState = GetItemState(TVIS_STATEIMAGEMASK) >> 12;

	// determine the new check state
	if (Check == nCheck)
	{
		if (Checked == nState || ChildSelfChecked == nState)
			return TRUE;

		switch (nState)
		{
			case Unchecked:
				nState = Checked;
				break;

			case ChildChecked:
				nState = ChildSelfChecked;
				break;
		}
	}
	else if (Uncheck == nCheck)
	{
		if (Unchecked == nState || ChildChecked == nState)
			return TRUE;

		switch (nState)
		{
			case Checked:
				nState = Unchecked;
				break;

			case ChildSelfChecked:
				nState = ChildChecked;
				break;
		}
	}
	else if (Toggle == nCheck)
	{
		switch (nState)
		{
			case Unchecked:
				nState = Checked;
				break;

			case Checked:
				nState = Unchecked;
				break;

			case ChildChecked:
				nState = ChildSelfChecked;
				break;

			case ChildSelfChecked:
				nState = ChildChecked;
				break;
		}
	}
	else if (Refresh == nCheck)
	{
		BOOL bChildSelected = FALSE;
		CXSTreeNode nodeChild = GetChildItem();

		// Scan children
		while (nodeChild.GetSafeHandle())
		{
			UINT nChildState = nodeChild.GetItemState(TVIS_STATEIMAGEMASK) >> 12;
			if (Unchecked != nChildState && NoState != nChildState)
			{
				bChildSelected = TRUE;
				break;
			}

			nodeChild = nodeChild.GetNextItem(TVGN_NEXT);
		}

		if (bChildSelected)
		{
			if (Checked == nState)
				nState = ChildSelfChecked;
			else if (Unchecked == nState)
				nState = ChildChecked;
		}
		else
		{
			if (ChildSelfChecked == nState)
				nState = Checked;
			else if (ChildChecked == nState)
				nState = Unchecked;
		}
	}

    // Set the new state of this Node
	SetItemState(INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

    // Now verify Parent state
	if (Checked == nState || (Refresh && (ChildSelfChecked == nState || ChildChecked == nState)))
	{
		// Mark the parents to indicate that a child is selected
        CXSTreeNode nodeParent = GetParentItem();
		while (nodeParent.GetSafeHandle())
		{
			nState = nodeParent.GetItemState(TVIS_STATEIMAGEMASK) >> 12;
			if (Unchecked == nState)
				nodeParent.SetItemState(INDEXTOSTATEIMAGEMASK(ChildChecked), TVIS_STATEIMAGEMASK);
			else if (Checked == nState)
				nodeParent.SetItemState(INDEXTOSTATEIMAGEMASK(ChildSelfChecked), TVIS_STATEIMAGEMASK);

            // Get the next Parent of the Parent
            nodeParent = nodeParent.GetParentItem();
		}
	}
	else if (Unchecked == nState)
	{
		// Maybe the Parent (ancestor) state needs to be adjusted 
		// if no more children selected
        CXSTreeNode nodeParent = GetParentItem();
		while (nodeParent.GetSafeHandle())
		{
			// Scan children of Parent
			BOOL bChildSelected = FALSE;
			CXSTreeNode nodeChild = nodeParent.GetChildItem();

			while (nodeChild.GetSafeHandle())
			{
				UINT nChildState = nodeChild.GetItemState(TVIS_STATEIMAGEMASK) >> 12;
				if(Unchecked != nChildState && NoState != nChildState)
				{
					bChildSelected = TRUE;
					break;
				}

				nodeChild = nodeChild.GetNextItem(TVGN_NEXT);
			}

            if (bChildSelected)
			{
				// The parent does not need to be updated
				// since there are other children still selected
				break;
			}
			else
			{
				// The parent item has no more children selected
				// Mark accordingly
				UINT nParentState = nodeParent.GetItemState(TVIS_STATEIMAGEMASK) >> 12;
				if (ChildChecked == nParentState)
					nodeParent.SetItemState(INDEXTOSTATEIMAGEMASK(Unchecked), TVIS_STATEIMAGEMASK);
				else if (ChildSelfChecked == nParentState)
					nodeParent.SetItemState(INDEXTOSTATEIMAGEMASK(Checked), TVIS_STATEIMAGEMASK);
			}

            // Get the next Parent of the Parent
            nodeParent = nodeParent.GetParentItem();
		}
	}

	return TRUE;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetFirstChecked
// Purpose   : 
//  Retrieves the first checked object in the treeview control
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the checked object
// -------------------------------------------------------------
CXSTreeNode 
CXSTreeNode::GetFirstChecked()
{
	for (CXSTreeNode treeNode = GetRootItem(); treeNode.GetSafeHandle(); /**/)
	{
		int iImage = GetItemState(TVIS_STATEIMAGEMASK) >> 12;
		
		if (Checked == iImage || ChildSelfChecked == iImage)
			return treeNode;
		
		if (ChildChecked != iImage)
		{
			CXSTreeNode nodeNext = treeNode.GetNextItem(TVGN_NEXT);
			if (nodeNext.GetSafeHandle())
				treeNode = treeNode.GetNextItem();
			else
				treeNode = nodeNext;
		}
		else
		{
			treeNode = treeNode.GetNextItem();
		}
	}

	return NodeNull;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetNextChecked
// Purpose   : 
//  Retrieves a copy of the next checked object, starting from
//  this object
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the checked object
// -------------------------------------------------------------
CXSTreeNode 
CXSTreeNode::GetNextChecked()
{
	CXSTreeNode treeNode = GetNextItem();
	while (treeNode.GetSafeHandle())
	{
		int iImage = treeNode.GetItemState(TVIS_STATEIMAGEMASK) >> 12;
		
		if (Checked == iImage || ChildSelfChecked == iImage)
			return *this;

		if (ChildChecked != iImage)
		{
			CXSTreeNode nodeNext = treeNode.GetNextItem(TVGN_NEXT);
			if (!nodeNext.GetSafeHandle())
				treeNode = treeNode.GetNextItem();
			else
				treeNode = nodeNext;
		}
		else
		{
			treeNode = treeNode.GetNextItem();
		}
	}

	return NodeNull;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetPrevChecked
// Purpose   : 
//  Retrieves a copy of the previous checked object, starting 
//  from this object
// Parameters: 
//  None
// Returns   : 
//  CXSTreeNode - A copy of the checked object
// -------------------------------------------------------------
CXSTreeNode
CXSTreeNode::GetPrevChecked()
{	
    CXSTreeNode treeNode;
	for (treeNode = GetPrevItem(); treeNode.GetSafeHandle(); treeNode = treeNode.GetPrevItem()) 
		if (treeNode.IsChecked()) 
			return treeNode;

	return NodeNull;
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::IsChecked
// Purpose   : 
//  Determiones if this object is checked.
// Parameters: 
//  None
// Returns   : 
// TRUE if it is checked, otherwise FALSE if it is not.
// -------------------------------------------------------------
BOOL 
CXSTreeNode::IsChecked()
{	
	int iImage = GetItemState(TVIS_STATEIMAGEMASK) >> 12;
	return (iImage == Checked || iImage == ChildSelfChecked);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetNodeRect
// Purpose   : 
//  Retrieves the bounding rectangle of this object based on if
//  CXSTreeCtrl::m_nBoundText has been set. If this value is 0,
//  it uses CTreeCtrl::GetItemRect for the return value.
// Parameters: 
//  None
// Returns   : 
//  CXSRect - A copy of the returned RECT value.
// -------------------------------------------------------------
CXSRect
CXSTreeNode::GetNodeRect()
{
    return GetParentTree()->GetNodeRect(*this);
}

// -------------------------------------------------------------
// Function  : 
//  CXSTreeNode::GetSafeHandle
// Purpose   : 
//  Retrieves the HTREEITEM associated with this node, or NULL.
// Parameters: 
//  None
// Returns   : 
//  HTREEITEM - The HTREEITEM handle associated with this node,
//      or NULL
// -------------------------------------------------------------
HTREEITEM
CXSTreeNode::GetSafeHandle()
{ 
    return this == NULL ? NULL : m_hTreeItem == NULL ? 
        NULL : m_hTreeItem; 
}