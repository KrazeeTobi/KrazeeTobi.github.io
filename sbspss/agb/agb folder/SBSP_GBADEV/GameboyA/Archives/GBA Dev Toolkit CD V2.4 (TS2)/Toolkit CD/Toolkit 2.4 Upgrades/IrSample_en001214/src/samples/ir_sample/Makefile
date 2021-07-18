
.SFILES	=	crt0.s
.CFILES	=	main.c utility.c data.c
.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)

AGBINC	=	$(AGBDIR)/include
AGBLIB	=	$(AGBDIR)/lib

ASFLAGS	=	       -I $(AGBINC) -mthumb-interwork
CFLAGS	=	-g -O2 -I $(AGBINC) -mthumb-interwork -nostdlib -fno-common
LDFLAGS	+=	-Map $(MAPFILE) -nostartfiles \
			-Ttext 0x08000000 -Tbss 0x03000000 \
			-L$(AGBLIB) -lagbsyscall -lisagbprn -lagbir

DEPENDFILE	=	Makedepend
MAPFILE		=	ir_sample.map
TARGET_ELF	=	ir_sample.elf
TARGET_BIN	=	ir_sample.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)


.PHONY: all clean depend

all:	clean depend $(TARGET_BIN)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ELF) $(TARGET_BIN)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include Gasdepend
include $(DEPENDFILE)
