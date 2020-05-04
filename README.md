# Laigter [![Build Status](https://travis-ci.com/azagaya/laigter.svg?branch=master)](https://travis-ci.com/azagaya/laigter)

![Epic_MegaGrants_Recipient_logo_horizontal](https://user-images.githubusercontent.com/46932830/77976528-a0395800-72d3-11ea-8c3c-4c049350e247.png)

Laigter is a tool that automatically generates maps for dynamic lighting effects
in games. It allows normal, parallax, specular and occlusion map generation.
Also, it allows the user to preview how the effect will look in-game.

Laigter is available in Spanish, English, French, Brazilian-Portuguese, Catalan,
Danish and Greek. It should automatically detect your PC language.

[![Discord Server](https://discordapp.com/api/guilds/582648422167871514/embed.png)](https://discord.gg/88kJqry)

## Download

[**Download from itch.io**](https://azagaya.itch.io/laigter)

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

### Compiling on Linux

#### Getting the Dependencies

Compiling on Linux is pretty straightforward. The following dependencies are required:

- Qt 5 (modules Concurrent, Core, Gui, Widgets) and optionally Qt Creator.
- OpenCV.
- OpenGL development libraries.
  
Install prerequisites by entering the following command in a terminal (depending
on your distribution):

##### Debian/Ubuntu

```bash
sudo apt install qt5-default qt5-qmake libopencv-dev libgl1-mesa-dev
```

##### Fedora

```bash
sudo dnf install qt5-devel opencv-devel mesa-libGL-devel
```

#### Arch Linux/Manjaro

```bash
sudo pacman -Sy opencv hd5 vtk qt5-base
```

#### Building

Using QT Creator:

	That's it, you can now open `laigter.pro` with Qt Creator and build or debug Laigter.

Using the terminal:

	After installing dependencies, you can also build from the terminal with:

	```bash
	mkdir build
	cd build
	qmake ../
	make -j$(nproc)
	```

### Compiling on Windows

For Windows, unfortunately, there are more steps to be done.

- Install Qt: I strongly discourage the offline installer, use the online
  installer instead. In the components selection window, you'll need to select
  Qt Creator under **Qt > Developer and Designer Tools** and the MinGW 64-bit or
  32-bit toolchain under **Qt > Developer and Designer Tools > MinGW 7.3.0**
  and **Qt > Qt 5.13.0 > MinGW 7.3.0**. Do not choose the MSVC toolchain. If you
  choose both the 64-bit and 32-bit versions, make sure that only one version is
  in the system path, otherwise you will have problems compiling. Tested with Qt
  5.11, 5.12 and 5.13.
- Install CMake: [download](https://cmake.org/download/) and install CMake.
- Install OpenCV:
  [download](https://github.com/opencv/opencv/releases/tag/3.2.0) and compile
  OpenCV 3.2. It **must** be version 3.2, it cannot be any other version; be
  warned.

Once you have installed CMake and downloaded OpenCV 3.2, follow
[this tutorial](https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows).
But before clicking **Generate** in the CMake GUI, be sure to uncheck
`BUILD_opencv_python3` in case you have this flag and it is checked. I could not
compile until I unchecked this. Also change `EXECUTABLE_OUTPUT_PATH` to
`C:\opencv-build\install\x86\mingw\bin` which is the path set on `laigter.pro`
(or you could change the path on your `laigter.pro` to match your
`EXECUTABLE_OUTPUT_PATH`).

After several minutes, OpenCV compilation should finish. If it finished
successfully, you can open `laigter.pro` in Qt Creator, compile and run it.

#### Deploying the application

If you want to deploy the application for Windows, you will need the
[windeployqt](https://doc.qt.io/qt-5/windows-deployment.html) command. Something
like the following should be enough:

```batch
mkdir .\deploy
windeployqt --dir .\deploy ..\build-laigter-Desktop_Qt_5_13_0_MinGW_32_bit-Release\release\laigter.exe
copy /Y ..\build-laigter-Desktop_Qt_5_13_0_MinGW_32_bit-Release\release\laigter.exe .\deploy\laigter.exe
```

If for some reason the OpenCV libraries weren't copied, copy them as well:

```batch
copy /Y C:\opencv-build\install\x86\mingw\bin\libopencv_core320.dll .\deploy\
copy /Y C:\opencv-build\install\x86\mingw\bin\libopencv_imgproc320.dll .\deploy\
```

### Compiling on macOS

I don't have a Mac, but a few tests I made on a friend's computer made me arrive
to the following (maybe incomplete) steps:

- Install [Homebrew](https://brew.sh/), then install pkg-config using
  `brew install pkg-config`.
- Install Qt and Qt Creator: online installer is recommended.
- Install OpenCV: on macOS, like on Linux, I could only install OpenCV4.
  After installing, you should append the path to the OpenCV includes to the
  `INCLUDEPATH` build variable in Qt Creator (or edit `laigter.pro` manually to do so).
  I think it was: `/usr/local/Cellar/opencv/4.0.1/include/opencv4/`
- If pkg-config can't find opencv, add a variable `PKG_CONFIG_PATH` to the
  project environment, with the path to `opencv.pc`.

And that's all the test I could make before I had to return the Mac.

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
