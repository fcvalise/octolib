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
protected:
    virtual void        resizeEvent(QResizeEvent *event);
private:
    ColorPickerItem*    createPickerItem(int index);
    void                updateColorPicker(int index);
    void                updatePickers();
private slots:
    void                onPickerMoved(int index);
private:
    QImage                  m_image;
    QPixmap                 m_originalPixmap;
    QGraphicsScene*         m_scene;
    QGraphicsPixmapItem*    m_pixmap;
    QList<ColorPickerItem*> m_pickers;
    PaletteModel*           m_model;
};



#endif // IMAGECOLORPICKER_HPP
