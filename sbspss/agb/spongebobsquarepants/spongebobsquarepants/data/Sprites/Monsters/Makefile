.BMPFILES = clamsidesnap0001.bmp \
	clamsidesnap0003.bmp \
	clamsidesnap0005.bmp \
	clamsidesnap0007.bmp \
	clamsnapup0001.bmp \
	clamsnapup0003.bmp \
	clamsnapup0005.bmp
 
.CFILES = $(.BMPFILES:.bmp=.c)

.OFILES = $(.BMPFILES:.bmp=.o)

_AGBDIR = ($AGBDIR)

CFLAGS	= -g -O2 -I$(AGBDIR)/include -mthumb-interwork -nostdlib

TARGET_ARC = lib\Monsters_Sprs.a

$(TARGET_ARC): $(.OFILES)
	ar rcs $(TARGET_ARC) $(.OFILES)

BMP2AGB := bmp2agb -onp

clamsidesnap0001.c: clamsidesnap0001.bmp
	$(BMP2AGB) $@ $<
clamsidesnap0003.c: clamsidesnap0003.bmp
	$(BMP2AGB) $@ $<
clamsidesnap0005.c: clamsidesnap0005.bmp
	$(BMP2AGB) $@ $<
clamsidesnap0007.c: clamsidesnap0007.bmp
	$(BMP2AGB) $@ $<
clamsnapup0001.c: clamsnapup0001.bmp
	$(BMP2AGB) $@ $<
clamsnapup0003.c: clamsnapup0003.bmp
	$(BMP2AGB) $@ $<
clamsnapup0005.c: clamsnapup0005.bmp
	$(BMP2AGB) $@ $<

clean:
	-rm $(TARGET_ARC) $(.OFILES) $(.CFILES)
