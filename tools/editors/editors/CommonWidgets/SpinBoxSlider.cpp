#include "SpinBoxSlider.hpp"
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

SpinBoxSlider::SpinBoxSlider(QWidget *parent) :
    QWidget(parent),
    m_slider(new QSlider(Qt::Horizontal)),
    m_spinBox(new QSpinBox)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->addWidget(m_slider);
    layout->addWidget(m_spinBox);
    connect(m_slider, SIGNAL(valueChanged(int)), SLOT(onSliderChanged(int)), Qt::DirectConnection);
    connect(m_spinBox, SIGNAL(valueChanged(int)), SLOT(onSpinBoxChanged(int)), Qt::DirectConnection);
}

SpinBoxSlider::SpinBoxSlider(int min, int max, QWidget *parent) :
    SpinBoxSlider(parent)
{
    setMinimum(min);
    setMaximum(max);
}

SpinBoxSlider::~SpinBoxSlider()
{
}

int SpinBoxSlider::value() const
{
    return (m_value);
}

void SpinBoxSlider::setValue(int value)
{
    m_value = value;
    m_slider->blockSignals(true);
    m_spinBox->blockSignals(true);
    m_slider->setValue(value);
    m_spinBox->setValue(value);
    m_slider->blockSignals(false);
    m_spinBox->blockSignals(false);
}

void SpinBoxSlider::setMinimum(int value)
{
    m_min = value;
    m_slider->setMinimum(value);
    m_spinBox->setMinimum(value);
}

void SpinBoxSlider::setMaximum(int value)
{
    m_max = value;
    m_slider->setMaximum(value);
    m_spinBox->setMaximum(value);
}

void SpinBoxSlider::onSliderChanged(int value)
{
    m_value = value;
    m_spinBox->blockSignals(true);
    m_spinBox->setValue(m_value);
    m_spinBox->blockSignals(false);
    emit valueChanged(m_value);
}

void SpinBoxSlider::onSpinBoxChanged(int value)
{
    m_value = value;
    m_slider->blockSignals(true);
    m_slider->setValue(value);
    m_slider->blockSignals(false);
    emit valueChanged(m_value);
}
