include tallon_base.mk

all : metroid_prime_1 metroid_prime_2 metroid_prime_3
	zip -j -r "$(OUT_BIN)/Source Movement.zip" "Source Movement.mpk" binary_dir/mp1/Source1S0N.elf binary_dir/mp2/Source2S0N.elf binary_dir/mp3/Source3S0N.elf

freestanding : $(FREESTANDING_O)

metroid_prime_1 : $(FREESTANDING_O)
	$(MAKE) -C mp1

metroid_prime_2 : $(FREESTANDING_O)
	$(MAKE) -C mp2

metroid_prime_3 : $(FREESTANDING_O)
	$(MAKE) -C mp3

$(FREESTANDING_O) : $(FREESTANDING_SRC) $(FREESTANDING_INC)
	$(CC) $(CPPFLAGS_OPT) -o $(FREESTANDING_O) $(FREESTANDING_SRC)

clean :
	rm -rf $(OUT_BIN)*
	rm -rf $(OUT_BUILD)*

.PHONY : all clean metroid_prime_1 metroid_prime_2 metroid_prime_3 freestanding
