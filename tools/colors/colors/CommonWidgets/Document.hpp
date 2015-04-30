#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <QObject>
#include <QFileInfo>

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
signals:
    void        documentFilePathChanged(QString const& filePath);
    void        documentModified(bool modified);
public:
    void        newDocumentCreated(QString const& prefix, QString const& extension);
    void        documentOpened(QString const& filePath);
    void        documentSaved();
    void        documentSavedAs(QString const& filePath);
public slots:
    void        setDocumentModified();
private:
    void        setDocumentModified(bool modified);
private:
    QFileInfo   m_file;
    bool        m_modified;
};

#endif // DOCUMENT_HPP
