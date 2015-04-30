#include "Document.hpp"

Document::Document(QObject *parent) : QObject(parent)
{

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

void Document::newDocumentCreated(const QString &prefix, const QString &extension)
{
    static int  s_counter = 0;

    m_file.setFile(QString("%0%1.%2").arg(prefix).arg(++s_counter).arg(extension));
    setDocumentModified(true);
}

void Document::documentOpened(const QString &filePath)
{
    m_file.setFile(filePath);
    setDocumentModified(false);
}

void Document::documentSaved()
{
    setDocumentModified(false);
}

void Document::documentSavedAs(const QString &filePath)
{
    m_file.setFile(filePath);
    setDocumentModified(false);
}

void Document::setDocumentModified(bool modified)
{
    m_modified = modified;
    emit documentFilePathChanged(m_file.fileName() + "[*]");
    emit documentModified(modified);
}

void Document::setDocumentModified()
{
    setDocumentModified(true);
}
