<p align="center">
  <img width=50% alt="Lemmings-amiga-front-cover" src="https://user-images.githubusercontent.com/14791312/233193545-137030ab-9be8-4545-9a21-d3d78eae2d5d.jpg">
</p>

# Lemmings

A non-exact copy of the video game [Lemmings (1991)](https://en.wikipedia.org/wiki/Lemmings_(video_game)) made with C++, SDL2 and TinyXML for PC at the technical college.

https://user-images.githubusercontent.com/14791312/233218129-b5980646-b39e-4916-a688-f0fce6d1565b.mp4


# Getting Started

This project has been made with Windows. But you should be able to use it on Linux and Mac.

## Pre-requisites

Before you start, make sure you have an IDE/Compiler such as [Visual Studio](https://visualstudio.microsoft.com/downloads), [Code::Blocks](https://www.codeblocks.org/downloads) or [XCode](https://developer.apple.com/xcode).


# Installation

> **Note** If you are on Windows, you can skip the first step

1. [Hello SDL](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).
2. Download the last version of [SDL2](https://github.com/libsdl-org/SDL/releases), [SDL2_image](https://github.com/libsdl-org/SDL_image/releases) and [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases) corresponding to your operating system.

## Windows

1. Download the `VC.zip` for Visual Studio or the `mingw.tar.gz` for Code::Blocks and MinGW.
2. Put the corresponding libraries in the next folder path (you have to create folders): "Lemmings/Libraries/SDL2-version", "../../SDL2_image-version" and "../../SDL2_mixer-version".
3. Remove "-version" in the folders. Then you wil have the following names: "SDL2", "SDL2_image", "SDL2_mixer".
4. Paste in "Lemmings/x64/Debug or Release" the next `.dll`:
    * `SDL2.dll` (Lemmings/Libraries/SDL2/lib/x64)
    * `SDL2_image.dll` (../../SDL2_image/lib/x64)
    * `SDL2_mixer.dll` (../../SDL2_mixer/lib/x64)
5. Compile and run the solution in `Debug/Release-x64`.

### Run "Lemmings.exe"
1. Paste in "Lemmings/x64/Debug or Release" the next files: "Art" and "Levels" folders (Lemmings/Assets)
2. Run the executable in "Lemmings/x64/Debug or Release".


# Authors

| [<img src="https://user-images.githubusercontent.com/14791312/233219860-32856bfe-bfa3-4a68-b0c4-f4d7f6ab0730.png" width=115><br><sub>Samuel Balcells</sub>](https://github.com/sFaith3) | [<img src="https://user-images.githubusercontent.com/14791312/233219903-417078c4-c93e-4ad5-bdb1-4fcdafe6b293.jpg" width=115><br><sub>Víctor Amorós</sub>](https://github.com/Viamos)
| :---: | :---: |


# License

[MIT License](./LICENSE)
