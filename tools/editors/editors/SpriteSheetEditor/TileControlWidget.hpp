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
public slots:
    void    setTileSize(QSize const& size);
private slots:
    void    onSpinBoxChanged();
signals:
    void    tileSizeEdited(QSize const& size);
private:
    QSpinBox*   m_width;
    QSpinBox*   m_height;
};

#endif // TILECONTROLWIDGET_HPP
