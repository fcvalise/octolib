#include "CommandManager.hpp"
#include "AbstractSpriteSheetCommand.hpp"

#include <QActionGroup>

CommandManager::CommandManager(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    m_scene(scene),
    m_group(new QActionGroup(this))
{
    connect(m_group, SIGNAL(triggered(QAction*)), SLOT(selectCommand(QAction*)));
}

CommandManager::~CommandManager()
{
}

AbstractSpriteSheetCommand *CommandManager::currentCommand() const
{
    return (m_currentCommand.data());
}

void CommandManager::restartCurrentCommand()
{
    if (m_currentCommand)
    {
        m_currentCommand->onStarted(m_scene);
    }
}

void CommandManager::addCommand(AbstractSpriteSheetCommand *command, bool enable)
{
    QAction*        action = command->action();
    CommandPointer  commandPtr(command);

    m_mapper.insert(action, commandPtr);
    m_group->addAction(action);
    if (enable)
    {
        action->setChecked(true);
        selectCommand(action);
    }
}

QList<QAction *> CommandManager::commandActions() const
{
    return (m_group->actions());
}

void CommandManager::selectCommand(QAction *action)
{
    CommandPointer  newCommand = m_mapper.value(action, CommandPointer());

    if (m_currentCommand)
    {
        m_currentCommand->onStopped(m_scene);
    }
    m_currentCommand = newCommand;
    if (m_currentCommand)
    {
        m_currentCommand->onStarted(m_scene);
    }
}


