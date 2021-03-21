CC := powerpc-eabi-g++.exe
LD := powerpc-eabi-ld.exe
AR := powerpc-eabi-ar.exe
AS := powerpc-eabi-as.exe
MAKE := make

PROJECT_BASE := $(dir $(lastword $(MAKEFILE_LIST)))
LINK_SCRIPT := $(PROJECT_BASE)mod_mapping.inc
OUT_BUILD := $(PROJECT_BASE)build_dir/
OUT_BIN := $(PROJECT_BASE)binary_dir/

CPPFLAGS_NOOPT := -O0 -c -ffreestanding -fno-exceptions -std=c++17 -Wall -Wno-trigraphs -I$(PROJECT_BASE).
CPPFLAGS_OPT := -O2 -c -ffreestanding -fno-exceptions -std=c++17 -Wall -Wno-trigraphs -I$(PROJECT_BASE).

FREESTANDING_O := $(OUT_BUILD)lib_freestanding.o
FREESTANDING_INC := $(PROJECT_BASE)freestanding.hh
FREESTANDING_SRC := $(PROJECT_BASE)freestanding.cc

MP1_SDK_H := $(wildcard $(PROJECT_BASE)mp1/mpsdk/*.hh)
MP1_RSTL_H := $(wildcard $(PROJECT_BASE)mp1/mpsdk/*.hh)
UTIL_H := $(wildcard $(PROJECT_BASE)util/*.hh)