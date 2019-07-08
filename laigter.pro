#Laigter: an automatic map generator for lighting effects.
#Copyright (C) 2019  Pablo Ivan Fonovich
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <https://www.gnu.org/licenses/>.
#Contact: azagaya.games@gmail.com

#-------------------------------------------------
#
# Project created by QtCreator 2019-02-20T15:10:05
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = laigter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += core ui c++11

SOURCES += \
    gui/presetsmanager.cpp \
        main.cpp \
        mainwindow.cpp \
    src/imageloader.cpp \
    src/imageprocessor.cpp \
    src/openglwidget.cpp \
    gui/nbselector.cpp

HEADERS += \
    gui/presetsmanager.h \
        mainwindow.h \
    src/imageloader.h \
    src/imageprocessor.h \
    src/openglwidget.h \
    gui/nbselector.h

FORMS += \
    gui/presetsmanager.ui \
        mainwindow.ui \
    gui/nbselector.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

DISTFILES += \
    acknowledgements.html \
    license.html

TRANSLATIONS = laigter_es.ts \
               laigter_en.ts

RESOURCES += \
    shaders.qrc \
    images.qrc \
    translations.qrc \
    icons.qrc

win32: LIBS += C:\opencv-build\install\x86\mingw\bin\libopencv_core320.dll
win32: LIBS += C:\opencv-build\install\x86\mingw\bin\libopencv_imgproc320.dll
win32: LIBS += C:\opencv-build\install\x86\mingw\bin\libopencv_imgcodecs320.dll

win32: INCLUDEPATH += C:\opencv\opencv\build\include

win32: RC_ICONS = icons\laigter-icon.ico


