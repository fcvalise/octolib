#include "GenerateRectangleDialog.hpp"
#include "SpriteSheetView.hpp"

#include <QGridLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>

GenerateRectangleDialog::GenerateRectangleDialog(QPixmap const& texture, QWidget *parent) :
    QDialog(parent),
    m_view(new SpriteSheetView),
    m_widthSubDiv(new QSpinBox),
    m_heightSubDiv(new QSpinBox)
{
    QGridLayout*        layout = new QGridLayout(this);
    QWidget*            controlPanel = new QFrame;
    QFormLayout*        controlLayout = new QFormLayout(controlPanel);
    QDialogButtonBox*   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_view->setTexturePixmap(texture);
    m_widthSubDiv->setMinimum(1);
    m_widthSubDiv->setMaximum(99999);
    m_heightSubDiv->setMinimum(1);
    m_heightSubDiv->setMaximum(99999);
    layout->addWidget(m_view, 0, 0);
    layout->addWidget(controlPanel, 0, 1);
    layout->addWidget(buttonBox, 1, 0, 1, 2);
    controlLayout->addRow(tr("Sub div width:"), m_widthSubDiv);
    controlLayout->addRow(tr("Sub div height:"), m_heightSubDiv);
    connect(m_widthSubDiv, SIGNAL(valueChanged(int)), SLOT(regenerate()));
    connect(m_heightSubDiv, SIGNAL(valueChanged(int)), SLOT(regenerate()));
    connect(buttonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), SLOT(reject()));
}

GenerateRectangleDialog::~GenerateRectangleDialog()
{
}

int GenerateRectangleDialog::widthSubDivCount() const
{
    return (m_widthSubDiv->value());
}

int GenerateRectangleDialog::heightSubDivCount() const
{
    return (m_heightSubDiv->value());
}

void GenerateRectangleDialog::regenerate()
{
    m_view->generateRectangles(m_widthSubDiv->value(), m_heightSubDiv->value());
}

void GenerateRectangleDialog::resizeEvent(QResizeEvent *)
{
    m_view->zoomToFit();
}

void GenerateRectangleDialog::showEvent(QShowEvent *event)
{
    m_view->zoomToFit();
    QDialog::showEvent(event);
}
