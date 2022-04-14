include ../tallon_base.mk

MP2_BIN := $(OUT_BIN)mp2/
MP2_BUILD := $(OUT_BUILD)mp2/
MP2_INCLUDES := $(UTIL_H)

SRCS := source_movement_mp2.cc
INTERMEDIATES := $(MP2_BUILD)source_movement_mp2.o $(MP2_BUILD)mod_lowlevel.o

all : directories $(MP2_BIN)source_movement_mp2.mmd $(MP2_BIN)source_movement_mp2.elf

directories :
	mkdir -p $(MP2_BIN)
	mkdir -p $(MP2_BUILD)

$(MP2_BIN)source_movement_mp2.mmd : source_movement_mp2.mmd
	cp source_movement_mp2.mmd $(MP2_BIN)

$(MP2_BIN)source_movement_mp2.elf : $(LINK_SCR) $(FREESTANDING_O) $(INTERMEDIATES)
	$(LD) -T $(LINK_SCRIPT) -o $(MP2_BIN)source_movement_mp2.elf $(FREESTANDING_O) $(INTERMEDIATES)

$(MP2_BUILD)source_movement_mp2.o : source_movement_mp2.cc $(FREESTANDING_INC) $(MP2_INCLUDES)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

$(MP2_BUILD)mod_lowlevel.o : mod_lowlevel.S
	$(AS) -o $@ $<

.PHONY : all directories
