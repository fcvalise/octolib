#include "RecentFileMenu.hpp"

#include <QList>
#include <QAction>
#include <QFileInfo>
#include <QSettings>

class RecentFileMenuPrivate : public QObject
{
    Q_OBJECT

    RecentFileMenu* q_ptr;
    Q_DECLARE_PUBLIC(RecentFileMenu)

    struct ActionPath
    {
        ActionPath() :
            action(0)
        {}

        ActionPath(QAction* nAction,const QString& nPath) :
            action(nAction),
            path(nPath)
        {}

        QAction* action;
        QString path;
    };

public:
    RecentFileMenuPrivate(RecentFileMenu* q) :
        QObject(q),
        q_ptr(q),
        m_maxEntries(0)
    {
        update();
    }

    QAction* createAction(const QString& filePath)
    {
        Q_Q(RecentFileMenu);
        QFileInfo fileInfo(filePath);

        QAction* const action = new QAction(fileInfo.fileName(),q);
        action->setToolTip(filePath);
        action->setStatusTip(tr("Open \"%0\"").arg(filePath));
        action->setEnabled(fileInfo.exists());

        return action;
    }

    bool containsFilePath(const QString& filePath)const
    {
        foreach(const ActionPath& actionPath,m_actionPaths)
        {
            if( actionPath.path == filePath )
            {
                return true;
            }
        }
        return false;
    }

    void movePathToTheTop(const QString& filePath)
    {
        Q_Q(RecentFileMenu);

        for(ActionPathList::Iterator it = m_actionPaths.begin();it != m_actionPaths.end();++it)
        {
            if( it->path == filePath )
            {
                ActionPath temp = *it;
                m_actionPaths.erase(it);
                m_actionPaths.push_front(temp);

                q->removeAction(temp.action);
                addAction(temp.action);
                break;
            }
        }
    }

    void addAction(QAction* action)
    {
        Q_Q(RecentFileMenu);

        QAction* tempFirstAction = 0;
        if( !q->actions().isEmpty() )
        {
            tempFirstAction = q->actions().front();
        }

        q->insertAction(tempFirstAction,action);
    }

    void removeAction(QAction* action)
    {
        Q_Q(RecentFileMenu);
        q->removeAction(action);
    }

    void update()
    {
        Q_Q(RecentFileMenu);
        q->setEnabled(!m_actionPaths.isEmpty());
    }

private slots:
    void onTriggered(QAction* action)
    {
        Q_Q(RecentFileMenu);
        foreach(const ActionPath& actionPath,m_actionPaths)
        {
            if( actionPath.action == action )
            {
                emit q->fileClicked(actionPath.path);
                return;
            }
        }
    }
public:
    typedef QList<ActionPath> ActionPathList;
    ActionPathList m_actionPaths;
    int m_maxEntries;
};

RecentFileMenu::RecentFileMenu(const QString& title,QWidget *parent) :
    QMenu(title,parent),
    d_ptr(new RecentFileMenuPrivate(this))
{
    connect(this,SIGNAL(triggered(QAction*)),d_ptr,SLOT(onTriggered(QAction*)));
    setMaximumPath(20);
}

void RecentFileMenu::addFile(const QString &filePath)
{
    Q_D(RecentFileMenu);

    if( !filePath.isEmpty() )
    {
        if( d->containsFilePath(filePath) )
        {
            d->movePathToTheTop(filePath);
        }
        else
        {
            QAction* const action = d->createAction(filePath);
            d->m_actionPaths.push_front(RecentFileMenuPrivate::ActionPath(action,filePath));
            d->addAction(action);

            if( (d->m_maxEntries > 0) && d->m_actionPaths.count() > d->m_maxEntries )
            {
                RecentFileMenuPrivate::ActionPath temp = d->m_actionPaths.back();
                removeFile(temp.path);
            }
        }
        d->update();
    }
}

void RecentFileMenu::removeFile(const QString &filePath)
{
    Q_D(RecentFileMenu);

    for(RecentFileMenuPrivate::ActionPathList::Iterator it = d->m_actionPaths.begin();it != d->m_actionPaths.end();)
    {
        if( it->path == filePath )
        {
            d->removeAction(it->action);
            delete it->action;
            it = d->m_actionPaths.erase(it);
        }
        else
        {
            ++it;
        }
    }
    d->update();
}

bool RecentFileMenu::contains(const QString &filePath) const
{
    Q_D(const RecentFileMenu);

    return (d->containsFilePath(filePath));
}

void RecentFileMenu::setFilePaths(const QStringList &filePaths)
{
    foreach(const QString& filePath,filePaths)
    {
        addFile(filePath);
    }
}

QStringList RecentFileMenu::filePaths() const
{
    Q_D(const RecentFileMenu);

    QStringList results;
    foreach(const RecentFileMenuPrivate::ActionPath& actionPath,d->m_actionPaths)
    {
        if( QFile::exists(actionPath.path))
        {
            results.append(actionPath.path);
        }
    }
    return results;
}

void RecentFileMenu::setMaximumPath(int max)
{
    Q_D(RecentFileMenu);
    d->m_maxEntries = max;

    if(d->m_maxEntries > 0)
    {
        while(d->m_actionPaths.count() > d->m_maxEntries)
        {
            RecentFileMenuPrivate::ActionPath temp = d->m_actionPaths.back();
            removeFile(temp.path);
        }
    }
}

void RecentFileMenu::saveSettings(QSettings& settings) const
{
    Q_D(const RecentFileMenu);
    int i = 0;

    settings.beginGroup("recent_file_menu");
    settings.setValue("max_entries", d->m_maxEntries);
    settings.beginWriteArray("paths", d->m_actionPaths.size());
    for (auto path : filePaths())
    {
        settings.setArrayIndex(i++);
        settings.setValue("path", path);
    }
    settings.endArray();
    settings.endGroup();
}

void RecentFileMenu::loadSettings(QSettings &settings)
{
    QStringList paths;
    int         maxEntries = 0;
    int         count = 0;

    settings.beginGroup("recent_file_menu");
    maxEntries = settings.value("max_entries", 0).toInt();
    count = settings.beginReadArray("paths");
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        paths.push_front(settings.value("path").toString());
    }
    settings.endArray();
    settings.endGroup();
    setMaximumPath(maxEntries);
    setFilePaths(paths);

}

void RecentFileMenu::clear()
{
    Q_D(RecentFileMenu);

    for(RecentFileMenuPrivate::ActionPathList::Iterator it = d->m_actionPaths.begin();it != d->m_actionPaths.end();)
    {
        d->removeAction(it->action);
        delete it->action;
        it = d->m_actionPaths.erase(it);
    }

    d->update();
}

#include "RecentFileMenu.moc"
