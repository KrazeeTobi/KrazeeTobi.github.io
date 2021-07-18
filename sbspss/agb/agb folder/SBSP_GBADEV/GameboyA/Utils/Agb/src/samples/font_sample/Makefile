.DATFILES  =   Ld937728.dat
.SFILES    =   crt0.s
.CFILES    =   main.c data.c
.OFILES    =   $(.SFILES:.s=.o) $(.CFILES:.c=.o) $(.DATFILES:.dat=.o)
ASFLAGS    =          -I../../../include -mthumb-interwork
CFLAGS     =   -g -O2 -I../../../include -mthumb-interwork -nostdlib #-DNDEBUG
LDFLAGS    +=  -Map $(MAPFILE) -nostartfiles \
               -Ttext 0x08000000 -Tbss 0x02000000 \
               -L../../../lib -lagbsyscall -lisagbprn \
               -L$(CYGNUSDIR)/thumbelf-981216/H-i586-cygwin32/lib/gcc-lib/thumb-elf/2.9-armelf-981216/ -L$(CYGNUSDIR)/thumbelf-981216/H-i586-cygwin32/thumb-elf/lib/
DEPENDFILE =   Makedepend
MAPFILE    =   font_sample.map
TARGET_ELF =   font_sample.elf
TARGET_BIN =   font_sample.bin

.SUFFIXES: .dat $(SUFFIXES)

.dat.o:
	objcopy -v -I binary -O elf32-little $< $@

$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

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
