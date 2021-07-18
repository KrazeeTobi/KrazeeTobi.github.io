# Microsoft Developer Studio Project File - Name="prevcl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** Do not edit. **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=prevcl - Win32 Debug
!MESSAGE This is not a valid makefile. Use NMAKE to build this project.
!MESSAGE Execute using [Export Makefile] command.
!MESSAGE 
!MESSAGE NMAKE /f "prevcl.mak".
!MESSAGE 
!MESSAGE Structure can be specified when executing NMAKE.
!MESSAGE Define macro setting on command line. Example:
!MESSAGE 
!MESSAGE NMAKE /f "prevcl.mak" CFG="prevcl - Win32 Debug"
!MESSAGE 
!MESSAGE Build mode you can select.:
!MESSAGE 
!MESSAGE "prevcl - Win32 Release" ("Win32 (x86) Console Application" use)
!MESSAGE "prevcl - Win32 Debug" ("Win32 (x86) Console Application" use)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "prevcl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "prevcl___Win32_Release"
# PROP BASE Intermediate_Dir "prevcl___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp2 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libmagbx.lib /nologo /subsystem:console /machine:I386 /out:"../../../../../bin/prev/prevcl.exe"

!ELSEIF  "$(CFG)" == "prevcl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "prevcl - Win32 Release"
# Name "prevcl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\agbanimnode.cpp
# End Source File
# Begin Source File

SOURCE=.\agbnode.cpp
# End Source File
# Begin Source File

SOURCE=.\c_access.cpp
# End Source File
# Begin Source File

SOURCE=.\flipbook.cpp
# End Source File
# Begin Source File

SOURCE=.\lex.yy.c
# End Source File
# Begin Source File

SOURCE=.\move_animation.cpp
# End Source File
# Begin Source File

SOURCE=.\multi_switch.cpp
# End Source File
# Begin Source File

SOURCE=.\ndanimation.cpp
# End Source File
# Begin Source File

SOURCE=.\ndbackground.cpp
# End Source File
# Begin Source File

SOURCE=.\ndcharacter.cpp
# End Source File
# Begin Source File

SOURCE=.\ndimage.cpp
# End Source File
# Begin Source File

SOURCE=.\ndmapcharacter.cpp
# End Source File
# Begin Source File

SOURCE=.\ndmapimage.cpp
# End Source File
# Begin Source File

SOURCE=.\ndobject.cpp
# End Source File
# Begin Source File

SOURCE=.\ndpalette.cpp
# End Source File
# Begin Source File

SOURCE=.\nodeinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\nodemagic.cpp
# End Source File
# Begin Source File

SOURCE=.\nodemanager.cpp
# End Source File
# Begin Source File

SOURCE=.\offset_animation.cpp
# End Source File
# Begin Source File

SOURCE=.\palette_animation.cpp
# End Source File
# Begin Source File

SOURCE=.\prev_util.cpp
# End Source File
# Begin Source File

SOURCE=.\rotate_animation.cpp
# End Source File
# Begin Source File

SOURCE=.\scale_animation.cpp
# End Source File
# Begin Source File

SOURCE=.\screenheader.cpp
# End Source File
# Begin Source File

SOURCE=.\switch.cpp
# End Source File
# Begin Source File

SOURCE=.\token_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\agbanimnode.h
# End Source File
# Begin Source File

SOURCE=.\agbnode.h
# End Source File
# Begin Source File

SOURCE=.\c_access.h
# End Source File
# Begin Source File

SOURCE=.\ex_reference.h
# End Source File
# Begin Source File

SOURCE=.\flipbook.h
# End Source File
# Begin Source File

SOURCE=.\move_animation.h
# End Source File
# Begin Source File

SOURCE=.\multi_switch.h
# End Source File
# Begin Source File

SOURCE=.\ndanimation.h
# End Source File
# Begin Source File

SOURCE=.\ndbackground.h
# End Source File
# Begin Source File

SOURCE=.\ndcharacter.h
# End Source File
# Begin Source File

SOURCE=.\ndimage.h
# End Source File
# Begin Source File

SOURCE=.\ndmapcharacter.h
# End Source File
# Begin Source File

SOURCE=.\ndmapimage.h
# End Source File
# Begin Source File

SOURCE=.\ndobject.h
# End Source File
# Begin Source File

SOURCE=.\ndpalette.h
# End Source File
# Begin Source File

SOURCE=.\nodeinfo.h
# End Source File
# Begin Source File

SOURCE=.\nodemagic.h
# End Source File
# Begin Source File

SOURCE=.\nodemanager.h
# End Source File
# Begin Source File

SOURCE=.\offset_animation.h
# End Source File
# Begin Source File

SOURCE=.\palette_animation.h
# End Source File
# Begin Source File

SOURCE=.\prev_util.h
# End Source File
# Begin Source File

SOURCE=.\rotate_animation.h
# End Source File
# Begin Source File

SOURCE=.\scale_animation.h
# End Source File
# Begin Source File

SOURCE=.\screenheader.h
# End Source File
# Begin Source File

SOURCE=.\switch.h
# End Source File
# Begin Source File

SOURCE=.\token_list.h
# End Source File
# Begin Source File

SOURCE=.\token_type.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
