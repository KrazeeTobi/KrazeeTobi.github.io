; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=convertDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "newavi2bmp.h"
LastPage=0

ClassCount=7
Class1=CChildFrame
Class2=CChildView
Class3=CMainFrame
Class4=CNewAVI2BMPApp
Class5=CAboutDlg
Class6=FileInfo

ResourceCount=5
Resource1=IDR_NEWAVITYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_FILEINFO
Class7=convertDialog
Resource5=IDD_MYCONVERT

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CNewAVI2BMPApp]
Type=0
BaseClass=CWinApp
HeaderFile=NewAVI2BMP.h
ImplementationFile=NewAVI2BMP.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=NewAVI2BMP.cpp
ImplementationFile=NewAVI2BMP.cpp
LastObject=CAboutDlg

[CLS:FileInfo]
Type=0
BaseClass=CDialog
HeaderFile=NewAVI2BMP.h
ImplementationFile=NewAVI2BMP.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_STATIC,static,1342308993
Control4=IDC_STATIC,static,1342308865

[DLG:IDD_FILEINFO]
Type=1
Class=FileInfo
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1342179458
Control9=IDC_EDIT2,edit,1342179458
Control10=IDC_EDIT3,edit,1342179458
Control11=IDC_EDIT4,edit,1342179458
Control12=IDC_EDIT5,edit,1342179458
Control13=IDC_EDIT7,edit,1342179458

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_NEWAVITYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_AVI_DETAILS
Command9=ID_AVI_CONVERT
Command10=ID_AVI_NEXT
Command11=ID_AVI_PREVIOUS
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_CASCADE
Command15=ID_WINDOW_TILE_HORZ
Command16=ID_WINDOW_ARRANGE
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_AVI_DETAILS
Command3=ID_AVI_NEXT
Command4=ID_FILE_OPEN
Command5=ID_AVI_PREVIOUS
Command6=ID_AVI_CONVERT
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[CLS:convertDialog]
Type=0
HeaderFile=newavi2bmp.h
ImplementationFile=newavi2bmp.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_MYCONVERT]
Type=1
Class=convertDialog
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LZ77,button,1342311433
Control4=IDC_RLE,button,1342180361
Control5=IDC_DIFF,button,1342180361
Control6=IDC_S2,button,1476529161
Control7=IDC_S4,button,1476398089
Control8=IDC_S8,button,1476398089
Control9=IDC_BSZ8,button,1476529161
Control10=IDC_BSZ16,button,1476398089

