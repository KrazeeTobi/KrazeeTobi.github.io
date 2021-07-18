AGB_DIR		= c:/agb
AGB_INC_DIR 	= $(AGB_DIR)/include
CYGNUS_DIR  	= c:/progra~1/cygnus/thumbelf-000512

DEPENDFILE 	= deps
MAPFILE    	= project.map
TARGET_ELF 	= project.elf
TARGET_BIN 	= project.bin

.SFILES    	= crt0.s taskutil.s
.CFILES    	= main.c oam.c util.c interrupt.c task.c fontprn/fontprn.c
.OFILES    	= $(.SFILES:.s=.o) $(.CFILES:.c=.o)

ASFLAGS    	= -I$(AGB_INC_DIR) -mthumb-interwork

OPT_FLAGS	= -O1
DEBUG_FLAGS	= -g -Wall -W
#DEBUG_FLAGS	+= -v -Wno-format

CFLAGS		= $(DEBUG_FLAGS) $(OPT_FLAGS) -I$(AGB_INC_DIR) -I. -mthumb-interwork -nostdlib

LDFLAGS    	+= -Map $(MAPFILE) \
               	-Ttext 0x08000000 -Tbss 0x03000000 -L$(AGB_DIR)/lib -lagbsyscall \
	       	-L$(CYGNUS_DIR)/H-i686-cygwin32/lib/gcc-lib/thumb-elf/2.9-arm-000512 -lgcc \
	       	-L$(CYGNUS_DIR)/H-i686-cygwin32/thumb-elf/lib -lc -lg -lm -lgcc

$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@
	agbload -n $(TARGET_BIN)

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	ld -o $@ $(.OFILES) $(LDFLAGS)

.PHONY: all clean run depend relink rmbin libdepend

all:    clean default

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN)

run:
	agbload -n $(TARGET_BIN)

relink: rmbin $(TARGET_BIN)

rmbin:
	-rm $(TARGET_ELF) $(TARGET_BIN)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE):
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

crt0.o:	crt0.s  c:\agb\include\AgbDefine.s c:\agb\include\AgbMacro.s c:\agb\include\AgbMemoryMap.s rom_header.s
taskutil.o: taskutil.s  c:\agb\include\AgbDefine.s c:\agb\include\AgbMacro.s c:\agb\include\AgbMemoryMap.s

include $(DEPENDFILE)
