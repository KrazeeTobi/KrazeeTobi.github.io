AGB_DIR	   	= c:/agb
AGB_INCLUDE_DIR = $(AGB_DIR)/include
CYGNUSDIR  	= c:/progra~1/cygnus/thumbelf-000512

ARM_ASSEMBLER	= armasm
ARM_C_COMPILER	= tcc
ARM_LINKER	= armlink

ARM_DEPENDFILE =   deps

ARM_TARGET_DIR 	= armbin

ARM_TARGET_MAP 	= project.map
ARM_TARGET_ELF 	= project.elf
ARM_TARGET_BIN 	= project.bin

.SFILES    	=   crt0_arm.s
.CFILES    	=   main.c data.c oam.c interrupt.c
.OFILES    	=   $(.SFILES:.s=.o) $(.CFILES:.c=.o)

ARM_ASMFLAGS 	= -apcs /interwork -i$(AGB_INCLUDE_DIR)

ARM_CFLAGS   	= -Wb -c -O0 -I$(AGB_INCLUDE_DIR) -apcs /interwork -o $(@:.c=.o)

ARM_LFLAGS      = -first crt0_arm.o -ro-base 0x8000000 -rw-base 0x3000000 -split -O $(ARM_TARGET_ELF)
ARM_MAP_FLAGS	= -MAP > $(ARM_TARGET_MAP)
ARM_FELF_FLAGS 	= -bin -o $(ARM_TARGET_DIR)

$(ARM_TARGET_BIN): $(ARM_TARGET_ELF)
	@fromelf $(ARM_FELF_FLAGS) -nodebug $(ARM_TARGET_ELF)
	armconv.bat

$(ARM_TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE)
	@echo Linking...
	$(ARM_LINKER) $(ARM_LFLAGS) $(.OFILES)

.SUFFIXES: .s .c .o

.s.o:
	$(ARM_ASSEMBLER) $(ARM_ASMFLAGS) $<
.c.o:
	$(ARM_C_COMPILER) $(ARM_CFLAGS) $<


.PHONY: all clean depend

all:    clean depend $(ARM_TARGET_BIN)

clean:
	rm $(.OFILES) $(DEPENDFILE) $(ARM_TARGET_ELF) $(ARM_TARGET_BIN) $(ARM_TARGET_MAP)

run:
	agbload -n $(ARM_TARGET_BIN)

depend:
	$(ARM_C_COMPILER) $(ARM_CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

#$(DEPENDFILE):
#	$(CC) $(CFLAGS_D) -M $(.CFILES) > $(DEPENDFILE)
#	$(ARM_C_COMPILER) $(ARM_CFLAGS) -M $(.CFILES) > $(DEPENDFILE)


include Gasdepend
include $(ARM_DEPENDFILE)

