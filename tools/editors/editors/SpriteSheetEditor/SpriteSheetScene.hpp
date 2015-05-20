#ifndef SPRITESHEETSCENE_HPP
#define SPRITESHEETSCENE_HPP
#include "CommandManager.hpp"

#include <QGraphicsScene>
#include <QVector>

class SpriteSheetScene;
class RectangleModel;

class QModelIndex;
class QItemSelectionModel;
class QGraphicsRectItem;
class QGraphicsPixmapItem;

class SpriteSheetScene : public QGraphicsScene
{
    Q_OBJECT

    static QPen const       RectanglePen;
    static QBrush const     SelectedRectangleBrush;
    static QPen const       GhostRectanglePen;
    static QBrush const     GhostRectangleBrush;
public:
    SpriteSheetScene(QObject* parent = nullptr);
    ~SpriteSheetScene();

    void                    setTexturePixmap(QPixmap const& pixmap);

    RectangleModel*         rectangleModel()const;
    QItemSelectionModel*    selectionRectangleModel() const;
    QList<QAction*>         commandActions()const;

    void                    resetRectangles(QList<QPointF> const& positions, QSizeF const& size);
    void                    setRectangleSize(QSizeF const& size);
    void                    setRectanglePosition(const QModelIndex &index, const QPointF &position);
    void                    moveRectangle(QModelIndex const& index, QPointF const& offset);
    void                    removeRectangle(QModelIndex const& index);
    void                    removeAllRectangles();
    void                    sortRectangles();

    void                    makeRectangleFromGhost();
    void                    setGhostRectangleEnabled(bool enable);
    void                    setGhostRectangleSize(QSizeF const& size);
    void                    setGhostRectanglePosition(QPointF const& position);

    void                    setCurrentRectangle(QModelIndex const& index);
    QModelIndex             rectangleUnder(QPointF const& pos)const;
    QModelIndex             currentRectangle()const;
    bool                    isIntoTexture(QPointF const& pos)const;
    QSizeF                  rectangleSize()const;
    QRectF                  rectangle(QModelIndex const& index)const;
    qreal                   textureWidth()const;
    qreal                   textureHeight()const;
    QPixmap                 texturePixmap()const;
protected slots:
    void                    dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void                    rowsInserted(const QModelIndex &, int start, int end);
    void                    rowsAboutToBeRemoved(const QModelIndex &, int start, int end);
    void                    modelReset();
    void                    onCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
private:
    void                    setupCommands();
    void                    commitChange(int row);
    QGraphicsRectItem*      createRectangle();
    void                    clearSelection();
    void                    setSelected(QModelIndex const& index, bool selected);
signals:
    void                    modified();
protected:
    virtual void            mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void            mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void            mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void            keyPressEvent(QKeyEvent *event);
    virtual void            keyReleaseEvent(QKeyEvent *event);
private:
    CommandManager              m_commandManager;
    RectangleModel*             m_rectangleModel;
    QItemSelectionModel*        m_selectionRectangleModel;
    QGraphicsPixmapItem*        m_texture;
    QVector<QGraphicsRectItem*> m_rectangles;
    QGraphicsRectItem*          m_ghostRectangle;
    QGraphicsRectItem*          m_textureBorder;
};

#endif // SPRITESHEETSCENE_HPP
