#include "AnaloguousOffsetDialog.hpp"
#include "ui_AnaloguousOffsetDialog.h"

#include "WheelModel.hpp"
#include "PaletteModel.hpp"
#include "ColorItemDelegate.hpp"

AnaloguousOffsetDialog::AnaloguousOffsetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnaloguousOffsetDialog),
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

AnaloguousOffsetDialog::~AnaloguousOffsetDialog()
{
    delete ui;
}

void AnaloguousOffsetDialog::addOffsets(WheelModel *model)
{
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        model->addOffset(m_model->getOffset(i).addOffset(ui->globalHueSlider->value()));
    }
}

void AnaloguousOffsetDialog::addColors(PaletteModel *model)
{
    HueOffset   offset;

    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        offset = m_model->getOffset(i);
        offset = offset.addOffset(ui->globalHueSlider->value());
        model->addColor(offset.computeColor(ui->globalHueSlider->value()));
    }
}

void AnaloguousOffsetDialog::setHue(int hue)
{
    m_model->setHue(hue);
}

void AnaloguousOffsetDialog::updateModel()
{
    quint16 hue = 0;

    m_model->removeAll();
    while (m_model->rowCount() < ui->countSpinBox->value())
    {
        m_model->addOffset(hue,
                           ui->saturationSlider->value(),
                           ui->valueSlider->value(),
                           ui->alphaSlider->value());
        hue += ui->intervalSpinBox->value();
    }
}
