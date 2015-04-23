#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T00:22:04
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = colors
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    PaletteModel.cpp \
    PaletteEditor.cpp \
    AbstractColorEditor.cpp \
    ColorEditor.cpp \
    RgbaColorEditor.cpp \
    ColorItemDelegate.cpp \
    SpinBoxSlider.cpp \
    HsvColorEditor.cpp

HEADERS  += MainWindow.hpp \
    PaletteModel.hpp \
    PaletteEditor.hpp \
    AbstractColorEditor.hpp \
    ColorEditor.hpp \
    RgbaColorEditor.hpp \
    ColorItemDelegate.hpp \
    SpinBoxSlider.hpp \
    HsvColorEditor.hpp

FORMS    +=



unix|win32: LIBS += -L$$PWD/../../../ -locto

INCLUDEPATH += $$PWD/../../../includes
DEPENDPATH += $$PWD/../../../includes

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../octo.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../../libocto.a
