#ifndef SUBRECTPREVIEW_HPP
#define SUBRECTPREVIEW_HPP

#include <QGraphicsView>

class SpriteSheetModel;

class QGraphicsScene;
class QGraphicsPixmapItem;
class QAction;
class QItemSelectionModel;

class GraphicsMark;

class TilePreview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TilePreview(QWidget* parent = nullptr);
    ~TilePreview();

    void    setModel(SpriteSheetModel* model);
    void    setSelectionModel(QItemSelectionModel* model);
public slots:
    void    addVerticalMark();
    void    addHorizontalMark();
    void    removeMarks();
private:
    void    setupActions();
private slots:
    void    updateTilePreview();
private:
    QList<GraphicsMark*>        m_marks;
    SpriteSheetModel*           m_model;
    QItemSelectionModel*        m_selectionModel;
    QGraphicsScene*             m_scene;
    QGraphicsPixmapItem*        m_pixmapItem;
    QGraphicsRectItem*          m_borderItem;
    QAction*                    m_addVerticalMark;
    QAction*                    m_addHorizontalMark;
    QAction*                    m_clearMarks;
};

#endif // SUBRECTPREVIEW_HPP
