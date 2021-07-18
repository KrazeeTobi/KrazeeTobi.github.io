.SFILES    =   crt0.s MultiSioAsm.s
.CFILES    =   main.c data.c MultiSio.c
.OFILES    =   $(.SFILES:.s=.o) $(.CFILES:.c=.o) $(.PROJFILES:.proj=.o)
.PROJFILES =   demo.proj
ASFLAGS    =          -I/agb/include -mthumb-interwork
CFLAGS     =   -g -O2 -I/agb/include -mthumb-interwork \
               -nostdlib #-DNDEBUG
LDFLAGS    +=  -Map $(MAPFILE) -nostartfiles \
			   -L. -lMusyX_thumb \
               -Ttext 0x08000000 -Tbss 0x03000000 \
               -L/agb/lib -lagbsyscall -lisagbprn
DEPENDFILE =   Makedepend
MAPFILE    =   multi_sio.map
TARGET_ELF =   multi_sio.elf
TARGET_BIN =   multi_sio.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

.PHONY: all clean depend

.SUFFIXES:	.proj $(SUFFIXES)

.proj.o:
	objcopy -v -I binary -O elf32-little $< $@

all:    clean depend $(TARGET_BIN)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include Gasdepend
include $(DEPENDFILE)
