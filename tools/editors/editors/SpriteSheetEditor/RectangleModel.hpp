#ifndef RECTANGLEMODEL_HPP
#define RECTANGLEMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <QRectF>

#include <BinaryOutputStream.hpp>
#include <BinaryInputStream.hpp>

class RectangleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    RectangleModel(QObject* parent = nullptr);
    ~RectangleModel();

    virtual int             rowCount(const QModelIndex &parent) const;
    virtual QVariant        data(const QModelIndex &index, int role) const;
    virtual bool            setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags   flags(const QModelIndex &index) const;
    void                    reset(QList<QPointF> const& positions, QSizeF const& size);
    void                    addRectangle(QPointF const& position);
    void                    removeRectangle(QModelIndex const& index);
    void                    removeAll();
    void                    moveRectangle(QModelIndex const& index, QPointF const& offset);
    void                    setRectanglePosition(QModelIndex const& index, QPointF const& position);
    void                    setSize(const QSizeF &size);
    QSizeF const&           size()const;
    bool                    isEmpty()const;
    void                    sortRectanglesByXY();

    QRectF                  rectangle(int row)const;
    QRectF                  rectangle(QModelIndex const& index)const;
    QList<QPointF> const&   positions()const;
    bool                    writeDatas(octo::BinaryOutputStream& os)const;
    bool                    loadDatas(octo::BinaryInputStream& is);
signals:
    void                    rectangleChanged(QModelIndex const& index, QRectF const& rect);
private:
    QList<QPointF>      m_values;
    QSizeF              m_size;
};

#endif // RECTANGLEMODEL_HPP
