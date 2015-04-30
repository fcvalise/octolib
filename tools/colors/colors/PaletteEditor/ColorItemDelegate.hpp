#ifndef COLORITEMDELEGATE_HPP
#define COLORITEMDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QImage>

class ColorItemDelegate : public QStyledItemDelegate
{
public:
    explicit ColorItemDelegate(QObject* parent);
    ~ColorItemDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QImage  m_background;
};

#endif // COLORITEMDELEGATE_HPP
