#include "SpriteSheetView.hpp"
#include "SpriteSheetModel.hpp"
#include "CommandManager.hpp"
#include "AbstractCommand.hpp"

#include <InteractiveGraphicsScene.hpp>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QItemSelectionModel>
#include <QModelIndex>

QPen const          SpriteSheetView::RectanglePen = QPen(Qt::red, 0);
QBrush const        SpriteSheetView::SelectedRectangleBrush = QBrush(QColor(255, 0, 0, 120));
QBrush const        SpriteSheetView::HoveredRectangleBrush = QBrush(QColor(255, 0, 0, 30));
QPen const          SpriteSheetView::BorderRectanglePen = QPen(Qt::black, 0, Qt::DotLine);

class SpriteSheetView::GraphicsTileItem : public QGraphicsRectItem
{
    enum State
    {
        Default = 0,
        Selected = 0x1,
        Hovered = 0x2
    };

    Q_DECLARE_FLAGS(States, State)
public:
    GraphicsTileItem(QGraphicsItem* parent = nullptr) :
        QGraphicsRectItem(parent),
        m_state(Default)
    {
        setPen(RectanglePen);
        setZValue(1);
        setAcceptHoverEvents(true);
    }

    void    setHovered(bool state)
    {
        if (state)
            m_state |= Hovered;
        else
            m_state &= ~Hovered;
        updateDisplay();
    }

    void    setTileSelected(bool state)
    {
        if (state)
            m_state |= Selected;
        else
            m_state &= ~Selected;
        updateDisplay();
    }
private:
    void    updateDisplay()
    {
        if (m_state.testFlag(Hovered))
        {
            setBrush(SpriteSheetView::HoveredRectangleBrush);
        }
        else if (m_state.testFlag(Selected))
        {
            setBrush(SpriteSheetView::SelectedRectangleBrush);
        }
        else
        {
            setBrush(Qt::transparent);
        }
    }
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *)
    {
        setHovered(true);
    }

    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *)
    {
        setHovered(false);
    }
private:
    QBrush  m_oldBrush;
    States  m_state;
};

SpriteSheetView::SpriteSheetView(QWidget *parent) :
    QGraphicsView(parent),
    m_model(nullptr),
    m_selectionModel(nullptr),
    m_scene(new InteractiveGraphicsScene(this)),
    m_zoomFactor(1.0),
    m_texture(nullptr),
    m_textureBorder(nullptr)
{
    setInteractive(true);
    setMouseTracking(true);
    setScene(m_scene);
    setupBackgroundBrush();
    enableBackground(true);
    m_texture = m_scene->addPixmap(QPixmap());
    m_textureBorder = m_scene->addRect(0, 0, 0, 0, BorderRectanglePen);
}

SpriteSheetView::~SpriteSheetView()
{
}

void SpriteSheetView::setModel(SpriteSheetModel *model)
{
    if (m_model)
    {
        setSelectionModel(nullptr);
        disconnect(m_model.data(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
        disconnect(m_model.data(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(onRowsInserted(QModelIndex,int,int)));
        disconnect(m_model.data(), SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
        disconnect(m_model.data(), SIGNAL(modelReset()), this, SLOT(onModelReset()));
        m_model = nullptr;
    }
    m_model = model;
    if (m_model)
    {
        connect(m_model.data(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
        connect(m_model.data(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(onRowsInserted(QModelIndex,int,int)));
        connect(m_model.data(), SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
        connect(m_model.data(), SIGNAL(modelReset()), this, SLOT(onModelReset()));
        onModelReset();
        setSelectionModel(new QItemSelectionModel(m_model, this));
    }
}

void SpriteSheetView::setSelectionModel(QItemSelectionModel *model)
{
    if (m_selectionModel)
    {
        disconnect(m_selectionModel.data(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
    }
    m_selectionModel = model;
    if (m_selectionModel)
    {
        connect(m_selectionModel.data(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
    }
}

void SpriteSheetView::enableBackground(bool enable)
{
    if (enable)
        m_scene->setBackgroundBrush(m_backgroundBrush);
    else
        m_scene->setBackgroundBrush(QBrush());
}

void SpriteSheetView::zoomIn()
{
    setZoom(m_zoomFactor + 0.1);
    centerOnCurrent();
}

void SpriteSheetView::zoomOut()
{
    if (m_zoomFactor > 0.1)
    {
        setZoom(m_zoomFactor - 0.1);
        centerOnCurrent();
    }
}

void SpriteSheetView::zoomZero()
{
    setZoom(1.0);
}

void SpriteSheetView::zoomToFit()
{
    if (m_model == nullptr)
        return;
    QRectF  viewRect = viewport()->rect().adjusted(2, 2, -2, -2);
    QRectF  textureRect = m_model->textureRect();
    qreal   factorX = viewRect.width() / textureRect.width();
    qreal   factorY = viewRect.height() / textureRect.height();

    setZoom(std::min(factorX, factorY));
}

void SpriteSheetView::setZoom(qreal factor)
{
    m_zoomFactor = factor;
    setTransform(QTransform::fromScale(m_zoomFactor, m_zoomFactor), false);
}

void SpriteSheetView::enableCommands(bool enable)
{
    m_scene->enableCommands(enable);
}

void SpriteSheetView::addCommand(AbstractCommand *command, bool enable)
{
    m_scene->addCommand(command, enable);
}

void SpriteSheetView::restartCurrentCommand()
{
    m_scene->restartCurrentCommand();
}

QList<QAction *> SpriteSheetView::commandActions() const
{
    return (m_scene->commandActions());
}

void SpriteSheetView::setupBackgroundBrush()
{
    static const QColor s_light = QColor(125, 125, 125);
    static const QColor s_dark = QColor(75, 75, 75);
    QPixmap             pixmap(16, 16);
    QPainter            painter(&pixmap);

    painter.fillRect(0, 0, 8, 8, s_light);
    painter.fillRect(8, 0, 8, 8, s_dark);
    painter.fillRect(0, 8, 8, 8, s_dark);
    painter.fillRect(8, 8, 8, 8, s_light);
    m_backgroundBrush = QBrush(pixmap);
}

void SpriteSheetView::centerOnCurrent()
{
    QRect   boundingRect(std::numeric_limits<int>::max(),
                         std::numeric_limits<int>::max(),
                         std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::min());
    QRect   rect;

    if (m_model == nullptr || m_selectionModel == nullptr || m_selectionModel->hasSelection() == false)
        return;
    for (QModelIndex const& index : m_selectionModel->selectedIndexes())
    {
        rect = m_model->tile(index);
        if (rect.left() < boundingRect.left())
            boundingRect.setLeft(rect.left());
        if (rect.right() > boundingRect.right())
            boundingRect.setRight(rect.right());
        if (rect.top() < boundingRect.top())
            boundingRect.setTop(rect.top());
        if (rect.bottom() > boundingRect.bottom())
            boundingRect.setBottom(rect.bottom());
    }
    centerOn(boundingRect.center());
}

void SpriteSheetView::commitChange(int row)
{
    if (m_model == nullptr)
        return;
    QGraphicsRectItem*  item = m_tiles.at(row);
    QRectF              rect = m_model->tile(row);

    item->setRect(rect);
}

SpriteSheetView::GraphicsTileItem *SpriteSheetView::createTile()
{
    return (new GraphicsTileItem(m_texture));
}

void SpriteSheetView::setTileSelected(const QModelIndex &index, bool selected)
{
    GraphicsTileItem* item = nullptr;

    if (index.isValid() == false)
        return;
    item = m_tiles.at(index.row());
    item->setTileSelected(selected);
}

void SpriteSheetView::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    for (int i = topLeft.row(); i < bottomRight.row() + 1; ++i)
    {
        commitChange(i);
    }
    emit modified();
}

void SpriteSheetView::onRowsInserted(const QModelIndex &, int start, int end)
{
    int pos = start;
    int count = (end - start) + 1;

    for (int i = 0; i < count; ++i)
    {
        m_tiles.insert(pos + i, createTile());
        commitChange(pos + i);
    }
    emit modified();
}

void SpriteSheetView::onRowsAboutToBeRemoved(const QModelIndex &, int start, int end)
{
    int                 pos = start;
    int                 count = (end - start) + 1;
    QGraphicsRectItem*  item = nullptr;

    for (int i = 0; i < count; ++i)
    {
        item = m_tiles.at(pos);
        m_scene->removeItem(item);
        delete item;
    }
    m_tiles.remove(start, count);
    emit modified();
}

void SpriteSheetView::onModelReset()
{
    qDeleteAll(m_tiles);
    m_tiles.clear();
    for (int i = 0; i < m_model->rowCount(QModelIndex()); ++i)
    {
        m_tiles.append(createTile());
        commitChange(i);
    }
    m_texture->setPixmap(m_model->texture());
    m_textureBorder->setRect(m_texture->boundingRect());
    m_scene->setSceneRect(m_texture->boundingRect());

    emit modified();
}

void SpriteSheetView::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    setTileSelected(previous, false);
    setTileSelected(current, true);
}

void SpriteSheetView::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    for (QModelIndex const& index : selected.indexes())
    {
        setTileSelected(index, true);
    }
    for (QModelIndex const& index : deselected.indexes())
    {
        setTileSelected(index, false);
    }
}
