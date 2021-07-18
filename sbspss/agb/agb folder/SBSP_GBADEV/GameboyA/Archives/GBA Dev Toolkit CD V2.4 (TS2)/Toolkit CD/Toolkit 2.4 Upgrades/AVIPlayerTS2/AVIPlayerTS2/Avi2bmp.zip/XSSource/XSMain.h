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

#if !defined(AFX_XSMAIN_H__FD833968_73B7_11D1_AB26_742502C10000__INCLUDED_)
#define AFX_XSMAIN_H__FD833968_73B7_11D1_AB26_742502C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxcview.h>		// MFC Common controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>		// MFC Template support
#include <afxpriv.h>		// Undocumented MFC (usefull classes)

#ifndef AFX_WND_REG
//#include <..\src\afximpl.h>	// Auxiliary System/Screen metrics (MFC SRC dir)
#endif

#include <io.h>
#include <stdio.h>
#include <memory.h>
#include <ctype.h>

// ----------------------------------------------------------------
// Inline definitions
#ifdef _DEBUG
	#define XS_INLINE
#else
	#define XS_INLINE __inline
#endif  // _DEBUG

// ----------------------------------------------------------------
// XSAPI is used on global public functions
#if 0
#ifndef XSAPI
    #define XSAPI __stdcall
#endif
#endif
#define XSAPI


// ----------------------------------------------------------------
// Export/Import definitions
// If you are using this class library in a DLL, then #define
// _XSDLL in your project settings.
// If you are importing classes/function/data from a DDL that
// contains this library, then #define _XSIMPORT so they will be
// imported correctly.
#if 0
#ifdef _XSDLL
	#ifdef _XSIMPORT
		#define XSCLASS	__declspec(dllimport)
		#define XSFUNC	__declspec(dllimport) WINAPI
		#define XSDATA	__declspec(dllimport)
	#else // _XSIMPORT
		#define XSCLASS	__declspec(dllexport)
		#define XSFUNC	__declspec(dllexport) WINAPI
		#define XSDATA	__declspec(dllexport)
	#endif // _XSIMPORT
#else // _XSDLL
	#define XSCLASS
	#define XSFUNC  WINAPI
	#define XSDATA
#endif // _XSDLL
#endif
#define XSCLASS
#define XSFUNC
#define XSDATA


// ----------------------------------------------------------------
// Libraries to link with when including this header file
// Use _XSINTERNAL to make sure a DLL doesn't link with itself.
// Use _XSDLL when you want to link with an XS DLL
#if 0
#ifndef _XSINTERNAL
	#ifdef _DEBUG
		#ifdef _UNICODE
			#ifdef _XSDLL
				#pragma comment(lib,"XSD100ud.lib")
			#else
				#pragma comment(lib,"XS100ud.lib")
			#endif // _XSDLL
		#else // _UNICODE
			#ifdef _XSDLL
				#pragma comment(lib,"XSD100d.lib")
			#else
				#pragma comment(lib,"XS100d.lib")
			#endif // _XSDLL
		#endif // _UNICODE
	#else // _DEBUG
		#ifdef _UNICODE
			#ifdef _XSDLL
				#pragma comment(lib,"XSD100u.lib")
			#else
				#pragma comment(lib,"XS100u.lib")
			#endif // _XSDLL
		#else // _UNICODE
			#ifdef _XSDLL
				#pragma comment(lib,"XSD100.lib")
			#else
				#pragma comment(lib,"XS100.lib")
			#endif // _XSDLL
		#endif // _UNICODE
	#endif // _DEBUG
#endif // _XSINTERNAL
#endif
// ----------------------------------------------------------------
// Extension Include Files - only when building non-internally
#ifndef _XSINTERNAL
#include "XSError.h"

#include "XSMisc.h"
#include "XSRect.h"

#include "XSPalApi.h"
#include "XSPalette.h"

#include "XSDibApi.h"
#include "XSBitmap.h"

#include "XSSubWndCtrl.h"
#include "XSNotify.h"
#include "XSObject.h"

#include "XSBgCtrl.h"

#include "XSCaption.h"

#include "XSNodeData.h"
#include "XSCheckType.h"
#include "XSTreeNode.h"
#include "XSTreeCtrl.h"
#endif  // _XSINTERNAL

#endif // !defined(AFX_XSMAIN_H__FD833968_73B7_11D1_AB26_742502C10000__INCLUDED_)
