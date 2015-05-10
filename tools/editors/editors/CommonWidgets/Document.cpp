#include "Document.hpp"

Document::Document(QObject *parent) :
    QObject(parent),
    m_modified(false)
{
    connect(&m_watcher, SIGNAL(fileChanged(QString)), SIGNAL(documentFileModified()));
}

Document::~Document()
{
}

QString Document::absoluteFilePath() const
{
    return (m_file.absoluteFilePath());
}

QString Document::fileName() const
{
    return (m_file.fileName());
}

bool Document::hasExistingFile() const
{
    return (m_file.exists());
}

bool Document::isModified() const
{
    return (m_modified);
}

void Document::enableWatch(bool enable)
{
    QString filePath = m_file.absoluteFilePath();

    if (filePath.isEmpty() == false)
    {
        if (enable)
            m_watcher.addPath(filePath);
        else
            m_watcher.removePath(filePath);
    }
}

void Document::newDocumentCreated(const QString &prefix, const QString &extension)
{
    static int  s_counter = 0;

    setFilePath(QString("%0%1.%2").arg(prefix).arg(++s_counter).arg(extension));
    setDocumentModified(false);
}

void Document::documentOpened(const QString &filePath)
{
    setFilePath(filePath, true);
    setDocumentModified(false);
}

void Document::documentReopened()
{
    setDocumentModified(false);
}

void Document::documentSaved()
{
    setDocumentModified(false);
}

void Document::documentSavedAs(const QString &filePath)
{
    setFilePath(filePath, true);
    setDocumentModified(false);
}

void Document::setDocumentModified(bool modified)
{
    m_modified = modified;
    emit documentFilePathChanged(m_file.fileName() + "[*]");
    emit documentModified(modified);
}

void Document::setFilePath(const QString &filePath, bool watchFile)
{
    if (m_file.absoluteFilePath().isEmpty() == false)
        m_watcher.removePath(m_file.absoluteFilePath());
    m_file.setFile(filePath);
    if (watchFile)
        m_watcher.addPath(filePath);
}

void Document::setDocumentModified()
{
    setDocumentModified(true);
}
