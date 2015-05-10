#ifndef RECENTFILEMENU_HPP
#define RECENTFILEMENU_HPP

#include <QMenu>

class RecentFileMenuPrivate;

class QSettings;

class RecentFileMenu : public QMenu
{
    Q_OBJECT
public:
    explicit RecentFileMenu(const QString& title,QWidget *parent = 0);
public slots:
    void addFile(const QString& filePath);

    void removeFile(const QString& filePath);

    void clear();
public:
    bool contains(const QString& filePath)const;
    void setFilePaths(const QStringList& filePaths);
    QStringList filePaths()const;
    void setMaximumPath(int max);
    void saveSettings(QSettings &settings)const;
    void loadSettings(QSettings& settings);
signals:
    void fileClicked(const QString& filePath);
private:
    RecentFileMenuPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(RecentFileMenu)
};

#endif // RECENTFILEMENU_HPP
