#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <QObject>
#include <QMap>
#include <QSharedPointer>

class QActionGroup;
class QAction;

class AbstractSpriteSheetCommand;

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(QObject *parent = 0);
    ~CommandManager();

    AbstractSpriteSheetCommand* currentCommand()const;
    void                        addCommand(AbstractSpriteSheetCommand* command);
    QList<QAction*>             commandActions()const;
private slots:
    void                        selectCommand(QAction* action);
private:
    typedef QSharedPointer<AbstractSpriteSheetCommand>  CommandPointer;
    typedef QMap<QAction*, CommandPointer>              CommandMapper;

    QActionGroup*   m_group;
    CommandMapper   m_mapper;
    CommandPointer  m_currentCommand;
};

#endif // COMMANDMANAGER_HPP
