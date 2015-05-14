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
    m_saveSpriteSheetAs(nullptr)
{
    setupDocument();
    setupActions();
    setupToolBar();
    setCentralWidget(m_editor);
}

MainWindow::~MainWindow()
{
}

void MainWindow::newSpriteSheet()
{
    QString textureFilePath;
    QPixmap pixmap;

    if (maybeSave())
    {
        textureFilePath = QFileDialog::getOpenFileName(this, tr("Choose a texture"), QString(), tr("Images (*.png *.jpg *.jpeg)"));
        if (pixmap.load(textureFilePath))
        {
            m_document->newDocumentCreated(tr("untitled_sprite_sheet"), "oss");
            m_editor->newSpriteSheet(pixmap);
        }
    }
}

void MainWindow::openSpriteSheet()
{

}

void MainWindow::openSpriteSheet(QString filePath)
{

}

bool MainWindow::saveSpriteSheet()
{
    return (false);
}

bool MainWindow::saveSpriteSheetAs()
{
    return (false);
}

void MainWindow::showAbout()
{
    AboutDialog dialog(QPixmap(":/images/palette_editor.png"), this);

    dialog.exec();
}

void MainWindow::updateAction()
{
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
        //m_editor->openSpriteSheet(m_document->absoluteFilePath());
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
    QMenu*          helpMenu = menuBar->addMenu(tr("Help"));
    QAction*        quit = nullptr;

    m_newSpriteSheet = new QAction(QIcon(":/images/new_sprite_sheet.png"), tr("New..."), this);
    m_openSpriteSheet = new QAction(QIcon(":/images/open_sprite_sheet.png"), tr("Open..."), this);
    m_saveSpriteSheet = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    m_saveSpriteSheetAs = new QAction(QIcon(":/images/save_as.png"), tr("Save as"), this);
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
}

void MainWindow::setupToolBar()
{
    QToolBar*   toolBar = addToolBar(tr("Main tool bar"));

    toolBar->addAction(m_newSpriteSheet);
    toolBar->addSeparator();
    toolBar->addAction(m_openSpriteSheet);
    toolBar->addSeparator();
    toolBar->addAction(m_saveSpriteSheet);
    toolBar->addAction(m_saveSpriteSheetAs);
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
