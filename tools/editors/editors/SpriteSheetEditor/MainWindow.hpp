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
    void    resetTexture();
private slots:
    void    updateAction();
    void    onDocumentFileModified();
    void    showAbout();
protected:
    void    closeEvent(QCloseEvent *event);
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

    QAction*            m_selectAllTiles;
    QAction*            m_copySelectedTiles;
    QAction*            m_cutSelectedTiles;
    QAction*            m_pasteTiles;
    QAction*            m_createTileByDivision;
    QAction*            m_deleteSelectedTiles;
    QAction*            m_sortTiles;
    QAction*            m_resetTexture;

    QAction*            m_zoomIn;
    QAction*            m_zoomOut;
    QAction*            m_zoomZero;
    QAction*            m_zoomToFit;
};

#endif // MAINWINDOW_HPP
