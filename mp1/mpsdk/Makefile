include ../../tallon_base.mk

LIBS := $(FREESTANDING_LIB)
SRCS := $(wildcard *.cc)
HDRS := $(wildcard *.hh) $(MP1_RSTL_H) $(UTIL_H)

MP1_BIN := $(OUT_BIN)mp1/
MP1_BUILD := $(OUT_BUILD)mp1/
INTERMEDIATES := $(patsubst %.cc,$(MP1_BUILD)%.o,$(SRCS))

all : directories $(MP1_BIN)libmp1sdk.a

$(MP1_BIN)libmp1sdk.a : $(INTERMEDIATES)
	$(AR) rcs $@ $^

$(MP1_BUILD)%.o : %.cc $(HDRS)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

clean :
	rm -f $(INTERMEDIATES) $(MP1_BIN)libmp1sdk.a

.PHONY : all directories clean
