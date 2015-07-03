#include "SpriteSheetEditor.hpp"
#include "SpriteSheetView.hpp"
#include "SpriteSheetModel.hpp"
#include "TileControlWidget.hpp"
#include "GenerateRectangleDialog.hpp"
#include "TilePreview.hpp"
#include "SelectMoveCommand.hpp"
#include "AddTileCommand.hpp"
#include "CreateTileFromDivisionDialog.hpp"

#include <QGridLayout>
#include <QTableView>
#include <QItemSelectionModel>
#include <QStyledItemDelegate>
#include <QHeaderView>

#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>

#include <fstream>

namespace
{
    class TileItemDelegate : public QStyledItemDelegate
    {
    public:
        explicit TileItemDelegate(QObject* parent = nullptr) :
            QStyledItemDelegate(parent)
        {
        }

        virtual QString displayText(const QVariant &value, const QLocale &) const;
    };

    QString TileItemDelegate::displayText(const QVariant &value, const QLocale &) const
    {
        QRectF  rect = value.value<QRectF>();

        return (QString("%0;%1").arg(rect.x()).arg(rect.y()));
    }
}

SpriteSheetEditor::SpriteSheetEditor(QWidget *parent) :
    QWidget(parent),
    m_spriteSheetModel(new SpriteSheetModel(this)),
    m_spriteSheetView(new SpriteSheetView),
    m_tileView(new QTableView),
    m_tileControl(new TileControlWidget),
    m_tilePreview(new TilePreview)
{
    setup();
    setupCommands();
}

SpriteSheetEditor::~SpriteSheetEditor()
{
}

void SpriteSheetEditor::newSpriteSheet(const QString &textureFilePath)
{
    m_spriteSheetModel->reset(textureFilePath);
}

bool SpriteSheetEditor::openSpriteSheet(const QString &filePath)
{
    if (m_spriteSheetModel->loadFromFile(filePath) == false)
        return (false);

    m_spriteSheetView->restartCurrentCommand();
    return (true);
}

bool SpriteSheetEditor::saveSpriteSheet(const QString &filePath)
{
    m_spriteSheetModel->sortTiles();
    return (m_spriteSheetModel->saveToFile(filePath));
}

void SpriteSheetEditor::createTileByDivision()
{
    CreateTileFromDivisionDialog   dialog(m_spriteSheetModel);

    if (dialog.exec() == QDialog::Accepted)
    {
        m_spriteSheetModel->resetPositions(dialog.positions());
    }
}

void SpriteSheetEditor::resetTexture(const QString &textureFilePath)
{
    m_spriteSheetModel->resetTexture(textureFilePath);
}

void SpriteSheetEditor::zoomIn()
{
    m_spriteSheetView->zoomIn();
}

void SpriteSheetEditor::zoomOut()
{
    m_spriteSheetView->zoomOut();
}

void SpriteSheetEditor::zoomZero()
{
    m_spriteSheetView->zoomZero();
}

void SpriteSheetEditor::zoomToFit()
{
    m_spriteSheetView->zoomToFit();
}

void SpriteSheetEditor::selectAllTiles()
{
    for (QModelIndex const& index : m_spriteSheetModel->indexes())
    {
        m_selectionModel->select(index, QItemSelectionModel::Select);
    }
}

void SpriteSheetEditor::copySelectedTiles()
{
    m_tileBuffer.clear();
    for (QModelIndex const& index : m_selectionModel->selectedIndexes())
    {
        m_tileBuffer.append(m_spriteSheetModel->tilePosition(index));
    }
}

void SpriteSheetEditor::cutSelectedTiles()
{
    m_tileBuffer.clear();
    for (QModelIndex const& index : m_selectionModel->selectedIndexes())
    {
        m_tileBuffer.append(m_spriteSheetModel->tilePosition(index));
    }
    m_spriteSheetModel->removeTiles(m_selectionModel->selectedIndexes());
    m_selectionModel->clearSelection();
}

void SpriteSheetEditor::pasteTiles()
{
    QPair<QModelIndex, QModelIndex> range;

    if (m_tileBuffer.empty())
        return;
    m_selectionModel->clearSelection();
    range = m_spriteSheetModel->addTiles(m_tileBuffer);
    m_selectionModel->select(QItemSelection(range.first, range.second), QItemSelectionModel::Select);
}

void SpriteSheetEditor::deleteSelectedTiles()
{
    m_spriteSheetModel->removeTiles(m_selectionModel->selectedRows());
}

void SpriteSheetEditor::sortTiles()
{
    m_spriteSheetModel->sortTiles();
}

bool SpriteSheetEditor::hasSelection() const
{
    return (m_selectionModel->hasSelection());
}

QList<QAction *> SpriteSheetEditor::commandActions() const
{
    return (m_spriteSheetView->commandActions());
}

void SpriteSheetEditor::setup()
{
    QGridLayout*    layout = new QGridLayout(this);

    m_spriteSheetModel = new SpriteSheetModel(this);
    m_selectionModel = new QItemSelectionModel(m_spriteSheetModel);
    m_tileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_tileView->setModel(m_spriteSheetModel);
    m_tileView->setSelectionModel(m_selectionModel);
    m_tileView->setItemDelegate(new TileItemDelegate(this));
    m_tileView->horizontalHeader()->setStretchLastSection(true);
    m_tileView->horizontalHeader()->setHidden(true);
    m_tileView->verticalHeader()->setDefaultSectionSize(20);
    m_spriteSheetView->setModel(m_spriteSheetModel);
    m_spriteSheetView->setSelectionModel(m_selectionModel);
    m_tilePreview->setModel(m_spriteSheetModel);
    m_tilePreview->setSelectionModel(m_selectionModel);
    layout->addWidget(m_spriteSheetView, 0, 0, 0, 1);
    layout->addWidget(m_tileControl, 0, 1);
    layout->addWidget(m_tileView, 1, 1);
    layout->addWidget(m_tilePreview, 2, 1);
    layout->setColumnStretch(0, 4);
    connect(m_spriteSheetModel, SIGNAL(modified()), SIGNAL(modified()));
    connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SIGNAL(selectionChanged()));
    //connect(m_selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), SIGNAL(selectionChanged()));
    connect(m_tileControl, SIGNAL(tileSizeEdited(QSize)), m_spriteSheetModel, SLOT(setTileSize(QSize)));
    connect(m_spriteSheetModel, SIGNAL(tileSizeChanged(QSize)), m_tileControl, SLOT(setTileSize(QSize)));
}

void SpriteSheetEditor::setupCommands()
{
    m_spriteSheetView->addCommand(new SelectMoveCommand(m_spriteSheetModel, m_selectionModel), true);
    m_spriteSheetView->addCommand(new AddTileCommand(m_spriteSheetModel, m_selectionModel));
}
