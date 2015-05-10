#include "MainWindow.hpp"
#include "PaletteEditor.hpp"
#include "Document.hpp"
#include "RecentFileMenu.hpp"

#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#include <QIcon>
#include <QToolBar>
#include <QSettings>
#include <AboutDialog.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_editor(new PaletteEditor(this)),
      m_document(new Document(this)),
      m_recentFileMenu(new RecentFileMenu(tr("Open recents"), this)),
      m_newPalette(nullptr),
      m_openPalette(nullptr),
      m_savePalette(nullptr),
      m_savePaletteAs(nullptr),
      m_addColor(nullptr),
      m_addColorFromImage(nullptr),
      m_addAnaloguous(nullptr),
      m_addComplementaries(nullptr),
      m_addTriad(nullptr),
      m_addSquare(nullptr),
      m_deleteColor(nullptr),
      m_deleteAllColors(nullptr)
{
    connect(m_recentFileMenu, SIGNAL(fileClicked(QString)), this, SLOT(openPalette(QString)));
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
        openPalette(filePath);
    }
}

void MainWindow::openPalette(QString filePath)
{
    if (maybeSave() && filePath.isEmpty() == false)
    {
        m_editor->openPalette(filePath);
        m_document->documentOpened(filePath);
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
        m_document->enableWatch(false);
        m_editor->savePalette(m_document->absoluteFilePath());
        m_document->documentSaved();
        m_document->enableWatch(true);
        m_recentFileMenu->addFile(m_document->absoluteFilePath());
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
        m_recentFileMenu->addFile(m_document->absoluteFilePath());
    }
    return (filePath.isEmpty() == false);
}

void MainWindow::addColor()
{
    m_editor->addColor();
}

void MainWindow::addColorFromImage()
{
    m_editor->addColorFromImage(this);
}

void MainWindow::addAnaloguous()
{
    m_editor->addAnaloguous(this);
}

void MainWindow::addComplementaries()
{
    m_editor->addComplementaries(this);
}

void MainWindow::addTriad()
{
    m_editor->addTriad(this);
}

void MainWindow::addSquare()
{
    m_editor->addSquare(this);
}

void MainWindow::deleteColor()
{
    m_editor->removeCurrent();
}

void MainWindow::deleteAllColors()
{
    m_editor->removeAll();
}

void MainWindow::showAbout()
{
    AboutDialog dialog(QPixmap(":/images/palette_editor.png"), this);

    dialog.exec();
}

void MainWindow::updateAction()
{
    bool    isModified = m_document->isModified();

    m_savePalette->setEnabled(isModified);
    m_deleteColor->setEnabled(m_editor->hasSelection());
    m_deleteAllColors->setEnabled(m_editor->isEmpty());
}

void MainWindow::onDocumentFileModified()
{
    QMessageBox     msgBox(QMessageBox::Question,
                           QApplication::applicationName(),
                           tr("The file '%0' has changed outside %1.").arg(m_document->fileName()).arg(QApplication::applicationDisplayName()),
                           QMessageBox::Yes | QMessageBox::No,
                           this);

    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(QApplication::applicationDisplayName());
    msgBox.setInformativeText(tr("Do you want to reload it?"));
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);
    if (msgBox.exec() == QMessageBox::Yes)
    {
        m_editor->openPalette(m_document->absoluteFilePath());
        m_document->documentReopened();
    }
}

void MainWindow::setupDocument()
{
    connect(m_document, &Document::documentFilePathChanged, this, &MainWindow::setWindowTitle);
    connect(m_document, &Document::documentModified, this, &MainWindow::setWindowModified);
    connect(m_document, &Document::documentModified, this, &MainWindow::updateAction);
    connect(m_document, &Document::documentFileModified, this, &MainWindow::onDocumentFileModified);
    connect(m_editor, SIGNAL(modified()), m_document, SLOT(setDocumentModified()));
    connect(m_editor, &PaletteEditor::selectionChanged, this, &MainWindow::updateAction);
}

void MainWindow::setupActions()
{
    QMenuBar*       menuBar = this->menuBar();
    QMenu*          fileMenu = menuBar->addMenu(tr("File"));
    QMenu*          editMenu = menuBar->addMenu(tr("Edit"));
    QMenu*          helpMenu = menuBar->addMenu(tr("Help"));
    QAction*        quit = nullptr;

    m_newPalette = new QAction(QIcon(":/images/new_palette.png"), tr("New..."), this);
    m_openPalette = new QAction(QIcon(":/images/open_palette.png"), tr("Open..."), this);
    m_savePalette = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    m_savePaletteAs = new QAction(QIcon(":/images/save_as.png"), tr("Save as"), this);
    m_addColor = new QAction(QIcon(":/images/add.png"), tr("Add color"), this);
    m_addColorFromImage = new QAction(QIcon(":/images/add.png"), tr("Add colors from image..."), this);
    m_addAnaloguous = new QAction(QIcon(":/images/add.png"), tr("Add analoguous scheme..."), this);
    m_addComplementaries = new QAction(QIcon(":/images/add.png"), tr("Add complementary scheme..."), this);
    m_addTriad = new QAction(QIcon(":/images/add.png"), tr("Add triad scheme..."), this);
    m_addSquare = new QAction(QIcon(":/images/add.png"), tr("Add square scheme..."), this);
    m_deleteColor = new QAction(QIcon(":/images/delete.png"), tr("Remove color"), this);
    m_deleteAllColors = new QAction("Delete all", this);
    m_newPalette->setShortcut(QKeySequence::New);
    m_openPalette->setShortcut(QKeySequence::Open);
    m_savePalette->setShortcut(QKeySequence::Save);
    m_savePaletteAs->setShortcut(QKeySequence::SaveAs);
    m_deleteColor->setShortcut(QKeySequence::Delete);
    fileMenu->addAction(m_newPalette);
    fileMenu->addAction(m_openPalette);
    fileMenu->addMenu(m_recentFileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(m_savePalette);
    fileMenu->addAction(m_savePaletteAs);
    fileMenu->addSeparator();
    quit = fileMenu->addAction(tr("Quit"));
    editMenu->addAction(m_addColor);
    editMenu->addSeparator();
    editMenu->addAction(m_addColorFromImage);
    editMenu->addSeparator();
    editMenu->addAction(m_addAnaloguous);
    editMenu->addAction(m_addComplementaries);
    editMenu->addAction(m_addTriad);
    editMenu->addAction(m_addSquare);
    editMenu->addSeparator();
    editMenu->addAction(m_deleteColor);
    editMenu->addAction(m_deleteAllColors);
    connect(helpMenu->addAction(tr("About...")), &QAction::triggered, this, &MainWindow::showAbout);
    connect(m_newPalette, &QAction::triggered, this, &MainWindow::newPalette);
    connect(m_openPalette, SIGNAL(triggered()), this, SLOT(openPalette()));
    connect(m_savePalette, &QAction::triggered, this, &MainWindow::savePalette);
    connect(m_savePaletteAs, &QAction::triggered, this, &MainWindow::savePaletteAs);
    connect(quit, &QAction::triggered, this, &MainWindow::close);
    connect(m_addColor, &QAction::triggered, this, &MainWindow::addColor);
    connect(m_addColorFromImage, &QAction::triggered, this, &MainWindow::addColorFromImage);
    connect(m_addAnaloguous, &QAction::triggered, this, &MainWindow::addAnaloguous);
    connect(m_addComplementaries, &QAction::triggered, this, &MainWindow::addComplementaries);
    connect(m_addTriad, &QAction::triggered, this, &MainWindow::addTriad);
    connect(m_addSquare, &QAction::triggered, this, &MainWindow::addSquare);
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
                           QApplication::applicationDisplayName(),
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
    m_recentFileMenu->loadSettings(settings);
}

void MainWindow::saveSettings()
{
    QSettings    settings;

    settings.beginGroup("main_window");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();
    m_recentFileMenu->saveSettings(settings);
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
