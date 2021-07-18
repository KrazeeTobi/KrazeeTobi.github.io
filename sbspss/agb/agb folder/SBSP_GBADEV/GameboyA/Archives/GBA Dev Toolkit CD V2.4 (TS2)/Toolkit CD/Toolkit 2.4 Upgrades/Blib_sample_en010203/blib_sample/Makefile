.SFILES		=	crt0.s
.CFILES		=	Main.c Data.c MemDump.c SramTest.c FlashTest.c EepromTest.c
.OFILES   	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)

AGBINC		=	$(AGBDIR)/include
AGBLIB		=	$(AGBDIR)/lib

ASFLAGS		=	-I$(AGBINC) -mthumb-interwork
CFLAGS		=	-g -O2 -I$(AGBINC) -I$(AGBINC)/backup -Imylib \
			-mthumb-interwork
LDFLAGS		=	-Map $(MAPFILE) -nostartfiles \
			-Ttext 0x08000000 -Tbss 0x03000000 \
			-L$(AGBLIB) -lagbsyscall -lisagbprn -lagbbackup \
			-Lmylib -lmyfunc

DEPENDFILE	=	Makedepend
MAPFILE		=	blib_sample.map
TARGET_ELF	=	blib_sample.elf
TARGET_BIN	=	blib_sample.bin


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
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE) > error.txt 2>&1

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include Gasdepend
include $(DEPENDFILE)
