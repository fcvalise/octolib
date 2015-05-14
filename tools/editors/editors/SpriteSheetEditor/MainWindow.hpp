#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class Document;
class RecentFileMenu;
class SpriteSheetEditor;

class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void    newSpriteSheet();
    void    openSpriteSheet();
    void    openSpriteSheet(QString filePath);
    bool    saveSpriteSheet();
    bool    saveSpriteSheetAs();

    void    updateAction();
    void    onDocumentFileModified();

    void    showAbout();
protected:
    void closeEvent(QCloseEvent *event);
private:
    void    setupDocument();
    void    setupActions();
    void    setupToolBar();
    bool    maybeSave();
    void    loadSettings();
    void    saveSettings();
private:
    Document*           m_document;
    RecentFileMenu*     m_recentFileMenu;
    SpriteSheetEditor*  m_editor;
    QAction*            m_newSpriteSheet;
    QAction*            m_openSpriteSheet;
    QAction*            m_saveSpriteSheet;
    QAction*            m_saveSpriteSheetAs;
};

#endif // MAINWINDOW_HPP
