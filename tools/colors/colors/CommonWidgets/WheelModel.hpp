#ifndef WHEELMODEL_HPP
#define WHEELMODEL_HPP

#include <QAbstractListModel>

#include <HueOffset.hpp>

class WheelModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns
    {
        ComputedColor,
        ColumnCount
    };

    explicit WheelModel(QObject* parent = nullptr);
    ~WheelModel();

    virtual int         rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int         columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant    data(const QModelIndex &index, int role) const;
    Qt::ItemFlags       flags(const QModelIndex &index) const;

    quint16             getHue()const;
    HueOffset           getOffset(int row)const;
    HueOffset           getOffset(const QModelIndex &index)const;
    void                setOffset(const QModelIndex& index, HueOffset const& offset);
    void                saveToFile(QString const& path)const;
    void                loadFromFile(const QString &path);
public slots:
    void                setHue(quint16 hue);
    QModelIndex         addOffset(qint16 offset, quint8 saturation = 255, quint8 value = 255, quint8 alpha = 255);
    QModelIndex         addOffset(HueOffset const& offset);
    void                removeOffset(QModelIndex index);
    void                removeAll();
private:
    QList<HueOffset>    m_offsets;
    quint16             m_hue;
};

#endif // WHEELMODEL_HPP
