AGBINC = $(AGBDIR)/include/
AGBLIB = $(AGBDIR)/lib/

.SFILES		=	crt0.s
.CFILES		=	main.c player.c player_dat.c enemy.c enemy_dat.c game_dat.c \
				bg.c hitcheck.c ring.c \
				obj/r_kihon0.c obj/r_kihon1.c obj/r_kihon2.c obj/r_kihon3.c \
				obj/r_kihon4.c obj/r_kihon5.c obj/r_kihon6.c obj/r_kihon7.c \
				obj/r_up0.c obj/r_up1.c obj/r_up2.c obj/r_up3.c \
				obj/r_up4.c obj/r_up5.c obj/r_up6.c obj/r_up7.c \
				obj/r_up8.c \
				obj/r_go_up0.c obj/r_go_up1.c obj/r_go_up2.c obj/r_go_up3.c \
				obj/r_go_up4.c obj/r_go_up5.c obj/r_go_up6.c obj/r_go_up7.c \
				obj/r_down0.c obj/r_down1.c obj/r_down2.c obj/r_down3.c \
				obj/r_down4.c obj/r_down5.c obj/r_down6.c obj/r_down7.c \
				obj/r_down8.c \
				obj/r_go_down0.c obj/r_go_down1.c obj/r_go_down2.c obj/r_go_down3.c \
				obj/r_go_down4.c obj/r_go_down5.c obj/r_go_down6.c obj/r_go_down7.c \
				obj/r_jump0.c obj/r_jump1.c obj/r_jump2.c obj/r_jump3.c \
				obj/r_jump4.c obj/r_jump5.c obj/r_jump6.c obj/r_jump7.c \
				obj/r_jump8.c obj/r_jump9.c obj/r_jump10.c \
				obj/r_attack1.c obj/r_attack2.c obj/r_attack3.c \
				obj/r_attack4.c obj/r_attack5.c obj/r_attack6.c \
				obj/r_attack7.c \
				obj/o_kihon001.c obj/o_kihon002.c obj/o_kihon003.c \
				obj/o_kihon004.c obj/o_kihon005.c obj/o_kihon006.c \
				obj/o_kihon007.c obj/o_kihon008.c obj/o_kihon009.c \
				obj/o_kihon010.c \
				obj/o_kougeki000.c obj/o_kougeki001.c obj/o_kougeki002.c \
				obj/o_kougeki003.c obj/o_kougeki004.c obj/o_kougeki005.c \
				obj/o_kougeki006.c obj/o_kougeki007.c obj/o_kougeki008.c \
				obj/o_kougeki009.c obj/o_kougeki010.c obj/o_kougeki011.c \
				obj/o_kougeki012.c obj/o_kougeki013.c obj/o_kougeki014.c \
				obj/o_kougeki015.c obj/o_kougeki016.c obj/o_kougeki017.c \
				obj/o_kougeki018.c obj/o_kougeki019.c obj/o_kougeki020.c \
				obj/o_yarare000.c obj/o_yarare001.c obj/o_yarare002.c \
				obj/o_yarare003.c obj/o_yarare004.c obj/o_yarare005.c \
				obj/o_yarare006.c obj/o_yarare007.c obj/o_yarare008.c \
				obj/o_yarare009.c obj/o_yarare010.c obj/o_yarare011.c \
				obj/o_yarare012.c obj/o_yarare013.c obj/o_yarare014.c \
				obj/o_yarare015.c obj/o_yarare016.c obj/o_yarare017.c \
				obj/o_yarare018.c obj/o_yarare019.c obj/o_yarare020.c \
				obj/o_fukiya000.c \
				obj/awa.c \
				obj/ring_32_64_left.c obj/ring_32_64_right.c \
				bg_parts/umia_.c \
				bg_parts/umi_ab_256x512.c \
				bg_parts/sango1024x256.c \
				bg_parts/sora.c \
				bg_parts/light4.c \
				bg_parts/wave2nd1.c \
				bg_parts/wave2nd2.c \
				bg_parts/wave2nd3.c

.OFILES		=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)
ASFLAGS		=			  -I$(AGBINC) -mthumb-interwork
CFLAGS		=	-g -c -O2 -I$(AGBINC) -mthumb-interwork -nostdlib #-DNDEBUG
LDFLAGS		+=  -Map $(MAPFILE) -nostartfiles \
				-Ttext 0x08000000 -Tbss 0x03000000 \
				-L$(AGBLIB) -lagbsyscall -lisagbprn
DEPENDFILE	=	Makedepend
MAPFILE		=	dolphin.map
TARGET_ELF	=	dolphin.elf
TARGET_BIN	=	dolphin.bin


$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)

.PHONY: all clean depend

all:	clean depend $(TARGET_BIN)

clean:
	-rm $(.OFILES) $(DEPENDFILE) $(TARGET_ELF)

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include Gasdepend
include $(DEPENDFILE)
