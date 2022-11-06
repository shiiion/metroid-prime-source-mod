include tallon_base.mk

all : metroid_prime_1 metroid_prime_2

freestanding : $(FREESTANDING_O)

metroid_prime_1 : $(FREESTANDING_O)
	$(MAKE) -C mp1

metroid_prime_2 : $(FREESTANDING_O)
	$(MAKE) -C mp2

$(FREESTANDING_O) : $(FREESTANDING_SRC) $(FREESTANDING_INC)
	$(CC) $(CPPFLAGS_OPT) -o $(FREESTANDING_O) $(FREESTANDING_SRC)

clean :
	rm -rf $(OUT_BIN)*
	rm -rf $(OUT_BUILD)*

.PHONY : all clean metroid_prime_1 metroid_prime_2 freestanding
