#ifndef SUBRECTPREVIEW_HPP
#define SUBRECTPREVIEW_HPP

#include <QGraphicsView>

class QGraphicsScene;
class QGraphicsPixmapItem;
class QAction;

class GraphicsMark;

class TilePreview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TilePreview(QWidget* parent = nullptr);
    ~TilePreview();

    void    setRectangleSize(QSizeF const& size);
    void    setPixmap(QPixmap const& pixmap);

public slots:
    void    addVerticalMark();
    void    addHorizontalMark();
    void    removeMarks();
private:
    void    setupActions();
private:
    QList<GraphicsMark*>        m_marks;
    QGraphicsScene*             m_scene;
    QGraphicsPixmapItem*        m_pixmapItem;
    QAction*                    m_addVerticalMark;
    QAction*                    m_addHorizontalMark;
    QAction*                    m_clearMarks;
};

#endif // SUBRECTPREVIEW_HPP
