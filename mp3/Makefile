include ../tallon_base.mk

MP3_BIN := $(OUT_BIN)mp3/
MP3_BUILD := $(OUT_BUILD)mp3/
MP3_INCLUDES := $(UTIL_H)
MP3_LIBS := -L$(MP3_BIN). -lrstl -lmp3sdk

SRCS := $(wildcard *.cc)
INTERMEDIATES := $(patsubst %.cc,$(MP3_BUILD)%.o,$(SRCS)) $(MP3_BUILD)mod_lowlevel.o

all : directories $(MP3_BIN)source_movement_mp3.mmd $(MP3_BIN)source_movement_mp3.elf

directories :
	@mkdir -p $(MP3_BIN)
	@mkdir -p $(MP3_BUILD)

$(MP3_BIN)source_movement_mp3.mmd : source_movement_mp3.mmd
	cp source_movement_mp3.mmd $(MP3_BIN)

$(MP3_BIN)source_movement_mp3.elf : mp3_sdk $(LINK_SCR) $(FREESTANDING_O) $(INTERMEDIATES)
	$(LD) -T $(LINK_SCRIPT) -o $(MP3_BIN)source_movement_mp3.elf $(FREESTANDING_O) $(INTERMEDIATES) $(MP3_LIBS)

$(MP3_BUILD)mod_lowlevel.o : mod_lowlevel.S
	$(AS) -o $@ $<

$(MP3_BUILD)%.o : %.cc $(FREESTANDING_INC) $(MP3_INCLUDES)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

mp3_sdk :
	$(MAKE) -C rstl
	$(MAKE) -C mpsdk

.PHONY : all mp3_sdk directories
