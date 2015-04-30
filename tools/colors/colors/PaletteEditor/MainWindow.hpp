#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QAction;
class QCloseEvent;

class PaletteEditor;
class Document;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void    newPalette();
    void    openPalette();
    bool    savePalette();
    bool    savePaletteAs();

    void    addColor();
    void    deleteColor();
    void    deleteAllColors();

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
    QAction*        m_newPalette;
    QAction*        m_openPalette;
    QAction*        m_savePalette;
    QAction*        m_savePaletteAs;
    QAction*        m_addColor;
    QAction*        m_deleteColor;
    QAction*        m_deleteAllColors;
};

#endif // MAINWINDOW_HPP
