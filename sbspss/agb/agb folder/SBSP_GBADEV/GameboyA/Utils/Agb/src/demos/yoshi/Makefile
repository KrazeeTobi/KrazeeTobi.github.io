SOUND_DIR = sound/
include $(SOUND_DIR)Soundfiles

.SFILES		=	crt0.s
.CFILES		=	yos_game.c yos_game_dat.c yos_anm.c \
			bg_proc.c \
			yos_game_sub.c yos_game_mov.c yos_game_pr.c \
			yos_main.c yos_main_dat.c \
			oam_proc.c \
			menu.c menu_dat.c
.OFILES_FROM_SRC =	$(.SFILES:.s=.o) $(.CFILES:.c=.o)
.OFILES		=	$(.OFILES_FROM_SRC) $(SOUND_FILES)
.AFILES		=	bmp/islebmp/libislebmp.a \
			bmp/yosbgbmp/libyosbgbmp.a \
			bmp/yosbmp/libyosbmp.a \
			bmp/menubmp/libmenubmp.a

AGBINC		=	$(AGBDIR)/include
AGBLIB		=	$(AGBDIR)/lib

ASFLAGS		=	       -I$(AGBINC) -mthumb-interwork
CFLAGS		=	-g -O2 -I$(AGBINC) -mthumb-interwork \
			-nostdlib -Wall # -save-temps

LDFLAGS		+=	-Map $(MAPFILE) -nostartfiles \
			-Ttext 0x08000000 -Tbss 0x03000000 \
			-L$(AGBLIB) -lisagbprn -lagbsyscall\
			-Lbmp/yosbmp/ -lyosbmp \
			-Lbmp/yosbgbmp/ -lyosbgbmp \
			-Lbmp/islebmp/ -lislebmp \
			-Lbmp/menubmp/ -lmenubmp \
			-T$(LDSCRIPT) 
#			-L. -lyossound
LDSCRIPT	=	ldscript.x
DEPENDFILE	=	Makedepend
MAPFILE		=	yoshi.map
TARGET_ELF	=	yoshi.elf
TARGET_BIN	=	yoshi.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(.AFILES) $(DEPENDFILE) $(LDSCRIPT)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

.PHONY: all clean depend data

all:	clean depend data $(TARGET_BIN)

clean:
	-rm $(.OFILES_FROM_SRC) $(DEPENDFILE)
clean_data:
	$(foreach .ADIR_TMP, $(dir $(.AFILES)), make -C $(.ADIR_TMP) clean;)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

.SUFFIXES: .s .c .o .a

include Gasdepend
include $(DEPENDFILE)
data:
	$(foreach .ADIR_TMP, $(dir $(.AFILES)), make -C $(.ADIR_TMP);)

