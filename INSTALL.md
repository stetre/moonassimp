
## How to install MoonAssimp

### On Ubuntu

Install Lua as described in the installation instructions for 
[MoonFLTK](https://github.com/stetre/moonfltk/).

Install Assimp:

```sh
$ sudo apt-get install libassimp-dev
```

Download MoonAssimp's [latest release](https://github.com/stetre/moonassimp/releases)
(e.g. moonassimp-0.1.tar.gz).

```sh
$ tar -zxpvf moonassimp-0.1.tar.gz
$ cd moonassimp-0.1
moonassimp-0.1$ make
moonassimp-0.1$ sudo make install
```

### On Windows with MSYS2/MinGW

Set up the MSYS2/MinGW environment and install Lua as described in the installation 
instructions for [MoonFLTK](https://github.com/stetre/moonfltk/).

Install Assimp:

```sh
$ pacman -S mingw-w64-i686-assimp      # (32-bit)
$ pacman -S mingw-w64-x86_64-assimp    # (64-bit)
```

Download MoonAssimp's [latest release](https://github.com/stetre/moonassimp/releases)
(e.g. moonassimp-0.1.tar.gz).

```sh
$ tar -zxpvf moonassimp-0.1.tar.gz
$ cd moonassimp-0.1
moonassimp-0.1$ make platform=mingw
moonassimp-0.1$ make install platform=mingw
```

