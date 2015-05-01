#include "OffsetEditor.hpp"

#include <QFormLayout>

OffsetEditor::OffsetEditor(QWidget *parent) :
    QWidget(parent),
    m_mapper(new QDataWidgetMapper(this)),
    m_offset(new SpinBoxSlider(0, 359)),
    m_saturation(new SpinBoxSlider(0, 255)),
    m_value(new SpinBoxSlider(0, 255)),
    m_alpha(new SpinBoxSlider(0, 255))
{
    QFormLayout*    layout = new QFormLayout(this);

    layout->addRow(tr("Offset:"), m_offset);
    layout->addRow(tr("Saturation:"), m_saturation);
    layout->addRow(tr("Value:"), m_value);
    layout->addRow(tr("Alpha:"), m_alpha);
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
    m_offset->blockSignals(true);
    m_saturation->blockSignals(true);
    m_value->blockSignals(true);
    m_alpha->blockSignals(true);

    m_offset->setValue(offset.getOffset());
    m_saturation->setValue(offset.getSaturation());
    m_value->setValue(offset.getValue());
    m_alpha->setValue(offset.getAlpha());

    m_offset->blockSignals(false);
    m_saturation->blockSignals(false);
    m_value->blockSignals(false);
    m_alpha->blockSignals(false);
}

void OffsetEditor::emitOffsetChanged()
{
    emit offsetChanged(getOffset());
}

