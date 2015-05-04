#include "ImageColorPicker.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <PaletteModel.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include <QRgb>

class ColorPickerItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

    static int const    CenterRadius = 2;
    static int const    BorderRadius = 8;
    static int const    CenterThickness = 1;
    static int const    BorderThickness = 2;
    static int const    TotalRadius = BorderRadius + BorderThickness;
public:
    explicit ColorPickerItem(int index);

    virtual QRectF  boundingRect() const;
    virtual void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);
signals:
    void            moved(int index, QPointF pos);
private:
    int     m_index;
};

void ColorPickerItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    emit moved(m_index, event->scenePos());
}

ColorPickerItem::ColorPickerItem(int index) :
    m_index(index)
{
    setActive(true);
    setFlags(QGraphicsItem::ItemSendsGeometryChanges | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF ColorPickerItem::boundingRect() const
{
    QPointF totalSize(TotalRadius, TotalRadius);
    QPointF position = pos();
    QRectF  rect(position - totalSize, position + totalSize);

    return (rect);
}

void ColorPickerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF center = pos();

    painter->save();
    painter->setPen(QPen(Qt::white, BorderThickness));
    painter->drawEllipse(center, BorderRadius + BorderThickness, BorderRadius + BorderThickness);
    painter->setPen(QPen(Qt::black, CenterThickness));
    painter->drawEllipse(center, CenterRadius, CenterRadius);
    painter->drawEllipse(center, BorderRadius, BorderRadius);
    painter->setPen(QPen(Qt::white, CenterThickness));
    painter->drawEllipse(center, CenterRadius + CenterThickness, CenterRadius + CenterThickness);
    painter->restore();
}

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
        }
    }
}

void ImageColorPicker::setImage(const QPixmap &pixmap)
{
    QSize   viewportSize = contentsRect().size();
    QPixmap scaledPixmap = pixmap.scaled(viewportSize, Qt::KeepAspectRatio);
    QPixmap thePixmap = scaledPixmap;

    if (m_pixmap == nullptr)
    {
        m_pixmap = m_scene->addPixmap(thePixmap);
        m_pixmap->setZValue(-1);
    }
    else
    {
        m_pixmap->setPixmap(thePixmap);
    }
    m_image = thePixmap.toImage();
    setSceneRect(m_pixmap->boundingRect());
    centerOn(m_pixmap);
}

ColorPickerItem *ImageColorPicker::createPickerItem(int index)
{
    ColorPickerItem*   item = new ColorPickerItem(index);

    connect(item, SIGNAL(moved(int, QPointF)), SLOT(onPickerMoved(int, QPointF)));
    return (item);
}

void ImageColorPicker::updateColorPicker(int index, QPointF pos)
{
    ColorPickerItem*    item = m_pickers.value(index, nullptr);
    QPointF             position = mapFromScene(item->pos());
    QRgb                rgb;

    if (item == nullptr)
        return;
    qDebug() << "pos: " << pos;
    qDebug() << "item: " << item->pos();
    qDebug() << "viewport: " << position;
    qDebug() << "global: " << mapToGlobal(item->pos().toPoint());
    qDebug() << "from global: " << mapFromGlobal(item->pos().toPoint());
    qDebug() << "dpi x: " << m_image.dotsPerMeterX();
    qDebug() << "dpi y: " << m_image.dotsPerMeterY();

    rgb = m_image.pixel(item->pos().toPoint() * 2);
    m_model->setColor(m_model->index(index), QColor::fromRgb(rgb));
}

void ImageColorPicker::onPickerMoved(int index, QPointF pos)
{
    ColorPickerItem*    item = m_pickers.at(index);

    updateColorPicker(index, pos);
}

#include "ImageColorPicker.moc"
