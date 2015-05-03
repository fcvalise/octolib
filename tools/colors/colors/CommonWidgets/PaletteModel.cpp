#include "PaletteModel.hpp"
#include <QVariant>
#include <QFile>
#include <fstream>

#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>

namespace
{
    template <class T>
    void    write(std::ostream& stream, T const& value)
    {
        stream.write(reinterpret_cast<char const*>(&value), sizeof(T));
    }

    template <class T>
    void    read(std::istream& stream, T& value)
    {
        stream.read(reinterpret_cast<char *>(&value), sizeof(T));
    }
}

PaletteModel::PaletteModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

PaletteModel::~PaletteModel()
{
}

int PaletteModel::rowCount(const QModelIndex &) const
{
    return (m_colors.size());
}

QVariant PaletteModel::data(const QModelIndex &index, int role) const
{
    QVariant    result;

    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        result = QVariant(m_colors[index.row()]);
    }
    return (result);
}

bool PaletteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() == false || role != Qt::EditRole || value.canConvert<QColor>() == false)
        return (false);
    if (role != Qt::EditRole)
        return (false);
    m_colors[index.row()] = value.value<QColor>();
    emit dataChanged(index, index);
    return (true);
}

Qt::ItemFlags PaletteModel::flags(const QModelIndex &index) const
{
    return ((index.isValid()) ? Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable : Qt::NoItemFlags);
}

QColor PaletteModel::getColor(const QModelIndex &index) const
{
    QColor  color;

    if (index.isValid())
        color = m_colors.at(index.row());
    return (color);
}

void PaletteModel::setColor(const QModelIndex &index, QColor color)
{
    if (index.isValid())
    {
        m_colors[index.row()] = color;
        emit dataChanged(index, index);
    }
}

void PaletteModel::saveToFile(const QString &path) const
{
    std::fstream    file;
    quint64         count = m_colors.size();

    file.open(path.toStdString(), std::ios_base::out | std::ios_base::binary);
    if (file.is_open())
    {
        octo::ByteArray             buffer;
        octo::BinaryOutputStream    out(buffer);

        out.write(count);
        for (int i = 0; i < m_colors.size(); ++i)
        {
            out.write(static_cast<quint8>(m_colors[i].red()));
            out.write(static_cast<quint8>(m_colors[i].green()));
            out.write(static_cast<quint8>(m_colors[i].blue()));
            out.write(static_cast<quint8>(m_colors[i].alpha()));
        }
        buffer.write(file);
    }
}

void PaletteModel::loadFromFile(const QString &path)
{
    std::ifstream   file;
    quint64         count = 0u;
    QList<QColor>   colors;
    quint8          r = 0;
    quint8          g = 0;
    quint8          b = 0;
    quint8          a = 0;

    file.open(path.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open())
    {
        octo::ByteArray         buffer;
        octo::BinaryInputStream in(buffer);

        buffer.read(file);
        in.read(count);
        for (quint64 i = 0; i < count; ++i)
        {
            in.read(r, g, b, a);
            colors.append(QColor(r, g, b, a));
        }
        beginResetModel();
        m_colors = colors;
        endResetModel();
    }
}

void PaletteModel::removeAll()
{
    beginResetModel();
    m_colors.clear();
    endResetModel();
}

QModelIndex PaletteModel::addColor(QColor color)
{
    int row = m_colors.size();

    beginInsertRows(QModelIndex(), m_colors.size(), m_colors.size());
    m_colors.append(color);
    endInsertRows();
    return (index(row));
}

void PaletteModel::removeColor(QModelIndex index)
{
    if (index.isValid() == false)
        return;
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_colors.removeAt(index.row());
    endRemoveRows();
}
