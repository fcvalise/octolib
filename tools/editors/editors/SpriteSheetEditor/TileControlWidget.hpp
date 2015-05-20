#ifndef TILECONTROLWIDGET_HPP
#define TILECONTROLWIDGET_HPP

#include <QWidget>

class QSpinBox;

class TileControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TileControlWidget(QWidget* parent = nullptr);
    ~TileControlWidget();

    void    setTileSize(QSizeF const& size);
private slots:
    void    onSpinBoxChanged();
signals:
    void    tileSizeChanged(QSize const& size);
private:
    QSpinBox*   m_width;
    QSpinBox*   m_height;
};

#endif // TILECONTROLWIDGET_HPP
