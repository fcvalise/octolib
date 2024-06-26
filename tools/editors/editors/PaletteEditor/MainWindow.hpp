#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QAction;
class QCloseEvent;
class QMenu;

class PaletteEditor;
class Document;
class RecentFileMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void    newPalette();
    void    openPalette();
    void    openPalette(QString filePath);
    bool    savePalette();
    bool    savePaletteAs();

    void    addColor();
    void    addColorFromImage();
    void    addAnaloguous();
    void    addComplementaries();
    void    addTriad();
    void    addSquare();
    void    deleteColor();
    void    deleteAllColors();

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
    PaletteEditor*  m_editor;
    Document*       m_document;
    RecentFileMenu* m_recentFileMenu;
    QAction*        m_newPalette;
    QAction*        m_openPalette;
    QAction*        m_savePalette;
    QAction*        m_savePaletteAs;
    QAction*        m_addColor;
    QAction*        m_addColorFromImage;
    QAction*        m_addAnaloguous;
    QAction*        m_addComplementaries;
    QAction*        m_addTriad;
    QAction*        m_addSquare;
    QAction*        m_deleteColor;
    QAction*        m_deleteAllColors;
};

#endif // MAINWINDOW_HPP
