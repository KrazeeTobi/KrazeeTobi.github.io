// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__DE3FD00A_D89F_11D3_BE17_A64F4CB9BB4E__INCLUDED_)
#define AFX_CHILDFRM_H__DE3FD00A_D89F_11D3_BE17_A64F4CB9BB4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
	
#define MAX_LOADSTRING 255

#include "ChildView.h"
#include "XSMain.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	// view for the client area of the frame.
	CChildView m_wndView;
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CString WINFileName;
	CString FilePath;
	CString FileName;
	CString FileType;
	CString FilePreName;
	
	// AVI File access variables
	PAVIFILE			avifile;
	AVIFILEINFO			aviheader;
	PAVISTREAM			avistream, audiostream;
	AVISTREAMINFO		avistreamheader, audiostreamheader;

	// BMP access variables
	PGETFRAME			currentframe;
	LPBITMAPINFO		bmpheader;
	long				frameposition;
	HBITMAP				hBMP;	// needed to convet the project.

	HDIB				DIBBuffer;
	CRect				rt, dibrt;

	// WAV access variables
	LPWAVEFORMATEX		lpFormat;
	int					NoAudio; // Used if no audio is available


// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	afx_msg void OnFileClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__DE3FD00A_D89F_11D3_BE17_A64F4CB9BB4E__INCLUDED_)
