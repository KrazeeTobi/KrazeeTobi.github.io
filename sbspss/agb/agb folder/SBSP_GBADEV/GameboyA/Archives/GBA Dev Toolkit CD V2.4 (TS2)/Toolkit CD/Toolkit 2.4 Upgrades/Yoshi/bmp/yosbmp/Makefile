include bmpfiles

.OFILES = $(.BMPFILES:.bmp=.o)
.IMBFILES = $(.BMPFILES:.bmp=.imb)

TARGET_ARC = libyosbmp.a

$(TARGET_ARC): $(.OFILES)
	ar rcs $(TARGET_ARC) $(.OFILES)

.SUFFIXES: .bmp .imb

.imb.o:
	objcopy -v -I binary -O elf32-little $< $@

.bmp.imb:
	bmp2bin $<

clean:
	-rm $(TARGET_ARC) $(.OFILES) $(.IMBFILES)
