
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.BMPFILES =	ap_bg0.bmp ap_bg1.bmp ap_bg2.bmp ap_PS_hey5.bmp
.CIMAGE	=	$(.BMPFILES:.bmp=.c)
.CFILES	=	alpha.c alpha_data.c alexpl.c
.OFILES	=	$(.CFILES:.c=.o) $(.CIMAGE:.c=.o)
CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib -Wall
DEPENDFILE =	Makedepend
TARGET_ARC =	../libalphasm.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE) $(.CIMAGE)
	ar crs $@ $(.OFILES)

ap_bg%.c : ap_bg%.bmp
	bmp2map -f $<

ap_PS_hey5.c : ap_PS_hey5.bmp
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
