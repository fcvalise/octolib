/********************************************************************************
** Form generated from reading UI file 'SquareOffsetDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQUAREOFFSETDIALOG_H
#define UI_SQUAREOFFSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "ColorListPreView.hpp"

QT_BEGIN_NAMESPACE

class Ui_SquareOffsetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *globalHueLabel;
    QSlider *globalHueSlider;
    QLabel *saturationLabel;
    QSlider *saturationSlider;
    QLabel *valueLabel;
    QSlider *valueSlider;
    QLabel *alphaLabel;
    QSlider *alphaSlider;
    ColorListPreView *listView;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SquareOffsetDialog)
    {
        if (SquareOffsetDialog->objectName().isEmpty())
            SquareOffsetDialog->setObjectName(QStringLiteral("SquareOffsetDialog"));
        SquareOffsetDialog->resize(495, 208);
        verticalLayout = new QVBoxLayout(SquareOffsetDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        globalHueLabel = new QLabel(SquareOffsetDialog);
        globalHueLabel->setObjectName(QStringLiteral("globalHueLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, globalHueLabel);

        globalHueSlider = new QSlider(SquareOffsetDialog);
        globalHueSlider->setObjectName(QStringLiteral("globalHueSlider"));
        globalHueSlider->setMaximum(359);
        globalHueSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, globalHueSlider);

        saturationLabel = new QLabel(SquareOffsetDialog);
        saturationLabel->setObjectName(QStringLiteral("saturationLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, saturationLabel);

        saturationSlider = new QSlider(SquareOffsetDialog);
        saturationSlider->setObjectName(QStringLiteral("saturationSlider"));
        saturationSlider->setMaximum(255);
        saturationSlider->setValue(255);
        saturationSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, saturationSlider);

        valueLabel = new QLabel(SquareOffsetDialog);
        valueLabel->setObjectName(QStringLiteral("valueLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, valueLabel);

        valueSlider = new QSlider(SquareOffsetDialog);
        valueSlider->setObjectName(QStringLiteral("valueSlider"));
        valueSlider->setMaximum(255);
        valueSlider->setValue(255);
        valueSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, valueSlider);

        alphaLabel = new QLabel(SquareOffsetDialog);
        alphaLabel->setObjectName(QStringLiteral("alphaLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, alphaLabel);

        alphaSlider = new QSlider(SquareOffsetDialog);
        alphaSlider->setObjectName(QStringLiteral("alphaSlider"));
        alphaSlider->setMaximum(255);
        alphaSlider->setValue(255);
        alphaSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(3, QFormLayout::FieldRole, alphaSlider);


        verticalLayout->addLayout(formLayout);

        listView = new ColorListPreView(SquareOffsetDialog);
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

        verticalLayout->addWidget(listView);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(SquareOffsetDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SquareOffsetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SquareOffsetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SquareOffsetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SquareOffsetDialog);
    } // setupUi

    void retranslateUi(QDialog *SquareOffsetDialog)
    {
        SquareOffsetDialog->setWindowTitle(QApplication::translate("SquareOffsetDialog", "Square scheme", 0));
        globalHueLabel->setText(QApplication::translate("SquareOffsetDialog", "Global hue:", 0));
        saturationLabel->setText(QApplication::translate("SquareOffsetDialog", "Saturation:", 0));
        valueLabel->setText(QApplication::translate("SquareOffsetDialog", "Value:", 0));
        alphaLabel->setText(QApplication::translate("SquareOffsetDialog", "Alpha:", 0));
    } // retranslateUi

};

namespace Ui {
    class SquareOffsetDialog: public Ui_SquareOffsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQUAREOFFSETDIALOG_H
