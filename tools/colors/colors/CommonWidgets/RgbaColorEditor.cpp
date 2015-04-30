#include "RgbaColorEditor.hpp"

#include <QFormLayout>

static void setupSpinBox(SpinBoxSlider* sb)
{
    sb->setMinimum(0);
    sb->setMaximum(255);
}

RgbaColorEditor::RgbaColorEditor(QWidget *parent) :
    AbstractColorEditor(parent),
    m_red(new SpinBoxSlider),
    m_green(new SpinBoxSlider),
    m_blue(new SpinBoxSlider),
    m_alpha(new SpinBoxSlider)
{
    setup();
}

RgbaColorEditor::~RgbaColorEditor()
{
}

void RgbaColorEditor::setColor(QColor color)
{
    m_red->setValue(color.red());
    m_green->setValue(color.green());
    m_blue->setValue(color.blue());
    m_alpha->setValue(color.alpha());
}

QColor RgbaColorEditor::getColor() const
{
    return (QColor(m_red->value(), m_green->value(), m_blue->value(), m_alpha->value()));
}

void RgbaColorEditor::setup()
{
    QFormLayout*    layout = new QFormLayout(this);

    setupSpinBox(m_red);
    setupSpinBox(m_green);
    setupSpinBox(m_blue);
    setupSpinBox(m_alpha);
    connect(m_red, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()));
    connect(m_green, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()));
    connect(m_blue, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()));
    connect(m_alpha, SIGNAL(valueChanged(int)), SLOT(emitColorChanged()));
    layout->addRow(tr("Red:"), m_red);
    layout->addRow(tr("Green:"), m_green);
    layout->addRow(tr("Blue:"), m_blue);
    layout->addRow(tr("Alpha:"), m_alpha);
    layout->setSpacing(3);
}

void RgbaColorEditor::emitColorChanged()
{
    emit colorChanged(getColor());
}

