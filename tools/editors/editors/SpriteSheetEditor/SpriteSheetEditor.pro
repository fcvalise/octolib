#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T00:43:42
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG	+= c++11

TARGET = "Sprite Sheet Editor"
TEMPLATE = app

ICON = sprite_sheet_editor.icns

SOURCES += main.cpp\
        MainWindow.cpp \
    SpriteSheetEditor.cpp \
    SpriteSheetView.cpp \
    SpriteSheetScene.cpp \
    RectangleModel.cpp \
    AbstractSpriteSheetCommand.cpp \
    RectangleListView.cpp \
    CommandManager.cpp \
    PointerSpriteSheetCommand.cpp \
    TileControlWidget.cpp \
    RectangleSpriteSheetCommand.cpp \
    GenerateRectangleDialog.cpp \
    TilePreview.cpp

HEADERS  += MainWindow.hpp \
    SpriteSheetEditor.hpp \
    SpriteSheetView.hpp \
    SpriteSheetScene.hpp \
    RectangleModel.hpp \
    AbstractSpriteSheetCommand.hpp \
    RectangleListView.hpp \
    CommandManager.hpp \
    PointerSpriteSheetCommand.hpp \
    TileControlWidget.hpp \
    RectangleSpriteSheetCommand.hpp \
    GenerateRectangleDialog.hpp \
    TilePreview.hpp



# CommonWidgets
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CommonWidgets/release/ -lCommonWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CommonWidgets/debug/ -lCommonWidgets
else:unix: LIBS += -L$$OUT_PWD/../CommonWidgets/ -lCommonWidgets

INCLUDEPATH += $$PWD/../CommonWidgets
DEPENDPATH += $$PWD/../CommonWidgets

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonWidgets/release/libCommonWidgets.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonWidgets/debug/libCommonWidgets.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonWidgets/release/CommonWidgets.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CommonWidgets/debug/CommonWidgets.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CommonWidgets/libCommonWidgets.a

# Octolib
unix|win32: LIBS += -L$$PWD/../../../../ -locto

INCLUDEPATH += $$PWD/../../../../includes
DEPENDPATH += $$PWD/../../../../includes

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../octo.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../libocto.a

RESOURCES += \
    Resources.qrc
