#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2015/05/10 01:03:12 by irabeson          #+#    #+#             *#
#*   Updated: 2015/05/10 01:35:56 by irabeson         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

QT_MAJOR_MINOR = 5.4
QT_REVISION = 0
QT_VERSION = $(QT_MAJOR_MINOR).$(QT_REVISION)
QT_DIR = /Users/$(USER)/Qt$(QT_VERSION)/$(QT_MAJOR_MINOR)/clang_64
QMAKE = $(QT_DIR)/bin/qmake

PRO_FILE = ../WheelEditor/WheelEditor.pro

BUILD_DIR = ../builds_path

.PHONY: builds

all: builds
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)
	$(QMAKE) -r $(PRO_FILE)
	make
