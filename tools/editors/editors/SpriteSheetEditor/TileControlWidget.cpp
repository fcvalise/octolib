#include "TileControlWidget.hpp"

#include <QFormLayout>
#include <QSpinBox>

TileControlWidget::TileControlWidget(QWidget *parent) :
    QWidget(parent),
    m_width(new QSpinBox),
    m_height(new QSpinBox)
{
    QFormLayout*    layout = new QFormLayout(this);

    layout->addRow(tr("Tiles width:"), m_width);
    layout->addRow(tr("Tiles height:"), m_height);
    m_width->setMinimum(1);
    m_width->setMaximum(9999);
    m_width->setValue(16);
    m_width->setSuffix(tr("px"));
    m_height->setMinimum(1);
    m_height->setMaximum(9999);
    m_height->setValue(16);
    m_height->setSuffix(tr("px"));
    connect(m_width, SIGNAL(valueChanged(int)), SLOT(onSpinBoxChanged()));
    connect(m_height, SIGNAL(valueChanged(int)), SLOT(onSpinBoxChanged()));
}

TileControlWidget::~TileControlWidget()
{
}

void TileControlWidget::setTileSize(const QSizeF &size)
{
    m_width->blockSignals(true);
    m_height->blockSignals(true);
    m_width->setValue(size.width());
    m_height->setValue(size.height());
    m_width->blockSignals(false);
    m_height->blockSignals(false);
}

void TileControlWidget::onSpinBoxChanged()
{
    emit tileSizeChanged(QSize(m_width->value(), m_height->value()));
}

