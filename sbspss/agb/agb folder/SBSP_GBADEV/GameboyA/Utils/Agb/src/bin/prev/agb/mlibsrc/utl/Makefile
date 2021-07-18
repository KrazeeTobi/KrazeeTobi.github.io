
INCDIR	=	$(AGBDIR)/include/
LIBDIR	=	$(AGBDIR)/lib/
MINCDIR	=	../../minc/
MLIBDIR	=	../../mlib/

AR	=	ar

.SFILES	=	
.CFILES	=	util.c controller.c
.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS	=		  -I$(INCDIR) -mthumb-interwork
CFLAGS	=	-g -c -O2 -I$(INCDIR) -I$(MINCDIR) -mthumb-interwork -nostdlib
DEPENDFILE =	Makedepend
TARGETDIR =	$(MLIBDIR)
TARGET_AR =	$(TARGETDIR)libutl.a


$(TARGET_AR): $(.OFILES)
	$(AR) cr $@ $(.OFILES)
	cp *.h $(MINCDIR)

.PHONY: all clean depend hcp

all:	clean depend $(TARGET_AR)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_AR)

hcp:
	cp *.h ../../minc/

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
