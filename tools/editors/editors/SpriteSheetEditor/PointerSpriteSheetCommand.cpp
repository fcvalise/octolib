#include "PointerSpriteSheetCommand.hpp"
#include "SpriteSheetScene.hpp"

#include <QAction>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QModelIndex>
#include <QKeyEvent>

#include <cmath>

PointerSpriteSheetCommand::PointerSpriteSheetCommand(SpriteSheetScene *scene) :
    AbstractSpriteSheetCommand(scene),
    m_action(nullptr)
{
    m_action = new QAction(QIcon(":/images/cursor.png"), QObject::tr("Pointer"), nullptr);
    commandActionSetup(m_action);
}

PointerSpriteSheetCommand::~PointerSpriteSheetCommand()
{
    delete m_action;
}

QAction *PointerSpriteSheetCommand::action() const
{
    return (m_action);
}

QCursor PointerSpriteSheetCommand::cursor() const
{
    return (Qt::ArrowCursor);
}

void PointerSpriteSheetCommand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QModelIndex rectangleIndex = scene()->rectangleUnder(event->scenePos());

    m_grabbedIndex = rectangleIndex;
    m_previous = QPointF(std::floor(event->scenePos().x()), std::floor(event->scenePos().y()));
    scene()->setCurrentRectangle(m_grabbedIndex);
}

void PointerSpriteSheetCommand::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(std::floor(event->scenePos().x()), std::floor(event->scenePos().y()));
    QPointF offset(pos - m_previous);
    QPointF currentRectPos;
    QSizeF  currentRectSize;

    if (m_grabbedIndex.isValid() && offset.manhattanLength() >= 1)
    {
        // Constraint rectangle into the texture
        currentRectPos = scene()->rectangle(m_grabbedIndex).topLeft();
        currentRectSize = scene()->rectangle(m_grabbedIndex).size();
        if (currentRectPos.x() + offset.x() < 0)
            offset.setX(-currentRectPos.x());
        else if (currentRectPos.x() + currentRectSize.width() + offset.x() > scene()->textureWidth())
            offset.setX(scene()->textureWidth() - currentRectSize.width() - currentRectPos.x());
        if (currentRectPos.y() + offset.y() < 0)
            offset.setY(-currentRectPos.y());
        else if (currentRectPos.y() + currentRectSize.height() + offset.y() > scene()->textureHeight())
            offset.setY(scene()->textureHeight() - currentRectSize.height() - currentRectPos.y());
        scene()->moveRectangle(m_grabbedIndex, offset);
        m_previous = pos;
    }
}

void PointerSpriteSheetCommand::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    m_grabbedIndex = QModelIndex();
}

void PointerSpriteSheetCommand::keyPressEvent(QKeyEvent *event)
{
    QPointF     offset;
    QModelIndex currentRectangleIndex = scene()->currentRectangle();
    QPointF     currentRectPos;
    QSizeF      currentRectSize;

    if (currentRectangleIndex.isValid() == false)
        return;
    switch(event->key())
    {
    case Qt::Key_Up:
        offset.setY(-1);
        break;
    case Qt::Key_Down:
        offset.setY(1);
        break;
    case Qt::Key_Left:
        offset.setX(-1);
        break;
    case Qt::Key_Right:
        offset.setX(1);
        break;
    default:
        break;
    }
    if (event->modifiers().testFlag(Qt::ShiftModifier))
        offset *= 10;
    if (offset.manhattanLength() >= 1)
    {
        // Constraint rectangle into the texture
        currentRectPos = scene()->rectangle(currentRectangleIndex).topLeft();
        currentRectSize = scene()->rectangle(currentRectangleIndex).size();
        if (currentRectPos.x() + offset.x() < 0)
            offset.setX(-currentRectPos.x());
        else if (currentRectPos.x() + currentRectSize.width() + offset.x() > scene()->textureWidth())
            offset.setX(scene()->textureWidth() - currentRectSize.width() - currentRectPos.x());
        if (currentRectPos.y() + offset.y() < 0)
            offset.setY(-currentRectPos.y());
        else if (currentRectPos.y() + currentRectSize.height() + offset.y() > scene()->textureHeight())
            offset.setY(scene()->textureHeight() - currentRectSize.height() - currentRectPos.y());
        scene()->moveRectangle(currentRectangleIndex, offset);
    }
}

void PointerSpriteSheetCommand::keyReleaseEvent(QKeyEvent *)
{
}

void PointerSpriteSheetCommand::onStarted()
{
}

void PointerSpriteSheetCommand::onStopped()
{
    m_grabbedIndex = QModelIndex();
}
