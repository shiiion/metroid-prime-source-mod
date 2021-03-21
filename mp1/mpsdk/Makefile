include ../../tallon_base.mk

LIBS := $(FREESTANDING_LIB)
SRCS := $(wildcard *.cc)
HDRS := $(wildcard *.hh) $(MP1_RSTL_H) $(UTIL_H)

INTERMEDIATES := $(patsubst %.cc,$(OUT_BUILD)%.o,$(SRCS))

all : directories $(OUT_BIN)libmp1sdk.a

$(OUT_BIN)libmp1sdk.a : $(INTERMEDIATES)
	$(AR) rcs $@ $^

$(OUT_BUILD)%.o : %.cc $(HDRS)
	$(CC) $(CPPFLAGS_OPT) -o $@ $<

directories : $(OUT_BUILD) $(OUT_BIN)

$(OUT_BUILD) :
	mkdir -p $(OUT_BUILD)
$(OUT_BIN) :
	mkdir -p $(OUT_BIN)

clean :
	rm -f $(INTERMEDIATES) $(OUT_BIN)lib_mpsdk.a

.PHONY : all directories clean