#ifndef SPRITESHEETEDITOR_HPP
#define SPRITESHEETEDITOR_HPP

#include <QWidget>
#include <ByteArray.hpp>

class SpriteSheetView;
class SpriteSheetModel;
class RectangleListView;
class TileControlWidget;
class TilePreview;

class QItemSelectionModel;

class QPixmap;
class QTableView;
class QModelIndex;

class SpriteSheetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteSheetEditor(QWidget *parent = 0);
    ~SpriteSheetEditor();

    void            newSpriteSheet(QString const& textureFilePath);
    bool            openSpriteSheet(QString const& filePath);
    bool            saveSpriteSheet(QString const& filePath);
    void            createTileByDivision();
    void            resetTexture(const QString &textureFilePath);

    void            zoomIn();
    void            zoomOut();
    void            zoomZero();
    void            zoomToFit();

    bool            hasSelection()const;
    QList<QAction*> commandActions()const;
public slots:
    void            selectAllTiles();
    void            copySelectedTiles();
    void            cutSelectedTiles();
    void            pasteTiles();
    void            deleteSelectedTiles();
    void            sortTiles();
signals:
    void            selectionChanged();
    void            modified();
private:
    void            setup();
    void            setupCommands();
private:
    SpriteSheetModel*       m_spriteSheetModel;
    QItemSelectionModel*    m_selectionModel;
    SpriteSheetView*        m_spriteSheetView;
    QTableView*             m_tileView;
    TileControlWidget*      m_tileControl;
    TilePreview*            m_tilePreview;
    QList<QPoint>           m_tileBuffer;
};

#endif // SPRITESHEETEDITOR_HPP
