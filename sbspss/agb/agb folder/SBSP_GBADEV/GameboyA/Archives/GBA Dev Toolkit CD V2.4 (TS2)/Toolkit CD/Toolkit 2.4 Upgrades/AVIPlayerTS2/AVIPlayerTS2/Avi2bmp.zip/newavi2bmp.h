// NewAVI2BMP.h : main header file for the NEWAVI2BMP application
//

#if !defined(AFX_NEWAVI2BMP_H__DE3FD004_D89F_11D3_BE17_A64F4CB9BB4E__INCLUDED_)
#define AFX_NEWAVI2BMP_H__DE3FD004_D89F_11D3_BE17_A64F4CB9BB4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNewAVI2BMPApp:
// See NewAVI2BMP.cpp for the implementation of this class
//

class CNewAVI2BMPApp : public CWinApp
{
public:
	CNewAVI2BMPApp();
	unsigned short NumberOpen;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewAVI2BMPApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	unsigned long err;					// used for error tracking

	

public:
// WINGetFile Variables
	char * filter;
	OPENFILENAME ofn;

	HMENU	m_hMDIMenu;
	HACCEL	m_hMDIAccel;

	//{{AFX_MSG(CNewAVI2BMPApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnViewDetails();
	afx_msg void OnAviConvert();
	afx_msg void OnAviNext();
	afx_msg void OnAviPrevious();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// FileInfo dialog

class FileInfo : public CDialog
{
// Construction
public:
	FileInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FileInfo)
	enum { IDD = IDD_FILEINFO };
	long	m_Streams;
	long	m_Frames;
	long	m_usecPerFram;
	long	m_BufferSz;
	long	m_Width;
	long	m_Height;
	CString	m_Compression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FileInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FileInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// convertDialog dialog

class convertDialog : public CDialog
{
// Construction
public:
	convertDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(convertDialog)
	enum { IDD = IDD_MYCONVERT };
	int		m_SearchVal;
	int		m_CompType;
	int		m_DiffBitSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(convertDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(convertDialog)
	afx_msg void OnDiff();
	afx_msg void OnLz77();
	afx_msg void OnRle();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWAVI2BMP_H__DE3FD004_D89F_11D3_BE17_A64F4CB9BB4E__INCLUDED_)
