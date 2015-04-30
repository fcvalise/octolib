#include "MainWindow.hpp"
#include "PaletteEditor.hpp"
#include "Document.hpp"

#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#include <QIcon>
#include <QToolBar>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_editor(new PaletteEditor(this)),
      m_document(new Document(this)),
      m_newPalette(nullptr),
      m_openPalette(nullptr),
      m_savePalette(nullptr),
      m_savePaletteAs(nullptr),
      m_addColor(nullptr),
      m_deleteColor(nullptr),
      m_deleteAllColors(nullptr)
{
    setupDocument();
    setupActions();
    setupToolBar();
    setCentralWidget(m_editor);
    newPalette();
    loadSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::newPalette()
{
    if (maybeSave())
    {
        m_document->newDocumentCreated(tr("untitled_palette"), "opa");
        m_editor->newPalette();
    }
}

void MainWindow::openPalette()
{
    QString filePath;

    if (maybeSave())
    {
        filePath = QFileDialog::getOpenFileName(this, tr("Open palette"), QString(), tr("Palettes (*.opa)"));
        if (filePath.isEmpty() == false)
        {
            m_editor->openPalette(filePath);
            m_document->documentOpened(filePath);
        }
    }
}

bool MainWindow::savePalette()
{
    if (m_document->hasExistingFile() == false)
    {
        return (savePaletteAs());
    }
    else
    {
        m_editor->savePalette(m_document->absoluteFilePath());
        m_document->documentSaved();
        return (true);
    }
}

bool MainWindow::savePaletteAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save palette as"), QString(), tr("Palettes (*.opa)"));

    if (filePath.isEmpty() == false)
    {
        m_editor->savePalette(filePath);
        m_document->documentSavedAs(filePath);
    }
    return (filePath.isEmpty() == false);
}

void MainWindow::addColor()
{
    m_editor->addColor();
}

void MainWindow::deleteColor()
{
    m_editor->removeCurrent();
}

void MainWindow::deleteAllColors()
{
    m_editor->removeAll();
}

void MainWindow::updateAction()
{
    bool    isModified = m_document->isModified();

    m_savePalette->setEnabled(isModified);
    m_deleteColor->setEnabled(m_editor->hasSelection());
    m_deleteAllColors->setEnabled(m_editor->hasSomeColors());
}

void MainWindow::setupDocument()
{
    connect(m_document, &Document::documentFilePathChanged, this, &MainWindow::setWindowTitle);
    connect(m_document, &Document::documentModified, this, &MainWindow::setWindowModified);
    connect(m_document, &Document::documentModified, this, &MainWindow::updateAction);
    connect(m_editor, SIGNAL(modified()), m_document, SLOT(setDocumentModified()));
    connect(m_editor, &PaletteEditor::selectionChanged, this, &MainWindow::updateAction);
}

void MainWindow::setupActions()
{
    QMenuBar*       menuBar = this->menuBar();
    QMenu*          fileMenu = menuBar->addMenu(tr("File"));
    QMenu*          editMenu = menuBar->addMenu(tr("Edit"));
    QAction*        quit = nullptr;

    m_newPalette = new QAction(QIcon(":/images/new_palette.png"), tr("New..."), this);
    m_openPalette = new QAction(QIcon(":/images/open_palette.png"), tr("Open..."), this);
    m_savePalette = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    m_savePaletteAs = new QAction(QIcon(":/images/save_as.png"), tr("Save as"), this);
    m_addColor = new QAction(QIcon(":/images/add.png"), tr("Add color"), this);
    m_deleteColor = new QAction(QIcon(":/images/delete.png"), tr("Remove color"), this);
    m_deleteAllColors = new QAction("Delete all", this);
    m_newPalette->setShortcut(QKeySequence::New);
    m_openPalette->setShortcut(QKeySequence::Open);
    m_savePalette->setShortcut(QKeySequence::Save);
    m_savePaletteAs->setShortcut(QKeySequence::SaveAs);
    m_deleteColor->setShortcut(QKeySequence::Delete);
    fileMenu->addAction(m_newPalette);
    fileMenu->addAction(m_openPalette);
    fileMenu->addSeparator();
    fileMenu->addAction(m_savePalette);
    fileMenu->addAction(m_savePaletteAs);
    fileMenu->addSeparator();
    quit = fileMenu->addAction(tr("Quit"));
    editMenu->addAction(m_addColor);
    editMenu->addSeparator();
    editMenu->addAction(m_deleteColor);
    editMenu->addAction(m_deleteAllColors);
    connect(m_newPalette, &QAction::triggered, this, &MainWindow::newPalette);
    connect(m_openPalette, &QAction::triggered, this, &MainWindow::openPalette);
    connect(m_savePalette, &QAction::triggered, this, &MainWindow::savePalette);
    connect(m_savePaletteAs, &QAction::triggered, this, &MainWindow::savePaletteAs);
    connect(quit, &QAction::triggered, this, &MainWindow::close);
    connect(m_addColor, &QAction::triggered, this, &MainWindow::addColor);
    connect(m_deleteColor, &QAction::triggered, this, &MainWindow::deleteColor);
    connect(m_deleteAllColors, &QAction::triggered, this, &MainWindow::deleteAllColors);
}

void MainWindow::setupToolBar()
{
    QToolBar*   toolBar = addToolBar(tr("Main tool bar"));

    toolBar->addAction(m_newPalette);
    toolBar->addSeparator();
    toolBar->addAction(m_openPalette);
    toolBar->addSeparator();
    toolBar->addAction(m_savePalette);
    toolBar->addAction(m_savePaletteAs);
    toolBar->addSeparator();
    toolBar->addAction(m_addColor);
    toolBar->addAction(m_deleteColor);
    toolBar->setIconSize(QSize(16, 16));
    toolBar->setObjectName("main_tool_bar");
}

bool MainWindow::maybeSave()
{
    int             msgResult = 0;
    bool            result = true;
    QMessageBox     msgBox(QMessageBox::Question,
                           QApplication::applicationName(),
                           tr("The current document '%0' has been modified.").arg(m_document->fileName()),
                           QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                           this);

    if (m_document->isModified())
    {
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle(QApplication::applicationName());
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setEscapeButton(QMessageBox::Cancel);
        msgResult = msgBox.exec();
        switch (msgResult)
        {
        case QMessageBox::Save:
            result = savePalette();
            break;
        case QMessageBox::Discard:
            result = true;
            break;
        case QMessageBox::Cancel:
            result = false;
            break;
        }
    }
    return (result);
}

void MainWindow::loadSettings()
{
    QSettings    settings;

    settings.beginGroup("main_window");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings    settings;

    settings.beginGroup("main_window");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
    {
        event->setAccepted(true);
        saveSettings();
    }
    else
    {
        event->setAccepted(false);
    }
}
