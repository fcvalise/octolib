#ifndef RECTANGLESPRITESHEETCOMMAND_HPP
#define RECTANGLESPRITESHEETCOMMAND_HPP
#include "AbstractSpriteSheetCommand.hpp"

class QAction;
class QGraphicsRectItem;

class RectangleSpriteSheetCommand : public QObject, public AbstractSpriteSheetCommand
{
    Q_OBJECT
public:
    explicit RectangleSpriteSheetCommand(SpriteSheetScene* scene);
    ~RectangleSpriteSheetCommand();

    virtual QAction *action() const;
    virtual QCursor cursor() const;
    virtual void    mousePressEvent(QGraphicsSceneMouseEvent *);
    virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void    mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    virtual void    keyPressEvent(QKeyEvent *);
    virtual void    keyReleaseEvent(QKeyEvent *);
    virtual void    onStarted();
    virtual void    onStopped();
private:
    QPointF             m_previous;
    QAction*            m_action;
    QGraphicsRectItem*  m_ghost;
};

#endif // RECTANGLESPRITESHEETCOMMAND_HPP
