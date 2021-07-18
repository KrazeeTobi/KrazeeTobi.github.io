
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.BMPFILES =	ce_PS_hey5.bmp ce_bg1.bmp ce_bg3.bmp
.CIMAGE	=	$(.BMPFILES:.bmp=.c)
.CFILES	=	c_effect.c ce_data.c ceexpl.c
.OFILES	=	$(.CFILES:.c=.o) $(.CIMAGE:.c=.o)
CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib -Wall
DEPENDFILE =	Makedepend

TARGET_ARC =	../libcoleffsm.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE) $(.CIMAGE)
	ar crs $@ $(.OFILES)

ce_bg%.c : ce_bg%.bmp
	bmp2map -f $<

ce_PS_hey5.c : ce_PS_hey5.bmp
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
