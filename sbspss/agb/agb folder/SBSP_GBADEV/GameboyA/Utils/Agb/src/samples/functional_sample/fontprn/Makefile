
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.CFILES	=	fontprn.c
.OFILES	=	$(.CFILES:.c=.o)

CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib
DEPENDFILE =	Makedepend

TARGET_ARC =	../libfontprn.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE)
	ar crs $@ $(.OFILES)


.PHONY: all clean depend

all:	clean depend $(TARGET_ARC)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ARC)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)
