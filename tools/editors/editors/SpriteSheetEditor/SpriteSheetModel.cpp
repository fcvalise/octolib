#include "SpriteSheetModel.hpp"

#include <ByteArray.hpp>
#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>

#include <fstream>

namespace
{
    struct SortByXY
    {
        bool    operator()(QPoint const& left, QPoint const& right)const
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

SpriteSheetModel::SpriteSheetModel(QObject *parent) :
    QAbstractListModel(parent),
    m_tileSize(0, 0)
{
}

SpriteSheetModel::~SpriteSheetModel()
{
}

int SpriteSheetModel::rowCount(const QModelIndex &) const
{
    return (m_tilePositions.size());
}

QVariant SpriteSheetModel::data(const QModelIndex &index, int role) const
{
    QVariant    result;

    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        result = qVariantFromValue(QRect(m_tilePositions.at(index.row()), m_tileSize));
    }
    return (result);
}

Qt::ItemFlags SpriteSheetModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags   result;

    if (index.isValid())
        result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
        result = Qt::NoItemFlags;
    return (result);
}

void SpriteSheetModel::reset()
{
    beginResetModel();
    m_tilePositions.clear();
    m_tileSize = QSize();
    m_texture = QPixmap();
    endResetModel();
    emit modified();
    emit textureChanged(m_texture);
    emit tileSizeChanged(m_tileSize);
}

void SpriteSheetModel::reset(const QString &textureFileName, const QList<QPoint> &positions, const QSize &tileSize)
{
    octo::ByteArray         textureBytes;
    std::fstream            file;

    file.open(textureFileName.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open())
        textureBytes.read(file);
    reset(textureBytes, positions, tileSize);
}

void SpriteSheetModel::reset(octo::ByteArray const& textureBytes, const QList<QPoint> &positions, const QSize &tileSize)
{
    beginResetModel();
    m_tilePositions = positions;
    if (m_texture.loadFromData(reinterpret_cast<uchar const*>(textureBytes.bytes()), textureBytes.size()) == false)
        qDebug("merde");
    m_textureBytes.assign(textureBytes);
    if (tileSize.isEmpty())
        m_tileSize = m_texture.size();
    else
        m_tileSize = tileSize;
    endResetModel();
    emit modified();
    emit textureChanged(m_texture);
    emit tileSizeChanged(m_tileSize);
}

void SpriteSheetModel::resetPositions(const QList<QPoint> &positions)
{
    beginResetModel();
    m_tilePositions = positions;
    endResetModel();
    emit modified();
}

void SpriteSheetModel::subDivideTexture(int widthSubDiv, int heightSubDiv)
{
    QRect           textureRect(QPoint(0, 0), m_texture.size());
    int             width = textureRect.width() / widthSubDiv;
    int             height = textureRect.height() / heightSubDiv;
    int             posX = 0;
    int             posY = 0;
    QList<QPoint>   positions;

    for (int y = 0; y < heightSubDiv; ++y)
    {
        posX = 0;
        for (int x = 0; x < widthSubDiv; ++x)
        {
            positions.append(QPoint(posX, posY));
            posX += width;
        }
        posY += height;
    }
    beginResetModel();
    m_tilePositions = positions;
    m_tileSize = QSize(width, height);
    endResetModel();
    emit modified();
    emit tileSizeChanged(m_tileSize);
}

bool SpriteSheetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool    result = false;
    QRect  rect;
    QPoint pos;

    if (value.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        pos = value.value<QPoint>();
        m_tilePositions[index.row()] = pos;
        result = true;
        emit dataChanged(index, index);
        emit tileChanged(index, QRect(pos, m_tileSize));
        emit modified();
    }
    return (result);
}

QModelIndex SpriteSheetModel::addTile(const QPoint &position)
{
    QModelIndex result;
    int         indexOf = m_tilePositions.size();

    beginInsertRows(QModelIndex(), m_tilePositions.size(), m_tilePositions.size());
    m_tilePositions.append(position);
    endInsertRows();
    result = index(indexOf);
    emit modified();
    return (result);
}

QPair<QModelIndex, QModelIndex> SpriteSheetModel::addTiles(const QList<QPoint> &positions)
{
    QPair<QModelIndex, QModelIndex> result;
    int                             firstIndex = m_tilePositions.size();
    int                             lastIndex = firstIndex + positions.size() - 1;

    if (positions.empty() == false)
    {
        beginInsertRows(QModelIndex(), firstIndex, firstIndex + positions.size() - 1);
        m_tilePositions.append(positions);
        endInsertRows();
        emit modified();
        result.first = index(firstIndex);
        result.second = index(lastIndex);
    }
    return (result);
}

void SpriteSheetModel::removeTile(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_tilePositions.removeAt(index.row());
    endRemoveRows();
    emit modified();
}

void SpriteSheetModel::removeTiles(const QList<QModelIndex> &indexes)
{
    QList<QPersistentModelIndex>    persistentIndexes;

    for (QModelIndex const& index : indexes)
    {
        persistentIndexes.append(QPersistentModelIndex(index));
    }
    for (QPersistentModelIndex const& index : persistentIndexes)
    {
        removeTile(index);
    }
}

void SpriteSheetModel::removeAllTiles()
{
    beginResetModel();
    m_tilePositions.clear();
    endResetModel();
    emit modified();
}

void SpriteSheetModel::moveTile(const QModelIndex &index, QPoint offset)
{
    QPoint  currentRectPos;

    if (index.isValid() == false || offset.manhattanLength() < std::numeric_limits<qreal>::epsilon())
        return;
    currentRectPos = tile(index).topLeft();
    if (currentRectPos.x() + offset.x() < 0)
        offset.setX(-currentRectPos.x());
    else if (currentRectPos.x() + m_tileSize.width() + offset.x() > m_texture.width())
        offset.setX(m_texture.width() - m_tileSize.width() - currentRectPos.x());
    if (currentRectPos.y() + offset.y() < 0)
        offset.setY(-currentRectPos.y());
    else if (currentRectPos.y() + m_tileSize.height() + offset.y() > m_texture.height())
        offset.setY(m_texture.height() - m_tileSize.height() - currentRectPos.y());
    m_tilePositions[index.row()] += offset;
    emit dataChanged(index, index);
    emit modified();
}

void SpriteSheetModel::moveTiles(const QList<QModelIndex> &indexes, QPoint offset)
{
    QPoint  currentRectPos;

    for (QModelIndex const& index : indexes)
    {
        if (index.isValid() == false || offset.manhattanLength() < std::numeric_limits<qreal>::epsilon())
            return;
        currentRectPos = tile(index).topLeft();
        if (currentRectPos.x() + offset.x() < 0)
            offset.setX(-currentRectPos.x());
        else if (currentRectPos.x() + m_tileSize.width() + offset.x() > m_texture.width())
            offset.setX(m_texture.width() - m_tileSize.width() - currentRectPos.x());
        if (currentRectPos.y() + offset.y() < 0)
            offset.setY(-currentRectPos.y());
        else if (currentRectPos.y() + m_tileSize.height() + offset.y() > m_texture.height())
            offset.setY(m_texture.height() - m_tileSize.height() - currentRectPos.y());
        m_tilePositions[index.row()] += offset;
    }
}

void SpriteSheetModel::setTilePosition(const QModelIndex &index, const QPoint &position)
{
    if (index.isValid() == false)
        return;
    m_tilePositions[index.row()] = position;
    emit dataChanged(index, index);
    emit tileChanged(index, tile(index));
    emit modified();
}

void SpriteSheetModel::setTileSize(const QSize &size)
{
    m_tileSize = size;
    if (m_tilePositions.empty() == false)
    {
        emit dataChanged(index(0), index(m_tilePositions.size() - 1));
    }
    emit tileSizeChanged(m_tileSize);
    emit modified();
}

bool SpriteSheetModel::isEmpty() const
{
    return (m_tilePositions.isEmpty());
}

QPoint SpriteSheetModel::tilePosition(int row) const
{
    return (m_tilePositions.at(row));
}

QPoint SpriteSheetModel::tilePosition(const QModelIndex &index) const
{
    QPoint  result;

    if (index.isValid())
        result = tilePosition(index.row());
    return (result);
}

void SpriteSheetModel::sortTiles()
{
    beginResetModel();
    std::sort(m_tilePositions.begin(), m_tilePositions.end(), SortByXY());
    endResetModel();
    emit modified();
}

QRect SpriteSheetModel::tile(int row) const
{
    return (QRect(m_tilePositions.at(row), m_tileSize));
}

QList<QPoint> SpriteSheetModel::tilePositions() const
{
    return (m_tilePositions);
}

QRect SpriteSheetModel::tile(const QModelIndex &index) const
{
    QRect  result;

    if (index.isValid())
        result = tile(index.row());
    return (result);
}

QSize SpriteSheetModel::tileSize() const
{
    return (m_tileSize);
}

const QList<QPoint> &SpriteSheetModel::positions() const
{
    return (m_tilePositions);
}

const QPixmap &SpriteSheetModel::texture() const
{
    return (m_texture);
}

QRect SpriteSheetModel::textureRect() const
{
    return (QRect(0, 0, m_texture.width(), m_texture.height()));
}

const octo::ByteArray &SpriteSheetModel::textureBytes() const
{
    return (m_textureBytes);
}

namespace
{
    class FindTile
    {
    public:
        FindTile(QPoint const& pos, QSize const& size) :
            m_position(pos),
            m_size(size)
        {
        }

        bool    operator()(QPoint const& pos)const
        {
            return (m_position.x() >= pos.x() &&
                    m_position.x() < (pos.x() + m_size.width()) &&
                    m_position.y() >= pos.y() &&
                    m_position.y() < (pos.y() + m_size.height()));
        }
    private:
        QPoint  m_position;
        QSize   m_size;
    };
}

QModelIndex SpriteSheetModel::tileAt(const QPoint &pos) const
{
    QModelIndex result;
    auto        it = std::find_if(m_tilePositions.begin(), m_tilePositions.end(), FindTile(pos, m_tileSize));

    if (it != m_tilePositions.end())
    {
        result = index(std::distance(m_tilePositions.begin(), it));
    }
    return (result);
}

QList<QModelIndex> SpriteSheetModel::indexes() const
{
    QList<QModelIndex>  results;

    for (int i = 0; i < m_tilePositions.size(); ++i)
    {
        results.append(index(i));
    }
    return (results);
}

bool SpriteSheetModel::loadFromFile(const QString &fileName)
{
    octo::ByteArray         buffer;
    octo::BinaryInputStream is(buffer);
    std::fstream            file;

    file.open(fileName.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open() == false)
        return (false);
    if (buffer.read(file) == false)
        return (false);
    return (loadFromMemory(is));
}

bool SpriteSheetModel::saveToFile(const QString &fileName) const
{
    octo::ByteArray             buffer;
    octo::BinaryOutputStream    os(buffer);
    std::fstream                file;

    if (writeToMemory(os) == false)
        return (false);
    file.open(fileName.toStdString(), std::ios_base::out | std::ios_base::binary);
    if (file.is_open() == false)
        return (false);
    buffer.write(file);
    file.close();
    return (true);
}

bool SpriteSheetModel::writeToMemory(octo::BinaryOutputStream &os) const
{
    os.write<quint32>(m_textureBytes.size());
    os.writeBytes(m_textureBytes.bytes(), m_textureBytes.size());
    os.write<quint32>(m_tileSize.width());
    os.write<quint32>(m_tileSize.height());
    os.write<quint32>(m_tilePositions.size());
    for (int i = 0; i < m_tilePositions.size(); ++i)
    {
        os.write<quint32>(m_tilePositions.at(i).x());
        os.write<quint32>(m_tilePositions.at(i).y());
    }
    return (true);
}

bool SpriteSheetModel::loadFromMemory(octo::BinaryInputStream &is)
{
    QList<QPoint>   tilePositions;
    octo::ByteArray textureBytes;
    quint32         tileWidth = 0u;
    quint32         tileHeight = 0u;
    quint32         tileCount = 0u;
    quint32         x = 0u;
    quint32         y = 0u;
    quint32         textureByteCount = 0u;

    is.read(textureByteCount);
    is.readBytes(textureBytes, textureByteCount);
    is.read(tileWidth, tileHeight, tileCount);
    for (quint32 i = 0u; i < tileCount; ++i)
    {
        is.read(x, y);
        tilePositions.append(QPoint(x, y));
    }
    reset(textureBytes, tilePositions, QSize(tileWidth, tileHeight));
    return (true);
}
