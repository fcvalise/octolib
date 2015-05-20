#include "RectangleModel.hpp"

namespace
{
    struct SortByXY
    {
        bool    operator()(QPointF const& left, QPointF const& right)const
        {
            if (left.y() < right.y())
            {
                return (true);
            }
            else if (left.y() > right.y())
            {
                return (false);
            }
            else
            {
                return (left.x() < right.x());
            }
        }
    };
}

RectangleModel::RectangleModel(QObject *parent) :
    QAbstractListModel(parent),
    m_size(0, 0)
{
}

RectangleModel::~RectangleModel()
{
}

int RectangleModel::rowCount(const QModelIndex &) const
{
    return (m_values.size());
}

QVariant RectangleModel::data(const QModelIndex &index, int role) const
{
    QVariant    result;

    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        result = qVariantFromValue(QRectF(m_values.at(index.row()), m_size));
    }
    return (result);
}

Qt::ItemFlags RectangleModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags   result;

    if (index.isValid())
        result = Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    else
        result = Qt::NoItemFlags;
    return (result);
}

void RectangleModel::reset(const QList<QPointF> &positions, const QSizeF &size)
{
    beginResetModel();
    m_values = positions;
    m_size = size;
    endResetModel();
}

bool RectangleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool    result = false;
    QRectF  rect;
    QPointF pos;

    if (value.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        pos = value.value<QPointF>();
        m_values[index.row()] = pos;
        result = true;
        emit dataChanged(index, index);
        emit rectangleChanged(index, QRectF(pos, m_size));
    }
    return (result);
}

void RectangleModel::addRectangle(const QPointF &position)
{
    beginInsertRows(QModelIndex(), m_values.size(), m_values.size());
    m_values.append(position);
    endInsertRows();
}

void RectangleModel::removeRectangle(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_values.removeAt(index.row());
    endRemoveRows();
}

void RectangleModel::removeAll()
{
    beginResetModel();
    m_values.clear();
    endResetModel();
}

void RectangleModel::moveRectangle(const QModelIndex &index, const QPointF &offset)
{
    if (index.isValid() == false || offset.manhattanLength() < std::numeric_limits<qreal>::epsilon())
        return;
    m_values[index.row()] += offset;
    emit dataChanged(index, index);
}

void RectangleModel::setRectanglePosition(const QModelIndex &index, const QPointF &position)
{
    if (index.isValid() == false)
        return;
    m_values[index.row()] = position;
    emit dataChanged(index, index);
}

void RectangleModel::setSize(QSizeF const& size)
{
    m_size = size;
    if (m_values.empty() == false)
    {
        emit dataChanged(index(0), index(m_values.size() - 1));
    }
}

const QSizeF &RectangleModel::size() const
{
    return (m_size);
}

bool RectangleModel::isEmpty() const
{
    return (m_values.isEmpty());
}

void RectangleModel::sortRectanglesByXY()
{
    beginResetModel();
    std::sort(m_values.begin(), m_values.end(), SortByXY());
    endResetModel();
}

QRectF RectangleModel::rectangle(int row) const
{
    return (QRectF(m_values.at(row), m_size));
}

QRectF RectangleModel::rectangle(const QModelIndex &index) const
{
    QRectF  result;

    if (index.isValid())
        result = rectangle(index.row());
    return (result);
}

const QList<QPointF> &RectangleModel::positions() const
{
    return (m_values);
}

bool RectangleModel::writeDatas(octo::BinaryOutputStream &os) const
{
    os.write<quint32>(m_size.width());
    os.write<quint32>(m_size.height());
    os.write<quint32>(m_values.size());
    for (int i = 0; i < m_values.size(); ++i)
    {
        os.write<quint32>(m_values.at(i).x());
        os.write<quint32>(m_values.at(i).y());
    }
    return (true);
}

bool RectangleModel::loadDatas(octo::BinaryInputStream &is)
{
    quint32 width = 0u;
    quint32 height = 0u;
    quint32 count = 0u;
    quint32 x = 0u;
    quint32 y = 0u;
    QList<QPointF>  values;

    is.read(width, height, count);
    for (quint32 i = 0u; i < count; ++i)
    {
        is.read(x, y);
        values.append(QPointF(x, y));
    }
    beginResetModel();
    m_size = QSizeF(width, height);
    std::swap(m_values, values);
    endResetModel();
    return (true);
}
