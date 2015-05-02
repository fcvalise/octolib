#include "OffsetEditor.hpp"
#include "WheelModel.hpp"

#include <QDataWidgetMapper>
#include <QFormLayout>

#include <SpinBoxSlider.hpp>

OffsetEditor::OffsetEditor(QWidget *parent) :
    QWidget(parent),
    m_offset(new SpinBoxSlider(-359, 359)),
    m_saturation(new SpinBoxSlider(0, 255)),
    m_value(new SpinBoxSlider(0, 255)),
    m_alpha(new SpinBoxSlider(0, 255))
{
    QFormLayout*    layout = new QFormLayout(this);

    layout->addRow(tr("Offset:"), m_offset);
    layout->addRow(tr("Saturation:"), m_saturation);
    layout->addRow(tr("Value:"), m_value);
    layout->addRow(tr("Alpha:"), m_alpha);
    connect(m_offset, SIGNAL(valueChanged(int)), SLOT(emitOffsetChanged()));
    connect(m_saturation, SIGNAL(valueChanged(int)), SLOT(emitOffsetChanged()));
    connect(m_value, SIGNAL(valueChanged(int)), SLOT(emitOffsetChanged()));
    connect(m_alpha, SIGNAL(valueChanged(int)), SLOT(emitOffsetChanged()));
}

OffsetEditor::~OffsetEditor()
{
}

HueOffset OffsetEditor::getOffset() const
{
    return (HueOffset(m_offset->value(),
                      m_saturation->value(),
                      m_value->value(),
                      m_alpha->value()));
}

void OffsetEditor::setOffset(const HueOffset &offset)
{
    m_offset->setValue(offset.getOffset());
    m_saturation->setValue(offset.getSaturation());
    m_value->setValue(offset.getValue());
    m_alpha->setValue(offset.getAlpha());
}

void OffsetEditor::emitOffsetChanged()
{
    emit offsetChanged(getOffset());
}

