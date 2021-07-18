
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

ARCDIR0 = 	RLEsmoke
.AFILES	=	libbitmap.a
.SFILES	=	crt0.s
.CFILES	=	main.c share.c bitmap.c data.c $(ARCDIR0)/bmpdata.c
.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS	=	-I$(AGBINC) -I$(ARCDIR0) -mthumb-interwork
CFLAGS	=	-g -O2 -I$(AGBINC) -I$(ARCDIR0) -mthumb-interwork -nostdlib -D_DEBUG
LDFLAGS	+=  	-Map $(MAPFILE) -nostartfiles \
				-Tbss 0x03000000 -Ttext 0x08000000 \
				-L$(AGBLIB) -lagbsyscall \
				-L$(ARCDIR0) -lbitmap
DEPENDFILE	= Makedepend
MAPFILE		= player.map
TARGET_ELF	= player.elf
TARGET_BIN	= player.bin

default:
	@$(MAKE) $(TARGET_BIN)

$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE) $(.AFILES)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

.PHONY: all clean depend relink rmbin

all:	clean default

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ELF) $(TARGET_BIN) $(MAPFILE)
	#make -C $(ARCDIR0) clean
	#cd ..

relink: rmbin $(TARGET_BIN)

rmbin:
	-rm $(TARGET_ELF) $(TARGET_BIN)

depend:

	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(.AFILES):
	make -C $(ARCDIR0)
	cd ..

include gasDepend
include $(DEPENDFILE)
