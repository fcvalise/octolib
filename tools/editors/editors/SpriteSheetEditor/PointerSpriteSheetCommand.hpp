#ifndef POINTERSPRITESHEETCOMMAND_HPP
#define POINTERSPRITESHEETCOMMAND_HPP

#include "AbstractSpriteSheetCommand.hpp"

#include <QModelIndex>

class PointerSpriteSheetCommand : public AbstractSpriteSheetCommand
{
public:
    explicit PointerSpriteSheetCommand(SpriteSheetScene* scene);
    ~PointerSpriteSheetCommand();

    virtual QAction *action() const;
    virtual QCursor cursor() const;

    virtual void    mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void    mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    virtual void    keyPressEvent(QKeyEvent *event);
    virtual void    keyReleaseEvent(QKeyEvent *);
    virtual void    onStarted();
    virtual void    onStopped();
private:
    QAction*        m_action;
    QModelIndex     m_grabbedIndex;
    QPointF         m_previous;
};

#endif // POINTERSPRITESHEETCOMMAND_HPP
