# Laigter

Laigter is a tool that automatically generates maps for dynamic lighting effects in games. It allows normal, parallax, specular and occlusion map generation. Also, it allows the user to preview how the effect will look ingame.
You can get binaries from itch.io: https://azagaya.itch.io/laigter

Laigter is available in english and spanish. It should automatically detect your PC language.

## Prerequisites

You need Qt framework (online installer is the recommended way to get it) and opencv 3.2 or above. Opencv is not meant for tools like this, but is the one i'm used to. In the future it would be nice to do without it.

## Contributing

Easiest way to contribute is trying laigter and giving me your feedback. Please open an issue when you find a bug, and try to specify the way to reproduce it.
Also, suggestions, feature requests, and new ideas are welcome. Please open issues for all that!

On itch.io, you can download the tool for free, or choose to pay any amount to support the project.

You can also support the development on [patreon](https://www.patreon.com/azagaya),
or support it by paypal: [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://paypal.me/PabloFonovich).

Now you can also [![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/O5O110W22)

If you wan't to contribute by coding, please contact me and we will see how can we work together! Many things are needed.

## Screenshots

![specular2](https://user-images.githubusercontent.com/46932830/60845793-cbaf6c00-a1b3-11e9-999b-404670185b4c.png)
![captura-piedra-5](https://user-images.githubusercontent.com/46932830/60845822-dcf87880-a1b3-11e9-879c-e909fbd83469.png)
![captura-piedras-9](https://user-images.githubusercontent.com/46932830/60845823-dcf87880-a1b3-11e9-8772-a42180f3abdc.png)
![specular4](https://user-images.githubusercontent.com/46932830/60845825-dcf87880-a1b3-11e9-9f32-45ccc27abe0f.png)

## Compiling on Linux

Compiling on linux is pretty straightforward. Just use your package manager to install prerequisites:

* Qt and Qt creator: from package manager or online installer.
* OpenCV: libopencv-dev from package manager
* OpenGL libray: libgl1-mesa-dev from package manager.

Thats it, you can open the .pro file with qtcreator and build or debug laigter.

## Compiling on Windows

For windows, unfortunately, there are more steps to be done.

* Install Qt: I strongly discourage the offline installer, use the online installer instead. In the components selection window you will need to select  qt creator under "qt >> developer and designers tools" and the mingw 7.3 32bit or 64bit toolchain under "qt >> developer and designers tools >> mingw 7.3.0" and "qt >> qt 5.13.0 >> mingw 7.3.0". Do not choose the msvc toolchain. If you choose both the 32 and 64 bit versions, make sure that only one version is in the system path, otherwise you will have problems compiling. Tested with Qt 5.11, 5.12 and 5.13.

* Install cmake: [download](https://cmake.org/download/) and install cmake.

* Install opencv: [download](https://github.com/opencv/opencv/releases/tag/3.2.0) and compile opencv 3.2. It must be version 3.2, it cannot be any other version; be warned.

Once you have installed cmake and downloaded opencv 3.2, folow this tutorial here:

https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows

But before clicking "generate" on cmake-gui, be sure to uncheck BUILD_opencv_python3 in case you have this flag and it is checked. I could not compile until I unchecked this. And also change EXECUTABLE_OUTPUT_PATH to C:\opencv-build\install\x86\mingw\bin wich is the path set on laigter.pro (or you could change the path on your laigter.pro to match your EXECUTABLE_OUTPUT_PATH).

After several minutes, fortunately your compilation will be sucessfull. If that's the case, you can open the project on qt-creator, compile and run it. 

* Deploy application: Once you want to deploy the application for windows, you will need the windeployqt command. Something like the following should be enough:

```
mkdir .\deploy
windeployqt --dir .\deploy ..\build-laigter-Desktop_Qt_5_13_0_MinGW_32_bit-Release\release\laigter.exe
copy /Y ..\build-laigter-Desktop_Qt_5_13_0_MinGW_32_bit-Release\release\laigter.exe .\deploy\laigter.exe
```

If for some reason the opencv libraries do not get copied, copy them also
```
copy /Y C:\opencv-build\install\x86\mingw\bin\libopencv_core320.dll .\deploy\
copy /Y C:\opencv-build\install\x86\mingw\bin\libopencv_imgproc320.dll .\deploy\
```

## Compiling on MAC

I don't have a MAC, but a few tests i made on a friend's computer made me arrive to the following (maybe incomplete) steps:

* Install pkg-config

* Install Qt and Qt Creator: online installer is recommended.

* Install opencv: in mac, like in linux, i could only install opencv4. After installing, you should add to includepaht in Qt Creator the path to opencv (i think it was: /usr/local/Cellar/opencv/4.0.1/include/opencv4/)

* If pkg-config does not find opencv, add a variable PKG_CONFIG_PATH to the project environment, with the path to opencv.pc

And thats all the test i could make before i had to return the MAC. 


## Using Laigter with command line

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
Exporting normals, specular, occlusion and parallax textures of the specified diffuse texture using the specified preset profile.