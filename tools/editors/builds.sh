#!/bin/sh
QT_MAJOR_MINOR='5.4'
QT_REVISION='0'
QT_VERSION=$QT_MAJOR_MINOR.$QT_REVISION
QT_DIR=/Users/$USER/Qt$QT_VERSION/$QT_MAJOR_MINOR/clang_64
QMAKE=$QT_DIR/bin/qmake
QMACDEPLOY=$QT_DIR/bin/macdeployqt

PRO_FILE='../editors/editors.pro'
BUILD_DIR='./builds_path'

mkdir -p $BUILD_DIR
cd $BUILD_DIR
$QMAKE -r $PRO_FILE
make
cp -r */*.app ../
cd ..
rm -rf $BUILD_DIR
$QMACDEPLOY "./Palette Editor.app" -dmg
$QMACDEPLOY "./Wheel Editor.app" -dmg
$QMACDEPLOY "./Sprite Sheet Editor.app" -dmg
