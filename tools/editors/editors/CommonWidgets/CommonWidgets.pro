#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T17:01:12
#
#-------------------------------------------------

QT += core widgets

TARGET = CommonWidgets
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

DEFINES += "GIT_COMMIT_SHORT=\"\\\"$$system(git rev-parse --short HEAD)\\\"\""
DEFINES += "GIT_BRANCH=\"\\\"$$system(git rev-parse --abbrev-ref HEAD)\\\"\""

SOURCES += \
    HsvColorEditor.cpp \
    RgbaColorEditor.cpp \
    SpinBoxSlider.cpp \
    ColorEditor.cpp \
    AbstractColorEditor.cpp \
    Document.cpp \
    AboutDialog.cpp \
    RecentFileMenu.cpp \
    ColorItemDelegate.cpp \
    PaletteModel.cpp \
    WheelModel.cpp \
    ColorListPreView.cpp \
    HueOffset.cpp \
    ComplementaryOffsetDialog.cpp \
    SquareOffsetDialog.cpp \
    TriadOffsetDialog.cpp \
    AnaloguousOffsetDialog.cpp \
    InteractiveGraphicsScene.cpp \
    AbstractCommand.cpp \
    CommandManager.cpp

HEADERS += \
    SpinBoxSlider.hpp \
    ColorEditor.hpp \
    RgbaColorEditor.hpp \
    HsvColorEditor.hpp \
    AbstractColorEditor.hpp \
    Document.hpp \
    AboutDialog.hpp \
    RecentFileMenu.hpp \
    ColorItemDelegate.hpp \
    PaletteModel.hpp \
    WheelModel.hpp \
    ColorListPreView.hpp \
    HueOffset.hpp \
    SquareOffsetDialog.hpp \
    TriadOffsetDialog.hpp \
    ComplementaryOffsetDialog.hpp \
    AnaloguousOffsetDialog.hpp \
    InteractiveGraphicsScene.hpp \
    AbstractCommand.hpp \
    CommandManager.hpp

FORMS += \
    SquareOffsetDialog.ui \
    AnaloguousOffsetDialog.ui \
    ComplementaryOffsetDialog.ui \
    TriadOffsetDialog.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# Octolib
unix|win32: LIBS += -L$$PWD/../../../../ -locto

INCLUDEPATH += $$PWD/../../../../includes
DEPENDPATH += $$PWD/../../../../includes

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../octo.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../libocto.a

