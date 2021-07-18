
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.BMPFILES =	img24bit.bmp img24bit2.bmp umiB.bmp
.CIMAGE	=	$(.BMPFILES:.bmp=.c)
.CFILES	=	bitmap.c bmexpl.c
.OFILES	=	$(.CFILES:.c=.o) $(.CIMAGE:.c=.o)
CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib
DEPENDFILE =	Makedepend
TARGET_ARC =	../libbmpmode.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE) $(.CIMAGE)
	ar crs $@ $(.OFILES)

%.c:%.bmp
	bmp2agb -bm $<


.PHONY: all clean depend

all:	clean depend $(TARGET_ARC)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ARC) $(.CIMAGE)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)
