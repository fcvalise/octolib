#include "ImageColorPicker.hpp"
#include "ColorPickerItem.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <PaletteModel.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QRgb>
#include <QPen>
#include <QtDebug>  // TEST

ImageColorPicker::ImageColorPicker(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmap(nullptr),
    m_model(new PaletteModel(this))
{
    setScene(m_scene);
}

ImageColorPicker::~ImageColorPicker()
{
}

PaletteModel *ImageColorPicker::paletteModel() const
{
    return (m_model);
}

void ImageColorPicker::setColorCount(int count)
{
    ColorPickerItem*   item = nullptr;

    if (count < m_pickers.size())
    {
        while (m_pickers.size() > count)
        {
            m_model->removeColor(m_model->index(m_pickers.size() - 1));
            m_scene->removeItem(m_pickers.back());
            delete m_pickers.back();
            m_pickers.pop_back();
        }
    }
    else if (count > m_pickers.size())
    {
        while (m_pickers.size() < count)
        {
            item = createPickerItem(m_pickers.size());

            m_scene->addItem(item);
            m_pickers.push_back(item);
            m_model->addColor();
            item->setZValue(1);
            item->setPos(mapToScene(viewport()->rect().center()));
            updatePickers();
        }
    }
}

void ImageColorPicker::setImage(const QPixmap &pixmap)
{
    QSize   viewportSize = contentsRect().size();
    QPixmap scaledPixmap = pixmap.scaled(viewportSize, Qt::KeepAspectRatio);

    m_originalPixmap = pixmap;
    if (m_pixmap == nullptr)
    {
        m_pixmap = m_scene->addPixmap(scaledPixmap);
        m_pixmap->setZValue(-1);
    }
    else
    {
        m_pixmap->setPixmap(scaledPixmap);
    }
    m_image = scaledPixmap.toImage();
    setSceneRect(m_pixmap->boundingRect());
    centerOn(m_pixmap);
    updatePickers();
}

ColorPickerItem *ImageColorPicker::createPickerItem(int index)
{
    ColorPickerItem*   item = new ColorPickerItem(index, m_pixmap);

    connect(item, SIGNAL(moved(int)), SLOT(onPickerMoved(int)));
    return (item);
}

void ImageColorPicker::updateColorPicker(int index)
{
    ColorPickerItem*    item = m_pickers.value(index, nullptr);
    QRgb                rgb;

    if (item == nullptr)
        return;
    rgb = m_image.pixel(item->pos().toPoint());
    m_model->setColor(m_model->index(index), QColor::fromRgb(rgb));
}

void ImageColorPicker::updatePickers()
{
    for (int i = 0; i < m_pickers.size(); ++i)
    {
        updateColorPicker(i);
    }
}

void ImageColorPicker::onPickerMoved(int index)
{
    updateColorPicker(index);
}

void ImageColorPicker::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    setImage(m_originalPixmap);
}
