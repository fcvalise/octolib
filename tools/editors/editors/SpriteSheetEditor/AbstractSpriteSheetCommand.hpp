#ifndef ABSTRACTSPRITESHEETCOMMAND_HPP
#define ABSTRACTSPRITESHEETCOMMAND_HPP
#include <QString>
#include <QIcon>
#include <QCursor>

class QAction;
class QGraphicsSceneMouseEvent;
class QKeyEvent;

class SpriteSheetScene;

class AbstractSpriteSheetCommand
{
public:
    explicit AbstractSpriteSheetCommand(SpriteSheetScene* scene);
    virtual ~AbstractSpriteSheetCommand();

    virtual QAction*    action()const = 0;
    virtual QCursor     cursor()const = 0;

    virtual void        mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void        mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void        mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void        keyPressEvent(QKeyEvent *event) = 0;
    virtual void        keyReleaseEvent(QKeyEvent *event) = 0;
    virtual void        onStarted() = 0;
    virtual void        onStopped() = 0;
protected:
    void                commandActionSetup(QAction* action)const;
    SpriteSheetScene*   scene()const;
private:
    SpriteSheetScene* const m_scene;
};

#endif // ABSTRACTSPRITESHEETCOMMAND_HPP
