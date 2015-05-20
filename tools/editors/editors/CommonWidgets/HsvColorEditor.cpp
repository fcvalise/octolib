#include "HsvColorEditor.hpp"
#include "SpinBoxSlider.hpp"

#include <QFormLayout>

HsvColorEditor::HsvColorEditor(QWidget *parent) :
    AbstractColorEditor(parent),
    m_hue(new SpinBoxSlider(0, 359)),
    m_saturation(new SpinBoxSlider(0, 255)),
    m_value(new SpinBoxSlider(0, 255)),
    m_alpha(new SpinBoxSlider(0, 255))
{
    setup();
}

HsvColorEditor::~HsvColorEditor()
{
}

void HsvColorEditor::setColor(QColor color)
{
    m_hue->setValue(color.hue());
    m_saturation->setValue(color.hsvSaturation());
    m_value->setValue(color.value());
    m_alpha->setValue(color.alpha());
}

QColor HsvColorEditor::getColor() const
{
    return (QColor::fromHsv(m_hue->value(), m_saturation->value(), m_value->value(), m_alpha->value()));
}

void HsvColorEditor::setup()
{
    QFormLayout*    layout = new QFormLayout(this);

    m_hue->setMaximum(359);
    m_hue->setMinimum(0);
    m_saturation->setMaximum(255);
    m_saturation->setMinimum(0);
    m_value->setMaximum(255);
    m_value->setMinimum(0);
    m_alpha->setMaximum(255);
    m_alpha->setMinimum(0);
    connect(m_hue, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()), Qt::DirectConnection);
    connect(m_saturation, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()), Qt::DirectConnection);
    connect(m_value, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()), Qt::DirectConnection);
    connect(m_alpha, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()), Qt::DirectConnection);
    layout->addRow(tr("Hue:"), m_hue);
    layout->addRow(tr("Saturation:"), m_saturation);
    layout->addRow(tr("Value:"), m_value);
    layout->addRow(tr("Alpha:"), m_alpha);
}

void HsvColorEditor::emitColorChanged()
{
    emit colorChanged(getColor());
}
