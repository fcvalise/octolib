#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <QObject>
#include <QMap>
#include <QSharedPointer>

class QGraphicsScene;
class QActionGroup;
class QAction;

class AbstractSpriteSheetCommand;

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(QGraphicsScene* scene, QObject *parent = 0);
    ~CommandManager();

    AbstractSpriteSheetCommand* currentCommand()const;
    void                        restartCurrentCommand();
    void                        addCommand(AbstractSpriteSheetCommand* command, bool enable = false);
    QList<QAction*>             commandActions()const;
public slots:
    void                        selectCommand(QAction* action);
private:
    typedef QSharedPointer<AbstractSpriteSheetCommand>  CommandPointer;
    typedef QMap<QAction*, CommandPointer>              CommandMapper;

    QGraphicsScene* m_scene;
    QActionGroup*   m_group;
    CommandMapper   m_mapper;
    CommandPointer  m_currentCommand;
};

#endif // COMMANDMANAGER_HPP
