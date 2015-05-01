#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T17:01:12
#
#-------------------------------------------------

QT       += widgets

TARGET = CommonWidgets
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

SOURCES += \
    HsvColorEditor.cpp \
    RgbaColorEditor.cpp \
    SpinBoxSlider.cpp \
    ColorEditor.cpp \
    AbstractColorEditor.cpp \
    Document.cpp \
    AboutDialog.cpp \
    RecentFileMenu.cpp

HEADERS += \
    SpinBoxSlider.hpp \
    ColorEditor.hpp \
    RgbaColorEditor.hpp \
    HsvColorEditor.hpp \
    AbstractColorEditor.hpp \
    Document.hpp \
    AboutDialog.hpp \
    RecentFileMenu.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
