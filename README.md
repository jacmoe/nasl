
    /*
    *   This file is part of the
    * ███╗   ██╗ █████╗ ███████╗██╗     
    * ████╗  ██║██╔══██╗██╔════╝██║     
    * ██╔██╗ ██║███████║███████╗██║     
    * ██║╚██╗██║██╔══██║╚════██║██║     
    * ██║ ╚████║██║  ██║███████║███████╗
    * ╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚══════╝
    *   project : https://github.com/jacmoe/nasl
    *
    *   Copyright 2017 Jacob Moen
    *
    */

# nasl
Nasl is Not A Sixteen-bit Library

## Requirements

* CMake 2.8+
* [Glfw3][glfw]
* Glew (Optionally)

## Using

* [MY-BASIC][mybasic]
* [Nuklear][nuklear]
* [stb_image][stbimage]

## Based on

* [Herrecito's 2.5D Raycaster engine][engine]

## Using code from

* [David Brakeen - 256-Color VGA Programming in C][brakeen]


## How to build

    mkdir build
    cd build
    ccmake ..
    make -j4

## Screenshots

![Commodore 64 Palette][palette]
![Misc Tests][misc]



[stbimage]: https://github.com/nothings/stb "stb library"
[mybasic]: https://github.com/paladin-t/my_basic "MY-BASIC"
[nuklear]: https://github.com/vurtun/nuklear "Nuklear"
[glfw]: http://www.glfw.org/ "GLFW"
[palette]: https://github.com/jacmoe/nasl/raw/master/palette.jpg "Commodore 64 Palette"
[misc]: https://github.com/jacmoe/nasl/raw/master/misc.jpg "Misc Tests"
[engine]: https://github.com/herrecito/engine "Herrecito's 2.5D Raycaster engine"
[brakeen]: http://www.brackeen.com/vga/index.html "David Brakeen - 256-Color VGA Programming in C"
