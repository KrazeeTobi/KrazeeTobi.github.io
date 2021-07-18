.BMPFILES = bg1.bmp bg2.bmp bg3.bmp
.CFILES = $(.BMPFILES:.bmp=.c)
.OFILES = $(.BMPFILES:.bmp=.o)
_AGBDIR = ../../../../..
CFLAGS	= -g -O2 -I$(_AGBDIR)/include -mthumb-interwork -nostdlib

TARGET_ARC = libyosbgbmp.a

$(TARGET_ARC): $(.OFILES)
	ar rcs $(TARGET_ARC) $(.OFILES)

bg1.c: bg1.bmp
	bmp2map -o $@ $<
bg2.c: bg2.bmp
	bmp2map -f -o $@ $<
bg3.c: bg3.bmp
	bmp2map -f -p 15 -o $@ $<

clean:
	-rm $(TARGET_ARC) $(.OFILES) $(.CFILES)
