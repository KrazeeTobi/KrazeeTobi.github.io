# Microsoft Developer Studio Project File - Name="libsrc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** Please do not edit **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libsrc - Win32 Debug
!MESSAGE This is not a valid make file.  in order to build this project, please use NMAKE.
!MESSAGE [Export Make File] Please carry out by using Command
!MESSAGE 
!MESSAGE NMAKE /f "libsrc.mak".
!MESSAGE 
!MESSAGE You can specify structure when carrying out NMAKE
!MESSAGE Define the setting of macro on Command Line.  Example:
!MESSAGE 
!MESSAGE NMAKE /f "libsrc.mak" CFG="libsrc - Win32 Debug"
!MESSAGE 
!MESSAGE selectable Build Mode:
!MESSAGE 
!MESSAGE "libsrc - Win32 Release" (for "Win32 (x86) Static Library")
!MESSAGE "libsrc - Win32 Debug" (for "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libsrc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\libmagbx.lib"

!ELSEIF  "$(CFG)" == "libsrc - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp2 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\libmagbx.lib"

!ENDIF 

# Begin Target

# Name "libsrc - Win32 Release"
# Name "libsrc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\angle.cpp
# End Source File
# Begin Source File

SOURCE=.\buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\char16set.cpp
# End Source File
# Begin Source File

SOURCE=.\char256set.cpp
# End Source File
# Begin Source File

SOURCE=.\character.cpp
# End Source File
# Begin Source File

SOURCE=.\character16.cpp
# End Source File
# Begin Source File

SOURCE=.\charset.cpp
# End Source File
# Begin Source File

SOURCE=.\color.cpp
# End Source File
# Begin Source File

SOURCE=.\filename.cpp
# End Source File
# Begin Source File

SOURCE=.\hpicture.cpp
# End Source File
# Begin Source File

SOURCE=.\image.cpp
# End Source File
# Begin Source File

SOURCE=.\map.cpp
# End Source File
# Begin Source File

SOURCE=.\map16.cpp
# End Source File
# Begin Source File

SOURCE=.\map256.cpp
# End Source File
# Begin Source File

SOURCE=.\mapsrimage.cpp
# End Source File
# Begin Source File

SOURCE=.\maptextimage.cpp
# End Source File
# Begin Source File

SOURCE=.\maptextunit.cpp
# End Source File
# Begin Source File

SOURCE=.\palette.cpp
# End Source File
# Begin Source File

SOURCE=.\pathname.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\agbtypes.h
# End Source File
# Begin Source File

SOURCE=..\include\angle.h
# End Source File
# Begin Source File

SOURCE=..\include\bmpstruct.h
# End Source File
# Begin Source File

SOURCE=..\include\buffer.h
# End Source File
# Begin Source File

SOURCE=..\include\char16set.h
# End Source File
# Begin Source File

SOURCE=..\include\char256set.h
# End Source File
# Begin Source File

SOURCE=..\include\character.h
# End Source File
# Begin Source File

SOURCE=..\include\character16.h
# End Source File
# Begin Source File

SOURCE=..\include\character256.h
# End Source File
# Begin Source File

SOURCE=..\include\charset.h
# End Source File
# Begin Source File

SOURCE=..\include\color.h
# End Source File
# Begin Source File

SOURCE=..\include\filename.h
# End Source File
# Begin Source File

SOURCE=..\include\hpicture.h
# End Source File
# Begin Source File

SOURCE=..\include\image.h
# End Source File
# Begin Source File

SOURCE=..\include\map.h
# End Source File
# Begin Source File

SOURCE=..\include\map16.h
# End Source File
# Begin Source File

SOURCE=..\include\map256.h
# End Source File
# Begin Source File

SOURCE=..\include\mapsrimage.h
# End Source File
# Begin Source File

SOURCE=..\include\maptextimage.h
# End Source File
# Begin Source File

SOURCE=..\include\maptextunit.h
# End Source File
# Begin Source File

SOURCE=..\include\palette.h
# End Source File
# Begin Source File

SOURCE=..\include\pathname.h
# End Source File
# Begin Source File

SOURCE=..\include\picture.h
# End Source File
# Begin Source File

SOURCE=..\include\util.h
# End Source File
# End Group
# End Target
# End Project
