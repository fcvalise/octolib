#include "RectangleListView.hpp"

#include <QStyledItemDelegate>

namespace
{
    class ItemDelegate : public QStyledItemDelegate
    {
    public:
        explicit ItemDelegate(QObject* parent = nullptr) :
            QStyledItemDelegate(parent)
        {
        }

        virtual QString displayText(const QVariant &value, const QLocale &) const;
    };

    QString ItemDelegate::displayText(const QVariant &value, const QLocale &) const
    {
        QRectF  rect = value.value<QRectF>();

        return (QString("x: %0 y: %1 w: %2 h: %3").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height()));
    }
}

RectangleListView::RectangleListView(QWidget *parent) :
    QListView(parent)
{
    setItemDelegate(new ItemDelegate(this));
}

RectangleListView::~RectangleListView()
{

}

