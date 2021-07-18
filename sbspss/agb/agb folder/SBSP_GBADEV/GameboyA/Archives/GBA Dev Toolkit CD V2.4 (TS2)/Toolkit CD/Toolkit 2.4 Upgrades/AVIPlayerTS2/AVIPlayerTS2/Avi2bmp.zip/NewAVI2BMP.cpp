// NewAVI2BMP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NewAVI2BMP.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "Utils.h"
#include "XSMain.h"
#include "riff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewAVI2BMPApp

BEGIN_MESSAGE_MAP(CNewAVI2BMPApp, CWinApp)
	//{{AFX_MSG_MAP(CNewAVI2BMPApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_AVI_DETAILS, OnViewDetails)
	ON_COMMAND(ID_AVI_CONVERT, OnAviConvert)
	ON_COMMAND(ID_AVI_NEXT, OnAviNext)
	ON_COMMAND(ID_AVI_PREVIOUS, OnAviPrevious)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewAVI2BMPApp construction

CNewAVI2BMPApp::CNewAVI2BMPApp()
{
	// TODO: add construction code here,
	AVIFileInit();
	err = 1;
	NumberOpen = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNewAVI2BMPApp object

CNewAVI2BMPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNewAVI2BMPApp initialization

BOOL CNewAVI2BMPApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Nintendo of America, Cave"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMDIFrameWnd* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need. 

	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_NEWAVITYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_NEWAVITYPE));

	// Insert Create Window function here!!!
#ifdef _DEBUG
	createWinConsole(50, 50);
#endif

	// The main window has been initialized, so show and update it.
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CNewAVI2BMPApp message handlers

int CNewAVI2BMPApp::ExitInstance() 
{
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}

// Not currently used....
void CNewAVI2BMPApp::OnFileNew() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// create a new MDI child window
	pFrame->CreateNewChild(
		RUNTIME_CLASS(CChildFrame), IDR_NEWAVITYPE, m_hMDIMenu, m_hMDIAccel);
}


/////////////////////////////////////////////////////////////////////////////
// CNewAVI2BMPApp message handlers


void CNewAVI2BMPApp::OnFileOpen() 
{
	static char		szFilter[] = "AVI Files (*.avi)\0*.avi\0"; 
	unsigned char	value;
	CString			tempstr = " ";	// temp string used for file extension verification
	unsigned long	hr;				// used for error checks
	CChildFrame*	TempWnd;		// Child Frame pointer
	int				i;				// used for string location

	// Temporary filename variables....
	char WINFileName[MAX_LOADSTRING] = "\0";
	char FileName[MAX_LOADSTRING] = "\0";



	ofn.lStructSize				= sizeof(OPENFILENAME);
	ofn.hwndOwner				= NULL;
	ofn.hInstance				= NULL;
	ofn.lpstrFilter				= szFilter;
	ofn.lpstrCustomFilter		= NULL;
	ofn.nMaxCustFilter			= 0;
	ofn.nFilterIndex			= 0;
	ofn.lpstrFile				= WINFileName;
	ofn.nMaxFile				= _MAX_PATH;
	ofn.lpstrFileTitle			= FileName;
	ofn.nMaxFileTitle			= _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir			= NULL;
	ofn.lpstrTitle				= "Open File";
	ofn.Flags					= OFN_OVERWRITEPROMPT & OFN_FILEMUSTEXIST & OFN_PATHMUSTEXIST & OFN_EXTENSIONDIFFERENT;
	ofn.nFileOffset				= 0;
	ofn.nFileExtension			= 0;
	ofn.lpstrDefExt				= NULL;
	ofn.lCustData				= 0L;
	ofn.lpfnHook				= NULL;
	ofn.lpTemplateName			= NULL;


	// add error checking here!!
	while (tempstr.CompareNoCase(".avi")) {
		value = GetOpenFileName(&ofn);

		if (!value) 
		{
			#ifdef _DEBUG
			debugPrint("Error opening file!");
			#endif

			return;
		}

		tempstr = FileName;
		i = tempstr.Find(".");
		tempstr = tempstr.Right(tempstr.GetLength() - i);

		// need better error checking here... 
		if (tempstr.CompareNoCase(".avi"))
		{
			AfxMessageBox("You have chosen an incorrect file type for this application.\n Please choose another file or cancel the open window.",
						   MB_ICONEXCLAMATION & MB_OK, 0);
			#ifdef _DEBUG
			debugPrint("wrong file type!");
			#endif
		}
	} // end While

	// create the child window to display messages, etc.	
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	NumberOpen++;

	// create a new MDI child window
	TempWnd = (CChildFrame*)pFrame->CreateNewChild(RUNTIME_CLASS(CChildFrame), IDR_NEWAVITYPE, 
									 m_hMDIMenu, m_hMDIAccel);

	// Store filename info
	TempWnd->WINFileName = WINFileName;
	TempWnd->FileName = FileName;

	// Path
	i = TempWnd->WINFileName.Find(TempWnd->FileName);
	TempWnd->FilePath = TempWnd->WINFileName.Left(TempWnd->WINFileName.GetLength() - (TempWnd->WINFileName.GetLength() - i));
	
	// Type and Filename without extension
	i = TempWnd->FileName.Find(".");
	TempWnd->FileType = TempWnd->FileName.Right(TempWnd->FileName.GetLength() - i);
	TempWnd->FilePreName = TempWnd->FileName.SpanExcluding(".");	

	// Open the AVI file for manipulation
	hr = AVIFileOpen(&TempWnd->avifile, TempWnd->WINFileName, 
					 OF_SHARE_DENY_WRITE, NULL); 
	if (hr > 0) {
		AfxMessageBox("Unable to properly open AVI File. Exiting window.", MB_ICONERROR & MB_OK, 0);
		TempWnd->DestroyWindow();
		return;
	}

	// Get main AVI header information
	hr = AVIFileInfo(TempWnd->avifile, &TempWnd->aviheader, 
					 sizeof(TempWnd->aviheader));
	if (hr > 0){
		AfxMessageBox("Unable to get AVI header information from file. Exiting window.", MB_ICONERROR & MB_OK, 0);
		TempWnd->DestroyWindow();
		return;
	}

	// Load the video stream
	hr = AVIFileGetStream(TempWnd->avifile, &TempWnd->avistream, 
						  streamtypeVIDEO, 0);
	if (hr > 0){
		AfxMessageBox("Unable to properly open video stream. Exiting window.", MB_ICONERROR & MB_OK, 0);
		TempWnd->DestroyWindow();
		return;
	} 

	// Get video stream information
	hr = AVIStreamInfo(TempWnd->avistream, &TempWnd->avistreamheader, 
					   sizeof(TempWnd->avistreamheader));
	if (hr > 0){
		AfxMessageBox("Unable to properly open AVI video stream header information. Exiting window.", 
			MB_ICONERROR & MB_OK, 0);
		TempWnd->DestroyWindow();
		return;
	}

	// Open the frame area so we can grab the individual frames
	// (Can only store one DIB frame at a time!)
	TempWnd->currentframe = AVIStreamGetFrameOpen(TempWnd->avistream, NULL);

	// Set the rectangle coordinates for the window to the Height/Width of AVI
	TempWnd->GetClientRect(TempWnd->rt);
		
	// Get the first frame and store it in the DIB buffer
	TempWnd->DIBBuffer = (HDIB)AVIStreamGetFrame(TempWnd->currentframe, 
												 TempWnd->frameposition);

	// Store the size of the DIB in the dib rectangle for drawing
	TempWnd->dibrt.right = XSDib_Width(TempWnd->DIBBuffer);
	TempWnd->dibrt.bottom = XSDib_Height(TempWnd->DIBBuffer);

	// Get the bitmap header information and store it for next use.
	TempWnd->bmpheader = (LPBITMAPINFO)TempWnd->DIBBuffer;	
	
	// Load the audio stream
	hr = AVIFileGetStream(TempWnd->avifile, &TempWnd->audiostream, 
						  streamtypeAUDIO, 0);
	if (hr > 0) {
		AfxMessageBox("No Audio Data available", MB_ICONERROR & MB_OK, 0);
		TempWnd->NoAudio = 0;
	} else {
		// Get audio stream information
		hr = AVIStreamInfo(TempWnd->audiostream, &TempWnd->audiostreamheader, 
					   sizeof(TempWnd->audiostreamheader));
		if (hr > 0) {
		AfxMessageBox("Unable to get audio stream data", MB_ICONEXCLAMATION & MB_OK, 0);
		TempWnd->NoAudio = 0;
		}
	}

	// return as there were no problems!
	return;	
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CNewAVI2BMPApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// FileInfo dialog


FileInfo::FileInfo(CWnd* pParent /*=NULL*/)
	: CDialog(FileInfo::IDD, pParent)
{
	// Get a pointer to the main window...
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);

	// Get the active frame..
	CChildFrame* TempWnd = (CChildFrame*)pFrame->GetActiveFrame();

	//{{AFX_DATA_INIT(FileInfo)
	m_Streams = TempWnd->aviheader.dwStreams;
	m_Frames = TempWnd->aviheader.dwLength;
	m_usecPerFram = TempWnd->aviheader.dwScale;
	m_BufferSz = TempWnd->aviheader.dwSuggestedBufferSize;
	m_Width = TempWnd->aviheader.dwWidth;
	m_Height = TempWnd->aviheader.dwHeight;
	//}}AFX_DATA_INIT
}


void FileInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FileInfo)
	DDX_Text(pDX, IDC_EDIT1, m_Streams);
	DDX_Text(pDX, IDC_EDIT2, m_Frames);
	DDX_Text(pDX, IDC_EDIT3, m_usecPerFram);
	DDX_Text(pDX, IDC_EDIT4, m_BufferSz);
	DDX_Text(pDX, IDC_EDIT5, m_Width);
	DDX_Text(pDX, IDC_EDIT7, m_Height);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileInfo, CDialog)
	//{{AFX_MSG_MAP(FileInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileInfo message handlers

void CNewAVI2BMPApp::OnViewDetails() 
{
	// TODO: Update variables here..

	// If no file is open, just exit
	if (NumberOpen <= 0)
		return;

	FileInfo FileInfoDlg;
	FileInfoDlg.DoModal();
}


// Convert the AVI file to BMPs and save them for now...
void CNewAVI2BMPApp::OnAviConvert() 
{
	// If no file is open, just exit
	if (NumberOpen <= 0)
		return;

	// Strings to hold filename information
	CString str, status, buffer;

	// Files to store the Makefile include information for the BMPs and the table of names
	CStdioFile	hfile, mkconv, cfile, mkfile;
	CFileException e;

	// A progress control meter to show the progress of the saving routine!
	CProgressCtrl progress;

	// used for error status
	int i;

	// Rectangle used for the progress bar
	RECT rt;

	// Used for Audio conversion..6/15/00 - JV
	const int MAX_CHANNELS = 4;
    LONG	cbFormat = NULL;
	LONG	slCurrent;
	LONG	BytesRead;
	LONG	SamplesRead;
	CString	outFilename;

	// Get a pointer to the main window...
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);

	// Get the active frame..
	CChildFrame* TempWnd = (CChildFrame*)pFrame->GetActiveFrame();

	//display the wait cursor while processing...may need to restore it before a message box.
	CWaitCursor wait;

	// reset the frame counter so we don't go out of bounds.
	TempWnd->frameposition = 0;

	// Set up the rectangle for the progress meter
	rt.top = TempWnd->rt.top + (TempWnd->rt.bottom - (TempWnd->rt.top + 50))/2;
	rt.left = TempWnd->rt.left + (TempWnd->rt.right - (TempWnd->rt.left + 500))/2;
	rt.bottom = rt.top + 50;
	rt.right = rt.left + 500;

	// check to see if the width and height and color depth are correct! If not,  
	// exit this function and display a message stating the problem!
	if ((TempWnd->bmpheader->bmiHeader.biWidth != 160) && 
		(TempWnd->bmpheader->bmiHeader.biWidth != 240)) {
		status.Format("The AVI frames are not the correct width for the AGB. They must be \neither 160 pixels, or 240 pixels, wide. This AVI is %d pixels wide.", 
					  TempWnd->bmpheader->bmiHeader.biWidth);
		AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);
		return;
	}

	if ((TempWnd->bmpheader->bmiHeader.biHeight != 128) && 
		(TempWnd->bmpheader->bmiHeader.biHeight != 160)) {
		status.Format("The AVI frames are not the correct height for the AGB. They must be \neither 128 pixels, or 160 pixels, tall. This AVI is %d pixels tall.", 
					  TempWnd->bmpheader->bmiHeader.biHeight);
		AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);
		return;
	}

	if ((TempWnd->bmpheader->bmiHeader.biBitCount != 4) && 
		(TempWnd->bmpheader->bmiHeader.biBitCount != 8) && 
		(TempWnd->bmpheader->bmiHeader.biBitCount != 24)) {
		status.Format("The AVI frames are not the correct color depth for the AGB. They must be \neither 4 bit, 8bit or 24 bit. This AVI has a %d bit color depth.", 
					  TempWnd->bmpheader->bmiHeader.biBitCount);
		AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);
		return;
	}

	// Get Compression style choices
	convertDialog ConvertDlg;
	if (ConvertDlg.DoModal() == IDCANCEL)
		return;
	
	// Create the Progress control bar and set up the step and range of it
	progress.Create(PBS_SMOOTH | WS_CAPTION | WS_CHILD | WS_VISIBLE, rt, pFrame, 0);

	progress.SetRange32(0, (int)TempWnd->aviheader.dwLength);

	progress.SetStep(1);

	// path to create
	str.Format("%s%s", TempWnd->FilePath, TempWnd->FilePreName);

	//Create the directory to store the BMP files in!
	i = CreateDirectory(str, NULL);
	err = GetLastError();

	if ((i == 0) && (err != 183 )) {
		status.Format("Conversion failed!\n\nUnable to create the directory to store the BMP files:\n%s", str);
		AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);

		#ifdef _DEBUG
		debugPrint("Directory not successfully created!");
		#endif
		return;
	} else {
		status.Format("Saving converted BMPs to %s", str);
		//AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);
		progress.SetWindowText(status);

		#ifdef _DEBUG
		debugPrint("Directory successfully created!\n");
		#endif
	}


	// File and path to create for Make file include
	str.Format("%s%s\\bmpfiles.mak", TempWnd->FilePath, TempWnd->FilePreName);

	// Create the file to save the BMPfile information for the Makefile
	if (!mkfile.Open(str, CFile::modeCreate | CFile::modeWrite, &e)) {
		#ifdef _DEBUG
		debugPrint("Include File could not be opened %s \n", e.m_cause);
		#endif
	}

	// File and path to create for Make file conversion include
	str.Format("%s%s\\makefile", TempWnd->FilePath, TempWnd->FilePreName);

	// Create the file to save the BMPfile information for the Makefile
	if (!mkconv.Open(str, CFile::modeCreate | CFile::modeWrite, &e)) {
		#ifdef _DEBUG
		debugPrint("Conversion File could not be opened %s \n", e.m_cause);
		#endif
	}

	// File and path to create for header file listing address information
	str.Format("%s%s\\bmpdata.c", TempWnd->FilePath, TempWnd->FilePreName);

	// Create the file to save the BMPfile information for the Makefile
	if (!cfile.Open(str, CFile::modeCreate | CFile::modeWrite, &e)) {
		#ifdef _DEBUG
		debugPrint("Header File could not be opened %s \n", e.m_cause);
		#endif
	}

	// File and path to create for header file listing address information
	str.Format("%s%s\\bmpdata.h", TempWnd->FilePath, TempWnd->FilePreName);

	// Create the file to save the BMPfile information for the Makefile
	if (!hfile.Open(str, CFile::modeCreate | CFile::modeWrite, &e)) {
		#ifdef _DEBUG
		debugPrint("Header File could not be opened %s \n", e.m_cause);
		#endif
	}

	// Create the header information for the header file
	buffer.Format("//============================================================\n");
	hfile.WriteString(buffer);

	buffer.Format("//\tbmpdata.h\n//\tBtimap Data Defines\n//\n//\tCopyright (C) 2000, NINTENDO Co., Ltd.\n");
	hfile.WriteString(buffer);

	buffer.Format("//============================================================\n\n");
	hfile.WriteString(buffer);

	buffer.Format("#ifndef	__BMPDATA_H__\n#define	__BMPDATA_H__\n\n#include <agb.h>\n\n");
	hfile.WriteString(buffer);

	buffer.Format("//------------------------- Defines  --------------------------\n\n");
	hfile.WriteString(buffer);

	buffer.Format("#define\tAVI_LENGTH\t%d\t\t\t\t\t// Number of AVI frames\n", TempWnd->aviheader.dwLength);
	hfile.WriteString(buffer);

	buffer.Format("#define\tAVI_SCALE\t%d\t\t\t\t// AVI u second per frame\n", TempWnd->aviheader.dwScale);
	hfile.WriteString(buffer);

	buffer.Format("#define\tFRAME_WAIT\t%d\t\t\t\t\t// V Blank waits to load frames\n", 
				  60/(TempWnd->aviheader.dwRate/TempWnd->aviheader.dwScale));
	hfile.WriteString(buffer);

	// Set up BMP mode dependent defines
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240)
		buffer.Format("#define\tBG_STATE\tDISP_MODE_4\t\t\t// 240x160 256 colors\n");
	else
		buffer.Format("#define\tBG_STATE\tDISP_MODE_5\t\t\t// 160x128 32K colors\n");
	hfile.WriteString(buffer);

	if (TempWnd->bmpheader->bmiHeader.biWidth == 240)
		buffer.Format("#define\tBG_CENTER_X\t120\t\t\t\t\t// Center X screen position\n");
	else
		buffer.Format("#define\tBG_CENTER_X\t(40 * 0x100) + 120\t// Center X screen position\n");
	hfile.WriteString(buffer);

	if (TempWnd->bmpheader->bmiHeader.biWidth == 240)
		buffer.Format("#define\tBG_CENTER_Y\t80\t\t\t\t\t// Center Y screen position\n");
	else
		buffer.Format("#define\tBG_CENTER_Y\t(16 * 0x100) + 80\t// Center Y screen position\n");
	hfile.WriteString(buffer);

	buffer.Format("//----------------------- Bitmap data  -----------------------\n\n");
	hfile.WriteString(buffer);

	buffer.Format("u16 Frame;\t// Frame Counter\n\n");
	hfile.WriteString(buffer);

	// 240x160 BMP mode requires palette data, set external define for combined BMP palette
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240) {
		buffer.Format("// Palette data for 256 color mode\n");
		hfile.WriteString(buffer);
		buffer.Format("extern u16 _binary_%s1_plb_start[];\n", TempWnd->FilePreName);
		hfile.WriteString(buffer);
		buffer.Format("extern u16 _binary_%s1_plb_start[];\n", TempWnd->FilePreName);
		hfile.WriteString(buffer);
		buffer.Format("extern u16 _binary_%s1_plb_start[];\n\n", TempWnd->FilePreName);
		hfile.WriteString(buffer);
	}	

	buffer.Format("extern const u8 *BMPAccessTable[];\n\n");
	hfile.WriteString(buffer);

	// Create the header information for the c file
	buffer.Format("//============================================================\n");
	cfile.WriteString(buffer);

	buffer.Format("//\tbmpdata.c\n//\tBtimap Data Defines\n//\n//\tCopyright (C) 2000, NINTENDO Co., Ltd.\n");
	cfile.WriteString(buffer);

	buffer.Format("//============================================================\n");
	cfile.WriteString(buffer);

	buffer.Format("\n#include <agb.h>\n#include \"bmpdata.h\"\n\n");
	cfile.WriteString(buffer);

	buffer.Format("//-------------------- Local variables  --------------------------\n\n");
	cfile.WriteString(buffer);

	switch (ConvertDlg.m_CompType) {
	case 0:
		if (ConvertDlg.m_SearchVal == 0) {
			buffer.Format("const u8 *BMPAccessTable[] = {\n_binary_%s%d_LZ_bin_start", TempWnd->FilePreName, 
				  TempWnd->frameposition + 1);
			cfile.WriteString(buffer);
			break;
		} else if (ConvertDlg.m_SearchVal == 1) {
			buffer.Format("const u8 *BMPAccessTable[] = {\n_binary_%s%d_LZ_bin_start", TempWnd->FilePreName, 
				  TempWnd->frameposition + 1);
			cfile.WriteString(buffer);
			break;
		} else {
			buffer.Format("const u8 *BMPAccessTable[] = {\n_binary_%s%d_LZ_bin_start", TempWnd->FilePreName, 
				  TempWnd->frameposition + 1);
			cfile.WriteString(buffer);
			break;
		}
	case 1: {
		buffer.Format("const u8 *BMPAccessTable[] = {\n_binary_%s%d_RL_bin_start", TempWnd->FilePreName, 
			  TempWnd->frameposition + 1);
		cfile.WriteString(buffer);
		break;
	}
	case 2:
		if (ConvertDlg.m_DiffBitSize == 0) {
			buffer.Format("const u8 *BMPAccessTable[] = {\n_binary_%s%d_Diff_bin_start", TempWnd->FilePreName, 
				  TempWnd->frameposition + 1);
			cfile.WriteString(buffer);
			break;
		} else {
			buffer.Format("const u8 *BMPAccessTable[] = {\n_binary_%s%d_Diff_bin_start", TempWnd->FilePreName, 
				  TempWnd->frameposition + 1);
			cfile.WriteString(buffer);
			break;
		}	
	} // end switch

	// Create the conversion routine and the makefile
	buffer.Format("# Pre-generated makefile for the bitmap library used with Player project\n");
	mkconv.WriteString(buffer);

	buffer.Format("# This file is also generated from AVI2BMP\ninclude bmpfiles.mak\n\n");
	mkconv.WriteString(buffer);

	buffer.Format("TARGET_ARC = libbitmap.a\n\n$(TARGET_ARC): $(BMPFILES:.bmp=.o)\n");
	mkconv.WriteString(buffer);

	buffer.Format("\tar rc $(TARGET_ARC) $(BMPFILES:.bmp=.o) ");
	mkconv.WriteString(buffer);

	// If using large screen, we must also be using 256 color palette so add it to library
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240) {
		buffer.Format("$(PALETTEOBJ)");
		mkconv.WriteString(buffer);
	}

	buffer.Format("\n\n.SUFFIXES: .bmp .o\n\n");
	mkconv.WriteString(buffer);

	buffer.Format(".bmp.o:\n\t@echo Creating bitmap library $<...\n\tbmp2agb -bi -bm -np ");
	mkconv.WriteString(buffer);

	// Add compression switch for BMP2AGB conversion 
	switch (ConvertDlg.m_CompType) {
	case 0:
		if (ConvertDlg.m_SearchVal == 0) {
			buffer.Format("-l 2 $<\n\tobjcopy -v -I binary -O elf32-little ");
			mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_LZ.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_LZ.bin)\n");
			mkconv.WriteString(buffer);
			break;
		} else if (ConvertDlg.m_SearchVal == 1) {
			buffer.Format("-l 4 $<\n\tobjcopy -v -I binary -O elf32-little ");
			mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_LZ.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_LZ.bin)\n");
			mkconv.WriteString(buffer);
			break;
		} else {
			buffer.Format("-l 8 $<\n\tobjcopy -v -I binary -O elf32-little ");
			mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_LZ.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_LZ.bin)\n");
			mkconv.WriteString(buffer);
			break;
		}
	case 1: {
		buffer.Format("-r $<\n\tobjcopy -v -I binary -O elf32-little ");
		mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_RL.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_RL.bin)\n");
			mkconv.WriteString(buffer);
		break;
	}
	case 2:
		if (ConvertDlg.m_DiffBitSize == 0) {
			buffer.Format("-d 8 $<\n\tobjcopy -v -I binary -O elf32-little ");
			mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_Diff.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_Diff.bin)\n");
			mkconv.WriteString(buffer);
			break;
		} else {
			buffer.Format("-d 16 $<\n\tobjcopy -v -I binary -O elf32-little ");
			mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_Diff.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_Diff.bin)\n");
			mkconv.WriteString(buffer);
			break;
		}	
	} // end switch


	// If the file is 240x160, then it must be need a palette. Add this to the conversion make file
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240) {

		buffer.Format("\n%s1.o: %s1.bmp\n\tbmp2agb -bi -bm -np ", TempWnd->FilePreName, TempWnd->FilePreName);
		mkconv.WriteString(buffer);

		// Add compression switch for BMP2AGB conversion 
		switch (ConvertDlg.m_CompType) {
		case 0:
			if (ConvertDlg.m_SearchVal == 0) {
				buffer.Format("-l 2 $<\n\tobjcopy -v -I binary -O elf32-little ");
				mkconv.WriteString(buffer);
				buffer.Format("$(<:.bmp=_LZ.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_LZ.bin)\n");
				mkconv.WriteString(buffer);
				break;
			} else if (ConvertDlg.m_SearchVal == 1) {
				buffer.Format("-l 4 $<\n\tobjcopy -v -I binary -O elf32-little ");
				mkconv.WriteString(buffer);
				buffer.Format("$(<:.bmp=_LZ.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_LZ.bin)\n");
				mkconv.WriteString(buffer);
				break;
			} else {
				buffer.Format("-l 8 $<\n\tobjcopy -v -I binary -O elf32-little ");
				mkconv.WriteString(buffer);
				buffer.Format("$(<:.bmp=_LZ.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_LZ.bin)\n");
				mkconv.WriteString(buffer);
				break;
			}
		case 1: {
			buffer.Format("-r $<\n\tobjcopy -v -I binary -O elf32-little ");
			mkconv.WriteString(buffer);
			buffer.Format("$(<:.bmp=_RL.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_RL.bin)\n");
			mkconv.WriteString(buffer);
			break;
		}
		case 2:
			if (ConvertDlg.m_DiffBitSize == 0) {
				buffer.Format("-d 8 $<\n\tobjcopy -v -I binary -O elf32-little ");
				mkconv.WriteString(buffer);
				buffer.Format("$(<:.bmp=_Diff.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_Diff.bin)\n");
				mkconv.WriteString(buffer);
				break;
			} else {
				buffer.Format("-d 16 $<\n\tobjcopy -v -I binary -O elf32-little ");
				mkconv.WriteString(buffer);
				buffer.Format("$(<:.bmp=_Diff.bin) $(<:.bmp=.o)\n\trm $(<:.bmp=_Diff.bin)\n");
				mkconv.WriteString(buffer);
				break;
			}	
		} // end switch
		
		buffer.Format("\n\tbmp2bin -p %s1.bmp\n\tobjcopy -v -I binary -O elf32-little", TempWnd->FilePreName);
		mkconv.WriteString(buffer);

		buffer.Format(" %s1.plb %s.o\n\trm %s1.plb\n", TempWnd->FilePreName, TempWnd->FilePreName, TempWnd->FilePreName);
		mkconv.WriteString(buffer);
	} //end if

	buffer.Format("\nclean:\n\trm $(BMPFILES:.bmp=.o)");
	mkconv.WriteString(buffer);

	// delete palette obj file when using clean option of makefile
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240) {
		buffer.Format(" %s.o\n", TempWnd->FilePreName);
		mkconv.WriteString(buffer);
	}
/*
	buffer.Format(" #$(TARGET_ARC) $(BMPFILES)");
	mkconv.WriteString(buffer);
*/
	// Save the initial information into the new file
	buffer.Format("BMPFILES\t=\t%s%d.bmp", TempWnd->FilePreName, TempWnd->frameposition + 1);
	mkfile.WriteString(buffer);

	// Get the device context for the child window
	HDC hDC = GetDC(TempWnd->m_hWnd);
	while (TempWnd->frameposition < (long)TempWnd->aviheader.dwLength) {

		status.Format("Saving frame %d of %d. Please wait for the application to finish.",
					   TempWnd->frameposition + 1, TempWnd->aviheader.dwLength);

		pFrame->m_wndStatusBar.SetPaneText(0, status);

		// Get the current frame and store it in the DIB buffer
		TempWnd->DIBBuffer = (HDIB)AVIStreamGetFrame(TempWnd->currentframe, 
													 TempWnd->frameposition);

		// Get the bitmap header information and store it for next use.
		TempWnd->bmpheader = (LPBITMAPINFO)TempWnd->DIBBuffer;

		// Increase the frame position by one before getting next frame
		TempWnd->frameposition++;
		
		// Create the filename for the dib
		str.Format("%s%s\\%s%d.bmp", TempWnd->FilePath, TempWnd->FilePreName, 
				   TempWnd->FilePreName, TempWnd->frameposition);

		// save the dib out to a file
		i = XSDib_Save(TempWnd->DIBBuffer, str);

	
		if (TempWnd->frameposition < (int)TempWnd->aviheader.dwLength) {
			buffer.Format("\\\n\t\t\t%s%d.bmp", TempWnd->FilePreName, TempWnd->frameposition + 1);
			mkfile.WriteString(buffer); 

			switch (ConvertDlg.m_CompType) {
			case 0:
				if (ConvertDlg.m_SearchVal == 0) {
					buffer.Format(",\n_binary_%s%d_LZ_bin_start", TempWnd->FilePreName, TempWnd->frameposition +1);
					cfile.WriteString(buffer);
					break;
				} else if (ConvertDlg.m_SearchVal == 1) {
					buffer.Format(",\n_binary_%s%d_LZ_bin_start", TempWnd->FilePreName, TempWnd->frameposition +1);
					cfile.WriteString(buffer);
					break;
				} else {
					buffer.Format(",\n_binary_%s%d_LZ_bin_start", TempWnd->FilePreName, TempWnd->frameposition +1);
					cfile.WriteString(buffer);
					break;
				}
			case 1: {
				buffer.Format(",\n_binary_%s%d_RL_bin_start", TempWnd->FilePreName, TempWnd->frameposition +1);
				cfile.WriteString(buffer);
				break;
			}
			case 2:
				if (ConvertDlg.m_DiffBitSize == 0) {
					buffer.Format(",\n_binary_%s%d_Diff_bin_start", TempWnd->FilePreName, TempWnd->frameposition +1);
					cfile.WriteString(buffer);
					break;
				} else {
					buffer.Format(",\n_binary_%s%d_Diff_bin_start", TempWnd->FilePreName, TempWnd->frameposition +1);
					cfile.WriteString(buffer);
					break;
				}	
			} // end switch
		}
			
		// Place a define for the file's name in the header file for easy reference 
		switch (ConvertDlg.m_CompType) {
		case 0:
			if (ConvertDlg.m_SearchVal == 0) {
				buffer.Format("extern u8 _binary_%s%d_LZ_bin_start[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_LZ_bin_end[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_LZ_bin_size[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 
				break;
			} else if (ConvertDlg.m_SearchVal == 1) {
				buffer.Format("extern u8 _binary_%s%d_LZ_bin_start[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_LZ_bin_end[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_LZ_bin_size[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 
				break;
			} else {
				buffer.Format("extern u8 _binary_%s%d_LZ_bin_start[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_LZ_bin_end[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_LZ_bin_size[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 
				break;
			}
		case 1: {
			buffer.Format("extern u8 _binary_%s%d_RL_bin_start[];\n", TempWnd->FilePreName, TempWnd->frameposition);
			hfile.WriteString(buffer); 

			buffer.Format("extern u8 _binary_%s%d_RL_bin_end[];\n", TempWnd->FilePreName, TempWnd->frameposition);
			hfile.WriteString(buffer); 

			buffer.Format("extern u8 _binary_%s%d_RL_bin_size[];\n", TempWnd->FilePreName, TempWnd->frameposition);
			hfile.WriteString(buffer); 
			break;
		}
		case 2:
			if (ConvertDlg.m_DiffBitSize == 0) {
				buffer.Format("extern u8 _binary_%s%d_Diff_bin_start[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_Diff_bin_end[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_Diff_bin_size[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); ;
				break;
			} else {
				buffer.Format("extern u8 _binary_%s%d_Diff_bin_start[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_Diff_bin_end[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 

				buffer.Format("extern u8 _binary_%s%d_Diff_bin_size[];\n", TempWnd->FilePreName, TempWnd->frameposition);
				hfile.WriteString(buffer); 
				break;
			}	
		} // end switch
	

		if (i == XSERR_HANDLENULL) { 
			// Display message box indicating an error has occured and break from loop
			status.Format("Invalid pointer to frame %d. My bad!", TempWnd->frameposition + 1);
			AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);

			#ifdef _DEBUG
			debugPrint("DIB handle was NULL\n");
			#endif
			break;
		} else if (i == XSERR_OPEN) {
			// Display message box indicating an error has occured and break from loop
			status.Format("Unable to open file for writing:\n%s", str);
			AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);

			#ifdef _DEBUG
			debugPrint("Unable to open the file\n");
			#endif
			break;
		} else if (i == XSERR_LOCK) {
			// Display message box indicating an error has occured and break from loop
			status.Format("Error locking memory in order to write to file:\n%s", str);
			AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);

			#ifdef _DEBUG
			debugPrint("Unable to lock memory\n");
			#endif
			break;
		} else if (i == XSERR_INVALIDFORMAT) {
			// Display message box indicating an error has occured and break from loop
			status.Format("Error in frame %d's format.\n Data may be corrupt.", TempWnd->frameposition + 1);
			AfxMessageBox(status, MB_ICONEXCLAMATION & MB_OK, 0);

			#ifdef _DEBUG
			debugPrint("Invalid DIB format\n");
			#endif
			break;
		} else {
			#ifdef _DEBUG
			debugPrint("No error\n");
			#endif
		}
		
		//  Update the progress bar to reflect our progress
		progress.StepIt();
	
	} // End While

	// Finish the h, c and makefile include created 
	// only need to add palette information if the large resolution is used.
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240) {
		buffer.Format("\n\nPALETTEOBJ\t=\t%s.o", TempWnd->FilePreName);
		mkfile.WriteString(buffer);
	}

	buffer.Format("\n//-------------------- Functions ----------------------\n");
	hfile.WriteString(buffer);

	buffer.Format("void DataInit();\nvoid FrameSwap();\n\n#endif\t//  __BITMAP_H__\n");
	hfile.WriteString(buffer);
	
	buffer.Format("\n};\n\n");
	cfile.WriteString(buffer);

	// Add Data Init function to the C file for initializing the playback
	buffer.Format("//--------------------------------------------------------------\n");
	cfile.WriteString(buffer);

	buffer.Format("//\t\t\tData Init\n//\t- - Initialize Frame data for playback\n");
	cfile.WriteString(buffer);

	buffer.Format("//--------------------------------------------------------------\n");
	cfile.WriteString(buffer);

	buffer.Format("\nvoid DataInit()\n{\n\n");
	cfile.WriteString(buffer);

	// Write BMP Mode dependent routine (if in 240x160 256 color it must load the shared palete)
	if (TempWnd->bmpheader->bmiHeader.biWidth == 240) {
		buffer.Format("\t// Send the shared palette data to VRAM\n");
		cfile.WriteString(buffer);
		buffer.Format("\tDmaCopy(3, _binary_%s1_plb_start, BG_PLTT, 256*2, 16);\n\n", TempWnd->FilePreName);
		cfile.WriteString(buffer);
	}

	buffer.Format("\t// Send the initial frame\n\tFrameSwap();\n}\n\n");
	cfile.WriteString(buffer);

	// Add Frame Swap function to the C file with the correct decompression
	buffer.Format("//--------------------------------------------------------------\n");
	cfile.WriteString(buffer);

	buffer.Format("//\t\t\tFrame Swap\n//\t- Switch out the frame to the correct buffer\n");
	cfile.WriteString(buffer);

	buffer.Format("//--------------------------------------------------------------\n");
	cfile.WriteString(buffer);

	buffer.Format("\nvoid FrameSwap()\n{\n\n");
	cfile.WriteString(buffer);

	buffer.Format("\t// For debugging.. A void pointer to the BMP data area\n");
	cfile.WriteString(buffer);

	buffer.Format("\tu32* bmpdataptr;\n\tbmpdataptr = (void*)BMPAccessTable[Frame];\n\n");
	cfile.WriteString(buffer);

	buffer.Format("\t// Copy the data from ROM to VRAM and uncompress it as you go...\n");
	cfile.WriteString(buffer);

	buffer.Format("\tif	(Frame & 0x1) {\n\t\t");
	cfile.WriteString(buffer);

	switch (ConvertDlg.m_CompType) {
	case 0: {
		buffer.Format("LZ77UnCompVram(bmpdataptr, (void*)BG_BITMAP1_VRAM);\n\t} else {\n\t\t");
		cfile.WriteString(buffer);

		buffer.Format("LZ77UnCompVram(bmpdataptr, (void*)BG_BITMAP0_VRAM);\n\t}\n\n");
		cfile.WriteString(buffer);
		break;
		}
	case 1:{
		buffer.Format("RLUnCompVram(bmpdataptr, (void*)BG_BITMAP1_VRAM);\n\t} else {\n\t\t");
		cfile.WriteString(buffer);

		buffer.Format("RLUnCompVram(bmpdataptr, (void*)BG_BITMAP0_VRAM);\n\t}\n\n");
		cfile.WriteString(buffer);
		break;
		}
	case 2:{
		if (ConvertDlg.m_DiffBitSize == 0) {
			buffer.Format("Diff8bitUnFilterVram(bmpdataptr, (void*)BG_BITMAP1_VRAM);\n\t} else {\n\t\t");
			cfile.WriteString(buffer);

			buffer.Format("Diff8bitUnFilterVram(bmpdataptr, (void*)BG_BITMAP0_VRAM);\n\t}\n\n");
			cfile.WriteString(buffer);
			break;
		} else {
			buffer.Format("Diff16bitUnFilter(bmpdataptr, (void*)BG_BITMAP1_VRAM);\n\t} else {\n\t\t");
			cfile.WriteString(buffer);

			buffer.Format("Diff16bitUnFilter(bmpdataptr, (void*)BG_BITMAP0_VRAM);\n\t}\n\n");
			cfile.WriteString(buffer);
			break;
			}
		}
	} // end switch
	
	buffer.Format("\t// Increment the Frame counter, if it is at the end, reset it for looping");
	cfile.WriteString(buffer);
	
	buffer.Format("\n\tif (Frame < (AVI_LENGTH-1)) {\n\t\tFrame++;\n\t");
	cfile.WriteString(buffer);
	
	buffer.Format("} else {\n\t\tFrame = 0;\n\t}\n}");
	cfile.WriteString(buffer);
	
	// Send text message to status bar indicating that conversion is done..
	if (!i) {

		status.Format("All %d frame(s) saved successfully!", TempWnd->aviheader.dwLength);

		pFrame->m_wndStatusBar.SetPaneText(0, status);
	} 
	else { // or an error has occurred

		pFrame->m_wndStatusBar.SetPaneText(0, status);
	}

	// invalidate rectangle so last frame processed will be drawn
	TempWnd->frameposition--;
	TempWnd->InvalidateRect(TempWnd->rt, TRUE);

	// Store the size of the DIB in the dib rectangle for drawing
	TempWnd->dibrt.right = XSDib_Width(TempWnd->DIBBuffer);
	TempWnd->dibrt.bottom = XSDib_Height(TempWnd->DIBBuffer);

	// Close files as we are done with them
	mkfile.Close();
	mkconv.Close();
	cfile.Close();
	hfile.Close();

	// Now grab the WAV data if it is available! 6/15/00 - JV
	if (TempWnd->NoAudio != 0) {

		// Using code from Don Cross to output the data to a file. May need to change this...
		WaveFile	WaveOut;
		outFilename.Format("%s%s\\%s.wav", TempWnd->FilePath, TempWnd->FilePreName, TempWnd->FilePreName);
	
		// Get size of header information and create the header pointer
		AVIStreamFormatSize(TempWnd->audiostream, 0, &cbFormat);
	
		TempWnd->lpFormat = (LPWAVEFORMATEX)new unsigned char [cbFormat];

		// Get the audio stream's format and store it in the header variable!
		AVIStreamReadFormat(TempWnd->audiostream, 0, TempWnd->lpFormat, &cbFormat);
	
		DDCRET rc = WaveOut.OpenForWrite (outFilename, TempWnd->lpFormat->nSamplesPerSec,
					TempWnd->lpFormat->wBitsPerSample, TempWnd->lpFormat->nChannels);

		if (rc != DDC_SUCCESS) {
			#ifdef _DEBUG
			debugPrint("Error creating output WAV file '%s'!", outFilename);
			#endif
	
			AfxMessageBox("Error creating output WAV file!", MB_ICONERROR & MB_OK, 0);

		} else if (TempWnd->lpFormat->nChannels > MAX_CHANNELS) {
			#ifdef _DEBUG
			debugPrint("Number of channels is too large: %d", TempWnd->lpFormat->nChannels);
			#endif
	
			AfxMessageBox("Number of channels is too large!", MB_ICONERROR & MB_OK, 0);
		
		} else { // Output file opened ok, so let's write the data!

			INT16 data [MAX_CHANNELS];

			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;

			// Get the starting point for the WAV data..
			slCurrent = AVIStreamStart(TempWnd->audiostream);
			long testing = AVIStreamEnd(TempWnd->audiostream);
	
			while (slCurrent < testing) {
				// Read the data from the stream into the buffer
				i = AVIStreamRead(TempWnd->audiostream, slCurrent, TempWnd->lpFormat->nChannels, data, 
						(2*MAX_CHANNELS), &BytesRead, &SamplesRead);

				// Update the pointer to current wave data by number of samples read...
				slCurrent += SamplesRead;

				int c = SamplesRead;

				if (TempWnd->lpFormat->wBitsPerSample == 8) {
					UINT8 data8 [MAX_CHANNELS];
					for (c=0; c < TempWnd->lpFormat->nChannels; ++c) {
						if (data[c] < 0 || data[c] > 255) {
							#ifdef _DEBUG
							debugPrint("Error:  data did not fit in 8 bits!");
							#endif
	
							AfxMessageBox("Error:  data did not fit in 8 bits!", MB_ICONERROR & MB_OK, 0);
							break;
						}
						data8[c] = UINT8 (data[c]);
						rc = WaveOut.WriteData (data8, TempWnd->lpFormat->nChannels);
					}

				} else if (TempWnd->lpFormat->wBitsPerSample == 16) {
					rc = WaveOut.WriteData (data, TempWnd->lpFormat->nChannels);
	
				} else {
					#ifdef _DEBUG
					debugPrint("Don't know how to process %d bits per sample!", 
						TempWnd->lpFormat->wBitsPerSample);
					#endif
	
					AfxMessageBox("Bits per sample are not 8 nor 16. Can't process WAV data!", MB_ICONERROR & MB_OK, 0);
					break;
				}

				if (rc != DDC_SUCCESS) {
					#ifdef _DEBUG
					debugPrint("Error writing data to output file '%s'!", outFilename);
					#endif
	
					AfxMessageBox("Error writing data to output file!", MB_ICONERROR & MB_OK, 0);
					break;
				}
			} // end while
		} // end if

		rc = WaveOut.Close();

		if (rc != DDC_SUCCESS) {
			#ifdef _DEBUG
			debugPrint("Error closing output WAV file '%s'!", outFilename);
			#endif
	
			AfxMessageBox("Error closing output WAV file!", MB_ICONERROR & MB_OK, 0);
		}

		// Get rid of pointers
		delete [] TempWnd->lpFormat;

	} else {
		#ifdef _DEBUG
		debugPrint("Audio Data not present or problem occurred..\n");
		#endif
	} // end WAV data if

	// Print that we are finished
	#ifdef _DEBUG
	debugPrint("We are at the end of the AVI.\n");
	#endif

	// Release the DC for other apps!
	ReleaseDC(TempWnd->m_hWnd, hDC);
}


void CNewAVI2BMPApp::OnAviNext() 
{
	// If no file is open, just exit
	if (NumberOpen <= 0)
		return;

	// Get a pointer to the main window...
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);

	// Get the active frame..
	CChildFrame* TempWnd = (CChildFrame*)pFrame->GetActiveFrame();

	if (TempWnd->frameposition < ((long)TempWnd->aviheader.dwLength)-1) {

		// Move to frame position to the next available frame
		TempWnd->frameposition++;

		// Get the current frame and store it in the DIB buffer
		TempWnd->DIBBuffer = (HDIB)AVIStreamGetFrame(TempWnd->currentframe, 
													 TempWnd->frameposition);

		// Store the size of the DIB in the dib rectangle for drawing
		TempWnd->dibrt.right = XSDib_Width(TempWnd->DIBBuffer);
		TempWnd->dibrt.bottom = XSDib_Height(TempWnd->DIBBuffer);

		// Get the bitmap header information and store it for next use.
		TempWnd->bmpheader = (LPBITMAPINFO)TempWnd->DIBBuffer;

		// invalidate rectangle so last frame processed will be drawn
		TempWnd->InvalidateRect(TempWnd->rt, TRUE);
	}
	else {
		// print out that we reached the end of the AVI
		#ifdef _DEBUG
		debugPrint("We are at the end of the AVI.\n");
		#endif
	} // endif

}

void CNewAVI2BMPApp::OnAviPrevious() 
{
	// If no file is open, just exit
	if (NumberOpen <= 0)
		return;
	// Get a pointer to the main window...
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);

	// Get the active frame..
	CChildFrame* TempWnd = (CChildFrame*)pFrame->GetActiveFrame();

	if (TempWnd->frameposition > 0) {

		// Move to frame position to the next available frame
		TempWnd->frameposition--;

		// Get the current frame and store it in the DIB buffer
		TempWnd->DIBBuffer = (HDIB)AVIStreamGetFrame(TempWnd->currentframe, 
													 TempWnd->frameposition);

		// Store the size of the DIB in the dib rectangle for drawing
		TempWnd->dibrt.right = XSDib_Width(TempWnd->DIBBuffer);
		TempWnd->dibrt.bottom = XSDib_Height(TempWnd->DIBBuffer);

		// Get the bitmap header information and store it for next use.
		TempWnd->bmpheader = (LPBITMAPINFO)TempWnd->DIBBuffer;

		// invalidate rectangle so last frame processed will be drawn
		TempWnd->InvalidateRect(TempWnd->rt, TRUE);
	}
	else {
		#ifdef _DEBUG
		debugPrint("We are at the beginning of the AVI.\n");
		#endif
	}// endif	

}
/////////////////////////////////////////////////////////////////////////////
// convertDialog dialog


convertDialog::convertDialog(CWnd* pParent /*=NULL*/)
	: CDialog(convertDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(convertDialog)
	m_SearchVal = -1;
	m_CompType = -1;
	m_DiffBitSize = -1;
	//}}AFX_DATA_INIT
}


void convertDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(convertDialog)
	DDX_Radio(pDX, IDC_S2, m_SearchVal);
	DDX_Radio(pDX, IDC_LZ77, m_CompType);
	DDX_Radio(pDX, IDC_BSZ8, m_DiffBitSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(convertDialog, CDialog)
	//{{AFX_MSG_MAP(convertDialog)
	ON_BN_CLICKED(IDC_DIFF, OnDiff)
	ON_BN_CLICKED(IDC_LZ77, OnLz77)
	ON_BN_CLICKED(IDC_RLE, OnRle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// convertDialog message handlers

void convertDialog::OnDiff() 
{
	// TODO: Add your control notification handler code here
	ENABLE_DLG_WINDOW(IDC_BSZ8);
	ENABLE_DLG_WINDOW(IDC_BSZ16);
	DISABLE_DLG_WINDOW(IDC_S2);
	DISABLE_DLG_WINDOW(IDC_S4);
	DISABLE_DLG_WINDOW(IDC_S8);
	UpdateData(TRUE);
	m_SearchVal = -1;
	UpdateData(FALSE);
}

void convertDialog::OnLz77() 
{
	// TODO: Add your control notification handler code here
	ENABLE_DLG_WINDOW(IDC_S2);
	ENABLE_DLG_WINDOW(IDC_S4);
	ENABLE_DLG_WINDOW(IDC_S8);
	DISABLE_DLG_WINDOW(IDC_BSZ8);
	DISABLE_DLG_WINDOW(IDC_BSZ16);
	UpdateData(TRUE);
	m_DiffBitSize = -1;
	UpdateData(FALSE);
}

void convertDialog::OnRle() 
{
	// TODO: Add your control notification handler code here
	DISABLE_DLG_WINDOW(IDC_S2);
	DISABLE_DLG_WINDOW(IDC_S4);
	DISABLE_DLG_WINDOW(IDC_S8);
	DISABLE_DLG_WINDOW(IDC_BSZ8);
	DISABLE_DLG_WINDOW(IDC_BSZ16);	
	UpdateData(TRUE);
	m_SearchVal = -1;
	m_DiffBitSize = -1;
	UpdateData(FALSE);
}

void convertDialog::OnOK() 
{
	// TODO: Add extra validation here
	// Update the data first!
	UpdateData(TRUE);

	if (m_CompType == -1) {
		AfxMessageBox("Please choose a compression type before continuing, or click the cancel button.", 
					  MB_ICONEXCLAMATION & MB_OK, 0);
	} else if ((m_CompType == 0) && (m_SearchVal == -1)){
		AfxMessageBox("Please choose a search size before continuing, or click the cancel button.", 
					  MB_ICONEXCLAMATION & MB_OK, 0);
	} else if ((m_CompType == 2) && (m_DiffBitSize == -1)) {
		AfxMessageBox("Please choose a bitsize before continuing, or click the cancel button.", 
					  MB_ICONEXCLAMATION & MB_OK, 0);
	} else {
		CDialog::OnOK();
	}
}
