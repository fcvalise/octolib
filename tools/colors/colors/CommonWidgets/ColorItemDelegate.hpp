#ifndef COLORITEMDELEGATE_HPP
#define COLORITEMDELEGATE_HPP

#include <QStyledItemDelegate>

class ColorItemDelegate : public QStyledItemDelegate
{
public:
    explicit ColorItemDelegate(QObject* parent);
    ~ColorItemDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COLORITEMDELEGATE_HPP
