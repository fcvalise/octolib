#include "ComplementaryOffsetDialog.hpp"
#include <WheelModel.hpp>
#include "ui_ComplementaryOffsetDialog.h"

#include <ColorItemDelegate.hpp>

ComplementaryOffsetDialog::ComplementaryOffsetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComplementaryOffsetDialog),
    m_model(new WheelModel(this))
{
    ui->setupUi(this);
    ui->listView->setModel(m_model);
    ui->listView->setItemDelegate(new ColorItemDelegate(this));
    connect(ui->globalHueSlider, SIGNAL(valueChanged(int)), SLOT(setHue(int)));
    connect(ui->saturationSlider, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    connect(ui->valueSlider, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    connect(ui->alphaSlider, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    connect(ui->countSpinBox, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    connect(ui->intervalSpinBox, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    updateModel();
}

ComplementaryOffsetDialog::~ComplementaryOffsetDialog()
{
    delete ui;
}

void ComplementaryOffsetDialog::addOffsets(WheelModel *model)
{
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        model->addOffset(m_model->getOffset(i).addOffset(ui->globalHueSlider->value()));
    }
}

void ComplementaryOffsetDialog::setHue(int hue)
{
    m_model->setHue(hue);
}

void ComplementaryOffsetDialog::updateModel()
{
    quint16         hue = 0;
    QList<quint16>  baseHues;
    int             i = 0;
    int             count = ui->countSpinBox->value();

    while (i < count)
    {
        baseHues.append(hue);
        hue += ui->intervalSpinBox->value();
        i++;
    }
    i = 0;
    while (i < count)
    {
        baseHues.append((baseHues[count - 1 - i] + 180) % 360);
        hue += ui->intervalSpinBox->value();
        i++;
    }
    m_model->removeAll();
    for (auto value : baseHues)
    {
        m_model->addOffset(value,
                           ui->saturationSlider->value(),
                           ui->valueSlider->value(),
                           ui->alphaSlider->value());
    }
}
