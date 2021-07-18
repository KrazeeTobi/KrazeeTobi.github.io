
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.BMPFILES =	sw_bg1.bmp sw_bg2.bmp sw_bg3.bmp sw_bg0.bmp sw_PS_hey5.bmp
.CIMAGE	=	$(.BMPFILES:.bmp=.c)
.CFILES	=	window.c swexpl.c
.OFILES	=	$(.CFILES:.c=.o) $(.CIMAGE:.c=.o)
CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib -Wall
DEPENDFILE =	Makedepend

TARGET_ARC =	../libswinsm.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE) $(.CIMAGE)
	ar crs $@ $(.OFILES)

sw_bg%.c : sw_bg%.bmp
	bmp2map -f $<

sw_PS_hey5.c : sw_PS_hey5.bmp
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
