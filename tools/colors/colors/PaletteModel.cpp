#include "PaletteModel.hpp"
#include <QVariant>
#include <QFile>
#include <QDataStream>

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
    QFile           file(path);
    QDataStream     stream(&file);
    std::uint64_t   count = m_colors.size();

    if (file.open(QFile::WriteOnly))
    {
        stream << count;
        for (int i = 0; i < m_colors.size(); ++i)
        {
            stream << static_cast<quint8>(m_colors[i].red());
            stream << static_cast<quint8>(m_colors[i].green());
            stream << static_cast<quint8>(m_colors[i].blue());
            stream << static_cast<quint8>(m_colors[i].alpha());
        }
    }
}

void PaletteModel::loadFromFile(const QString &path)
{
    QFile           file(path);
    QDataStream     stream(&file);
    quint64         count = 0u;
    QList<QColor>   colors;
    quint8          r = 0;
    quint8          g = 0;
    quint8          b = 0;
    quint8          a = 0;

    if (file.open(QFile::ReadOnly))
    {
        stream >> count;
        for (quint64 i = 0; i < count; ++i)
        {
            stream >> r >> g >> b >> a;
            colors.append(QColor(r, g, b, a));
        }
        beginResetModel();
        m_colors = colors;
        endResetModel();
    }
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
