
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.BMPFILES =	hey2.bmp
.CIMAGE	=	$(.BMPFILES:.bmp=.c)
.CFILES	=	obmain.c obexpl.c
.OFILES	=	$(.CFILES:.c=.o) $(.CIMAGE:.c=.o)
CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib
DEPENDFILE =	Makedepend
TARGET_ARC =	../libobj_rsm.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE) $(.CIMAGE)
	ar crs $@ $(.OFILES)

%.c : %.bmp
	bmp2agb $<


.PHONY: all clean depend

all:	clean depend $(TARGET_ARC)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ARC) $(.CIMAGE)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)
