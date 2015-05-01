#include "MainWindow.hpp"
#include "WheelEditor.hpp"
#include "Document.hpp"
#include "RecentFileMenu.hpp"
#include "AddOffsetsDialog.hpp"

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
      m_editor(new WheelEditor(this)),
      m_document(new Document(this)),
      m_recentFileMenu(new RecentFileMenu(tr("Open recents"), this)),
      m_newWheel(nullptr),
      m_openWheel(nullptr),
      m_saveWheel(nullptr),
      m_saveWheelAs(nullptr),
      m_addOffset(nullptr),
      m_addOffsets(nullptr),
      m_deleteOffset(nullptr),
      m_deleteAllOffsets(nullptr)
{
    connect(m_recentFileMenu, SIGNAL(fileClicked(QString)), this, SLOT(openWheel(QString)));
    setupDocument();
    setupActions();
    setupToolBar();
    setCentralWidget(m_editor);
    newWheel();
    loadSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::newWheel()
{
    if (maybeSave())
    {
        m_document->newDocumentCreated(tr("untitled_wheel"), "ocw");
        m_editor->newWheel();
    }
}

void MainWindow::openWheel()
{
    QString filePath;

    if (maybeSave())
    {
        filePath = QFileDialog::getOpenFileName(this, tr("Open wheel"), QString(), tr("Wheels (*.ocw)"));
        openWheel(filePath);
    }
}

void MainWindow::openWheel(QString filePath)
{
    if (filePath.isEmpty() == false)
    {
        m_editor->openWheel(filePath);
        m_document->documentOpened(filePath);
    }
}

bool MainWindow::saveWheel()
{
    if (m_document->hasExistingFile() == false)
    {
        return (saveWheelAs());
    }
    else
    {
        m_document->enableWatch(false);
        m_editor->saveWheel(m_document->absoluteFilePath());
        m_document->documentSaved();
        m_document->enableWatch(true);
        m_recentFileMenu->addFile(m_document->absoluteFilePath());
        return (true);
    }
}

bool MainWindow::saveWheelAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save wheel as"), QString(), tr("Wheels (*.ocw)"));

    if (filePath.isEmpty() == false)
    {
        m_editor->saveWheel(filePath);
        m_document->documentSavedAs(filePath);
        m_recentFileMenu->addFile(m_document->absoluteFilePath());
    }
    return (filePath.isEmpty() == false);
}

void MainWindow::addOffset()
{
    m_editor->addOffset();
}

void MainWindow::addOffsets()
{
    AddOffsetsDialog    dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        m_editor->addOffsets(dialog.getInitial(),
                             dialog.getInterval(),
                             dialog.getCount());
    }
}

void MainWindow::deleteOffset()
{
    m_editor->removeCurrent();
}

void MainWindow::deleteAllOffsets()
{
    m_editor->removeAll();
}

void MainWindow::showAbout()
{
    AboutDialog dialog(QPixmap(":/images/wheel_editor.png"), this);

    dialog.exec();
}

void MainWindow::updateAction()
{
    bool    isModified = m_document->isModified();

    m_saveWheel->setEnabled(isModified);
    m_deleteOffset->setEnabled(m_editor->hasSelection());
    m_deleteAllOffsets->setEnabled(m_editor->isEmpty());
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
        m_editor->openWheel(m_document->absoluteFilePath());
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
    connect(m_editor, &WheelEditor::selectionChanged, this, &MainWindow::updateAction);
}

void MainWindow::setupActions()
{
    QMenuBar*       menuBar = this->menuBar();
    QMenu*          fileMenu = menuBar->addMenu(tr("File"));
    QMenu*          editMenu = menuBar->addMenu(tr("Edit"));
    QMenu*          helpMenu = menuBar->addMenu(tr("Help"));
    QAction*        quit = nullptr;

    m_newWheel = new QAction(QIcon(":/images/new_wheel.png"), tr("New..."), this);
    m_openWheel = new QAction(QIcon(":/images/open_wheel.png"), tr("Open..."), this);
    m_saveWheel = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    m_saveWheelAs = new QAction(QIcon(":/images/save_as.png"), tr("Save as"), this);
    m_addOffset = new QAction(QIcon(":/images/add.png"), tr("Add offset"), this);
    m_addOffsets = new QAction(QIcon(":/images/add.png"), tr("Add offsets"), this);
    m_deleteOffset = new QAction(QIcon(":/images/delete.png"), tr("Remove offset"), this);
    m_deleteAllOffsets = new QAction("Delete all", this);
    m_newWheel->setShortcut(QKeySequence::New);
    m_openWheel->setShortcut(QKeySequence::Open);
    m_saveWheel->setShortcut(QKeySequence::Save);
    m_saveWheelAs->setShortcut(QKeySequence::SaveAs);
    m_deleteOffset->setShortcut(QKeySequence::Delete);
    fileMenu->addAction(m_newWheel);
    fileMenu->addAction(m_openWheel);
    fileMenu->addMenu(m_recentFileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(m_saveWheel);
    fileMenu->addAction(m_saveWheelAs);
    fileMenu->addSeparator();
    quit = fileMenu->addAction(tr("Quit"));
    editMenu->addAction(m_addOffset);
    editMenu->addAction(m_addOffsets);
    editMenu->addSeparator();
    editMenu->addAction(m_deleteOffset);
    editMenu->addAction(m_deleteAllOffsets);
    connect(helpMenu->addAction(tr("About...")), &QAction::triggered, this, &MainWindow::showAbout);
    connect(m_newWheel, &QAction::triggered, this, &MainWindow::newWheel);
    connect(m_openWheel, SIGNAL(triggered()), this, SLOT(openWheel()));
    connect(m_saveWheel, &QAction::triggered, this, &MainWindow::saveWheel);
    connect(m_saveWheelAs, &QAction::triggered, this, &MainWindow::saveWheelAs);
    connect(quit, &QAction::triggered, this, &MainWindow::close);
    connect(m_addOffset, &QAction::triggered, this, &MainWindow::addOffset);
    connect(m_addOffsets, &QAction::triggered, this, &MainWindow::addOffsets);
    connect(m_deleteOffset, &QAction::triggered, this, &MainWindow::deleteOffset);
    connect(m_deleteAllOffsets, &QAction::triggered, this, &MainWindow::deleteAllOffsets);
}

void MainWindow::setupToolBar()
{
    QToolBar*   toolBar = addToolBar(tr("Main tool bar"));

    toolBar->addAction(m_newWheel);
    toolBar->addSeparator();
    toolBar->addAction(m_openWheel);
    toolBar->addSeparator();
    toolBar->addAction(m_saveWheel);
    toolBar->addAction(m_saveWheelAs);
    toolBar->addSeparator();
    toolBar->addAction(m_addOffset);
    toolBar->addAction(m_deleteOffset);
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
            result = saveWheel();
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
