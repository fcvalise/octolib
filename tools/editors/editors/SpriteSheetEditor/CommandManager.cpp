#include "CommandManager.hpp"
#include "AbstractSpriteSheetCommand.hpp"

#include <QActionGroup>

CommandManager::CommandManager(QObject *parent) :
    QObject(parent),
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

void CommandManager::addCommand(AbstractSpriteSheetCommand *command)
{
    QAction*        action = command->action();
    CommandPointer  commandPtr(command);

    m_mapper.insert(action, commandPtr);
    // First command added is defined as default command
    if (m_group->actions().isEmpty())
    {
        action->setChecked(true);
        m_currentCommand = commandPtr;
        m_currentCommand->onStarted();
    }
    m_group->addAction(action);
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
        m_currentCommand->onStopped();
    }
    m_currentCommand = newCommand;
    if (m_currentCommand)
    {
        m_currentCommand->onStarted();
    }
}


