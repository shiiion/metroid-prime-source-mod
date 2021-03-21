# Build instructions:
## Windows:
If you don't have devkitPro installed and in your path already, then 
grab devkitPro's powerPC toolchain (Gamecube/Wii are the only toolkits needed)

https://github.com/devkitPro/installer/releases

Once installed, add `(devkitPro install dir)/devkitPPC/bin` and
`(devkitPro install dir)/devkitPPC/powerpc-eabi/bin` to your path

Run `make` in the root directory of this project. This should generate an ELF under `binary_dir/<game>/`, and copy the mod metadata file in the same folder.

Grab Ishiiruka Primehack, start up your copy of Metroid Prime, and load the mod (it wants the .mmd).

> Note: MP1 mod only supports MP1 GC NTSC v1.00, MP2 mod only supports MP2 GC NTSC.

## Linux:
N/A