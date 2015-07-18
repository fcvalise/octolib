QTDIR=/Users/iota/Qt5.4.2/5.4/clang_64
QMAKE=$QTDIR/bin/qmake
MACDEPLOY=$QTDIR/bin/macdeployqt
MAIN_PRO=../editors/editors.pro

mkdir auto_builds
cd auto_builds
$QMAKE $MAIN_PRO  -r -spec macx-clang CONFIG+=x86_64
make

cd ..
$MACDEPLOY "auto_builds/PaletteEditor/Palette Editor.app" -dmg
$MACDEPLOY "auto_builds/WheelEditor/Wheel Editor.app" -dmg
$MACDEPLOY "auto_builds/SpriteSheetEditor/Sprite Sheet Editor.app" -dmg

