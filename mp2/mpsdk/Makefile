include ../../tallon_base.mk

LIBS := $(FREESTANDING_LIB)
SRCS := $(wildcard *.cc)
HDRS := $(wildcard *.hh) $(MP2_RSTL_H) $(UTIL_H)

MP2_BIN := $(OUT_BIN)mp2/
MP2_BUILD := $(OUT_BUILD)mp2/
INTERMEDIATES := $(patsubst %.cc,$(MP2_BUILD)%.o,$(SRCS))

all : directories $(MP2_BIN)libmp2sdk.a

$(MP2_BIN)libmp2sdk.a : $(INTERMEDIATES)
	$(AR) rcs $@ $^

$(MP2_BUILD)%.o : %.cc $(HDRS)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

clean :
	rm -f $(INTERMEDIATES) $(MP2_BIN)libmp2sdk.a

.PHONY : all directories clean
