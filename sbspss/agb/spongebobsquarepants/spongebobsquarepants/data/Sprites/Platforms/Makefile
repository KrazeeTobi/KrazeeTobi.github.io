.BMPFILES = platform0001.bmp
 
.CFILES = $(.BMPFILES:.bmp=.c)

.OFILES = $(.BMPFILES:.bmp=.o)

_AGBDIR = ($AGBDIR)

CFLAGS	= -g -O2 -I$(AGBDIR)/include -mthumb-interwork -nostdlib

TARGET_ARC = lib\Platforms_Sprs.a

$(TARGET_ARC): $(.OFILES)
	ar rcs $(TARGET_ARC) $(.OFILES)

BMP2AGB := bmp2agb -onp

platform0001.c: platform0001.bmp
	$(BMP2AGB) $@ $<
clean:
	-rm $(TARGET_ARC) $(.OFILES) $(.CFILES)
