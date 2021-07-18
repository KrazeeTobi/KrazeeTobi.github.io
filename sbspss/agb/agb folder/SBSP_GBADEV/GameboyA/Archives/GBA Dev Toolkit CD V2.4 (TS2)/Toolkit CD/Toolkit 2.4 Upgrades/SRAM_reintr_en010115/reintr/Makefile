.SFILES     =   crt0.s
.CFILES     =   main.c data.c
.OFILES     =   $(.SFILES:.s=.o) $(.CFILES:.c=.o)

AGBINC	   =	$(AGBDIR)/include
AGBLIB	   =	$(AGBDIR)/lib

ASFLAGS     =          -I$(AGBINC) -mthumb-interwork
CFLAGS      =   -g -O2 -I$(AGBINC) -mthumb-interwork \
                -nostdlib #-DNDEBUG
LDFLAGS     +=  -Map $(MAPFILE) -nostartfiles \
                -Ttext 0x08000000 -Tbss 0x03000000 \
                -L$(AGBLIB) -lagbsyscall -lisagbprn

DEPENDFILE  =   Makedepend
MAPFILE     =   reintr.map
TARGET_ELF  =   reintr.elf
TARGET_BIN  =   reintr.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
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
