#include "RectangleSpriteSheetCommand.hpp"
#include "SpriteSheetScene.hpp"

#include <QAction>
#include <QGraphicsSceneMouseEvent>

#include <cmath>

RectangleSpriteSheetCommand::RectangleSpriteSheetCommand(SpriteSheetScene *scene) :
    AbstractSpriteSheetCommand(scene),
    m_action(nullptr),
    m_ghost(nullptr)
{
    m_action = new QAction(QIcon(":/images/rectangle.png"), QObject::tr("Add tile"), nullptr);
    commandActionSetup(m_action);
}

RectangleSpriteSheetCommand::~RectangleSpriteSheetCommand()
{
    delete m_action;
}

QAction *RectangleSpriteSheetCommand::action() const
{
    return (m_action);
}

QCursor RectangleSpriteSheetCommand::cursor() const
{
    return (Qt::CrossCursor);
}

void RectangleSpriteSheetCommand::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void RectangleSpriteSheetCommand::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(std::floor(event->scenePos().x()), std::floor(event->scenePos().y()));
    QPointF offset(pos - m_previous);
    QSizeF  size = scene()->rectangleSize();

    if (offset.manhattanLength() >= 1)
    {
        // Constraint rectangle into the texture
        if (pos.x() - size.width() / 2 < 0)
            pos.setX(size.width() / 2);
        else if (pos.x() + size.width() / 2 > scene()->textureWidth())
            pos.setX(scene()->textureWidth() - size.width() / 2);
        if (pos.y() - size.height() / 2 < 0)
            pos.setY(size.height() / 2);
        else if (pos.y() + size.height() / 2 > scene()->textureHeight())
            pos.setY(scene()->textureHeight() - size.height() / 2);
        scene()->setGhostRectanglePosition(QPointF(std::floor(pos.x() - size.width() / 2),
                                                   std::floor(pos.y() - size.height() / 2)));
        m_previous = QPointF(std::floor(event->scenePos().x()), std::floor(event->scenePos().y()));
    }
}

void RectangleSpriteSheetCommand::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    scene()->makeRectangleFromGhost();
}

void RectangleSpriteSheetCommand::keyPressEvent(QKeyEvent *)
{
}

void RectangleSpriteSheetCommand::keyReleaseEvent(QKeyEvent *)
{
}

void RectangleSpriteSheetCommand::onStarted()
{
    scene()->setGhostRectangleEnabled(true);
}

void RectangleSpriteSheetCommand::onStopped()
{
    scene()->setGhostRectangleEnabled(false);
}
