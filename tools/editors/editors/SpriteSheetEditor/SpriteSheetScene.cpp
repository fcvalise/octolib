#include "AbstractSpriteSheetCommand.hpp"
#include "SpriteSheetScene.hpp"
#include "RectangleModel.hpp"
#include "PointerSpriteSheetCommand.hpp"
#include "RectangleSpriteSheetCommand.hpp"

#include <QGraphicsPixmapItem>
#include <QItemSelectionModel>
#include <QModelIndex>

QPen const          SpriteSheetScene::RectanglePen = QPen(Qt::red, 0);
QBrush const        SpriteSheetScene::SelectedRectangleBrush = QBrush(QColor(255, 0, 0, 120));
QPen const          SpriteSheetScene::GhostRectanglePen = QPen(Qt::green, 0, Qt::DotLine);
QBrush const        SpriteSheetScene::GhostRectangleBrush = QBrush(QColor(0, 255, 0, 120));

SpriteSheetScene::SpriteSheetScene(QObject *parent) :
    QGraphicsScene(parent),
    m_rectangleModel(new RectangleModel(this)),
    m_selectionRectangleModel(new QItemSelectionModel(m_rectangleModel, this)),
    m_texture(nullptr),
    m_ghostRectangle(nullptr),
    m_textureBorder(nullptr)
{
    setupCommands();
    m_texture = addPixmap(QPixmap());
    m_texture->setZValue(-1);
    m_ghostRectangle = addRect(QRectF(), GhostRectanglePen, GhostRectangleBrush);
    m_ghostRectangle->setVisible(false);
    m_ghostRectangle->setZValue(2);
    m_textureBorder = addRect(QRect());
    m_textureBorder->setZValue(-0.9);
    connect(m_rectangleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
    connect(m_rectangleModel, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(rowsInserted(QModelIndex,int,int)));
    connect(m_rectangleModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
    connect(m_rectangleModel, SIGNAL(modelReset()), SLOT(modelReset()));
    connect(m_selectionRectangleModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
}

SpriteSheetScene::~SpriteSheetScene()
{
    qDeleteAll(m_rectangles);
}

RectangleModel *SpriteSheetScene::rectangleModel() const
{
    return (m_rectangleModel);
}

QItemSelectionModel* SpriteSheetScene::selectionRectangleModel()const
{
    return (m_selectionRectangleModel);
}

void SpriteSheetScene::setTexturePixmap(const QPixmap &pixmap)
{
    m_texture->setPixmap(pixmap);
    m_textureBorder->setRect(m_texture->boundingRect());
    setSceneRect(m_texture->boundingRect());
}

QList<QAction *> SpriteSheetScene::commandActions() const
{
    return (m_commandManager.commandActions());
}

void SpriteSheetScene::resetRectangles(const QList<QPointF> &positions, const QSizeF &size)
{
    m_rectangleModel->reset(positions, size);
}

void SpriteSheetScene::setRectangleSize(const QSizeF &size)
{
    m_rectangleModel->setSize(size);
    setGhostRectangleSize(size);
}

void SpriteSheetScene::moveRectangle(const QModelIndex &index, const QPointF &offset)
{
    m_rectangleModel->moveRectangle(index, offset);
}

void SpriteSheetScene::setRectanglePosition(const QModelIndex &index, const QPointF &position)
{
    m_rectangleModel->setRectanglePosition(index, position);
}

void SpriteSheetScene::removeRectangle(const QModelIndex &index)
{
    m_rectangleModel->removeRectangle(index);
}

void SpriteSheetScene::removeAllRectangles()
{
    m_rectangleModel->removeAll();
}

void SpriteSheetScene::sortRectangles()
{
    m_rectangleModel->sortRectanglesByXY();
}

void SpriteSheetScene::makeRectangleFromGhost()
{
    m_rectangleModel->addRectangle(m_ghostRectangle->pos());
}

void SpriteSheetScene::setGhostRectangleEnabled(bool enable)
{
    m_ghostRectangle->setVisible(enable);
    setGhostRectangleSize(m_rectangleModel->size());
}

void SpriteSheetScene::setGhostRectangleSize(const QSizeF &size)
{
    QRectF  rect = m_ghostRectangle->rect();

    rect.setSize(size);
    m_ghostRectangle->setRect(rect);
}

void SpriteSheetScene::setGhostRectanglePosition(const QPointF &position)
{
    m_ghostRectangle->setPos(position);
}

void SpriteSheetScene::setCurrentRectangle(const QModelIndex &index)
{
    m_selectionRectangleModel->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
}

QModelIndex SpriteSheetScene::rectangleUnder(const QPointF &pos) const
{
    QModelIndex result;

    for (int i = 0; i < m_rectangles.size(); ++i)
    {
        if (m_rectangles[i]->contains(pos))
        {
            result = m_rectangleModel->index(i);
            break;
        }
    }
    return (result);
}

QModelIndex SpriteSheetScene::currentRectangle() const
{
    return (m_selectionRectangleModel->currentIndex());
}

bool SpriteSheetScene::isIntoTexture(const QPointF &pos) const
{
    return (m_texture->contains(pos));
}

QSizeF SpriteSheetScene::rectangleSize() const
{
    return (m_rectangleModel->size());
}

QRectF SpriteSheetScene::rectangle(const QModelIndex &index) const
{
    return (m_rectangleModel->rectangle(index));
}

qreal SpriteSheetScene::textureWidth() const
{
    return (m_texture->boundingRect().width());
}

qreal SpriteSheetScene::textureHeight() const
{
    return (m_texture->boundingRect().height());
}

QPixmap SpriteSheetScene::texturePixmap() const
{
    return (m_texture->pixmap());
}

void SpriteSheetScene::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    for (int i = topLeft.row(); i < bottomRight.row() + 1; ++i)
    {
        commitChange(i);
    }
    emit modified();
}

void SpriteSheetScene::rowsInserted(const QModelIndex &, int start, int end)
{
    int pos = start;
    int count = (end - start) + 1;

    for (int i = 0; i < count; ++i)
    {
        m_rectangles.insert(pos + i, createRectangle());
        commitChange(pos + i);
    }
    emit modified();
}

void SpriteSheetScene::rowsAboutToBeRemoved(const QModelIndex &, int start, int end)
{
    int                 pos = start;
    int                 count = (end - start) + 1;
    QGraphicsRectItem*  item = nullptr;

    for (int i = 0; i < count; ++i)
    {
        item = m_rectangles.at(pos);
        removeItem(item);
        delete item;
    }
    m_rectangles.remove(start, count);
    emit modified();
}

void SpriteSheetScene::modelReset()
{
    qDeleteAll(m_rectangles);
    m_rectangles.clear();
    for (int i = 0; i < m_rectangleModel->rowCount(QModelIndex()); ++i)
    {
        m_rectangles.append(createRectangle());
        commitChange(i);
    }
    emit modified();
}

void SpriteSheetScene::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    setSelected(previous, false);
    setSelected(current, true);
}

void SpriteSheetScene::setupCommands()
{
    m_commandManager.addCommand(new PointerSpriteSheetCommand(this));
    m_commandManager.addCommand(new RectangleSpriteSheetCommand(this));
}

void SpriteSheetScene::commitChange(int row)
{
    QGraphicsRectItem*  item = m_rectangles.at(row);
    QRectF              rect = m_rectangleModel->rectangle(row);

    item->setRect(rect);
}

QGraphicsRectItem *SpriteSheetScene::createRectangle()
{
    QGraphicsRectItem*  item = new QGraphicsRectItem(m_texture);

    item->setPen(RectanglePen);
    item->setZValue(1);
    return (item);
}

void SpriteSheetScene::clearSelection()
{
    for (int i = 0; i < m_rectangleModel->rowCount(QModelIndex()); ++i)
    {
        setSelected(m_rectangleModel->index(i), false);
    }
}

void SpriteSheetScene::setSelected(const QModelIndex &index, bool selected)
{
    QGraphicsRectItem* item = nullptr;

    if (index.isValid() == false)
        return;
    item = m_rectangles.at(index.row());
    if (selected)
        item->setBrush(SelectedRectangleBrush);
    else
        item->setBrush(Qt::transparent);
}

void SpriteSheetScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractSpriteSheetCommand* command = m_commandManager.currentCommand();

    if (command)
        command->mousePressEvent(event);
}

void SpriteSheetScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractSpriteSheetCommand* command = m_commandManager.currentCommand();

    if (command)
        command->mouseMoveEvent(event);
}

void SpriteSheetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractSpriteSheetCommand* command = m_commandManager.currentCommand();

    if (command)
        command->mouseReleaseEvent(event);
}

void SpriteSheetScene::keyPressEvent(QKeyEvent *event)
{
    AbstractSpriteSheetCommand* command = m_commandManager.currentCommand();

    if (command)
        command->keyPressEvent(event);
}

void SpriteSheetScene::keyReleaseEvent(QKeyEvent *event)
{
    AbstractSpriteSheetCommand* command = m_commandManager.currentCommand();

    if (command)
        command->keyReleaseEvent(event);
}
