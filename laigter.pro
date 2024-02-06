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

QT       += core gui widgets network

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

QMAKE_CXXFLAGS_RELEASE *= -O3

!macx {
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -lgomp -lpthread
}

SOURCES += \
	gui/about_dialog.cpp \
	gui/exportwidget.cpp \
	gui/frame_splitter.cpp \
	gui/language_selector.cpp \
	gui/presets_manager.cpp \
	gui/remove_plugin_dialog.cpp \
	gui/widgets/animation_dock.cpp \
	gui/widgets/animationcreator.cpp \
	gui/widgets/slider.cpp \
	gui/widgets/slider2.cpp \
	gui/widgets/sprite_properties_dock.cpp \
	gui/widgets/themeselector.cpp \
	main.cpp \
	main_window.cpp \
	src/image_loader.cpp \
	src/image_processor.cpp \
	src/light_source.cpp \
	src/open_gl_widget.cpp \
	gui/nb_selector.cpp \
	src/project.cpp \
	src/sprite.cpp \
	src/texture.cpp \
	thirdparty/zip.c

HEADERS += \
	gui/exportwidget.h \
	gui/frame_splitter.h \
	gui/widgets/animation_dock.h \
	gui/widgets/animationcreator.h \
	gui/widgets/slider.h \
	gui/about_dialog.h \
	gui/language_selector.h \
	gui/presets_manager.h \
	gui/remove_plugin_dialog.h \
	gui/widgets/slider.h \
	gui/widgets/slider2.h \
	gui/widgets/sprite_properties_dock.h \
	gui/widgets/themeselector.h \
	main_window.h \
	src/brush_interface.h \
	src/image_loader.h \
	src/image_processor.h \
	src/light_source.h \
	src/open_gl_widget.h \
	gui/nb_selector.h \
	src/project.h \
	src/sprite.h \
	src/texture.h \
	thirdparty/CImg.h \
	thirdparty/miniz.h \
	thirdparty/zip.h

FORMS += \
	gui/about_dialog.ui \
	gui/exportwidget.ui \
	gui/frame_splitter.ui \
	gui/language_selector.ui \
	gui/presets_manager.ui \
	gui/remove_plugin_dialog.ui \
	gui/widgets/animation_dock.ui \
	gui/widgets/animationcreator.ui \
	gui/widgets/sprite_properties_dock.ui \
	gui/widgets/themeselector.ui \
	main_window.ui \
	gui/nb_selector.ui

unix{

    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = dist/laigter.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    iconfiles.files = dist/laigter.png
    iconfiles.path = $$PREFIX/share/icons/hicolor/256x256/apps/
    appdatafiles.files = dist/laigter.appdata.xml
    appdatafiles.path = $$PREFIX/share/metainfo/
	mimetypefiles.files = dist/x-laigter-project.xml
    mimetypefiles.path = $$PREFIX/share/mime/packages/

    INSTALLS += target
    INSTALLS += shortcutfiles
    INSTALLS += iconfiles
    INSTALLS += appdatafiles
    INSTALLS += mimetypefiles
}

DISTFILES += \
	ACKNOWLEDGEMENTS \
	LICENSE

TRANSLATIONS = translations/laigter_da.ts \
	translations/laigter_es.ts \
	translations/laigter_en.ts \
	translations/laigter_fr.ts \
	translations/laigter_pt_BR.ts \
	translations/laigter_ca_ES.ts \
        translations/laigter_el.ts \
        translations/laigter_tr.ts \
        translations/laigter_jp.ts \
        translations/laigter_de.ts \
        translations/laigter_zh_CN.ts

LANGUAGES = da\
	en \
	es \
	fr \
	pt_BR \
	ca_ES \
        el \
        tr \
        jp \
        de \
        zh_CN

# parameters: var, prepend, append
defineReplace(prependAll) {
	for(a,$$1):result += $$2$${a}$$3
		return($$result)
}

TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/translations/laigter_, .ts)

TRANSLATIONS_FILES =

qtPrepareTool(LRELEASE, lrelease)
win32 {
  LRELEASE=$$clean_path(LRELEASE)
  LRELEASE=$$replace(LRELEASE, \', )
}
for(tsfile, TRANSLATIONS) {
        qmfile = $$tsfile
        qmfile ~= s,.ts$,.qm,
        qmdir = $$dirname(qmfile)
        !exists($$qmdir) {
                mkpath($$qmdir)|error("Aborting.")
        }

        command = $$LRELEASE -removeidentical $$tsfile -qm $$qmfile
        win32 {
#          command = $$replace(command, /, \\))
        }
        system($$command)|error("Failed to run: $$command")
        TRANSLATIONS_FILES += $$qmfile
}

RESOURCES += \
	shaders.qrc \
	images.qrc \
	styles.qrc \
	translations.qrc \
	icons.qrc


win32: RC_ICONS = icons\laigter_icon.ico
mac: ICON = icons/laigter_icon.icns

