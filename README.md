# ConsoleArt

- [About](#about)
- [Used libraries](#used-libraries)
- [Documentation](#documentation)
- [Compilation](#compilation)
- [Project guide](#project-guide)
- [Donate](#donate)

## About

This application works with images and supports even multi-page and animated ones.

Highlighted features:

* Pack images into .dcx
* Convert images to ascii
* Apply some filters
* Apply signatures to images
* Split gif into individual frames
* And more...

### Project history

This project started quite some time ago, the initial commit was on 13th of July 2020. This project wasn't meant to have any "form or shape", just project for experimenting in C++, but it was turned into proper C++ project with focus on converting image to ASCII/UNICODE. So now it continues in this flow and it still serves it purpose that it is for learning/experimenting in C++.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console stuff | ✅ |
| [stb](https://github.com/nothings/stb) | Working with complex picture formats | ✅ |
| [SDL2](https://www.libsdl.org/) | GUI | ✅ |
| [tinyfiledialogs](http://tinyfiledialogs.sourceforge.net) | Crossplatform dialogs | ✅ |
| [ComponentSDL](https://github.com/Riyufuchi/ComponentSDL) | SDL GUI components | ✅ |

## Documentation

 ```bash
    # Make sure you have LaTeX installed

    # On Debian/Ubuntu
    sudo apt install texlive-full

    # On macOS
    brew install --cask mactex

    # On Windows
    # Get the installer from https://www.tug.org/texlive/windows.html

    # Get the repository - how to is in section Git and Make
    # Build the PDF documentation
    # (Makefile runs LaTeX twice so Table of Contents and references are correct)
    make docs
   ```

## Compilation

### Compiled & Tested on

| OS | Compiler |
| :------: | :----------: |
| Ubuntu | g++ 15.2.0 |
| Windows 10 | MSVC 19.50.35719.0 |

### CMake

   ```bash
   git clone https://github.com/Riyufuchi/ConsoleArt.git
   cd ConsoleArt
   # CMake
   cmake -B build -S .
   cmake --build build --config Release
   ```

## Project guide

- .hpp is used for single file code, that don't have coresponfing .cpp file

## Donate

I'm a 🇨🇿 student, so a few dollars will be enough. If you are planning to use this library in a commercial application, then it would be fair if you would send more, possibly a small share of 5-10% of monthly profits.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
