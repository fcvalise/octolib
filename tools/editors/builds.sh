#!/bin/sh
QT_MAJOR_MINOR='5.4'
QT_REVISION='0'
QT_VERSION=$QT_MAJOR_MINOR.$QT_REVISION
QT_DIR=/Users/$USER/Qt$QT_VERSION/$QT_MAJOR_MINOR/clang_64
QMAKE=$QT_DIR/bin/qmake
QMACDEPLOY=$QT_DIR/bin/macdeployqt
GIT_BRANCH="$(git rev-parse --abbrev-ref HEAD)"
GIT_SHORT_HASH="$(git rev-parse --short HEAD)"
PRO_FILE='../editors/editors.pro'
BUILD_DIR='./builds_dir'
FILE_PREFIX="${GIT_BRANCH}-${GIT_SHORT_HASH}"

echo - Building $FILE_PREFIX
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR
echo " - Running qmake"
$QMAKE -r $PRO_FILE > builds_log.txt
echo " - Running make"
make >> builds_log.txt
cp -r */*.app ../
cd ..
rm -rf $BUILD_DIR
echo " - Packing applications"
$QMACDEPLOY "./Palette Editor.app" -dmg
$QMACDEPLOY "./Wheel Editor.app" -dmg
$QMACDEPLOY "./Sprite Sheet Editor.app" -dmg
mv "./Palette Editor.dmg" "./Palette Editor-$FILE_PREFIX.dmg"
mv "./Wheel Editor.dmg" "./Wheel Editor-$FILE_PREFIX.dmg"
mv "./Sprite Sheet Editor.dmg" "./Sprite Sheet Editor-$FILE_PREFIX.dmg"
