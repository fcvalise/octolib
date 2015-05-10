#!/bin/sh

set -e

QT_MAJOR_MINOR='5.4'
QT_REVISION='0'
QT_VERSION=$QT_MAJOR_MINOR.$QT_REVISION
QT_INSTALLER=qt-opensource-linux-x64-$QT_VERSION.run
QT_INSTALLER_URL=http://download.qt.io/archive/qt/$QT_MAJOR_MINOR/$QT_VERSION/$QT_INSTALLER

packages="
mesa-common-dev
libglu1-mesa-dev
"

for package in $packages
do
	apt-get install -qq --allow-unauthenticated $package
done

wget $QT_INSTALLER_URL
chmod +x $QT_INSTALLER
./$QT_INSTALLER
