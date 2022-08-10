# Linux conio



## _"conio.h" implementation for Linux_

This is the implementation of "conio.h" from ms-dos based C compilers for linux/*nix systems

Project was made by casualsnek and rewritten by donarturo11
[https://github.com/casualsnek/linuxconio](https://github.com/casualsnek/linuxconio)

I'm going to make it more compatible with original from Borland.

### Features

- Does not use "curses" library.
- It works on linux with GCC and maybe BSD too


## Installation

Installation is done by copying "conio.h" file to location where compiler looks for header files Or keeping "conio.h" in same directory as your code and using ``` #include "conio.h"``` instead of ```#include <conio.h> ```

On most systems it can be installed by running following commands in terminal emulator

```sh
$ git clone https://github.com/casualsnek/linuxconio
$ cd linuxconio
$ make
```

Then add path of this dir to flags eg.
```sh
$ gcc -I ${PATH_TO_CONIO} -c source.c source.o
$ gcc -I ${PATH_TO_CONIO} -c source2.cpp source2.o
```

Don't forget to link:

```sh
$ gcc *.o -o prog -L ${PATH_TO_CONIO} -lconio
```

### Implemented functions
May not be exact to windows "conio.h" but mostly seems to work in similar ways
- showcursor
- nocursor
- cagxy
- gotox
- gotoxy
- clrscr
- kbhit
- textbackground
- textcolor
- getch
- getche
- clreol
- delline
- cprintf
- cscanf
- cputs
- cgets
- wherex
- wherey
- getpass

You can help by adding support for missing functions or improving the already existing ones.
Please star this repository if you find ths useful


## Credits
[https://github.com/casualsnek/linuxconio](https://github.com/casualsnek/linuxconio)
[donarturo11](https://github.com/donarturo11)

