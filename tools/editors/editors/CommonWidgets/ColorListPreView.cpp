#include "ColorListPreView.hpp"

#include <cmath>

ColorListPreView::ColorListPreView(QWidget *parent) :
    QListView(parent)
{
    setViewportMargins(0, 0, 0, 0);
    setFlow(QListView::LeftToRight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

ColorListPreView::~ColorListPreView()
{
}

QRect ColorListPreView::visualRect(const QModelIndex &index) const
{
    QRect   rect = QListView::visualRect(index);

    if (index.isValid() == false)
        return (rect);
    if (flow() == QListView::LeftToRight)
    {
        int     width = contentsRect().width() / model()->rowCount();
        int     left = width * index.row();

        if (index.row() + 1 == model()->rowCount())
        {
            width = contentsRect().width() - left;
        }
        rect.setLeft(left);
        rect.setWidth(width);
    }
    return (rect);
}
