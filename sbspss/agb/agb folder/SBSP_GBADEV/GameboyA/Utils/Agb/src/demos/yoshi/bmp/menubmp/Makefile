.BMPFILES = kumo.bmp umi64.bmp grade.bmp
.OFILES = $(.BMPFILES:.bmp=.o)
.IMBFILES = $(.BMPFILES:.bmp=.imb)

TARGET_ARC = libmenubmp.a

$(TARGET_ARC): $(.OFILES)
	ar rcs $(TARGET_ARC) $(.OFILES)

.SUFFIXES: .bmp .imb .o

.imb.o:
	objcopy -v -I binary -O elf32-little $< $@

.bmp.imb:
	bmp2bin $<

clean:
	-rm $(TARGET_ARC) $(.OFILES) $(.IMBFILES)
