include ../../tallon_base.mk

LIBS := $(FREESTANDING_LIB)
SRCS := $(wildcard *.cc)
HDRS := $(wildcard *.hh) $(UTIL_H)

MP1_BIN := $(OUT_BIN)mp1/
MP1_BUILD := $(OUT_BUILD)mp1/
INTERMEDIATES := $(patsubst %.cc,$(MP1_BUILD)%.o,$(SRCS))

all : directories $(MP1_BIN)librstl.a

$(MP1_BIN)librstl.a : $(INTERMEDIATES)
	$(AR) rcs $@ $^

$(MP1_BUILD)%.o : %.cc $(HDRS)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

directories : $(MP1_BUILD) $(MP1_BIN)

$(MP1_BUILD) :
	mkdir -p $(MP1_BUILD)
$(MP1_BIN) :
	mkdir -p $(MP1_BIN)

clean :
	rm -f $(INTERMEDIATES) $(MP1_BIN)librstl.a

.PHONY : all directories clean
