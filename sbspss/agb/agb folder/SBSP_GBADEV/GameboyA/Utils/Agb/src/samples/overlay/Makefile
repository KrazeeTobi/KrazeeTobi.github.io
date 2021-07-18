.SFILES     =   crt0.s
.CFILES     =   main.c sub.c title.c objmove.c bgmove.c data.c
.OFILES     =   $(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS     =          -I../../../include -mthumb-interwork
CFLAGS      =   -g -O2 -I../../../include -mthumb-interwork \
                -nostdlib -fno-common #-DNDEBUG
LDFLAGS     +=  -Map $(MAPFILE) -nostartfiles \
                -T $(LDSCRIPT) -Ttext 0x08000000 \
                -L../../../lib -lagbsyscall -lisagbprn
LDSCRIPT    =   linkerscript.x
DEPENDFILE  =   Makedepend
MAPFILE     =   overlay.map
TARGET_ELF  =   overlay.elf
TARGET_BIN  =   overlay.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(LDSCRIPT) $(DEPENDFILE)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

.PHONY: all clean depend

all:    clean depend $(TARGET_BIN)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include Gasdepend
include $(DEPENDFILE)
