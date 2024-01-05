# Procedural Infinite World Generator

//FIX// Description of PIWG

### *Supported Platforms*
- Windows

## Options
1. Download and run the latest release from [the releases page.]()
   > [How to use the PIWG demo.](https://github.com/Bwright257/Procedural-Infinite-World-Generator?tab=readme-ov-file#how-to-use)
3. Install and compile the program on your own by following the steps below.

## Installation and Setup

### *Requisites*
- [Visual Studio Code](https://code.visualstudio.com/download)
- [MinGW-64](https://www.mingw-w64.org/downloads/)
> If you have neither of these, a setup guide can be found on [the VSCode website.](https://code.visualstudio.com/docs/cpp/config-mingw)

### *Download*
Clone or download a ZIP of the program from the [main branch.](https://github.com/Bwright257/Procedural-Infinite-World-Generator)
> If you downloaded a ZIP, extract the PIWG-main folder

### *BearLibTerminal Setup*
> BearLibTerminal is used for rendering the demo.
> For more information about the library, visit the [BearLibTerminal GitHub.](https://github.com/cfyzium/bearlibterminal)

Go to the [BearLibTerminal Website.](http://foo.wyrd.name/en:bearlibterminal#download)
- Download the Windows archive
- Extract the folder and locate the **Include/** and **Windows64/** folders
- From the **Include/** folder, find the **C/** folder and move ***BearLibTerminal.h*** to **PIWG-main/Demo/BLT/**
- From the **Windows64/** folder, move ***BearLibTerminal.lib*** to **PIWG-main/Demo/BLT/**
- From the same folder, move ***BearLibTerminal.dll*** to **PIWG-main/**

//FIX// How to compile

## How to use the PIWG

Navigate to where the program was installed, and simply run the ***PIWGdemo.exe*** file found in the root folder

### *Controls*
- ***W*** and the ***Up Arrow*** increase the render/load distance
- ***S*** and the ***Down Arrow*** decrease the render/load distance
- ***A*** and the ***Left Arrow*** decrease the size of each region
- ***D*** and the ***Right Arrow*** increase the size of each region
- ***X*** clears and regenerates the world
- ***Escape*** closes the program
