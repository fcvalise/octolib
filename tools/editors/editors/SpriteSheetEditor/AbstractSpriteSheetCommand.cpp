#include "AbstractSpriteSheetCommand.hpp"

#include <QAction>

AbstractSpriteSheetCommand::AbstractSpriteSheetCommand(SpriteSheetScene *scene) :
    m_scene(scene)
{
}

AbstractSpriteSheetCommand::~AbstractSpriteSheetCommand()
{
}

void AbstractSpriteSheetCommand::commandActionSetup(QAction *action) const
{
    action->setCheckable(true);
}

SpriteSheetScene *AbstractSpriteSheetCommand::scene() const
{
    return (m_scene);
}

