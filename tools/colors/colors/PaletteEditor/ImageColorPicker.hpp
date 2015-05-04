#ifndef IMAGECOLORPICKER_HPP
#define IMAGECOLORPICKER_HPP

#include <QGraphicsView>

class ColorPickerItem;
class PaletteModel;

class ImageColorPicker : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ImageColorPicker(QWidget* parent);
    ~ImageColorPicker();

    PaletteModel*       paletteModel()const;
public slots:
    void                setColorCount(int count);
public:
    void                setImage(QPixmap const& pixmap);
private:
    ColorPickerItem*    createPickerItem(int index);
    void                updateColorPicker(int index, QPointF pos);
private slots:
    void                onPickerMoved(int index, QPointF pos);
private:
    QImage                  m_image;
    QGraphicsScene*         m_scene;
    QGraphicsPixmapItem*    m_pixmap;
    QList<ColorPickerItem*> m_pickers;
    PaletteModel*           m_model;
};

#endif // IMAGECOLORPICKER_HPP
