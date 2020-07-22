![laigter-banner](https://user-images.githubusercontent.com/46932830/87454669-acbf9300-c5da-11ea-932a-fa4ec67e705f.png)
# Laigter [![Build Status](https://travis-ci.com/azagaya/laigter.svg?branch=master)](https://travis-ci.com/azagaya/laigter)

## Overview

- [Download](https://github.com/azagaya/laigter#download)
- [Contributing](https://github.com/azagaya/laigter#contributing)
- [Screenshots](https://github.com/azagaya/laigter#screenshots)
- [Compiling](https://github.com/azagaya/laigter#compiling)
	- [Linux](https://github.com/azagaya/laigter#compiling-on-linux)
	- [Windows](https://github.com/azagaya/laigter#compiling-on-windows)
	- [MacOS](https://github.com/azagaya/laigter#compiling-on-macos)
- [License](https://github.com/azagaya/laigter#license)

Laigter is a tool that automatically generates maps for dynamic lighting effects
in games. It allows normal, parallax, specular and occlusion map generation.
Also, it allows the user to preview how the effect will look in-game.

Laigter is available in Spanish, English, French, Brazilian-Portuguese, Catalan,
Danish and Greek. It should automatically detect your PC language.

[![Discord Server](https://discordapp.com/api/guilds/582648422167871514/embed.png)](https://discord.gg/88kJqry)

## Download

[**Download from itch.io**](https://azagaya.itch.io/laigter)

[**Download from the Release page**](https://github.com/azagaya/laigter/releases)

## Contributing

The easiest way to contribute is trying Laigter and giving me your feedback.
Please open an issue when you find a bug, and try to specify the way to
reproduce it. Also, suggestions, feature requests, and new ideas are welcome.
Please open issues for all that!

On itch.io, you can download the tool for free, or choose to pay any amount to
support the project.

You can also support the development on Patreon: [![Become a Patron!](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/bePatron?u=19254491)

Or support it by PayPal:
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://paypal.me/PabloFonovich).

Now you can also
[![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/O5O110W22)

If you want to contribute by coding, please contact me and we'll see how we can
work together! Many things are needed. Also, please read the
[Contributing guidelines](CONTRIBUTING.md).

## Screenshots

![specular2](https://user-images.githubusercontent.com/46932830/60845793-cbaf6c00-a1b3-11e9-999b-404670185b4c.png)
![captura-piedra-5](https://user-images.githubusercontent.com/46932830/60845822-dcf87880-a1b3-11e9-879c-e909fbd83469.png)
![captura-piedras-9](https://user-images.githubusercontent.com/46932830/60845823-dcf87880-a1b3-11e9-8772-a42180f3abdc.png)
![specular4](https://user-images.githubusercontent.com/46932830/60845825-dcf87880-a1b3-11e9-9f32-45ccc27abe0f.png)

## Compiling

- [Linux](https://github.com/azagaya/laigter#compiling-on-linux)
- [Windows](https://github.com/azagaya/laigter#compiling-on-windows)
- [MacOS](https://github.com/azagaya/laigter#compiling-on-macos)

### Compiling on Linux

- [Dependencies](https://github.com/azagaya/laigter#getting-the-dependencies)
	- [Debian/Ubuntu](https://github.com/azagaya/laigter#debianubuntu)
	- [Fedora](https://github.com/azagaya/laigter#fedora)
	- [Arch Linux/Manjaro](https://github.com/azagaya/laigter#arch-linuxmanjaro)

- [Compiling and Building](https://github.com/azagaya/laigter#building)

#### Getting the Dependencies

Compiling on Linux is pretty straightforward. The following dependencies are required:

- Qt 5.14 or above (modules Concurrent, Core, Gui, Widgets) and optionally Qt Creator.
- OpenGL development libraries.
- (For Arch Linux/Manjaro: you will also need the VTK and HDF packages)

If you install Qt from the online installer, you don't need to install the qt related packages below.

Install prerequisites by entering the following command in a terminal (depending
on your distribution):



##### Debian/Ubuntu

```bash
sudo apt install qt5-default qt5-qmake libgl1-mesa-dev
```

##### Fedora

```bash
sudo dnf install qt5-devel mesa-libGL-devel
```

##### Arch Linux/Manjaro

```bash
sudo pacman -Sy hdf5 vtk qt5-base
```

#### Get the source

Then get the source either via `git clone`:

```bash
git clone https://github.com/azagaya/laigter
```

or download the package via:

1. Get the package [here](https://github.com/azagaya/laigter/archive/master.zip)
2. Extract the package in your desired location

Then finally `cd` into the laigter directory: `cd laigter`

#### Building

##### Using QT Creator:

That's it, you can now open `laigter.pro` with QtCreator and build or debug Laigter.

##### Using the terminal:

After installing dependencies, you can also build from the terminal with:

```bash
mkdir build
cd build
qmake ../
make -j$(nproc)
```

### Compiling on Windows

#### Getting Qt

For Windows, the steps are similar:

- Install Qt: I strongly discourage the offline installer, use the online installer instead. In the components selection window, you'll need to select Qt Creator under **Qt > Developer and Designer Tools** and the MinGW 64-bit or 32-bit toolchain under **Qt > Developer and Designer Tools > MinGW 7.3.0** and **Qt > Qt 5.14.0 > MinGW 7.3.0**.

Do not choose the MSVC toolchain. If you choose both the 64-bit and 32-bit versions, make sure that only one version is in the system path, otherwise you will have problems compiling.

Tested with Qt 5.14.

#### Get the source

You may get the source cloning the repository. For that, I recommend using (git for windows tool)[https://gitforwindows.org/]. With it, you can clone Laigter:

```bash
git clone https://github.com/azagaya/laigter
```

You may also download the package directly if you don't want to use git:

1. Get the package [here](https://github.com/azagaya/laigter/archive/master.zip)
2. Extract the package in your desired location

#### Building

Open Laigter project in QtCreator installed with the online installer, and run the project. No extra steps should be needed.

#### Deploying the application

If you want to deploy the application for Windows, you will need the
[windeployqt](https://doc.qt.io/qt-5/windows-deployment.html) command. Something
like the following should be enough:

```batch
mkdir .\deploy
windeployqt --dir .\deploy ..\build-laigter-Desktop_Qt_5_14_0_MinGW_32_bit-Release\release\laigter.exe
copy /Y ..\build-laigter-Desktop_Qt_5_14_0_MinGW_32_bit-Release\release\laigter.exe .\deploy\laigter.exe
```

### Compiling on macOS

On Mac, is very similar than on Linux.

#### Prerequisites

First, install Qt. I recommend using the online installer for Mac.

#### Get the source

Then get the source either via `git clone`:

```bash
git clone https://github.com/azagaya/laigter
```

or download the package via:

1. Get the package [here](https://github.com/azagaya/laigter/archive/master.zip)
2. Extract the package in your desired location

Then finally `cd` into the laigter directory: `cd laigter`

#### Building

That's it, you can now open `laigter.pro` with QtCreator and build or debug Laigter.

And thats all the test i could make before i had to return the MAC. 


### Using Laigter with command line

Laigter can be used from the command line with following options:

``` -?, -h, --help ```
Displays help on commandline options.

``` --help-all ```
Displays help including Qt specific options.

``` -v, --version ```
Displays version information.

``` -s, --software-opengl ```
Use software opengl renderer.

``` -g, --no-gui ```
Do not start graphical interface.

``` -d, --diffuse <diffuse texture path> ```
Diffuse texture to load.

``` -n, --normal ```
Generate normals texture.

``` -c, --specular ```
Generate specular texture.

``` -o, --occlusion ```
Generate occlusion teture.

``` -p, --parallax ```
Generate parallax textures.

``` -r, --preset <preset file path> ```
Preset file to use for texture generation.

``` --qmljsdebugger <value> ```
Activcates the QML/JS debugger with the specified port. The value must be of format port:1234[block] "block" makes the application wait for a connection.

``` --platform <platformName[:options]> ```
QPA plugin. See QGuiAplication documentation for available options for eah plugin.

``` --platformpluginpath <path> ```
Path to the platform plugins.

``` --platformtheme <theme> ```
Platform theme.

``` --plguin <plugin> ```
Additional plugins to load. Can be specified multiple times.

``` --qwindowgeometry <geometry> ```
Window geometry for the main windows, using the X11-syntax, lie 100x100+50+50.

``` --qwindowicon <icon> ```
Default window icon.

``` --qwindowtitle <title> ```
Title of the first window.

``` --revers ```
Sets the application's layout direction to Qt:RightToLeft (debugging helper).

``` --session <session> ```
Restores the application from an earlier session.

### Examples for command line

Some basic example for common usages:

``` <PathToLaigter>/laigter.exe --no-gui -d "<pathToDiffuseTexture>.png" -n ```
Exporting a normals texture of the specified diffuse texture using the default profile.

``` <PathToLaigter>/laigter.exe --no-gui -d "<pathToDiffuseTexture>.png" -n -c -o -p ```
Exporting normals, specular, occlusion and parallax textures of the specified diffuse texture using the default profile.

``` <PathToLaigter>/laigter.exe --no-gui -d "<pathToDiffuseTexture>.png" --r "<pathToPresetProfile>" -n -c -o -p ```
Exporting normals, specular, occlusion and parallax textures of the specified diffuse texture using the specified preset profile.#

## License

Copyright (C) 2019 Pablo Ivan Fonovich

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
