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

//#include "XSError.h"
//#include "XSNodeData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CXSNodeData, CObject);

// -------------------------------------------------------------
// Function  :
//  CXSNodeData::CXSNodeData
// Purpose   :
//  Constructor, initializes memory
// -------------------------------------------------------------
CXSNodeData::CXSNodeData()
{
    m_crFore = ::GetSysColor(COLOR_WINDOWTEXT);
    m_crBack = ::GetSysColor(COLOR_WINDOW);
    memset(&m_lfLogFont, '\0', sizeof(LOGFONT));
    m_nLabelLen = 0;
}

// -------------------------------------------------------------
// Function  :
//  CXSNodeData::CXSNodeData
// Purpose   :
//  Copy Constructor, initializes memory
// -------------------------------------------------------------
CXSNodeData::CXSNodeData(CXSNodeData& nodeData)
{
    *this = nodeData;
}

// -------------------------------------------------------------
// Function  :
//  CXSNodeData::~CXSNodeData
// Purpose   :
//    Destructor, cleans up memory
// -------------------------------------------------------------
CXSNodeData::~CXSNodeData()
{
}

// -------------------------------------------------------------
// Function  :
//  CXSNodeData::operator=
// Purpose   :
//  Copies referenced object to "this" object
// Parameters:
//  CXSNodeData& nodeData - object to copy from
// Returns   :
//  CXSNodeData& - A reference to "this"
// -------------------------------------------------------------
CXSNodeData&
CXSNodeData::operator=(CXSNodeData& nodeData)
{
    ASSERT(this);

    // Copy the data
    m_crFore = nodeData.m_crFore;
    m_crBack = nodeData.m_crBack;
    m_nLabelLen = nodeData.m_nLabelLen;
    memcpy(&m_lfLogFont, &nodeData.m_lfLogFont, sizeof(LOGFONT));

    return *this;
}

// -------------------------------------------------------------
// Function  :
//  CXSNodeData::operator==
// Purpose   :
//  Comparison operator for "is equal to"
// Parameters:
//  CXSNodeData& nodeData - class to compare
// Returns   :
//  TRUE if classes do equal each other
//  FALSE if classes do not equal each other
// -------------------------------------------------------------
BOOL
CXSNodeData::operator==(CXSNodeData& nodeData)
{
    ASSERT(this);

    if (m_crFore == nodeData.m_crFore &&
        m_crBack == nodeData.m_crBack &&
        m_nLabelLen == nodeData.m_nLabelLen &&
        (0 == memcmp(&m_lfLogFont, &nodeData.m_lfLogFont, sizeof(LOGFONT))))
    {
        return TRUE;
    }
    else
        return FALSE;
}

// -------------------------------------------------------------
// Function  :
//  CXSNodeData::operator!=
// Purpose   :
//  Comparison operator for "not equal to"
// Parameters:
//  CXSNodeData& nodeData - object to compare
// Returns   :
//  TRUE if objects do not equal each other
//  FALSE if objects do equal each other
// -------------------------------------------------------------
BOOL
CXSNodeData::operator!=(CXSNodeData& nodeData)
{
    return !(*this == nodeData);
}

