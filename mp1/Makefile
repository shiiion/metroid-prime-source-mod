include ../tallon_base.mk

MP1_BIN := $(OUT_BIN)mp1/
MP1_BUILD := $(OUT_BUILD)mp1/
MP1_INCLUDES := $(MP1_RSTL_H) $(MP1_SDK_H) $(UTIL_H)
MP1_LIBS := -L$(MP1_BIN). -lrstl -lmp1sdk

SRCS := $(wildcard *.cc)
INTERMEDIATES := $(patsubst %.cc,$(MP1_BUILD)%.o,$(SRCS)) $(MP1_BUILD)mod_lowlevel.o

all : directories $(MP1_BIN)source_movememnt_mp1.mmd $(MP1_BIN)source_movement_mp1.elf

directories :
	mkdir -p $(MP1_BIN)
	mkdir -p $(MP1_BUILD)

$(MP1_BIN)source_movememnt_mp1.mmd : source_movement_mp1.mmd
	cp source_movement_mp1.mmd $(MP1_BIN)

$(MP1_BIN)source_movement_mp1.elf : mp1_sdk $(LINK_SCR) $(FREESTANDING_O) $(INTERMEDIATES)
	$(LD) -T $(LINK_SCRIPT) -o $(MP1_BIN)source_movement_mp1.elf $(FREESTANDING_O) $(INTERMEDIATES) $(MP1_LIBS)

$(MP1_BUILD)mod_lowlevel.o : mod_lowlevel.S
	$(AS) -o $@ $<

$(MP1_BUILD)%.o : %.cc $(FREESTANDING_INC) $(MP1_INCLUDES)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<


mp1_sdk :
	$(MAKE) -C rstl
	$(MAKE) -C mpsdk

.PHONY : all mp1_sdk directories
