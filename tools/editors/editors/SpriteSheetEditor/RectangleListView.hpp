#ifndef RECTANGLELISTVIEW_HPP
#define RECTANGLELISTVIEW_HPP
#include <QListView>

class RectangleListView : public QListView
{
public:
    explicit RectangleListView(QWidget* parent = nullptr);
    ~RectangleListView();
};

#endif // RECTANGLELISTVIEW_HPP
