# Tetris clone

Created: April 3, 2022 11:01 AM

# Playing

## Available platforms :

[https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

The game is available on Windows, the DLLs to play are already in the `build` folder.

| Necessary dynamic libraries : |
| --- |
| SDL2.dll |
| SDL2_image.dll |
| zlib1.dll |
| libpng16-16.dll |

[https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)

To play on Ubuntu (or any graphic Linux distro), you need the `SDL2` and `SDL2_image` packages that you can easily download with `apt-get` . The executable is in the `build/` folder or you can compile the game yourself (in that case, you will probably need the `-dev` versions of the SDL2 packages).

You can then launch the game (from the `build/` directory).

## Why did I want to create my own Tetris?

I wanted to recreate Tetris, that was a sort of technical challenge I was giving myself.

I kinda knew that there were gonna some difficulties I would have to face, and that’s the reason why I tried it.

## Which tools did I choose?

[https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

I chose to use C++ as I already had some experience with SDL (a C library) but I wanted to have the power of OOP to create my game. C++ was then the perfect candidate.

### By Maxooz