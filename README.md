# Space Invaders Clone

https://github.com/user-attachments/assets/e1f8f65e-2659-44a8-a922-8faf94de8aed

This project is a modern take on the classic Space Invaders arcade game, built from scratch in C++ using the raylib graphics library. The build process is managed with CMake, ensuring portability and ease of compilation across platforms.

The game features:

- Core mechanics faithfully inspired by the original Space Invaders
- Clean and modular C++ code structure
- Real-time rendering and input handling via raylib
- Basic sound effects and sprite-based visuals
- Cross-platform build system using CMake

This project serves as a fun exploration of game development fundamentals, graphics rendering, and system architecture using modern C++ practices.

## Pre-requisites

### CMake

Before building the project you need to have CMake installed in your machine. You can use `brew install cmake` command or you can go to https://cmake.org/download/ and download the latest version for your machine OS. We recommend installing via first option but if you go with the second option after running the installer open the CMake app, go to Tools/How To Install For Command Line Use, and follow the instructions to finish installation.

To build the application on Windows you will need Visual Studio with Clang support. On the Visual Studio Installer app, make sure you install the following:

* Workloads
    * Desktop development with C++
* Individual components
    * C++ Clang Compiler for Windows
    * C++ Clang-cl for v143 build tools (x64/x86)

### Clang-format

macOS
```
brew install clang-format
```

Windows

You can get it as part of the LLVM compiler or Clang Compiler build for Windows. You also can try to install it with npm
```
npm install -g clang-format
```

## How to build project and open IDE? (recommended)

macOS
```
sh Scripts/macOS/build_xcode.sh
```

Windows
```
start Scripts/windows/build_vs22.bat
```

## How to format code?

macOS
```
sh Scripts/macOS/formatter.sh
```

Windows
```
start Scripts/windows/formatter.bat
```
