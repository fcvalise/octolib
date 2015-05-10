/********************************************************************************
** Form generated from reading UI file 'AddOffsetsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDOFFSETSDIALOG_H
#define UI_ADDOFFSETSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddOffsetsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *offsetCountLabel;
    QSpinBox *offsetCountSpinBox;
    QSpinBox *intervalSpinBox;
    QLabel *intervalLabel;
    QLabel *initialOffsetLabel;
    QSpinBox *initialOffsetSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddOffsetsDialog)
    {
        if (AddOffsetsDialog->objectName().isEmpty())
            AddOffsetsDialog->setObjectName(QStringLiteral("AddOffsetsDialog"));
        AddOffsetsDialog->resize(312, 162);
        AddOffsetsDialog->setMaximumSize(QSize(450, 190));
        AddOffsetsDialog->setModal(true);
        verticalLayout = new QVBoxLayout(AddOffsetsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        offsetCountLabel = new QLabel(AddOffsetsDialog);
        offsetCountLabel->setObjectName(QStringLiteral("offsetCountLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, offsetCountLabel);

        offsetCountSpinBox = new QSpinBox(AddOffsetsDialog);
        offsetCountSpinBox->setObjectName(QStringLiteral("offsetCountSpinBox"));
        offsetCountSpinBox->setMinimum(0);
        offsetCountSpinBox->setMaximum(999);

        formLayout->setWidget(1, QFormLayout::FieldRole, offsetCountSpinBox);

        intervalSpinBox = new QSpinBox(AddOffsetsDialog);
        intervalSpinBox->setObjectName(QStringLiteral("intervalSpinBox"));
        intervalSpinBox->setMaximum(359);

        formLayout->setWidget(2, QFormLayout::FieldRole, intervalSpinBox);

        intervalLabel = new QLabel(AddOffsetsDialog);
        intervalLabel->setObjectName(QStringLiteral("intervalLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, intervalLabel);

        initialOffsetLabel = new QLabel(AddOffsetsDialog);
        initialOffsetLabel->setObjectName(QStringLiteral("initialOffsetLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, initialOffsetLabel);

        initialOffsetSpinBox = new QSpinBox(AddOffsetsDialog);
        initialOffsetSpinBox->setObjectName(QStringLiteral("initialOffsetSpinBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, initialOffsetSpinBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(AddOffsetsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(offsetCountSpinBox, intervalSpinBox);
        QWidget::setTabOrder(intervalSpinBox, initialOffsetSpinBox);

        retranslateUi(AddOffsetsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddOffsetsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddOffsetsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddOffsetsDialog);
    } // setupUi

    void retranslateUi(QDialog *AddOffsetsDialog)
    {
        AddOffsetsDialog->setWindowTitle(QApplication::translate("AddOffsetsDialog", "Create offsets", 0));
        offsetCountLabel->setText(QApplication::translate("AddOffsetsDialog", "Offset count:", 0));
        intervalLabel->setText(QApplication::translate("AddOffsetsDialog", "Interval:", 0));
        initialOffsetLabel->setText(QApplication::translate("AddOffsetsDialog", "Initial offset:", 0));
    } // retranslateUi

};

namespace Ui {
    class AddOffsetsDialog: public Ui_AddOffsetsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDOFFSETSDIALOG_H
