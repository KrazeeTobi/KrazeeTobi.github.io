
AGBINC	=	$(AGBDIR)/include/
AGBLIB	=	$(AGBDIR)/lib/

.BMPFILES =	ball.bmp bg_map.bmp cl0.bmp
.CIMAGE	=	$(.BMPFILES:.bmp=.c)
.CFILES	=	bgmain.c bgexpl.c bg_map_map.c 
.OFILES	=	$(.CFILES:.c=.o) $(.CIMAGE:.c=.o) 
CFLAGS	=	-g -O2 -I$(AGBINC) -mthumb-interwork -nostdlib
DEPENDFILE =	Makedepend
TARGET_ARC =	../libbg_rsm.a


$(TARGET_ARC): $(.OFILES) Makefile $(DEPENDFILE) $(.CIMAGE)
	ar crs $@ $(.OFILES)

ball.c : ball.bmp
	bmp2agb $<

bg_map.c : bg_map.bmp
	bmp2agb $<

cl0.c : cl0.bmp
	bmp2map -o $@ $<


.PHONY: all clean depend

all:	clean depend $(TARGET_ARC)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ARC) $(.CIMAGE)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)
