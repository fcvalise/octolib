#include "SelectMoveCommand.hpp"
#include "SpriteSheetModel.hpp"

#include <QAction>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QModelIndex>
#include <QKeyEvent>
#include <QItemSelectionModel>

#include <cmath>

SelectMoveCommand::SelectMoveCommand(SpriteSheetModel *model, QItemSelectionModel *selection) :
    AbstractSpriteSheetCommand(model, selection),
    m_action(nullptr)
{
    m_action = new QAction(QIcon(":/images/cursor.png"), QObject::tr("Pointer"), nullptr);
    commandActionSetup(m_action);
}

SelectMoveCommand::~SelectMoveCommand()
{
    delete m_action;
}

QAction *SelectMoveCommand::action() const
{
    return (m_action);
}

QCursor SelectMoveCommand::cursor() const
{
    return (Qt::ArrowCursor);
}

void SelectMoveCommand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QModelIndex rectangleIndex = model()->tileAt(event->scenePos().toPoint());

    if (event->modifiers().testFlag(Qt::ControlModifier))
        selection()->setCurrentIndex(rectangleIndex, QItemSelectionModel::Select);
    else if (selection()->isSelected(rectangleIndex) == false)
        selection()->setCurrentIndex(rectangleIndex, QItemSelectionModel::ClearAndSelect);
    m_grabbedIndexes = selection()->selectedIndexes();
    m_previous = QPoint(std::floor(event->scenePos().x()), std::floor(event->scenePos().y()));
}

void SelectMoveCommand::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint              pos(std::ceil(event->scenePos().x()), std::ceil(event->scenePos().y()));
    QPoint              offset(pos - m_previous);

    if (m_grabbedIndexes.isEmpty() == false && offset.manhattanLength() >= 1)
    {
        for (QModelIndex const& index : m_grabbedIndexes)
        {
            model()->moveTile(index, offset);
        }
        m_previous = pos;
    }
}

void SelectMoveCommand::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    m_grabbedIndexes.clear();
}

void SelectMoveCommand::keyPressEvent(QKeyEvent *event)
{
    QPoint      offset;

    if (selection()->hasSelection() == false)
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
        for (QModelIndex const& index : selection()->selectedIndexes())
        {
            model()->moveTile(index, offset);
        }
    }
}

void SelectMoveCommand::keyReleaseEvent(QKeyEvent *)
{
}

void SelectMoveCommand::onStarted(QGraphicsScene *)
{
    m_grabbedIndexes.clear();
}

void SelectMoveCommand::onStopped(QGraphicsScene *)
{
    m_grabbedIndexes.clear();
}
