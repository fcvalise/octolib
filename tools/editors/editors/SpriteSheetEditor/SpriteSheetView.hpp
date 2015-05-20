#ifndef SPRITESHEETVIEW_HPP
#define SPRITESHEETVIEW_HPP
#include <QGraphicsView>

class SpriteSheetScene;
class RectangleModel;

class QModelIndex;
class QItemSelectionModel;

class SpriteSheetView : public QGraphicsView
{
    Q_OBJECT
public:
    SpriteSheetView(QWidget* parent = nullptr);
    ~SpriteSheetView();

    void                    enableBackground(bool enable);
    void                    setTexturePixmap(QPixmap const& pixmap);
    void                    clearTexturePixmap();

    void                    resetTiles(QList<QPointF> const& tilePosition, QSizeF const& tileSize);
    QSizeF                  generateRectangles(int widthSubDiv, int heightSubDiv);
    void                    setTileSize(QSizeF const& size);
    void                    removeRectangle(QModelIndex const& index);
    void                    removeAllRectangles();
    void                    sortRectangles();

    void                    zoomIn();
    void                    zoomOut();
    void                    zoomZero();
    void                    zoomToFit();
    void                    setZoom(qreal factor);

    RectangleModel*         rectangleModel()const;
    QItemSelectionModel*    selectionRectangleModel() const;
    QList<QAction*>         commandActions()const;
    QSizeF                  tileSize()const;
    QList<QPointF>          tilePositions()const;
    QRectF                  textureRectangle()const;
    QPixmap                 texturePixmap()const;
private:
    void                    setupBackgroundBrush();
    void                    centerOnCurrent();
signals:
    void                    modified();
private:
    SpriteSheetScene*       m_scene;
    QBrush                  m_backgroundBrush;
    qreal                   m_zoomFactor;
};

#endif // SPRITESHEETVIEW_HPP
