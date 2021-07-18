CFG=prevcl - Win32 Release

CPP=cl.exe
RSC=rc.exe
FLEX=..\flex.exe
FLEX_FLAGS=

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "..\..\..\..\..\bin\prev\prevcl.exe"


CLEAN :
	-@erase "$(INTDIR)\move_animation.obj"
	-@erase "$(INTDIR)\multi_switch.obj"
	-@erase "$(INTDIR)\ndanimation.obj"
	-@erase "$(INTDIR)\agbanimnode.obj"
	-@erase "$(INTDIR)\agbnode.obj"
	-@erase "$(INTDIR)\c_access.obj"
	-@erase "$(INTDIR)\flipbook.obj"
	-@erase "$(INTDIR)\ndbackground.obj"
	-@erase "$(INTDIR)\ndcharacter.obj"
	-@erase "$(INTDIR)\ndimage.obj"
	-@erase "$(INTDIR)\ndmapcharacter.obj"
	-@erase "$(INTDIR)\ndmapimage.obj"
	-@erase "$(INTDIR)\ndobject.obj"
	-@erase "$(INTDIR)\ndpalette.obj"
	-@erase "$(INTDIR)\nodeinfo.obj"
	-@erase "$(INTDIR)\nodemagic.obj"
	-@erase "$(INTDIR)\nodemanager.obj"
	-@erase "$(INTDIR)\offset_animation.obj"
	-@erase "$(INTDIR)\palette_animation.obj"
	-@erase "$(INTDIR)\prev_util.obj"
	-@erase "$(INTDIR)\rotate_animation.obj"
	-@erase "$(INTDIR)\scale_animation.obj"
	-@erase "$(INTDIR)\screenheader.obj"
	-@erase "$(INTDIR)\switch.obj"
	-@erase "$(INTDIR)\token_list.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\prevcl.exe"
	-@erase "$(INTDIR)\lex.yy.obj"
	-@erase "lex.yy.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp2 /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\prevcl.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c /I ..\..\..\include 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\prevcl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\..\lib\libmagbx.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\prevcl.pdb" /machine:I386 /out:"../../../../../bin/prev/prevcl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\agbanimnode.obj" \
	"$(INTDIR)\agbnode.obj" \
	"$(INTDIR)\c_access.obj" \
	"$(INTDIR)\flipbook.obj" \
	"$(INTDIR)\ndbackground.obj" \
	"$(INTDIR)\ndcharacter.obj" \
	"$(INTDIR)\ndimage.obj" \
	"$(INTDIR)\ndmapcharacter.obj" \
	"$(INTDIR)\ndmapimage.obj" \
	"$(INTDIR)\ndobject.obj" \
	"$(INTDIR)\ndpalette.obj" \
	"$(INTDIR)\nodeinfo.obj" \
	"$(INTDIR)\nodemagic.obj" \
	"$(INTDIR)\nodemanager.obj" \
	"$(INTDIR)\offset_animation.obj" \
	"$(INTDIR)\palette_animation.obj" \
	"$(INTDIR)\prev_util.obj" \
	"$(INTDIR)\rotate_animation.obj" \
	"$(INTDIR)\scale_animation.obj" \
	"$(INTDIR)\screenheader.obj" \
	"$(INTDIR)\switch.obj" \
	"$(INTDIR)\token_list.obj" \
	"$(INTDIR)\lex.yy.obj" \
	"$(INTDIR)\move_animation.obj" \
	"$(INTDIR)\multi_switch.obj" \
	"$(INTDIR)\ndanimation.obj"

"../../../../../bin/prev/prevcl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

lex.yy.c : prevcl.l
        $(FLEX) $(FLEX_FLAGS) prevcl.l

!INCLUDE "prevcl.dep"


"$(INTDIR)\lex.yy.obj" : prevcl.l token_type.h c_access.h

SOURCE=.\agbanimnode.cpp

"$(INTDIR)\agbanimnode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\agbnode.cpp

"$(INTDIR)\agbnode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\c_access.cpp

"$(INTDIR)\c_access.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\flipbook.cpp

"$(INTDIR)\flipbook.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ndcharacter.cpp

"$(INTDIR)\ndcharacter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ndimage.cpp

"$(INTDIR)\ndimage.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ndobject.cpp

"$(INTDIR)\ndobject.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ndpalette.cpp

"$(INTDIR)\ndpalette.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\nodeinfo.cpp

"$(INTDIR)\nodeinfo.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\nodemagic.cpp

"$(INTDIR)\nodemagic.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\nodemanager.cpp

"$(INTDIR)\nodemanager.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\offset_animation.cpp

"$(INTDIR)\offset_animation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\move_animation.cpp

"$(INTDIR)\move_animation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\multi_switch.cpp

"$(INTDIR)\multi_switch.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ndanimation.cpp

"$(INTDIR)\ndanimation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\palette_animation.cpp

"$(INTDIR)\palette_animation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\prev_util.cpp

"$(INTDIR)\prev_util.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\rotate_animation.cpp

"$(INTDIR)\rotate_animation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\scale_animation.cpp

"$(INTDIR)\scale_animation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\screenheader.cpp

"$(INTDIR)\screenheader.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\switch.cpp

"$(INTDIR)\switch.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\token_list.cpp

"$(INTDIR)\token_list.obj" : $(SOURCE) "$(INTDIR)"

