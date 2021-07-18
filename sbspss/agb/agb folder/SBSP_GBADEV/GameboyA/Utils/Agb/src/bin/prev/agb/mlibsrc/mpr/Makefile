
INCDIR	=	$(AGBDIR)/include/
LIBDIR	=	$(AGBDIR)/lib/
MINCDIR	=	../../minc/
MLIBDIR	=	../../mlib/

AR	=	ar

.SFILES	=	
.CFILES	=	datatrans.c objmanage.c object.c	\
		bgmanage.c background.c \
		node.c node_object.c node_image.c \
		node_animation.c node_background.c \
		ch_alloc.c mpr.c
.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS	=		  -I$(INCDIR) -mthumb-interwork
CFLAGS	=	-g -c -O2 -I$(INCDIR) -I$(MINCDIR) -mthumb-interwork -nostdlib

DEPENDFILE =	Makedepend

TARGETDIR =	$(MLIBDIR)
TARGET_AR =	$(TARGETDIR)libmpr.a

$(TARGET_AR): $(.OFILES)
	ar cr $@ $(.OFILES)

.PHONY: all clean depend hcp

all:	clean depend $(TARGET_AR) hcp

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
