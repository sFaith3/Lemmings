<p align="center">
  <img width=50% alt="Lemmings-amiga-front-cover" src="https://user-images.githubusercontent.com/14791312/233193545-137030ab-9be8-4545-9a21-d3d78eae2d5d.jpg">
</p>

# Lemmings

A non-exact copy of the video game [Lemmings (1991)](https://en.wikipedia.org/wiki/Lemmings_(video_game)) made with C++, SDL2 and TinyXML for PC at the technical college. This project has been made with Windows. But you should be able to use it in Linux and Mac.


# Getting Started

## Pre-requisites

Before you start, make sure you have an IDE/Compiler such as [Visual Studio](https://visualstudio.microsoft.com/downloads), [Code::Blocks](https://www.codeblocks.org/downloads) or [XCode](https://developer.apple.com/xcode).


# Installation

> **Note** If you are on Windows, you can go to the second step

1. [Hello SDL](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).
2. Download the last version of [SDL2](https://github.com/libsdl-org/SDL/releases), [SDL2_image](https://github.com/libsdl-org/SDL_image/releases) and [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases) corresponding to your operating system (if you are on Windows, see the next).

## Windows

1. Download the `VC.zip` for Visual Studio or the `mingw.tar.gz` for Code::Blocks and MinGW.
2. Put the corresponding libraries in the next folder path (you have to create folders): "Lemmings/Libraries/SDL2-version", "../../SDL2_image-version" and "../../SDL2_mixer-version".
3. Remove "-version" in the folders. Then you wil have the following names: "SDL2", "SDL2_image", "SDL2_mixer".
4. Compile and run the solution in `Debug/Release-x64`.

### Run "Lemmings.exe"
1. Paste in "Lemmings/x64/Debug or Release" the next files:
  - `SDL2.dll` (Lemmings/Libraries/SDL2/lib/x64)
  - `SDL2_image.dll` (../../SDL2_image/lib/x64)
  - `SDL2_mixer.dll` (../../SDL2_mixer/lib/x64)
  - "Art" and "Levels" folders (Lemmings/Assets)
2. Run the executable in "Lemmings/x64/Debug or Release".


# License

[MIT License](./LICENSE)
