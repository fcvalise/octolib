#include "AbstractCommand.hpp"

#include <QAction>

AbstractCommand::AbstractCommand(SpriteSheetModel* model, QItemSelectionModel* selection) :
    m_model(model),
    m_selection(selection)
{
}

AbstractCommand::~AbstractCommand()
{
}

void AbstractCommand::commandActionSetup(QAction *action) const
{
    action->setCheckable(true);
}

SpriteSheetModel *AbstractCommand::model() const
{
    return (m_model);
}

QItemSelectionModel *AbstractCommand::selection() const
{
    return (m_selection);
}

