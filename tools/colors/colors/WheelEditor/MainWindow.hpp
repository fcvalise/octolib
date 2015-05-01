#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QAction;
class QCloseEvent;
class QMenu;

class WheelEditor;
class Document;
class RecentFileMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void    newWheel();
    void    openWheel();
    void    openWheel(QString filePath);
    bool    saveWheel();
    bool    saveWheelAs();

    void    addOffset();
    void    addOffsets();

    void    deleteOffset();
    void    deleteAllOffsets();

    void    showAbout();

    void    updateAction();
    void    onDocumentFileModified();
private:
    void    setupDocument();
    void    setupActions();
    void    setupToolBar();
    bool    maybeSave();
    void    loadSettings();
    void    saveSettings();
protected:
    void    closeEvent(QCloseEvent* event);
private:
    WheelEditor*    m_editor;
    Document*       m_document;
    RecentFileMenu* m_recentFileMenu;
    QAction*        m_newWheel;
    QAction*        m_openWheel;
    QAction*        m_saveWheel;
    QAction*        m_saveWheelAs;
    QAction*        m_addOffset;
    QAction*        m_addOffsets;
    QAction*        m_deleteOffset;
    QAction*        m_deleteAllOffsets;
};

#endif // MAINWINDOW_HPP
