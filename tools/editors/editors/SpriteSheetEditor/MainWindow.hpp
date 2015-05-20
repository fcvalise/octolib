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

    void    deleteRectangle();
    void    deleteAllRectangles();
    void    generateRectangles();
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

    QAction*            m_generateRectangles;
    QAction*            m_deleteRectangle;
    QAction*            m_deleteAllRectangles;
    QAction*            m_sortRectangles;

    QAction*            m_zoomIn;
    QAction*            m_zoomOut;
    QAction*            m_zoomZero;
    QAction*            m_zoomToFit;
};

#endif // MAINWINDOW_HPP
