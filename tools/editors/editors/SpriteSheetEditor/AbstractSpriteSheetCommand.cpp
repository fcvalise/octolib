#include "AbstractSpriteSheetCommand.hpp"

#include <QAction>

AbstractSpriteSheetCommand::AbstractSpriteSheetCommand(SpriteSheetModel* model, QItemSelectionModel* selection) :
    m_model(model),
    m_selection(selection)
{
}

AbstractSpriteSheetCommand::~AbstractSpriteSheetCommand()
{
}

void AbstractSpriteSheetCommand::commandActionSetup(QAction *action) const
{
    action->setCheckable(true);
}

SpriteSheetModel *AbstractSpriteSheetCommand::model() const
{
    return (m_model);
}

QItemSelectionModel *AbstractSpriteSheetCommand::selection() const
{
    return (m_selection);
}

