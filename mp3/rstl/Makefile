include ../../tallon_base.mk

LIBS := $(FREESTANDING_LIB)
SRCS := $(wildcard *.cc)
HDRS := $(wildcard *.hh) $(UTIL_H)

MP3_BIN := $(OUT_BIN)mp3/
MP3_BUILD := $(OUT_BUILD)mp3/
INTERMEDIATES := $(patsubst %.cc,$(MP3_BUILD)%.o,$(SRCS))

all : directories $(MP3_BIN)librstl.a

$(MP3_BIN)librstl.a : $(INTERMEDIATES)
	$(AR) rcs $@ $^

$(MP3_BUILD)%.o : %.cc $(HDRS)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

directories : $(MP3_BUILD) $(MP3_BIN)

clean :
	rm -f $(INTERMEDIATES) $(MP3_BIN)librstl.a

.PHONY : all clean
