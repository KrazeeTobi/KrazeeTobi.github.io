include bmpfiles
.OFILES = $(.BMPFILES:.bmp=.o)

TARGET_ARC = libislebmp.a

$(TARGET_ARC): $(.OFILES)
	ar rcs $(TARGET_ARC) $(.OFILES)

.SUFFIXES: .bmp .o

.bmp.o:
	bmp2map -b -B -M $<
	objcopy -v -I binary -O elf32-little $(<:.bmp=.imb) $(<:.bmp=_b.o)
	objcopy -v -I binary -O elf32-little $(<:.bmp=.mpb) $(<:.bmp=_m.o)
	ld -r $(<:.bmp=_b.o) $(<:.bmp=_m.o) -o $@
	rm $(<:.bmp=.imb) $(<:.bmp=.mpb) $(<:.bmp=_b.o) $(<:.bmp=_m.o)

clean:
	-rm $(TARGET_ARC) $(.OFILES)
