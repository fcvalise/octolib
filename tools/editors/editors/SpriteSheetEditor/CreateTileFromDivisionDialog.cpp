#include "CreateTileFromDivisionDialog.hpp"
#include "SpriteSheetModel.hpp"
#include "SpriteSheetView.hpp"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>

CreateTileFromDivisionDialog::CreateTileFromDivisionDialog(const SpriteSheetModel *sourceModel, QWidget *parent) :
    QDialog(parent),
    m_view(new SpriteSheetView(this)),
    m_model(new SpriteSheetModel(this))
{
    QVBoxLayout*        centralLayout = new QVBoxLayout(this);
    QHBoxLayout*        mainLayout = new QHBoxLayout;
    QFrame*             controlFrame = new QFrame;
    QFormLayout*        controlLayout = new QFormLayout(controlFrame);
    QDialogButtonBox*   buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    m_model->reset(sourceModel->textureBytes(), QList<QPoint>(), sourceModel->tileSize());
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(controlFrame);
    centralLayout->addLayout(mainLayout);
    centralLayout->addWidget(buttons);
    m_widthDivision = createSpinBox(tr("Width divisions:"), 1, sourceModel->textureRect().width(), 1, controlLayout);
    m_heightDivision = createSpinBox(tr("Height divisions:"), 1, sourceModel->textureRect().height(), 1, controlLayout);
    m_widthInterval = createSpinBox(tr("Width interval:"), 0, sourceModel->textureRect().width(), 0, controlLayout);
    m_heightInterval = createSpinBox(tr("Height divisions:"), 0, sourceModel->textureRect().height(), 0, controlLayout);
    m_widthOffset = createSpinBox(tr("Width offset:"), 0, sourceModel->textureRect().width(), 0, controlLayout);
    m_heightOffset = createSpinBox(tr("Height offset:"), 0, sourceModel->textureRect().height(), 0, controlLayout);
    updateTiles();
    m_view->setModel(m_model);
    m_view->zoomToFit();
    connect(buttons, &QDialogButtonBox::accepted, this, &CreateTileFromDivisionDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &CreateTileFromDivisionDialog::reject);
}

CreateTileFromDivisionDialog::~CreateTileFromDivisionDialog()
{
}

QList<QPoint> CreateTileFromDivisionDialog::positions() const
{
    return (m_model->tilePositions());
}

QSize CreateTileFromDivisionDialog::tileSize() const
{
    return (m_model->tileSize());
}

QSpinBox *CreateTileFromDivisionDialog::createSpinBox(const QString &label, int min, int max, int current, QFormLayout *layout)
{
    QSpinBox*   spinBox = new QSpinBox;

    layout->addRow(label, spinBox);
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setValue(current);
    connect(spinBox, SIGNAL(valueChanged(QString)), SLOT(updateTiles()));
    return (spinBox);
}

void CreateTileFromDivisionDialog::updateTiles()
{
    QSize           textureSize = m_model->textureRect().size();
    int             x = m_widthOffset->value();
    int             y = m_heightOffset->value();
    int             tileWidth = textureSize.width() / m_widthDivision->value();
    int             tileHeight = textureSize.height() / m_heightDivision->value();
    QList<QPoint>   positions;

    while (x >= 0 && (x + tileWidth) <= textureSize.width())
    {
        while (y >= 0 && (y + tileHeight <= textureSize.height()))
        {
            positions.append(QPoint(x, y));
            y += tileHeight + m_heightInterval->value();
        }
        x += tileWidth + m_widthInterval->value();
        y = m_heightOffset->value();
    }
    m_model->setTileSize(QSize(tileWidth, tileHeight));
    m_model->resetPositions(positions);
}

void CreateTileFromDivisionDialog::showEvent(QShowEvent *)
{
    m_view->zoomToFit();
}

void CreateTileFromDivisionDialog::resizeEvent(QResizeEvent *)
{
    m_view->zoomToFit();
}



