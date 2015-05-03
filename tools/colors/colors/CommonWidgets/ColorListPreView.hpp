#ifndef COLORLISTPREVIEW_HPP
#define COLORLISTPREVIEW_HPP
#include <QListView>

class ColorListPreView : public QListView
{
public:
    explicit ColorListPreView(QWidget* parent);
    ~ColorListPreView();

    virtual QRect visualRect(const QModelIndex &index) const;
};

#endif // COLORLISTPREVIEW_HPP
