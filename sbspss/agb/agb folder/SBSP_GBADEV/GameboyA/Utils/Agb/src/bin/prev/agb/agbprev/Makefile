
INCDIR   =	$(AGBDIR)/include/
LIBDIR   =	$(AGBDIR)/lib/

MINCDIR	=	../minc/
MLIBDIR	=	../mlib/

.SFILES	=	crt0.s
.CFILES	=	main.c prevobj.c \
		prevbg.c prevdata.c 
.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS	=		  -I$(INCDIR) -mthumb-interwork
CFLAGS	=	-g -c -O2 -I$(INCDIR) -I$(MINCDIR) -mthumb-interwork -nostdlib
LDFLAGS	 +=	 -Map $(MAPFILE) -nostartfiles \
		-Ttext 0x08000000 -Tbss 0x02000000 \
		-L$(CYGNUSDIR)/thumbelf-981216/H-i586-cygwin32/lib/gcc-lib/thumb-elf/2.9-armelf-981216/ -L$(CYGNUSDIR)/thumbelf-981216/H-i586-cygwin32/thumb-elf/lib/ -L$(LIBDIR) -lisagbprn -L$(MLIBDIR) -lutl -lmpr
DEPENDFILE =	Makedepend
MAPFILE =	agbprev.map
TARGET_ELF =	agbprev.elf
TARGETDIR =	../../../../../bin/prev/
TARGET_BIN =	$(TARGETDIR)/agbprev.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	type >> $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

.PHONY: all clean depend elrm relink lib libmake

libmake:
	make -C ../mlibsrc/utl
	make -C ../mlibsrc/mpr

lib:	libmake relink

all:	clean depend $(TARGET_BIN)

relink:	elrm $(TARGET_BIN)

elrm:
	-rm $(TARGET_ELF) $(TARGET_BIN)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ELF) $(TARGET_BIN)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)

#ifdef _DEBUG
const u32 BMP_ADDRESS = 0x900000;
#else
#define	BMP_ADDRESS 0x900000
#endif
