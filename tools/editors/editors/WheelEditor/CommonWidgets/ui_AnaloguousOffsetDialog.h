/********************************************************************************
** Form generated from reading UI file 'AnaloguousOffsetDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALOGUOUSOFFSETDIALOG_H
#define UI_ANALOGUOUSOFFSETDIALOG_H

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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "ColorListPreView.hpp"

QT_BEGIN_NAMESPACE

class Ui_AnaloguousOffsetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *globalHueLabel;
    QSlider *globalHueSlider;
    QLabel *countLabel;
    QSpinBox *countSpinBox;
    QLabel *intervalLabel;
    QSpinBox *intervalSpinBox;
    QLabel *saturationLabel;
    QLabel *valueLabel;
    QSlider *saturationSlider;
    QSlider *valueSlider;
    QLabel *alphaLabel;
    QSlider *alphaSlider;
    ColorListPreView *listView;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AnaloguousOffsetDialog)
    {
        if (AnaloguousOffsetDialog->objectName().isEmpty())
            AnaloguousOffsetDialog->setObjectName(QStringLiteral("AnaloguousOffsetDialog"));
        AnaloguousOffsetDialog->resize(493, 270);
        verticalLayout = new QVBoxLayout(AnaloguousOffsetDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        globalHueLabel = new QLabel(AnaloguousOffsetDialog);
        globalHueLabel->setObjectName(QStringLiteral("globalHueLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, globalHueLabel);

        globalHueSlider = new QSlider(AnaloguousOffsetDialog);
        globalHueSlider->setObjectName(QStringLiteral("globalHueSlider"));
        globalHueSlider->setMaximum(359);
        globalHueSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, globalHueSlider);

        countLabel = new QLabel(AnaloguousOffsetDialog);
        countLabel->setObjectName(QStringLiteral("countLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, countLabel);

        countSpinBox = new QSpinBox(AnaloguousOffsetDialog);
        countSpinBox->setObjectName(QStringLiteral("countSpinBox"));
        countSpinBox->setMinimum(3);
        countSpinBox->setMaximum(999);

        formLayout->setWidget(4, QFormLayout::FieldRole, countSpinBox);

        intervalLabel = new QLabel(AnaloguousOffsetDialog);
        intervalLabel->setObjectName(QStringLiteral("intervalLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, intervalLabel);

        intervalSpinBox = new QSpinBox(AnaloguousOffsetDialog);
        intervalSpinBox->setObjectName(QStringLiteral("intervalSpinBox"));
        intervalSpinBox->setMaximum(359);
        intervalSpinBox->setValue(30);

        formLayout->setWidget(5, QFormLayout::FieldRole, intervalSpinBox);

        saturationLabel = new QLabel(AnaloguousOffsetDialog);
        saturationLabel->setObjectName(QStringLiteral("saturationLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, saturationLabel);

        valueLabel = new QLabel(AnaloguousOffsetDialog);
        valueLabel->setObjectName(QStringLiteral("valueLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, valueLabel);

        saturationSlider = new QSlider(AnaloguousOffsetDialog);
        saturationSlider->setObjectName(QStringLiteral("saturationSlider"));
        saturationSlider->setMaximum(255);
        saturationSlider->setValue(255);
        saturationSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, saturationSlider);

        valueSlider = new QSlider(AnaloguousOffsetDialog);
        valueSlider->setObjectName(QStringLiteral("valueSlider"));
        valueSlider->setMaximum(255);
        valueSlider->setValue(255);
        valueSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, valueSlider);

        alphaLabel = new QLabel(AnaloguousOffsetDialog);
        alphaLabel->setObjectName(QStringLiteral("alphaLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, alphaLabel);

        alphaSlider = new QSlider(AnaloguousOffsetDialog);
        alphaSlider->setObjectName(QStringLiteral("alphaSlider"));
        alphaSlider->setMaximum(255);
        alphaSlider->setValue(255);
        alphaSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(3, QFormLayout::FieldRole, alphaSlider);


        verticalLayout->addLayout(formLayout);

        listView = new ColorListPreView(AnaloguousOffsetDialog);
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

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(AnaloguousOffsetDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AnaloguousOffsetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AnaloguousOffsetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AnaloguousOffsetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AnaloguousOffsetDialog);
    } // setupUi

    void retranslateUi(QDialog *AnaloguousOffsetDialog)
    {
        AnaloguousOffsetDialog->setWindowTitle(QApplication::translate("AnaloguousOffsetDialog", "Analoguous scheme", 0));
        globalHueLabel->setText(QApplication::translate("AnaloguousOffsetDialog", "Global hue:", 0));
        countLabel->setText(QApplication::translate("AnaloguousOffsetDialog", "Count:", 0));
        intervalLabel->setText(QApplication::translate("AnaloguousOffsetDialog", "Interval:", 0));
        saturationLabel->setText(QApplication::translate("AnaloguousOffsetDialog", "Saturation:", 0));
        valueLabel->setText(QApplication::translate("AnaloguousOffsetDialog", "Value:", 0));
        alphaLabel->setText(QApplication::translate("AnaloguousOffsetDialog", "Alpha:", 0));
    } // retranslateUi

};

namespace Ui {
    class AnaloguousOffsetDialog: public Ui_AnaloguousOffsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALOGUOUSOFFSETDIALOG_H
