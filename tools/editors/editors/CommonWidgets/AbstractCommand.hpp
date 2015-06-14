#ifndef ABSTRACTCOMMAND_HPP
#define ABSTRACTCOMMAND_HPP
#include <QString>
#include <QIcon>
#include <QCursor>

class QAction;
class QGraphicsSceneMouseEvent;
class QKeyEvent;
class QItemSelectionModel;
class QGraphicsScene;

class SpriteSheetModel;

class AbstractCommand
{
public:
    virtual ~AbstractCommand();

    virtual QAction*    action()const = 0;
    virtual QCursor     cursor()const = 0;

    virtual void        mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void        mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void        mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void        keyPressEvent(QKeyEvent *event) = 0;
    virtual void        keyReleaseEvent(QKeyEvent *event) = 0;
    virtual void        onStarted(QGraphicsScene* scene) = 0;
    virtual void        onStopped(QGraphicsScene* scene) = 0;
};

#endif // ABSTRACTCOMMAND_HPP
