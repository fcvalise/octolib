#ifndef INTERACTIVEGRAPHICSSCENE_HPP
#define INTERACTIVEGRAPHICSSCENE_HPP
#include "CommandManager.hpp"

#include <QGraphicsScene>

class InteractiveGraphicsScene : public QGraphicsScene
{
public:
    explicit InteractiveGraphicsScene(QObject *parent = nullptr);
    ~InteractiveGraphicsScene();

    void            addCommand(AbstractCommand* command, bool enable);
    void            restartCurrentCommand();
    void            enableCommands(bool enable);
    void            mousePressEvent(QGraphicsSceneMouseEvent *event);
    void            mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void            mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void            keyPressEvent(QKeyEvent *event);
    void            keyReleaseEvent(QKeyEvent *event);
    QList<QAction*> commandActions()const;
private:
    CommandManager  m_commandManager;
    bool            m_commandEnabled;
};

#endif // INTERACTIVEGRAPHICSSCENE_HPP
