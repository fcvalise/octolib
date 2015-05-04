#ifndef COLORPICKERITEM_HPP
#define COLORPICKERITEM_HPP
#include <QObject>
#include <QAbstractGraphicsShapeItem>

class QGraphicsEllipseItem;

class ColorPickerItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
public:
    explicit ColorPickerItem(int index, QGraphicsPixmapItem* pixmap);

    virtual QPainterPath    shape() const;
    virtual bool            contains(const QPointF &point) const;
    virtual QRectF          boundingRect() const;
    virtual void            paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual QVariant        itemChange(GraphicsItemChange change, const QVariant &value);
signals:
    void                    moved(int index);
private:
    QGraphicsEllipseItem*   m_centerBlack;
    QGraphicsEllipseItem*   m_centerWhite;
    QGraphicsEllipseItem*   m_borderBlack;
    QGraphicsEllipseItem*   m_borderWhite;
    QGraphicsPixmapItem*    m_pixmap;
    int                     m_index;
};

#endif // COLORPICKERITEM_HPP
