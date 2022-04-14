include tallon_base.mk

all : metroid_prime_1 metroid_prime_2

metroid_prime_1 : directories $(FREESTANDING_O)
	$(MAKE) -C mp1

metroid_prime_2 : directories $(FREESTANDING_O)
	$(MAKE) -C _old

$(FREESTANDING_O) : $(FREESTANDING_SRC) $(FREESTANDING_INC)
	$(CC) $(CPPFLAGS_OPT) -o $(FREESTANDING_O) $(FREESTANDING_SRC)

directories : $(OUT_BUILD) $(OUT_BIN)

$(OUT_BUILD) :
	mkdir -p $(OUT_BUILD)
$(OUT_BIN) :
	mkdir -p $(OUT_BIN)

clean :
	rm -rf $(OUT_BIN)*
	rm -rf $(OUT_BUILD)*

.PHONY : all clean directories metroid_prime_1
