#include "InteractiveGraphicsScene.hpp"
#include "AbstractCommand.hpp"

InteractiveGraphicsScene::InteractiveGraphicsScene(QObject *parent) :
    QGraphicsScene(parent),
    m_commandManager(this),
    m_commandEnabled(true)
{
}


InteractiveGraphicsScene::~InteractiveGraphicsScene()
{
}

void InteractiveGraphicsScene::addCommand(AbstractCommand *command, bool enable)
{
    m_commandManager.addCommand(command, enable);
}


void InteractiveGraphicsScene::restartCurrentCommand()
{
    m_commandManager.restartCurrentCommand();
}


void InteractiveGraphicsScene::enableCommands(bool enable)
{
    m_commandEnabled = enable;
    if (enable == false)
        m_commandManager.selectCommand(nullptr);
}


void InteractiveGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractCommand* command = m_commandManager.currentCommand();

    if (m_commandEnabled && command)
        command->mousePressEvent(event);
}


void InteractiveGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractCommand* command = m_commandManager.currentCommand();

    if (m_commandEnabled && command)
        command->mouseMoveEvent(event);
    QGraphicsScene::mouseMoveEvent(event);
}


void InteractiveGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractCommand* command = m_commandManager.currentCommand();

    if (m_commandEnabled && command)
        command->mouseReleaseEvent(event);
}


void InteractiveGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    AbstractCommand* command = m_commandManager.currentCommand();

    if (m_commandEnabled && command)
        command->keyPressEvent(event);
}


void InteractiveGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    AbstractCommand* command = m_commandManager.currentCommand();

    if (m_commandEnabled && command)
        command->keyReleaseEvent(event);
}


QList<QAction *> InteractiveGraphicsScene::commandActions() const
{
    return (m_commandManager.commandActions());
}
