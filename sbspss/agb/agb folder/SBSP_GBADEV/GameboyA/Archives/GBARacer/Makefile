.SFILES    =   crt0.s
.CFILES    =   render.c main.c data.c data_math_table.c data_tile_proc.c
.OFILES    =   $(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS    =          -I$(AGBDIR)/include -mthumb-interwork
CFLAGS     =   -g -O2 -I$(AGBDIR)/include -mthumb-interwork -nostdlib #-DNDEBUG
LDFLAGS    +=  -Map $(MAPFILE) -nostartfiles \
               -Ttext 0x08000000 -Tbss 0x03000000 \
               -L$(AGBDIR)/lib -lagbsyscall -lisagbprn \
               -L$(CYGNUSDIR)/thumbelf-000512/H-i\686-cygwin32/lib/gcc-lib/thumb-elf/2.9-arm-000512/ -L$(CYGNUSDIR)/thumbelf-000512/H-i686-cygwin32/thumb-elf/lib/
DEPENDFILE =   Makedepend
MAPFILE    =   simple.map
TARGET_ELF =   simple.elf
TARGET_BIN =   simple.bin


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
