# Makefile for PCM_sound project

AGBDIR     =   c:/agb

# Declare wave data object file here
WAVEDATA   =   pikachu.o

.SFILES    =   crt0.s
.CFILES    =   main.c data.c sound.c
.OFILES    =   $(.SFILES:.s=.o) $(.CFILES:.c=.o) $(WAVEDATA)
ASFLAGS    =          -I$(AGBDIR)/include -mthumb-interwork
CFLAGS     =   -g -O2 -I$(AGBDIR)/include -mthumb-interwork -nostdlib #-DNDEBUG
LDFLAGS    +=  -Map $(MAPFILE) -nostartfiles \
               -Ttext 0x08000000 -Tbss 0x02000000 \
               -L$(AGBDIR)/lib -lagbsyscall -lisagbprn \
               -L$(CYGNUSDIR)/thumbelf-981216/H-i586-cygwin32/lib/gcc-lib/thumb-elf/2.9-armelf-981216/ \
               -L$(CYGNUSDIR)/thumbelf-981216/H-i586-cygwin32/thumb-elf/lib/
DEPENDFILE =   Makedepend
MAPFILE    =   simple.map
TARGET_ELF =   simple.elf
TARGET_BIN =   simple.bin

$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

$(WAVEDATA): $(WAVEDATA:.o=.bin)
	objcopy -v -I binary -O elf32-little $< $@

.PHONY: all clean depend

all:    clean depend $(TARGET_BIN)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ELF) $(TARGET_BIN)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE):
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include Gasdepend
include $(DEPENDFILE)
