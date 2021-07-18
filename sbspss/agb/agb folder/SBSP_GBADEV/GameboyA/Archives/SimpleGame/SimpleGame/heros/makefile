AGB_INC_DIR 	= $(AGBDIR)/include
CYGNUS_DIR  	= c:/progra~1/cygnus/thumbelf-000512

HERO_ART_DIR	= art
HERO_ART_LIB	= heroart

DEPENDFILE 	= deps
MAPFILE    	= heros.map
TARGET_ELF 	= heros.elf
TARGET_BIN 	= heros.bin

.SFILES    	= crt0.s
.CFILES    	= main.c oam.c util.c interrupt.c heros.c battle.c units.c cursor.c
.OFILES    	= $(.SFILES:.s=.o) $(.CFILES:.c=.o)

ASFLAGS    	= -I$(AGB_INC_DIR) -mthumb-interwork

OPT_FLAGS	= -O2
DEBUG_FLAGS	= -g -Wall -W
#DEBUG_FLAGS	+= -v -Wno-format

CFLAGS		= $(DEBUG_FLAGS) $(OPT_FLAGS) -I$(AGB_INC_DIR) -I. -mthumb-interwork -nostdlib

LDFLAGS    	+= -Map $(MAPFILE) -Ttext 0x08000000 -Tbss 0x03000000				\
               	-L$(AGBDIR)/lib -lagbsyscall -L$(HERO_ART_DIR) -l$(HERO_ART_LIB)		\
	       	-L$(CYGNUS_DIR)/H-i686-cygwin32/lib/gcc-lib/thumb-elf/2.9-arm-000512 -lgcc 	\
	       	-L$(CYGNUS_DIR)/H-i686-cygwin32/thumb-elf/lib -lc -lg -lm -lgcc


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	@echo Linking project...
	ld -o $@ $(.OFILES) $(LDFLAGS)

.PHONY: all clean run depend relink rmbin

all:    clean default

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN)

run:	$(TARGET_BIN)
	@echo Downloading project...
	agbload -n $(TARGET_BIN)

relink: rmbin $(TARGET_BIN)

rmbin:
	-rm $(TARGET_ELF) $(TARGET_BIN)

depend:
	@echo Updating Dependencies...
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE):
	@echo Creating Dependencies...
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

crt0.o:	crt0.s $(AGBDIR)/include/AgbDefine.s $(AGBDIR)/include/AgbMacro.s $(AGBDIR)/include/AgbMemoryMap.s rom_header.s
include $(DEPENDFILE)

