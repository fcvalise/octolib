/********************************************************************************
** Form generated from reading UI file 'ComplementaryOffsetDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPLEMENTARYOFFSETDIALOG_H
#define UI_COMPLEMENTARYOFFSETDIALOG_H

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

class Ui_ComplementaryOffsetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *globalHueLabel;
    QSlider *globalHueSlider;
    QLabel *saturationLabel;
    QLabel *countLabel;
    QSpinBox *countSpinBox;
    QLabel *intervalLabel;
    QSpinBox *intervalSpinBox;
    QLabel *valueLabel;
    QSlider *valueSlider;
    QSlider *saturationSlider;
    QLabel *alphaLabel;
    QSlider *alphaSlider;
    ColorListPreView *listView;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ComplementaryOffsetDialog)
    {
        if (ComplementaryOffsetDialog->objectName().isEmpty())
            ComplementaryOffsetDialog->setObjectName(QStringLiteral("ComplementaryOffsetDialog"));
        ComplementaryOffsetDialog->resize(511, 276);
        verticalLayout = new QVBoxLayout(ComplementaryOffsetDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        globalHueLabel = new QLabel(ComplementaryOffsetDialog);
        globalHueLabel->setObjectName(QStringLiteral("globalHueLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, globalHueLabel);

        globalHueSlider = new QSlider(ComplementaryOffsetDialog);
        globalHueSlider->setObjectName(QStringLiteral("globalHueSlider"));
        globalHueSlider->setMaximum(359);
        globalHueSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, globalHueSlider);

        saturationLabel = new QLabel(ComplementaryOffsetDialog);
        saturationLabel->setObjectName(QStringLiteral("saturationLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, saturationLabel);

        countLabel = new QLabel(ComplementaryOffsetDialog);
        countLabel->setObjectName(QStringLiteral("countLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, countLabel);

        countSpinBox = new QSpinBox(ComplementaryOffsetDialog);
        countSpinBox->setObjectName(QStringLiteral("countSpinBox"));
        countSpinBox->setMinimum(1);
        countSpinBox->setMaximum(999);
        countSpinBox->setValue(1);

        formLayout->setWidget(4, QFormLayout::FieldRole, countSpinBox);

        intervalLabel = new QLabel(ComplementaryOffsetDialog);
        intervalLabel->setObjectName(QStringLiteral("intervalLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, intervalLabel);

        intervalSpinBox = new QSpinBox(ComplementaryOffsetDialog);
        intervalSpinBox->setObjectName(QStringLiteral("intervalSpinBox"));
        intervalSpinBox->setMaximum(359);
        intervalSpinBox->setValue(30);

        formLayout->setWidget(5, QFormLayout::FieldRole, intervalSpinBox);

        valueLabel = new QLabel(ComplementaryOffsetDialog);
        valueLabel->setObjectName(QStringLiteral("valueLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, valueLabel);

        valueSlider = new QSlider(ComplementaryOffsetDialog);
        valueSlider->setObjectName(QStringLiteral("valueSlider"));
        valueSlider->setMaximum(255);
        valueSlider->setValue(255);
        valueSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, valueSlider);

        saturationSlider = new QSlider(ComplementaryOffsetDialog);
        saturationSlider->setObjectName(QStringLiteral("saturationSlider"));
        saturationSlider->setMaximum(255);
        saturationSlider->setValue(255);
        saturationSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, saturationSlider);

        alphaLabel = new QLabel(ComplementaryOffsetDialog);
        alphaLabel->setObjectName(QStringLiteral("alphaLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, alphaLabel);

        alphaSlider = new QSlider(ComplementaryOffsetDialog);
        alphaSlider->setObjectName(QStringLiteral("alphaSlider"));
        alphaSlider->setMaximum(255);
        alphaSlider->setValue(255);
        alphaSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(3, QFormLayout::FieldRole, alphaSlider);


        verticalLayout->addLayout(formLayout);

        listView = new ColorListPreView(ComplementaryOffsetDialog);
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

        buttonBox = new QDialogButtonBox(ComplementaryOffsetDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ComplementaryOffsetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ComplementaryOffsetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ComplementaryOffsetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ComplementaryOffsetDialog);
    } // setupUi

    void retranslateUi(QDialog *ComplementaryOffsetDialog)
    {
        ComplementaryOffsetDialog->setWindowTitle(QApplication::translate("ComplementaryOffsetDialog", "Complementary scheme", 0));
        globalHueLabel->setText(QApplication::translate("ComplementaryOffsetDialog", "Global hue:", 0));
        saturationLabel->setText(QApplication::translate("ComplementaryOffsetDialog", "Saturation:", 0));
        countLabel->setText(QApplication::translate("ComplementaryOffsetDialog", "Count:", 0));
        intervalLabel->setText(QApplication::translate("ComplementaryOffsetDialog", "Interval:", 0));
        valueLabel->setText(QApplication::translate("ComplementaryOffsetDialog", "Value:", 0));
        alphaLabel->setText(QApplication::translate("ComplementaryOffsetDialog", "Alpha:", 0));
    } // retranslateUi

};

namespace Ui {
    class ComplementaryOffsetDialog: public Ui_ComplementaryOffsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPLEMENTARYOFFSETDIALOG_H
