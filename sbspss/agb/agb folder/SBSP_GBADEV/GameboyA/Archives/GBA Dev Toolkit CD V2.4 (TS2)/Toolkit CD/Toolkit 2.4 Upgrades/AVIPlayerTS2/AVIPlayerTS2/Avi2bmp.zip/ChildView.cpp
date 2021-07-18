// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "NewAVI2BMP.h"
#include "ChildView.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_CAPTION;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{

	// device context for painting
	CPaintDC dc (this); 
	
	// Get a pointer to the main window... 
	CMainFrame* main = (CMainFrame*)this->GetActiveWindow();

	// Get the active frame.. 
	// (I am not sure if this is getting correct frame)
	CChildFrame* TempWnd = (CChildFrame*)GetParent();

	// Setting text still not working!
	TempWnd->SetWindowText(TempWnd->FileName);

	// Use the XSSource DIB Draw instead to keep things consistent
	XSDib_Paint(dc, TempWnd->dibrt, TempWnd->DIBBuffer, TempWnd->dibrt, NULL);

	// Print the Frame Number and bitmap information to the screen!
	CString string;
	int i = 8;

	// Frame Number goes below the DIB
	string.Format("Frame Number:   %d", 
				  ((int)TempWnd->frameposition)+1);
	dc.TextOut(i, TempWnd->bmpheader->bmiHeader.biHeight+8, string);

	// All of the Bitmap information goes to the right of the DIB
	// I am not sure if the offset will work appropriately for all resolutions...
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, 
			    i, "Bitmap Header Information:");

	// Actual size of the DIB
	string.Format("  Size in Bytes:  %d", 
				  (int)TempWnd->bmpheader->bmiHeader.biSizeImage);
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Width of the DIB in pixels
	string.Format("  Width:              %d", 
				  (int)TempWnd->bmpheader->bmiHeader.biWidth);
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Height of the DIB in pixels
	string.Format("  Height:             %d", 
				  (int)TempWnd->bmpheader->bmiHeader.biHeight);
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Number of planes used by the DIB (should always be 1)
	string.Format("  Planes:             %d", 
				  (int)TempWnd->bmpheader->bmiHeader.biPlanes);
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Bit count of the DIB
	string.Format("  Bits per Pixel:  %d", 
				  (int)TempWnd->bmpheader->bmiHeader.biBitCount);
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Compressed? If so, what compression is used?
	// I think the AVI API decompresses the DIB, therefore there won't be any compression!
	switch(TempWnd->bmpheader->bmiHeader.biCompression){
	case BI_RGB:
		string = "  Compression:   No compression used";
		break;
	case BI_RLE8:
		string = "  Compression:   run-length encoded - 8 bit";
		break;
	case BI_RLE4:
		string = "  Compression:   run-length encoded - 4 bit";
		break;
	case BI_BITFIELDS:
		string = "  Compression:   No compression - Possible color masks";
		break;
	default:
		string = "  Compression:   Unkown compression format";
		break;
	}
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Collors Used in the DIB
	if ((int)TempWnd->bmpheader->bmiHeader.biClrUsed != 0)
		if ((int)TempWnd->bmpheader->bmiHeader.biBitCount <= 8)
			string.Format("  Colors Used:     %d", (int)TempWnd->bmpheader->bmiHeader.biClrUsed);
		else
			string.Format("  Color Table Size: %d", (int)TempWnd->bmpheader->bmiHeader.biClrUsed);
	else
		string.Format("  Colors Used:    Maximum colors in use");
	i += 24;
	dc.TextOut(TempWnd->bmpheader->bmiHeader.biWidth+8, i, string);

	// Do not call CWnd::OnPaint() for painting messages
}

