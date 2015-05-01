#include "AddOffsetsDialog.hpp"
#include "ui_AddOffsetsDialog.h"

AddOffsetsDialog::AddOffsetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOffsetsDialog)
{
    ui->setupUi(this);
}

AddOffsetsDialog::~AddOffsetsDialog()
{
    delete ui;
}

quint16 AddOffsetsDialog::getInitial() const
{
    return (ui->initialOffsetSpinBox->value());
}

int AddOffsetsDialog::getCount() const
{
    return (ui->offsetCountSpinBox->value());
}

qint16 AddOffsetsDialog::getInterval() const
{
    return (ui->intervalSpinBox->value());
}
