#ifndef PALETTEMODEL_HPP
#define PALETTEMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <QColor>

class PaletteModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PaletteModel(QObject* parent);
    ~PaletteModel();

public:
    virtual int             rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant        data(const QModelIndex &index, int role) const;
    virtual bool            setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags   flags(const QModelIndex &index) const;

    QColor                  getColor(const QModelIndex &index)const;
    void                    setColor(const QModelIndex& index, QColor color);
    void                    saveToFile(QString const& path)const;
    void                    loadFromFile(const QString &path);
public slots:
    QModelIndex             addColor(QColor color = QColor());
    void                    removeColor(QModelIndex index);
    void                    removeAll();
private:
    QList<QColor>   m_colors;
};

#endif // PALETTEMODEL_HPP
