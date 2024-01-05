# Procedural Infinite World Generator

![PIWG Fullscreen Generation Sample](https://github.com/Bwright257/Procedural-Infinite-World-Generator/blob/main/Samples/PIWG-Full.png)

## How it works
The *Procedural Infinite World Generator*, or **PIWG** for short, is a program which simultaneously creates procedurally generated two dimensional landscapes and dynamically loads and unloads sections of the world. These sections, called *regions*, are uniform partitions of the world which each store an array of individual tiles. The algorithm used for the generation of the tiles within these regions is a derivation of *cellular automata*, which comes from the popular *Conway's Game of Life*. Loading and unloading of individual regions is determined by the location of the so-called *active region* and the *render distance* around that region. Regions that set to be loaded in are first populated by random noise and then conjoined with the other *to-be-loaded* regions in order for the cellular automaton to be most effective. Alongside this, the regions which fall out of the *render distance* are unloaded so that the program remains efficient.

## Options
1. Download and run the latest release (*PIWGv_._.zip*) from [the releases page.](https://github.com/Bwright257/Procedural-Infinite-World-Generator/releases)
   > [How to use the PIWG demo.](https://github.com/Bwright257/Procedural-Infinite-World-Generator?tab=readme-ov-file#how-to-use-the-piwg-demo)
3. Install and compile the program on your own by following the steps below.

## Installation and Setup

### *Supported Platforms*
- Windows

### *Requisites*
- [Visual Studio Code](https://code.visualstudio.com/download)
- [MinGW-64](https://www.mingw-w64.org/downloads/)
> If you have neither of these, a setup guide can be found on [the VSCode website.](https://code.visualstudio.com/docs/cpp/config-mingw)

### *Download*
Clone or download a ZIP of the program from the [main branch.](https://github.com/Bwright257/Procedural-Infinite-World-Generator)
> If you downloaded a ZIP, extract the Procedural-Infinite-World-Generator-main folder.

### *BearLibTerminal Setup*
> BearLibTerminal is used for rendering the demo.
> For more information about the library, visit the [BearLibTerminal GitHub.](https://github.com/cfyzium/bearlibterminal)

Go to the [BearLibTerminal Website.](http://foo.wyrd.name/en:bearlibterminal#download)
- Download the Windows archive
- Extract the folder and locate the **Include/** and **Windows64/** folders
- From the **Include/** folder, find the **C/** folder and move ***BearLibTerminal.h*** to **PIWG-main/Demo/BLT/**
- From the **Windows64/** folder, move ***BearLibTerminal.lib*** to **Procedural-Infinite-World-Generator-main/Demo/BLT/**
- From the same folder, move ***BearLibTerminal.dll*** to **Procedural-Infinite-World-Generator-main/**

### *Compiling*
1. Open the folder ***Procedural-Infinite-World-Generator-main*** in Visual Studio Code
2. While in Visual Studio Code, press ***Ctrl + Shift + B*** to compile the program

## How to use the PIWG demo

### Options
- Navigate to where the program was installed, and simply run the ***PIWGdemo.exe*** file found in the root folder.
- Open a terminal in the folder containing the executable and run ***./PIWGdemo.exe***

### *Controls*
- Move your ***Mouse*** to load in regions around the cursor
- ***W*** and the ***Up Arrow*** increase the render/load distance
- ***S*** and the ***Down Arrow*** decrease the render/load distance
- ***D*** and the ***Right Arrow*** increase the size of each region
- ***A*** and the ***Left Arrow*** decrease the size of each region
- ***X*** clears and regenerates the world
- ***Escape*** closes the program

## The PIWG Presentation

![PIWG GIF](https://github.com/Bwright257/Procedural-Infinite-World-Generator/blob/main/Samples/IPWG-Demo.gif)
##
![PIWG Small Sample 1](https://github.com/Bwright257/Procedural-Infinite-World-Generator/blob/main/Samples/PIWG-25SizeRegion1.png)
##
![PIWG Small Sample 2](https://github.com/Bwright257/Procedural-Infinite-World-Generator/blob/main/Samples/PIWG-25SizeRegion2.png)
