#ifndef SPRITESHEETVIEW_HPP
#define SPRITESHEETVIEW_HPP
#include <QGraphicsView>
#include <QPointer>
#include <QObject>

class SpriteSheetModel;
class InteractiveGraphicsScene;
class AbstractSpriteSheetCommand;
class GraphicsTileItem;

class QGraphicsScene;
class QModelIndex;
class QItemSelectionModel;
class QItemSelection;

class SpriteSheetView : public QGraphicsView
{
    Q_OBJECT

    static QPen const       RectanglePen;
    static QBrush const     SelectedRectangleBrush;
    static QBrush const     HoveredRectangleBrush;
    static QPen const       BorderRectanglePen;
    class GraphicsTileItem;
public:
    SpriteSheetView(QWidget* parent = nullptr);
    ~SpriteSheetView();

    void                    setModel(SpriteSheetModel* model);
    void                    setSelectionModel(QItemSelectionModel* model);
    void                    enableBackground(bool enable);

    void                    zoomIn();
    void                    zoomOut();
    void                    zoomZero();
    void                    zoomToFit();
    void                    setZoom(qreal factor);

    void                    enableCommands(bool enable);
    void                    addCommand(AbstractSpriteSheetCommand *command, bool enable = false);
    void                    restartCurrentCommand();
    QList<QAction*>         commandActions()const;
private:
    void                    setupBackgroundBrush();
    void                    centerOnCurrent();
    void                    commitChange(int row);
    GraphicsTileItem*       createTile();
    void                    setTileSelected(const QModelIndex &index, bool selected);
private slots:
    void                    onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void                    onRowsInserted(const QModelIndex &, int start, int end);
    void                    onRowsAboutToBeRemoved(const QModelIndex &, int start, int end);
    void                    onModelReset();
    void                    onCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
    void                    onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
signals:
    void                    modified();
private: 
    QPointer<SpriteSheetModel>      m_model;
    QPointer<QItemSelectionModel>   m_selectionModel;
    InteractiveGraphicsScene*       m_scene;
    QBrush                          m_backgroundBrush;
    qreal                           m_zoomFactor;
    QGraphicsPixmapItem*            m_texture;
    QGraphicsRectItem*              m_textureBorder;
    QVector<GraphicsTileItem*>      m_tiles;
};

#endif // SPRITESHEETVIEW_HPP
