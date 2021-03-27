# Source Movement Mods
This mod is intended to give a couple of source-engine-like features to the Metroid Prime series. It requires my mod loader, a feature of [Ishiiruka Primehack](https://github.com/shiiion/Ishiiruka).

## DevkitPro Setup:
### Windows:
If you don't have devkitPro installed and in your path already, then grab devkitPro's powerPC toolchain (Gamecube/Wii are the only toolkits needed)

https://github.com/devkitPro/installer/releases

Once installed, add `(devkitPro install dir)/devkitPPC/bin` and `(devkitPro install dir)/devkitPPC/powerpc-eabi/bin` to your path

### Linux:
Follow these instructions to install devkitPro, you should only need the gamecube-dev pacman group

https://devkitpro.org/wiki/devkitPro_pacman

Ensure it has been installed in `/opt/devkitpro/devkitPPC`, check to make sure that `powerpc-eabi-g++`, `powerpc-eabi-ld`, `powerpc-eabi-ar`, `powerpc-eabi-as` are all under `/opt/devkitpro/devkitPPC/bin`

## Building and Running:
Run `make` in the root directory of this project. This should generate an ELF under `binary_dir/<game>/`, and copy the mod metadata file (.mmd) in the same folder.

Grab Ishiiruka Primehack, start up your copy of Metroid Prime, and load the mod (it wants the .mmd).

> Note: MP1 mod only supports MP1 GC NTSC v1.00, MP2 mod only supports MP2 GC NTSC.