# ConsoleArt

- [About](#about)
- [Used libraries](#used-libraries)
- [Testing](#testing)
- [Compilation](#compilation)
- [Project guide](#project-guide)
- [Donate](#donate)

## About

This project started quite some time ago, the initial commit was on 13th of July 2020. This project wasn't meant to have any "form or shape", just project for experimenting in C++, but it was turned into proper C++ project with focus on converting image to ASCII/UNICODE. So now it continues in this flow and it still serves it purpose that it is for learning/experimenting in C++.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console stuff | 🟠 |
| [stb](https://github.com/nothings/stb) | Working with complex picture formats | 🟢 |
| [SDL2](https://www.libsdl.org/) | GUI | 🔴 |
| [tinyfiledialogs](http://tinyfiledialogs.sourceforge.net) | Crossplatform dialogs | 🟢 |
| [ComponentSDL](https://github.com/Riyufuchi/ComponentSDL) | SDL gui components | 🟠 |

## Testing

### Compiled & Tested on

| OS | Compiler |
| :------: | :----------: |
| Ubuntu | g++ 14.2.0 |
| <s>Windows 10</s> | <s>MSVC v143</s> |

## Compilation

  ### Linux

   *For debian based systems*

   ```bash
   # SDL2
   sudo apt install libgl-dev
   sudo apt install libsdl2-dev
   sudo apt install libsdl2-image-dev
   sudo apt install libsdl2-ttf-dev
   ```
  
  *Makefile automatically gets ConsoleLib and compiles it before program*
  
   ```bash
   git clone --branch master --single-branch https://github.com/Riyufuchi/ConsoleArt.git 
   cd ConsoleArt
   make
   ```

## Project guide

- .hpp is used for single file code, that don't have coresponfing .cpp file

## Donate

I'm a 🇨🇿 student, so a few dollars will be enough. If you are planning to use this library in a commercial application, then it would be fair if you would send more, possibly a small share of 5-10% of monthly profits.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
