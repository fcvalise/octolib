#include "PaletteModel.hpp"
#include "SquareOffsetDialog.hpp"
#include "ui_SquareOffsetDialog.h"

#include "WheelModel.hpp"
#include "PaletteModel.hpp"
#include "ColorItemDelegate.hpp"

SquareOffsetDialog::SquareOffsetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SquareOffsetDialog),
    m_model(new WheelModel(this))
{
    ui->setupUi(this);
    ui->listView->setModel(m_model);
    ui->listView->setItemDelegate(new ColorItemDelegate(this));
    connect(ui->globalHueSlider, SIGNAL(valueChanged(int)), SLOT(setHue(int)));
    connect(ui->saturationSlider, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    connect(ui->valueSlider, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    connect(ui->alphaSlider, SIGNAL(valueChanged(int)), SLOT(updateModel()));
    updateModel();
}

SquareOffsetDialog::~SquareOffsetDialog()
{
    delete ui;
}

void SquareOffsetDialog::addOffsets(WheelModel *model)
{
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        model->addOffset(m_model->getOffset(i).addOffset(ui->globalHueSlider->value()));
    }
}

void SquareOffsetDialog::addColors(PaletteModel *model)
{
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        model->addColor(m_model->getOffset(i).addOffset(ui->globalHueSlider->value()).computeColor(ui->globalHueSlider->value()));
    }
}

void SquareOffsetDialog::setHue(int hue)
{
    m_model->setHue(hue);
}

void SquareOffsetDialog::updateModel()
{
    quint16 hue = 0;

    m_model->removeAll();
    while (m_model->rowCount() < 4)
    {
        m_model->addOffset(hue,
                           ui->saturationSlider->value(),
                           ui->valueSlider->value(),
                           ui->alphaSlider->value());
        hue += 90;
    }
}
