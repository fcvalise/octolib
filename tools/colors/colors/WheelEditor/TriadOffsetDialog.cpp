#include "TriadOffsetDialog.hpp"
#include "ui_TriadOffsetDialog.h"

#include <WheelModel.hpp>

#include <ColorItemDelegate.hpp>

TriadOffsetDialog::TriadOffsetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TriadOffsetDialog),
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

TriadOffsetDialog::~TriadOffsetDialog()
{
    delete ui;
}

void TriadOffsetDialog::addOffsets(WheelModel *model)
{
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        model->addOffset(m_model->getOffset(i).addOffset(ui->globalHueSlider->value()));
    }
}

void TriadOffsetDialog::setHue(int hue)
{
    m_model->setHue(hue);
}

void TriadOffsetDialog::updateModel()
{
    quint16 hue = 0;

    m_model->removeAll();
    while (m_model->rowCount() < 3)
    {
        m_model->addOffset(hue,
                           ui->saturationSlider->value(),
                           ui->valueSlider->value(),
                           ui->alphaSlider->value());
        hue += 120;
    }
}
