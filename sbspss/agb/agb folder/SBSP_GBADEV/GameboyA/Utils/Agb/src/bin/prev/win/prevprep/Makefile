#
# 90/05/26 17:28:44 vern Exp $ (LBL)
#
# the first time around use "nmake f_flex"
#
#  This makefile is specific for Microsoft's Visual C 2.0, & nmake
#
#         - Stan Adermann <stana@leonardo.lmt.com>
#


CFLAGS = -nologo -W2 -F 8000 -Ox -DUSG -GX
LDFLAGS = /nologo /STACK:8000
FLEX_FLAGS = 

FLEX = ..\flex
CC = cl
MAKE = nmake /nologo

OBJS = \
	lex.yy.obj define.obj token_list.obj file_stack.obj if_control.obj

C_SOURCES = \
	lex.yy.c define.cpp token_list.cpp file_stack.cpp if_control.obj

TARGET = ..\..\..\..\..\bin\prev\prevprep.exe

all : $(TARGET)

$(TARGET) : $(OBJS)
        link $(LDFLAGS) $(OBJS) -out:$*.exe

.cpp.obj:
        $(CC) -c $(CFLAGS) $*.cpp

.c.obj:
        $(CC) -c $(CFLAGS) $*.c

lex.yy.c : pp.l
        $(FLEX) $(FLEX_FLAGS) pp.l

lex.yy.obj : pp.l global.h token_list.h file_stack.h
define.obj : define.cpp global.h token_list.h token_type.h
token_list.obj : token_list.cpp token_list.h global.h token_type.h
file_stack.obj : file_stack.cpp file_stack.h
if_control.obj : if_control.cpp if_control.h

clean :
        del *.obj
        del *.map
