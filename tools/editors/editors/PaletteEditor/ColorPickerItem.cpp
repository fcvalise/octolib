#include "ColorPickerItem.hpp"

#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

static constexpr int const    CenterRadius = 2;
static constexpr int const    BorderRadius = 8;
static constexpr int const    CenterThickness = 1;
static constexpr int const    BorderThickness = 1;
static constexpr QRectF const CenterBlackRect{-CenterRadius, -CenterRadius,
                                              CenterRadius * 2, CenterRadius * 2};
static constexpr QRectF const CenterWhiteRect{-(CenterRadius + CenterThickness), -(CenterRadius + CenterThickness),
                                              (CenterRadius + CenterThickness) * 2, (CenterRadius + CenterThickness) * 2};
static constexpr QRectF const BorderBlackRect{-BorderRadius, -BorderRadius,
                                              BorderRadius * 2, BorderRadius * 2};
static constexpr QRectF const BorderWhiteRect{-(BorderRadius + BorderThickness), -(BorderRadius + BorderThickness),
                                              (BorderRadius + BorderThickness) * 2, (BorderRadius + BorderThickness) * 2};

ColorPickerItem::ColorPickerItem(int index, QGraphicsPixmapItem *pixmap) :
    m_centerBlack(new QGraphicsEllipseItem(CenterBlackRect, this)),
    m_centerWhite(new QGraphicsEllipseItem(CenterWhiteRect, this)),
    m_borderBlack(new QGraphicsEllipseItem(BorderBlackRect, this)),
    m_borderWhite(new QGraphicsEllipseItem(BorderWhiteRect, this)),
    m_pixmap(pixmap),
    m_index(index)
{
    m_centerBlack->setPen(QPen(Qt::black, CenterThickness));
    m_centerWhite->setPen(QPen(Qt::white, CenterThickness));
    m_borderBlack->setPen(QPen(Qt::black, BorderThickness));
    m_borderWhite->setPen(QPen(Qt::white, BorderThickness));
    setFlags(QGraphicsItem::ItemSendsGeometryChanges | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF ColorPickerItem::boundingRect() const
{
    return (m_borderWhite->boundingRect());
}

void ColorPickerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_centerWhite->paint(painter, option, widget);
    m_centerBlack->paint(painter, option, widget);
    m_borderWhite->paint(painter, option, widget);
    m_borderBlack->paint(painter, option, widget);
}

QPainterPath ColorPickerItem::shape() const
{
    return (m_borderWhite->shape());
}

bool ColorPickerItem::contains(const QPointF &point) const
{
    return (m_borderWhite->contains(point));
}

QVariant ColorPickerItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange && m_pixmap)
    {
        QPointF newPos = value.toPointF();
        QRectF rect = m_pixmap->boundingRect();

        if (!rect.contains(newPos))
        {
            newPos.setX(qMin(rect.right() - 1, qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom() - 1, qMax(newPos.y(), rect.top())));
            return (newPos);
        }
    }
    else if (change == QGraphicsItem::ItemPositionHasChanged && m_pixmap)
    {
        emit moved(m_index);
    }
    return (QAbstractGraphicsShapeItem::itemChange(change, value));
}
