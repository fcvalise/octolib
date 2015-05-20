#include "MainWindow.hpp"
#include "SpriteSheetEditor.hpp"

#include <Document.hpp>
#include <RecentFileMenu.hpp>
#include <AboutDialog.hpp>

#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_document(new Document(this)),
    m_recentFileMenu(new RecentFileMenu(tr("Open recents"), this)),
    m_editor(new SpriteSheetEditor(this)),
    m_newSpriteSheet(nullptr),
    m_openSpriteSheet(nullptr),
    m_saveSpriteSheet(nullptr),
    m_saveSpriteSheetAs(nullptr),
    m_generateRectangles(nullptr),
    m_deleteRectangle(nullptr),
    m_sortRectangles(nullptr),
    m_zoomIn(nullptr),
    m_zoomOut(nullptr),
    m_zoomZero(nullptr),
    m_zoomToFit(nullptr)
{
    connect(m_recentFileMenu, SIGNAL(fileClicked(QString)), this, SLOT(openSpriteSheet(QString)));
    setupDocument();
    setupActions();
    setupToolBar();
    setCentralWidget(m_editor);
    updateAction();
    loadSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::newSpriteSheet()
{
    QString textureFilePath;

    if (maybeSave())
    {
        textureFilePath = QFileDialog::getOpenFileName(this, tr("Choose a texture"), QString(), tr("Images (*.png *.jpg *.jpeg)"));
        if (textureFilePath.isEmpty() == false)
        {
            m_document->newDocumentCreated(tr("untitled_sprite_sheet"), "oss");
            m_editor->newSpriteSheet(textureFilePath);
            m_editor->zoomToFit();
        }
    }
}

void MainWindow::openSpriteSheet()
{
    QString filePath;

    if (maybeSave())
    {
        filePath = QFileDialog::getOpenFileName(this, tr("Open sprite sheet"), QString(), tr("Sprite sheet (*.oss)"));
        openSpriteSheet(filePath);
    }
}

void MainWindow::openSpriteSheet(QString filePath)
{
    if (maybeSave() && filePath.isEmpty() == false)
    {
        m_editor->openSpriteSheet(filePath);
        m_document->documentOpened(filePath);
        m_editor->zoomToFit();
    }
}

bool MainWindow::saveSpriteSheet()
{
    if (m_document->hasExistingFile() == false)
    {
        return (saveSpriteSheetAs());
    }
    else
    {
        m_editor->sortRectangles();
        m_document->enableWatch(false);
        m_editor->saveSpriteSheet(m_document->absoluteFilePath());
        m_document->documentSaved();
        m_document->enableWatch(true);
        m_recentFileMenu->addFile(m_document->absoluteFilePath());
        return (true);
    }
}

bool MainWindow::saveSpriteSheetAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save sprite sheet as"), QString(), tr("Sprite sheets (*.oss)"));

    if (filePath.isEmpty() == false)
    {
        m_editor->sortRectangles();
        m_editor->saveSpriteSheet(filePath);
        m_document->documentSavedAs(filePath);
        m_recentFileMenu->addFile(m_document->absoluteFilePath());
    }
    return (filePath.isEmpty() == false);
}

void MainWindow::deleteRectangle()
{
    m_editor->deleteCurrentRectangle();
}

void MainWindow::deleteAllRectangles()
{
    m_editor->deleteAllRectangles();
}

void MainWindow::generateRectangles()
{
    m_editor->generateRectangles(this);
}

void MainWindow::showAbout()
{
    AboutDialog dialog(QPixmap(":/images/sprite_sheet_editor.png"), this);

    dialog.exec();
}

void MainWindow::updateAction()
{
    bool    hasDocument = m_document->hasDocument();
    bool    isModified = m_document->isModified();

    m_generateRectangles->setEnabled(hasDocument);
    m_sortRectangles->setEnabled(hasDocument);
    m_deleteRectangle->setEnabled(hasDocument && m_editor->hasSelection());
    m_saveSpriteSheet->setEnabled(isModified);
    m_saveSpriteSheetAs->setEnabled(hasDocument);
    m_zoomIn->setEnabled(hasDocument);
    m_zoomOut->setEnabled(hasDocument);
    m_zoomZero->setEnabled(hasDocument);
    m_zoomToFit->setEnabled(hasDocument);
    m_editor->setEnabled(hasDocument);
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
        m_editor->openSpriteSheet(m_document->absoluteFilePath());
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
    connect(m_editor, &SpriteSheetEditor::selectionChanged, this, &MainWindow::updateAction);
}

void MainWindow::setupActions()
{
    QMenuBar*       menuBar = this->menuBar();
    QMenu*          fileMenu = menuBar->addMenu(tr("File"));
    QMenu*          editMenu = menuBar->addMenu(tr("Edit"));
    QMenu*          viewMenu = menuBar->addMenu(tr("View"));
    QMenu*          helpMenu = menuBar->addMenu(tr("Help"));
    QAction*        quit = nullptr;

    m_newSpriteSheet = new QAction(QIcon(":/images/new_sprite_sheet.png"), tr("New..."), this);
    m_openSpriteSheet = new QAction(QIcon(":/images/open_sprite_sheet.png"), tr("Open..."), this);
    m_saveSpriteSheet = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    m_saveSpriteSheetAs = new QAction(QIcon(":/images/save_as.png"), tr("Save as..."), this);
    m_generateRectangles = new QAction(tr("Generate rectangles..."), this);
    m_sortRectangles = new QAction(tr("Sort rectangles"), this);
    m_deleteRectangle = new QAction(QIcon(":/images/remove_rectangle.png"), tr("Delete rectangle"), this);
    m_deleteAllRectangles = new QAction(tr("Delete all rectangles"), this);
    m_zoomIn = new QAction(QIcon(":/images/zoom_in.png"), tr("Zoom in"), this);
    m_zoomOut = new QAction(QIcon(":/images/zoom_out.png"), tr("Zoom out"), this);
    m_zoomZero = new QAction(QIcon(":/images/zoom_actual.png"), tr("Zoom 1:1"), this);
    m_zoomToFit = new QAction(QIcon(":/images/zoom_fit.png"), tr("Zoom to fit"), this);
    // File
    m_newSpriteSheet->setShortcut(QKeySequence::New);
    m_openSpriteSheet->setShortcut(QKeySequence::Open);
    m_saveSpriteSheet->setShortcut(QKeySequence::Save);
    m_saveSpriteSheetAs->setShortcut(QKeySequence::SaveAs);
    fileMenu->addAction(m_newSpriteSheet);
    fileMenu->addAction(m_openSpriteSheet);
    fileMenu->addMenu(m_recentFileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(m_saveSpriteSheet);
    fileMenu->addAction(m_saveSpriteSheetAs);
    fileMenu->addSeparator();
    quit = fileMenu->addAction(tr("Quit"));
    connect(helpMenu->addAction(tr("About...")), &QAction::triggered, this, &MainWindow::showAbout);
    connect(m_newSpriteSheet, &QAction::triggered, this, &MainWindow::newSpriteSheet);
    connect(m_openSpriteSheet, SIGNAL(triggered()), this, SLOT(openSpriteSheet()));
    connect(m_saveSpriteSheet, &QAction::triggered, this, &MainWindow::saveSpriteSheet);
    connect(m_saveSpriteSheetAs, &QAction::triggered, this, &MainWindow::saveSpriteSheetAs);
    connect(quit, &QAction::triggered, this, &MainWindow::close);
    // Edit
    m_deleteRectangle->setShortcut(QKeySequence::Delete);
    editMenu->addAction(m_generateRectangles);
    editMenu->addSeparator();
    editMenu->addAction(m_deleteRectangle);
    editMenu->addAction(m_deleteAllRectangles);
    editMenu->addSeparator();
    editMenu->addAction(m_sortRectangles);
    connect(m_generateRectangles, &QAction::triggered, this, &MainWindow::generateRectangles);
    connect(m_sortRectangles, &QAction::triggered, m_editor, &SpriteSheetEditor::sortRectangles);
    connect(m_deleteRectangle, &QAction::triggered, this, &MainWindow::deleteRectangle);
    connect(m_deleteAllRectangles, &QAction::triggered, this, &MainWindow::deleteAllRectangles);
    // View
    viewMenu->addAction(m_zoomIn);
    viewMenu->addAction(m_zoomOut);
    viewMenu->addAction(m_zoomZero);
    viewMenu->addAction(m_zoomToFit);
    connect(m_zoomIn, &QAction::triggered, m_editor, &SpriteSheetEditor::zoomIn);
    connect(m_zoomOut, &QAction::triggered, m_editor, &SpriteSheetEditor::zoomOut);
    connect(m_zoomZero, &QAction::triggered, m_editor, &SpriteSheetEditor::zoomZero);
    connect(m_zoomToFit, &QAction::triggered, m_editor, &SpriteSheetEditor::zoomToFit);
    loadSettings();
}

void MainWindow::setupToolBar()
{
    QToolBar*   toolBar = addToolBar(tr("Main tool bar"));
    QToolBar*   commandToolBar = addToolBar(tr("Commands tool bar"));

    toolBar->setIconSize(QSize(16, 16));
    toolBar->setObjectName("main_tool_bar");
    toolBar->addAction(m_newSpriteSheet);
    toolBar->addSeparator();
    toolBar->addAction(m_openSpriteSheet);
    toolBar->addSeparator();
    toolBar->addAction(m_saveSpriteSheet);
    toolBar->addAction(m_saveSpriteSheetAs);
    toolBar->addSeparator();
    toolBar->addAction(m_zoomIn);
    toolBar->addAction(m_zoomOut);
    toolBar->addAction(m_zoomZero);
    toolBar->addAction(m_zoomToFit);
    commandToolBar->setObjectName("commands_tool_bar");
    commandToolBar->setIconSize(QSize(16, 16));
    commandToolBar->addActions(m_editor->commandActions());
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
            result = saveSpriteSheet();
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
