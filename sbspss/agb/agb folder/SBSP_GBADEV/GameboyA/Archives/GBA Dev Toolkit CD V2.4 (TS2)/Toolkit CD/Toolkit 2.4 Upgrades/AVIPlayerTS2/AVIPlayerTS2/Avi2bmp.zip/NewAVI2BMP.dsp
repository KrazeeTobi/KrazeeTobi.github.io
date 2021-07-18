# Microsoft Developer Studio Project File - Name="NewAVI2BMP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NewAVI2BMP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NewAVI2BMP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NewAVI2BMP.mak" CFG="NewAVI2BMP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NewAVI2BMP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NewAVI2BMP - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/James/NewAVI2BMP", JWCAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NewAVI2BMP - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\XSSource" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/AVI2BMP.exe"

!ELSEIF  "$(CFG)" == "NewAVI2BMP - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\XSSource" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vfw32.lib kernel32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/AVI2BMP.exe" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /incremental:no /nodefaultlib

!ENDIF 

# Begin Target

# Name "NewAVI2BMP - Win32 Release"
# Name "NewAVI2BMP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "XS_Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XSSource\XSBgCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSCaption.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSDibApi.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSError.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSNodeData.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSObject.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSPalApi.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSPalette.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSRect.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSSubWndCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSTreeNode.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\Ddc.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NewAVI2BMP.cpp
# End Source File
# Begin Source File

SOURCE=.\NewAVI2BMP.rc
# End Source File
# Begin Source File

SOURCE=.\Riff.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "XS_Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XSSource\XSBgCtrl.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSBitmap.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSCaption.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSCheckType.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSDibApi.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSError.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSMain.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSMisc.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSNodeData.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSNotify.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSObject.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSPalApi.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSPalette.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSRect.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSSubWndCtrl.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\XSSource\XSTreeNode.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\Ddc.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NewAVI2BMP.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Riff.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\NewAVI2BMP.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewAVI2BMP.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
