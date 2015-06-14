#ifndef SELECTMOVECOMMAND_HPP
#define SELECTMOVECOMMAND_HPP

#include "AbstractSpriteSheetCommand.hpp"

#include <QModelIndex>

class SelectMoveCommand : public AbstractSpriteSheetCommand
{
public:
    explicit SelectMoveCommand(SpriteSheetModel* model, QItemSelectionModel* selection);
    ~SelectMoveCommand();

    virtual QAction *action() const;
    virtual QCursor cursor() const;

    virtual void    mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void    mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    virtual void    keyPressEvent(QKeyEvent *event);
    virtual void    keyReleaseEvent(QKeyEvent *);
    virtual void    onStarted(QGraphicsScene*);
    virtual void    onStopped(QGraphicsScene *);
private:
    QAction*            m_action;
    QList<QModelIndex>  m_grabbedIndexes;
    QPoint              m_previous;
};

#endif // SELECTMOVECOMMAND_HPP
