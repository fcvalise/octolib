#include "AddTileCommand.hpp"
#include "SpriteSheetModel.hpp"

#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include <cmath>

QPen const          AddTileCommand::GhostRectanglePen = QPen(Qt::green, 0, Qt::DotLine);
QBrush const        AddTileCommand::GhostRectangleBrush = QBrush(QColor(0, 255, 0, 90));

AddTileCommand::AddTileCommand(SpriteSheetModel *model, QItemSelectionModel *selection) :
    AbstractCommand(model, selection),
    m_action(nullptr),
    m_ghost(nullptr)
{
    m_action = new QAction(QIcon(":/images/rectangle.png"), QObject::tr("Add tile"), nullptr);
    m_ghost = new QGraphicsRectItem();
    m_ghost->setPen(GhostRectanglePen);
    m_ghost->setBrush(GhostRectangleBrush);
    commandActionSetup(m_action);
    connect(model, &SpriteSheetModel::tileSizeChanged, this, &AddTileCommand::onTileSizeChanged);
}

AddTileCommand::~AddTileCommand()
{
    delete m_action;
    delete m_ghost;
    m_action = nullptr;
    m_ghost = nullptr;
}

QAction *AddTileCommand::action() const
{
    return (m_action);
}

QCursor AddTileCommand::cursor() const
{
    return (Qt::CrossCursor);
}

void AddTileCommand::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void AddTileCommand::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint pos(std::floor(event->scenePos().x()), std::floor(event->scenePos().y()));
    QPoint offset(m_previous.isNull() ? pos : pos - m_previous);
    QSize  size = model()->tileSize();

    if (offset.manhattanLength() >= 1)
    {
        // Constraint rectangle into the texture
        if (pos.x() - size.width() / 2 < 0)
            pos.setX(size.width() / 2);
        else if (pos.x() + size.width() / 2 > model()->textureRect().width())
            pos.setX(model()->textureRect().width() - size.width() / 2);
        if (pos.y() - size.height() / 2 < 0)
            pos.setY(size.height() / 2);
        else if (pos.y() + size.height() / 2 > model()->textureRect().height())
            pos.setY(model()->textureRect().height() - size.height() / 2);
        m_ghost->setPos(QPointF(std::floor(pos.x() - size.width() / 2),
                        std::floor(pos.y() - size.height() / 2)));
        m_previous = pos;
    }
}

void AddTileCommand::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    QSize   tileSize = model()->tileSize();

    model()->addTile(m_previous - QPoint(tileSize.width(), tileSize.height()) / 2);
}

void AddTileCommand::keyPressEvent(QKeyEvent *)
{
}

void AddTileCommand::keyReleaseEvent(QKeyEvent *)
{
}

void AddTileCommand::onStarted(QGraphicsScene* scene)
{
    if (scene->items().contains(m_ghost) == false)
        scene->addItem(m_ghost);
    m_ghost->setVisible(true);
    m_ghost->setRect(QRectF(QPointF(0, 0), model()->tileSize()));
    m_previous = QPoint();
}

void AddTileCommand::onStopped(QGraphicsScene *scene)
{
    scene->removeItem(m_ghost);
}

void AddTileCommand::onTileSizeChanged(const QSize &size)
{
    m_ghost->setRect(QRectF(m_previous, size));
}
