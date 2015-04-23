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
    connect(m_slider, SIGNAL(sliderMoved(int)), SLOT(onSliderChanged(int)));
    connect(m_spinBox, SIGNAL(valueChanged(int)), SLOT(onSpinBoxChanged(int)));
    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->addWidget(m_slider);
    layout->addWidget(m_spinBox);
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
    m_slider->setValue(value);
    m_spinBox->setValue(value);
    emit valueChanged(value);
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
    m_spinBox->setValue(m_value);
    emit valueChanged(value);
}

void SpinBoxSlider::onSpinBoxChanged(int value)
{
    m_value = value;
    m_slider->setValue(value);
    emit valueChanged(value);
}
