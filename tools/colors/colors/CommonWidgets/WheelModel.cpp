#include "WheelModel.hpp"

#include <QVariant>
#include <QColor>

#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>
#include <ByteArray.hpp>

#include <fstream>

WheelModel::WheelModel(QObject* parent) :
    QAbstractTableModel(parent),
    m_hue(0)
{
}

WheelModel::~WheelModel()
{
}

int WheelModel::rowCount(const QModelIndex &) const
{
    return (m_offsets.size());
}

int WheelModel::columnCount(const QModelIndex &) const
{
    return (ColumnCount);
}

QVariant WheelModel::data(const QModelIndex &index, int role) const
{
    QVariant    result;

    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        HueOffset const&    value = m_offsets.at(index.row());

        result = value.computeColor(m_hue);
    }
    return (result);
}

Qt::ItemFlags WheelModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
    else
    {
        return (Qt::NoItemFlags);
    }
}


void WheelModel::setHue(quint16 hue)
{
    m_hue = hue;
    emit dataChanged(index(0, ComputedColor), index(m_offsets.size() - 1, ComputedColor));
}

quint16 WheelModel::getHue() const
{
    return (m_hue);
}

HueOffset WheelModel::getOffset(int row) const
{
    return (m_offsets.at(row));
}

HueOffset WheelModel::getOffset(const QModelIndex &index) const
{
    HueOffset   result;

    if (index.isValid())
    {
        result = m_offsets.at(index.row());
    }
    return (result);
}

void WheelModel::setOffset(const QModelIndex &index, HueOffset const &offset)
{
    if (index.isValid() == false)
        return;
    m_offsets[index.row()] = offset;
    emit dataChanged(index, index);
}

void WheelModel::saveToFile(const QString &path) const
{
    std::fstream    file;
    quint64         count = m_offsets.size();

    file.open(path.toStdString(), std::ios_base::out | std::ios_base::binary);
    if (file.is_open())
    {
        octo::ByteArray             buffer;
        octo::BinaryOutputStream    out(buffer);

        out.write(m_hue);
        out.write(count);
        for (int i = 0; i < m_offsets.size(); ++i)
        {
            HueOffset const&    offset = m_offsets.at(i);

            out.write(static_cast<qint16>(offset.getOffset()));
            out.write(static_cast<quint8>(offset.getSaturation()));
            out.write(static_cast<quint8>(offset.getValue()));
            out.write(static_cast<quint8>(offset.getAlpha()));
        }
        buffer.write(file);
    }
}

void WheelModel::loadFromFile(const QString &path)
{
    std::ifstream       file;
    quint64             count = 0u;
    QList<HueOffset>    offsets;
    qint16              offset = 0;
    quint8              saturation = 0;
    quint8              value = 0;
    quint8              alpha = 0;
    quint16             hue = 0;

    file.open(path.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open())
    {
        octo::ByteArray         buffer;
        octo::BinaryInputStream in(buffer);

        buffer.read(file);
        in.read(hue);
        in.read(count);
        for (quint64 i = 0; i < count; ++i)
        {
            in.read(offset, saturation, value, alpha);
            offsets.append(HueOffset(offset, saturation, value, alpha));
        }
        beginResetModel();
        m_offsets = offsets;
        m_hue = hue;
        endResetModel();
    }
}

QModelIndex WheelModel::addOffset(qint16 offset, quint8 saturation, quint8 value, quint8 alpha)
{
    return (addOffset(HueOffset(offset, saturation, value, alpha)));
}

QModelIndex WheelModel::addOffset(const HueOffset &offset)
{
    int row = m_offsets.size();

    beginInsertRows(QModelIndex(), row, row);
    m_offsets.append(offset);
    endInsertRows();
    return (index(row, 0));
}

void WheelModel::removeOffset(QModelIndex index)
{
    if (index.isValid() == false)
        return;
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_offsets.removeAt(index.row());
    endRemoveRows();
}

void WheelModel::removeAll()
{
    beginResetModel();
    m_offsets.clear();
    endResetModel();
}
