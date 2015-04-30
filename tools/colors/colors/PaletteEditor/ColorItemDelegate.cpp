#include "ColorItemDelegate.hpp"

#include <QPainter>

ColorItemDelegate::ColorItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

ColorItemDelegate::~ColorItemDelegate()
{
}

void ColorItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    static const QColor s_light = QColor(125, 125, 125);
    static const QColor s_dark = QColor(75, 75, 75);
    QRect   rect = option.rect;
    int     i = 0;
    QColor  current = index.data().value<QColor>();
    QColor  inverse(255 - current.red(), 255 - current.green(), 255 - current.blue());
    bool    selected = option.state & QStyle::State_Selected;

    painter->save();
    painter->setClipRect(rect);
    // Draw background grid
    for (int y = 0; y < rect.height(); y += 8)
    {
        for (int x = 0; x < rect.width(); x += 16)
        {
            painter->fillRect(x + rect.left(), y + rect.top(), 8, 8, (i % 2) ? s_light : s_dark);
            painter->fillRect(x + rect.left() + 8, y + rect.top(), 8, 8, (i % 2) ? s_dark : s_light);
        }
        ++i;
    }
    // Draw color
    if (selected)
        rect.adjust(8, 0, -8, 0);
    painter->fillRect(rect, current);
    painter->restore();
}

