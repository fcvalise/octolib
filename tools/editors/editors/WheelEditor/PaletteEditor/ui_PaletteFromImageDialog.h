/********************************************************************************
** Form generated from reading UI file 'PaletteFromImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PALETTEFROMIMAGEDIALOG_H
#define UI_PALETTEFROMIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "ColorListPreView.hpp"
#include "ImageColorPicker.hpp"

QT_BEGIN_NAMESPACE

class Ui_PaletteFromImageDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    ImageColorPicker *graphicsView;
    QVBoxLayout *verticalLayout;
    QToolButton *loadImageButton;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *colorsCountLabel;
    QSpinBox *colorsCountSpinBox;
    ColorListPreView *listView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PaletteFromImageDialog)
    {
        if (PaletteFromImageDialog->objectName().isEmpty())
            PaletteFromImageDialog->setObjectName(QStringLiteral("PaletteFromImageDialog"));
        PaletteFromImageDialog->resize(492, 560);
        verticalLayout_2 = new QVBoxLayout(PaletteFromImageDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new ImageColorPicker(PaletteFromImageDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

        horizontalLayout->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        loadImageButton = new QToolButton(PaletteFromImageDialog);
        loadImageButton->setObjectName(QStringLiteral("loadImageButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/folder_image.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadImageButton->setIcon(icon);

        verticalLayout->addWidget(loadImageButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        colorsCountLabel = new QLabel(PaletteFromImageDialog);
        colorsCountLabel->setObjectName(QStringLiteral("colorsCountLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, colorsCountLabel);

        colorsCountSpinBox = new QSpinBox(PaletteFromImageDialog);
        colorsCountSpinBox->setObjectName(QStringLiteral("colorsCountSpinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, colorsCountSpinBox);


        verticalLayout_2->addLayout(formLayout);

        listView = new ColorListPreView(PaletteFromImageDialog);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setMaximumSize(QSize(16777215, 64));
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        listView->setAutoScroll(false);
        listView->setAutoScrollMargin(0);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setFlow(QListView::LeftToRight);
        listView->setProperty("isWrapping", QVariant(false));
        listView->setLayoutMode(QListView::Batched);
        listView->setViewMode(QListView::ListMode);
        listView->setUniformItemSizes(false);

        verticalLayout_2->addWidget(listView);

        buttonBox = new QDialogButtonBox(PaletteFromImageDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(PaletteFromImageDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PaletteFromImageDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PaletteFromImageDialog, SLOT(reject()));
        QObject::connect(loadImageButton, SIGNAL(clicked()), PaletteFromImageDialog, SLOT(loadImage()));

        QMetaObject::connectSlotsByName(PaletteFromImageDialog);
    } // setupUi

    void retranslateUi(QDialog *PaletteFromImageDialog)
    {
        PaletteFromImageDialog->setWindowTitle(QApplication::translate("PaletteFromImageDialog", "Color extractor", 0));
        loadImageButton->setText(QApplication::translate("PaletteFromImageDialog", "Load an image...", 0));
        colorsCountLabel->setText(QApplication::translate("PaletteFromImageDialog", "Colors count:", 0));
    } // retranslateUi

};

namespace Ui {
    class PaletteFromImageDialog: public Ui_PaletteFromImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PALETTEFROMIMAGEDIALOG_H
