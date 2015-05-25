#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T05:17:37
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG	+= c++11

TARGET = "Wheel Editor"

TEMPLATE = app
ICON = wheel_editor.icns

SOURCES += main.cpp\
        MainWindow.cpp \
    WheelEditor.cpp \
    OffsetEditor.cpp \
    AddOffsetsDialog.cpp

HEADERS  += MainWindow.hpp \
    WheelEditor.hpp \
    OffsetEditor.hpp \
    AddOffsetsDialog.hpp

RESOURCES += \
    Resources.qrc

FORMS += \
    AddOffsetsDialog.ui

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

