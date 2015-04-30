#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <QObject>
#include <QFileInfo>
#include <QFileSystemWatcher>

/*! \class Document
 *  \brief Manage a document
 *
 */
class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = 0);
    ~Document();

    QString     absoluteFilePath()const;
    QString     fileName()const;
    bool        hasExistingFile()const;
    bool        isModified()const;

    void        enableWatch(bool enable);
signals:
    void        documentFilePathChanged(QString const& filePath);
    void        documentModified(bool modified);
    void        documentFileModified();
public:
    void        newDocumentCreated(QString const& prefix, QString const& extension);
    void        documentOpened(QString const& filePath);
    void        documentReopened();
    void        documentSaved();
    void        documentSavedAs(QString const& filePath);
public slots:
    void        setDocumentModified();
private:
    void        setDocumentModified(bool modified);
    void        setFilePath(QString const& filePath, bool watchFile = false);
private:
    QFileSystemWatcher  m_watcher;
    QFileInfo           m_file;
    bool                m_modified;
};

#endif // DOCUMENT_HPP
