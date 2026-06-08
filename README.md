# Source Movement Mod
This mod is intended to give a couple of quake/source-like features to the Metroid Prime series. It requires my mod loader, a feature of [Primehack](https://github.com/shiiion/dolphin).

## Supported Games
 - Metroid Prime (GameCube) NTSC revision 1.00
 - Metroid Prime 2: Echoes (GameCube) NTSC
 - Metroid Prime 3: Corruption (Wii, Standalone) NTSC

## DevkitPro Setup
### Windows
If you don't have devkitPro installed and in your path already, then grab devkitPro's powerPC toolchain (Gamecube/Wii are the only toolkits needed)

https://github.com/devkitPro/installer/releases

Once installed, add `(devkitPro install dir)/devkitPPC/bin` and `(devkitPro install dir)/devkitPPC/powerpc-eabi/bin` to your path

### Linux
Follow these instructions to install devkitPro, you should only need the gamecube-dev pacman group

https://devkitpro.org/wiki/devkitPro_pacman

Ensure it has been installed in `/opt/devkitpro/devkitPPC`, check to make sure that `powerpc-eabi-g++`, `powerpc-eabi-ld`, `powerpc-eabi-ar`, `powerpc-eabi-as` are all under `/opt/devkitpro/devkitPPC/bin`

## Building and Running
### Building
Run `make` in the root directory of this project. This should generate a zip archive at `binary_dir/Source.zip`.

### Running
 1. Launch PrimeHack version 1.0.9 or later
 2. Ensure `Enable Mod Loader` is checked under the PrimeHack menu bar dropdown
 3. If you haven't imported yet
     - Go to `PrimeHack -> Import Mod` in the menu bar
     - Select the generated `Source.zip`
     - A popup should notify you that it "Successfully imported '<path/to/Source.zip>'".
 4. Configure CVars for each game under `PrimeHack -> Configure Mods -> Source`
 5. Enable the mod by checking `PrimeHack -> Enabled Mods -> Source`. This can be toggled at any time.
 6. Launch one of the supported games
