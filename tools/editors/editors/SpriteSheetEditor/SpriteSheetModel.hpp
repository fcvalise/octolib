#ifndef SPRITESHEETMODEL_HPP
#define SPRITESHEETMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <QRect>
#include <QPixmap>

#include <BinaryOutputStream.hpp>
#include <BinaryInputStream.hpp>
#include <ByteArray.hpp>

class SpriteSheetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SpriteSheetModel(QObject* parent = nullptr);
    ~SpriteSheetModel();

    virtual int                     rowCount(const QModelIndex &parent) const;
    virtual QVariant                data(const QModelIndex &index, int role) const;
    virtual bool                    setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags           flags(const QModelIndex &index) const;

    bool                            isEmpty()const;
    QPoint                          tilePosition(int row)const;
    QPoint                          tilePosition(QModelIndex const& index)const;
    QRect                           tile(int row)const;
    QList<QPoint>                   tilePositions()const;
    QRect                           tile(QModelIndex const& index)const;
    QSize                           tileSize()const;
    QList<QPoint> const&            positions()const;
    QPixmap const&                  texture()const;
    QRect                           textureRect()const;
    octo::ByteArray const&          textureBytes()const;
    QModelIndex                     tileAt(QPoint const& pos)const;
    QList<QModelIndex>              indexes()const;

    bool                            loadFromFile(QString const& fileName);
    bool                            saveToFile(QString const& fileName)const;
    bool                            writeToMemory(octo::BinaryOutputStream& os)const;
    bool                            loadFromMemory(octo::BinaryInputStream& is);
public slots:
    void                            reset();
    void                            reset(QString const& textureFileName,
                                          QList<QPoint> const& positions = {},
                                          QSize const& tileSize = {0, 0});
    void                            reset(const octo::ByteArray &textureBytes,
                                          QList<QPoint> const& positions = {},
                                          QSize const& tileSize = {0, 0});
    void                            resetPositions(QList<QPoint> const& positions);
    void                            setTileSize(const QSize &size);
    QModelIndex                     addTile(QPoint const& position);
    QPair<QModelIndex, QModelIndex> addTiles(QList<QPoint> const& positions);
    void                            subDivideTexture(int widthSubDiv, int heightSubDiv);
    void                            removeTile(QModelIndex const& index);
    void                            removeTiles(QList<QModelIndex> const& indexes);
    void                            removeAllTiles();
    void                            moveTile(QModelIndex const& index, QPoint offset);
    void                            moveTiles(QList<QModelIndex> const& indexes, QPoint offset);
    void                            setTilePosition(QModelIndex const& index, QPoint const& position);
    void                            sortTiles();
signals:
    void                            tileChanged(QModelIndex const& index, QRect const& rect);
    void                            tileSizeChanged(QSize const& size);
    void                            textureChanged(QPixmap const& texture);
    void                            modified();
private:
    QList<QPoint>       m_tilePositions;
    QSize               m_tileSize;
    QPixmap             m_texture;
    octo::ByteArray     m_textureBytes;
};

#endif // SPRITESHEETMODEL_HPP
